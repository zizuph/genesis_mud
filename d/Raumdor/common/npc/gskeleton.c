/* Greater Skeleton Warrior, Sarr */

#include "defs.h"
inherit STD_UNDEAD;
inherit "/d/Raumdor/common/npc/common_equipment";

void
create_monster()
{
    ::create_monster();
    string adj = one_of_list(({
      "frightening", "terrifying", "evil", "lifeless",
    }));

    set_name("skeleton");
    set_race_name("skeleton");
    set_adj("champion");
    add_adj(adj);
    set_short(adj + " champion skeleton");
    set_long(
      "This skeletal warrior looks like it comes right out of a nightmare. " +
      "Its evil flashing eyes, boney frame, and sharp skeletal claws invoke " +
      "a sense of panic. It looks like it was once a very powerful warrior, " +
      "and still remembers how to fight well. This one in particular seems " +
      "to have held considerable authority, for it holds itself in a strong, " +
      "dominating posture.\n");

    set_skill(SS_DEFENCE, 85);
    set_skill(SS_UNARM_COMBAT, 5);
    set_skill(SS_WEP_SWORD, 90);
    set_skill(SS_WEP_POLEARM, 90);
    set_skill(SS_WEP_KNIFE, 90);
    add_prop(OBJ_I_WEIGHT, 10000);
    add_prop(OBJ_I_VOLUME, 9000);
    add_prop(LIVE_I_UNDEAD, 40);
    add_prop(LIVE_I_NO_CORPSE, 1);
    set_random_move(12);
    set_act_time(3);
    add_act("emote smiles coldly.");
    add_act("emote glares, a red flash erupting from its empty sockets.");
    set_cact_time(3);
    add_cact("emote lets out a silent scream of fury.");
    add_cact("emote wants to tear the flesh off you.");
    set_mm_in("drops out of a tree in front of you!");

    if (random(2))
        equip(({
          one_of_list(({
            COMMON_WEP_DIR + "cnaginata", COMMON_WEP_DIR + "ckatana",
            COMMON_WEP_DIR + "cwakizashi",
          }))
        }));
    else
        equip(({one_of_list(({
                            COMMON_WEP_DIR + "cbsword", COMMON_WEP_DIR + "cbdagger",
                            COMMON_WEP_DIR + "cblsword",
                            }))
                    }));

    add_undead_armours();
}

void
do_die(object killer)
{
    object bones;
    command("emote falls to the ground in a pile of bones.");
    bones = clone_object(COMMON_OBJ_DIR + "pbones");
    bones->move(E(TO));
    ::do_die(killer);
}
