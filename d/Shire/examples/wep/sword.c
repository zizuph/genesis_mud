/*
 *  Sword for the Hin Warrior guard
 */

 // needed for all weapons. basic routines for object.
inherit "/std/weapon";

// inherits keepability for item
inherit "/lib/keep.c";

// additonal routines for object
#include <macros.h>
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"


// opening statement to object
create_weapon()
{
// defines name of weapon
    set_name("sword");

// sets plurality of weapon
    set_pname("swords");

// sets short description
    set_short("shiny sword");

// sets plural short descriptions
    set_pshort("shiny swords");

// sets adjective    
    set_adj("long");

// sets long description of sword. 
// This is what you see when you exa the sword.

    set_long("The sword has been polished lately and looks dangerous.\n");

    set_default_weapon( /* See /sys/wa_types.h for maxima */
       11,                     /* 'to hit' value    */
       10,                     /* penetration value */
       W_SWORD,                /* weapon type       */
       W_IMPALE | W_SLASH,     /* damage type       */
       W_NONE,                 /* nr of hands       */
       0);           /* object that defines wield and unwield functions */

   add_prop(OBJ_I_WEIGHT,5000); /* Weighs 5 kg  */
   add_prop(OBJ_I_VOLUME,2941); /* Volume 3 Ltr */

 /* Formula taken from /doc/man/general/weapon:
  * cc = 50 + ((wchit * wcpen * min(wchit,wcpen)) / 4)
  */
   add_prop(OBJ_I_VALUE,30 + random(40) + ((10*11*10)/4));

/*
 * 0 = keep not set (best for default), 1 = keep set
 */
   set_keep(0);

}




// routine necessary to enable weapon recovery after armageddon
string query_recover()
{
    return MASTER + ":" + query_wep_recover();
}

 
// Initializes weapon recovery
void init_recover(string arg)
{
    init_wep_recover(arg);
}

