/*
 * This is a common sea gull
 * Can be cloned by ~Cirath/ak_wela/pier*.c and ~Cirath/ak_wela/bwalk*.c
 */

inherit "/std/creature";
inherit "/std/act/action";
inherit "/std/combat/unarmed";

#include "/sys/ss_types.h"
#include "/sys/wa_types.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"

create_creature()
{
    if (!IS_CLONE)
        return;
    seteuid(getuid(this_object()));
    set_name("gull");
    add_name("bird");
    set_race_name("bird"); 
    set_gender(G_NEUTER);

    set_short("sea gull");
    set_long("This is definitely a sea gull.\n");

    add_prop(LIVE_I_NEVERKNOWN);

    set_stats(({ 5, 10, 2, 15, 15, 25 }));

    set_attack_unarmed(0,  8, 8,W_IMPALE, 100, "beak");
    set_hitloc_unarmed(0, ({ 8, 8, 8, 8 }), 100, "body");

    set_act_time(10);
    add_act("@@drop");

    add_prop(CONT_I_WEIGHT, 50);   /* 0.05 Kg  */
    add_prop(CONT_I_VOLUME, 100);   /* 0.10 Ltr */
}

drop()
{
    int ran;
    ran = random(3);

    switch(ran)
    {
        case 0: tell_room(environment(), "The bird leaves a reminder of its " +
                          "presence on your shoulder.\n");
                break;
        case 1: tell_room(environment(), "The bird stares at you.\n");
                break;
        case 2: tell_room(environment(), "The bird dives down and catches a " +
                          "fish from the lake.\n");
                break;
    }
}
