/*
   cshield.c
   ---------

   Coded ........: 95/03/21
   By ...........: Jeremiah

   Latest update : 95/03/22
   By ...........: Jeremiah

   Part of the strange contraption (contraption.c)
   Shield 

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
   set_name(({"shield", "wooden shield", "_part5_"}));
   set_short("wooden shield");
   set_long("A large scarred wooden shield. It has many cuts, as " +
            "if it has been hit many times with sharp weapons. " +
            "The shield has some unusual strings on the backside. " +
            "It is not possible to wear this as a normal shield.\n");

   add_adj("scarred");
   
   add_prop(OBJ_I_VALUE,50);
   add_prop(OBJ_I_WEIGHT,5000);
   add_prop(OBJ_I_VOLUME,2000);
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
