/**********************************************************************
 * - armour_rack.c                                                  - *
 *
 * - A rack for holding armours for Gladiator guild.                - *
 *
 * - Created by Damaris@Genesis 09/2005                             - *
 * April 2013 (Serpine) - Made into closet for cleaner access
 *********************************************************************
 */
#pragma strict_types
#pragma save_binary

#include <files.h>
#include <formulas.h>
#include <wa_types.h>
#include "../defs.h"
inherit RACK_BASE;

public void
create_rack()
{
    set_name("closet");
    add_name("hooks");
    add_name("hook");
    remove_name("rack");
    set_adj("armour");
    set_short("armour closet");
    set_long("This closet has hooks for storing armours of all " +
        "different shapes and sizes. While the hooks are iron it is " +
        "likely that stealing them in so public a place would only earn " +
        "you a quick death.\n"+
        "You may <sort armour closet> to organise the contents.\n");
        
    set_no_show_composite(1);
        
    add_prop(CONT_I_WEIGHT, 200000);
    add_prop(CONT_I_VOLUME, 50000);
    add_prop(CONT_I_MAX_WEIGHT, 1000000);
    add_prop(CONT_I_MAX_VOLUME, 1000000);
    add_prop(CONT_I_RIGID, 1);
    add_prop(OBJ_I_NO_GET, "This is firmly bolted to the wall.\n");
}

public int
prevent_enter(object ob)
{
    int armour;
        
    if (IS_ARMOUR_OBJECT(ob))
        return 0;
    write("This closet is for armour only.\n");
    return 1;
}
