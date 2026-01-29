/*
 *      /d/Gondor/common/arm/nazgul_basic_helm.c
 *
 *      The non-magical helm of the nazgul.
 *		--Raymundo, March 2020
 *
 */
#pragma strict_types
inherit "/std/armour.c";

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"

void
create_armour()
{
    set_name(({"helm", "helmet" }));
    set_pname("helms");
    add_pname("helmets");
    set_short("black steel helm");
    set_pshort("black steel helms");
    set_adj(({"steel", "black", }));
    set_long(BSN("This helmet is completely black, showing neither scratch "
		+ "nor dent. It is made of thick black steel and bears the imprint "
		+ "of an all-seeing eye on its visor. The top of the helm has been fashioned "
		+ "to resemble a crown.\n"));
    set_default_armour(50, A_HEAD, ({ 0, 0, 0, 0}), TO);
    add_prop(OBJ_I_WEIGHT, 2500);
    add_prop(OBJ_I_VOLUME,  680);
    add_prop(OBJ_I_VALUE, 500);
	add_prop(OBJ_M_NO_BUY, 1);
	add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
	add_prop(MAGIC_AM_ID_INFO,({
    BSN("This helm is both lightweight and powerful."), 10,
    BSN("Blessed with magical powers, it is more effective than a regular helmet!"),50,
     }));
    add_prop(OBJ_S_WIZINFO, "The basic helmet of the nazgul (/d/Gondor/common/npc/blackrider).\n"
      + "It's light weight and has good stats\n");


	add_item( ({"visor", "stamp", "stamp of minas morgul"}), 
		"The visor attaches "
		+ "to the helm with a strong rivet. It is designed to "
		+ "both protect the wearer's face and obscure their appearance. "
		+ "On the side of the visor you see an imprint of an "
		+ "all-seeing eye.\n");
	
}