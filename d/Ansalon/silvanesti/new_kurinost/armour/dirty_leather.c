/*
 * dirty_leather.c
 *
 * A rather dirty leather armour that can be found in a garbage pile.
 *
 * Copyright (C): Kellon, oktober 2012
 *                Poul Erik Jensen
 *
 *    The original armour was not created by me. I am just adding a
 *    few things to make it dirty. ;-)
 *
 */
#pragma strict_types

// I N C L U D E D   F I L E S
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "../local.h"

// I N H E R I T E D   F I L E S
inherit "/d/Krynn/solamn/splains/obj/barmour3";

// D E F I N I T I O N S

// G L O B A L   V A R S

// P R O T O T Y P E S

// P U B L I C   F U N C T I O N S
/*
 *  FUNCTION : create_armour
 *  Arguments:
 *  Returns  :
 * 
 *  Basic creation of the armour.
 *
 */
public void
create_armour()
{
    set_name("armour");
    set_pname("armours");
    set_adj(({"blue","leather"}));
    set_color("green");

    add_adj("dirty");
    set_short("dirty green leather armour");
    set_long("Stinking quite badly, this studded leather shirt " +
        "seems to have been covered in dried grey-brown hobgoblin " +
        "dung. Giving only basic protection, it shows signs of " +
        "having been used quite a lot and now has a few broken " +
        "straps here and there. Beneath the muck, you notice some " +
        "faded green markings.\n");
    add_item(({ "markings", "green markings", "faded markings", 
        "faded green markings" }), "The markings are quite faded " +
        "and covered in dried dung, but it seems to be the green " +
        "markings of a dragonarmy.\n");
    set_default_armour(15);
    add_prop(OBJ_I_COLORABLE, 1);
}
