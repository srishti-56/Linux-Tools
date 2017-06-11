#!/usr/bin/env python
import sys
import optparse
import requests
import json
import time
import datetime
from datetime import datetime, timedelta

#get JWT token
# userkey and username is optional right now (not required)
jwtPayload = {
  "apikey": "API-KEY-HERE",
 # "userkey": "USER-KEY-HERE",
  # "username": "USERNAME-HERE"
}


parser = optparse.OptionParser()

parser.add_option('-n', '--series', dest='series', help='Name of Series: ')
parser.add_option('-s', '--season', dest='season', help='Season: ', type=int)
parser.add_option('-e', '--episode', dest='epnum', help='Episode: (type lt to return latest episode or type all to return all airdates of all seasons)')
	
(options, args) = parser.parse_args()

if options.series is None:
	options.series = input('Enter series: ')
if options.season is None:
	options.season = input('Enter season: ')
if options.epnum is None:
	options.epnum = input('Enter episode: (type lt to return latest episode)')


series = options.series
season = options.season
epnum = options.epnum
if(epnum == "lt"):
	epnum = "latest"


baseurl = 'https://api.thetvdb.com/'
headers = {'content-type': 'application/json' }


r = requests.post( baseurl+'login' , data=json.dumps(jwtPayload) , headers = headers)

#print r.text
res = json.loads(r.text)
token = res['token']

headers = {'content-type': 'application/json', 'Authorization' : 'Bearer '+token}


#get Series ID
paramsSeries = {
	'name' : series
}
rSeries = requests.get( baseurl + 'search/series', params= paramsSeries , headers = headers)
res= json.loads(rSeries.text)
#print res
seriesId = res['data'][0]['id']
seriesStatus = res['data'][0]['status']

#check if latest episode/season required
if(epnum == 'latest'): 
	rltSeries = requests.get(baseurl + 'series/' + str(seriesId) , headers= headers)
	res = json.loads(rltSeries.text)
	lastUpdated = res['data']['lastUpdated']
	if(seriesStatus == 'Continuing'):
		flag = 0
		date_time = str(datetime.now())
		epQueryParams = { 'airedSeason' : season}
		repQuery = requests.get( baseurl + 'series/' + str(seriesId) + '/episodes/query', params = epQueryParams, headers = headers)
		res = json.loads(repQuery.text)
		try:
			if (res['Error']):
				print('No results found! Looks like this episode or season or show does not exist right now!')
				quit()
		except KeyError:
			for var in res['data']:
				if( datetime.strptime( (var['firstAired']), "%Y-%m-%d").date() > datetime.strptime(date_time, "%Y-%m-%d %H:%M:%S.%f").date()):
					print ('Up next : Episode ' + str(var['airedEpisodeNumber']) +' ' + var['episodeName'] + ' releasing on ' + str(var['firstAired']) )
					print ('\nOverview : ' + var['overview'] )
					flag = 1
					break
			if(flag == 0):
				print ('Last episode ' + str(var['airedEpisodeNumber']) + ' ' + var['episodeName'] + ' aired on ' + str(var['firstAired']) )
				print ('\nOverview : ' + var['overview'] )
	else: 
		print ("Show ended on " + str(lastUpdated) )

elif(epnum != 'latest'):
	#get Episode info
	epParams = {
		'id' : seriesId,
		'airedSeason' : season,
		'airedEpisode': epnum
	}
	rEpisodes = requests.get( baseurl + 'series/' + str(seriesId) + '/episodes/query' , params = epParams, headers=headers)
	res = json.loads(rEpisodes.text)

	try:
		if (res['Error']):
			print ('No results found! Looks like this episode or season or show does not exist right now!')
			quit()
	except KeyError:
		print (res)
		epName = res['data'][0]['episodeName']
		epAirdate = res['data'][0]['firstAired']
		epOverview = res['data'][0]['overview']
		airedEpisodeNumber = res['data'][0]['airedEpisodeNumber'] 

		print ("Episode " + str(airedEpisodeNumber) + " " + epName + "\t AirDate : " + epAirdate)
		print ("\n Overview : " + epOverview)


sys.exit
