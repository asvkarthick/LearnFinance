#!/usr/bin/python3
# Author: Karthick Kumaran <asvkarthick@gmail.com>
# Command to run: python3 tutorial-01.py

import pandas as pd
import datetime
import pandas_datareader.data as web

today = datetime.datetime.now()
today_date = today.strftime("%Y-%m-%d")
print(today_date)

ticker = input("Enter ticker : ")
start_date = input("Enter start date (yyyy-mm-dd) : ")
end_date = input("Enter end date (yyyy-mm-dd) : ")

df = web.DataReader(ticker, 'yahoo', start_date, end_date)
print(df.head)

df.to_csv(ticker + '.csv')
