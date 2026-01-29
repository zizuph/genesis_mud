/*
 * fishing_rod.c
 *
 * Used in npc/sailor.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/weapon";

#include "defs.h"
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>

int bait;

string
query_recover()
{
    return MASTER + ":" + query_wep_recover() + "#bait#" + bait + "#";
}

void
init_recover(string arg)
{
    string dum1, dum2;
    init_wep_recover(arg);
    sscanf(arg, "%s#bait#%d#%s", dum1, bait, dum2);
}

void catchf();

int
fish(string str)
{
    mixed temp;
    temp = environment(TP)->query_prop(ROOM_I_TYPE);

    if (!(temp == ROOM_BEACH) && !(temp == ROOM_IN_WATER))
    {
        TP->catch_msg("You suddenly realize that this room has no water.\n");
        return 1;
    }

    if (bait)
    {
        NF("You have used all the bait on this rod.\n");
        return 0; 
    }
    bait = 1;

    say(QCTNAME(TP) + " tries to catch a fish.\n");
    TP->catch_msg("You begin fishing.\n");

    set_alarm(10.0, 0.0, catchf);

    return(1);
}

void
catchf()
{
    mixed temp;
    temp = environment(TP)->query_prop(ROOM_I_TYPE);

    if ((temp == ROOM_BEACH) || (temp == ROOM_IN_WATER))
    {
        say(QCTNAME(TP) + " caught a fish! It looks very tasty.\n");
        clone_object(ROKEDIR + "obj/fish")->move(TP);
        TP->catch_msg("You feel a sudden move in the fishingrod and " +
                      "pull the line out of the water. You have caught " +
                      "a fish! You carefully remove the fish from the hook " +
                      "and put it in your pocket.\n");
        set_long("This is a sturdy fishingrod, suitable for fishing.\n" +
                 "Unfortunately it has no bait.\n");
    }
    else
        TP->catch_msg("It is usually better to stay near the water " +
                      "when fishing than to run away from it.\n");
}

nomask void
create_weapon()
{
    bait = 0;

    set_name("rod");
    add_name("fishing_rod");
    set_adj("fishing");
    set_short("fishing rod");
    set_long("This is a very sturdy fishing rod.\n" +
             "Maybe you should try to fish with it?\n");
    set_hit(5);
    set_pen(5);
  
    set_wt(W_SWORD);
    set_dt(W_IMPALE);

    add_prop(OBJ_I_WEIGHT, 4);
    add_prop(OBJ_I_VOLUME, 1);
}

void
init()
{
    ::init();
    add_action(fish, "fish");
}
