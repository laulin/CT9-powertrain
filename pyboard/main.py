import powertrain
# use for interrupt execption
import micropython
micropython.alloc_emergency_exception_buf(100)

p = powertrain.Powertrain()
p.loop()