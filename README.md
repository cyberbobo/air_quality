# air_quality
Station de mesure de la qualité de l'air (pollution)</br>

Ressources Web :</br>
https://www.esrl.noaa.gov/gmd/ccgg/trends/global.html Valeurs de référence pour le taux de CO2 dans l'air</br>
https://www.epa.gov/criteria-air-pollutants (US gov; quid de l'Europe?)</br>
http://arthur.lutz.im/blog/2016/02/surveiller-la-qualite-de-lair-avec-du-open-hardware-et-du-logiciel-libre/</br>
https://luftdaten.info/fr/montage-detecteur-de-particules-fines/ (projet allemand de mesures des PM2.5 + cartographie)</br>
https://openhomeautomation.net/arduino-battery (à étudier plus tard pour l'autonomie énergétique)</br>
https://www.lesnumeriques.com/batterie-externe/adata-p20000d-powerbank-p37895/test.html Solution bourrine pour l'alimentation électrique<br>
http://www.dreamgreenhouse.com/projects/2014/air/index.php</br>
https://aqicn.org/sensor/sds011/fr/ Rétro-ingénierie du capteur SDS011 (PM)<br>
https://www.airparif.asso.fr/reglementation/recommandations-oms Recommandations OMS <br>

MCU :<br>
https://makeradvisor.com/esp32-vs-esp8266/ ESP32 vs ESP8266 <br>
https://www.fais-le-toi-meme.fr/fr/electronique/tutoriel/esp8266-arduinoota-mise-a-jour-logiciel-esp8266-wifi Mise à jour et debug OTA<br>

Spécial MQ-135 :</br>
La datasheet est naze, le capteur a l'inconvénient d'être non-sélectif sur les gaz testés.</br>
https://projetsdiy.fr/capteurs-mq-detecter-gaz-polluants-fumees/ => Récap technique sur la gamme de capteurs MQ <b>Attention</b> cet article signale que le MQ-135 doit être alimenté en permanence (inadapté à un appareil nomade)</br>
https://hackaday.io/project/3475-sniffing-trinket/log/12363-mq135-arduino-libraryLes commentaires de l'auteur de la librairie pour le MQ-135</br>
http://davidegironi.blogspot.com/2014/01/cheap-co2-meter-using-mq135-sensor-with.html#.VJXAgsC3b Blog de Davide Gironi qui a utilisé le MQ-135 comme capteur de CO2, avec une formule en ppm = a*(Rs/Ro)^b</br>
http://davidegironi.blogspot.com/2017/05/mq-gas-sensor-correlation-function.html Le détail de cette évaluation des paramètres du capteur : l'auteur utilise un outil pour extraire les données du graphe de la datasheet, avec ces valeurs opère une régression non-linéaire (avec un script R mais c'est faisable avec Python, Matlab...) et en retire les coefs a et b.</br>

Ensuite, que faire?<br>
https://www.franceculture.fr/emissions/la-methode-scientifique/la-methode-scientifique-emission-du-vendredi-31-mai-2019 à 14:45 : oxydes de graphène (nano-particules) pour capter les polluants dans l'air ou l'eau
