from flask import Flask, request, jsonify
import mysql.connector

app = Flask(__name__)

# MySQL 데이터베이스 연결 설정
db = mysql.connector.connect(
    host="database-1.czkmo68qelp7.ap-northeast-2.rds.amazonaws.com",
    user="mk",
    password="1234",
    database="Driving"
)

@app.route('/api/signup', methods=['POST'])

def signup():
    data = request.get_json()
    print(data)
    id = data.get('user_id')
    password = data.get('user_password')
    name = data.get('user_name')
    birthday = data.get('user_birthday')
    print(1)

    # # 데이터베이스에서 사용자가 이미 존재하는지 확인
    cursor = db.cursor()
    # cursor.execute("SELECT * FROM member WHERE ID = %s", (id,))
    # user = cursor.fetchone()

    # if user:
    jsonify({'error': 'Username already exists'}), 400
    
        # 새로운 사용자 생성
    cursor.execute("INSERT INTO member (Birthday, Name, ID, Password) VALUES (%s, %s, %s, %s)", (birthday, name, id, password))
    print(2)
    db.commit()
    print(3)
    return jsonify({'message': '회원가입 완료'}), 201

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000, debug=True)
