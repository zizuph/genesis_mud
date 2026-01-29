/*
* /d/Faerun/guilds/fire_knives/rooms/obj/cuffed_boots.c
*
*
* Nerull 19.
*/
#pragma strict_types
inherit "/std/armour";
inherit "/lib/keep";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>


void
create_armour()
{
    set_name("boots"); 
    set_pname("pairs of cuffed leather boots");
  
    set_adj("cuffed");
    add_adj("leather");
    
    set_short("pair of cuffed leather boots"); 
    set_pshort("pairs of cuffed leather boots");
    
    set_long("The black leather boots are made of soft calfskin and go to "
    +"about knee length  before folding into a cuff. They lace in the "
    +"back down to about ankle length, making you able to secure the "
    +"boots tight and the soles are made of layered hardened leather "
    +"that lifts the heel slightly.\n");
      
    set_ac(5);
    set_am(({0, 1, -1}));
    set_at(A_FEET);
    set_keep(1);
    add_prop(OBJ_I_WEIGHT, 300);
    add_prop(OBJ_I_VOLUME, 2300);
    add_prop(OBJ_I_VALUE, 2500);
}