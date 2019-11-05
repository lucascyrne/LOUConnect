from flask import Flask, render_template, url_for
app = Flask(__name__)

posts = [
    {
            'author': 'Lucas Cyrne',
            'title': 'Blog Post 1',
            'content': 'First Post Content',
            'date_posted': 'May 28, 1996'
    },
    {
            'author': 'Eduardo Eile',
            'title': 'Blog Post 2',
            'content': 'Second Post Content',
            'date_posted': 'Apr 1, 2000'
    },
]

@app.route("/")
@app.route("/home")
def home():
    return render_template('home.html', posts=posts)

@app.route("/about")
def about():
    return render_template('about.html', title='About')

if __name__ == '__main__':
    app.run(debug=True)