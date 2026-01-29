/* OBJECT:  Pumpkin patch 
   CALIA DOMAIN  /d/Calia/valkira/objects/pumpkin.c

   Date      Coder      Action    Comment/Purpose
   ------- ----------- -----------------------------
   10/4/99   Valkira    Created   Pulp from carved pumpkin
*/


// INCLUSIONS AND DEFINITIONS

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include <options.h>

// OBJECT DEFINITION

void
create_object()

{

    set_short("pumpkin pulp");
    set_long("It is squishy, seedy pumpkin pulp.");
    set_name("pulp");
       
    /*  PROPERTIES  */

    add_prop(OBJ_I_WEIGHT, 5);
    add_prop(OBJ_I_VOLUME, 7);
    
}

