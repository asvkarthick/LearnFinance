#!/usr/bin/python3
# Author : Karthick Kumaran <asvkarthick@gmail.com>
# Date   : 2020-12-31
# Command to run: python3 compute-stock-returns.py
# Prerequisite:
# pip3 install pandas
# pip3 install pandas_datareader

import pandas as pd
import datetime
import pandas_datareader.data as web
from datetime import datetime

today = datetime.now()
today_date = today.strftime("%Y-%m-%d")
print(today_date)

# Get Input CSV file and monthly contribution
input_file = input("Enter input CSV file without .csv : ")
monthly_contribution = input("Enter monthly contribution : ")
monthly_contribution = float(monthly_contribution)
tickers = []
dates = []

# Read the input CSV file containing tickers and dates
df = pd.read_csv(input_file + '.csv', parse_dates = ['DATE'])

# Get all the tickers
for t in df['TICKER']:
    tickers.append(t)
for d in df['DATE']:
    dt = pd.to_datetime(str(d)).strftime('%Y-%m-%d')
    dates.append(dt)

stock_purchase_price = []
units_purchased = []
stock_current_price = []
profit_loss = []
i = 0
for t in tickers:
    if t != 'ALL':
        # Get the stock price on the desired date
        df_ticker = web.DataReader(t, 'yahoo', dates[i], dates[i])
        purchase_price = df_ticker['Adj Close'][0]
        num_units_purchased = monthly_contribution / purchase_price
        print('-------------------------------------------')
        print('Ticker = {}, Date = {}'.format(t, dates[i]))
        print('Stock purchase price = {}'.format(purchase_price))
        print('Num Units Purchased = {}'.format(num_units_purchased))
        stock_purchase_price.append(purchase_price)
        units_purchased.append(num_units_purchased)

        # Get the current stock price
        df_ticker = web.DataReader(t, 'yahoo', today_date, today_date)
        current_price = df_ticker['Adj Close'][0]
        stock_current_price.append(current_price)
        print('Stock current price = {}'.format(current_price))
        pl = (current_price - purchase_price) * num_units_purchased
        profit_loss.append(pl)
    else:
        print('*** Investing in all tickers currently not supported ***')
    i = i + 1

df['Purchase Price'] = stock_purchase_price
df['Units'] = units_purchased
df['Current Price'] = stock_current_price
df['Profit Loss'] = profit_loss
print(df)
df.to_csv('Analysis_Results.csv')

print('********* SUMMARY *********')
total_contribution = monthly_contribution * len(stock_purchase_price)
total_investment = sum([a * b for a, b in zip(stock_purchase_price, units_purchased)])
total_returns = sum([a * b for a, b in zip(stock_current_price, units_purchased)])
pl_percentage = (total_returns - total_investment) / total_investment * 100.0
print('Total Investment   = {}'.format(total_investment))
print('Total Returns      = {}'.format(total_returns))
print('Total Profit/Loss  = {:.2f}'.format(sum(profit_loss)))
print('Profit/Loss %      = {:.2f}%'.format(pl_percentage))
