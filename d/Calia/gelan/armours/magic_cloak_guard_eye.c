/* 

    This is an armour of the town Gelan, a magical cloak. 

    coder(s):   Merlin and Maniac 
 
    history: 
                13/7/01    magic properties added          Maniac 
                   8.94    armour stats changed            Maniac 
                9. 1.93    slight modifications            Merlin 
                31.10.92    changed to match with text     Merlin 

    purpose:    magical cloak of a magical guard 
 
    quests:     none 
    special:    eye on cloak for an entrance guard 
 
    to do:      really magical armour, no tool slot used 
    bug:        had problems with 'set_at(A_MAGIC)', armour diappeared 
*/ 

inherit "/std/armour"; 

#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include "armours.h"


/* 
 * Function name: create_armour 
 * Description:   creates the cloak 
 * Arguments:     none 
 * Returns:       none 
 */ 
void 
create_armour() 
{ 
    set_name("cloak"); 
    set_adj(({ "magical", "gelan"})); 
    set_short("magical cloak of Gelan"); 
    set_pshort("magical cloaks of Gelan"); 
    set_long("A blue magical cloak, used by the magical " + 
             "guards of Gelan. It has a big white eye on " + 
             "the back.\n"); 

    add_prop(OBJ_S_WIZINFO, "A magical cloak worn by the magical " + 
             "guard in Gelan, Calia, (/d/Calia/gelan/monsters/entrance_guard.c) " + 
             "at the entrance of the town (/d/Calia/gelan/rooms/gate.c).\n"); 

    add_prop(MAGIC_AM_MAGIC, ({25, "enchantment"})); 

    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1); 

    add_prop(MAGIC_AM_ID_INFO, 
          ({"The cloak was enchanted by the Guardians of " + 
            "Gelan to protect the wearer far more than normal.\n", 15 })); 

    add_prop(OBJ_I_WEIGHT, 5000); 
    add_prop(OBJ_I_VOLUME, 1000); 

    set_ac(30); 
    set_at(A_ROBE); 
    set_am(({0, 0, 0})); 
} 
