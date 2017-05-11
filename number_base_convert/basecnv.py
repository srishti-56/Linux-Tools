'''

A tool written for the Linux / Unix command line that allows conversion
of a number from one base to another, mentioned through command-line
parameters

- Anish Sujanani ( asi7296 )

'''

import argparse


allowed_bases = ['decimal', 'hex', 'octal']



ap = argparse.ArgumentParser(description='Command-line parameters')
ap.add_argument("num",  help="Input number")
ap.add_argument( "--bin", required=True, dest='bin', help='Base of input number')
ap.add_argument( "--bout", required=True, dest="bout", help='Base of output number');
args = ap.parse_args()
'''print args.num
print args.bin
print args.bout'''

print 'Number: ', args.num

if args.bin in allowed_bases:
	print 'input bases ok: ', args.bin
else:
	print 'Invalid input base supplied: ', args.bin
	print 'Allowed bases: ', allowed_bases


if args.bout in allowed_bases:
		print 'output bases ok: ', args.bout
else:
	print 'Invalid output base supplied: ', args.bout
	print 'Allowed bases: ', allowed_bases
