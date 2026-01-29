/*
 * /d/Kalad/common/guilds/khiraa/khiraa.h
 * Purpose    : Useful defs for the Khiraa guild
 * Located    : /d/Kalad/common/guilds/khiraa/
 * Created By : Sarr 6.Mar.96
 * Modified By: Fysix, Jan 1998
 */

#include "/d/Kalad/sys/paths.h"

//      Death Knights
#define DK_OCC_NAME     "DK of Khiraa"
#define DK_OCC_TYPE     "occupational"
#define DK_OCC_STYLE    "fighter"
#define DK_LAY_NAME     "DK of Khiraa"
#define DK_LAY_TYPE     "layman"
#define DK_LAY_STYLE    "cleric"

//      Lich Priesthood
#define LP_OCC_NAME     "LP of Khiraa"
#define LP_OCC_TYPE     "occupational"
#define LP_OCC_STYLE    "cleric"
#define LP_LAY_NAME     "LP of Khiraa"
#define LP_LAY_TYPE     "layman"
#define LP_LAY_STYLE    "fighter"

//      Dir aliases
#define DK_DIR          KHIRAA + "dk/"
#define LP_DIR          KHIRAA + "lp/"

//      Shadows and souls
#define DK_SOUL         (DK_DIR + "commands/dk_soul")
#define DK_OCC_SHADOW   (DK_DIR + "obj/dk_shadow")
#define DK_LAY_SHADOW   (DK_DIR + "obj/dk_lay_shadow")

#define LP_SOUL         (LP_DIR + "commands/lp_soul")
#define LP_OCC_SHADOW   (LP_DIR + "obj/lp_shadow")
#define LP_LAY_SHADOW   (LP_DIR + "obj/lp_lay_shadow")

//      Member checks
#define IS_DK(ob) (ob->query_guild_name_occ() == "DK of Khiraa")
#define IS_LP(ob) (ob->query_guild_name_occ() == "LP of Khiraa")
#define IS_GUILD_MASTER(ob) ( member_array(ob->query_real_name(),\
    ({"sarr", "fysix"}) ) != -1)

//      Servers
#define KHIRAA_SERVER (KHIRAA + "khiraa_server")


//      Taxes

#define DK_OCC_TAX 22
#define DK_LAY_TAX 11
#define LP_OCC_TAX 25
#define LP_LAY_TAX 10


//       Misc
#define SOULDESC(s) (TP->add_prop(LIVE_S_SOULEXTRA, (s)))
#define DK_AS_CORPSE   "_dk_as_corpse"
#define KHIRAA_JOIN_INITIATE  "_khiraa_join_initiate"
#define KHIRAA_JOIN_ADJS      "_khiraa_join_adjs"
#define KHIRAA_CIRCLE_PERMISSION "_khiraa_circle_permission"

#define KHIRAA_ADJ_LIST ({ "eyeless", "deathly", "glowing-eyed", \
                           "corpse-like", "ember-eyed", "zombie-like", \
                           "empty-eyed", "wraith-like", "vacant-eyed", \
                           "hunchbacked", "ghoulish", "rancid", \
                           "unholy", "ghastly", "foul", "decaying", \
                           "cruel", "blue-skinned", "demented", \
                           "pale-skinned", "deformed", "translucent", \
                           "white-skinned", "skeletal", "gloomy", \
                           "sullen", "ominous", "ashen", "grim", \
                           "ethereal","eerie","haggard","spectral", \
                           "ghostly","macabre","soul-less","gaunt", \
                           "horrible","cold" })

// Ceremony
#define CER_WASHED_IN_BLOOD  "_cer_washed_in_blood"

