/*Simple Shaman's Medicine Stick
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

#define HIT 38
#define PEN 38

int volume;

void 
create_weapon()
{
    set_name("whip");
	add_name("club");
	set_adj("long");
    add_adj("black");
    set_short("long black whip");
    set_pshort("long black whips");
    set_long("This is the whip of a cruel slave driver. It has a thick black leather handle, and a cord made of hard leather. It is nearly as long as your arm span, and could certainly inflict some pain.\n");
    set_default_weapon(HIT, PEN, W_CLUB, W_SLASH, W_RIGHT);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(PEN, W_CLUB));
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(HIT, PEN));
    add_prop(OBJ_I_VOLUME, 2750);
}
