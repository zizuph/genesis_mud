/*
 *  /d/Gondor/morgul/city/mm_stables/obj/boots.c
 *
 *  The riding boots made for the stables of Minas Morgul.
 *
 *  Deagol, August 2002
 */

inherit "/std/armour";

#include <stdproperties.h>

#include "../mm_stables.h"

void
create_armour()
{
    ::create_armour();
    
    set_name("boots");
    set_pname("boots");
    remove_pname("bootses");
    add_name("pair of boots");
    add_pname("pairs of boots");
    remove_pname("pair of bootses");
    set_adj(({"pair", "riding"}));
    set_short("pair of riding boots");
    set_pshort("pairs of riding boots");
    set_long("The pair of riding boots is orderly stored in the rack.\n");

    MM_STABLES_NO_GET;    
}
