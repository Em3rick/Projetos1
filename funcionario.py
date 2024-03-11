class Funcionarios:
    def __init__(self, nome, prontuario, salario) :
        self.nome=nome
        self.prontuario=prontuario
        self.salario=salario
    def exibirInfo(self):
        return f"Nome: {self.nome}, salário: R${self.salario:.2f}, Prontuario: {self.prontuario}"
igor=Funcionarios("igor de Moraes", "SP3117821",501.64)
print(igor.exibirInfo())

class servidoradm(Funcionarios):
    def __init__(self, nome, prontuario, salario, cargo):
        super().__init__(nome, prontuario, salario)
        self.cargo=cargo

    def exibirInfo(self):
        return super().exibirInfo()+ f",Cargo: {self.cargo}"
claudio= servidoradm("Claudio Oreio","SP5678",2100,"coletor")
print (claudio.exibirInfo())
