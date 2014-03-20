++===========================================================================++                                                                       
++===========================================================================++                                                                       
||          ,--,                                ,----..      .--,-``-.       ||
||        ,--.'|       ,----,     ,----..      /   /   \    /   /     '.     ||
||     ,--,  | :     .'   .' \   /   /   \    /   .     :  / ../        ;    ||
||  ,---.'|  : '   ,----,'    | |   :     :  .   /   ;.  \ \ ``\  .`-    '   ||
||  |   | : _' |   |    :  .  ; .   |  ;. / .   ;   /  ` ;  \___\/   \   :   ||
||  :   : |.'  |   ;    |.'  /  .   ; /--`  ;   |  ; \ ; |       \   :   |   ||
||  |   ' '  ; :   `----'/  ;   ;   | ;     |   :  | ; | '       /  /   /    ||
||  '   |  .'. |     /  ;  /    |   : |     .   |  ' ' ' :       \  \   \    ||
||  |   | :  | '    ;  /  /-,   .   | '___  '   ;  \; /  |   ___ /   :   |   ||
||  '   : |  : ;   /  /  /.`|   '   ; : .'|  \   \  ',  /   /   /\   /   :   ||
||  |   | '  ,/  ./__;      :   '   | '/  :   ;   :    /   / ,,/  ',-    .   ||
||  ;   : ;--'   |   :    .'    |   :    /     \   \ .'    \ ''\        ;    ||
||  |   ,/       ;   | .'        \   \ .'       `---`       \   \     .'     ||
||  '---'        `---'            `---`                      `--`-,,-'       ||
||                                                                           ||
++===========================================================================++                                                                       
++===========================================================================++                                                                       

Udv!

Nos, ez itt az en kis beadandom. Hasznaljatok egeszseggel! :-)

Node mi is ez?
==============

A program egy roppantul primitiv, 2D-s merevtest-szimulator. A kor alaku testek
nem deformalodnak, de utkozhetnek egymassal es a fallal, ekkor a newtoni mech-
hanika szabalyai szerint pattannak vissza.

Az ipari fizikai motoroknal megszokotthoz van egy "applyImpulse" metodus az
engine-ben. Ez adott lendulettel loki meg a testeket. Alapertelmezesben egy
test tomege a teruletevel (r ^ 2-tel, hiszen 2D-ben vagyunk) aranyos, de ezt
barmikor lehet modositani.

A gravitacio erteke valtoztathato, csupan a main.spn-ben kell atirni a
PhysX.g erteket. Negativ gravitaciot is megadhatunk, valamint ki is tudjuk
iktatni azt teljesen (0-ra allitassal).

Az applyImpulse hasznalatahoz szinten nagyon egyszeru UI tartozik. A kepernyo
kozepebol kiindulo lila "vektor" mutatja az impulzusvektor nagysagat, iranyat.
Ezeket az ASDF gombokkal tudjuk valtoztatni (az A es D az X, a W es S pedig az
y iranyu komponenst novelik-csokkentik).

A "space" gombbal tudunk "raloni" az aktualisan kivalasztott testre (=impulzust
adunk neki). Egy test kivalasztasa bal gombos rakattintassal tortenik.
A kivalasztott test szine vilagoskekrol narancssargara valtozik.

Az elobbiekben felsorolt 5 billentyun kivul barmelyik mas billentyu leutese
kilep a programbol.


How to build?
=============

$ make
$ ./beadando_1


Mi az a physx.spn meg a main.spn?
=================================

Az engine legnagyobb resze az altalam tervezett es implementalt szkriptnyelven,
Sparklingban van irva. A Sparkling/ alkonyvtarban a jelenleg legfrissebb
GitHub-os snapshot van. (`git pull' mukodik, ha szukseges.)

A Sparkling szigoru, szabvanyos, konformans C89-ben van irva, tehat fordulnia
kell(ene) Linux, OS X, BSD, Solaris, es tulajdonkepp meg Windows alatt is.

A C++ forrasfaljjaim szinten -std=c++98 -pedantic -Wall kapcsoloval fordulnak.
A C++ forraskod legnagyobb reszet a Flugi-fele grafikus konyvtar wrappelese
kepezi (az API stilusat kicsit atalakitottam, refaktoroztam, stb., plusz a
Sparkling kodbol valo hasznalathoz hozzaadtam a nativ bindingeket.)

Nemcsak a kovetelmeny/elvaras miatt, hanem azert is, mert igy helyes, szep es
idiomatikus, a C++ kodom termeszetesen tartalmazza azokat, amik a feladat
kiirasaban szerepeltek: `private` data memeber-ek, setterek es
`const`-kvalifikalt (!) getterek, konstruktorok.

Remelem, tetszeni fog a munkam.
Jo szimulaciot!

-- Arpi (H2CO3)


