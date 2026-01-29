/*
* /d/Faerun/guilds/fire_knives/rooms/obj/cuffed_gloves.c
*
*
* Nerull 15.
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
    set_name("gloves"); 
    set_pname("pairs of cuffed leather gloves");
  
    set_adj("cuffed");
    add_adj("leather");
    
    set_short("pair of cuffed leather gloves"); 
    set_pshort("pairs of cuffed leather gloves");
    
    set_long("The black leather gloves are made of soft calfskin and go up to "
    +"about elbow length before folding into a cuff. On each hand there is an "
    +"imprint into the leather of a dagger with a flaming aura.\n");
      
    set_ac(2);
    set_am(({0, 1, -1}));
    set_at(A_HANDS);
    set_keep(1);
    add_prop(OBJ_I_WEIGHT, 150);
    add_prop(OBJ_I_VOLUME, 200);
    add_prop(OBJ_I_VALUE, 2500);
}