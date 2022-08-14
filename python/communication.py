import requests
import datetime as dt
import pandas as pd
import json
from os.path import exists
from os import remove
import pytz
timezone = pytz.timezone("America/Lima")
URL_AUTH_USERS = 'https://srf-webapp-prd.azurewebsites.net/api/colaborador/hash'
URL_ATTENDANCE_USERS = 'https://srf-webapp-prd.azurewebsites.net/api/asistencia'

user_register_file = 'user_register.csv'

#response = requests.get(URL_AUTH_USERS)
#auth_users = response.json()
#df_auth = pd.json_normalize(auth_users)
#df_auth.to_csv('/home/pi/access_mdp/python/auth_users.csv')
#print(df_auth)

if exists(user_register_file):
    df = pd.read_csv(user_register_file, dtype=object)
    remove(user_register_file)
    for index, row in df.iterrows():
        data = {'Mac': '00:04:4B:E5:AD:A0', 'Colaboradores':[{"FechaHora": dt.datetime.strftime((dt.datetime.now(timezone)),'%Y-%m-%d %H:%M:%S'), 'Hash': str(row['hash']), 'Dni': str(row['dni'])}]}
        print(f'{"-"*20}{index+1}')
        print(data)
        response_post = requests.post(url = URL_ATTENDANCE_USERS, json = data)

#data = {'mac': '00:04:4B:E5:AD:A1', 'Colaboradores':[{"FechaHora": str(dt.datetime.now()), 'hash': auth_users[0]['hash'] , 'Dni': auth_users[0]['dni']}]}
#response_post = requests.post(url = URL_ATTENDANCE_USERS, data = data)
