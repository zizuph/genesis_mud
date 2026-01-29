/*
    maid.c

    Code by Sarr,
    Recoded by Fysix, March 1998
    2017-06-04 Malus: Added race name
    Updated with add_name("noble"); - Mirandus - Feb 2018
*/
#pragma strict_types

inherit "/d/Kalad/std/monster";

#include "default.h"

void
create_kalad_monster()
{
    string radj = ({"beautiful", "cute", "young", "petite", "modest",
      "sweet-smelling"})[random(6)];
    object arm;

    set_name("noblewoman", 1);
    add_name("noble");
    set_pname("noblewomen");
    set_adj(radj);
    set_race_name("human");
    set_short(radj +" noblewoman");
    set_pshort(radj +" noblewomen");
    set_long("This is a young noblewoman. She looks pretty, but "+
      "she seems to regard you below her rank. She smiles sweetly "+
      "and takes a sip of her wine.\n");
    set_gender(1);
    set_stats(({40,50,50,70,70,30}));
    set_skill(SS_DEFENCE,30);
    set_alignment(600);
    set_knight_prestige(-300);

    set_act_time(5);
    add_act("emote picks at her food.");
    add_act("giggle");
    add_act("say What a wonderful dinner!");
    add_act("emote fixes her hair.");
    add_act("laugh merr");
    add_act("bat");

    set_cact_time(3);
    add_cact("shout Help ! Help !");
    add_cact("say What did I ever do to you!");
    add_cact("scream");
    add_cact("cower");

    add_prop(LIVE_I_NEVERKNOWN,1);
    // I am a Kabal citizen
    add_prop(LIVE_I_KABAL_NPC_TYPE, KABAL_CITIZEN);

    add_equipment(({
	NOBLE + "arm/silk_skirt",
	NOBLE + "arm/silk_tunic",
	NOBLE + "arm/high-heels",
	/*
		NOBLE + "arm/pearl_necklace",
	 */
	NOBLE + "arm/pierce3",
      }));

    arm = clone_object(NOBLE + "arm/pair_rings");
    arm->set_ring_metal("gold");
    arm->set_ring_metal("emerald",1);
    arm->set_ring_value(2872);
    arm->move(TO, 1);
    command("insert rings in both ears");
}

void
attacked_by(object enemy)
{
    ::attacked_by(enemy);
    command("shout Guards! Help! Help!");
    set_alarm(3.0, 0.0, "call_guards", enemy);
}

void
call_guards(object enemy)
{
    call_other(ENV(TO),"call_guards",enemy);
}

