#define GUILD_DIR         "/d/Terel/mecien/wicked/"
#define GUILD_HELP_DIR     GUILD_DIR + "help/"
#define GUILD_SHADOW       GUILD_DIR + "wicked_sh"
#define GUILD_NAME        "The Wicked"
#define GUILD_STYLE       "mage"
#define GUILD_TYPE        "layman"
#define GUILD_TAX         13
#define GUILD_ALIGN       -750
#define GUILD_SOUL        GUILD_DIR + "wicked_soul"
#define SPELL_DIR         GUILD_DIR + "spells/"
                           
#define TP                this_player()
#define TO                this_object()
#define NF(xx)            notify_fail(xx)
#define ENV               environment

#define T_WIZ(xx)      ((xx)->query_wiz_level() &&\
			"/secure/master"->query_wiz_dom(xx)=="Terel")

#define MEMBER(xx)     ((xx)->query_guild_member(GUILD_NAME))
