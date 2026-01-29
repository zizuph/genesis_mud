=========================
PENDRAGONS for LIBRARIANS
=========================
Vitwitch 10/2020

A somewhat-personalised reward item for Librarians of Guilds and Clubs across Genesis.
Please note - this is NOT a quest.  This does NOT provide experience of any kind.
Pendragons have NO combat value.

Code path:
----------
/d/Khalakhor/se_speir/claryn/tabor/pendragon/

Object files:
-------------

pendragon_woman.c	Danuine, Woman in Woad, servant of Danu, Goddess of Wisdom in
			Khalakhor.  The tattoos on her body tell a story and provide
			the syntax by which Librarians of Genesis can claim the gift
			of Danu, a pendragon, to help them in their librarian duties. 

pendragon.c		personalised dragon tattoo-artist and one-way messenger provided as a
                        reward to all Librarians of Genesis guilds and clubs for their service
                        in enchancing the written content of the game;  pendragon ink-colour
			is selected from 36 possible options based on NAME_TO_RANDOM() to 
			individualise the pendragon of any given librarian.

pendragon_adder.c	***object to be cloned by wizards into their inventory if they
			wish to add a library-path or librarian name to the pendragon
         		access list (pendragon_librmap.o); adding the library-path is 
			preferred over explicit librarian names since it means that
			newly appointed librarians will be able to access pendragons
			without further wizard intervention.

pendragon_tattoo.c      dragon_tattoo object, one line of text message created by pendragon
			that can be used to summon pendragon after it has been dismissed;
                        librarians can carry as many dragon_tattoos as they like; can be
                        removed by the librarian.

pendragon_inkblot.c	one-way message object delivered by pendragon; can be removed by
			the recipient; pendragons do not hang around to take replies.

pendragon_librmap.o	mapping containing library-paths and/or librarian-names which
			is checked when a player tries to ask the pendragon_woman
			for her gift; non-librarians are ineligible for the gift.


In-game location of Danuine, the Woman in Woad
(cloned instance of pendragon_woman object)
where Librarians can seek their pendragon:
------------------------------------------

/d/Khalakhor/se_speir/claryn/tabor/room/trail_0


****HINT to be provided to Guild/Club/etc Librarians by guild/domain wizards
so that they know to go in search of a reward for their service:
----------------------------------------------------------------

O Keeper of Written Words: hear the call from far-off Khalakhor...

On the high crest of a grassy hill overlooking a sleepy village,
amidst rocky outcrops, there lies the Woman in Woad. Come learn
her story of duty and sacrifice in the preservation of written
knowledge in these wide Realms. In so doing, you may ask of her
the gift of Danu, to better discharge your sacred duty. 


=======EOF===============================

