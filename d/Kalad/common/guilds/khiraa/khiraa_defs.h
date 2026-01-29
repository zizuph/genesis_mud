/*
 * /d/Kalad/common/guilds/khiraa/khiraa_defs.h
 * Purpose    : Useful defs for the Khiraa guild
 * Located    : /d/Kalad/common/guilds/khiraa/
 * Created By : Sarr 6.Mar.96
 * Modified By: 
 */


/*      Death Knights                   */
#define DK_OCC_NAME "DK of Khiraa"
#define DK_OCC_TYPE "occupational"
#define DK_OCC_STYLE "fighter"
#define DK_LAY_NAME "DK of Khiraa"
#define DK_LAY_TYPE "layman"
#define DK_LAY_STYLE "cleric"

/*      Lich Priesthood                 */
#define LP_OCC_NAME "LP of Khiraa"
#define LP_OCC_TYPE "occupational"
#define LP_OCC_STYLE "cleric"
#define LP_LAY_NAME "LP of Khiraa"
#define LP_LAY_TYPE "layman"
#define LP_LAY_STYLE "fighter"

/*      Dir aliases                     */
#define KHIRAA_DIR(x) "/d/Kalad/common/guilds/khiraa/x"
#define DK_DIR(x) "/d/Kalad/common/guilds/khiraa/dk/x"
#define LP_DIR(x) "/d/Kalad/common/guilds/khiraa/lp/x"

/*      Shadows and souls               */
#define DK_SOUL "/d/Kalad/common/guilds/khiraa/dk/commands/dk_soul"
#define DK_OCC_SHADOW "/d/Kalad/common/guilds/khiraa/dk/obj/dk_shadow"
#define DK_LAY_SHADOW "/d/Kalad/common/guilds/khiraa/dk/obj/dk_lay_shadow"

#define LP_SOUL "/d/Kalad/common/guilds/khiraa/lp/commands/lp_soul"
#define LP_OCC_SHADOW "/d/Kalad/common/guilds/khiraa/lp/obj/lp_shadow"
#define LP_LAY_SHADOW "/d/Kalad/common/guilds/khiraa/lp/obj/lp_lay_shadow"

/*      Member checks                   */
#define IS_DK(ob) (ob->query_guild_name_occ() == "DK of Khiraa")
#define IS_LP(ob) (ob->query_guild_name_occ() == "LP of Khiraa")
#define IS_GUILD_MASTER(ob) ( member_array(ob->query_real_name(),({"sarr","fysix"}) ) != -1)

/*      Taxes                           */

#if 0
#define DK_OCC_TAX 22
#define DK_OCC_LES_TAX 18 /* Taken lay difference into account */
#define DK_LAY_TAX 11
#define LP_OCC_TAX 23
#define LP_OCC_INI_TAX 15
#define LP_OCC_APP_TAX 17
#define LP_OCC_LES_TAX 19
#define LP_OCC_GRE_TAX 22
#define LP_LAY_TAX 10
#endif

#define DK_OCC_TAX     0
#define DK_OCC_LES_TAX 0
#define DK_LAY_TAX     0
#define LP_OCC_TAX     0
#define LP_OCC_INI_TAX 0
#define LP_OCC_APP_TAX 0
#define LP_OCC_LES_TAX 0
#define LP_OCC_GRE_TAX 0
#define LP_LAY_TAX     0

/*       Misc                           */
#define SOULDESC(s) (TP->add_prop(LIVE_S_SOULEXTRA, (s)))
#define DK_AS_CORPSE   "_dk_as_corpse"
#define KHIRAA_JOIN_INITIATE  "_khiraa_join_initiate"
#define KHIRAA_JOIN_JOINING   "_khiraa_join_joining"
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

/* Ceremony */

#define CER_WASHED_IN_BLOOD  "_cer_washed_in_blood"

