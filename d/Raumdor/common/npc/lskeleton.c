/* Lesser Skeleton Warrior, Sarr */
#include "defs.h"
inherit STD_UNDEAD;
inherit "/std/combat/unarmed";
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
    add_adj(adj);
    set_short(adj + " skeleton");
    set_long(
      "This skeletal warrior looks like it comes right out of a nighmare. " +
      "Its evil flashing eyes, boney frame, and sharp skeletal claws invoke " +
      "a feeling of panic. It looks like it was once a very powerful warrior " +
      "and still remembers how to fight well.\n");
    set_gender(G_NEUTER);
    set_stats(STAT_ARRAY(110));
    set_skill(SS_DEFENCE, 80);
    set_skill(SS_UNARM_COMBAT, 100);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(OBJ_I_WEIGHT, 6500);
    add_prop(OBJ_I_VOLUME, 3500);
    add_prop(LIVE_I_UNDEAD, 20);
    add_prop(LIVE_I_NO_CORPSE, 1);
    set_random_move(10);
    set_act_time(3);
    add_act("emote smiles coldly.");
    add_act(
      "emote glares; a red flash erupts momentarily from the empty sockets.");
    set_cact_time(3);
    add_cact("emote lets out a silent scream of fury.");
    add_cact("emote wants to tear the flesh off you.");
    set_attack_unarmed(0, 40, 40, W_SLASH, 10, "right skeletal foot");
    set_attack_unarmed(1, 35, 35, W_SLASH, 40, "left skeletal claw");
    set_attack_unarmed(2, 35, 35, W_SLASH, 40, "right skeletal claw");
    set_attack_unarmed(3, 40, 40, W_SLASH, 10, "left skeletal foot");
    set_hitloc_unarmed(0, 30, 45, "rib cage");
    set_hitloc_unarmed(1, 30, 15, "skull");
    set_hitloc_unarmed(2, 30, 20, "legs");
    set_hitloc_unarmed(3, 30, 10, "left arm");
    set_hitloc_unarmed(4, 30, 10, "right arm");
    
    add_undead_armours();

}

string
query_combat_file()
{
    return "/d/Raumdor/common/std/chumanoid";
}

void
do_die(object killer)
{
    command("emote falls to the ground in a pile of bones.");
    clone_object(COMMON_OBJ_DIR + "pbones")->move(E(TO));
    ::do_die(killer);
}
