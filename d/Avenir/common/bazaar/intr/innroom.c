//-*-C++-*-
// The Dancing Potato Inn's Sleeping Room
// file name: /d/Avenir/common/bazaar/intr/innroom.c
// creator(s): Ilyian, 17 May, 1995
// last update: Lilith, June 2004: keeping path names, but this
//               now connects to the pub in the port area.
//              Lucius, Jan 2005: further updates to work with the
//               move to the port.
// purpose: A Room to spend the night in above the Dancing Potato
// note: Similiar to the Sleeping Stallion Inn in Minas Tirinth by
//         Elessar and Olorin, which is where this frame obtained.
// bug(s):
// to-do:

inherit "/std/room";
inherit "/lib/trade";

#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Avenir/smis/sys/statserv.h"
#include "/d/Avenir/common/common.h"

#ifndef SCROLLING_LOG
#define SCROLLING_LOG(file, entry)   ((file_size(file) > 10000) ? \
          (rm(file) && write_file(file, ctime(time()) + ": " + entry + "\n")) : \
          (write_file(file, ctime(time()) + ": " + entry + "\n")))
#endif

public int
start(string s)
{
    object ob;
  
    if (s!="here")
    {
        notify_fail("Start where?\n");
        return 0;
    }
  
    if(!(ob=present("port_inn_key",TP)))
    {
        write("You don't have the key you need!\n");
        return 1;
    }
  
    ob->remove_object();
    TP->set_temp_start_location(BAZAAR + "intr/innroom");
    STATSERV_LOG_EVENT("port", "Rented a room");
    SCROLLING_LOG("/d/Avenir/log/bazaar/hotel", TP->query_name() +
        " stays in the inn.");

    write("You will now awaken in this room when you next enter "+
	"this world.\n");
  return 1;
}

public int 
wash(string str)
{
    write("You wash the dirt from your long journey away, "
        +"using the refreshing water in the basin.\n");
    return 1;
}

public void
create_room(void)
{
    set_short("A guesting room above the Stormy Haven");
    set_long(
        "   If you have bought a key from the innkeeper downstairs "+
        "you can spend the night by typing 'start here', allowing you "+
        "to awaken here after you have gone to sleep.\n"+
	  "This is a small but comfortable room above the great hall of "+
        "the Stormy Haven. A washbasin is in the corner, along with "+
        "a chest for your clothes. A soft bed rests against the east "+
        "wall. It is very quiet here, but you can't help but notice "+
        "there is a slight vibration in the stone, probably caused "+
        "by the massive waterfall just outside.\n"); 

    add_item(({"basin","washbasin"}),
        "The washbasin is made from heavy grey granite, and contains "+ 
        "some cool water which you may wash with.\n");
    add_item(({"chest"}),"This is a large sturdy chest where your "+
        "personal possessions are placed when you go to sleep.\n");
    add_item(({"bed","bunk"}),"The bunk is small and has a very "+
        "soft mattress stuffed with what feels like feathers.\n");
/*  No longer valid, not located in the bazaar anymore.
    add_item(({"window","activity","bazaar"}),
        "Looking out the window, you see the ceaseless activity "+
        "in the bazaar below. In the center of the bazaar you can "+
        "see a large hill, atop which some figures seem to be "+
        "moving about.\n");
*/
    add_exit(PORT +"landing", "north", 0, 2);
  
    add_prop(ROOM_I_INSIDE,1); 
    IN_IN;
}

public void
init(void)
{
    ::init();
    add_action(start,"start");
    add_action(wash,"wash");
}

