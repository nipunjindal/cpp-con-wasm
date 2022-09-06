from operator import itemgetter
from bottle import get, post, request, run, static_file

leaderboard = []


@post("/log/")
def add_log():
    log = request.body.read().decode("utf-8")
    print(log)
    leaderboard.append(log)


@get("/logs")
def get_leaderboard():
    print(leaderboard)
    return ", ".join(leaderboard)


@get("/delete")
def delete_leaderboard():
    leaderboard.clear()


@get("/")
def index_file():
    return send_static("/index.html")


@get("/<path:path>")
def send_static(path):
    return static_file(path, root=".")


run(host="0.0.0.0", port=8000)
