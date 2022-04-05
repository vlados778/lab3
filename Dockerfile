FROM debian:latest

RUN apt update && apt install -y g++

WORKDIR /home

COPY main.cpp .

RUN g++ ./main.cpp -o main
