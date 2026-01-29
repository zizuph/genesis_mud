/* Pax Tharkas, inside Sla-Mori.
 *
 * 950406 by Rastlin 
 *
 * 970310 - Karath - made this room include macros.h and changed the
 * person climbing message to use QCTNAME(TP)
 *
 * May 2016 - Arman - added the entry to the Treasury vault
 *
 */

#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <macros.h>

inherit PAXINROOM;

int secret_door_open;

object up_room = WALL_LEVEL + "chainshaft1";
object gDoor_wood, gDoor_bronze;

void
create_pax_room()
{
    set_short("Chain room");
    set_long("@@my_desc");

    add_item(({"column", "chain"}), "A close look makes it obvious that the " +
		"column is actually a massive chain, supported by a huge iron " +
		"bracket sunk into the center of the floor. Each link is as " +
		"long as a man, and the iron bands forming the links are " +
		"nearly a foot thick. The chain is the final support " +
		"mechanism for the heavy stone defenses the protect Pax " +
		"Tharkas against attack from the north. If it is released, " +
		"massive blocks of granite drop behind the gate of the " +
		"fortress.\n");

    add_item(({"wall", "walls"}), "There is nothing unusual about the walls here, " +
                "except for the eastern wall where there seems to be a faint " +
                "outline.\n");

    add_item(({"eastern wall","east wall","outline","faint outline","secret door"}), 
                "@@wall_desc"); 

    add_item("dust", "The dust seems to be very, very old.\n");

    add_item("floor", "There is a lot of dust and loose chunks of rock " +
		"on the floor.\n");

    add_item("catch", "There is a catch in the wall that you could pull, that will " +
                "open the suspiciously obvious secret door in the wall to your east.\n");

    add_cmd_item("catch","pull","@@pull_catch");

/*    add_exit(PSLA + "treasure_vault", "east"); */

    add_prop(ROOM_I_LIGHT, 0);

    seteuid(getuid());

    gDoor_wood = clone_object(POBJ + "d_chainroom_wood");
    gDoor_wood->move(TO);
    gDoor_wood->set_key(FINAL_KEY);

    gDoor_bronze = clone_object(POBJ + "d_chainroom_bronze");
    gDoor_bronze->move(TO);
}

string
wall_desc()
{
   if(secret_door_open)
     return "A sliding secret door stands open in the wall to your east.\n";
   else
     return "On the eastern wall is a faint outline that looks like a " +
            "secret door. Unusually obvious for dwarven craftsmanship. " +
            "There looks like there is a catch you can pull to open it.\n";
}

void
set_door_closed()
{
   secret_door_open = 0;
   remove_exit("east");
}

void
set_door_open()
{
   if(!secret_door_open)
   {
     secret_door_open = 1;
     add_exit(PSLA + "treasure_vault", "east");
   }
}

string
pull_catch()
{
   string vault = PSLA + "treasure_vault.c";

   if(secret_door_open)
     return "The secret door is currently open.\n";

   write("You pull the catch in the wall, and a secret door slides open " +
       "in the eastern wall.\n");
   say(QCTNAME(TP)+ " pulls a catch in the wall, and a secret door " +
       "slides open in the eastern wall.\n");

   tell_room(vault, "A secret door slides open to the west.\n");
   set_door_open();
   find_object(vault)->set_door_open();

   return "";
}

void
init()
{
   ::init();
   add_action("climb_chain", "climb");
}


public string
door_line(object door)
{
    if (door->query_open())
	return "open";

    return "closed";
}

public string
my_desc()
{
    string desc;

    desc = "You are standing in a large, circular room. The dust " +
	"on the floor is thick and unmarked. A curious feature " +
	"of the room is the crooked column in its center, which " +
	"slants to the side but climbs far out of sight above. That's " +
	"funny, the dwarves actually built a crooked column. It has " +
	"never been heard of before in the history of dwarven craftsmanship. " +
        "You can sense a strange power in here, something unnatural. On the south " +
	"wall is a " + door_line(gDoor_wood) + " wooden door and on the " +
	"north wall is a " + door_line(gDoor_bronze) + " door made of solid " +
	"bronze. There is something unusual about the wall to your east.\n";

    return desc;
}

int
climb_chain(string dir)
{
   if (dir == "up" || dir == "up chain" || dir == "up the chain")
   {
      write("You climb carefully up the chain.\n");
      // say(C(TP->query_real_name()) + " climbs up the chain.\n");
      say(QCTNAME(TP)+ " climbs up the chain.\n");
      up_room->someone_arrives(TP,1);
      TP->move_living("M", WALL_LEVEL + "chainshaft1", 0, 0);
      return 1;
   }

   NF("Climb where?\n");
   return 0;
}


void
someone_arrives(object who, int from)
{
   string *from_where = ({"down", "up"});

   tell_room(TO, C(who->query_real_name()) + " arrives, climbing " + 
             from_where[from] + " the chain.\n");
}

