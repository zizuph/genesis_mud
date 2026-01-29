/* 	this is an armour of the town Gelan

    coder(s):   Merlin

    history:     9. 2.93    error removed                   Merlin
                 9. 1.93    slight modifications            Merlin
                 8.11.92    created                         Merlin

    purpose:    these are the standard gauntlets for an apprentice fighter of
                Gelan

    quests:     none
    special:    none

    to do:      none
    bug:        none known
*/

inherit "/std/armour";

#include "armours.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>

#define ACMIN   10                              /* min value armour class */
#define ACDIFF  5                               /* diff between max an min */

/*
 * Function name: create_armour
 * Description:   creates the armour
 * Arguments:     none
 * Returns:       none
 */

create_armour()
{

    set_name("gloves");

    set_adj(({"apprentice","chain","standard"}));

    set_short("chain gloves");
    set_pshort("chain gloves");

    set_long(BS("These are solid chain gloves, as they are use by the "
              + "fighter guards of Gelan.\n"));

    add_prop(OBJ_I_WEIGHT, 150);
    add_prop(OBJ_I_VOLUME, 20);

    set_default_armour(
        ACMIN + random(ACDIFF),                 /* armour class */
        A_HANDS,                                /* armour type */
        ({0,0,0}),                              /* modifier list */
        0);                                     /* special wear remove func */

}
