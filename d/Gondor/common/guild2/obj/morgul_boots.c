/*
 * A pair of expensive boots.  More for looks than protection.
 * Coded by Morbeche March 2000
 *
 */
#pragma strict_types

inherit "/std/armour";
inherit "/lib/keep";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>

void
create_armour()
{
    set_name("boots");
    add_name(({"armour","pair of boots","pair of leather boots",
	"pair of black boots","pair of black leather boots",
	"black boots"}));
    set_pname("boots");
    add_pname(({"armours","pairs of boots","pairs of leather boots",
	"pairs of black boots","pairs of black leather boots"}));
    set_adj("black");
    add_adj(({"leather"}));
    set_short("pair of black leather boots");
    set_pshort("pairs of black leather boots");
    set_long("These black leather boots are of exceptional quality.  " +
      "The leather has been treated to be mostly stiff and durable, " +
      "but flexible in the necessary areas.  " +
      "The bottom of the boot is comprised of a metal plate attached to " +
      "a thick padding of leather.  While not much in the way of "+
      "protection, the boots will hold up well during travel.  \n"+
      "There is a picture of a red eye on the outer side of each boot.\n");

    set_ac(5);
    set_am(({0, 1, -1}));
    set_at(A_FEET);
    set_keep(1);
    add_prop(OBJ_I_WEIGHT, 400);
    add_prop(OBJ_I_VOLUME, 2500);
    add_prop(OBJ_I_VALUE, 11 * F_VALUE_ARMOUR(1) - 9);

// removed Sep 16 2017 per AOB request, Finwe
//    add_prop("_obj_i_ignore_recovery", 1);
}

