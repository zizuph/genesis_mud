/*
   Pax Tharkas.

   dragon_shadow.c
   ---------------

   Coded ........: Jeremiah
   By ...........: 95/04/30
   
   Latest update : Jeremiah
   By ...........: 95/04/30

   The shadow of a dragon moving along the road from Newports
   to the valley in from of Pax Tharkas.

*/

inherit "/std/object";
#include <macros.h>
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"

int    counter = 1;
int    direction = 0;

/* The rooms the dragon shadow flies through. */

object *flypath = ({ ROAD + "road1", ROAD + "road2", 
                     ROAD + "road3", ROAD + "road4", 
                     ROAD + "road5", ROAD + "road6", 
                     ROAD + "road7" });


void
create_object()
{
   set_name(({"shadow", "_dragon_shadow_"}));
   set_long("It is a birdlike shadow, slowly gliding over the ground. " +
            "Whatever is casting the shadow is most probably somewhere " +
            "up in the air above you.\n");

   add_prop(OBJ_I_VOLUME, 0);
   add_prop(OBJ_I_WEIGHT, 0);
   add_prop(OBJ_I_NO_GIVE, "Give away a shadow?\n");
   add_prop(OBJ_I_NO_GET, "Take a shadow?\n");

   add_item("dragon", "It is a large red dragon. Its brilliant red " +
            "scales glittering in the sunlight, its huge leathery " +
            "wings fanned out and its long tail stretched, stabilizing " +
            "its flight.\n"); 

   set_no_show_composite(1);

   if (IS_CLONE)
     set_alarm(30.0, 180.0,"do_move_shadow");
}


init()
{
   ::init();
   add_action("do_look", "look");
}


void
do_move_shadow()
{
   TO->move(flypath[counter]);

   if(direction == 0)
   {
      counter++;
   }
   else
      counter--;

   if(counter > 6)   
   {
      counter = 5;
      direction = 1;
      return;
   }

   if(counter < 0)
   {
      counter = 1;
      direction = 0;
   }
}


string
query_direction()
{
   if(direction == 0)
      return "northeast";

   return "southwest";
}


int
do_look(string where)
{
   if(where == "up")
   {
      write("You look up. High above you, you see a dragon flying " +
            query_direction() + "wards along the road. You hope it " +
            "doesn't notice you.\n");

      return 1;
   }

   return 0;   
}


void
enter_env(object dest, object old)
{
   tell_room(dest, "Suddenly a large shadow glides over the ground, " +
             "slowly moving " + query_direction() + "wards.\n");
             
   ::enter_env(dest,old);

   tell_room(old, "The large shadow slowly glides " +
             query_direction() + ", out of view.\n");
}

