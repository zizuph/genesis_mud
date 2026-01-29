/* 	this is a object of the volcano

    coder(s):   Deinonychus

    history:	DD.MM.YY	what done			who did
		01.04.93	created				Deinonychus

    purpose:    none

    quests:     none
    special:    none

    to do:      none
    bug:        none known
*/


inherit "/std/weapon";
#include "weapons.h"
#include <wa_types.h>   /* Weapon and armour types */
#include <formulas.h>   /* Some handy conversion formulas */
#include <stdproperties.h>

create_weapon()
{
    set_name("knife"); 
    set_pname("knives");
    set_short("tooth knife"); 
    set_pshort("tooth knives");
    set_adj("tooth");
    set_long(BS("This knife is made of a deadly tooth of a tyrannosaurus rex. "
        + "It's quite big and sharp.\n"));
    
    set_default_weapon(
        10,                 /* Weapon hit                                   */
        10,                 /* Penetration                                  */
        W_KNIFE,            /* Weapon type                                  */
        W_SLASH | W_IMPALE, /* Damage type                                  */
        W_NONE,             /* A one hand weapon, free to choose wich hand  */
        0);                 /* The object defining the (un)wield functions  */

    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(OBJ_I_VOLUME, 250);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(10,10) + random(100) - 50);
}

