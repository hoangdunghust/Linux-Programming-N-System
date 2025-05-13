// app.js
const net = require("net");
const readline = require("readline");
const { addConnection, removeConnection } = require("./connection");
const {
  showMyIP,
  showMyPort,
  connectToPeer,
  listAllConnections,
  terminateConnection,
  sendMessage,
  addNameToConnection,
  exitProgram,
} = require("./Function");

const PORT = process.argv[2] || 9000;
const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout,
});
let server = null;

// CLI
console.log("Nhập 'help' để xem danh sách lệnh");

// Hàm hiển thị lệnh help
function showHelp() {
  console.log(`
help                      - Hiển thị các lệnh
myip                      - Hiển thị địa chỉ IP của bạn
myport                    - Hiển thị port đang lắng nghe
connect <ip> <port>       - Kết nối tới peer khác
list                      - Liệt kê các kết nối đang hoạt động
terminate <id>            - Ngắt kết nối theo ID
send <id> <message>       - Gửi tin nhắn tới kết nối theo ID
addname <id> <name>       - Đặt tên cho kết nối ID bằng name
exit                      - Thoát chương trình
  `);
}

rl.on("line", (input) => {
  const args = input.trim().split(" ");
  const command = args[0];

  switch (command) {
    case "help":
      showHelp();
      break;

    case "myip":
      showMyIP();
      break;

    case "myport":
      showMyPort(PORT);
      break;

    case "connect":
      const ip = args[1];
      const port = parseInt(args[2]);
      connectToPeer(ip, port);
      break;

    case "list":
      listAllConnections();
      break;

    case "terminate":
      const id = parseInt(args[1]);
      terminateConnection(id);
      break;

    case "send":
      const identifier = args[1];
      const message = args.slice(2).join(" ");
      sendMessage(identifier, message);
      break;

    case "addname":
      const targetId = parseInt(args[1]);
      const newName = args[2];
      addNameToConnection(targetId, newName);
      break;

    case "exit":
      exitProgram();
      break;

    default:
      console.log("Lệnh không hợp lệ. Nhập 'help' để xem các lệnh.");
  }
});

// TCP server để nhận kết nối
server = net.createServer((socket) => {
  const ip = socket.remoteAddress;
  const port = socket.remotePort;
  addConnection(socket, ip, port);
  console.log(`Peer mới kết nối: ${ip}:${port}`);

  socket.on("data", (data) => {
    console.log(`\nNhận từ ${ip}:${port}: ${data.toString()}`);
    rl.prompt();
  });

  socket.on("close", () => {
    removeConnection(socket);
    console.log(`Mất kết nối với ${ip}:${port}`);
  });
});

server.listen(PORT, () => {
  console.log("Server đang chạy tại port:", PORT);
});
