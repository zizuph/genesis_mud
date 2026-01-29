/* /d/Kalad/common/guilds/red_fang/default.h */
/* This holds some macros fo ruse with the red fang guild */
/* Sarr sometime in 96?  */
/* Modified: Sarr 17.Apr.97 -- Revision */

#define GUILD_NAME "Red Fang Guild"
#define GUILD_TYPE "race"
#define GUILD_STYLE "race"

#define GUILDMASTERS ({ "damaris" })
#define FANG_DIR(xxx) "/d/Kalad/common/guilds/red_fang/xxx"
#define AK_DEBUG(x)   find_player("arman")->catch_msg("[RF] " + x + "\n")

#define MEMBERS     FANG_DIR(obj/master)
#define FANG_SHADOW "/d/Kalad/common/guilds/red_fang/obj/fang_shadow"
#define FANG_SOUL "/d/Kalad/common/guilds/red_fang/commands/fang_soul"

#define IS_MEMBER(ob) (ob->query_guild_name_race() == "Red Fang Guild")
#define IS_GUILD_MASTER(ob)  (member_array(ob->query_real_name(), GUILDMASTERS) > -1)

#define WOLF_HEALTH         "_redfang_wolf_health_value"
#define WOLF_FATIGUE        "_redfang_wolf_fatigue_value"
#define WOLF_DISMISS_TIME   "_redfang_wolf_dismiss_time"

#define TAX 2
#define SOULDESC(s) (TP->add_prop(LIVE_S_SOULEXTRA, (s)))

/* The mother of all adjective lists for wolves */

#define MASTER_WOLF_ADJ_LIST ({"ferocious","furry","deadly","hairy", \
 "fearsome","foul-smelling","lethal","howling","drooling","vicious", \
 "blood-lusting","wild","snarling","menacing","fierce","massive", \
 "cruel","red-eyed","savage","black-eyed","grey-maned","blue-eyed", \
 "black-maned","brown-eyed","white-maned","silver-eyed","red-maned", \
 "male","female","brown-maned","sharp-fanged","hungry","human-eating", \
 "silver-maned","pale","gaunt","only" })
