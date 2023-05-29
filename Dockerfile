FROM python:2.7.18-buster


COPY ./setup.sh ./

RUN ./setup.sh

WORKDIR /home

COPY ./evaluation ./evaluation
COPY ./payloads ./payloads 
COPY ./source ./source

CMD bash
