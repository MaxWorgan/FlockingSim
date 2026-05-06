# FlockingSim

A real-time 3D flocking simulation built with [openFrameworks](https://openframeworks.cc). A flock of 100 agents navigate a 3D space using classic Boids rules — separation, alignment, and cohesion — with layered forces including attractors, repulsors, wind, and a center pull. The simulation can be driven autonomously or steered live via OSC.

## Features

- **Boids flocking** — separation, alignment, and cohesion with tunable strengths and neighbourhood radius
- **Attractors & repulsors** — place random force points that perturb the flock; auto-spawn mode fires them on a random timer
- **IPC shared memory** — all agent positions are published every frame into a POSIX shared memory segment so external processes can read swarm state without network overhead
- **Wind** — a continuous directional force with adjustable amount and multiplier
- **Center pull** — keeps the flock loosely anchored to a configurable region
- **OSC control** — receive `/flock/event` to trigger attractors, `/flock/position` to puppet individual agents, and `/flock/pca` to stream 10-channel PCA data into the sparkline display
- **Camera modes** — free EasyCam orbit or a follow-cam that tracks the swarm's center of mass; toggle orthographic projection and adjust FOV/distance from the GUI
- **Sparklines** — 10 colour-coded time-series overlays for visualising incoming PCA data
- **Swarm stats** — bounding box, center of mass, average velocity, and entropy tracked each frame
- **Data export** — press `w` to write all agent positions to `data.csv`
- **Separate GUI window** — all parameters live in a detached panel so the main view is uncluttered

## Requirements

- openFrameworks (tested on macOS 14.6, targeting `gnu++17`)
- Addons:
  - `ofxGui`
  - `ofxOsc`
  - `ofxRange`
  - `ofxSparklines`

## Building

Open `Flocking.xcodeproj` in Xcode and build, or use the Makefile:

```bash
make
make run
```

Ensure `OF_ROOT` in `config.make` points to your local openFrameworks installation.

## OSC

| Address | Args | Description |
|---|---|---|
| `/flock/event` | — | Spawn a random attractor and repulsor |
| `/flock/position` | `int index, float x, float y, float z` | Move agent at `index` to a position |
| `/flock/pca` | `float[10]` | Push a 10-element PCA frame to the sparklines |

Receive port: **12345**  
Send port: **7779** (localhost)

## Keyboard Shortcuts

| Key | Action |
|---|---|
| `e` | Toggle auto attractor/repulsor spawning |
| `a` | Toggle attractor visualisation |
| `s` | Toggle sparkline overlay |
| `w` | Toggle CSV position recording |
| `f` | Toggle fullscreen |

## Shared Memory IPC

Every frame, `AgentController` writes the full array of agent positions into a POSIX shared memory segment, making the live swarm state available to any other process on the same machine with zero network overhead.

| Segment | Name | Content |
|---|---|---|
| Position data | `/position_data` | `glm::vec3[N]` — one entry per agent, updated each tick |
| Mutex | `/mutex_lock` | `pthread_mutex_t` with `PTHREAD_PROCESS_SHARED` — guards concurrent reads |

A consumer process calls `shm_open("/position_data", O_RDONLY, ...)` and `mmap` to map the segment, then locks `/mutex_lock` before reading. The segment size is `N × sizeof(glm::vec3)` bytes (N = 100 agents by default → 1200 bytes). The segment is unlinked cleanly on exit.

## GUI Parameters

All parameters are adjustable at runtime in the floating GUI panel.

**Flocking**
- Separation / Alignment / Cohesion strength
- Neighbourhood distance
- Lower / Higher threshold (controls zone boundaries)
- Draw neighbourhood / bounding box overlays

**Attractors & Repulsors**
- Strength and minimum distance for each type
- Buttons to add random instances or clear all

**Center Pull**
- Pull strength and maximum distance from center

**Wind**
- Wind amount and multiplier

**Camera**
- Follow camera toggle
- Distance and FOV
- Orthographic projection toggle
