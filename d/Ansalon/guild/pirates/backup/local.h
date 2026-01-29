/*
 * File Name        : local.h
 * By               : Elmore.
 * Inspiration from : The Neidar Guild by Arman.
 *                    
 * Date             : Nov. 2000.
 *
 * Modified by Navarre June 20th 2006:
 * Tax recalculated to match current abilities and skills.
 *
 */ 



#define GUILD_NAME             "Pirate of the Bloodsea"
#define GUILD_STYLE            "fighter"
#define GUILD_TAX              10
#define I_CAN_BECOME_PIRATE    "_i_can_become_pirate"

#define GUILD_DIR              "/d/Ansalon/guild/pirates/"
#define GUILD_SHADOW           GUILD_DIR + "shadow/pirate_shadow"
#define GUILD_CMDSOUL          GUILD_DIR + "soul/pirate_soul"
#define GUILD_ROOM             GUILD_DIR + "room/"
#define GUILD_OBJ              GUILD_DIR + "obj/"
#define GUILD_EMBLEM           GUILD_OBJ + "sash2"
#define GUILD_NPC              GUILD_DIR + "npc/"
#define GUILD_LOG              GUILD_DIR + "log/"
#define GUILD_OFF_SPECIAL      GUILD_DIR + "soul/pbash"
#define PIRATE_BOARD           GUILD_LOG + "boards/normal/"
#define BAN_PRESSGANGER_FILE   GUILD_LOG + "banned_pressgangers.o"
#define GUILD_EMBLEM_ID        GUILD_OBJ + "sash"


#define I_AM_ALLOWED           "_i_have_king_permission"

/* The skill number for the guild's special skill.
 * Check with the liege of your domain to get your own skills.
 */
#define SS_SPECIAL_STAGGER 143030

#define GUILD_STARTLOC GUILD_ROOM + "pirate_start"

#define PADMIN   ("/d/Ansalon/guild/pirates/room/admin")
#define SAVE_PATH           GUILD_LOG

// The Ranks available
#define KING 3
#define FIRSTMATE 2
#define PRESSGANGER 1
#define REGULAR_MEMBER 0
#define PIRATE_KING_INCOGNITO "pirate_king_incognito"


