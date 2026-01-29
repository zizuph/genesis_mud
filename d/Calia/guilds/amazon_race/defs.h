/*
 *    defs.h  
 *
 * Definitions file for the Amazon racial guild
 *
 * Baldacin@Genesis, Nov 2003   
 *
 *
 */
 
#pragma strict_types
#include "/d/Calia/domain.h"

/* Activate this define if we don't accept new members */
//#define NOT_ACCEPTING_NEW_MEMBERS

/* Basic information definitions */
#define GUILD_NAME   "Amazon racial guild"
#define STYLE        "race"
#define TAX          2
#define GUILDMASTERS ({"baldacin"})

/* Directory and File definitions */      
#define CONNECTING_ROOM "/d/Calia/argos/silent_forest/nforest05_02"
#define BASEDIR       "/d/Calia/guilds/amazon_race/"
#define DOC           ( BASEDIR +       "docs/" )
#define LOG           ( BASEDIR +       "logs/" )
#define OBJ           ( BASEDIR +    "objects/" )
#define NPC           ( BASEDIR +       "npcs/" )
#define LIB           ( BASEDIR +    "library/" )
#define ROOMS         ( BASEDIR +      "rooms/" )
#define ARM           (     OBJ +    "armours/" )
#define WEP           (     OBJ +    "weapons/" )

#define SERVER_SAVE   ( LOG     + "server_save" )
#define VOTE_SAVE     ( LOG     +   "vote_save" )
#define VOTING        ( LIB     +    "voting" )
#define SERVER        ( LIB     +    "server" )
#define SHADOW        ( LIB     +    "shadow" )
#define SOUL          ( LIB     +      "soul" )
#define TRAINING      ( ROOMS   +     "tree2" )
#define START_ROOM    ( ROOMS   +     "tree1" )

/* Miscellaneous definitions */
#define IS_MEMBER(x)       (x->query_guild_name_race() == GUILD_NAME)
#define DEBUG(x)           tell_room(SERVER, x)
#define IS_GUILDMASTER(ob) (member_array(ob->query_real_name(), \
                           GUILDMASTERS ) != -1)
#define LOGFILE(x,y)       write_file(LOG + x, extract(ctime(time()), \
                            4, 15) +" "+ y )
#define HIS(x)             x->query_possessive()
#define HE(x)              x->query_pronoun()
#define HIM(x)             x->query_objective()

#define VTIME       0
#define VDESC       1
#define VPRESENTER  2
#define VAPPLICANT  3

#define VOTE_EXPIRE 30

#define AMAZON_SUB "_amazon_race_subloc"

/* Guild title defines */
#define MAX_AGE  30
#define MAX_STAT 100
#define TITLES   ({ "Feeble",\
                    "Neophyte",\
                    "Flimsy",\
                    "Rookie",\
                    "Weak",\
                    "Drastic",\
                    "Dashing",\
                    "Robust",\
                    "Tough",\
                    "Great",\
                    "Strong",\
                    "Fearless",\
					"Eminent",\
                    "Courageous",\
					"Distinguished",\
                    "Dauntless",\
                    "Feared",\
					"Well-known",\
                    "Valiant",\
                    "High",\
					"Glorious",\
                    "Venerated",\
					"Remarkable",\
                    "Powerful",\
					"Striking",\
                    "Crushing",\
					"Famous",\
					"Celebrated",\
                    "Mighty",\
                    "Grand",})