docker build  -t "windows_build_32" .
docker run --name windows_build_32 --mount type=bind,source="$(pwd)"/output,target=/output -it windows_build_32
docker container rm windows_build_32
docker image rm windows_build_32
