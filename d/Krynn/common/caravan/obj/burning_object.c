
/*
 *      /w/vencar/caravan/obj/burning_object.c
 *
 *      The invisible object part of a burning
 *      of a person.
 *      Created by Vencar 11/09/2003
 *
 *      Copyright by Peter Bech Lund (Vencar)
 *      09/2003
 *
 *      Credits to:
 *      Calia Stoiecheio (fire elemental form)
 *      for initial design of the invisible
 *      object that here is copied.
 */

#pragma strict_types

inherit "/std/object";

#include "../wagon/wagon.h"
#include <stdproperties.h>
#include <cmdparse.h>
#include <macros.h>

object s_shadow;
int    remove_id,start_ok;
void
create_object()
{
    set_name("_krynn_burning_object");
    set_no_show();
    remove_prop(OBJ_I_VALUE);
    remove_prop(OBJ_I_VOLUME);
    remove_prop(OBJ_I_WEIGHT);

    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_GIVE, 1);
}


int
do_extinguish(string str)
{

    return 1;
}


void
init()
{
    ::init();
    add_action("do_extinguish","extinguish");
    add_action("do_roll","roll");
}

public void
remove_object()
{
    /* Remove the shadow before removing myself */
    if (!start_ok)
    {
        ::remove_object();
        return;
    }


    add_prop(OBJ_I_LIGHT, 0);

    s_shadow->remove_krynn_burning_shadow();
    remove_alarm(remove_id);
    ::remove_object();
}

void
remove_krynn_burning_shadow()
{
    remove_object();
}

int
do_roll(string str)
{
    int res;

    if (str == "over on the ground")
    {
        TP->add_fatigue(-(TP->query_max_fatigue() / 10));

        if (TP->query_fatigue() > 0)
        {
            tell_object(TP,"You desperately rolls on the ground, trying to " +
            "get rid of the fire.\n");
            tell_room(E(TP), QCTNAME(TP) + " rolls around on the ground "+
            "desperately trying to get rid of the fire.\n" , TP);

            res = TP->query_magic_res(MAGIC_I_RES_FIRE);
            res = min(res, 100);
            res += random(100);
            if (res > random(100) )
            {
                if (s_shadow->diminish_fire() < 1)
                    remove_krynn_burning_shadow();
            }
        }
        else
        {
            tell_object(TP,"You are too tired to do that.\n");
        }

        return 1;
    }

    NF("Roll over on the ground perhaps?\n");
    return 0;
}

public int
start(object player,int firelevel, int firestrength, float firetime)
{

    setuid();
    seteuid(getuid());
    start_ok = 0;

    /* guy is already on fire? */
    if (player->query_burning_shadow())
    {
        remove_object();
        return 0;
    }
    tell_object(player, "OUCH it hurts!\n");
    add_prop(OBJ_I_LIGHT, 1);
    s_shadow=clone_object(OBJ + "burning_shadow");
    s_shadow->shadow_me(player);
    s_shadow->start_burning_shadow(firelevel, firestrength);
    remove_id = set_alarm(firetime, 0.0,"remove_krynn_burning_shadow");
    start_ok = 1;
    return 1;

}


