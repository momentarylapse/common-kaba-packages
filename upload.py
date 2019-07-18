from pymongo import MongoClient
import time
from os import listdir

c = MongoClient()
db = c.wiki


def new_article(name, wiki):
	return {'name':name, 'wiki':wiki, 'creation_time':int(time.time()), 'creation_user_id':1, 'privilege_read':0, 'privilege_edit':2}


def upload(name, wiki):
	r = db.articles.find({'name':name})
	try:
		r = db.articles.update_one({'_id': r[0]['_id']}, {'$set': {'wiki': wiki}})
	except:
		article = new_article(name, wiki)
		db.articles.insert_one(article)


for f in listdir("./"):
	if f[-4:] == ".txt":
		name = f[:-4]
		print(name)

		file = open(f, "r")
		wiki = file.read()

		upload(name, wiki)
