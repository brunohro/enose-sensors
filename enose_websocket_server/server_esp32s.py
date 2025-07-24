from websocket_server import WebsocketServer
import MySQLdb

mq5 = 0
mq8 = 0


con = MySQLdb.connect("localhost", "root", "", "websocket")

# Função chamada quando um novo cliente se conecta
def new_client(client, server):
    print(f"Cliente {client['id']} conectado")

# Função chamada quando uma mensagem é recebida 
def message_received(client, server, message):
    sensor_values = message.split(",")

    mq5 = float(sensor_values[0])  
    mq8 = float(sensor_values[1])
    

    print("Valor % MQ-5: "+str(mq5))
    print("Valor % MQ-8: "+str(mq8))
   
    print("")

    try:
        cursor = con.cursor()  # Inicia um cursor do banco de dados
        # cursor.execute("ALTER TABLE sensor ADD COLUMN MQ2 FLOAT NULL, ADD COLUMN MQ8 FLOAT NULL, ADD COLUMN MQ5 FLOAT NULL, ADD COLUMN MQ8 FLOAT NULL, ADD COLUMN MQ135 FLOAT NULL;")
        cursor.execute("INSERT INTO sensor (MQ5, MQ8) VALUES (%s, %s)", (mq5,mq8))  # Comando para inserir valores no banco
        con.commit()  # Executa o comando do banco de dados
    except MySQLdb.IntegrityError:
        print("Falha ao inserir valores no banco de dados.")
    finally:
        cursor.close()
    
    server.send_message(client, "Mensagem recebida com sucesso")

# Criação do servidor WebSocket
server = WebsocketServer(host='192.168.147.91', port=8765)
server.set_fn_new_client(new_client)
server.set_fn_message_received(message_received)

print("Servidor WebSocket iniciado...")



server.run_forever()
