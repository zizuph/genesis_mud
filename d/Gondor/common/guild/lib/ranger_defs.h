/* 
 *      /d/Gondor/common/guild/lib/ranger_defs.h 
 *
 *      Modification log:
 *       5-Mar-1997, Olorin:    Changes due to change in adv guild skills.
 *      27-Aug-2000, Stern:     Added some ranger looks.
 *
 */
#ifndef RANGER_DEFS
#define RANGER_DEFS

#define NEW_RANGER_SHADOW

#define RANGER_SHORT_GUILDNAME "ranger"

/*
 * **************************************************
 */
#define SKILLS ({ SS_WEP_SWORD, SS_WEP_POLEARM, SS_DEFENCE, SS_PARRY, \
		  SS_SNEAK, SS_HIDE, SS_AWARENESS, SS_FR_TRAP, \
		  SS_HERBALISM, SS_ALCHEMY, SS_SPELLCRAFT, \
		  SS_ELEMENT_LIFE, SS_FORM_CONJURATION, SS_FORM_ABJURATION, \
		  SS_TRACKING, SS_LOC_SENSE, SS_HUNTING, SS_ANI_HANDL, \
		  SS_HEARING, SS_BRAWLING })

#define PUPIL_SKILLS  ({ 50, 20, 35, 15, \
			 50, 50, 70, 15, \
			 35, 20, 30, 30, 15, 15, \
			 40, 20, 20, 20, \
			 50, 50 })
#define GONDOR_SKILLS ({ 75,  0, 55, 25, \
			 70, 70, 80,  0, \
			 70,  0, 65, 50, 50, 30, \
			 60,  0,  0,  0, \
			100, 100 })
#define ITHIL_SKILLS  ({ 80, 70, 70, 50, \
			 70, 70, 80,  0, \
                    45,  0, 40, 40, 20, 15, \
			 65,  0,  0,  0, \
			100, 100 })

#define COMPANIES ({ "the Ranger pupils", "Gondor", "Ithilien"})
#define RANGER_S_SUBLOC    "Ranger_s_SubLoc"

#define COMPANY_SKILLS ({ PUPIL_SKILLS, GONDOR_SKILLS, ITHIL_SKILLS })

/* Skills with training limited by the guild stat SS_OCCUP */
#define SUBTERFUGE_SKILLS ({ \
			    SS_SNEAK, SS_HIDE, SS_HEARING, \
			    SS_FR_TRAP, SS_AWARENESS })
#define NATURE_SKILLS     ({ \
			    SS_HERBALISM, SS_ALCHEMY, SS_TRACKING, \
			    SS_HUNTING, SS_LOC_SENSE })
#define COMBAT_SKILLS     ({ SS_BRAWLING, SS_WEP_SWORD, SS_DEFENCE })
#define LEARN_FACTOR    3

#define RECRUITHALL     "/d/Gondor/common/guild/recruithall"
#define DIR             "/d/Gondor/common/guild/"
#define GUILD           "/d/Gondor/common/guild/recruithall"
#define COUNCIL         "/d/Gondor/common/guild/council"
#define SPONSOR         "/d/Gondor/common/guild/sponsors"
#define COMPANY_POST ({ "/d/Gondor/common/guild/gondor/post", \
			"/d/Gondor/common/guild/gondor/post", \
			"/d/Gondor/common/guild/ithilien/post" })
#define COMPANY_TRAIN  ({ "/d/Gondor/common/guild/gondor/gondor_train", \
			  "/d/Gondor/common/guild/gondor/gondor_train", \
			  "/d/Gondor/common/guild/ithilien/ithilien_train" })
#define COMPANY_TITLE ({ "the Ranger pupils",     \
			 "Gondor",                \
			 "Ithilien" })
			 
#define RANGER_LOOKS   ({ "young and energetic", \
			  "fresh and spirited", \
			  "young but thoughtful", \
			  "slightly tattered", \
			  "fairly well-travelled", \
			  "dusty and windblown", \
			  "disheveled and care-worn", \
			  "hardened and wind-swept", \
			  "weather-beaten and grim-faced", \
                          "weary and stone-faced", \
                          "wary and scarred", \
			  "aged and storm-blown", \
			  "worn by years of travel", \
			  "grim and terrible, yet wise", \
		       })
#define STD_TITLE  ({    " of ",                  \
			 " of the Rangers of ",   \
			 " of the Rangers of " })

#define MASTER_RANK  80
#define SPECIALTY_RANK 60
#define COMP_REQUIREMENT 40
#define PUP_RANK_REQUIREMENT 40
/* SS_MASTER_TASK is defined in /d/Gondor/defs.h */
#define HISTORIAN  9
#define INSTRUCTOR 12
#define RECRUITER 14
#define SCHOLAR   15

#define MAX_PUPILS      5

#define MALE_TITLE ({  \
			 "Apprentice Strider",    \
			 "Strider",               \
			 "Expert Strider",        \
			 "Apprentice Scout",      \
			 "Scout",                 \
			 "Expert Scout",          \
			 "Apprentice Courser",    \
			 "Courser",               \
			 "Expert Courser",        \
			 "Apprentice Tracker",    \
			 "Tracker",               \
			 "Expert Tracker",        \
			 "Apprentice Guide",      \
			 "Guide",                 \
			 "Expert Guide",          \
			 "Apprentice Pathfinder", \
			 "Pathfinder",            \
			 "Expert Pathfinder",     \
			 "Veteran" })

#define RANGER_TITLE ({ \
			 "Messenger",                \
			 "Strider",               \
			 "Scout",                 \
			 "Courser",               \
			 "Tracker",               \
			 "Guide",                 \
			 "Pathfinder",            \
			 "Veteran",               \
		      })
#define FEMALE_TITLE ({ \
			 "Apprentice Strider",    \
			 "Strider",               \
			 "Expert Strider",      \
			 "Apprentice Scout",      \
			 "Scout",                 \
			 "Expert Scout",        \
			 "Apprentice Courser",    \
			 "Courser",               \
			 "Expert Courser",      \
			 "Apprentice Tracker",    \
			 "Tracker",               \
			 "Expert Tracker",      \
			 "Apprentice Guide",      \
			 "Guide",                 \
			 "Expert Guide",        \
			 "Apprentice Pathfinder", \
			 "Pathfinder",            \
			 "Expert Pathfinder",   \
			 "Veteran" })

#define TAXRATE   18
#define PUPIL_TAX  8
#define G_CPT      1
#define I_CPT      2
#define G_LT       3
#define I_LT       4

#define RANGER_MIN_EVIL_ALIGN      100
#define RANGER_ALIGN_WARN           50  /* warn at MIN + WARN */

#define RANGER_KILLS "/d/Gondor/log/rangerkills"
#define NPC_KILLS    "/d/Gondor/log/npckills"
#define STATUS_LOG   "/d/Gondor/log/rangers"
#define APPLICANT_LOG "/d/Gondor/log/ranger_application"

#endif
