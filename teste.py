
from my import Database, Pessoa

db = Database()
pes = Pessoa(nome="Alguem ai", idade=15)

pes.nome = "outro"
pes.idade = 28
print('Pessoa: ', pes.nome )

db.add( pes ).add( Pessoa(nome="Outro Ser", idade=27) )

db.add( Pessoa(nome="Nenhuma Pessoa", idade=34) )
db.add( Pessoa(nome="Ela", idade=41) )
db.save("./build/database.txt")

print('Fim.')
