import serial
import time

def connect():
    conn = serial.Serial(port = '/dev/ttyACM0', baudrate=9600, timeout = 1)

    return conn

def send(conn):
    while True:
        data = input("Input : ")
        if (data == 'q'):
            break
        conn.write(data.encode())
        time.sleep(0.1)

        if (conn.readable()):
            recv = conn.readline().decode().strip('\r\n')
            if (len(recv) > 0):
                print("recv : " + str(recv))

    return


if __name__ == "__main__":
    conn = connect()
    send(conn)
    conn.close()