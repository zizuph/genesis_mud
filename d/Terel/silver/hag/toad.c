/*
    A slimy toad, turns into a prince when kissed :-) Mortricia 920721
    The 'kiss' function is not yet implemented.

    Modified for the new silver forest -- Tomas 09/05
 */
 
inherit "/std/creature";

inherit "/std/combat/unarmed";
inherit "/std/act/action";
inherit "/std/act/seqaction";

#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include <wa_types.h>
#include <ss_types.h>
#include "../include/defs.h"


create_creature()
{
    if (!IS_CLONE)
        return;
    set_name("toad");
    add_name("ragata:toad");
    set_short("slimy toad");
    set_long("It's a very slimy toad. You feel disgusted just by looking at it. " +
        "Wherever it jumps it leaves a trail of yellow slime.\n");
    set_adj("slimy");
    set_race_name("toad");
    set_stats(({5, 30, 5, 100, 100, 5}));
    set_hp(9999);
    set_mana(1000);
    set_gender(2);

    set_act_time(20);
    add_act("burp");

    set_skill(SS_DEFENCE, 5 + random(5));

    add_prop(CONT_I_WEIGHT, 200);
    add_prop(CONT_I_VOLUME,  400);
    add_prop(CONT_I_MAX_WEIGHT, 250);
    add_prop(CONT_I_MAX_VOLUME, 500);

    seq_new("do_stream");
    seq_addfirst("do_stream", "@@equip_me");
}

equip_me()
{
    seteuid(getuid(this_object()));
    clone_object(HAG + "gem") -> move(this_object());
}


#define A_SPIT  0
#define A_JUMP  1

#define H_HEAD 0
#define H_BODY 1
#define H_LEGS 2

public void
cr_configure()
{
    add_attack(10,  2, W_BLUDGEON, 25, A_SPIT);
    add_attack(15,  5, W_BLUDGEON, 75, A_JUMP);

    add_hitloc( ({ 7, 7, 7 }), 35, "head", H_HEAD);
    add_hitloc( ({ 6, 6, 6 }), 45, "body", H_BODY);
    add_hitloc( ({ 6, 6, 6 }), 20, "legs", H_LEGS);
}

public string
cr_attack_desc(int aid)
{
    switch(aid)
    {
    case A_SPIT:return "spittle";
    case A_JUMP:return "leap";
    }
}
