FROM alpine:3.12

RUN apk add autoconf automake libtool curl make g++ unzip zip bash 

WORKDIR /src

COPY . .
RUN ./autogen.sh
RUN ./configure --disable-shared
RUN make


#check on alpine will no pass
#RUN make check

# install localy on docker so container can serve as standalone protoc
RUN make install


# export installed artifacts to /dits so it can later be extracted using docker cp and released in github
RUN mkdir /dist
RUN make install DESTDIR=/dist

WORKDIR /dist
RUN zip -r dist.zip **



# install required grpc plugins
RUN apk add go grpc

ENV GO111MODULE=on
ENV GOPATH=/tmp/go
ENV GOBIN=/tmp/go/bin
ENV GOCACHE=/tmp/go/cache
ENV PATH=/tmp/go/bin/:$PATH

RUN go get github.com/golang/protobuf/protoc-gen-go
RUN go get github.com/golang/protobuf/proto
RUN go get google.golang.org/grpc

ENTRYPOINT ["/usr/local/bin/protoc"]