'''
Created on Jun 28, 2021

@author:  Gabriel Dimitriu
'''
import sqlalchemy as sa
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.orm import sessionmaker

conn = sa.create_engine("sqlite://")

Base = declarative_base()
class Zoo(Base):
    __tablename__ = 'zoo'
    critter = sa.Column('critter', sa.String, primary_key=True)
    count = sa.Column('count', sa.Integer)
    damages = sa.Column('damages', sa.Float)
    def __init__(self, critter, count, damages):
        self.critter = critter
        self.count = count
        self.damages = damages
    def __repr__(self):
        return "<Zoo({}, {}, {})>".format(self.critter, self.count,self.damages)
    
Base.metadata.create_all(conn)
first = Zoo('duck', 10, 0.0)
second = Zoo('bear', 2, 1000.0)
third = Zoo('weasel', 1, 2000.0)
Session = sessionmaker(bind=conn)
session = Session()
session.add(first)
session.add_all([second, third])
session.commit()

rows = conn.execute('SELECT * from zoo')
for row in rows:
    print(row)