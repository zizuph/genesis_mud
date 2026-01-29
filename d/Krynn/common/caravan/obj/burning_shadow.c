/*
 *      /w/vencar/caravan/obj/burning_shadow.c
 *
 *      A shadow that sets people on fire.
 *      Created by Vencar 09/09/2003
 *
 *      Copyright by Peter Bech Lund (Vencar)
 *      09/2003
 *
 *      Credits to:
 *      Shire for original design in their
 *      puddle files (very dirty adjectives)
 *      /d/Shire/open/dirty_puddle.c +
 *      /d/Shire/open/dirty_shadow.c
 */
#pragma strict_types

inherit "/std/shadow";

#include "../wagon/wagon.h"
#include <macros.h>
#include <terrain.h>
void remove_krynn_burning_shadow();

int hurt_id,
    msg_id,
    firelevel,
    fire_strength;

string str;

public string
query_my_adjectives()
{

    switch (firelevel) {
        case 1:
        {
            str = "slightly-smouldering";
            break;
        }
        case 2:
        {
            str = "somewhat-smouldering";
            break;
        }
        case 3:
        {
            str = "flaming";
            break;
        }
        case 4:
        {
            str = "fiercely-burning";
            break;
        }
        case 5:
        {
            str = "wildly-burning";
            break;
        }

    }

    return str;
}

/***************** OVERRIDE OF NORMAL FEATURES ****************/

varargs public mixed
query_adj(int arg)
{
    return ({query_my_adjectives()});
}

public string *
query_adjs()
{
    return ({query_my_adjectives()});
}

public int
adjectiv_id(string str)
{
    return (member_array(str, ({query_my_adjectives()})) >= 0);
}

string *
parse_command_adjectiv_id_list()
{
    return ({query_my_adjectives()}) + ({query_shadow_who()->
                parse_command_adjective_id_list()});
}

/******************* START/STOP + BURN functions ***************/

int query_burning_shadow()
{
    return 666;
}

int
diminish_fire()
{
    return --firelevel;
}



void
check_water(object victim)
{
    if (E(victim)->query_prop(OBJ_I_CONTAIN_WATER) ||
        E(victim)->query_prop(ROOM_I_TYPE) == ROOM_IN_WATER)
    {
        tell_object(victim,"Through the pain of the flames, " +
                 "you hear the sizzling sound of the fire being extinguished " +
                 "in the water around you.\n");
        tell_room(E(victim), "A sizzling sound comes from near " +
         QCTNAME(victim) + " the fire is extinguished on the water " +
         "nearby.\n", victim);
         /* take 2 levels of fire off */
         diminish_fire();
                if (diminish_fire() < 1)
                    remove_krynn_burning_shadow();
        return;
    }

    if (E(victim)->query_prop(ROOM_I_TYPE) == ROOM_UNDER_WATER ||
        E(victim)->terrain_includes_any(TERRAIN_UNDERWATER))
    {
        tell_object(victim,"Through the pain of the flames, " +
                 "you hear the sizzling sound of the fire being extinguished " +
                 "in the water all around you.\n");
        tell_room(E(victim), "A sizzling sound comes from near " +
         QCTNAME(victim) + " the fire is extinguished in the water." +
         "\n", victim);

        remove_krynn_burning_shadow();
        return;
    }

}
//345678901234567890123456789012345678901234567890123456789012345678901234567890
void
hurt_shadow_owner()
{
    object victim;

    victim = query_shadow_who();
    remove_alarm(hurt_id);
    if (random(100) > 50 && firelevel < 5)
    {

        tell_object(victim,"The fire spreads further on you.\n");
        tell_room(E(victim), QCTNAME(victim) + " is " +
        "even more on fire.\n" , victim);
        firelevel = min(++firelevel,5);
    }
    check_water(victim);
    (OBJ + "burning_damage")->hurt_player(victim, fire_strength *
    firelevel);
    hurt_id = set_alarm(itof(random(10) + 4), 0.0, hurt_shadow_owner);
}

void
remove_krynn_burning_shadow()
{
    tell_object(query_shadow_who(),"The fire goes out.\n");
    tell_room(E(query_shadow_who()), "The fire surrounding " + QCTNAME(
        query_shadow_who()) + " slowly dimishes and goes out.\n" ,
        query_shadow_who ());
    remove_shadow();
}

void
start_burning_shadow(int fire, int firestrength)
{
    tell_object(query_shadow_who(),"You start burning!\n");
    tell_room(E(query_shadow_who()), QCTNAME(query_shadow_who()) +
    " starts burning like a torch!\n" , query_shadow_who());
    firelevel = min(fire,5);
    fire_strength = firestrength;
    hurt_id = set_alarm(itof(random(10) + 4), 0.0, hurt_shadow_owner);
}

