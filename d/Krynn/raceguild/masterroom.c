/* This is the master room of the Krynn race guild.
 * New regions, family names etc. can be added here.
 *
 * Version 0.01, ~Aridor 12/96
 *
 * revision history:
 * 17/03-200 by Boron - Added Hammerfist to the dwarves on request from
 *					  - the player Blizzard
 * Milan 10.9.02 - fixed runtime error caused by familynames - region_boos
 *	records not matching + added extra check in update_book(...)
 */

#include "/d/Krynn/common/defs.h"

inherit "/std/room";

/* mapping familynames
 * -------------------
 * Format ([<race>:([<region>:({ ({<region title>,...}), <lastname>,...}) ]) ])
 *
 * For each race, there is a mapping with a number of regions the player can
 * come from. Within each region, there are region title(s) and lastnames
 * available.
 * The player can choose either one lastname or one region title, or he can
 * choose a combination of both. Example: * Given the region:
 *    (["solamnian human":({ ({"of Solamnia", "of Palanthas" }), "Silverblade",
	"Dallyon",})])
 *    Teth of Solamnia, male human
 *    Teth Dallyon, male human
 *    Teth Dallyon of Solamnia, male human
 *    Teth Silverblade of Palanthas, male human
 * are all valid choices. However,
 *    Teth of Palanthas of Solamnia, male human
 * or even
 *    Teth of Solamnia of Solamnia, male human
 * is NOT possible.
 *
 *
 *
 *
 * NOTE: The mud does not support special characters in the names,
 * therefore they can not be allowed!!!!
 *
 *
 * After adding a new name, be sure to update the library books with
 * Call /d/Krynn/raceguild/masteroom update_books
 * The kender do not keep a book in the library and are not updated.
 *
 */
mapping familynames =
(["human":(["abanasinian human":({ ({"of Abanasinia", "of Ankatavaka",
	"of Crossing", "of Esker",
	"of Goodbay", "of Haven",
	"of Long Ridge", "of Que-Kiri",
	"of Que-Shu", "of Que-Teh",
	"of Solace", "of Tantallon",
	"of Zaradene",
      }),
      "Acorn", "Adams", "Aranta",
      "Ashleaf", "Avynn", "Batoche",
      "Brant", "Calla", "Cowen",
      "Dasaray", "Dawnstar",
      "Dervlin", "Elithon",
      "Eveningstar", "Evertear", "Faud",
      "Ferin", "Gannel", "Gentle",
      "Haddun", "Huckle", "Icetear",
      "Ironfeld", "Jessop", "Jurrie",
      "Kastay", "Krane", "Lakes",
      "Loime", "Mees", "Moonglow",
      "Nightbreeze", "Noll", "Oan",
      "Ossan", "Patrick", "Preston",
      "Quill", "Robyne",
      "Sandath", "Skygazer", "Softsulle",
      "Tigereye", "Toront", "Trillium",
      "Uth Destar", "Vallen", "Vireo",
      "Waylan", "Wesley", "Westan",
      "Ylled", "Zemlan",
    }),
    "balifor human":({ ({"of Balifor", "of Flotsam",
	"of Port Balifor",
      }),
      "Acelin", "Alawen", "Astode",
      "Baldmar", "Bernard", "Cano",
      "Christophe", "Darthe", "Di'thon", "Durris",
      "Farsted", "Kar-thon", "Ketral",
      "Laria", "Roberts", "Talayn",
      "Werinnon", "Wyrd",
    }),
    "minotaur":({ ({"of Mithas", "of Kothas",
                    "of Nethosak", "of Holakan",
                    "of Saifhum", "of Karthay",
                    "of Lacynos", "of Kalpethis",
                    "of Morthosak",
      }),
      "De-Kaz", "De-Orilg",
      "De-Toron", "De-Flarok",
      "De-Teskos", "Es-Hestos",
      "Es-Kalin", "Es-Istian",
      "El-Halup", "Et-Pethis",
      "Ohn-Koraf", "Ra-Kar",
    }),

    "draconian":({ ({"of Pax Tharkas", "of Solace",
                    "of Flotsam", "of Port Balifor",
                    "of Gateway", "of Tarsis",
                    "of Xak Tsaroth", "of Icereach",
                    "of Neraka", "of Sanction",
					"of Zakhalax", "of Teyr",
      }),
      "Kapak", "Aurak","Bozak", "Sivak",
    }),
	
    "ergothian human":({ ({"of Bavil", "of Brandal", "of Dalevil",
	"of Daltigoth", "of Daring",
	"of Eastport", "of Ergoth",
	"of Errow", "of Fairkeep",
	"of Finn", "of Gulfport", "of Gwynned",
	"of Heit", "of Hilfort", "of Insel",
	"of Lancton", "of Linsel", "of Logan",
	"of Mereklar", "of Northern Ergoth",
	"of Pontigoth", "of Serval",
	"of Southern Ergoth",
	"of Sutvil", "of Thonvil", "of Vocalion",
	"of Zhea Harbour",
      }),
      "Aelfred", "Aerin", "Alidale",
      "Bailey", "Beacham", "Caerroil",
      "Camber", "Clark", "Dallyon",
      "De Ayrennyn", "De Winter",
      "Douceson", "Edaece", "Elsworth",
      "Forthe", "Fuller", "Gilliot",
      "Godard", "Hawkins", "Henslow",
      "Ipsword", "Jomorthy", "Kay", "Kendrick",
      "Kent", "Killian", "Littel",
      "Llewyl", "Maedric", "Mellegien",
      "Myrtis", "Noble", "Northiby",
      "Olivier", "Ordred", "Pendragon",
      "Preston", "Pytrigon", "Quentin",
      "Qrushis", "Raka", "Rensworth",
      "Roberts", "Roderick", "Sancton",
      "Sterne", "Thornton", "Toppe",
      "Trevelyan", "Uriens", "Walters",
      "Wesley", "Ymes",
    }),
    "elian human":({  ({ "of Elian Wilds", "of Misty Isle",
        }),
    "Evarista",
    }),
    "estwilde human":({ ({"of Estwilde", "of Kalaman",
      }),
      "Adan", "Aimil", "Akvar",
      "Edilaron", "Kashi", "Killian",
      "Roberts", "Wiatlan",
    }),
    "half-elf":({ ({"of Abanasinia", "of Balinest", "of Belkuthas",
	"of Flotsam", "of Halter Wood", "of Haven",
	"of Palanthas", "of Qualinost", "of Solace",
	"of Tantallon",
      }),
      "Aerinha", "Ahanna", "Aladan", "Allyn", "Amethyst",
      "Amrisha", "Anvareth", "Balderon", "Benderick",
      "Brandolyn", "Brynnda", "Caoinleain", "Chibuike",
      "Cyne", "Dacia", "Deorawine", "Donnelaith",
      "Elessea", "Eevroen", "Estelle", "Falconeye",
      "Flora", "Germaine", "Gileana", "Half-Elf",
      "Half-Elven", "Half-Human", "Hawkflight",
      "Illissia", "Issel", "Jacinta", "Jeliala",
      "Lassalal", "Laurealote", "Lilias",
      "Maddalena", "Merie", "Nsa'la", "Nyssa",
      "Oceanus", "Orsola", "Peleswyff", "Phoebe",
      "Quilliam", "Quith", "Rhynne", "Rose",
      "Saluayn", "Saress", "Shadowstar", "Silverleaf",
      "Silvyre", "Tallis", "Taras", "Tsalasa", "Usse",
      "Vallena", "Wildwood", "Wyllows", "Zyllis",
    }),
    "icereach human":({ ({"of Icereach",
	"of the Ice Folk Village",
      }),
      "Aesa", "Aleric", "Annica",
      "Ellirt", "Glacen", "Kneiss",
      "Knut",
    }),
    "kern human":({ ({"of Kern", "of Kernen",
      }),
      "Haemas", "Sarga", "Woard",
      "Zeboa",
    }),
    "khur human":({ ({"of Khur", "of Zhakar",
      }),
      "Anarch", "Arak", "Ares",
      "Haemas", "Sarga", "Zeboa",
    }),
    "nordmaar human":({ ({"of Nordmaar", "of North Keep",
      }),
      "Alssa", "Arnwulf", "Aska",
      "Kevisson", "Olsson",
      "Vinasson",
    }),
    "sancrist human":({ ({"of Castle Uth Wistan", "of Gunthar",
	"of Sancrist", "of Sancrist Isle",
      }),
      "Arnand", "Asden", "Attehyll",
      "Lyrdriat", "Pender", "Roberts",
      "Uth Wistan",
    }),
    "solamnian human":({ ({"of Ash", "of Brasdel", "of Caergoth",
	"of Caermish", "of Coastlund", "of Daron",
	"of Dargaard Keep", "of Dart", "of Deepdel",
	"of Edgerton", "of Elkholm", "of Elmwood",
	"of Fangoth", "of Gaardlund",
	"of Garnet", "of Gulbluff", "of Gwyntarr",
	"of Hamilton", "of Heartlund",
	"of Kyre", "of Lathe", "of Lemish",
	"of Lockhart", "of Maelgoth",
	"of Mageport", "of Manydell",
	"of Palanthas", "of Portsmith", "of Rening",
	"of Sancrist", "of Solamnia", "of Solanthus",
	"of Southlund", "of Starport",
	"of Tanith", "of Thelgaard Keep",
	"of Two Creek", "of Vingaard",
	"of Vingaard Keep", "of Walmish",
	"of Wayfold", "of Winterholm",
      }),
      "Alabaster", "Auguste", "Avaline",
      "Beam", "Beaumont", "Brightblade",
      "Calamon", "Caldwell", "Celtis", "Colfax",
      "Crownguard", "Darkmoor", "Delancis",
      "di Caela", "di Castellan", "Dragonbane",
      "Eagles", "Edgesword", "Fletcher",
      "Freeman", "Gelt", "Grimbane",
      "Hawthorn", "Hinton", "Idde",
      "Istanandus", "Jochanan", "Jeoffrey",
      "Kolan", "Kyrus", "Ledyard", "Llewyl",
      "Makalis", "MarKenin", "MarThasal",
      "Mayfair", "Montoya", "Nanta", "Ochre",
      "Pathwarden", "Pender", "Peres", "Raka",
      "Redworth", "Roberts", "Sams", "Sennay",
      "Shadowstar", "Sifte", "Silverblade",
      "Soth", "Steelheart", "Stoutoak", "Tallbow",
      "Thornton", "Tiberio", "Trueheart",
      "Usten", "Uth Maer", "Uth Matar",
      "Uth Nall", "Uth Parreth", "Uth Vinsent",
      "Verne", "Wesley", "Whiteguard",
      "Wyvernsbane", "Yellin",
    }),
    "taman busuk human":({ ({"of Jelek", "of Neraka",
	"of Sanction", "of Taman Busuk",
      }),
      "Adamo", "Akkad", "Atila",
      "Lockne", "Monmart", "Sarga",
      "Senn", "Zeboa",
    }),
    "tarsis human":({ ({"of Tarsis", "of Zeriak",
      }),
      "Ailean", "Ames",
      "Gloome", "Sandspit",
    }),
  ]),

  "elf":(["dark elf":({ ({
      }),
      "the Dark Elf", "the Dark", "the Outcast of Qualinesti",
      "the Outcast of Silvanesti", "the Outcast"
    }),
    "half-human":({ ({"of Abanasinia", "of Balinest", "of Belkuthas",
	"of Flotsam", "of Halter Wood", "of Haven",
	"of Palanthas", "of Qualinost", "of Solace",
	"of Tantallon",
      }),
      "Aerinha", "Ahanna", "Aladan", "Allyn", "Amethyst",
      "Amrisha", "Anvareth", "Balderon", "Benderick",
      "Brandolyn", "Brynnda", "Caoinleain", "Chibuike",
      "Cyne", "Dacia", "Deorawine", "Donnelaith",
      "Elessea", "Eevroen", "Estelle", "Falconeye",
      "Flora", "Germaine", "Gileana", "Half-Elf",
      "Half-Elven", "Half-Human", "Hawkflight",
      "Illissia", "Issel", "Jacinta", "Jeliala",
      "Lassalal", "Laurealote", "Lilias",
      "Maddalena", "Merie", "Nsa'la", "Nyssa",
      "Oceanus", "Orsola", "Peleswyff", "Phoebe",
      "Quilliam", "Quith", "Rhynne", "Rose",
      "Saluayn", "Saress", "Shadowstar", "Silverleaf",
      "Silvyre", "Tallis", "Taras", "Tsalasa", "Usse",
      "Vallena", "Wildwood", "Wyllows", "Zyllis",
    }),
    "kagonesti elf":({ ({"of Kagonesti", "of Southern Ergoth",
      }),
      "Alvy", "Aquine", "Aster", "Belrene",
      "Brirn", "Caileass", "Cynbel", "Danielle",
      "Danis", "Del'Verden", "Dencede", "Elema", "Erthey",
      "Faerr", "Falconclaw", "Gilden", "Gullcry",
      "Hazel", "Hilles", "Icess", "Immin",
      "Jaycall", "Juniper", "Kasse", "Kimbrel",
      "Lilysbreath", "Luness", "Mallow",
      "Moonseye", "Nansala", "Nuitekin",
      "Oakslife", "Otterstail", "Pineresin",
      "Poolsdeep", "Quietleaf", "Rainmoss",
      "Reswyll", "Soroine", "Starsblood",
      "Tselune", "the Wilder Elf", "Thunderstorm",
      "Ursa", "Vinesinew", "Vitas", "Watersoft",
      "Yellowbloom", "Zenithe",
    }),
    "qualinesti elf":({ ({"of Ahtanost", "of Blanost", "of Frenost",
	"of Havlinost", "of Lauranost", "of Porliost",
	"of Qualinesti", "of Qualinost", "of Shrivost",
      }),
      "Adaeria", "Aladas", "Annalaveras", "Arvaire",
      "Belearas", "Buteras", "Cellion",
      "Clirriel", "Dalel", "Dalleteriel",
      "Desseras", "Emalis", "Ennobredar",
      "Estivas", "Evennas", "Fealthas", "Flierie",
      "Gilanas", "Hallas", "Halvanas", "Havlinas",
      "Herrais", "Illas", "Inniel", "Jallerel",
      "Jennederel", "Kananas", "Kerrillas",
      "Lilias", "Lonniel", "Lureas", "Maplequer",
      "Merrinas", "Nallias", "Nimphais", "Oleas",
      "Onniel", "Paselas", "Prellias", "Quillas",
      "Quivillas", "Revellas", "Rillias", "Sivas",
      "Solaneas", "Talenteriel", "Tenniel", "Thanas",
      "Thalasa", "Ullasa", "Vallas", "Wylleriel",
    }),
    "silvanesti elf":({ ({"of Alinosti", "of Balinost",
	"of Brattalnosti", "of Felinosti",
	"of Kurinost", "of Phalinost", "of Ravinost",
	"of Shalost", "of Shanarah", "of Silvanesti",
	"of Silvanost", "of Sithelnost",
      }),
      "Arcstar", "Argenta", "Autumntide",
      "Bluesky", "Breezesoft", "Caladon",
      "Calanathas", "Dawnsky", "Deepglow",
      "E'lithas", "Eveningblaze", "Everlight",
      "Fairvoice", "Feyre", "Fireblaze", "Greeneyes",
      "Hopedawn", "Huith", "I'lith", "Imathas",
      "J'lith", "J'ranthas", "Kanan", "Kazalanthas",
      "L'tah", "Landsoft", "Lith", "Mayflower",
      "Moonrose", "Moonsong", "N'lith", "Nearsky",
      "O'lith", "Palmopen", "Pondsparkle",
      "Qui'lith", "Q'lith", "Rainpatter",
      "Rainsigh", "Redhair", "Silverfang",
      "Sithnal", "Skytear",
      "Starbreeze", "Summerstone", "Tansoft",
      "Treekeeper", "Touchgentle", "U'lith",
      "Vathas", "Vinathas", "Windsigh", "Woven",
      "Y'lith", "Yllid", "Zenithsky",
    }),
    "draconian":({ ({"of Pax Tharkas", "of Solace",
                    "of Flotsam", "of Port Balifor",
                    "of Gateway", "of Tarsis",
                    "of Xak Tsaroth", "of Icereach",
                    "of Neraka", "of Sanction",
					"of Zakhalax", "of Teyr",
      }),
      "Kapak", "Aurak","Bozak", "Sivak",
    }),
  ]),

  "dwarf":(["kayolin mountain dwarf":({ ({"of Kayolin",
      }),
      "Armstrong",
    }),
    "kharolis hill dwarf":({ ({"of Hilltop",
	"of the Kharolis Mountains", "of Iron Delving", "of Estwilde",
	"of the Neidar",
      }),
      "Armflex", "Auburnhair", "Blackbeard",
      "Battlehammer", "Bluebellows", "Casden", "Claymoor",
      "Deepvoice", "Dregren", "Durathor",
      "Everlaugh", "Fireforge",
      "Forgebellows", "Freespirit",
      "Girthwide", "Gorth", "Hammerfall",
      "Hammerswing", "Hearthwarm",
      "the Hill Dwarf", "Hillminer",
      "Joysmile", "Killogre", /*"Khal n", sorry, NO special characters!!*/ "Leadfoot",
      "Lookclose", "Lurne", "Metalworker",
      "Miner", "Moonmaker", "Nearsight",
      "Orebearer", "Predune", "Rarestrength",
      "Rhodrune", "Rockblood", "Rockwarm",
      "Shaftmaker", "Steelshaper",
      "Tall", "Tantrumroar", "Teamworth",
      "Udune", "Veryshort", "Wellheart",
      "Zadune","Hammerfist",
    }),

    "thorbardin mountain dwarf":({ ({"of Northgate", "of Southgate",
	"of Thorbardin",
      }),
      "of the Daergar",
      "of the Daewar",
      "of the Hylar",
      "of the Klar",
      "of the Theiwar",
      "Winterseed",
    }),
     "vingaard mountain dwarf":({ ({"of Vingaard",
			       }),
			     }),
    "zhakar mountain dwarf":({ ({"of Zhakar",
      }),
      "Arkfire", "Axeswift",
    }),
    "minotaur":({ ({"of Mithas", "of Kothas",
                    "of Nethosak", "of Holakan",
                    "of Saifhum", "of Karthay",
                    "of Lacynos", "of Kalpethis",
                    "of Morthosak",
      }),
      "De-Kaz", "De-Orilg",
      "De-Toron", "De-Flarok",
      "De-Teskos", "Es-Hestos",
      "Es-Kalin", "Es-Istian",
      "El-Halup", "Et-Pethis",
      "Ohn-Koraf", "Ra-Kar",
    }),
    "draconian":({ ({"of Pax Tharkas", "of Solace",
                    "of Flotsam", "of Port Balifor",
                    "of Gateway", "of Tarsis",
                    "of Xak Tsaroth", "of Icereach",
                    "of Neraka", "of Sanction",
					"of Zakhalax", "of Teyr",
      }),
      "Kapak", "Aurak","Bozak", "Sivak",
    }),
  ]),

  "goblin":(["blode goblin":({ ({"of Blode", "of Bloten", "of Bludgeon",
	"of Brukt", "of Onyx", "of Sardonyx",
	"of Takar", "of Tarn", "of Vantal",
      }),
      "Akkz", "Axeth", "Blud", "Bozzek",
      "Cakkelz", "Deztroy", "Drezakk", "Ezzer",
      "Fangz", "Freakzho", "Fuzzik", "Gazz",
      "Gekk", "Hezzek", "Hokz", "Huzzuk",
      "Izzik", "Jawgz", "Jezzek", "Kanez",
      "Kazzek", "Kikz", "Lazz", "Lokzjaw",
      "Makzpain", "Mekkz", "Nawng", "Nozzik",
      "Okkz", "Otz", "Pazzik", "Pekkz",
      "Rakz", "Razakle", "Redz", "Skarr",
      "Skazz", "Skuzz", "Teznakk", "Tokz",
      "Uzzik", "Wazzak", "Wzzk", "Yazk",
      "Zakk", "Zezz", "Zeznakk", "Zukz",
    }),
    "kern goblin":({ ({"of Kern", "of Kernen",
      }),
      "Auma", "Azyuna",
      "Kane",
    }),
    "taman busuk goblin":({ ({"of Neraka", "of Ogrebond",
	"of Taman Busuk",
      }),
      "Augwild", "Azz",
      "Flikt", "Makfly", "Torak", "Visker",
    }),
    "throtyl goblin":({ ({"of Throt", "of Throtyl Gap",
      }),
      "Addler", "Arthrot",
      "Karnaj", "Malis", "Sadest",
    }),
    "hobgoblin":({ ({"of Throt", "of Throtyl Gap",
      "of Neraka", "of Ogrebond","of Kern", "of Kernen",}),
      "Addler", "Arthrot", "Augwild", "Auma", "Azyuna", "Azz",
      "Flikt", "Kane",
      "Karnaj", "Makfly", "Malis", "Sadest", "Torak", "Visker",
    }),
    "minotaur":({ ({"of Mithas", "of Kothas",
                    "of Nethosak", "of Holakan",
                    "of Saifhum", "of Karthay",
                    "of Lacynos", "of Kalpethis",
                    "of Morthosak",
      }),
      "De-Kaz", "De-Orilg",
      "De-Toron", "De-Flarok",
      "De-Teskos", "Es-Hestos",
      "Es-Kalin", "Es-Istian",
      "El-Halup", "Et-Pethis",
      "Ohn-Koraf", "Ra-Kar",
    }),

    ]),
  "hobbit":(["kender":({ ({"of Kendermore",
      "of Hilo", "the Wanderer", }),
      "Lockpicker", "Talespinner",
      "Stonethrower","Piemaker",
      "Lightheart","Yawnmaster",
      "Starthumb","Nettlekettle",
      "Treeskipper","Butterberry",
      "Bigpouch", "Makland",
      "Fleetfeet", "Thistleknot",
      "Shadowpoker", "Metwinger",
      "Nimblefingers", "Tanglemop",
      "Streamskimmer","Tendertongue",
      "Burrfoot","Trapspringer",
      "Burrthistle","Brambletow",
      "Tethersmeet","Flamehair",
      "Wrinklecap","Quickfoot",
      "Springtoe","Gatehop",
      "Pakslinger","Wanderfuss",
      "Gemgetter","Furrfoot",
      "Cloverleaf","Whistlerot",
      "Knotwillow","Elderdrake",
      "Twackdinger","Dunstan",
      "Cobblehammer","Hammerwart",
      "Lightfingers","Jingleburr",
      "Froghair","Goldring",
      "Thicketsway","Springheel",
      "Toymaker", "Skitterbug",
      "Treehugger", "Tippypaw",
      "Nimblenose", "Ogrekicker",
      "Razortongue", "Shadowcat",
      "Silkthread", "Quicksilver",
      "Tenderfinger", "Goldenknot",
      "Silverstreak", "Wondercoin"}),
  ]),
  
    "draconian":({ ({"of Pax Tharkas", "of Solace",
                    "of Flotsam", "of Port Balifor",
                    "of Gateway", "of Tarsis",
                    "of Xak Tsaroth", "of Icereach",
                    "of Neraka", "of Sanction",
					"of Zakhalax", "of Teyr",
      }),
      "Kapak", "Aurak","Bozak", "Sivak",
    }),
  /*"gnome":([]),
   * They have their own race guild in Krynn!
   */
]);

/*   0: no restrictions,
 *   1: knights only,
 *   2: good aligned only (>-200)
 *   4: evil aligned only (< 200)
 *   8:
 *  16:
 * add names in all lowercase please!!
 *
 * This is binary encoded, so giving a 6 will mean:
 * both good and evil aligned: ie. neutral.
 *
 */
mapping restriction =
([/* 1: knights only */
  "of thelgaard keep":1,
  "of vingaard":1,
  "of vingaard keep":1,

  /* 2: good aligned */
  "of ahlanost":2,
  "of blanost":2,
  "of frenost":2,
  "of havlinost":2,
  "of the hylar":2,
  "of the klar":2,
  "of lauranost":2,
  "of porliost":2,
  "of qualinesti":2,
  "of qualinost":2,
  "of silvanesti":2,
  "of silvanost":2,
  "of shalost":2,
  "of shrivost":2,

  /* 3: knight only & good aligned - all knights must be good anyway */

  /* 4: evil aligned */
  "of the daergar":4,
  "of the daewar":4,
  "of the theiwar":4,
  "of throt":4,
  "of blode":4,
  "of kern":4,
  "the dark elf":4,
  "the outcast of qualinesti":4,
  "the outcast of silvanesti":4,

  /* 5: knight only & evil aligned - guess that's empty :) */

  /* 6: good aligned & evil aligned = neutral! */
  "of tarsis":6,

  /* 7: knight only & good aligned & evil aligned
   * neutral knights? - nah... empty. */

  /* 8: nothing yet */

]);

mapping region_books =
(["human":(["abanasinian human":({("Abanasinian Humans\n" +
				   "==================\n" +
				   "Abanasinian humans are a sturdy race. After the Cataclysm, they rebuilt\n" +
				   "their homes and lands with vigour, and are now one of the more\n" +
				   "successful regions of Ansalon. The tribal names of Que-kiri, Que-shu,\n" +
				   "and Que-teh are typically nature-based.\n"),"abanasinia"}),
	    "balifor human":({("Humans of Balifor\n" +
			       "=================\n"),"balifor"}),
	    "ergothian human":({("Ergothian Humans\n" +
				 "================\n" +
				 "Ergothian humans are members of a race that had the first expansive\n" +
				 "human empire on Ansalon. Now, they are relegated to two islands west\n" +
				 "of the larger Solamnian province, but they are still influential and\n" +
				 "important peoples within Krynn.\n"),"ergoth"}),
	    "estwilde human":({("Humans of Estwilde\n" +
				 "=================\n"),"estwilde"}),
	    "icereach human":({("Humans of Icereach\n" +
				"==================\n"),"icereach"}),
	    /*"half-elf":({(""),"half-elf"}), this is already present in the elves section*/
	    "kern human":({("Humans of Kern\n" +
			    "==============\n"),"kern"}),
	    "khur human":({("Humans of Khur\n" +
			    "==============\n"),"khur"}),
	    "nordmaar human":({("Humans of Nordmaar\n" +
				"==================\n"),"nordmaar"}),
	    "sancrist human":({("Humans of Sancrist\n" +
				"==================\n"),"sancrist"}),
	    "solamnian human":({("Humans of Solamnia\n" +
				 "=================\n" +
				 "Hailing from the northern part of Ansalon, Solamnian humans are a strong\n" +
				 "race with strong ideals. From a nation founded by Vinas Solamnus, they\n" +
				 "are members of the largest human province on Ansalon.\n"),"solamnia"}),
	    "taman busuk human":({("Humans of Taman Busuk\n" +
				   "=====================\n"),"tamanbusuk"}),
	    "tarsis human":({("Humans of Tarsis\n" +
			      "================\n"),"tarsis"}),
// Milan 10.9.02 fixed minotaurs -> minotaur (see declaration of familynames)
	    "minotaur":({("Minotaurs of Krynn\n" +
			      "================\n"),"theminotaursofkrynn"}),
	    "draconians":({("Draconians of Krynn\n" +
			      "================\n"),"thedraconiansofkrynn"}),
				  
	    ]),
  "elf":(["dark elf":({("Dark Elves\n" +
			"==========\n" +
			"The Dark Elves are not a racial group, per se, but rather elves that have\n" +
			"cast aside the light and have delved into evil. When outcast, they are\n" +
			"stripped of their last names, and thus their families and heritage.\n" +
			"There are no known Kagonesti dark elves on record.\n"),"darkelves"}),
	  "half-human":({("The Half-Humans of Krynn\n" +
			  "========================\n" +
			  "The half-humans are considered such by elves only, therefore, this\n" +
			  "book is located in the Elf section. Anyone else will usually refer\n" +
			  "to these individuals as half-elves. Half-elves, or half-humans,\n" +
			  "whichever you might prefer, is commonly known as someone with an\n" +
			  "elvish mother and a human father. The other combination (human\n" +
			  "mother and elvish father) is not known to have produced offspring.\n"),"halfhumans"}),
	  "kagonesti elf":({("Kagonesti Elves\n" +
			     "===============\n" +
			     "The Wilder Elves, the Kagonesti are a tribal people that live in a \n" +
			     "primitive state relative to the other two main land-based groups of\n" +
			     "Elves, the Qualinesti and Silvanesti. They shun metal, and tend to\n" +
			     "use druidic magic.\n"),"kagonestielves"}),
	  "qualinesti elf":({("Qualinesti Elves\n" +
			      "================\n" +
			      "Those who separated from the Silvanesti called themselves Qualinesti\n" +
			      "Elves. They moved to the forest of Qualinesti with the capital\n" +
			      "Qualinost. These elves are seen much more often in the rest of Krynn\n" +
			      "than their cousins.\n"),"qualinestielves"}),
	  "silvanesti elf":({("Silvanesti Elves\n" +
			      "================\n" +
			      "The original tribe are the Silvanesti Elves with the capital Silvanost.\n" +
			      "They live very isolated in the woods of Silvanesti and rarely have\n" +
			      "contact with the rest of the world.\n"),"silvanestielves"}),
	  ]),
  "dwarf":(["kayolin mountain dwarf":({("Mountain Dwarves of the Kayolin Mountains\n" +
					"=========================================\n"),"kayolin"}),
	    "kharolis hill dwarf":({("Hill Dwarves of Kharolis Mountains\n" +
				     "==================================\n" +
				     "The Hill Dwarves of the Kharolis Mountains, also known as the Neidar,\n" +
				     "live in a region of Krynn populated by many other races, including\n" +
				     "the humans of Abanasinia and the elves of Qualinesti. They live in\n" +
				     "isolation from their other dwarven counterparts due to a long-\n" +
				     "standing rivalry. They are, however, a merry people, hard-working and\n" +
				     "strong.\n"),"kharolis"}),
	    "thorbardin mountain dwarf":({("Mountain Dwarves of the Thorbardin Mountains\n" +
					   "===================================\n"),"thorbardin"}),
	    "vingaard mountain dwarf":({("Mountain Dwarves of the Vingaard Mountains\n" +
					 "==========================================\n"),"vingaard"}),
	    "zhakar mountain dwarf":({("Mountain Dwarves of the Zhakar Mountains\n" +
				       "========================================\n"),"zhakar"}),
	    ]),
  "goblin":(["blode goblin":({("Blode Goblins\n" +
			       "=============\n" +
			       "The goblins of blode are notorious for their cruelty and evil manner.\n" +
			       "They are members of a race that is known for its strength. However,\n" +
			       "their small minds make them easily lead, and often they need to be\n" +
			       "kept in line by ogres or others.\n"),"blode"}),
	     "kern goblin":({("Kern Goblins\n" +
			      "============\n"),"kerngoblins"}),
	     "taman busuk goblin":({("Goblins of Taman Busuk\n" +
				     "======================\n"),"tamanbusukgoblins"}),
	     "throtyl goblin":({("Goblins of Throtyl\n" +
				 "==================\n"),"throtyl"}),
	     "hobgoblin":({("Hobgoblins\n" +
			    "==========\n"),"hobgoblin"}),
	     ]),
  "hobbit":([/* No books for the hobbits (kender), they keep their own history */
	     ]),
  ]);


void
update_book(string race, string region)
{
    mixed val = region_books[race];
    string intro, filename;
    string* areas;
    string* fnames;
    int i;

    if (!val)
    {
	notify_fail("No such race.\n");
	return;
    }
    val = val[region];
    if (!val)
    {
	notify_fail("No such region.\n");
	return;
    }

    intro = val[0];
    filename = "/d/Krynn/race/books/book/" + val[1];

    // Milan added this to check if familynames match region_books record
    val = familynames[race];
    if (!val)
    {
	notify_fail("No such race in familynames.\n");
	return;
    }
    val = val[region];
    if (!val)
    {
	notify_fail("No such region in familynames.\n");
	return;
    }

    rm(filename);
    write_file(filename,intro + "\n");

    areas = familynames[race][region][0];
    fnames = familynames[race][region][1..];

    if (region == "half-human")
      write_file(filename,"Type:     'Half-human' or 'Half-elf' depending on your original race.\n");
    else
      write_file(filename,"Type:     '" + C(region) + "'\n");

    write_file(filename,"Region:   ");
    for(i=0;i<sizeof(areas);i++)
    {
	write_file(filename,"'" + areas[i] + "', ");
	if (i < sizeof(areas)-1 && i % 4 == 3)
	  write_file(filename,"\n          ");
    }
    write_file(filename,"\nFamilies: ");
    for(i=0;i<sizeof(fnames);i++)
    {
	write_file(filename,"'" + fnames[i] + "', ");
	if (i < sizeof(fnames)-1 && i % 6 == 5)
	  write_file(filename,"\n          ");
    }
    write_file(filename,"\n");
}

void
update_race(string race)
{
    int i;
    string* idx = m_indexes(region_books[race]);

    for(i=0;i<sizeof(idx);i++)
      set_alarm(itof(i),0.0,&update_book(race,idx[i]));
}

void
update_books()
{
    int i;
    string* idx = m_indexes(region_books);

    for(i=0;i<sizeof(idx);i++)
      set_alarm(itof(i),0.0,&update_race(idx[i]));
}



void
create_room()
{
    set_short("Master room of the Krynn race guild");
    set_long("You are in the master room of the Krynn race guild.\n");
    update_books();
/* Milan 10.9.02 this is unnecessary due to fix above (minotaurs -> minotaur)
    update_race("minotaur");
    update_book("human", "minotaur");
*/
    add_exit("/d/Krynn/workroom","out");
}


mixed
query_additional_family_name(string race, string region)
{
    if (!familynames[race])
	return ({});
    if (!familynames[race][region])
	return ({});
    if (sizeof(familynames[race][region]) < 1)
	return ({});
    return familynames[race][region][0];
}

mixed
query_families(string race, string region)
{
    if (!familynames[race])
	return 0;
    if (!familynames[race][region])
	return 0;
    if (sizeof(familynames[race][region]) < 1)
	return 0;
    return familynames[race][region][1..] +
    query_additional_family_name(race, region);
}

mixed
query_regions(string race)
{
    return familynames[race];
}


/*   0: no restrictions,
 *   1: knights only,
 *   2: good aligned only (>-200)
 *   4: evil aligned only (<200)
 *   8:
 *  16:
 */
int
query_allowed(object who, string famname)
{
    int res = restriction[L(famname)];

    if (res & 1)
	if (who->query_knight_level() == 0)
	{
	    write("You must be a knight to take the name you selected.\n");
	    return 0;
	}
    if (res & 2)
	if (who->query_alignment() <= -200)
	{
	    write("You are too evil to take the name you selected.\n");
	    return 0;
	}
    if (res & 4)
	if (who->query_alignment() >= 200)
	{
	    write("You are too good to take the name you selected.\n");
	    return 0;
	}
    if (res & 8)
	if (0)
	    return 0;
	/* add further restrictions here */

    return 1;
}

/* this is the check to see if a name is allowed.
 * called from the joinroom.
 * returns:
 *  0: race not allowed to join guild.
 *  1: region not allowed. (no such region)
 *  2: family name not allowed. (no such family name)
 *  3: name is restricted. (not allowed to take name)
 * else returns array
 *  ({region,family name}) with the correct capitalization.
 */
mixed
check_name_ok(object who, string region, string famname)
{
    int i,j;
    string race = who->query_race();
    string *avnames, *first;

    if (!query_regions(race))
	return 0;

    if (!query_families(race,region))
	return 1;

    first = query_additional_family_name(race, region);

    avnames = query_families(race,region);
    for(i=0;i<sizeof(avnames);i++)
    {
	if (L(famname) == L(avnames[i]))
	    if (query_allowed(who,famname))
		return ({ region, avnames[i] });
	    else
		return 3;
    }
    for(i=0;i<sizeof(avnames);i++)
	for(j=0;j<sizeof(first);j++)
	{
	    if (L(famname) == L(avnames[i] + " " + first[j]))
		if (query_allowed(who,avnames[i]) && query_allowed(who,first[j]))
		{
		    /*if (avnames[i] != first[j])*/
		    if (member_array(avnames[i],first) == -1)
			return ({ region, avnames[i] + " " + first[j] });
		    else
			return 2;
		}
		else
		    return 3;
	}
    return 2;
}
