/*
    A bat. Mortricia 920917
 */
 
inherit "/std/creature";

inherit "/std/combat/unarmed";
inherit "/std/act/action";

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
    set_name("bat");
    set_short("black bat");
    set_long(BS(
        "It's a black bat. Its teeth are small but sharp.\n"
        ));
    set_adj("black");
    set_race_name("bat");
    set_stats(({15,15,15,5,5,5}));
    set_hp(1000);
    set_alignment(-40);
    set_gender(2);

    set_act_time(20);
    add_act("scream");

    set_skill(SS_DEFENCE, 5 + random(5));

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(CONT_I_WEIGHT, 3000);
    add_prop(CONT_I_VOLUME, 1000);
    add_prop(CONT_I_MAX_WEIGHT, 3500);
    add_prop(CONT_I_MAX_VOLUME, 1200);

    add_item(({"wings"}), "The wings are hairy.\n");
    add_item(({"teeth"}), "The teeth are sharp.\n");
}

#define A_BITE  0
#define A_CLAW  1

#define H_HEAD 0
#define H_BODY 1
#define H_WING 2

public void
cr_configure()
{
    add_attack(15, 15, W_IMPALE, 75, A_BITE);
    add_attack(10, 10, W_SLASH, 25, A_CLAW);

    add_hitloc( ({ 7, 7, 7 }), 20, "head", H_HEAD);
    add_hitloc( ({ 6, 6, 6 }), 35, "body", H_BODY);
    add_hitloc( ({ 2, 2, 2 }), 45, "wings", H_WING);
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
