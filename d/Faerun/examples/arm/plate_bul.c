/*
 * Armour from the Mere of Dead Men
 * -- Finwe, August 2006
 */
// domain defs file. Always include this with every file.
#include "/d/Faerun/defs.h"
// it is recommended that def file of the area be inherited, 
// but not necessary.

// standard definitions for the file
#include <formulas.h>
#include <language.h>
#include <stdproperties.h>
#include <wa_types.h>

// this is defined in the domain def file. This is the base file for 
// domain armours. Include in all armours
inherit FAERUN_ARM_BASE;

// sets the first and second adjectives for the armour
#define ADJ1        "large"
#define ADJ2        "turtle"
// defines what type of armour
#define ARMOUR      "platemail"
//defines what part of the body is protected
#define BOD_TYPE    A_TORSO | A_LEGS
// armour class modifiers for the armour. see 'man armour_guide' 
// for more info
#define AC_MOD      1,1,-2

// sets the armour class for the armour and then adds a random num to it.
int ac =  25 + random(10);

// creates the armour. create_faerun_armour() is defined FAERUN_ARM_BASE 
void create_faerun_armour()
{

// sets the default name for the armour
    set_name("armour");
//adds the ARMOUR name to the item. The player can refer to ARMOUR, too.
    add_name(ARMOUR);
// sets the adjectives
    set_adj(ADJ1);
    set_adj(ADJ2);
// creates the short and long description
    set_short(ADJ1 + " " + ADJ2 + " " + ARMOUR); 
    set_long("This " + short() + " is made of large overlapping pieces " +
        "of steel. It fits over the head and hangs over the shoulders by " +
        "two large leather strips. The portions that protect the torso " +
        "are irregular shaped and bulge slightly like turtle shells. " +
        "It extends down over the legs, protecting them in battles.\n");
 
// sets what body parts are protected
    set_at(BOD_TYPE);
// sets the armour class of the armour
    set_ac(ac);
// sets the modifiers for different attacks
    set_am(({AC_MOD}));
// sets the weight, volume, and value of the item
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(ac, BOD_TYPE));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);
    add_prop(OBJ_I_VALUE, 700 + random(250));
}
