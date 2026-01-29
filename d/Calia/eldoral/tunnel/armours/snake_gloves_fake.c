/*   snake_gloves_fake.c
 *
 * This pair of fake snake-skin gloves is not only an armour,
 * it also shadows the player with a function that changes
 * the hit descriptions when you fight unarmed.
 *
 * Baldacin@Genesis, Sep 2003
 */
inherit "/std/armour";
#include "snake_gloves.h"
#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

void
create_armour()
{
    set_name("gloves");
    set_adj("snake-skin");
    add_adj("green");
    set_short("pair of snake-skin gloves"); 
    set_pshort("pairs of snake-skin gloves"); 
    set_long("This is a pair of green snake-skin gloves, crafted "+
      "with great expertise by an expert armourer. They seem to "+
      "fit your hands very well.\n");
    set_ac(10);
    set_at(A_HANDS);
    set_wf(this_object());
    add_prop(OBJ_I_WEIGHT, 1200);
    add_prop(OBJ_I_VOLUME, 1500);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(15 + random(5)));
}

/*
 * Function name: wear
 * Description  : This function might be called when someone tries to wear
 *                this armour. To have it called, use set_wf().
 * Arguments    : object obj - The armour we want to wear.
 * Returns      : int  0 - The armour can be worn normally.
 *                     1 - The armour can be worn, but print no messages.
 *                    -1 - The armour can't be worn, use default messages.
 *                string - The armour can't be worn, use this message.
 */
public mixed
wear(object obj)
{   
    setuid(); seteuid(getuid());    
    clone_object(GLOVE_SHAD_FAKE)->start_gloves(this_player());        
    return 0;
}

/*
 * Function name: remove
 * Description  : This function might be called when someone tries to remove
 *                this armour. To have it called, use set_wf().
 * Arguments    : object obj - The armour to remove.
 * Returns      : int  0 - Remove the armour normally.
 *                     1 - Remove the armour, but print no messages.
 *                    -1 - Do not remove the armour, print default message.
 *                string - Do not remove the armour, use this message.
 */
public mixed
remove(object obj)
{   
    this_player()->stop_gloves();
    return 0;
}

