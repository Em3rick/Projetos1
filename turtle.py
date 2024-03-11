import turtle                     # permite usar as funções e objetos do módulo turtle

wn = turtle.Screen()
wn.bgcolor("lightgreen")         # define a cor de fundo da janela

tess = turtle.Turtle()
tess.color("blue")               # tess fica azul
tess.pensize(3)                  # define a espessura da caneta

tess.forward(50)                 # diz o quanto tess irá andar para frente
tess.left(120)                   # diz o quanto tess irá andar para esquerda (left)
tess.forward(50)

wn.exitonclick()
