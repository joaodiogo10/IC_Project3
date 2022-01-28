#! /bin/sh

texts=`ls ../Train`;

[ ! -d "../Models" ] && mkdir ../Models

cd ./build ;

for text in $texts
do
    order=$1

    [ ! -d "../../Models" ] && mkdir ../../Models

    [ ! -d "../../Models/Order_${order}" ] && mkdir ../../Models/Order_${order}

    ./loadFile "${text}" ${order} "../../Train/${text}/data"

    mv ${text}.fcm ../../Models/Order_${order}

done

