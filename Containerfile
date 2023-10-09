FROM debian:testing AS build
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends build-essential ca-certificates git libglib2.0-dev ninja-build pkg-config python3 python3-venv
RUN git clone -b v8.0.4 --depth 1 https://gitlab.com/qemu-project/qemu.git
RUN cd qemu && mkdir build && cd build && ../configure --target-list=aarch64-linux-user --static --disable-pie && make -j $(nproc) && cp qemu-aarch64 /aarch64-binfmt-P
COPY register.c register.c
RUN gcc -Wall -Wextra -Werror -static -o /register-aarch64-binfmt-P register.c

FROM scratch
COPY --from=build /aarch64-binfmt-P /aarch64-binfmt-P
COPY --from=build /register-aarch64-binfmt-P /register-aarch64-binfmt-P
CMD [ "/register-aarch64-binfmt-P" ]
