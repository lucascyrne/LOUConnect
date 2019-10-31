from flask import Flask, render_template, url_for
app = Flask(__name__)

posts = [
    {
        'nome': 'Lucas Cyrne',
        'desc': 'Blog Post 1',
        'email': 'lcf@cesar.school',
        'cpf': '444.278.278-45',
        'skills': 'Python',
        'id': 'First Post Content',
        'member_since': 'May 28, 1996'
    },
    {
        'nome': 'Eduardo Eile',
        'desc': 'Blog Post 2',
        'email': 'eec@cesar.school',
        'cpf': '999.333.333-66',
        'skills': 'Python, Arduino, Agile', 
        'id': 'Second Post Content',
        'member_since': 'Dez 12, 1998'
    },
]

@app.route("/")
@app.route("/home")
def home():
    return render_template('home.html', posts=posts)

@app.route("/about")
def about():
    return render_template('about.html', title='About')

@app.route("/results") # Resultados da procura
def results():
    return render_template('results.html', title='Results')

if __name__ == '__main__':
    app.run(debug=True)