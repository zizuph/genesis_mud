/**********************************************************************
 * - axe_rack.c                                                     - *
 *
 * - A rack for holding axes for Gladiator guild.                   - *
 *
 * - Created by Damaris@Genesis 09/2005                             - *
 * April 2013 (Serpine) - Edited
 * January 2018 (Mirandus) - Typo Fixed
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
    set_name("rack");
    set_adj("solid");
    add_adj("wooden");
    add_adj("axe");
    set_short("solid wooden axe rack");
    set_long("This rack is obviously meant to hold the axes prized " +
        "by the Gladiators of Athas. There are slots for axes of " +
        "all different shapes and sizes, even those of exotic type.\n" +
        "You may <sort axe rack> to organize the contents.\n");
        
    set_no_show_composite(1);
        
    add_prop(CONT_I_WEIGHT, 200000);
    add_prop(CONT_I_VOLUME, 50000);
    add_prop(CONT_I_MAX_WEIGHT, 1000000);
    add_prop(CONT_I_MAX_VOLUME, 1000000);
    add_prop(CONT_I_RIGID, 1);
    add_prop(OBJ_I_NO_GET, "It is firmly mounted to the wall.\n");
}



public int
prevent_enter(object ob)
{
        if (IS_WEAPON_OBJECT(ob) && (ob->query_wt() == W_AXE))
            return 0;

        write("This rack is only for axes.\n");
        return 1;
}
