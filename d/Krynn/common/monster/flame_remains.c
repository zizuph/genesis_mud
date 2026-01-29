/* created by Aridor 07/11/93 */
/*
 * Typecasted and indented by Stralle @ Genesis 000926
 */

#pragma strict_types

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#define DIS(xx)  xx->query_base_stat(SS_DIS)

object *victims;

void evapourate();
void hurt_everyone_around();

void
create_object()
{
    set_name("flame");
    add_name("fire");
    add_name("humanoid");
    add_name("shape");
    set_pname("flames");
    add_pname("fires");
    add_pname("humanoids");
    add_pname("shapes");
    set_adj("hot");
    add_adj("burning");
    set_short("hot burning flame shaped like a humanoid");
    set_pshort("hot burning flames shaped like humanoids");
    set_long("You are standing engulfed by this fire, which slowly " +
        "burns everything around. - including you!\n");

    add_prop(OBJ_I_WEIGHT, 20);
    add_prop(OBJ_I_VOLUME, 2000000);
    add_prop(OBJ_M_NO_GET, "You cannot get hold of the flames.\n");
    add_prop(OBJ_I_HAS_FIRE, 1);
    add_prop(OBJ_I_LIGHT, 1);
    add_prop(OBJ_I_RES_FIRE, 100);

    set_alarm(itof(random(10) + 23), 0.0, evapourate);
    set_alarm(itof(random(4) + 4), 0.0, hurt_everyone_around);
}

void
evapourate()
{
    this_object()->change_prop(CONT_I_NO_REM, 0);
    if (!environment(this_object())->query_prop(OBJ_I_HAS_FIRE))
        tell_room(environment(this_object()), "The flames slowly burn " +
            "out.\n");

    this_object()->remove_object();
}

void
hurt_it(object livin)
{
    object co;
    int hitp;
    string str;

    hitp = livin->query_hp();
    /*write ("b" + hitp);   for testing how bad the hits are*/
    co = livin->query_combat_object();

    if (hitp < 21)
        hitp = -random(hitp+1);
    else if (hitp < 275)
        hitp = -hitp / 2 - 1;
    else
        hitp = -125;

    /*hitpoint modifier on RES_FIRE:*/
    hitp -= hitp * (livin->query_prop(OBJ_I_RES_FIRE) +
        livin->query_magic_res(MAGIC_I_RES_FIRE));
    /*write("a" + hitp + "\n");  for testing how bad the hits are */

    if (member_array(livin,victims) < 0)
        hitp /= 6;

    if (hitp > 0)
        hitp = 0;
    else
    {
        if (hitp > -20)
            str = "slightly ";
        else if (hitp > -50)
            str = "somewhat ";
        else if (hitp > -100)
            str = "";
        else
            str = "badly ";

        tell_object(livin,"You are " + str + "burnt from the flames.\n");
    }

    tell_room(environment(livin), QCTNAME(livin) + " is engulfed in " +
        "the flames.\n", livin);

    // Setting a cap on damage
    // Since we had a problem with players getting negative resistance values
    // and dying instantly.
    if(hitp < -250)
    {
        hitp = -250;
    }
    livin->heal_hp(hitp);

    hitp = -(hitp * 50 / DIS(livin));
    hitp = (hitp > 60 ? 60 : hitp);
    co->cb_add_panic(hitp);
    co->cb_may_panic("north");
    if (!livin->query_ghost() && livin->query_hp() <= 0)
        livin->do_die(this_object());
}

void
destroy_it(object obje)
{
    tell_room(environment(obje), "The " + obje->short() + " is " +
        "destroyed by the fire.\n");

    obje->move_all_to(environment(obje));
    obje->remove_object();
}

void
hurt_everyone_around()
{
    int i;
    object *things;

    setuid();
    seteuid(getuid(this_object()));
    things = all_inventory(environment(this_object()));

    for (i = 0; i < sizeof(things); i++)
    {
        if (things[i]->query_prop(OBJ_I_RES_FIRE) < random(100))
        {
            if (things[i]->query_prop(LIVE_I_IS))
            {
                hurt_it(things[i]);
            }
            else if ((!random(4)) &&
                (things[i]->query_prop(OBJ_I_VOLUME) <= 5000) &&
                (things[i]->query_prop(OBJ_I_WEIGHT) <= 5000) &&
                (!things[i]->query_prop(MAGIC_AM_MAGIC)))
            {
                destroy_it(things[i]);
            }
        }
    }

    set_alarm(itof(random(10) + 4), 0.0, hurt_everyone_around);
}

void
set_my_victims(object *whos)
{
    victims = whos;
}
