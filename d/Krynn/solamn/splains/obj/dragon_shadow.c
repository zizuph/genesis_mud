/* THIS IS A COPY OF THE DRAGON SHADOW FROM
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

/* Adjustments for vingaard keep by Aridor
 * 04/96
 *
 * 1997/01/21 ? - Last updated
 * 2011/07/17 Lavellan - Fixed runtime at end of path
 */

inherit "/std/object";
#include <macros.h>
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"
//#include "/d/Krynn/pax/local.h"

int    counter = 0;


/* The rooms the dragon shadow flies through. */
string *flypath = ({ "west","southwest","southwest","southwest","southeast",
		     "southeast","southeast","east","east","east","east","east",
		     "east","east","north","north","north","east","east","east",
		     "west","west","west","west","west","west","east","east",
		     "east","south","south","south","east" });


void
create_object()
{
    set_short("shadow on the ground");
    set_name(({"shadow", "_dragon_shadow_"}));
    set_long("It is a birdlike shadow, slowly gliding over the ground. " +
	     "Whatever is casting the shadow is most probably somewhere " +
	     "up in the air above you.\n");
    
    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_NO_GIVE, "Give away a shadow?\n");
    add_prop(OBJ_I_NO_GET, "Take a shadow?\n");
    
    add_item("dragon", "It is a large blue dragon. Its brilliant blue " +
	     "scales glittering in the sunlight, its huge leathery " +
	     "wings fanned out and its long tail stretched, stabilizing " +
	     "its flight.\n"); 
    
    //set_no_show_composite(1);
    
    
    if (IS_CLONE)
      set_alarm(30.0, 50.0,"do_move_shadow");
}


init()
{
   ::init();
   add_action("do_look", "look");
}


void
do_move_shadow()
{
    string room;
    mixed *exits;
    int i;

    if (counter >= sizeof(flypath))
    {
      TO->remove_object();
      return;
    }

    exits = E(TO)->query_exit();
    for(i=1;i<sizeof(exits);i+=3)
      if(exits[i] == flypath[counter])
	break;
    
    if (i>=sizeof(exits))
      set_alarm(1.0,0.0,"remove_object");
    else
      room = exits[i-1];

    TO->move(room);
    counter++;
}


int
do_look(string where)
{
   if(where == "up")
   {
      write("You look up. High above you, you see a dragon flying " +
	    (counter >= sizeof(flypath) ? "northeast" :
            flypath[counter]) + "wards. You hope it " +
            "doesn't notice you.\n");

      return 1;
   }

   return 0;   
}


void
enter_env(object dest, object old)
{
   tell_room(dest,"Suddenly a large shadow glides over the ground, " +
             "slowly moving " + flypath[counter] + "wards.\n");
             
   ::enter_env(dest,old);

   tell_room(old, "The large shadow slowly glides " +
             flypath[counter] + ", out of view.\n");
}

void
remove_object()
{
    tell_room(E(TO),"The large shadow slowly glides towards the northeast, " +
	      "beyond the Vingaard River and out of view.\n");
    ::remove_object();
}

