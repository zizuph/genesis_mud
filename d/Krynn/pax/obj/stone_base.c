/*
   stone_base.c
   ------------

   Coded ........: 95/03/20
   By ...........: Jeremiah

   Latest update : 95/03/23
   By ...........: Jeremiah

   Base of the strange contraption (contraption.c) .. this object checks
   if all the parts needed to assemble to contraption are present.
 
*/

inherit "/std/object";
#include <macros.h>
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"

/* each part of the contraption has an extra name to identify it */
/*                                                               */
/* _part1_  = this object      /d/Krynn/pax/obj/stone_base.c     */
/* _part2_  = wooden_rack      /d/Krynn/pax/obj/wooden_rack.c    */
/* _part3_  = vpole            /d/Krynn/pax/obj/vpole.c          */
/* _part4_  = hpole            /d/Krynn/pax/obj/hpole.c          */
/* _part5_  = cshield          /d/Krynn/pax/obj/cshield.c        */
/* _part6_  = sandbag          /d/Krynn/pax/pbj/sandbag.c        */
/* _part7_  = bag              /d/Krynn/pax/obj/bag.c            */
/* _part8_  = strappings       /d/Krynn/pax/obj/strappings.c     */

string *parts = ({"_part2_", "_part3_", "_part4_", "_part5_", "_part6_",
                  "_part7_", "_part8_"});


void
create_object()
{
   set_name(({"stone", "square stone", "_part1_"}));
   set_short("square stone");
   set_long("This is a large square stone with a hole down the center. " +
            "A greasy substance has been applied to the hole. Four " +
            "smaller holes circle the center hole. On all four sides " +
            "of the stone an iron handle has been mounted.\n");

   add_adj("large");
   
   add_item(({"hole", "holes"}), "A deep hole, drilled into the stone, " +
            "right in the center. Some greasy substance has been smeared " +
            "on the sides inside the hole. Circling the large hole, four " +
            "smaller holes, not as deep as the center one, has been " +
            "drilled.\n");

   add_prop(OBJ_I_VALUE, 250);
   add_prop(OBJ_I_WEIGHT,100000);
   add_prop(OBJ_I_VOLUME,20000);

   seteuid(getuid(TO));
}


init()
{
   ::init();
   add_action("do_assemble", "assemble");
}


int
all_present()
{
   int i;

   for (i=0; i<7; i++)
   {
      if(!present(parts[i], E(TO)))
         return 0;
   }

   return 1;
}    




int
do_assemble(string what)
{
   int    i;
   object contrp;

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

   if(!all_present())
   {
      write("There seems to be someting missing.\n");
      return 1;
   }

   if(!(TP->test_bit("krynn", 1, 15)))
   {
      write("You try to assemble something from the parts lying " +
            "around on the ground here. Somehow you don't seem " +
            "to get the grasp of the idea behind it all.\n");
      tell_room(E(TO), QCTNAME(TP) + " fumbles around with the various " +
            "parts lying on the ground, but ends up looking at them " +
            "with an expression of utter confusion on the face.\n", TP, TO);

      return 1;
   }

   write("With gnomish expertise, you assemble a strange contraption from " +
         "the various parts lying around on the ground.\n");
   tell_room(E(TO), "With gnomish expertise, " + QCTNAME(TP) + " assembles " +
         "a strange contraption from the parts lying around on the " +
         "ground.\n", TP, TO);

  
   for(i=0; i<7; i++)
   {
      present(parts[i], E(TO))->remove_object();
   }   

   contrp = clone_object(POBJ + "contraption");
   contrp->move(E(TO));
   remove_object();

   return 1;
}
	
