create database obchod;
use obchod;

-- tabulky
create table zakaznik(zakaznik_id int primary key auto_increment not null, jmeno blob not null, prijmeni blob not null, email blob, telefon blob not null, adresa blob); -- blob pro sifrovana data, soukromi zakazniku
create table dodavatel(dodavatel_id int primary key auto_increment not null, firma varchar(100) not null, email varchar(100) not null, telefon int(20) not null);
create table zbozi(zbozi_id int primary key auto_increment not null, nazev varchar(100) not null, cena int not null, dodavatel int not null, constraint foreign key(dodavatel) references dodavatel(dodavatel_id));
create table objednavka(objednavka_id int primary key auto_increment not null, zakaznik int not null, datum date not null, constraint foreign key(zakaznik) references zakaznik(zakaznik_id));
create table seznam(seznam_id int primary key auto_increment, zbozi int not null, objednavka int not null, pocet int not null, constraint foreign key(objednavka) references objednavka(objednavka_id), constraint foreign key(zbozi) references zbozi(zbozi_id));
-- tabulky

 -- zkusebni data
 insert into dodavatel(firma, email, telefon) values ('HP', 'pocitace@volny.cz', 456123456);
 insert into zbozi(nazev, cena, dodavatel) values ('laptop', 15000, 1), ('osciloskop', 100000, 1);
 insert into zakaznik(jmeno, prijmeni, email, telefon, adresa) values (aes_encrypt('Pavel', '123abc'), aes_encrypt('Novák', '123abc'), aes_encrypt('petrnov@gmail.com', '123abc'), aes_encrypt('456159753', '123abc'), aes_encrypt('Praha, Vodičkova', '123abc')); -- sifrovani dat zakazniku pod heslem 123abc
 insert into objednavka(zakaznik, datum) values (1, '2017-05-03');
 insert into seznam(zbozi, objednavka, pocet) values (1, 1, 3), (2, 1, 1);
 -- zkusebni data
 
 -- vypis vsech zaznamu
select objednavka.objednavka_id as 'ID objednavky',
objednavka.datum as 'Datum',
 cast(aes_decrypt(zakaznik.jmeno, '123abc') as char) as 'Zakaznik jmeno:',
 cast(aes_decrypt(zakaznik.prijmeni, '123abc') as char) as 'Zakaznik prijmeni:',
 cast(aes_decrypt(zakaznik.telefon, '123abc') as char) as 'Zakaznik telefon:',
 zbozi.cena as 'Cena',
 zbozi.nazev as 'Zbozi',
 seznam.pocet as 'Pocet zbozi',
 dodavatel.firma as 'Dodavatel'
 from dodavatel 
 inner join zbozi on zbozi.dodavatel = dodavatel.dodavatel_id
 inner join seznam on seznam.zbozi = zbozi.zbozi_id
 inner join objednavka on objednavka.objednavka_id = seznam.objednavka
 inner join zakaznik on zakaznik.zakaznik_id = objednavka.zakaznik;
 -- vypis vsech zaznamu
 
 -- celkova cena objednavky
 select sum(zbozi.cena) as 'Celkova cena objednavky',
 objednavka.objednavka_id as 'ID objednavky',
 cast(aes_decrypt(zakaznik.jmeno, '123abc') as char) as 'Zakaznik jmeno:',
 cast(aes_decrypt(zakaznik.prijmeni, '123abc') as char) as 'Zakaznik prijmeni:',
 cast(aes_decrypt(zakaznik.telefon, '123abc') as char) as 'Zakaznik telefon:'
 from zakaznik
 inner join objednavka on objednavka.zakaznik = zakaznik.zakaznik_id
 inner join seznam on seznam.objednavka = objednavka.objednavka_id
 inner join zbozi on zbozi.zbozi_id = seznam.zbozi
 inner join dodavatel on dodavatel.dodavatel_id = zbozi.dodavatel group by objednavka.objednavka_id;
 -- celkova cena objednavky
 
 -- selekce objednavky
 select objednavka.objednavka_id as 'ID objednavky',
 cast(aes_decrypt(zakaznik.jmeno, '123abc') as char) as 'Zakaznik jmeno:',
 cast(aes_decrypt(zakaznik.prijmeni, '123abc') as char) as 'Zakaznik prijmeni:',
 cast(aes_decrypt(zakaznik.telefon, '123abc') as char) as 'Zakaznik telefon:',
 zbozi.nazev as 'Zbozi',
 zbozi.cena as 'Cena',
 seznam.pocet as 'Pocet zbozi',
 dodavatel.firma as 'Dodavatel'
 from dodavatel 
 inner join zbozi on zbozi.dodavatel = dodavatel.dodavatel_id
 inner join seznam on seznam.zbozi = zbozi.zbozi_id
 inner join objednavka on objednavka.objednavka_id = seznam.objednavka
 inner join zakaznik on zakaznik.zakaznik_id = objednavka.zakaznik where objednavka.objednavka_id = 1;
 -- selekce objednavky
 
 -- pocet polozek objednavky
 select sum(seznam.pocet) as 'Pocet polozek',
 objednavka.objednavka_id as 'ID objednavky',
 cast(aes_decrypt(zakaznik.jmeno, '123abc') as char) as 'Zakaznik jmeno:',
 cast(aes_decrypt(zakaznik.prijmeni, '123abc') as char) as 'Zakaznik prijmeni:',
 cast(aes_decrypt(zakaznik.telefon, '123abc') as char) as 'Zakaznik telefon:'
 from zakaznik
 inner join objednavka on objednavka.zakaznik = zakaznik.zakaznik_id
 inner join seznam on seznam.objednavka = objednavka.objednavka_id
 inner join zbozi on zbozi.zbozi_id = seznam.zbozi
 inner join dodavatel on dodavatel.dodavatel_id = zbozi.dodavatel group by objednavka.objednavka_id;
 -- pocet polozek objednavky
 
 -- pocet objednavek u zakaznika
 select count(objednavka.objednavka_id) as 'Pocet objednavek',
 zakaznik.zakaznik_id as 'ID zakaznika',
 cast(aes_decrypt(zakaznik.jmeno, '123abc') as char) as 'Zakaznik jmeno:',
 cast(aes_decrypt(zakaznik.prijmeni, '123abc') as char) as 'Zakaznik prijmeni:',
 cast(aes_decrypt(zakaznik.telefon, '123abc') as char) as 'Zakaznik telefon:'
 from zakaznik
 inner join objednavka on objednavka.zakaznik = zakaznik.zakaznik_id
 inner join seznam on seznam.objednavka = objednavka.objednavka_id
 inner join zbozi on zbozi.zbozi_id = seznam.zbozi
 inner join dodavatel on dodavatel.dodavatel_id = zbozi.dodavatel group by zakaznik.zakaznik_id;
 -- pocet objednavek u zakaznika
 