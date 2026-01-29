/*
   Pax Tharkas, Ground level, The Pax Tharkas throne room. Earlier 
                the hall of Thanes.


   throne_room.c
   -------------

   Coded ........: 95/01/25
   By ...........: Jeremiah

   Latest update : 95/04/19
   By ...........: Jeremiah

*/


#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"

inherit PAXINROOM;

#define BALC \
   ({   \
      WALL_LEVEL + "balcony2", \
   })


object highlord, dragon;

void
reset_pax_room()
{
    if (!objectp(highlord))
    {
	highlord = clone_object(PMONSTER + "verminaard");
    }
    
    if (!objectp(dragon) && !(dragon = P("ember", TO)))
    {
	dragon = clone_object(PMONSTER + "pyros");
    }
    
    if (environment(highlord) != TO)
        highlord->move_living("arrives", TO, 0, 0);
    
    if (environment(dragon) != TO)
        dragon->move_living("arrives", TO, 0, 0);
    
    if (objectp(dragon) && objectp(highlord))
    {
        dragon->set_leader(highlord);
	highlord->team_join(dragon);
    }
}


void
create_pax_room()
{
    set_short("Throne room");
    set_long("You are standing in a large room, furnished with every " +
        "possible luxury. You are sure that all that is beautiful, " +
        "graceful, delicate and valuable in the world, has been " +
        "brought here to decorate this room. A large ornate throne " +
        "stands, raised above the floor on a stone dais, in the " +
        "south end of the room. Rare and priceless silver mirrors " + 
        "hang on the walls. High above you, just under the ceiling, " +
        "a balcony, most of it hidden in shadow, runs along the " +
        "north side of the room. A pair of huge open doors lead " +
        "west, into dimly lit room.\n");
	
    INSIDE;

    add_item("throne","A huge ornate throne, beautifully carved out of " +
        "a solid piece of bright rock. Gemstones in all colours " +
        "decorate the sides and the back of the throne. Large, and " +
        "smooth polished gems, decorate the end of each armrest. " +
        "A marvellous piece of stone masonry.\n");

    add_item(({"gem", "gems"}), "The gems are solidly planted into " +
        "the stone throne.\n");

    add_item("dais", "A semi circle shaped stone plateau rising in " +
        "the south end of the room. On the dais you see a large " +
        "ornate throne.\n");

    add_item(({"mirror", "mirrors", "silver mirror"}), "These are " +
        "beautiful silver mirrors. You can't remember ever to " +
        "have seen anything like them. Looking closer you " +
        "realize, that all the mirrors have been placed in a " +
        "way, so that no matter where you look, you would see " +
        "the person standing on the dais in front of the " + 
        "throne.\n");

    add_item("balcony","@@balcony_descr@@");

    add_exit(GROUND_LEVEL + "corridor2", "north",0);
    add_exit(GROUND_LEVEL + "dragons_lair", "west", 0);

    reset_pax_room();
}


string
balcony_descr()
{
    string *roomfiles;
    string ret_str;
    object *inv, *live, room;
    int    i;

    roomfiles = BALC;
    ret_str = "Taking a closer look at the balcony above you, ";
    inv = ({});

    for (i = 0; i < sizeof(roomfiles); i++)
    {
        if ((room = find_object(roomfiles[i])) != 0)
            inv += all_inventory(room);
    }

    if (sizeof(inv) == 0)
        ret_str += "you see nothing.";

    if (sizeof(inv) == 1)
        ret_str += "you see a figure standing in the shadows. You " +
            "cannot see who or what it is.";

    if (sizeof(inv) > 1)
        ret_str += "you see some figures standing in the shadows. " +
            "You cannot see who or what they are.";

    ret_str += "\n";
    return ret_str;
}
