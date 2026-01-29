/* created by Aridor 07/11/93 */
/*
 * 000911: Stralle @ Genesis: Before hurting people, it will hurt their
 *         boots. Generally cleaned up the code.
 * 151025  Arman @ reduced the time taken to evaporate by 9, and reduced
 *         the chance of damage to boots per burn to 20% from 100%
 *         Also reduced the potential decay from 0-2 to 0-1
 */

#pragma strict_types

inherit "/std/object";

#include "/sys/stdproperties.h"
#include <macros.h>
#include <wa_types.h>

object *gVictims;

static void hurt_everyone_around();
static void evapourate();

void
create_object()
{
    set_name("acid");
    add_name("liquid");
    set_name("pool");
    set_adj("acid");
    set_long("You are standing in a pool of acid, which slowly dissolves everything around. - including you!\n");
    add_prop(OBJ_I_WEIGHT, 20000);
    add_prop(OBJ_I_VOLUME, 20000);
    add_prop(OBJ_M_NO_GET, "You cannot get hold of the liquid.\n");
    add_prop(OBJ_I_RES_ACID, 100);

    set_alarm(itof(random(10) + 10), 0.0, evapourate);
    set_alarm(itof(random(4) + 4), 0.0, hurt_everyone_around);
}

/* Function name: evapourate
 * Description:   Removes the acid object
 */
static void
evapourate()
{
    this_object()->change_prop(CONT_I_NO_REM, 0);
    tell_room(environment(this_object()), "The liquid has evaporated " +
        "completely.\n");
    this_object()->remove_object();
}

/* Function name: hurt_it
 * Description:   Hurt a specific living in this room, gets called from
 *                hurt_everyone_around
 * Arguments:     object livin - the living
 */
void
hurt_it(object livin)
{
    object boots, co = livin->query_combat_object();
    int size, hitp = livin->query_hp();
    string str;

    if (objectp(boots = livin->query_armour(A_FEET)))
    {
        /* Magical boots which would not insentigrate in acid pools
         * would have to guard for that themselves.
         */
        if(random(5) == 1)
          boots->set_condition(boots->query_condition() + random(2));
        if (!boots->query_prop(OBJ_I_BROKEN))
        {
            /* See if they are still whole and if so do not hurt */
            tell_object(livin, "The boots you're wearing protect " +
		    "you from acid in the pool.\n");
            return;
        }
    }

    /*write ("b" + hitp);   for testing how bad the hits are*/
    if (hitp < 21)
        hitp = -random(hitp+1);
    else if (hitp < 275)
        hitp = -hitp / 2 - 1;
    else
        hitp = -125;

    /*hitpoint modifier on RES_ACID:*/
    hitp -= hitp * (livin->query_prop(OBJ_I_RES_ACID) +
        livin->query_magic_res(MAGIC_I_RES_ACID));
    /*write("a" + hitp + "\n");  for testing how bad the hits are */

    if (member_array(livin, gVictims) < 0)
        hitp /= 6;

    if (hitp > 0)
        hitp = 0;
    else
    {
        if (hitp > -20)
            str = "a little ";
        else if (hitp > -50)
            str = "partly ";
        else if (hitp > -100)
            str = "badly ";
        else
            str = "very badly ";

        tell_object(livin,"You are " + str + "dissolved by the " +
            "acid pool.\n");
    }

    tell_room(environment(livin), QCTNAME(livin) + "'s skin sizzles as " +
        livin->query_pronoun() +  " stands in the acid pool.\n", livin);

    livin->heal_hp(hitp);

    if (!livin->query_ghost() && livin->query_hp() <= 0)
        livin->do_die(this_object());

    co->cb_add_panic(-hitp / 4);
    co->cb_may_panic();
}


/* Function name: destroy_it
 * Description:   Reduce quality or destroy an object in the acid pool,
 *                the same environment as it i.e. the room.
 * Arguments:     object obje - the object
 */
void
destroy_it(object obje)
{
    if (obje->check_weapon())
    {
        if (obje->set_corroded(obje->query_corroded() + random(2)))
            tell_room(environment(obje), "The " + obje->short() +
                " is partly damaged by the acid pool.\n");
    }
    else if (obje->check_armour())
    {
        if (obje->set_condition(obje->query_condition() + random(2)))
	        tell_room(environment(obje), "The " + obje->short() +
	            " is partly damaged by the acid pool.\n");
    }
    else if ((!random(4)) && (obje->query_prop(OBJ_I_VOLUME) <= 5000) &&
        (obje->query_prop(OBJ_I_WEIGHT) <= 5000) && 
        (!obje->query_prop(MAGIC_AM_MAGIC)) && (!obje->id("coin")) )
    {
        tell_room(environment(obje), "The " + obje->short() +
            " is dissolved by the acid pool.\n");
        obje->move_all_to(environment(obje));
        obje->remove_object();
    }
}

/* Function name: hurt_everyone_around
 * Description:   Gets called in an alarm every so often to hurt everyone
 *                in the room, both livings and objects
 */
static void
hurt_everyone_around()
{
    int i, size;
    object *things;

    seteuid(getuid(this_object()));

    if (environment(this_object()))
    {
        things = all_inventory(environment(this_object()));
        for (i = 0, size = sizeof(things) ; i < size ; i++)
            if ((things[i]->query_prop(OBJ_I_RES_ACID) < random(100)) &&
                (!things[i]->query_prop(LIVE_O_STEED)))
            {
                if (things[i]->query_prop(LIVE_I_IS))
                    hurt_it(things[i]);
                else
                    destroy_it(things[i]);
            }
    }

    set_alarm(itof(random(10) + 4), 0.0, hurt_everyone_around);
}

void
set_my_victims(object *whos)
{
    gVictims = whos;
}
