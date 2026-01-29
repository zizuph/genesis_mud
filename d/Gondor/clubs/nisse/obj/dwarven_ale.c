/*
 *  /d/Gondor/clubs/nisse/obj/dwarven_ale.c
 *
 *  The glass of dwarven ale.
 *
 *  Deagol, March 2003
 */

inherit "/std/drink";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

void
create_drink()
{
    ::create_drink();

    set_name("ale");
    add_name("glass");
    set_adj("dwarven");
    set_pname("ales");
    add_pname("glasses");
    set_short("glass of dwarven ale");
    set_pshort("glasses of dwarven ale");
    set_long("This dark dwarven ale is very strong, more like a whiskey " +
        "than regular ale. It is not for those of weak constitution as " +
        "this powerful drink could leave those who are not of stout heart " +
        "napping by the fire while the strong go off to fight the " +
        "battles.\n");

    add_prop(OBJ_I_VALUE, 75);
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);

    set_soft_amount(100);
    set_alco_amount(40);
    
    setuid();
    seteuid(getuid());
}
