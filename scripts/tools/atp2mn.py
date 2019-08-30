import csv


input_path = '../../data/atp_matches_2016.csv'
output_path = '../../data/atp_matches_2016.dat'

with open(input_path,'r') as csvfile,open(output_path,'w') as outfile:
	score_reader = csv.reader(csvfile,delimiter=',',skipinitialspace=True)
	# Skip the header
	next(score_reader, None)
	teams = set()
	n_games = 0
	# String with info of the games.
	out_str = ''
	for row in score_reader:
		teams.add(row[7])
		teams.add(row[17])
		n_games = n_games+1
		out_str = out_str + row[5] + ' ' + row[7] + ' ' + '1' + ' ' + row[15] + ' ' + '0' + '\n'
	# Write number of teams and games
	outfile.write(str(len(teams)) + ' ' + str(n_games) + '\n')
	# Write games details
	outfile.write(out_str)

	print("Done")
