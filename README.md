⚠️ 🚫 🚧 🚧 WIP 🚧 🚧 🚫 ⚠️ 

# cache_dvf_db
Cache the dvf DB in a msgpack format on a redis server
  

### Step 1. setup the network and the redis server.
Using docker.

- Create a docker network:
```bash
docker network create mynetwork
```

- Pull redis image: 
```bash
docker pull redis
```

```bash
docker run --name myredis --network mynetwork -d redis
```

### Step 2. Setup the http server with the redis client.

From the ``network_components/http_redis_client`` dir.
- Build the image:
```bash
docker build -t llvm_redispp_crow .
```

- Then run the container:
```bash
docker run -it --network mynetwork -v path_to_dir:/workspace --name cont_llvm_redispp_crow llvm_redispp_crow /bin/bash
```

### Step 3 Build the redis client.

From the ``network_comps/http_redis_client/build`` dir.

- Run Cmake to generate makefile:
``` bash
cmake ..
```

- Run make to compile:
```bash
make
```

- Run the redis client:
```bash
./RedisTest
```

- Remove current build:
```bash
make clean
```

From the project root dir.
- Remove ``build`` dir before generating a new makefile:
```bash
rm -r build
mkdir build
```

### Step 3 - optional Build and run tests with GoogleTest.

From the ``network_components/http_redis_client`` dir:

- Generate the build system:
```bash
cmake -S . -B build -DENABLE_GTEST=ON
```

- Build the executable and the tests:
```bash
cmake --build build
```

- Run the tests:
```bash
cd build && ctest
```


### Step 4. Build the nginx load balancer.

From the ``network_components/lb`` dir:

- Build the nginx image:
```bash
docker build -t my-nginx-load-balancer .
```

- Run the nginx container:
```bash
docker run --name nginx-lb --net mynetwork -p 80:80 my-nginx-load-balancer
```

