/* Satyr
** This is the priestly satyr in the Satyr forest found in rooms/sforruin.c
** A newbie can solve the quest by giving him the broken leg from the
** statue (objects/sforleg.c) found by 'search underbrush' in rooms/sfro12.c
**
** History:
** Date      Coder       Action
** -------- ------------ ------------------------
** 2/17/95  Zima         created
** 2/21/95  Zima         rewritten as humanoid
**/
inherit "/std/monster";
#include <ss_types.h>
#include <stdproperties.h>
#include <money.h>
#include <macros.h>
#include <cmdparse.h>
#include "defs.h"
 
void equip_me() {
    object this=this_object();
 
    (clone_object(ARMOUR_DIR+"satcape"))->move(this);
    (clone_object(WEAPON_DIR+"satsword"))->move(this);
    (clone_object(OBJ_DIR+"sflute"))->move(this);
    command("wield all");
    command("wear all");
}
 
void create_monster() {
    set_name("satyr");
    add_adj(({"regal","caped"}));
    set_short("regal caped satyr");
    set_race_name("satyr");
    set_long(
        "It is a great satyr, a little larger than most you have seen "+
        "in the forest, wearing a long purple cape around its neck "+
        "which flows down its back to the ground. Its black eyes convey "+
        "a great wisdom. Its goat legs are covered in curly white fleece "+
        "and it has two large horns curling out from the white hair on its "+
        "head.\n");
 
    add_prop(ATTACK_TEAM,"_satyr_attack_team");
    set_stats(({ 30, 30, 30, 30, 30, 30}));
 
    set_hp(1000);
    set_gender(2); /* neuter */
    set_skill(SS_DEFENCE,   30);
    set_skill(SS_PARRY,     30);
    set_skill(SS_WEP_SWORD, 30);
 
    set_alignment(-3);
    set_act_time(10);
    add_act("emote paws the ground with its hoof.");
    add_act("emote glances at the statue longingly.");
    add_act("emote rubs the stub of the broken leg of the statue.");
    add_act("emote stares deeply into your eyes.");
    add_act("emote circles the statue.");
    add_act("emote crosses its arms.");
    add_act("emote scratches its head.");
 
    set_default_answer("The regal caped satyr turns its head sideways and "+
                       "looks confused.\n");
    add_ask(({"quest","tour","statue","leg","for quest","for tour",
              "about statue","about leg"}),
              "emote points at the statue and sobs with a lost look "+
              "in its eyes.",1);
    set_cact_time(5);
    add_cact("emote charges with its horns.");
    add_cact("emote kicks violently with its hooves.");
    add_cact("emote glares with murder in its eyes.");
    add_cact("emote hisses loudly.");
 
    add_prop(CONT_I_WEIGHT,  30000);
    add_prop(CONT_I_VOLUME,  30000);
    set_all_hitloc_unarmed(query_average_stat() / 4);
}
