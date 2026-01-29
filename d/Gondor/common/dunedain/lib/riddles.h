
/*
 *	Format of the riddles:
 *	({ riddle, solution, riddle, solution, ... })
 *	solution = ({ solution1, solution2, ..., solution_N, })
 *      solution_1 = ({ alternative_1, alternative_2, ... })
 *
 *	==> ({ riddle1, ({ ({ alt_111, alt_112, }), ({ alt_121, alt_122, }), ({ alt_131, }), )},
 *	       riddle2, ... })
 *
 *       Modicications:
 *       April 5 2000 Stern : added "Great Battle" to RIDDLES_LEV6 battles.
 *       August 14 2001 Skippern : corrected solutions to "Fell winter" in
 *                                   RIDDLES_LEV10.
 */
#define RIDDLES_LEV1	({ \
	"Name the Two Trees that gave light to Valinor before the Coming of the Sun and the Moon!", \
	({ ({ "Laurelin" }), ({ "Telperion" }) }), \
	"Who is Steward in Gondor?", \
	({ ({ "Denethor", "Denethor II" }) }), \
	"Who is King of Rohan?", \
	({ ({ "Theoden" }) }), \
	"Who was the last King of Arnor?", \
	({ ({ "Earendur" }) }), \
	"What was the name of the first Ruling Steward of Gondor?", \
	({ ({ "Mardil Voronwe", "Mardil", }), }), \
	"Who is the Lord of the realm of Arda, King of the Valar, first of all Kings?", \
        ({ ({ "Manwe", "Sulimo", "Manwe Sulimo", }), }), \
			})
#define RIDDLES_LEV2	({ \
        "Who is Lord of the Waters?", \
	({ ({ "Ulmo", }), }), \
	"Who belonged to the Valar once but is not counted among them any more?", \
	({ ({ "Melkor", "Morgoth", }), }), \
	"Who is the Lady of the Stars?", \
	({ ({ "Varda", "Elbereth", "Varda Elbereth", }), }), \
	"Which of the Valar is called 'the Smith'?", \
   ({ ({ "Aule", "Mahal", "Aule Mahal", }), }), \
	"Who is the Giver of Fruits, Queen of the Earth?", \
	({ ({ "Yavanna", "Kementari", "Yavanna Kementari", }), }), \
	"Who created the Silmarilli?", \
	({ ({"Feanor", }), }), \
			})
#define RIDDLES_LEV3	({ \
	"Who of the Valar are the Feanturi?", \
	({ ({ "Namo", "Mandos", "Namo Mandos", }), ({ "Lorien", "Irmo", "Irmo Lorien", }), }), \
	"Who is the sister of the Feanturi?", \
	({ ({ "Nienna", }), }), \
	"Who is greatest in strength and deeds of prowess among the Valar?", \
	({ ({ "Tulkas", "Tulkas Astaldo", "Astaldo", }), }), \
	"In what year of the Third Age did the Rohirrim come to Calenardhon?", \
	({ ({ "2510", "TA 2510", }), }), \
	"Who was the leader of the Rohirrim when they came to Calenardhon?", \
	({ ({ "Eorl", "Eorl the Young", }), }), \
   "Who was Steward in Gondor when the Rohirrim came to Calenardhon?", \
   ({ ({ "Cirion", }), }), \
			})
#define RIDDLES_LEV4	({ \
	"How many White Trees were there in Gondor? From which tree came the fruit " \
	  + "from which the first of the White Trees of Gondor was grown? " \
	  + "And in which city grew the tree from which the fruit was taken?", \
	({ ({ "Three", "3", }), ({ "Nimloth", "Nimloth the Fair", }), ({ "Armenelos", }), }), \
	"Who are the Lords of the Valar?", \
   ({ ({ "Manwe", "Sulimo", "Manwe Sulimo", }), ({ "Ulmo", }), ({ "Aule", "Mahal", "Aule Mahal", }), \
           ({ "Orome", "Araw", "Orome Araw", }), ({ "Mandos", "Namo", "Namo Mandos", }), \
	   ({ "Lorien", "Irmo", "Irmo Lorien", }), \
           ({ "Tulkas", "Tulkas Astaldo", "Astaldo", }), }), \
	"Who are the Valier, the Queens of the Valar?", \
	({ ({ "Varda", "Elbereth", "Varda Elbereth", }), \
           ({ "Este", }), ({ "Yavanna", "Kementari", "Yavanna Kementari", }), \
           ({ "Nienna", }), ({ "Vaire", }), ({ "Vana", }), ({ "Nessa", }), }), \
	"Who is the father of the house of the Stewards of Gondor, " \
	  + "and of what part of the realm was he the Lord?", \
	({ ({ "Hurin", }), ({ "Emyn Arnen", }), }), \
	"Name all of the Ship-kings of Gondor.", \
	({ ({ "Tarannon", "Tarannon Falastur", "Falastur",  }), ({ "Earnil I", "Earnil", }), ({ "Ciryandil", }), \
           ({ "Hyarmendacil I", "Hyarmendacil", }), }), \
			})
#define RIDDLES_LEV5	({ \
	"What are the names of the first Three Houses of the Edain?", \
	({ ({ "Beor", }), ({ "Hador", }), ({ "Haladin", "Haleth", }), }), \
	"What are the names of the High Kings of the Noldor in Middle Earth?", \
	({ ({ "Fingolfin", }), ({ "Fingon", }), ({ "Turgon", }), ({ "Gilgalad", "Gil-galad", "Ereinion", }), }), \
	"What was Sauron's name when he dwelt among the elves of Eregion in the Second Age?", \
	({ ({ "Annatar", }), }), \
	"What was the name of Isildur's sword?", \
	({ ({ "Narsil", }), }), \
	"What are the names of the three hosts of the Eldar that followed Orome from Cuivienen?", \
	({ ({ "Vanyar", }), ({ "Noldor", }), ({ "Teleri", }), }), \
	"Who were the Lords of the three hosts of the Eldar that set forth from Cuivienen?", \
	({ ({ "Ingwe", }), ({ "Finwe", }), ({ "Elwe", "Olwe", "Elwe and Olwe", }), }), \
			})
#define RIDDLES_LEV6	({ \
	"Name the three kingdoms into which the North Kingdom, Realm of Arnor, decayed.", \
	({ ({ "Arthedain", }), ({ "Cardolan", }), ({ "Rhudaur", }), }), \
	"What are the names of the sons of Fingolfin?", \
	({ ({ "Fingon", }), ({ "Turgon", }), }), \
	"Who is the mother of Galadriel? And who is her mother's father?", \
	({ ({ "Earwen", }), ({ "Olwe", "Olwe of Alqualonde", }), }), \
	"Where is the abode of Manwe?", \
	({ ({ "Taniquetil", "Oiolosse", "Amon Uilos", }), }), \
	"Name the Five Battles of the War of the Silmarilli.", \
	({ ({ "Dagor-nuin-Giliath", "Battle-under-Stars", "Battle under Stars", }), \
	   ({ "Dagor Aglareb", "The Glorious Battle", }), \
	   ({ "Dagor Bragollach", "The Battle of the Sudden Flame", }), \
	   ({ "Nirnaeth Arnoediad", "Unnumbered Tears", }), \
({ "The Great Battle", "Great Battle", "War of Wrath", "The War of Wrath", }), }), \
	"Who slew Gothmog, Lord of Balrogs and high-captain of Angband?", \
	({ ({ "Ecthelion", "Ecthelion of the Fountain", }), }), \
			})
#define RIDDLES_LEV7	({ \
	"What is the name of the sword of the King of Rohan?", \
	({ ({ "Herugrim", }), }), \
	"Name the children of Finarfin, son of Finwe.", \
	({ ({ "Finrod", "Felagund", "Finrod Felagund", }), ({ "Orodreth", }), \
	   ({ "Angrod", }), ({ "Aegnor", }), ({ "Galadriel", }), }), \
	"What are the names of the three mariners that accompanied Earendil on all his voyages?", \
	({ ({ "Aerandir", }), ({ "Falathar", }), ({ "Erelond", "Erellont", }), }), \
	"Which were the names of swords of Fingolfin, of Turgon, his son, and of Elwe Singollo, Lord of Beleriand?", \
	({ ({ "Ringil", }), ({ "Glamdring", }), ({ "Aranruth", }), }), \
	"Which Lords of the Eldar were slewn by Gothmog, Lord of Balrogs and high-captain of Angband? " \
	  + "And who was captured by Gothmog during the Nirnaeth Arnoediad?", \
	({ ({ "Feanor", }), ({ "Fingon", }), ({ "Ecthelion", }), ({ "Hurin", }), }), \
			})
#define RIDDLES_LEV8	({ \
	"Name the sons of Feanor.", \
	({ ({ "Maedhros", }), ({ "Maglor", }), ({ "Celegorm", }), ({ "Caranthir", }), \
	   ({ "Curufin", }), ({ "Amrod", }), ({ "Amras", }), }), \
	"Who were the grand parents of Elrond and Elros?", \
	({ ({ "Tuor", }), ({ "Idril", "Idril Celebrindal", }), \
	   ({ "Dior", "Dior Eluchil", }), ({ "Nimloth", "Nimloth of Doriath", }), }), \
   "What was the name of Anglachel after it was reforged? Who wielded it, " \
     + "and under which name was he known because of his sword?", \
	({ ({ "Gurthang", }), ({ "Mormegil", }), ({ "Turin", "Turin Turambar", }), }), \
	"What were the names of the weapons of Beleg Cuthalion?", \
	({ ({ "Anglachel", }), ({ "Belthronding", }), }), \
			})
#define RIDDLES_LEV9	({ \
	"Name the last twelve companions of Barahir, Lord of the House of Beor, " +\
	"in Dorthonion after the Dagor Bragollach.", \
	({ ({ "Beren", }), ({ "Baragund", }), ({ "Belegund", }), ({ "Radhruin", }), \
	   ({ "Dairuin", }), ({ "Dagnir", }), ({ "Ragnor",}), ({ "Gildor", }), \
	   ({ "Gorlim", }), ({ "Arthad", }), ({ "Urthel", }), ({ "Hathaldir", }), }), \
	"What are the names of the swords that Eol forged from meteoric iron?", \
	({ ({ "Anglachel", }), ({ "Anguirel", }), }), \
	"Which weapons of renown were forged by Telchar of Nogrod?", \
	({ ({ "Narsil", }), ({ "Angrist", }), }), \
	"Who betrayed the hiding place of Barahir and his companions in Dorthonion?", \
	({ ({ "Gorlim", "Gorlim the Unhappy", "Gorlim the Accursed", }), }), \
			})
#define RIDDLES_LEV10	({ \
	"What are the names of the children of Elros?", \
	({ ({ "Vardamir", "Vardamir Nolimon", "Nolimon", }), ({ "Tindomiel", }), \
	   ({ "Manwendil", }), ({ "Atanalcar", }), }), \
	"Give the Elvish names of all of the five Istari.", \
	({ ({ "Curunir", }), ({ "Mithrandir", }), ({ "Radagast", }), ({ "Alatar", }), ({ "Pallando", }), }), \
	"Where was the Grave of Elendil?", \
        ({ ({ "Halifirien", "Amon Anwar", "Hill of Awe", "Eilenaer", }), }), \
	"Who was the spouse of Silmarien, daughter of Tar-Elendil?", \
	({ ({ "Elatan", "Elatan of Andunie", }), }), \
	"What was the name of the wife of Aldarion, Heir to the throne of Numenor, and where did she live?", \
	({ ({ "Erendis", }), ({ "Emerie", "Mittalmar", }), }), \
	"Who was Captain of the Outer Gate of the Orfalch Echor in the year of the Fell Winter?", \
	({ ({ "Elemmakil", "Ecthelion", }), }), \
			})
#if 0
#define RIDDLES_LEV4	({ })
#define RIDDLES_LEV5	({ })
#define RIDDLES_LEV6	({ })
#define RIDDLES_LEV7	({ })
#define RIDDLES_LEV8	({ })
#define RIDDLES_LEV9	({ })
#define RIDDLES_LEV10	({ })
#endif

