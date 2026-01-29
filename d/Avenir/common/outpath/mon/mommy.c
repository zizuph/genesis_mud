// file name:    Mommy
// creator(s):   Cirion, April 1996
// last update:
// purpose:      Mommy grub
// note:         She lays the eggs that clone the little grubs.
// bug(s):
// to-do: 
#pragma strict_types

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/attack";

#include "../outpath.h"

#define A_TAIL       0
#define A_HEADS      1

#define H_HEADS      0
#define H_BODY       1
#define H_TAIL       2

void create_creature()
{
    set_name("grub");
    add_name("mommy");
    set_race_name("grub");

    set_adj("enormous");
    set_gender(G_FEMALE);

    set_long("She is a massive, slimy maggot-like creature "
            +"with a long fat body. She lies in the corner, "
            +"seemingly passive.\n");

    set_stats(({ 25, 10, 35, 5, 5, 10 }));

    set_skill(SS_UNARM_COMBAT,  10);
    set_skill(SS_DEFENCE,        5);
    set_skill(SS_AWARENESS,     50);

    set_alignment(0);

    set_attack_unarmed(A_TAIL, 10, 10, W_BLUDGEON, 60, "slimy tail");
    set_attack_unarmed(A_HEADS, 10, 10, W_BLUDGEON, 40, "head");

    set_hitloc_unarmed(H_HEADS,   ({ 8, 8, 6 }), 30, "head");
    set_hitloc_unarmed(H_BODY,   ({ 2, 2, 20 }), 40, "body");
    set_hitloc_unarmed(H_TAIL,   ({ 4, 4, 20 }), 30, "tail");

    add_prop(CONT_I_WEIGHT, 5);
    add_prop(CONT_I_VOLUME, 25);

    add_prop(LIVE_I_SEE_INVIS,  -1);  // She is blind...
    add_prop(LIVE_I_NEVERKNOWN,  1);
    add_prop(NPC_I_NO_LOOKS,     1);

    set_act_time(25);
      add_act("@@lay_egg@@");

}

string lay_egg()
{
  seteuid(getuid());
  clone_object(OBJ+"egg")->move(ENV(TO), 1);
  return "emote expells a slimy white egg from her bloated body.";
}

object make_corpse()
{
    object   corpse;

    seteuid(getuid());

    corpse = clone_object(OBJ+"mcorpse");
    corpse->set_name(query_name());
    corpse->change_prop(CONT_I_WEIGHT, query_prop(CONT_I_WEIGHT));
    corpse->change_prop(CONT_I_VOLUME, query_prop(CONT_I_VOLUME));
    corpse->add_prop(CORPSE_S_RACE, query_race_name());
    corpse->add_prop(CONT_I_TRANSP, 1);
    corpse->change_prop(CONT_I_MAX_WEIGHT,
	query_prop(CONT_I_MAX_WEIGHT));
    corpse->change_prop(CONT_I_MAX_VOLUME,
	query_prop(CONT_I_MAX_VOLUME));
    corpse->set_leftover_list(query_leftover());

    return corpse;
}
