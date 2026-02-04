inherit "/std/room";

/*
 * Coffin for entrance to "another world"
 *
 *  Make the player think they are dead but really we just move them to another
 *  room.  
 */

#include <stdproperties.h>
#include <macros.h>

#include "/d/Terel/common/terel_defs.h"
#include "tomb.h"

int is_occupied()
{
     object *op;
     int i;

     op = deep_inventory();
     for (i = 0; i < sizeof(op); i++)
	  if (interactive(op[i])) return 1;
     return 0;
}

create_room()
{
     set_short("in coffin");
     set_long("You lie down in the coffin.  It is not as comfortable " +
                  "as it looked from the outside.  You can feel sharp " +
                  "spikes beneath the surface of the velvet that dig " +
                  "painfully into your back.  The velvet lining is covered " +
                  "with odd looking bumps.  At once you are overcome with " +
                  "the powerful presence of death.\n"
     );
     add_item(({"bump", "bumps", "odd bumps"}), 
         "You take a closer look at the buttons and notice that they " +
         "are caused by sharp spikes just beneath the surface of the velvet"
     );                                                    

     add_prop(ROOM_I_INSIDE, 1);
}

init()
{
     ::init();
     add_action("close_lid", "close");
}

int close_lid(string str)
{
     notify_fail("Close what?\n");
     if ((str == "lid") || (str == "coffin")) {
     
     write("You close the lid.  It is completely dark.  " +
               "You cry out in agony as your body is pierced by sharp " +
               "spikes that emerge from benath the velvet bottom of " +
               "the coffin.  The spikes pass right through and " +
               "splinter the wood of the coffin lid above you.  You feel " +
               "very cold and you fear that your life may be slipping away.\n " 
               );
     
     tell_room("The lid of the coffin shuts with a resounding " +
                    "click.  Suddenly the lid of the coffin is pierced by " +
                    "blood covered spikes.   You hear muffled screams of " +
                    "agony followed by... silence.\n"
     );

     set_alarm(10.0, -1.0, "near_death");
     set_alarm(20.0, -1.0, "at_death");
     set_alarm(30.0, -1.0, "after_death");
     
     return 1;
}
return 0;
}

near_death()
{
     write("You desperately attempt to cling to life, but the spikes " +
           "have done too much damage.  Your body becomes colder and " +
           "begins to stiffen as you lose conciousness...\n"
     );
}

at_death() { write("...and die.\n"); }

after_death()
{
     TP->move_living("X", SORGUMDIR + "workroom");
     
}
