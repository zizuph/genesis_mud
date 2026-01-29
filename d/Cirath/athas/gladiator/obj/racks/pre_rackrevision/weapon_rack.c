/**********************************************************************
 * - weapon_rack.c                                                  - *
 * - A rack for holding weapons that are not weapons for Gladiator     - *
 * - Guild.                                                         - *
 * - Created by Damaris@Genesis 09/2005                             - *
 **********************************************************************/
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
	set_pname("racks");
	set_adj("weapon");
	set_short("weapon rack");
	set_pshort("weapon racks");
	set_long("This rack is obviously meant to hold and "+
	"store weapons of all different shapes and sizes. You "+
	"may <sort weapon rack>.\n");
	
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
	int weapon;
        
	if (IS_WEAPON_OBJECT(ob) && (ob->query_wt() != W_AXE))
            return 0;

        write("This " + short() + " is not for axes or armours.\n");
        return 1;
}
