/*
   hpole.c
   -------

   Coded ........: 95/03/21
   By ...........: Jeremiah

   Latest update : 95/03/23
   By ...........: Jeremiah

   Part of the strange contraption (contraption.c)
   Horizontal pole. 

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
   set_name(({"pole", "_part4_"}));
   set_short("pole");
   set_long("A strong wooden pole. It looks pretty ordinary. There " +
            "are, however, some marks on both ends, and in the middle " +
            "of the pole.\n"); 

   add_prop(OBJ_I_VALUE,10);
   add_prop(OBJ_I_WEIGHT,4000);
   add_prop(OBJ_I_VOLUME,1000);
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

