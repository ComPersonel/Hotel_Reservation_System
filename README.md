<img width="148" height="168" alt="image" src="https://github.com/user-attachments/assets/9fc98035-a507-49e2-8c9a-b24b78de9743" />

# Eetu Parén, 25TietoB

---

Hotellin varaus systeemi työ on tehty 5p suoritus tavoitteena. Ohjelma käyttää 2 structia, 3 tiedostoa ja 46 aliohjelmaa toteuttamaan sen kaikki toiminnot.

Systeemi sisältää useamman kerroksen käsittelyn, 2 eri huone tyyppiä, 3 erilaista huone laatua ja työkaluja niiden käsittelyyn. Puolet hotellin huoneista on yhden hengen ja puolet 2 hengen huoneita. Puolet näistä on perus huoneita, puolet preemium huoneita ja joka kerroksella on 1 luksus huone per huoneen tyyppi.

---

##	Varaa Huone

Huoneen varaus etenee seuraavassa järjestyksessä
1.	Kysytään käyttäjältä haluaako hän valita huoneen itse
2.	Kysytään haluaako käyttäjä yhden vai kahden hengen sängyn
3.	Mikäli käyttäjä halusi valita huoneen itse jatketaan tässä, mutta jos ei siirrytään suoraan 4 vaiheeseen
   
	  -	Pyydetään huoneelle kerrosta ja Annetaan ylä ja ala raja huoneilla joista käyttäjä saa valita
4.	Tulostetaan huone ja pyydetään käyttäjää hyväksymään se, jos käyttäjä ei hyväksy huonetta palataan vaiheeseen 2
5.	Pyydetään käyttäjän nimeä
6.	Kysytään kuinka pitkä varaus on
7.	Tulostetaan varauksen tiedot ja lasku
Varaus tallentuu reservations_array vectoriin, josta se siirtyy reservation_data.txt tiedostoon kun ohjelmasta poistutaan


##	Tulosta Varaus

Tämä komento tulostaa viimeisimmän varauksen systeemissä. Systeemi tulostaa kokonaisuudessaan Varauksen tiedot, Huoneen tiedot ja laskun.


##	Etsi Varaus

Huonetta etsiessä käyttäjältä pyydetään joko varauksen nimi tai varauksen numero. Tämän jälkeen huone/huoneet tulostetaan listana


##	Muokkaa Varausta

Komento alkaa samalla tavalla kuin etsiessä varausta, mutta tämän jälkeen käyttäjältä pyydetään tarkkaa varausta mikäli useampi varaus vastasi hakukriteereitä.
Käyttäjä saa seuraavat vaihtoehdot

1.	Peru Varaus
   
    -	Käyttäjää pyydetään varmentamaan varauksen peruminen ja jos käyttäjä on varma varaus poistetaan
3.	Vaihda huonetta

    -	Systeemi toteuttaa huoneen varauksen 1-4 vaiheista ja vaihtaa huoneen uuteen valintaan
5.	Vaihda nimeä

     -	Käyttäjää pyydetään syöttämään uusi nimi ja varmentamaan että se on oikein
7.	Vaihda Kestoa

    -	Käyttäjää pyydetään syöttämään uusi varauksen pituus ja varmentamaan että se on oikein
9.	Poistu
   
     -	Poistuu ohjelmasta

  
##	Tulosta Kaikki Varaukset
Tulostaa kaikki varaukset listaan


#	Developer Menu
Developer menu avataan syöttämällä 420 main menu tehtävä syötteenä ja se sisältää 3 uniikkia komentoa.
1.	Luo uusi huonedata
   
    -	Luo huonedatan maasta ylöspäin. Mekaanisesti ei tee mitään muuta kuin arpoo huoneille uudet alennukset
3.	Poista varaukset
   
    -	Poistaa kaikki varaukset
5.	Luo uusi hotelli
   
    -	Kysyy käyttäjää haluaako hän syöttää hotellin uuden koon (kerrokset ja huone määrät)
  	
    -	Jos käyttäjä ei syötä arvoja ohjelma arpoo ne
