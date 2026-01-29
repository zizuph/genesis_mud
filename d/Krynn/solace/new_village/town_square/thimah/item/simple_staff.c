/*
*Simple Shaman's Medicine Stick
*Created By Leia
*05/04/2005
*/

/*
** Last Updated By:
** Leia
** July 1, 2005
*/

inherit "/std/weapon";

#include "/d/Ansalon/common/defs.h"
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>

#define HIT 36
#define PEN 36

int volume;

void create_weapon(){
        set_name("stick");
	add_name("polearm");
	add_name("staff");
        add_name("medicine stick");
	set_adj("medicine");
        add_adj("simple");
        set_short("simple medicine stick");
        set_pshort("simple medicine sticks");
        set_long("This is the medicine stick of a great shaman. It is long and made of an oak branch. On the end are feathers and a pouch of some sort. Best not to open the pouch for fear of what sort of hex may have been placed upon it.\n");
        set_default_weapon(HIT, PEN, W_POLEARM, W_IMPALE | W_BLUDGEON, W_BOTH);
        add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(PEN, W_POLEARM));
        add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(HIT, PEN));
        add_prop(OBJ_I_VOLUME, 2000 + random(800));}