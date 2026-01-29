/* OBJECT:  Jack-o-lantern  
   CALIA DOMAIN  /d/Calia/valkira/objects/pumpkin.c

   Date      Coder      Action    Comment/Purpose
   ------- ----------- -----------------------------
   9/23/99   Valkira    Created   Halloween fun object - used with pumpkin
 */
  
 
// INCLUSIONS AND DEFINITIONS

inherit "std/torch";                  
#include "/d/Calia/domain.h"
#include <stdproperties.h>             /* ( /sys/stdproperties.h ) This file
                                          holds definition of all the standard
                                          properties that an object can have.
                                          The documentation for the properties
                                          can all be found in the directory
                                           /doc/man/properties              */

#include <macros.h>
// #include <options.h>



void
create_torch()
 {

/*  VARIABLES  */

    string *faces = ({"ghoulish", "jolly", "krougish", "shrewish"});
    int num = random(sizeof(faces));

    string face = faces[num];
      
    set_name("jack-o-lantern");
    add_name("lantern");
    set_short(face + " " + "faced jack-o-lantern");
    set_pshort("jack-o-lanterns");
    set_long("This jack-o-lantern has a " + face + " " + "face.\n");
    set_adj(face[num]);
    set_strength(2);
 
    add_prop(OBJ_I_WEIGHT, 200);

 }

