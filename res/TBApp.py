import tb, time, multiprocessing
import numpy as np
import scipy.io as sio
from numpy import pi
from scipy.integrate import quad
from scipy.interpolate import interp1d
from PythonQt import *



class ChainSpec():

    def __init__(self, value):
    
        self.materials = []
        self.couplings = []
        
        for material in value['materials']:
            self.materials.append( MaterialSpec(material) )
        
        for coupling in value['couplings']:
            self.couplings.append( eval(coupling) )  



class MaterialSpec():

    def __init__(self, value):
    
        self.e_up = eval( value['e_up'] )
        self.e_dn = eval( value['e_dn'] )
        self.t_up = eval( value['t_up'] )
        self.t_dn = eval( value['t_dn'] )
        self.thickness = eval( value['thickness'] )
        self.temperature = eval( value['temperature'] )
        self.gamma = eval( value['gamma'] )
        self.lBias = eval( value['lBias'] )
        self.rBias = eval( value['rBias'] )
        
        
        
class TBApp():
    
    def __init__(self, userParameters):
        
        
        
        num = 7+8
        VV = np.linspace(-0.6, 0.6, num)
        RR = []
        
        
        for V in VV:
            
            print("Start V = ", V)
            tic = time.clock()
            
            lL = tb.Lead(1.2, 2.0, -0.4, -0.4, 300, 0, 0)
            T1 = "-0.4, 0.0; 0.0, -0.4"
            B1 = tb.Insulator(5.4, 5.4, -0.4, -0.4, 5, 0, 0, V)
            T2 = "-0.4, 0.0; 0.0, -0.4"
            lR = tb.Lead(1.2, 2.0, -0.4, -0.4, 300, pi/2, V)
            wire = tb.Chain(lL, T1, B1, T2, lR)
            
            RR.append(self.__func3__(wire, V))
            print("Result = ", RR[-1])
            toc = time.clock()
            print("Δt = ", toc-tic, "sec\n")
            sio.savemat("result.mat", {"VV": VV, "RR": RR})
        
        print("All calculation finish")
        
        
        
        

    #def run(self):
    #
    #    R = self.__func3__(self.chain, -0.2)#TODO
    #    print(R)
        
    
    
    def __func00__(self, wire, θ1, θ2, E):
        
        def func0(wire, θ1, θ2, E):
        
            return wire.unname_z(θ1, θ2, E)
        
        vfunc = np.vectorize(func0)
        return vfunc(wire, θ1, θ2, E)
    
    
    
    def __func11__(self, wire, θ2, E):
        
        def func1(wire, θ2, E):
    
            num = 20
            xx = np.linspace(-pi, pi, num)
            yy = self.__func00__(wire, xx, θ2, E)
            
            spl = interp1d(xx, yy, kind="cubic")
            r = quad(spl, -pi, pi)
            return r[0]
        
        vfunc = np.vectorize(func1)
        return vfunc(wire, θ2, E)
        
    
    
    def __func22__(self, wire, E):
        
        def func2(wire, E):
        
            num = 20
            xx = np.linspace(-pi, pi, num)
            yy = self.__func11__(wire, xx, E)
            
            spl = interp1d(xx, yy, kind="cubic")
            r = quad(spl, -pi, pi)
            return r[0]
    
        vfunc = np.vectorize(func2)
        return vfunc(wire, E)
        

    
    def __func3__(self, wire, bias):
        
        E_min = 1.2 - 6*(0.4) + bias
        E_max = 1.3 # TODO not 0.3 ...or 0
        const = 0.4/(16*pi**3)
        
        num = 20
        EE = np.linspace(E_min, E_max, num)
        yy = self.__func22__(wire, EE)
        
        spl = interp1d(EE, yy, kind="cubic")
        r = quad(spl, E_min, E_max)
        return r[0]*const



userParameters_py = ChainSpec(userParameters_c)
app = TBApp(userParameters_py)
#p = multiprocessing.Process(target=app.run)
#p.start()
        

