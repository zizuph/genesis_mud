/*
 * /d/Gondor/minas/obj/denethor_robe.c
 *
 * A white robe for Denethor II
 *
 * Add/remove code structure borrowed from Gwyneth
 *
 * Alto 23 April 2001
 *
 */
 
inherit "/std/armour";
inherit "/lib/keep";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Gondor/defs.h"

int worn;
object actor;


void
create_armour()
{
    set_name("robe");
    set_adj("stately");
    add_adj("white");
    set_short("stately white robe");
    set_pshort("stately white robes");
    set_pname("robes");
    set_long("A formal white robe made of the finest linen.\n");
    set_ac(0);
    set_at(A_BODY);
    add_prop(OBJ_I_VALUE, 300);
    add_prop(OBJ_I_VOLUME, 300);
    add_prop(OBJ_I_WEIGHT, 300);
    set_af(TO);
    seteuid(getuid(TO));
    worn = 0;
}

mixed
wear(object what)
{
    if (what != TO)
        return 0;

    write("You pull the stately white robe over your shoulders.\n");
    say(QCTNAME(TP) + " pulls on the stately white robe.\n");
    worn = 1;
    return 1;
}

mixed
remove(object what)
{
    if (what != TO || !TP)
        return 0;

    write("You slide the stately white robe off your shoulders and "
        + "over your head.\n"); 
    say(QCTNAME(TP) + " removes the stately white robe.\n"); 
    worn = 0;
    return 1;
}

void
init()
{
   ::init();
   add_action("smooth_robe", "smooth");
}

int
smooth_robe(string str)
{

    actor = TP;

    if (!strlen(str))
        NF0("Smooth what?\n");

    if (str != "waistcoat")
        NF0("What do you want to smooth?\n");
    switch (random(2))
    {
    case 0:
        write("You smooth a wrinkle in the stately white robe.\n");
        say(QTNAME(actor) + " smooths a wrinkle in the stately white robe.\n");
        break;
    case 1:
        write("You adjust the stately white robe until the wrinkles "
            + "smooth out of it.\n");
        say(QTNAME(actor) + " adjusts the stately white robe until the "
            + "wrinkles smooth out of it.\n");
        break;
    default:
        break;
    }
        return 1;

}

