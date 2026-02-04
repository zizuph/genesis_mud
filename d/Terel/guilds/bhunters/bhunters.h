/*
 defs for bounty hunters guild
 by Udana 05/06
 */
#ifndef _BH_DEFS
#define _BH_DEFS

#include "/d/Terel/include/Terel.h"

/* info */
#define BHTAX (2)
#define BHSTYLE "ranger"
#define BHNAME "Bounty Hunters"

/* dirs */
#define BHDIR GUILDS_DIR + "bhunters/"
#define BHHELP BHDIR + "help/"
#define BHROOM BHDIR + "room/"
#define BHTRAPS BHDIR + "traps/"
#define BHOBJ BHDIR + "obj/"
#define BHNPC BHDIR + "npc/"
#define TRAP_COMPONENTS  BHTRAPS + "components/"

/* guild stuff */
#define BHSHADOW BHDIR + "layman_shadow"
#define BHSOUL BHDIR + "soul"
#define BHTITLES1 ({"", "Paid Thug of Last", "Bounty Hunter of Last", \
	"Hitman of Last", "Experienced Bounty Hunter of Last", \
	"Paid Assasin of Last", "Supreme Hunter of Men and Bests"})
#define BHTITLES2 ({"", "Paid Thug of Last", "Bounty Huntress of Last", \
	"Head Huntress of Last", "Experienced Bounty Huntress of Last", \
	"Paid Assasin of Last", "Supreme Huntress of Men and Bests"})
	
#define TRAP_FILES ([ "foothold" : BHTRAPS + "snare_trap", \
				"pitfall" : BHTRAPS + "pitfall_trap", \
				"pepper-spray" : BHTRAPS + "pepper_trap", \
				"paint" : BHTRAPS + "paint_trap", \
				"shock" : BHTRAPS + "shock_trap", \
				"dartgun" : BHTRAPS + "poison_trap"])

/* skills */
#define BHRANK 130060
#define SS_SET_TRAP 130061

/* traps : test*/
#define TRAP_SHADOW BHTRAPS + "trap_shadow"

/* bounty hunters office */
#define OFFICE (LAST_DIR + "bounty_office")

#define BASE_PAYMENT 15

/* stored member list with ranks and nr of coins */
#define BH_MEMBERS BHDIR + "members"

/* others */
#ifndef E
#define E(x) environment(x)
#endif

#define SEND(x) find_player("udana")->catch_msg(x + "\n")

#endif 