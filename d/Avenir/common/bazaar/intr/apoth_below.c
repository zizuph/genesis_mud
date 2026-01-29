// The Apothecary Main Shop
// file name:    /d/Avenir/common/bazaar/intr/apoth_below.c
// creator(s):   Lilith DEc 2021
// last update:  
// purpose:      Below the apothecarist, storage of items and place
//               where Nemur's wand teleports to.
// note: 
// bug(s):
// to-do: 
/* Inherit the standard room object */
inherit "/d/Avenir/inherit/room";

/* Inherit the Avenir time object   */
inherit "/d/Avenir/inherit/avenir_time";

/* Inherit the room_tell functions  */
inherit "/d/Avenir/inherit/room_tell";

#include "/d/Avenir/common/bazaar/bazaar.h"

void
reset_domain_room()
{

}

void
create_domain_room()
{
    set_short("Small room with shelves on all walls");
    set_long("A small room with shelves lining every wall. "+
        "Neatly stock-piled with odd bits of medical and "+
        "magical paraphernalia, the shelves appear to be "+
        "magically warded. "+
        "A ladder leads up to a trap-door in the ceiling "+
        "above.\n");
		
    add_item(({"paraphernalia", "medical paraphernalia", "magical "+
        "paraphernalia"}), "A jumble of ingredients for everything "+
        "from poultices to potions.\n");
    add_item(({"shelf", "shelves", "wall", "walls"}),
        "Wooden shelves cover all the walls of this room, and they "+
        "fairly groan under the weight of the paraphernalia piled "+
        "upon them. They appear to be protected by magical wards.\n");
    add_item(({"ladder", "wooden ladder"}), "A simple ladder leading "+
        "up to a trapdoor.\n");
    add_cmd_item(({"air", "smoke", "incense"}), ({"smell", "sniff"}),
        "It smells of pine-needles, lemon, and sandalwood.\n");
    add_cmd_item(({"parphernalia", "medical paraphernalia", "magical "+
        "paraphernalia", "corpses", "rat", "mice", "pelts", "skins",
        "bones", "body parts", "parts", "henna patterns", "sachets",
        "bottles", "amulets", "curiosities"}), ({"get", "take"}), 
        "As soon as your fingertips pass into the shelf space you "+
        "feel and intense, burning pain. OUCH!\n");
    set_tell_time(60);
      add_tell("The scent of herbs is carried in on a little puff of "+
          "wind.\n");
      add_tell("You hear the sound of footsteps overhead.\n");

    add_cmd_item(({"door","trapdoor","trap door", "ladder"}),
        ({"push","open", "push up", "climb"}),"@@trapdoor");
	
	IN;       // Avenir is an undergound domain.
	IN_IN;    // Interior room, no flux msgs, steeds etc.

	add_prop(ROOM_I_LIGHT, -3);
	add_prop(OBJ_S_WIZINFO, "This room is accessed via Nemur's "+
       "ruby in fuchsite wand.\n");
    add_prop(ROOM_S_DARK_LONG, "A small, dark space. You can feel "+
       "shelves all around you, and a ladder leading up.\n"); 

    add_exit(INTR + "apoth1",  "up", "@@up_trapdoor");
    reset_domain_room();
}


public mixed
trapdoor()
{
    write("You climb the ladder and push up on the trapdoor above you, "+
       "then climb through the opening.\n");
    say(QCTNAME(TP) + " pushes open a trapdoor in the ceiling, then " +
       "climbs through it. The trapdoor closes behind them.\n");
    tell_room(INTR +"apoth1", QCTNAME(TP) +" climbs through a trapdoor "+
        "in the floor and lets it swing closed behind them.\n");
    TP->move_living("M", INTR + "apoth1",1,0);
    return 1;
}


public mixed
up_trapdoor()
{
    write("You go up the ladder and push on the trapdoor above you, "+
       "then climb through the opening.\n");
    say(QCTNAME(TP) + " pushes open a trapdoor in the ceiling, then " +
       "climbs through it. The trapdoor closes behind them.\n");
    return 0;
}

/* Start the room tells as soon as someone enters the room */
void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (interactive(ob))
      start_room_tells();
}
