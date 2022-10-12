#pragma once

#include "ofMain.h"
#include <stdio.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <pthread.h>
#include <cerrno>
#include <fcntl.h>


/*
 Adapted from ofxSharedMemory by Trent Brooks
*/

template<class T>
class ofxSharedMemory {
    
public:

    ofxSharedMemory();
    ~ofxSharedMemory();
    
    void setup(int size);
    
    bool connect();
    void close();

    void setData(T sourceData);
    int des_mutex;
    pthread_mutex_t* mutex;
    
    // data to share
    T getData();
    
    const char *MUTEX = "/mutex_lock";
    const char *SHARED_DATA = "/position_data";

protected:

    int memorySize;
    
    //unsigned char *sharedData;
    T sharedData;
    bool isReady;
};


//--------------------------------------------------------------
/*
 Implementation
 Keeping implementation inside the .h to make the client side neater.
 Otherwise the testApp has to import ofxSharedMemory.cpp as well as ofxSharedMemory.h
 */
//--------------------------------------------------------------
template <typename T>
ofxSharedMemory<T>::ofxSharedMemory(){
    
    sharedData = NULL;
    memorySize = 0;
    isReady = false;
}

template <typename T>
ofxSharedMemory<T>::~ofxSharedMemory(){
    close();
}

template <typename T>
void ofxSharedMemory<T>::setup(int memorySize) {
    
    this->memorySize = memorySize;

}

template <typename T>
void ofxSharedMemory<T>::close() {
    
    shm_unlink(SHARED_DATA);
    shm_unlink(MUTEX);
    munmap(sharedData, memorySize);
    munmap(mutex, sizeof(pthread_mutex_t));

}

template <typename T>
bool ofxSharedMemory<T>::connect() {
    
    // create/connect to shared memory from dummy file
    int descriptor = shm_open(SHARED_DATA, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    if(descriptor == -1) {
        isReady = false;
        return false;
    }
    
    ofLog() << "Shared memory file descriptor " << descriptor;
    
    // map to memory
    ftruncate(descriptor, memorySize);
    sharedData = (T) mmap(NULL, memorySize, PROT_WRITE | PROT_READ, MAP_SHARED, descriptor, 0);
    if(sharedData == NULL) {
        shm_unlink(SHARED_DATA);
        isReady = false;
        return false;
    }
    
    // create the mutex shared memory
    des_mutex = shm_open(MUTEX, O_CREAT | O_RDWR | O_TRUNC, S_IRWXU | S_IRWXG);
    
    if (des_mutex < 0) {
        shm_unlink(MUTEX);
        perror("failure on shm_open on des_mutex");
        ofLog() << "Error code: " << errno;
        isReady = false;
        return false;
    }
    
    if (ftruncate(des_mutex, sizeof(pthread_mutex_t)) == -1) {
        perror("Error on ftruncate to sizeof pthread_cond_t\n");
        isReady = false;
        return false;
    }
    
    ofLog() << "Size of mutex: " << sizeof(pthread_mutex_t);
    
    mutex = (pthread_mutex_t*) mmap(NULL, sizeof(pthread_mutex_t),
                                    PROT_READ | PROT_WRITE, MAP_SHARED, des_mutex, 0);
    
    if (mutex == MAP_FAILED ) {
        perror("Error on mmap on mutex\n");
        isReady = false;
        return false;
    }
    
    /* set mutex shared between processes */
    pthread_mutexattr_t mutexAttr;
    pthread_mutexattr_init(&mutexAttr);
    pthread_mutexattr_setpshared(&mutexAttr, PTHREAD_PROCESS_SHARED);
    pthread_mutex_init(mutex, &mutexAttr);
    
    isReady = true;
    return true;
}

// copies source data to shared data
template <typename T>
void ofxSharedMemory<T>::setData(T sourceData) {
    pthread_mutex_lock(mutex);
    memcpy(sharedData, sourceData, memorySize);
    pthread_mutex_unlock(mutex);
}

// returns shared data
template <typename T>
T ofxSharedMemory<T>::getData() {
    return sharedData;
}
