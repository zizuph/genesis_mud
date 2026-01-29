/*
 *  /d/Gondor/morgul/city/mm_stables/obj/oats.c
 *
 *  A bag of oats for the horses of Minas Morgul.
 *
 *  Deagol, October 2002
 *
 *  Upped the amount to 100 since one horse before could eat 200 bags... (Toby, jan 2007)
 */

inherit "/std/food";

#include <stdproperties.h>
#include <macros.h>

#include "/d/Gondor/defs.h"

void
create_food()
{
    ::create_food();
    
    set_name(({"bag", "oats"}));
    set_pname("bags");
    set_adj("leather");
    set_short("leather bag of oats");
    set_pshort("leather bags of oats");
    set_long("You look closer at the leather bag of oats. It is just " +
             "a bag. Made of leather, though.\n");
    set_amount(100);
    add_prop(OBJ_I_VALUE, 1200);
    add_prop(OBJ_I_WEIGHT, 300);
    add_prop(OBJ_I_VOLUME, 400);
}

init()
{
    ::init();
}
