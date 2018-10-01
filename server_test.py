from twisted.internet import protocol, reactor, endpoints

import json

SPEED = 4

def foo(x, y):
    payload = {
        "command": 3,
        "username": "vesche",
        "arguments": {
            "x": x,
            "y": y
        }
    }
    return payload

class Test(protocol.Protocol):

    def __init__(self):
        self.x = 0
        self.y = 0

    def dataReceived(self, data):
        test = json.loads(data)
        print("RECV: {}".format(test))

        if test['command'] == 'move':
            # do things here
            d = test['arguments']['direction']
            if d == 'up':
                self.y -= SPEED
            elif d == 'down':
                self.y += SPEED
            elif d == 'left':
                self.x -= SPEED
            elif d == 'right':
                self.x += SPEED
            self.transport.write( json.dumps(foo(self.x, self.y)).encode() )

class TestFactory(protocol.Factory):
    def buildProtocol(self, addr):
        return Test()

endpoints.serverFromString(reactor, "tcp:1234").listen(TestFactory())
reactor.run()
