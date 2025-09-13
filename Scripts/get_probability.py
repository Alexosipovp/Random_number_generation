from scipy.stats import chi2
import sys

pearson, freedom_numbers = map(float, sys.argv[1:3])
probability = chi2.sf(pearson, freedom_numbers)
print(probability, "(" + str(int(probability*1000)/10) + "%)")