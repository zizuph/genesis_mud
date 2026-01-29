/* Piwafwi Pocket
 * Finwe, March 2008
 */
#pragma strict_types

inherit "/std/container";
//inherit "/w/finwe/shelf.c";

#include "/d/Faerun/defs.h"
#include <ss_types.h>


void create_container() 
{
    setuid(); 
    seteuid(getuid());

    if(!IS_CLONE)
        return;

    set_name("pocket");
    add_name("_piwafwi_pocket");
    set_adj(({"small","hidden"}));
    set_short("small hidden pocket");
    set_long("This is a small hidden pocket sewn into the piwafwi. It is small enough to hold coins, gems and other small objects. It looks durable and hidden from view.\n");

    add_prop(CONT_I_IN,             1);
    add_prop(CONT_I_RIGID,          0);
//    add_prop(CONT_I_TRANSP,         0);
    add_prop(CONT_I_CLOSED,         0);
    add_prop(CONT_I_WEIGHT,       300);
    add_prop(CONT_I_VOLUME,       300);
    add_prop(CONT_I_MAX_WEIGHT, 18000);
    add_prop(CONT_I_MAX_VOLUME,  9000);
    add_prop(OBJ_I_VALUE,          96);

//    set_no_show_composite(1);

}
