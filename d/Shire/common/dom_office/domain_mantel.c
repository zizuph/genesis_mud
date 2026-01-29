/* 
 * Fireplace mantel for domain office
 * Finwe, April 2005
 */
#pragma strict_types

//inherit "/std/container";
inherit "/w/finwe/shelf.c";

#include "/d/Shire/sys/defs.h"
#include <ss_types.h>

object mantel;

void add_stuff()
{
    object bottle, corkscrew, letter_o;
    int count;
/*    
    if(!present("_esgaroth_bottle_", mantel))
        clone_object("/d/Shire/esgaroth/objects/bottle")->move(this_object(), 1);

    if(!present("opener", mantel))
        clone_object("/d/Shire/common/dom_office/letter_o")->move(this_object(), 1);
    
    if(!present("corkscrew", mantel))
        clone_object("/d/Shire/common/dom_office/corkscrew")->move(this_object(), 1);
*/
    return;
}

void create_surface() 
{
    setuid(); 
    seteuid(getuid());

    if(!IS_CLONE)
        return;

    set_name("mantle");
    set_adj(({"long", "wide"}));
    set_short("long wide mantle");
    set_long("This is a long, wide mantle. It is made of granite and " +
        "sits above the fireplace.\n");

    remove_prop(CONT_I_TRANSP);
    add_prop(CONT_I_WEIGHT, 50000);
    add_prop(CONT_I_VOLUME, 500000);
    add_prop(OBJ_I_VALUE, 0);
    add_prop(CONT_I_RIGID, 1);
    add_prop(OBJ_M_NO_GET, "You can't take the mantle.\n");
    add_prop(CONT_I_ATTACH, 1);

    set_no_show_composite(1);
    add_stuff();
}
