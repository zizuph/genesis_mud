#pragma strict_types
/*
 * ~/tray.c
 *
 * Food tray for the bath.
 *
 * Revisions:
 *   Lucius, Jul 2017: Code Cleanups.
 *
 */
inherit "/std/container";
inherit "/lib/keep";

#include <stdproperties.h>
#include "../bath.h"

#define FOOD	(CITY + "obj/food/")


public void
fill_tray(void)
{
    object obj;

    obj = clone_object(FOOD + "iced_coffee");
    obj->set_heap_size(6);
    obj->move(this_object(), 1);   

    obj = clone_object(FOOD + "salmon");
    obj->set_heap_size(6);
    obj->move(this_object(), 1);   

    obj = clone_object(FOOD + "cucumber");
    obj->set_heap_size(6);
    obj->move(this_object(), 1);   

    obj = clone_object(FOOD + "shaved_ice");
    obj->set_heap_size(6);
    obj->move(this_object(), 1);   
}

public void
create_container(void)
{
    setuid();
    seteuid(getuid());

    set_name("tray");
    add_name("food tray");
    set_adj(({"silver","metal","engraved"}));
    set_short("silver food tray");
    set_long("A silver tray with a repeating knot pattern engraved on "+
	"the surface. ");

    add_prop(CONT_I_MAX_WEIGHT, 50000);
    add_prop(CONT_I_MAX_VOLUME, 50000);
    add_prop(CONT_I_WEIGHT, 500);
    add_prop(CONT_I_VOLUME, 500);
    add_prop(OBJ_I_VALUE, 500);
    add_prop(CONT_I_RIGID, 1);
    add_prop(CONT_I_ATTACH, 1);
}
