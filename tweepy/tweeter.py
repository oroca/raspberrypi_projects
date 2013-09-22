#!/usr/bin/env python

import sys
import tweepy

CONSUMER_KEY = 'xxxxxxxxxxxxx'
CONSUMER_SECRET = 'xxxxxxxxxxxxx'
ACCESS_KEY = 'xxxxxxxxxxxxx'
ACCESS_SECRET = 'xxxxxxxxxxxxx'


auth = tweepy.OAuthHandler(CONSUMER_KEY, CONSUMER_SECRET)
auth.set_access_token(ACCESS_KEY, ACCESS_SECRET)
api = tweepy.API(auth)
api.update_status(sys.argv[1])
