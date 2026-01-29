/* 
 * Fireplace mantel
 * This is an example of how to clone items into a container,
 * in this case, a fireplace mantel.
 * -- Finwe, October 2007
 */

#pragma strict_types

inherit "/d/Faerun/examples/obj/shelf.c";

#include "/d/Faerun/defs.h"
#include <ss_types.h>

void add_stuff()
{
    object obj1, obj2;
    int count;

    for (count = 0; count < 2; count++)
    {
        clone_object("/d/Faerun/examples/obj/bottle")->move(this_object(), 1);
    }
}

void create_surface() 
{
    setuid(); 
    seteuid(getuid());

    if(!IS_CLONE)
        return;

    set_name("mantel");
    add_name("GH_mantel");
    set_adj(({"east","wide","wood","sturdy"}));
    set_short("long mantel");
    set_long("This is a long, wide mantel. It is made of granite and sits above the fireplace. ");

    remove_prop(CONT_I_TRANSP);
    add_prop(CONT_I_MAX_WEIGHT, 500000);
    add_prop(CONT_I_MAX_VOLUME, 500000);
    add_prop(CONT_I_WEIGHT, 100000);
    add_prop(CONT_I_VOLUME, 100000);
    add_prop(OBJ_I_VALUE, 1934);
    add_prop(CONT_I_RIGID, 1);
    add_prop(OBJ_M_NO_GET, "You can't take the mantel.\n");
    add_prop(CONT_I_ATTACH, 1);

    set_no_show_composite(1);
    add_stuff();

}
