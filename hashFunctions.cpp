struct hashPairs { 
  size_t operator() (const pair<int, int> &x) const {
  	hash<int> stdhash;
  	return stdhash(stdhash(x.first) + stdhash(x.second)); 
  } 
};
