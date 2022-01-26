#! /bin/sh

texts=`ls ../Texts`;

[ ! -d "../Models" ] && mkdir ../Models

cd ./build ;

for text in $texts
do

    [ ! -d "../../Models/${text}" ] && mkdir ../../Models/${text}

    [ ! -d "../../Models/${text}/order_0" ] && mkdir ../../Models/${text}/order_0
    [ ! -d "../../Models/${text}/order_1" ] && mkdir ../../Models/${text}/order_1
    [ ! -d "../../Models/${text}/order_2" ] && mkdir ../../Models/${text}/order_2
    [ ! -d "../../Models/${text}/order_3" ] && mkdir ../../Models/${text}/order_3

    ./loadFile "${text}" 0 "../../Texts/${text}/data"

    mv ${text}_0.fcm ../../Models/${text}/order_0

    ./loadFile "${text}" 1 "../../Texts/${text}/data"

    mv ${text}_1.fcm ../../Models/${text}/order_1

    ./loadFile "${text}" 2 "../../Texts/${text}/data"

    mv ${text}_2.fcm ../../Models/${text}/order_2

    ./loadFile "${text}" 3 "../../Texts/${text}/data"

    mv ${text}_3.fcm ../../Models/${text}/order_3

done

