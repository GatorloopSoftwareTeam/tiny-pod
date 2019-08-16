from flask import Flask, render_template, jsonify
from manage_database import getTableAccelaration, getTableVoltage, getTableTemperature, getTableGyroscope
from manage_database import insertTableTemperature, insertTableAccelaration, insertTableGyroscope, insertTableVoltage
from drivers import tm4c

app = Flask(__name__)

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/dashboard')
@app.route('/dashboard/')
def dashboard():
    return render_template('dashboard.html')

@app.route('/api/temperature', methods = ['GET'])
def getTemperature():
    temp = [{'t': getTableTemperature()[0][1] }]
    return jsonify(temp)

@app.route('/api/accelaration', methods = ['GET'])
def getAccelaration():
    temp1 = getTableAccelaration()
    temp2 = [{'x': temp1[0][1], 'y': temp1[0][2], 'z': temp1[0][3] }]
    return jsonify({'a': temp2})

@app.route('/api/gyroscope', methods = ['GET'])
def getGyroscope():
    temp1 = getTableGyroscope()
    temp2 = [{'x': temp1[0][1], 'y': temp1[0][2], 'z': temp1[0][3] }]
    return jsonify({'g': temp2})

@app.route('/api/voltage', methods = ['GET'])
def getVoltage():
    temp = [{'v': getTableVoltage()[0][1] }]
    return jsonify(temp)

#rough testing
# @app.route('/sensordatas')
# def sensordatas():
#     return render_template('page.html')


if __name__ == '__main__':
    tm4c.init(insertTableTemperature, insertTableAccelaration, insertTableGyroscope, insertTableVoltage)
    app.run(debug=True, host='0.0.0.0')
