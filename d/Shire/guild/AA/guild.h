// Added gnome as an alowed race
// Finwe, November 2017
#ifndef _SHIRE_ANGMAR_GUILD_DEFS_
#define _SHIRE_ANGMAR_GUILD_DEFS_

#define AA_TESTING 1
#if AA_TESTING == 1
#define DBGMSG(x)   find_player("finwe")->catch_msg(x)
#else
#define DBGMSG(x)
#endif AA_TESTING

// Include the Shire defs.h
#include "/d/Shire/sys/defs.h"
#include "/d/Genesis/specials/std/defs.h"
#include <alignment.h>

#define AA_DIR ("/d/Shire/guild/AA/")

#define FOOD_DIR (AA_DIR + "/food/")
#define HE(o)  (o)->query_pronoun()
#define HIS(o) (o)->query_possessive()
#define HIM(o) (o)->query_objective()

#define GUILD_NAME  "Angmar Army"
#define GUILD_STYLE "fighter"
#define GUILD_TAX_LAY  14
#define GUILD_TAX_OCC  30

// time constants
#define DAY         86000
#define WEEK        (7*86400)
#define TEN_DAYS    864000
#define MONTH       (30*86400)

// guild skills
#define SS_SMASH        112200
#define SMASH_NAME      "smash"
#define SS_SHIELD       112201
#define SHIELD_NAME     "shield"
#define SS_BASH         112202
#define BASH_NAME       "shield bash"
#define SS_RETREAT      112203
#define RETREAT_NAME    "retreat"

// shadows and souls
#define AA_EVADE_OBJ    (AA_DIR+"shadow/aa_evade_obj")
#define AA_SHADOW       (AA_DIR+"shadow/aa_shadow")
#define AA_OCC_SHADOW   (AA_DIR+"shadow/aa_sh_occ")
#define AA_LAY_SHADOW   (AA_DIR+"shadow/aa_sh_lay")
#define AA_SOUL         (AA_DIR+"soul/aa_soul")
#define AA_SOUL_E       (AA_DIR+"soul/aa_emotes")
#define AA_SOUL_R       (AA_DIR+"soul/rumour_soul")

#define AA_TRAINER      (AA_DIR+"rooms/train")
#define AA_VOTE_ROOM    (AA_DIR+"rooms/vote")
#define AA_RANKS_OBJ    (AA_DIR+"obj/aa_ranks")
#define AA_COUNCIL_OBJ  (AA_DIR+"obj/aa_council")
#define AA_PUNISH_OBJ   (AA_DIR+"obj/aa_punish")
#define AA_OPTIONS_OBJ  (AA_DIR+"obj/aa_options")
#define AA_JOIN_ROOM    (AA_DIR + "rooms/chapel")

#define AA_SPECIAL      (AA_DIR+"special/aa_special")
#define SMASH_ABILITY   (AA_DIR+"special/smash")
#define SMACK_ABILITY   (AA_DIR+"special/smack")
#define SCARE_ABILITY   (AA_DIR+"special/scare")

// alignment checks
#define ALIGN_JOIN      ALIGN_EVIL
#define ALIGN_BOOT      ALIGN_DISAGREEABLE

// adjectives
#define ADJ_LIST ({"Fresh","Insecure","Young","Training","Proud", \
                   "Legionary","Experienced","Elder","Dangerous","Cruel", \
                   "Notorious","Infamous","Bestial","Feared", \
                   "Formidable", "Dreadful"})

#define SPEC_ATTACK_IS    "_aa_spec_attack_is_"

#define IS_MEMBER(x) ((x)->query_guild_member(GUILD_NAME))
#define IS_LAYMAN(x) ((x)->query_guild_name_lay() == GUILD_NAME)
#define IS_HIGHER(ob)  (TP->query_name() != "Milan" && IS_MEMBER(ob) && \
                        (ob->query_wiz_level() || \
                         AA_RANKS_OBJ->rank_no(ob) > AA_RANKS_OBJ->rank_no(TP)))
#define IS_LOWER(ob)   (IS_MEMBER(ob) && !ob->query_wiz_level() && \
                        (TP->query_name() != "Milan" || \
                         AA_RANKS_OBJ->rank_no(ob) < AA_RANKS_OBJ->rank_no(TP)))


#define ALLOWED_RACES ({ "gnome", "ogre", "minotaur", "orc", "goblin", \
                        "hobgoblin", "dwarf", "human", "troll",\
                        "wraith"})

#define AA_PUN        "_aa_punishment_"

// No more defines after this line.
#endif
