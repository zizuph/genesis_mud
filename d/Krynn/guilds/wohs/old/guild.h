#ifndef _WOHS_DEFS
#define _WOHS_DEFS

/*
 * Various Guild Defines
 */
#define GUILDMASTERS            ({ "cotillion" })
#define GUILD_NAME              "Wizards of High Sorcery"
#define GUILD_STYLE             "magic"
#define SPELL_BOOK              "_wohs_spell_book"
#define ROBE_SUBLOC             "_subloc_wohs_robe"
#define WOHS_XP_SKILL          101010

/*
 * Paths
 */ 
#define PATH                    ("/d/Krynn/guilds/wohs/")
#define LOG                     (PATH + "log/")
#define ROOMS                   (PATH + "rooms/")
#define NPC                     (PATH + "npc/")
#define OBJ                     (PATH + "obj/")
#define SPELLS                  (PATH + "spells/")
#define SPELL_OBJ               (SPELLS + "obj/")
#define TOBJ                    (ROOMS + "obj/")


/* 
 * Files 
 */
#define ADMIN                   (PATH + "admin")
#define SPELL_STD               (SPELLS + "spell_std")
#define TOWERROOM               (ROOMS + "tower_base")

/* 
 * Sub Orders 
 */
#define INITIATE    "Initiate" /* Those without Color */
#define RED         "Red"
#define BLACK       "Black"
#define WHITE       "White"

/*
 * Useful Macros
 */
#define MEMBER(x)   (ADMIN->query_member(x))
#define ORDER(x)    (ADMIN->query_member_type(x))
#define CONCLAVE(x) (ADMIN->query_conclave_member(x))

/* 
 * Title Defines
 */
#define LEVEL_COUNT 10

/* 
 * Old Macros
 */
#define AI              add_item
#define ACI             add_cmd_item


#endif /* _WOHS_DEFS */
