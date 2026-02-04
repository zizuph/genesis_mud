/*
    A dog. Mortricia 920917
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
    set_name("dog");
    set_short("black dog");
    set_long(BS(
        "It's a black dog. It's drooling.\n"
        ));
    set_adj("black");
    set_race_name("dog");
    set_stats(({30,30,30,5,5,5}));
    set_hp(9999);
    set_alignment(-150);
    set_gender(2);
    set_whimpy(30);
    set_random_move(20);

    set_act_time(10);
    add_act("@@do_bark");

    trig_new("%s 'purrs' %s", "kill_cat");

    set_skill(SS_DEFENCE, 15 + random(5));

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(CONT_I_WEIGHT, 20000);
    add_prop(CONT_I_VOLUME,  15000);
    add_prop(CONT_I_MAX_WEIGHT, 24000);
    add_prop(CONT_I_MAX_VOLUME, 18000);

    add_item(({"legs"}), "The legs are hairy.\n");
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
    add_attack(25, 25, W_IMPALE, 70, A_BITE);
    add_attack(10, 10, W_SLASH, 30, A_CLAW);

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
    case A_CLAW:return "paws";
    }
}

do_bark()
{
    tell_room(environment(TO), "The drooling dog barks at you.\n");
    return "";
}

kill_cat(str1, str2)
{
    set_follow(lower_case(str1));
    write("The black dog attacks you!\n");
    say(QCTNAME(TP) + " is attacked by the black dog.\n");
    attack_object(TP);
}
