make all
read statistic
for filename in inputs/input_${statistic}_*.txt; do
  #you can remove the comment tag(#) to see the file name before every 10 iteration
  echo $filename
  for (( i = 0; i < 10; i++ )); do
	  ./homework2 ${filename}
  done;
done;