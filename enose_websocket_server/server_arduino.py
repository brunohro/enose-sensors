from websocket_server import WebsocketServer
import MySQLdb

mq2 = 0
mq3 = 0
mq5 = 0
mq135 = 0

con = MySQLdb.connect("localhost", "root", "", "websocket")

# Função chamada quando um novo cliente se conecta
def new_client(client, server):
    print(f"Cliente {client['id']} conectado")

# Função chamada quando uma mensagem é recebida 
def message_received(client, server, message):
    sensor_values = message.split(",")

    mq2 = float(sensor_values[0]) 
    mq3 = float(sensor_values[1])  
    mq5 = float(sensor_values[2])
    mq135 = float(sensor_values[3])

    print("Valor % MQ-2: "+str(mq2))

    print("Valor % MQ-3: "+str(mq3))
    
    print("Valor % MQ-5: "+str(mq5))

    print("Valor % MQ-135: "+str(mq135))
   
    print("")

    try:
        cursor = con.cursor()  # Inicia um cursor do banco de dados
        cursor.execute("INSERT INTO sensor(MQ2, MQ3, MQ5, MQ135) VALUES(%s, %s, %s, %s)", (mq2, mq3, mq5, mq135))  # Comando para inserir valores no banco
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
