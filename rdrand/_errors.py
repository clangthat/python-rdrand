""" Error class for rdrand """

class RdrandBaseException(BaseException):
    pass

class InstructionNotSupported(RdrandBaseException):
    pass

