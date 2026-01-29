
/* this is a room of the town Gelan
 
   coder(s):   Deinonychus & Maniac

   history:    
              7/11/96 Feathers can be collected
                      here, for Elemental Worshippers,   
                                                   Maniac
              5/9/95  pigeon code added            Jaacar/Maniac
 
   purpose:    none
   exits:      none
 
   objects:    none
   npcs:       none
 
   quests:     none
   special:    none
 
   to do:      none
   bug:        none known
*/


#pragma save_binary

#include "defs.h"
#include <stdproperties.h>
#include <money.h>
#include <macros.h>
#include "room.h"

inherit GELAN_BASE_ROOM;

#define MAILREADER	"/secure/mail_reader"
#define FEATHER "/d/Calia/worshippers/objects/feather"


string messages;
int new_mail;

leave_inv(ob, to)
{
    object reader;
    ::leave_inv(ob); /* , to); */

    reader = present("mailread", ob);
    if (reader) reader->remove_object();

}


/* Action of hiring a pigeon */
int
hire(string str)
{
    object tp = this_player();
    object pigeon;

    if (str != "pigeon") {
        notify_fail("Hire pigeon?\n");
        return 0;
     }

    if (present("pigeon", tp)) {
        notify_fail("Why would you need more than one pigeon?\n"); 
        return 0;
    }

   if (MONEY_ADD(tp,-24)) {
      pigeon=clone_object("/d/Genesis/obj/pigeon");
      pigeon->move(tp);
      tp->catch_msg("You quietly hire a messenger pigeon.\n");
      }
   else 
      tp->catch_msg("Hmm, not enough money perhaps?\n");

   return 1;
}



public void
create_gelan_room()
{
    set_short("Post office of Gelan");

    set_long("You're in the post office of Gelan. " +
	     "There are several desks with ink-wells and pens on them, " +
	     "but nobody uses that stuff anymore. " +
	     "At the entrance you've taken one of those super-modern " +
	     "mailreaders that one uses nowadays for writing and reading " +
	     "mail. You notice that pigeons are available for <hire> " +
             "here, at the cost of 24 copper. There are lots of feathers " +
             "on the ground.\n");

    add_exit(GELAN_ROOMS + "square_northend_w", "east", 0);
    add_exit(GELAN_ROOMS + "square_corner_nw", "south", 0);

    add_item(({"desk","desks"}),
	     "The wooden desks are made for a single person and " +
	     "they look as though they've seen better days. " +
	     "Each desk has in its upper right corner an ink-well.\n");

    add_item(({"feathers"}), 
             "There are lots of them on the ground, as one would " +
             "expect because of all the pigeons. You could try " +
             "collecting them.\n"); 

    add_item(({"pen", "pens"}),
	     "Before the invention of the mailreader one used to " +
	     "dip the pen into ink and then could write with it " +
	     "on paper. Of course one produced lots of ink-blots, " +
	     "but this gave a handwritten letter an even more personal " +
	     "touch.\n");

    add_item(({"ink-well", "ink-wells"}),
	     "The ink-wells are not filled anymore. But by the colour " +
	     "of their bases you see that they must once have been " +
	     "full of black ink.\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
}


int
collect(string str)
{
    object feather;
    int num;
    if (str != "feathers")
    {
        notify_fail("Collect feathers?\n");
        return 0;
    }

    feather=clone_object(FEATHER);
    num = 3 + random(6);
    feather->set_heap_size(num);
    if (!feather->move(this_player())) { 
        write("You quietly collect "+num+" feathers from the ground.\n");
        return 1;
    } 
    write("You didn't manage to collect any feathers.\n"); 
    return 1;
}


void
init()
{
    object reader;
    ::init();

    reader = clone_object(MAILREADER);
    if(!reader)
    {
	write("No mailreader is available at this time.\n");
	return;
    }
    reader->move(this_player());

    add_action(hire, "hire");
    add_action(hire, "buy");
    add_action(collect, "collect"); 
}

