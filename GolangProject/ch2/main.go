package main

import (
    "log"
    "net/http"

    "github.com/gorilla/websocket"
)

var upgrader = websocket.Upgrader{
    ReadBufferSize:  1024,
    WriteBufferSize: 1024,
}

func echo(w http.ResponseWriter, r *http.Request) {
    // 将HTTP连接升级为WebSocket连接
    conn, err := upgrader.Upgrade(w, r, nil)
    if err != nil {
        log.Println(err)
        return
    }
    defer conn.Close()

    for {
        // 从WebSocket连接中读取消息
        messageType, p, err := conn.ReadMessage()
        if err != nil {
            log.Println(err)
            return
        }
        // 将消息写回到WebSocket连接中
        if err := conn.WriteMessage(messageType, p); err != nil {
            log.Println(err)
            return
        }
    }
}

func main() {
    // 设置WebSocket路由
    http.HandleFunc("/echo", echo)

    // 启动WebSocket服务器，监听在localhost:8080
    log.Fatal(http.ListenAndServe(":8080", nil))
}

