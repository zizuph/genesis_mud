#include "/d/Shire/skills.h"
#include "/sys/ss_types.h"
#include "/d/Shire/sys/defs.h"
#include "/sys/wa_types.h"

/* the names of certain files */

#define SMITHS_LAY_SOUL     "smiths_lay_soul"
#define SMITHS_MASTER_SOUL  "smiths_master_soul"

#define SMITHS_LAY_SHADOW   "smiths_lay_shadow"

#define SMITHSDIR           "/d/Shire/smiths/"
#define NEW_SMITHSDIR       (SMITHSDIR + "/forge/")

/* directory in which smiths guild is placed */

#define SMITHSDIR_DOC       (SMITHSDIR + "doc/")
#define SMITHSDIR_HELP      (SMITHSDIR + "help/")
#define SMITHSDIR_LIB       (SMITHSDIR + "lib/")
#define SMITHSDIR_LOG       (SMITHSDIR + "log/")
#define SMITHSDIR_NPC       (SMITHSDIR + "npc/")
#define SMITHSDIR_OBJ       (SMITHSDIR + "obj/")
#define SMITHSDIR_ROOMS     (SMITHSDIR + "rooms/")

#define SMITHS_NEWS_LOG     (SMITHSDIR_LOG + "news.log")
#define SMITHS_WIZ_LOG      (SMITHSDIR_LOG + "smiths.log")

#define SMITHS_MASTER_LOG   (SMITHSDIR_LOG + "master")
#define SMITHS_MASTER_OBJ   (SMITHSDIR_LIB + "master")

/* material additions used in the smiths guild */

#define GREYALLOY   3
#define HIGHSTEEL   2
#define BLUESTEEL   1
#define STEEL       0
#define IRON        -1
#define COPPER      -2
#define KINE        1
#define LEATHER     0
#define WOOD        0
#define GEM         1

/* material costs used in the smiths guild */

#define GREYALLOY_COST      1000
#define HIGHSTEEL_COST       800
#define BLUESTEEL_COST       600
#define STEEL_COST           400
#define IRON_COST            300
#define COPPER_COST          200
#define TANNING_COST          20
#define LEATHER_COST         300
#define WOOD_COST            300
#define GEM_COST             500

/* used in the shadow */

#define LAYMAN_GUILD_TAX     6
#define GUILD_NAME           "The Smiths Guild"
#define GUILD_STYLE          "fighter"

/* training room */

#define SMITHS_GUILD_TRAINER (SMITHSDIR_ROOMS + "improve")

/* properties used in guild */

// #define SMITHS_AMOUNT_FORGED "_smiths_i_numbers_forged"


/* Macros for easier reading while working with manager object */
// weapons
#define DIF 0
#define WT 1
#define DT 2
#define HANDS 3
#define NAME 4
#define ADJ 5
#define SHORTD 6
#define LONGD 7
#define MATERIALS 8
#define HIT 9
#define PEN 10
// armour
#define AC 1
#define LOC 2
#define MOD 3
#define SA_NAME 4
#define SA_ADJ 5
#define SA_SHORT 6
#define SA_LONG 7
#define SA_MATERIALS 8

/* Support for finding manager object */
#define MANAGER (SMITHSDIR_ROOMS + "manager_room")
 
/* Shadows we need for setting and recovering adjectives on items */
// #define SMITH_ADJ_SHADOW ("/d/Shire/smiths/obj/bl_final")
#define SMITH_ADJ_TEXT (([ "blackened" : "Its blade has been blackened by fire.\n",\
                           "copper-plated" : "It has been plated in copper.\n",\
                           "copper-edged" : "It has been edged in copper.\n",\
                           "silver-plated" : "It has been plated in silver.\n",\
                           "silver-edged" : "It has been edged in silver.\n",\
                           "gold-plated" : "It has been plated in gold.\n",\
                           "gold-edged" : "It has been edged in gold.\n",\
                           "platinum-plated" : "It has been plated in platinum.\n",\
                           "platinum-edged" : "It has been edged in platinum.\n",\
                       ])) 

#define SMITH_OBJECT_LOG (SMITHSDIR_LOG + "smith_object_log")
/*
#define SMITH_ADJ_LIST (({ "blackened", "polished", "copper-edged", "copper-plated", \
                           "silver-edged", "silver-plated", "gold_edged", "gold-plated", \
                           "platinum-edged", "platinum-plated" }))
*/
/* Prop for Smiths personal seal. */
#define OBJ_I_SMITH_SEAL "_obj_i_smith_seal"

/* misc */
#define OBJ_S_MODIFIED_BY_SMITH "_obj_s_modified_by_smith"
#define OBJ_I_BELLOW_USED "_obj_i_bellow_used"
#define LIVE_I_SMITH_ENTRANCE_QUEST "_live_i_smith_entrance_quest"
#define SMITH_MATERIAL_LIST ([ 1 : "smiths_iron_bar", \
                               2 : "smiths_leather", \
                               3 : "sm_wood", \
                            ])
#define DT_AS ({ "Impale","Slash","Slash and Impale","Bludgeon", \
                 "Impale and Bludgeon","Slash and Bludgeon", \
                 "Impale, Slash, and Bludgeon", \
              })
#define WT_AS ({ "Sword","Polearm","Axe","Knife","Club", \
              })
#define HANDS_MAP ([ W_ANYH : "Either hand", W_RIGHT : "Right hand", \
                     W_LEFT : "Left hand", W_BOTH : "Both hands", \
                  ])
#define AT_MAP ([ A_BODY : "Body armour", A_HEAD : "Head armour", \
                  A_ARMS : "Arm armour", A_LEGS : "Leg armour", \
                  A_BODY | A_ARMS : "Body and arm armour", \
                  A_BODY | A_LEGS : "Body and leg armour", \
                  A_BODY | A_ARMS | A_LEGS : "Body, arm, and leg armour", \
               ])

/***** Log guild membership *****/

#define SMITH_MEMBERSHIP_LOG (SMITHSDIR_LOG + "membership.log")
#define MAX_MEMBERSHIP_LOG_SIZE 10000

void
log_membership(string s) 
{
    setuid(); seteuid(getuid());

    if (file_size(SMITH_MEMBERSHIP_LOG) > MAX_MEMBERSHIP_LOG_SIZE)
        rename(SMITH_MEMBERSHIP_LOG, (SMITH_MEMBERSHIP_LOG + ".old"));

    s = ctime(time())+" "+s;
    write_file(SMITH_MEMBERSHIP_LOG, s);  
}


/***** Detemine guild membership *****/

int
IS_MEMBER(object pl) 
{
    if (pl->query_guild_name_lay() != GUILD_NAME)
        return 0;
   
    return 1;
}


/***** End guild membership *****/

int
remove_smith_guild_member(object member) 
{
    object item;
   
    member->setup_skill_decay();
    if (objectp(item = present("smiths_necklace", member)))
        item->remove_object();
   
    member->remove_guild_lay();
    member->clear_guild_stat(SS_LAYMAN);
    member->remove_cmdsoul(SMITHS_LAY_SOUL);
    member->update_hooks();
   
  /*    If the player starts in the guild by default, set this to
   *    the default starting location for all players.
   */

    if (member->query_default_start_location() == SMITHSDIR_ROOMS+"start_r")
        member->set_default_start_location(member->query_def_start());
}


// checks players to see if they are advanced smiths
check_player()
{
    if (TP->query_stat(SS_LAYMAN)>=50 || this_player()->query_wiz_level())

        return 0;
    else
        TP->catch_tell("An apprentice steps in front of you and " +
            "declares: You have not proven yourself worthy to go there.\n");
        return 1;
}