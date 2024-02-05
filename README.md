# cache_dvf_db
Cache the dvf DB in a msgpack format on a redis server

## How to install the dev environment;  

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


### Step 2. setup the http server with the redis client.

From the ``network_components/http_redis_client`` dir.
- Build the image:
```bash
docker build -t llvm_redispp_crow .
```

- Then run the container:
```bash
docker run -it --network mynetwork -v /root/Dockerfolder/host/share/host:/workspace --name cont_llvm_redispp_crow llvm_redispp_crow /bin/bash


### Step 3. Build the nginx load balancer.

From the ``network_components/nginx_load_balancer`` dir:

- Build the nginx image:
```bash
docker build -t my-nginx-load-balancer .
```

- Run the nginx container:
```bash
docker run --name nginx-lb --net mynetwork -p 80:80 my-nginx-load-balancer
```