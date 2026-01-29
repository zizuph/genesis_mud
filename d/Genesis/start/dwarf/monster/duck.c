#pragma save_binary
#pragma strict_types

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/domove"; /* Include this if you want the creature to move */
inherit "/std/act/action"; /* Include this if you want your creature to act */

#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>

#include <stdproperties.h>
#include "../defs.h"

#define A_BITE  0
#define H_HEAD 0
#define H_BODY 1

void
create_creature()
{
    set_name("duck");
    add_name("donald");
    set_race_name("duck");
    set_short("white duck");
    set_adj("white");
    set_long("It's a white duck, with a yellow beak.\n");

    set_stats(({7,4,5,2,2,10}));

    set_gender(0);

    set_attack_unarmed(A_BITE,  5, 3, W_IMPALE, 40, "yellow beak");
   
    set_hitloc_unarmed(H_HEAD, ({ 1, 2, 2, 2 }), 20, "head");
    set_hitloc_unarmed(H_BODY, ({ 1, 1, 3, 2 }), 80, "body");

    set_random_move(10);
    set_act_time(15);
  
    add_act("emote quacks.");

    add_prop(OBJ_I_WEIGHT,300);
    add_prop(OBJ_I_VOLUME,500);
    add_prop(CONT_I_WEIGHT,300);
    add_prop(CONT_I_VOLUME,500);

    remove_prop(OBJ_I_NO_GET);

    /* ducks tend to swim well */

    set_skill(SS_SWIM,100);
}

void
enter_env(object to,object from)
{
    int p;

    ::enter_env(to,from);

    p = to->query_prop(ROOM_I_TYPE);

    if(p == 1 || p == 2 || p == 3 || to->query_prop(OBJ_I_CONTAIN_WATER))
        set_alarm(5.0, 0.0, &command("emote swims around in the water."));

    set_fatigue(5000); /* keep it floating */
}

int
bonk(string s)
{
    notify_fail("Bonk what?\n");
    if(s!="duck")
        return 0;
  
    write("You bonk the duck on his head.\n");
    say(QCTNAME(this_player())+" bonks the duck on its head.\n");
    command("scream");

    return 1;
}

void
init_living()
{
    ::init_living();

    add_action(bonk,"bonk");

}
