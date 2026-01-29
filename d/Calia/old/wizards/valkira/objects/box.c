/* OBJECT:  Box in Valsroom  
   CALIA DOMAIN  /d/Calia/valkira/objects/box1.c

   Date      Coder      Action    Comment/Purpose
   ------- ----------- -----------------------------
   9/01/99   Valkira    Created   Learn how to put actions to objects */
  
 
// INCLUSIONS AND DEFINITIONS

inherit "std/object";                  /* standard object file             */

#include "/d/Calia/domain.h"           /* Default include file for  
                                          Calia Domain                      */
#include <stdproperties.h>             /* ( /sys/stdproperties.h ) This file
                                          holds definition of all the standard
                                          properties that an object can have.
                                          The documentation for the properties
                                          can all be found in the directory
                                           /doc/man/properties              */
// #include <ss_types.h>                ADD IF MAKE STAT OR SKILL DEPENDENT
					  /* ( /sys/ss_types.h) This file 
                                          defines the available stats and 
                                          skills. Use this file in conjunction
                                          with query_stat() and query_skill()
                                          calls.                            */

void create_object()
 {
    set_name("box");
    set_short("green box");
    set_pshort("green boxes");
    set_long("It's a green box with tape wrapped around. The" +
             " tape looks as if it could be pulled loose. \n");
    add_item("tape",
       "You wonder what would happen if you pull the tape.\n");
    add_cmd_item("tape","pull",
       " You hear a deep voice remind you that box does not" +
       " belong to you.\n");
 
    add_prop(OBJ_I_WEIGHT, 200);
    
}

