```bash
mkdir build_docker_windows
cd build_docker_windows
git clone --recursive https://github.com/tioui/Aquaria_Randomizer.git src
cp -rp src/docker_windows_compilation/* ./
sudo docker build  -t "windows_build_32" .
sudo docker run --name windows_build_32 --mount type=bind,source="$(pwd)"/output,target=/output -it windows_build_32
sudo docker container rm windows_build_32
sudo docker image rm windows_build_32
sudo docker system prune # Warning prune every unused docker things. Use at your own risk.
```
