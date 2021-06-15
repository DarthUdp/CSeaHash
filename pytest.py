import ctypes
import pathlib
import binascii


class SeahashState(ctypes.Structure):
    _fields_ = [
        ("a", ctypes.c_ulong),
        ("b", ctypes.c_ulong),
        ("c", ctypes.c_ulong),
        ("d", ctypes.c_ulong),
        ("written", ctypes.c_ulong),
    ]


if __name__ == '__main__':
    libname = pathlib.Path().absolute()
    libname = libname.joinpath("cmake-build-debug/libcseahash.so")
    c_lib = ctypes.CDLL(libname)
    val = b"this is a string val"
    state = ctypes.pointer(SeahashState())
    c_lib.seahash_pre_seed(state)
    ret = ctypes.create_string_buffer(bytes(8), 8)
    ctypes.c_ulong(c_lib.seahash_buff_return(state, ret, ctypes.create_string_buffer(val, len(val)), len(val)))
    print(binascii.hexlify(ret.value))
