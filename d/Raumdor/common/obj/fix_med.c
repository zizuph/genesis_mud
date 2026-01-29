/*
 *  
 *
 *  Correction medallion for fix-quest, for those that have done 
 *  quest 3.5 twice. It sets the 3.4 bit when delivered.
 *
 *  
 *
 *  - Nerull      20/6.10.
*/

#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
inherit "/std/armour";
inherit "/lib/keep";


void
create_armour()
{
    set_name("medallion");
    add_name("spectre_med");
    set_adj("pink");
    add_adj("white");
    set_short("pink white medallion");
    set_long("This is a pink white medallion.\n");

    set_ac(5);
    set_at(A_NECK);
    set_af(this_object());
    set_wf(this_object());
    add_prop(OBJ_I_NO_STEAL, 1);
    add_prop(OBJ_I_VALUE, 1093); 
    add_prop(OBJ_I_VOLUME, 500); 
    add_prop(OBJ_I_WEIGHT, 50); 
         
    setuid();
    seteuid(getuid());
}




  














