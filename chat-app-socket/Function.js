// File: Function.js
const net = require("net");
const readline = require("readline");
const { getMyIP, isValidIP } = require("./helpers");
const {
  addConnection,
  removeConnection,
  listConnections,
  getConnectionById,
  connections,
} = require("./connection");

// Hàm hiển thị IP của bạn
function showMyIP() {
  console.log("IP của bạn là:", getMyIP());
}

// Hàm hiển thị port đang lắng nghe
function showMyPort(port) {
  console.log("Đang lắng nghe ở port:", PORT);
}

// Hàm kết nối đến peer khác
function connectToPeer(ip, port) {
  if (!isValidIP(ip) || isNaN(port)) {
    console.log("Địa chỉ IP hoặc port không hợp lệ");
    return;
  }
  const socket = new net.Socket();
  socket.setTimeout(5000); // Timeout 5 giây
  socket.connect(port, ip, () => {
    addConnection(socket, ip, port);
    console.log("Đã kết nối đến", ip + ":" + port);
  });

  socket.on("data", (data) => {
    const conn = connections.find((c) => c.socket === socket);
    const name = conn.name || "";
    console.log(
      `\nNhận từ ${name}:${conn.ip}:${conn.port}: ${data.toString()}`
    );
    rl.prompt();
  });

  socket.on("close", () => {
    removeConnection(socket);
    console.log(`Mất kết nối với ${ip}:${port}`);
  });
}

// Hàm liệt kê các kết nối
function listAllConnections() {
  listConnections();
  rl.prompt();
}

// Hàm ngắt kết nối theo ID
function terminateConnection(id) {
  const conn = getConnectionById(id);
  if (!conn) {
    console.log("ID không tồn tại");
    return;
  }
  conn.socket.end();
  removeConnection(conn.socket);
  console.log("Đã ngắt kết nối");
}

// Hàm gửi tin nhắn tới kết nối theo ID hoặc tên
function sendMessage(identifier, message) {
  let target;
  if (!isNaN(parseInt(identifier))) {
    const id = parseInt(identifier);
    target = connections.find((c) => c.id === id);
  } else {
    target = connections.find((c) => c.name === identifier);
  }

  if (!target) {
    console.log("ID hoặc tên không hợp lệ.");
  } else {
    target.socket.write(message);
    console.log(
      `\nĐã gửi đến ${target.name} (${target.ip}:${target.port}): ${message}`
    );
  }
}

// Hàm gán tên cho kết nối
function addNameToConnection(id, newName) {
  const connect = connections.find((c) => c.id === id);
  if (!connect) {
    console.log("Không tìm thấy ID kết nối");
  } else {
    connect.name = newName;
    console.log(`Đã gán tên '${newName}' cho kết nối ID ${id}`);
  }
}

// Hàm thoát chương trình
function exitProgram() {
  console.log("🔚 Đang thoát...");
  process.exit(0);
}
module.exports = {
  showMyIP,
  showMyPort,
  connectToPeer,
  listAllConnections,
  terminateConnection,
  sendMessage,
  addNameToConnection,
  exitProgram,
};
