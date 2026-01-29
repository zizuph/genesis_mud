/* Giant Skeleton Warrior, Sarr */
/* 2017-08-19 Malus: Added set_mm_in, moving defaults to base/std file */

#include "defs.h"
inherit STD_UNDEAD;
inherit "/d/Raumdor/common/npc/common_equipment";

void
create_monster()
{
    ::create_monster();
    set_name("skeleton");
    set_race_name("skeleton");
    set_adj("giant");
    set_short("giant skeleton");
    set_long(
      "This skeletal warrior looks like it arrived right out of a nighmare. " +
      "Its evil flashing eyes, boney frame, and sharp skeletal claws invoke " +
      "a sense of panic. This one is huge, making you wonder if it was once " +
      "an ogre or giant.\n");
    set_skill(SS_DEFENCE, 90);
    set_skill(SS_WEP_SWORD, 95);
    set_skill(SS_WEP_POLEARM, 95);
    set_skill(SS_WEP_KNIFE, 95);

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(OBJ_I_WEIGHT, 10000);
    add_prop(OBJ_I_VOLUME, 9000);
    add_prop(LIVE_I_UNDEAD, 45);
    add_prop(LIVE_I_NO_CORPSE, 1);

    set_random_move(5);
    set_act_time(3);
    add_act("emote smiles coldly.");
    add_act("emote glares, a red flash erupting from its empty sockets.");
    set_cact_time(3);
    add_cact("emote lets out a silent scream of fury.");
    add_cact("emote wants to tear the flesh off you.");
    add_cact("emote mauls into you with a charge.");
    set_mm_in("smashes its way out of the trees!");

    if (random(2))
        equip(({
          one_of_list(({
            COMMON_WEP_DIR + "cnaginata", COMMON_WEP_DIR + "ckatana",
            COMMON_WEP_DIR + "cwakizashi",
          }))
        }));
    else
        equip(({
          one_of_list(({
            COMMON_WEP_DIR + "cblsword", COMMON_WEP_DIR + "cbsword",
            COMMON_WEP_DIR + "cbdagger",
          })),
        }));

    add_undead_armours();
}

void
do_die(object killer)
{
    command("emote falls to the ground in a pile of bones.");
    clone_object(COMMON_OBJ_DIR + "pbones")->move(E(TO));
    ::do_die(killer);
}
