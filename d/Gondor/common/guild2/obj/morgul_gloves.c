/*
 *	/d/Gondor/common/arm/herb_gloves2.c
 *
 *	Copied from /d/Krynn/common/armours/herb_gloves.c
 *	Herbalist's gloves by Teth Jan 22 1997
 *
 *	Olorin, 30-Jun-1997
 *      --  Modified to be a more expensive nicer pair of gloves.
 *          Morbeche, Feb 10 2000
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
    set_name("gloves");
    add_name(({"armour","pair of gloves","pair of leather gloves",
	"pair of black gloves","pair of black leather gloves",
	"black gloves"}));
    set_pname("gloves");
    add_pname(({"armours","pairs of glove","pairs of leather gloves",
	"pairs of black gloves","pairs of black leather gloves"}));
    set_adj("black");
    add_adj(({"leather","herbing"}));
    set_short("pair of black leather gloves");
    set_pshort("pairs of black leather gloves");
    set_long("These black leather gloves are herbing tools of "+
      "exceptional quality.  " +
      "The leather is very supple and thin, providing " +
      "little in the way of protection from attack, but giving " +
      "the wearer ample defense against the poisons and oils which " +
      "are known to cover the herbs of the realm.\n"+
      "There is a picture of a red eye on the palm.\n");

    set_ac(1);
    set_am(({0, 1, -1}));
    set_at(A_HANDS);
    set_keep(1);
    add_prop(OBJ_I_WEIGHT, 150);
    add_prop(OBJ_I_VOLUME, 200);
    add_prop(OBJ_I_VALUE, 11 * F_VALUE_ARMOUR(1) - 9);

// removed Sep 16 2017 per AOB request, Finwe
//    add_prop("_obj_i_ignore_recovery", 1);
}

