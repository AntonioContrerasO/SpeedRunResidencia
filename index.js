const express = require('express');
const app = express();
const port = 3000;

app.use(express.json());

app.get('/', (req, res) => {
  res.send('Hola desde el servidor Express.js');
});

app.listen(port, () => {
  console.log(`Servidor Express.js en ejecución en http://localhost:${port}`);
});

