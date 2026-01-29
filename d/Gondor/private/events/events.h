/*
 * /d/Gondor/events/events.h
 *
 * Definitions for events.
 *
 * Gwyneth September 27, 2000
 */

#define AUTHORIZED  ({ "Gwyneth", "Mercade", "Rohim", "Skippern", "Stern" })

#define EVENTLIST   ({"armour", "drink", "food", "npc", "object", "weapon"})

#define MASTERLIST   ({ "clear", "display", "distribute", "echo", "gecho", \
                       "group", "help", "tell", "gtell", "npc", "preset", \
                       "reward", "greward", "sgreward", "team", "where",  \
                       "won" })

#define EVENTDIR    "/d/Gondor/private/events/"
#define EVENTOBJ    EVENTDIR + "obj/"
#define EVENTREC   EVENTDIR + "recall/"
#define EVENTLOG    EVENTDIR + "logs/"
#define COMMENTLOG  EVENTLOG + "comments.log"
#define MASTERLOG   EVENTLOG + "mtool.log"
#define TOOLLOG     EVENTLOG + "tool.log"
#define REWARDLOG   EVENTLOG + "reward.log"
#define CREATELOG   EVENTLOG + "creations.log"
#define COMMENTER   EVENTOBJ + "event_command"

/* Stat levels */
#define BIG_STATS   ({ 150, 150, 150, 150, 150, 150 })
#define MED_STATS   ({ 80, 80, 80, 80, 80, 80 })
#define SMALL_STATS ({ 20, 20, 20, 20, 20, 20 })
#define DEF_STATS   ({ 100, 100, 100, 100, 100, 100 })

/* Skillsets */
#define FIGHTING ({ SS_2H_COMBAT, SS_UNARM_COMBAT, SS_BLIND_COMBAT,       \
                    SS_PARRY, SS_DEFENCE, SS_WEP_SWORD, SS_WEP_CLUB,      \
		    SS_WEP_KNIFE, SS_WEP_POLEARM, SS_WEP_AXE })
#define THIEF    ({ SS_OPEN_LOCK, SS_PICK_POCKET, SS_ACROBAT, SS_FR_TRAP, \
		    SS_SNEAK, SS_HIDE, SS_BACKSTAB })
#define MAGIC    ({ SS_SPELLCRAFT, SS_HERBALISM, SS_ALCHEMY,              \
		    SS_FORM_TRANSMUTATION, SS_FORM_ILLUSION,              \
		    SS_FORM_DIVINATION, SS_FORM_ENCHANTMENT,		  \
		    SS_FORM_CONJURATION, SS_FORM_ABJURATION,		  \
		    SS_ELEMENT_FIRE, SS_ELEMENT_AIR, SS_ELEMENT_EARTH,    \
		    SS_ELEMENT_WATER, SS_ELEMENT_LIFE, SS_ELEMENT_DEATH   \
		 })
#define GENERAL  ({ SS_LANGUAGE, SS_APPR_MON, SS_APPR_OBJ, SS_SWIM,	  \
		    SS_CLIMB, SS_ANI_HANDL, SS_LOC_SENSE, SS_TRACKING,    \
		    SS_HUNTING, SS_AWARENESS, SS_TRADING, SS_RIDING	  \
		 })

/* Message prompts */
#define ABORT       "Aborting command.\n"
#define CLEAR       "Enter value to clear (exp, extra, group, tell " +     \
                    "or echo)\nor hit return to clear them all: "
#define CLEARMAP    "Enter name of preset to clear or all: "
#define DEFAULT     "Invalid option.\n"
#define DISPLAY     "Enter value(s) to display (exp, extra, group, " +     \
                    "tell or echo): "
#define DISTRIBUTE  "Enter echo to send to each player who " +             \
                    "receives an item or type 'comment' to distribute " +  \
                    "a commenter: "
#define DISTRIB2    "Enter domain to distribute item to, group name, " +   \
                    "'groups' or 'all' followed by the pathname of the " +  \
                    "item (gondor /d/Gondor/private/events/obj/foo.c): "
#define COMMENTS    "You somehow sense that 'event' will allow you to " +  \
                    "give a response.\n"
#define ECHO        "Enter an individual to echo to or hit return when " + \
                    "done: "
#define ECHO2       "Enter string to echo or the name of a preset echo: "
#define GECHO       "Enter group name, 'groups' or 'all' to echo to " +    \
                    "or hit return when done: "
#define GROUP       "Enter the leader of the group, which will be " +      \
                    "the group's identifier: "
#define GROUP2      "Enter a group follower or hit return when done: "
#define TELL        "Enter an individual to send a tell to or hit " +      \
                    "return when done: "
#define TELL2       "Enter string to tell or the name of a preset tell: "
#define GTELL       "Enter group name, 'groups' or 'all' to tell to or " + \
                    "hit return when done: "
#define NPC         "Enter '[remove/place] living-name': "
#define NPC2        "Enter path to place npc: "
#define PRESET      "Enter value to preset (exp, extra, tell or echo): "
#define PRESET_ECHO "Enter name to associate with preset echo: "
#define PRESET_E2   "Enter echo message to preset: "
#define PRESET_TELL "Enter name to associate with preset tell: "
#define PRESET_T2   "Enter tell message to preset: "
#define PRESETEXP   "Enter experience to preset (combat general quest): "
#define PRESETEX    "Enter extra experience to preset (combat " +         \
                    "general quest): "
#define REWARD      "Enter individual to reward or hit return when done: "
#define EXP         "Enter experience to reward (combat general " +      \
                    "quest) or type exp or extra to reward that " +      \
                    "preset. Type 'silent' at the end if you wish the " + \
                    "reward to be given silently: "
#define GREWARD     "Enter group to reward or hit return when done: "
#define TEAM        "The following teams are around:\n"
#define WHERE       "The locations of the preset group members is as " +   \
                    "follows:\n"
#define WON         "Enter the group winner: "
#define WON2        "Enter 'tell <message>' or 'echo <message>' to " +     \
                    "send to all groups (preset tells/echos may be used): "

#define MESSAGES ([ "clear"      : CLEAR,        \
                    "default"    : DEFAULT,      \
                    "display"    : DISPLAY,      \
                    "distribute" : DISTRIBUTE,   \
                    "echo"       : ECHO,         \
                    "gecho"      : GECHO,        \
                    "group"      : GROUP,        \
                    "tell"       : TELL,         \
                    "gtell"      : GTELL,        \
                    "npc"        : NPC,          \
                    "preset"     : PRESET,       \
                    "reward"     : REWARD,       \
                    "greward"    : GREWARD,      \
                    "team"       : TEAM,         \
                    "where"      : WHERE,        \
                    "won"        : WON           \
                    ])

#define FUNCS    ([ "clear"      : "clear",      \
                    "default"    : "default",    \
                    "display"    : "display",    \
                    "distribute" : "distribute", \
                    "echo"       : "echo",       \
                    "gecho"      : "gecho",      \
                    "group"      : "group",      \
                    "tell"       : "tell",       \
                    "gtell"      : "gtell",      \
                    "npc"        : "npc",        \
                    "preset"     : "preset",     \
                    "reward"     : "reward",     \
                    "greward"    : "greward",    \
                    "team"       : "team",       \
                    "where"      : "where",      \
                    "won"        : "won"         \
                    ])
