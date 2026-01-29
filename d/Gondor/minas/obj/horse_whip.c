/*
 * /d/Gondor/minas/obj/horse_whip.c
 *
 * Whip carried by the Master of the Royal Stables
 *
 * Alto 16 April 2001
 *
 */

inherit "/std/weapon";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>
#include "/d/Gondor/defs.h"


object actor;


void
create_weapon()
{
    set_name(({ "horse-whip", "weapon", "whip" }));
    set_pname("horse-whips");
    add_pname("whips");
    set_short("long leather horse-whip");
    set_pshort("long leather horse-whips");
    set_long("A long horse-whip made out of stiff leather. Although it "
        + "seems designed for training horses, it might make a reasonable "
        + "weapon in a pinch.\n");
    set_adj("horse");
    add_adj(({ "long", "leather"}));
    set_default_weapon(20, 27, W_CLUB, W_BLUDGEON, W_ANYH, 0);
    add_prop(OBJ_I_WEIGHT, 10000);
    add_prop(OBJ_I_VOLUME, 4300);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(20,27)+random(200)-100);
}

void
init()
{
   ::init();
   add_action("crack_whip", "crack");
}

int
crack_whip(string str)
{

    actor = TP;

    if (!strlen(str))
        NF0("Crack what?\n");

    if (str != "whip")
        NF0("What do you want to crack?\n");
    switch (random(2))
    {
    case 0:
        write("Crack! You give the horse-whip a loud snap.\n");
        say("Crack! " + QTNAME(actor) + " gives the horse-whip a loud snap.\n");
        break;
    case 1:
        write("Fffffft! You didn't snap it hard enough to produce a crack.\n");
        say("Fffffft! " + QTNAME(actor) + " doesn't snap the horse-whip hard "
            + "enough to make a crack.\n");
        break;
    default:
        break;
    }
        return 1;

}
