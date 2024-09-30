from flask import Flask
from controllers import mercadinho_bp

app = Flask(__name__)
app.register_blueprint(mercadinho_bp)

if __name__ == '__main__':
    app.run(debug=True)