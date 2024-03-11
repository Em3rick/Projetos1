class Carros:
    def __init__(self,p ,c, m, a):
        self.potencia=p
        self.cor=c
        self.marca=m
        self.ano=a
    def vrum_vrum(self):
        for i in range(self.potencia):
            print("Vrum", end="")
