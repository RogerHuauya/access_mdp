import requests
import pandas as pd
import json
#import datetime as dt
from os.path import exists
from os import remove
from os import listdir
URL_AUTH_USERS = 'https://srf-webapp-prd.azurewebsites.net/api/colaborador/hash'
URL_ATTENDANCE_USERS = 'https://srf-webapp-prd.azurewebsites.net/api/asistencia'

user_register_file = 'user_register.csv'

#response = requests.get(URL_AUTH_USERS)
#auth_users = response.json()
#df_auth = pd.json_normalize(auth_users)
#df_auth.to_csv('/home/pi/access_mdp/python/auth_users.csv')
#print(df_auth)
ROOT_PATH = '/home/pi/access_mdp'
dirs = listdir(f'{ROOT_PATH}/python/marks')
print(dirs)
for mark in dirs:
    now = mark[:-4]
    #utc = dt.datetime.strptime(now, '%Y-%m-%d %H:%M:%S')
    #local =  utc - dt.timedelta(hours = 5)
    #now = local.strftime("%Y-%m-%d %H:%M:%S")
    print('now', now)
    mark = f'{ROOT_PATH}/python/marks/{mark}' 
    print(f'Mark found: {mark}')
    df = pd.read_csv(mark, dtype=object)
    remove(mark)
    for index, row in df.iterrows():
        data = {'Mac': '00:04:4B:E5:AD:A0', 'Colaboradores':[{"FechaHora": now, 'Hash': str(row['hash']), 'Dni': str(row['dni'])}]}
        print(f'{"-"*20}{index+1}')
        print(data)
        response_post = requests.post(url = URL_ATTENDANCE_USERS, json = data)

else:
    print("No file found")
#data = {'mac': '00:04:4B:E5:AD:A1', 'Colaboradores':[{"FechaHora": str(dt.datetime.now()), 'hash': auth_users[0]['hash'] , 'Dni': auth_users[0]['dni']}]}
#response_post = requests.post(url = URL_ATTENDANCE_USERS, data = data)
