from flask import Blueprint, render_template, request, redirect, url_for
from models.mercadinho import Produto, produtos

mercadinho_bp = Blueprint('mercadinho', __name__)

# Tela de Listagem
@mercadinho_bp.route('/')
def index():
    return render_template('index.html', produtos=produtos)

# Tela de Adição
@mercadinho_bp.route('/adicionar', methods=['GET', 'POST'])
def adicionar():
    if request.method == 'POST':
        id = len(produtos) + 1
        nome = request.form['nome']
        descricao = request.form['descricao']
        preco = request.form['preco']
        data_criacao = request.form['data_criacao']
        novo_produto = Produto(id, nome, descricao, preco, data_criacao)
        produtos.append(novo_produto)
        return redirect(url_for('mercadinho.index'))
    return render_template('add.html')

# Tela de Edição
@mercadinho_bp.route('/editar/<int:id>', methods=['GET', 'POST'])
def editar(id):
    produto = None
    for p in produtos:
        if p.id == id:
            produto = p
            break
    
    if request.method == 'POST':
        produto.nome = request.form['nome']
        produto.descricao = request.form['descricao']
        produto.preco = request.form['preco']
        produto.data_criacao = request.form['data_criacao']
        return redirect(url_for('mercadinho.index'))
    
    return render_template('edit.html', produto=produto)

# Exclusão de Produto
@mercadinho_bp.route('/excluir/<int:id>')
def excluir(id):
    global produtos
    produtos = [p for p in produtos if p.id != id]
    return redirect(url_for('mercadinho.index'))