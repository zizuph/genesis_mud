/*********************************************************************
 * - table.c                                                       - *
 * - Table that sits in the lobby of the Ladies Club.              - *
 * - Created by Damaris@Genesis 5/2003                             - *
 *********************************************************************/


inherit "/std/container";
#include <stdproperties.h>


void
create_container()
{
    set_name("table");
    set_adj(({"large", "oval"}));
    set_short("large oval table");
    set_long("A large oval table made from cherry wood.\n");
    add_prop(OBJ_I_NO_GET, 1);
    add_prop(CONT_I_ATTACH, 1);
    add_prop(OBJ_I_VOLUME, 5000);
    add_prop(OBJ_I_WEIGHT, 9000);
    add_prop(CONT_I_MAX_WEIGHT, 100000);
    add_prop(CONT_I_MAX_VOLUME, 1000000);
}
