from threading import Thread
import zmq, socketio, eventlet
from flask import Flask, render_template
from flask_socketio import send

sio = socketio.Server()
app = Flask(__name__)

@app.route('/')
def index():
    return render_template('index.html')

@sio.on('connect')
def connect(socket_id, environment):
    print 'connect sid: %s, env: %s' % (socket_id, environment)

@sio.on('message')
def message(socket_id, data):
    print 'message sid: %s, data: %s' % (socket_id, data)

@sio.on('disconnect')
def disconnect(socket_id):
    print 'disconnect sid: %s' % socket_id


def init_zeromq():
    
    print 'zmq version %s' % zmq.zmq_version()
    
    context = zmq.Context()
    subscriber = context.socket(zmq.SUB)
    subscriber.connect("tcp://localhost:5556")
    subscriber.setsockopt(zmq.SUBSCRIBE, "")
    
    while True:
        r = subscriber.recv()
        print r
    
    
    
    subscriber.close()
    context.term()


if __name__ == '__main__':
    
    # start 0mq, it blocks so we start a thread
    t = Thread(target=init_zeromq)
    t.start()
    
    # start flask
    app = socketio.Middleware(sio, app)
    eventlet.wsgi.server(eventlet.listen(('', 8000)), app)
    
    t.join()
