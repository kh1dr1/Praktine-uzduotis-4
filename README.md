# Ketvirta praktinė užduotis

Parašykite programą, kuri padėtų vietiniam restoranui automatizuoti pusryčių apskaitos sistemą. Programa turėtų atlikti šiuos veiksmus:

1. Rodyti klientui skirtingus pusryčių pasiūlymus.
2. Leisti klientui pasirinkti daugiau nei vieną elementą iš meniu.
3. Apskaičiuoti ir atspausdinti sąskaitą, kuris turi būti išsaugojamas faile.
4. Klientas galėtų pasirinkti kelias to paties patiekalo porcijas.

Restoranas siūlo šį pusryčių meniu (kiekvieno meniu patiekalo kaina pateikiama dešinėje nuo elemento):

* Kiaušinienė                           1.45€
* Kiaulienos šoninė su keptu kiaušiniu  2.45€
* Keksiukas su vyšnia                   0.99€
* Prancūziškas skrebutis                1.99€
* Vaisių salotos                        2.49€
* Pusryčių dribsniai                    0.69€
* Kava                                  0.50€
* Arbata                                0.75€

Naudokite masyvą **menuList**, kuris yra struktūros **menuItemType** masyvas su dviem parametrais: *menuItem*, teksto tipo ir *menuPrice*, skaičius su dvejais skaitmenimis po kablelio tipo. Programa turi turėti bent šias funkcijas:

* Funkcija **getData**: Ši funkcija įkelia duomenis į masyvą menuList.
* Funkcija **showMenu**: Ši funkcija rodo skirtingus restorano siūlomus pusryčių patiekalus ir praneša vartotojui, kaip užsisakyti juos.
* Funkcija **printCheck**: Ši funkcija apskaičiuoja ir spausdina sąskaitą. (Atkreipkite dėmesį, kad į mokėjimo sumą turėtų būti įtraukta 21% mokesčių.)

## Pavyzdinis rezultatas

```txt
Sveiki atvykę į restoraną „Pavadinimas“

Kiaulienos šoninė su keptu kiaušiniu   2.45€

Keksiukas su vyšnia                    0.99€

Kava                                   0.50€

Mokesčiai                              0.20€

Galutinė suma                          4.14€
```

Rezultatas turi būti dviejų skaitmenų po kablelio tikslumu. Kiekvieno patiekalo pavadinimas rezultate turi būti kairėje.

Punkte „4“ užduotį atlikite taip, kad klientas galėtų pasirinkti kelis elementus vieno tipo. Pavyzdinė išvestis šiuo atveju:

```txt
Sveiki atvykę į restoraną „Pavadinimas“

1 Kiaulienos šoninė su keptu kiaušiniu 2.45€

2 Keksiukas su vyšnia                  0.99€

1 Kava                                 0.50€

Mokesčiai                              0.25€

Galutinė suma                          5.18€
```
