/* Cow that roams the west Calian moorland.
   Coded by Digit.

   Modified Maniac 5/5/95, 21.6.95

*/


#pragma save_binary

inherit "/std/creature";
inherit "/std/act/chat";
inherit "/std/combat/unarmed";
inherit "/std/act/domove";
inherit "/std/act/action";

#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include "/d/Genesis/login/login.h"
#include "monster.h"

#define A_BITE 0
#define A_HOOF 1

#define H_HEAD 0
#define H_BODY 1


void
create_creature()
{
    string *colour = ({"brown", "light-brown", "black"});
    string *general = ({"large", "lazy", "dozy"});

    set_name("cow");
    set_race_name("cow");
    set_adj(({general[random(sizeof(general))], 
               colour[random(sizeof(colour))]})); 
    set_long("This cow seems to be ignoring your presence here.  She "+
        "is eating the small strands of grass growing here.\n");
    set_stats(({5,5,10,10,10,15}));
    set_hp(1000);
    set_gender(1);
    set_alignment(50);
    set_attack_unarmed(A_HOOF,5,5,W_BLUDGEON,80,"hooves");
    set_attack_unarmed(A_BITE,5,5,W_IMPALE,20,"bite");
    set_hitloc_unarmed(H_HEAD,({8,8,8,8}), 20, "head");
    set_hitloc_unarmed(H_BODY,({8,8,8,8}), 80, "body");

    set_restrain_path(ROAD+"m"); /* restrict it to the moor */
    set_random_move(15);

    set_act_time(2);

    add_act("emote chews on some grass.");
    add_act("emote wags her tail.");
    add_act("emote lies down in some grass.");
    add_act("emote stares at you dreamily.");
    add_act("emote chews her cud.");
    add_act("emote shoos away some flies.");
    add_act("emote stares dumbly at the sky.");

    set_chat_time(2);
    add_chat("Mooooo");
    add_chat("Moo");
    add_chat("Oin...err Mooo");
    add_chat("Moooooooooooo");

    add_prop(CONT_I_WEIGHT, 100000);
    add_prop(CONT_I_MAX_WEIGHT, 200000);
    add_prop(CONT_I_VOLUME, 100000);
    add_prop(CONT_I_MAX_VOLUME, 200000);
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_m_in("lumbers in slowly");
    set_mm_in("lumbers in slowly.");
    set_m_out("lumbers away slowly");
    set_mm_out("lumbers away slowly");
}


string
actor_race_sound()
{
    return "moo"; 
}

string
race_sound()
{
    return "moos"; 
}