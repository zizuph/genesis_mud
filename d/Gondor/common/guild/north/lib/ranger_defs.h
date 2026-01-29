/* 
 *      /d/Gondor/common/guild/lib/ranger_defs.h 
 *
 *      Modification log:
 *       5-Mar-1997, Olorin:    Changes due to change in adv guild skills.
 *
 */
#ifndef RANGER_DEFS
#define RANGER_DEFS

/*
 * **************************************************
 */

#define NORTH_MASTER    "/d/Gondor/common/guild/north/member_master"
#define GUILD_TOKEN  "/d/Gondor/common/guild/north/obj/brooch"
#define GUILD_STYLE "ranger"
#define GUILD_TYPE "occupational"
#define GUILD_NAME "Rangers of the North"

#define RECRUIT_RANK    12
#define SKILLS ({ SS_WEP_SWORD, SS_WEP_POLEARM, SS_DEFENCE, SS_PARRY, \
		  SS_SNEAK, SS_HIDE, SS_AWARENESS, SS_FR_TRAP, \
		  SS_HERBALISM, SS_ALCHEMY, SS_SPELLCRAFT, \
		  SS_ELEMENT_LIFE, SS_FORM_CONJURATION, SS_FORM_ABJURATION, \
		  SS_TRACKING, SS_LOC_SENSE, SS_HUNTING, SS_ANI_HANDL, \
		  SS_HEARING, SS_BRAWLING })

#define PUPIL_SKILLS  ({ 50,  0, 35, 15, \
			 50, 50, 70,  0, \
			 35,  0, 30, 30, 10,  0, \
			 40,  0,  0,  0, \
			 50, 50 })
#define NORTH_SKILLS  ({ 75,  0, 55, 25, \
			 90, 90, 85,  0, \
			 0,  45, 0, 50, 40, 20, \
			 85, 50,  0,  0, \
			100, 100 })

#define RANGER_S_SUBLOC    "Ranger_s_SubLoc"


/* Skills with training limited by the guild stat SS_OCCUP */
#define SUBTERFUGE_SKILLS ({ \
			    SS_SNEAK, SS_HIDE, SS_HEARING, \
			    SS_FR_TRAP, SS_AWARENESS })
#define NATURE_SKILLS     ({ \
			    SS_HERBALISM, SS_ALCHEMY, SS_TRACKING, \
			    SS_HUNTING, SS_LOC_SENSE })
#define COMBAT_SKILLS     ({ SS_BRAWLING, SS_WEP_SWORD, SS_DEFENCE })
#define LEARN_FACTOR    4

#define RANGER_POST   "/d/Gondor/common/guild/north/post"
			 
#define RANGER_LOOKS   ({ "young and energetic", \
			  "fresh and spirited", \
			  "young but thoughtful", \
			  "slightly tattered", \
			  "fairly well-travelled", \
			  "dusty and windblown", \
			  "disheveled and care-worn", \
			  "hardened and wind-swept", \
			  "weather-beaten and grim-faced", \
			  "aged and storm-blown", \
			  "worn by years of travel", \
			  "grim and terrible, yet wise", \
		       })
#define TAXRATE   19
#define PUPIL_TAX  8
#define RANGER_MIN_EVIL_ALIGN      200
#define RANGER_ALIGN_WARN           100  /* warn at MIN + WARN */

#define RANGER_KILLS "/d/Gondor/log/rangerkills"
#define NPC_KILLS    "/d/Gondor/log/npckills"
#define NORTH_LOG    "/d/Gondor/log/rangers_n"
#define STATUS_LOG   "/d/Gondor/log/rangers"
#define APPLICANT_LOG "/d/Gondor/log/ranger_application"

#endif
