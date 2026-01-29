/*
 *      /d/Gondor/common/arm/nazgul_plate.c
 *      
 *      The non-magical platemail of the nazgul.
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
    set_name(({"chainmail"}));
	add_name("mail");
    set_pname("chainmails");
    add_pname("mails");
    add_pname("chains");
    set_adj(({"black", "chain" }));
    set_short("black chainmail");
    set_pshort("black chainmails");
    set_long("The black chainmail is made of hundreds and hundreds of "
		+ "tiny metal rings. The craftsmanship is exquisite, leaving "
		+ "almost no gaps anywhere on the armour. Across the front of "
		+ "the chainmail is a painting of a lidless eye!\n");
    set_default_armour(50, A_BODY, 0, TO);
    add_prop(OBJ_I_WEIGHT, (F_WEIGHT_DEFAULT_ARMOUR(50, A_BODY)/2) );
    add_prop(OBJ_I_VOLUME, 2500);
    add_prop(OBJ_I_VALUE, 500);
    add_prop(OBJ_M_NO_BUY, 1);
	add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
	add_prop(MAGIC_AM_ID_INFO,({
    BSN("This chainmail is both lightweight and powerful."), 10,
    BSN("Blessed with magical powers, it is more effective than a regular chainmail!"),50,
     }));
    add_prop(OBJ_S_WIZINFO, "The basic body armour of the nazgul (/d/Gondor/common/npc/blackrider).\n"
      + "It's light weight and has good stats\n");
	add_item( ({"ring", "rings"}), "You examine the rings closely and "
		+ "notice they are made of a shiny black metal, which seems both "
		+ "lightweight and strong!\n");
	add_item( ({"eye", "lidless eye", "painting"}), "The eye is red "
		+ "and all-seeing, leaving no doubt that this armour is used "
		+ "by the elite troops of Minas Morgul, or perhaps by one of "
		+ "the Nine!\n");
    
}
