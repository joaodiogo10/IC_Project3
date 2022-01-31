#! /bin/sh

languagesToTest=`ls ../Texts`;

order=$1
alpha=$2

[ ! -d "Results" ] && mkdir ../Models

rm -f "./Results/order${order}_${alpha}.txt"
file="./Results/order${order}_${alpha}.txt"

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

