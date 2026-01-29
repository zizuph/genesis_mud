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
    set_name("war-hammer"); 
    set_pname("war-hammers");
    set_short("bloody war-hammer"); 
    set_pshort("bloody war-hammers");
    set_adj("bloody");
    set_long(BS("Looks as if this weapons was much in use, for the wood " +
      "is colored red by the blood of the victimes.\n"));
    
    set_default_weapon(
        10,                 /* Weapon hit                                   */
        10,                 /* Penetration                                  */
        W_CLUB,             /* Weapon type                                  */
        W_BLUDGEON,	    /* Damage type                                  */
        W_NONE,             /* A one hand weapon, free to choose wich hand  */
        0);                 /* The object defining the (un)wield functions  */

    add_prop(OBJ_I_WEIGHT, 600);
    add_prop(OBJ_I_VOLUME, 700);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(10,10) + random(100));
}

