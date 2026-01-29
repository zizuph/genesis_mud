/*
   wooden_rack.c
   -------------

   Coded ........: 95/03/21
   By ...........: Jeremiah

   Latest update : 95/03/23
   By ...........: Jeremiah

   Part of the strange contraption (contraption.c)
 
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
   set_name(({"rack", "wooden rack", "_part2_"}));
   set_short("wooden rack");
   set_long("This is a strongly buildt wooden rack. The rack is made " +
            "of four vertical poles tied closely together with smaller " +
            "pieces of wood in between, in several places, making the " +
            "vertical poles look like a square tube. From the top of " +
            "the vertical poles, longer poles stretches to four sides, " +
            "two poles to each side, giving the rack a shape like a " +
            "small pyramid.\n");

   add_adj("strong");
   
   add_prop(OBJ_I_VALUE, 40);
   add_prop(OBJ_I_WEIGHT,40000);
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

