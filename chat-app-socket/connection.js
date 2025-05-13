// connections.js
const connections = [];
let nextId = 1; // Biến toàn cục để quản lý ID kết nối tiếp theo

// Thêm một kết nối mới vào danh sách
function addConnection(socket, ip, port, name = null) {
  const connection = {
    id: nextId++, // Sử dụng biến nextId để đảm bảo ID duy nhất
    socket,
    ip,
    port,
    name: name || `Peer-${nextId}`,
  };
  connections.push(connection);
}

// Xóa một kết nối khỏi danh sách
function removeConnection(socket) {
  const index = connections.findIndex((c) => c.socket === socket);
  if (index >= 0) connections.splice(index, 1);
}

// Liệt kê tất cả các kết nối
function listConnections() {
  if (connections.length === 0) {
    console.log("Không có kết nối nào.");
  } else {
    console.log("Danh sách kết nối:");
    connections.forEach((conn) => {
      console.log(`${conn.id}. ${conn.name} - ${conn.ip}:${conn.port}`);
    });
  }
}

// Lấy kết nối theo ID
function getConnectionById(id) {
  return connections.find((conn) => conn.id === id);
}

module.exports = {
  addConnection,
  removeConnection,
  listConnections,
  getConnectionById,
  connections,
};
