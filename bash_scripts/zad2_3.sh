while true
do
echo "(a) informacje o systemie"
echo "(b) nazwa uzytkownika i sciezka biezacego argumentu"
echo "(c) wyswietl aktualna date i czas"
echo "(d) wyjscie"

read text

case "$text" in
  "a") uname -n
       uname -o
   ;;
  "b") logname
       pwd
   ;;
  "c") date +%F
       date +%T
   ;;
  "d") break
   ;;
  *) echo "Zly wybor"
  ;;
esac
done
