from twisted.internet import protocol, reactor, endpoints

import json
import rc4

SPEED = 4
KEY = "yellowsubmarine" # tmp, redis session key based on username?

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
        # NOTE: this might be slow, convert to hex before sending?
        data = rc4.decrypt(KEY, data.hex()) 
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
            
            ret_data = json.dumps(foo(self.x, self.y)).encode()
            enc_data = rc4.encrypt(KEY, str(ret_data)) # str?
            # print(ret_data, enc_data); quit()
            self.transport.write(enc_data)

class TestFactory(protocol.Factory):
    def buildProtocol(self, addr):
        return Test()

endpoints.serverFromString(reactor, "tcp:1234").listen(TestFactory())
reactor.run()
