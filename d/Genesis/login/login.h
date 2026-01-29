/*
 * /d/Genesis/login/login.h
 *    
 * Some constants relevant to the login procedure.
 */

/*
 * PATH
 * 
 * The path in which the login rooms reside
 */
#define PATH         "/d/Genesis/login/"
#ifndef TUTORIAL_DIR
#define TUTORIAL_DIR "/d/Sparkle/area/tutorial/"
#endif
#undef  WEBSITE_CMS  "/d/Web/cms/website"

/*
 * HELP
 *
 * The path which contains all the login help files
 */
#define HELP (PATH + "help/")

/*
 * ATTRIBS
 *
 * The path to the directory containing all the player attributes
 *
 */
#define ATTRIBS (PATH + "attributes/")

/*
 * Path macros to various rooms, if wanted.
 */
#define LOGIN_CREATION       (PATH + "creation")
#define LOGIN_DEATH          (PATH + "death_chamber")
#define LOGIN_MENU           (PATH + "creation_menu")
#define LOGIN_PRE            (TUTORIAL_DIR + "pre_creation_new/0")
#define LOGIN_TUTORIAL       (TUTORIAL_DIR + "lars_room")

/* 
 * Used by certain domain code (Calia), but not in the login
 * or character creation process.
 */
#define LOGIN_FEATURES       (PATH + "features")

/*  
 * LOGIN_FILE_NEW_PLAYER_INFO
 *
 * This is the names of the files that are written to new users logging in.
 */
#define LOGIN_FILE_NEW_PLAYER_INFO "/d/Genesis/doc/login/NEW_PLAYER_INFO"

/*
 * RACEMAP
 *
 * This mapping holds the names of the allowed player races in the game and
 * which player file to use for new characters of a given race.
 */
#define RACEMAP ([ \
		"human"  : "/d/Genesis/race/human_std",   \
		"elf"    : "/d/Genesis/race/elf_std",     \
		"dwarf"  : "/d/Genesis/race/dwarf_std",   \
		"hobbit" : "/d/Genesis/race/hobbit_std",  \
		"gnome"  : "/d/Genesis/race/gnome_std",   \
		"goblin" : "/d/Genesis/race/goblin_std",  \
		])
/*
 * RACEATTR
 *
 * This mapping holds the standard attributes for each race. The attributes
 * are: 
 *      standard height         (cm)
 *      standard weight         (kg)
 *      standard opinion        (0-100)
 *      standard appereance     (0-100)
 *      standard volume         (dm^3)
 *      standard fatness        (g/cm)
 */
#define RACEATTR ([ \
		"human"  : ({180, 70, 50, 50, 70, 389 }), \
		"elf"    : ({200, 50, 40, 40, 60, 250 }), \
		"dwarf"  : ({130, 70, 60, 60, 60, 538 }), \
		"hobbit" : ({110, 40, 30, 30, 40, 364 }), \
		"gnome"  : ({ 90, 50, 20, 20, 50, 555 }), \
		"goblin" : ({100, 45, 90, 90, 45, 450 }), \
		])

/*
 * RACESTATMOD
 *
 * This mapping holds the standard modifiers of each stat, i.e. a dwarf
 * should have it easier to raise con than other races, but get a harder
 * time raising its int.
 *
 * Mapping is: race:  str, dex, con, int, wis, dis, race, occ, lay, craft
 */


#define RACESTATMOD ([ \
		"human"  : ({ 11, 11, 11, 11, 11, 11, 10, 10, 10, 10 }), \
		"elf"    : ({ 11, 11, 11, 11, 11, 11, 10, 10, 10, 10 }),    \
                "dwarf"  : ({ 11, 11, 11, 11, 11, 11, 10, 10, 10, 10 }),    \
                "hobbit" : ({ 11, 11, 11, 11, 11, 11, 10, 10, 10, 10 }),    \
                "gnome"  : ({ 11, 11, 11, 11, 11, 11, 10, 10, 10, 10 }),    \
                "goblin" : ({ 11, 11, 11, 11, 11, 11, 10, 10, 10, 10 }),   \
		])


/*
 * when m_indexex work on constants: m_indexes(RACEMAP)
 */
#define RACES ({ "human", "elf", "dwarf", "hobbit", "gnome", "goblin"})

#define RACES_SHORT ([ \
                      "human" : "hum", \
		      "elf"   : "elf", \
		      "dwarf" : "dwf", \
		      "hobbit": "hob", \
		      "gnome" : "gno", \
		      "goblin": "gob", \
		    ])

/*
 * RACESTART
 *
 * This mapping holds the files of the starting locations for each race.
#define RACESTART ([ \
		    "human"  : "/d/Genesis/start/human/town/church",   \
		    "elf"    : "/d/Genesis/start/elf/room/begin",      \
		    "dwarf"  : "/d/Genesis/start/dwarf/lvl1/temple",   \
		    "hobbit" : "/d/Genesis/start/hobbit/v/church",     \
		    "gnome"  : "/d/Genesis/start/human/town/church",   \
		    "goblin" : "/d/Genesis/start/goblin/caverns/quarters", \
	          ])
 *
 * These old values are being replaced for now. To support new players
 * properly we need to create a solid and consistent single experience that
 * welcomes new players to the game and gets them started properly. This
 * is what Sparkle is being designed to do. The various old racial start
 * locations are not set up to do this at all. (Gorboth, December 2010)
 */
#define RACESTART ([ \
                    "human"  : "/d/Genesis/start/human/town/church",   \
                    "elf"    : "/d/Genesis/start/human/town/church",   \
                    "dwarf"  : "/d/Genesis/start/human/town/church",   \
                    "hobbit" : "/d/Genesis/start/human/town/church",   \
                    "gnome"  : "/d/Genesis/start/human/town/church",   \
                    "goblin" : "/d/Genesis/start/human/town/church",   \
                  ])
/*
 * RACEPOST
 *
 * This mapping holds the files of the post office locations for each race.
 */
#define RACEPOST ([ \
		    "human"  : "/d/Genesis/start/human/town/post",    \
		    "elf"    : "/d/Genesis/start/elf/room/vill_post", \
		    "dwarf"  : "/d/Genesis/start/human/town/post",    \
		    "hobbit" : "/d/Genesis/start/hobbit/v/p_office",  \
		    "gnome"  : "/d/Genesis/start/human/town/post",    \
		    "goblin" : "/d/Genesis/start/human/town/post",    \
	          ])

#define TUTORIAL_POST  (TUTORIAL_DIR + "town/post_office")

/*
 * IS_IN_TUTORIAL - returns true if the player is located somewhere in the
 *    tutorial area.
 */
#define IS_IN_TUTORIAL(pl) wildmatch(TUTORIAL_DIR + "*", file_name(environment(pl)))

/*
 * RACESTAT
 *
 * This mapping holds the stats that each race has on start
 */


#define RACESTAT ([            /* str, dex, con, int, wis, dis */      \
		    "human"  : ({   9,  9,   9,   9,   9,   9 }),      \
		    "elf"    : ({   6,  6,   9,  11,  11,  11 }),      \
		    "dwarf"  : ({  14,  4,  11,   7,   9,   9 }),      \
		    "hobbit" : ({   9,  9,  11,   6,   8,  11 }),      \
		    "gnome"  : ({   4, 17,   8,  11,   7,   7 }),      \
		    "goblin" : ({   7, 14,   8,  11,  13,   5 }),      \
	          ])


/*
 * RACEMISCCMD
 *
 * This mapping holds the files of the souls that should be used as
 * misc command soul for each race
 */
#define RACEMISCCMD ([ \
		    "human"  : "/d/Genesis/cmd/misc_cmd_human",  \
		    "elf"    : "/d/Genesis/cmd/misc_cmd_elf",    \
		    "dwarf"  : "/d/Genesis/cmd/misc_cmd_dwarf",  \
		    "hobbit" : "/d/Genesis/cmd/misc_cmd_hobbit", \
		    "gnome"  : "/d/Genesis/cmd/misc_cmd_gnome",  \
		    "goblin" : "/d/Genesis/cmd/misc_cmd_goblin", \
	          ])

/*
 * RACESOULCMD
 *
 * This mapping holds the files of the souls that should be used as
 * misc command soul for each race
 */
#define RACESOULCMD ([ \
		    "human"  : "/d/Genesis/cmd/soul_cmd_human",  \
		    "elf"    : "/d/Genesis/cmd/soul_cmd_elf",    \
		    "dwarf"  : "/d/Genesis/cmd/soul_cmd_dwarf",  \
		    "hobbit" : "/d/Genesis/cmd/soul_cmd_hobbit", \
		    "gnome"  : "/d/Genesis/cmd/soul_cmd_gnome",  \
		    "goblin"  : "/d/Genesis/cmd/soul_cmd_goblin",  \
	          ])
/*
 * RACESOUND
 *
 * What sound do subindex-race hear when mainindex race speaks
 */
#define RACESOUND2 ([						\
		    "human" : ([ 				\
				"human" : "says",		\
				"elf" 	: "sings",		\
				"dwarf" : "thunders",		\
                                "gnome" : "blurts",             \
				"hobbit": "chatters",		\
				"goblin": "mumbles",		\
				]),				\
		    "elf" : ([					\
				"human" : "yells",		\
				"elf" 	: "says",		\
				"dwarf" : "rumbles",		\
				"gnome"	: "murmurs",		\
				"hobbit": "chirps",		\
				"goblin": "grates",		\
				]),				\
		    "dwarf" : ([				\
				"human" : "whispers",		\
				"elf" 	: "whines",		\
				"dwarf" : "says",		\
				"gnome"	: "mimes",		\
				"hobbit": "squeaks",		\
				"goblin": "murmurs",		\
				]),				\
		    "gnome" : ([				\
				"human" : "yells",		\
				"elf" 	: "howls",		\
				"dwarf" : "thunders",		\
				"gnome"	: "says",		\
				"hobbit": "jabbers",		\
                                "goblin": "squeals",            \
				]),				\
		    "hobbit" : ([				\
				"human" : "bellows",		\
				"elf" 	: "sings",		\
				"dwarf" : "roars",		\
				"gnome"	: "growls",		\
				"hobbit": "says",		\
				"goblin": "rasps",		\
				 ]),				\
		    "goblin" : ([				\
				"human" : "howls",		\
				"elf" 	: "chirps",		\
				"dwarf" : "booms",		\
				"gnome"	: "says",		\
				"hobbit": "howls",		\
				"goblin": "says",		\
				 ]),				\
		    ])

#define RACESOUND ([						\
		    "human" : ([ 				\
				"human" : "says",		\
				"elf" 	: "yells",		\
				"dwarf" : "whispers",		\
				"gnome"	: "yells",		\
				"hobbit": "bellows",		\
				"goblin": "howls",		\
				]),				\
		    "elf" : ([					\
				"human" : "sings",		\
				"elf" 	: "says",		\
				"dwarf" : "whines",		\
				"gnome"	: "howls",		\
				"hobbit": "sings",		\
				"goblin": "chirps",		\
				]),				\
		    "dwarf" : ([				\
				"human" : "thunders",		\
				"elf" 	: "rumbles",		\
				"dwarf" : "says",		\
				"gnome"	: "thunders",		\
				"hobbit": "roars",		\
				"goblin": "booms",		\
				]),				\
		    "gnome" : ([				\
                                "human" : "blurts",             \
				"elf" 	: "murmurs",		\
				"dwarf" : "mimes",		\
				"gnome"	: "says",		\
				"hobbit": "growls",		\
                                "goblin": "squeals",            \
				]),				\
		    "hobbit" : ([				\
				"human" : "chatters",		\
				"elf" 	: "chirps",		\
				"dwarf" : "squeaks",		\
				"gnome"	: "jabbers",		\
				"hobbit": "says",		\
				"goblin": "howls",		\
				 ]),				\
		    "goblin" : ([				\
				"human" : "mumbles",		\
				"elf" 	: "grates",		\
				"dwarf" : "murmurs",		\
				"gnome"	: "says",		\
				"hobbit": "rasps",		\
				"goblin": "says",		\
				 ]),				\
		    ])

#define LINKDEATH_MESSAGE ([ \
       "human"  : " passes into limbo.\n",                  \
       "hobbit" : " enters the world of dreams.\n",         \
       "elf"    : " travels to the land of bliss.\n",       \
       "dwarf"  : " returns to the bowels of the earth.\n", \
       "gnome"  : " is lost in the shadows.\n",             \
       "goblin" : " is cast into the void.\n" ])

#define REVIVE_MESSAGE ([ \
       "human"  : " returns from limbo.",                   \
       "elf"    : " returns from the land of bliss.",       \
       "hobbit" : " awakens from the world of dreams.",     \
       "dwarf"  : " ascends from the depths of the earth.", \
       "gnome"  : " finds the way back from the shadows.",  \
       "goblin" : " returns from the void." ])
 
/*
 * HEIGHTDESC
 */
#define HEIGHTDESC ({"extremely short", "very short", "short", \
    "of normal length", "tall", "very tall", "extremely tall" })

/*
 * WIDTHDESC
 */
#define WIDTHDESC ({"very skinny", "skinny", "lean", "of normal width", \
    "plump", "fat", "very fat" })

/*
 * SPREAD_PROC
 */
#define SPREAD_PROC ({ 70, 80, 90, 100, 110, 120, 130 })

/*
 * LOGIN_NO_NEW - Log file for failed creation attempts.
 */
#define LOGIN_NO_NEW "/d/Genesis/login/no_new_players"

/*
 * This is the current state of this ghost (uses set_ghost() / query_ghost())
 *
 * GP_BODY   - Set when the player needs a new body
 */
#define GP_BODY		  1
#define GP_MANGLE	  2       /* OBSOLETE */
#define GP_FEATURES	  4       /* OBSOLETE */
#define GP_SKILLS         8       /* OBSOLETE */
#define GP_DEAD          32
#define GP_PRE           64
#define GP_TUTORIAL     128
#define GP_NOSKILL_LOSS 256

#define GP_NEW          (GP_BODY | GP_TUTORIAL)

/* No definitions beyond this line. */
