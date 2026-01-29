/**********************************************************************
 * - armour_rack.c                                                  - *
 * - A rack for holding armours for Gladiator guild.                - *
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
	set_adj("armour");
	set_short("armour rack");
	set_pshort("armour racks");
	set_long("This rack is obviously meant to hold and "+
	"store armours of all different shapes and sizes. You "+
	"may <sort armour rack>.\n");
	
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
