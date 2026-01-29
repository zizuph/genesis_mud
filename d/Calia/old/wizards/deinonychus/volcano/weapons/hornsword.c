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
    set_name("sword"); 
    set_pname("swords");
    set_short("horn sword"); 
    set_pshort("horn swords");
    set_adj("horn");
    set_long(BS("Someone has made this sword of a horn of a triceratops. "
        + "It's quite sharp for a weapon made of that material.\n"));
    
    set_default_weapon(
        10,                 /* Weapon hit                                   */
        10,                 /* Penetration                                  */
        W_SWORD,            /* Weapon type                                  */
        W_SLASH | W_IMPALE, /* Damage type                                  */
        W_NONE,             /* A one hand weapon, free to choose wich hand  */
        0);                 /* The object defining the (un)wield functions  */

    add_prop(OBJ_I_WEIGHT, 2000);
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(10,10) + random(100));
}

