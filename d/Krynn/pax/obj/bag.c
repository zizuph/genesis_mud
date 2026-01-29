/*
   sandbag.c
   ---------

   Coded ........: 95/03/21
   By ...........: Jeremiah

   Latest update : 95/03/23
   By ...........: Jeremiah

   Part of the strange contraption (contraption.c)
   Bag, with head drawn on it.

*/

inherit "/std/object";
#include <macros.h>
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"


void
create_object()
{
   set_name(({"bag", "_part7_"}));
   set_short("bag");
   set_long("This is an old bag made of rough bleached linen. Someone " +
            "has drawn a grinning face on the side of the bag.\n"); 

   add_adj("old");
   
   add_prop(OBJ_I_VALUE,5);
   add_prop(OBJ_I_WEIGHT,200);
   add_prop(OBJ_I_VOLUME,200);
}


init()
{
   ::init();
   add_action("do_assemble", "assemble");
}


int
do_assemble(string what)
{
   if(!what)
   {
      write("Assemble what?\n");
      return 1;
   }

   if(what != "contraption" && what != "strange contraption")
   {
      write("What is it you want to assemble?\n");
      return 1;
   }

   if(!present("_part1_", E(TO)))
   {
      write("There seems to be something missing.\n");
      return 1;
   }

   return 0;
}

