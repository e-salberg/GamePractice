trying to recreate Atari's Asteroids game. Can be played [here](https://luin213.itch.io/asteroids) on itch.io

![screen_shot}(Screenshot.png)

# Build and Run locally
```
mkdir build
cmake -B build
cmake --build build
./build/asteroids
```

# Build for Web
```
cd build/web
emcmake cmake ../.. -DPLATFORM=Web
emmake make
```

# Run web build locall
```
emrun --browser "/mnt/c/Program Files/Google/Chrome/Application/chrome.exe" pool.html
```
