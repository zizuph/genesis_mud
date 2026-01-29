
//
// File: /d/Shire/claws/claw_defs.h
// This file contains the titles for the Black Claw guild.
// Titles are based upon which rank you get in the guild.
// The Master Orc will get the title 'Captain of the Black Claw clan'
// Warriors will get different titles depending upon level.
// Scout will get different titles depending upon level.
// Slaves will be simply slaves.
//
// /Odin, 7 October 1996
// Revision history:
//
//
#include "/d/Shire/skills.h"
#include "/d/Shire/common/defs.h"

#define GUILD_STYLE "fighter"
#define GUILD_NAME "Black Claw Clan"
#define GUILD_TAX 20
#define SHADOW "/d/Shire/claws/claws_shadow"
#define SOUL   "/d/Shire/claws/claws_soul"
#define THRONE "/d/Shire/claws/obj/throne"
#define RANDOM_ROOMS ({"/d/Shire/claws/rooms/join", "/d/Shire/claws/rooms/meeting",\
    "/d/Shire/claws/rooms/training", "/d/Shire/claws/rooms/throne" })
#define SKILLS ({SS_WEP_CLUB, \
           SS_DEFENSE, SS_PARRY, SS_SNEAK, \
		SS_HIDE, SS_AWARENESS, SS_UNARM_COMBAT,\
		 SS_CLIMB })

#define SLAVE_SKILLS ({ 40, 30, 40, \
                        15, 0, 0, \
			0, 20, 10,\
                         20 })
#define SCOUT_SKILLS ({ 70, 50, 60, \
                        40, 40, 60, \
			60, 60, 20,\
	                    60 })
#define WARRIOR_SKILLS ({ 70, 80,  60,\
			       80, 60, 60,\
                          60, 50, 20, \
	                        10, 50 })

#define RANKS ({"slave", "scout", "warrior", "captain"})
#define RANK_SKILLS ({SLAVE_SKILLS, SCOUT_SKILLS, WARRIOR_SKILLS, WARRIOR_SKILLS })

/*
 * These are the different titles the scouts will get.
 * Scouts have lesser powers, skills then warriors, but
 * are better 'scouts' then warriors, meaning they will
 * receive good sneak and hide.
 */
#define SCOUT_TITLES ({       \
	"Fresh Pathfinder",       \
	"Trainee Pathfinder",     \
	"Pathfinder",             \
	"Apprentice Pathfinder",  \
	"Learned Pathfinder",     \
	"Experienced Pathfinder", \
	"Expert Pathfinder",      \
	"Veteran Pathfinder",     \
	"Fumbling Scout",         \
	"Apprentice Scout",       \
	"Learned Scout",          \
	"Experienced Scout",      \
	"Expert Scout",           \
	"Veteran Scout",          \
	"Master Scout" })

#define NUM_SCOUT_TITLES 15

/*
 * These are the titles the slaves will get.
 */
#define SLAVE_TITLES ({ \
	"Untrusted Slave", \
	"Slave", \
	"Trusted Slave" })

#define NUM_SLAVE_TITLES 3
/*
 * These are the titles the warriors will receive.
 * There are a max of 25 warriors, hand picked by
 * the master orc, the captain of the black claw clan.
 */
#define WARRIOR_TITLES ({ \
	"Fresh Fighter", \
	"Insecure Fighter", \
	"Trainee Fighter", \
	"Proud Fighter", \
	"Devout Fighter", \
	"Experienced Fighter", \
	"Cruel Fighter", \
	"Bloody Fighter", \
	"Vicious Fighter", \
	"Dangerous Fighter", \
	"Bestial Fighter", \
	"Feared Fighter", \
	"Proud Warrior", \
	"Experienced Warrior", \
	"Bloody Warrior", \
	"Dangerous Warrior", \
	"Cruel Warrior", \
	"Feared Warrior", \
	"Mythical Warrior", \
	"Legendary Warrior" })

#define NUM_WARRIOR_TITLES 20

#define MAX_SS_OCCUP 100

/*
 * This is the title the one chief orc will get.
 * When he dies he will loose it, and become a warrior.
 */
#define MASTER_TITLE "Captain"

/*
 * Here follow a list over the different skill used to define
 * what membership the orcs have, if they are scouts/warriors/slaves
 * or a master.
 */
#define SLAVE   1
#define SCOUT   2
#define WARRIOR 3
#define CAPTAIN 4

#define IS_MEMBER(x)  ((x)->query_guild_name_occ() == GUILD_NAME)
