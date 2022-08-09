from pymongo import MongoClient
import time
from os import listdir

c = MongoClient()
db = c.wiki


def new_article(name, wiki):
	return {'name':name, 'wiki':wiki, 'creation_time':int(time.time()), 'creation_user_id':1, 'privilege_read':0, 'privilege_edit':2}


def upload(name, wiki):
	print(name)
	r = db.articles.find({'name':name})
	try:
		r = db.articles.update_one({'_id': r[0]['_id']}, {'$set': {'wiki': wiki}})
		#print("updated")
	except:
		print("-------- new -----------")
		article = new_article(name, wiki)
		db.articles.insert_one(article)

n = 0
n_skip = 0

for f in sorted(listdir("current")):
	if f[-4:] == ".txt":
		name = f[:-4]

		file = open("current/" + f, "r")
		wiki = file.read()

		wiki0 = ""
		try:
			file0 = open("previous/" + f, "r")
			wiki0 = file0.read()
		except:
			pass

		if wiki != wiki0:
			upload(name, wiki)
		else:
			n_skip += 1
		n += 1

print(f"{n-n_skip} of {n} updated, {n_skip} skipped")

