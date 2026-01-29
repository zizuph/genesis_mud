/*
   sandbag.c
   ---------

   Coded ........: 95/03/21
   By ...........: Jeremiah

   Latest update : 95/03/23
   By ...........: Jeremiah

   Part of the strange contraption (contraption.c)
   Sandbag.

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
   set_name(({"sandbag", "_part6_"}));
   set_short("sandbag");
   set_long("This is a bag filled with sand, it's quite heavy. " +
            "The rope sealing the bag is, for some reason, extra " +
            "long.\n"); 

   add_adj("heavy");
   
   add_prop(OBJ_I_VALUE,5);
   add_prop(OBJ_I_WEIGHT,50000);
   add_prop(OBJ_I_VOLUME,20000);
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
