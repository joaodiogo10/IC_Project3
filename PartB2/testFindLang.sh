#! /bin/sh

languagesToTest=`ls ../Texts`;

order=4
alpha=0.2

rm -f results_order${order}.txt
file="results_order${order}.txt"

cd ./build ;

for language in $languagesToTest
do
    texts=`ls ../../Texts/${language}`;

    for text in $texts
    do
        echo "Language: ${language} Text: ${text} \n" >> ../$file
        ./findlang ../../Models ../../Texts/${language}/${text} ${alpha} ${order} >> ../$file
        echo '\n' >> ../$file
    done

    
done

touch $file &

