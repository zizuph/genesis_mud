/*
    A slimy toad, turns into a prince when kissed :-) Mortricia 920721
 */
 
inherit "/std/creature";

inherit "/std/combat/unarmed";
inherit "/std/act/seqaction";

#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include <wa_types.h>
#include <ss_types.h>

#define HOME_DIR "/d/Terel/mortricia/objects/"

create_creature()
{
    if (!IS_CLONE)
        return;
    set_name("cow");
    set_short("white cow");
    set_long(break_string(
        "It's a white cow. It's not well-fed since you see the bones " +
        "under the skin.\n", 70));
    set_adj("white");
    set_race_name("animal");
    set_stats(({20, 20, 20, 10, 10, 20}));
    set_hp(1000);
    set_gender(2);

    set_skill(SS_DEFENCE, 10 + random(10));

    add_prop(OBJ_I_WEIGHT, 300000);
    add_prop(OBJ_I_VOLUME, 250000);
    add_prop(CONT_I_MAX_WEIGHT, 350000);
    add_prop(CONT_I_MAX_VOLUME, 300000);
}

#define A_BUTT  0
#define A_TRAM  1

#define H_HEAD 0
#define H_BODY 1
#define H_LEGS 2

public void
cr_configure()
{
    add_attack(15, 10, W_BLUDGEON, 50, A_BUTT);
    add_attack(20, 20, W_BLUDGEON, 50, A_TRAM);

    add_hitloc( ({15,15,15}), 35, "head", H_HEAD);
    add_hitloc( ({15,15,15}), 45, "body", H_BODY);
    add_hitloc( ({10,10,10}), 20, "legs", H_LEGS);
}

public string
cr_attack_desc(int aid)
{
    switch(aid)
    {
    case A_BUTT:return "head butt";
    case A_TRAM:return "trample";
    }
}
