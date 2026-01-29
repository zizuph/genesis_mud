/*
   vpole.c
   -------

   Coded ........: 95/03/21
   By ...........: Jeremiah

   Latest update : 95/03/23
   By ...........: Jeremiah

   Part of the strange contraption (contraption.c)
   Vertical pole. 

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
   set_name(({"pole", "long pole", "_part3_"}));
   set_short("long pole");
   set_long("A long pole. It's more than one and a half times as high " +
            "than a full grown human, and as thick as a leg. About one " +
            "fourth down the pole a hole has been drilled through it.\n"); 

   add_adj("long");
   
   add_prop(OBJ_I_VALUE, 10);
   add_prop(OBJ_I_WEIGHT,5000);
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

