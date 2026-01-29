#define GUILD_NAME           "Sheagh d'Eria"
#define GUILD_STYLE          "ranger"
#define GUILD_TYPE           "occupational"
#define GUILD_TAX            25

/* Reputation to remain. */
#define REMAIN_REPU_SKILL   40
/* Reputation to join. */
#define JOIN_REPU_SKILL     50
/* Define Guild Titles */
#define TITLE_SOLDIER        00
#define TITLE_WARRIOR        30
#define TITLE_VETERAN        60
#define TITLE_HERALD         90
#define TITLE_EMBODIMENT    120
/* Define Reputation Titles */
#define REPU_UNTESTED        00
#define REPU_POPULAR         30
#define REPU_FAMOUS          60
#define REPU_HEROIC          90
#define REPU_LEGENDARY      120

#define PATH                 "/d/Khalakhor/guilds/sheagh/"
#define LIB                  PATH + "lib/"
#define SPELL                PATH + "spell/"
#define WEP                  PATH + "weapon/"
#define ARM                  PATH + "armour/"
#define OBJ                  PATH + "object/"
#define DOC                  PATH + "document/"
#define SHADOW               (LIB + "sheagh_shadow")
#define SOUL                 (LIB + "sheagh_soul")
#define TOKEN                (OBJ + "sheagh_tattoo")
#define JOIN_SCROLL          (OBJ + "scroll")

#define BLADEMASTER_TATTOO_NAME "_khalakhor_sheagh_tattoo"
#define BLADEMASTER_DIRK_NAME   "_khalakhor_sheagh_dirk"

#define IS_SHEAGH(x)         (x->query_guild_name_occ() == GUILD_NAME)
// #define IS_SHEAGH_BIT        4, 0

#define OBJ_I_SHEAGH_ARM     "_obj_i_sheagh_arm"
#define OBJ_I_SHEAGH_GOBJ    "_obj_i_sheagh_gobj"

#define TP this_player()
#define TO this_object()
#define NF(x) notify_fail(x)

#undef STAT_CAP
