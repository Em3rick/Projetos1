class Funcionarios:
    def __init__(self, nome, idade, tempodecarreira,Aposentado) :
        self.nome=nome
        self.idade=idade
        self.tempodecarreira=tempodecarreira
        self.Aposentado=Aposentado
    def exibirInfo(self):
        return f"Nome: {self.nome}, tempodecarreira: R${self.tempodecarreira}, idade: {self.idade}, aposentado: {self.Aposentado}"
igor=Funcionarios("igor de Moraes ", "5 ", "23 " , "sim")
print(igor.exibirInfo())

class Volei(Funcionarios):
    def __init__(self, nome, idade, tempodecarreira, Aposentado, bloqueios,pontosdesaque):
        super().__init__(nome, idade, tempodecarreira, Aposentado)
       
        self.bloqueios=bloqueios
        self.pontosdesaque=pontosdesaque

    def exibirInfo(self):
        return super().exibirInfo()+ f",bloqueios: {self.bloqueios}, pontos de saque: {self.pontosdesaque}"
claudio= Volei("Claudio Oreio ","10  ","60  ","200  ","500 ", "100")
print (claudio.exibirInfo())




class Basquete(Funcionarios):
    def __init__(self, nome, idade, tempodecarreira, Aposentado, pontos, assistencias):
        super().__init__(nome, idade, tempodecarreira, Aposentado)
        
        self.pontos=pontos
        self.assistencias=assistencias
    def exibirInfo(self):
        nota=(self.pontos + self.assistencias)/100
        return super().exibirInfo()+ f"pontos: {self.pontos}assistencias:{self.assistencias}, nota:{nota}"
Rafael= Basquete("Rafael Cardoso","10 ","20","Não","200", "240")
print (Rafael.exibirInfo())
