#class1
class Pessoa:

   def __init__(self, nome, idade):
    self.nome = nome 
    self.idade = idade


   def apresentar(self):
       return (f"Nome: {self.nome} idade: {self.idade}")
igor = Pessoa("Igor", 25 )
print (igor.apresentar())
