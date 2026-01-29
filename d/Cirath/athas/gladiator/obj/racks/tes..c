/**********************************************************************
 * - armour_rack.c                                                  - *
 *
 * - A rack for holding armours for Gladiator guild.                - *
 *
 * - Created by Damaris@Genesis 09/2005                             - *
 * April 2013 (Serpine) - Made into hooks for easier access
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
    set_name("hook");
    add_name("hooks);
    set_adj("armour");
    set_short("armour hooks");
    set_long("These hooks are for storing armours of all different " +
        "shapes and sizes. While made of iron it is likely stealing " +
        "them in so public a place would only earn you a quick death.\n"+
        "You may <sort armour hooks> to organise the contents.\n");
        
        set_no_show_composite(1);
        
        add_prop(CONT_I_WEIGHT, 200000);
        add_prop(CONT_I_VOLUME, 50000);
        add_prop(CONT_I_MAX_WEIGHT, 1000000);
        add_prop(CONT_I_MAX_VOLUME, 1000000);
        add_prop(CONT_I_RIGID, 1);
        add_prop(OBJ_I_NO_GET, "Even a half-giant couldn't lift this "+
        "thing.\n");
}



public int
prevent_enter(object ob)
{
        int armour;
        
        if (IS_ARMOUR_OBJECT(ob))
            return 0;
        write("This " + short() + " is not for armours only.\n");
        return 1;
}
