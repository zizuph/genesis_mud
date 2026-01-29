/*
 * /d/Gondor/minas/obj/white_rod.c
 *
 * The White Rod of the Stewards of Gondor
 *
 * Alto 23 April 2001
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
    set_name("rod");
    add_name("white rod");
    set_adj("white");
    set_short("white rod");
    set_pshort("white rods");
    set_pname("rods");
    set_long("A white rod with a golden knob. This is the rod of "
        + "the Stewards of Gondor\n");
    add_item(({"knob", "golden knob"}), "It caps the end of the "
        + "rod. Beyond its obvious value, it is plain and unadorned.\n");
    set_default_weapon(20, 27, W_CLUB, W_BLUDGEON, W_ANYH, 0);

    add_prop(OBJ_M_NO_STEAL, 1);
    add_prop(OBJ_I_WEIGHT, 10000);
    add_prop(OBJ_I_VOLUME, 4300);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(20,27)+random(200)-100);
}

void
init()
{
   ::init();
   add_action("rap_rod", "rap");
}

int
rap_rod(string str)
{

    actor = TP;

    if (!strlen(str))
        NF0("Rap what?\n");

    if (str != "rod")
        NF0("What do you want to rap?\n");
    switch (random(2))
    {
    case 0:
        write("You absentmindedly rap the white rod against your hand.\n");
        say(QCTNAME(actor) + " raps the rod against " 
            + actor->query_possessive() + " hand.\n");
        break;
    case 1:
        write("You carelessly rap the golden knob of the white rod against "
            + "the floor.\n");
        say(QCTNAME(actor) + " carelessly raps the golden knob of the white "
            + "rod against the floor.\n");
        break;
    default:
        break;
    }
        return 1;

}
