import matplotlib.pyplot as plt
import scipy.io as sio



def plot():

    data = sio.loadmat("result.mat", squeeze_me=True)
    x, y = data["VV"], data["RR"]
    
    plt.plot(x, y, '-o')
    plt.xlabel("Bias (V)")
    plt.ylabel("Ty (V/?)")
    plt.grid()
    plt.show()
