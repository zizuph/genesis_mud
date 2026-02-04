/*
    A cat. Mortricia 920917
 */
 
inherit "/std/creature";

inherit "/std/combat/unarmed";
inherit "/std/act/action";
inherit "/std/act/domove";

#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include <wa_types.h>
#include <ss_types.h>
#include "/d/Terel/common/terel_defs.h"

#define BS(message)         break_string(message, 70)
#define TO                  this_object()
#define TP                  this_player()

create_creature()
{
    if (!IS_CLONE)
        return;
    set_name("cat");
    set_short("white cat");
    set_long(BS(
        "It's an ordinary white cat.\n"
        ));
    set_adj("white");
    set_race_name("cat");
    set_stats(({20,20,20,5,5,5}));
    set_hp(9999);
    set_alignment(100);
    set_gender(2);
    set_whimpy(30);
    set_random_move(5);

    set_act_time(10);
    add_act("purr");

    set_skill(SS_DEFENCE, 10 + random(5));

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(LIVE_I_QUICKNESS, 100);
    add_prop(CONT_I_WEIGHT, 10000);
    add_prop(CONT_I_VOLUME,  7500);
    add_prop(CONT_I_MAX_WEIGHT, 12000);
    add_prop(CONT_I_MAX_VOLUME, 9000);

    add_item(({"teeth"}), "The teeth are sharp.\n");
}

#define A_BITE  0
#define A_CLAW  1

#define H_HEAD 0
#define H_BODY 1
#define H_LEGS 2

public void
cr_configure()
{
    add_attack(10, 10, W_IMPALE, 25, A_BITE);
    add_attack(20, 20, W_SLASH, 75, A_CLAW);

    add_hitloc( ({ 7, 7, 7 }), 20, "head", H_HEAD);
    add_hitloc( ({ 9, 9, 9 }), 45, "body", H_BODY);
    add_hitloc( ({ 7, 7, 7 }), 35, "legs", H_LEGS);
}

public string
cr_attack_desc(int aid)
{
    switch(aid)
    {
    case A_BITE:return "teeth";
    case A_CLAW:return "claws";
    }
}
