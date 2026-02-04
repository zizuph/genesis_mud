#ifndef MAGES_DEFS
#define MAGES_DEFS

/* Information */

#define GUILD_NAME         "Order of the Arcanum"
#define GUILD_TAX           20
#define GUILD_TYPE         "occupational"
#define GUILD_STYLE        "mage"
#define NUM_TITLES          5
#define MAX_SS_OCC        120

#define GUILD_DIR          "/d/Terel/guilds/mages/"
#define GUILD_CMDSOUL      GUILD_DIR + "soul"
#define GUILD_SHADOW       GUILD_DIR + "shadow"
#define MAGES_SPELLS       GUILD_DIR + "spells/"
#define MAGES_NPC          GUILD_DIR + "npc/"
#define MAGES_OBJ          GUILD_DIR + "obj/"
#define MAGES_WEP          GUILD_DIR + "weapon/"
#define MAGES_LIB          GUILD_DIR + "lib/"
#define MAGES_SPELL_TXT    MAGES_SPELLS + "help/"
#define MAGES_SPELLBOOK    MAGES_OBJ + "spellbook"
#define MAGES_STARTROOM    GUILD_DIR + "guild/start"

/* Useful macros */
#define MEMBER(xx)         ((xx)->query_guild_member(GUILD_NAME))
#define MAGES_LOG          MAGES_OBJ + "mages_log_object"


/* Props */

#define MAGES_ACCEPTED    "_mages_accepted"
#define MAGES_BLESS          "_mages_bless"
#define MAGES_SEAL            "_mages_seal"
#define MAGES_SUBLOC        "_mages_subloc"



/* Skills */

#define SPELL_FLAMEWAVE      1
#define SPELL_HEAL                2
#define SPELL_TELL                3


#ifndef  SS_ARCANUM_SPELL_LIST
#define SS_ARCANUM_SPELL_LIST 898989 
#endif

#endif
