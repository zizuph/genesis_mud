/*
 * Thornhold
 * -- Twire/Gnim June 2016
 */
//#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"

inherit BASE_KEEP;
object guard_npc;

void
create_house()
{
    set_short("A spartan guardroom");
    set_long("This spartan guardroom serves as a functional " +
    		"duty station for the guards of Thornhold. A low oak " +
			"table dominates the room, surrounded by stout, " +
			"dwarf-sized chairs. A banner hanging from the " +
			"north wall displays a faceted white gem " +
			"against a steel-grey field. Against the west " +
			"wall are weapon and armour racks, well-stocked " +
			"with weapons and armours suitable for the guards " +
			"serving the hold. Slits in the west " +
			"east walls allow some light to filter in from the " +
			"but a thick wrought-iron lamp also hangs " +
			"suspended from the ceiling by a chain. You can " +
			"return to the courtyard to the " + 
			"east, and a tight, spiral stone set of " +
			"stairs in the southwest corner of the room " +
			"provides access to the hold's towers.\n");

     	add_item(({ "slits", "slit", }),
            "They are arrow slits, allowing guards within the " +
            "room take fire on the outside should the need " +
            "arise.\n");

     	add_item(({ "armour rack", "armour rack", "rack", 
     				"racks", "armour", "armours" }),
            "You see all manner of weapons and armours on the " +
            "racks here. It is basic guard gear, and clearly " +
            "marked as property of Clan Stoneshaft. It is " +
            "of no use to you.\n");

     	add_item(({ "banner", "gem", "white gem" }),
            "The heraldry of Clan Stoneshaft, the dwarven clan " +
            "that currently claims ownership of Thornhold.\n");
            
        add_item(({ "thornhold", "Thornhold", "hold", 
        	"fortress", "fort" }),
			"You stand within the guardroom of the great " +
			"fortress of Thornhold.\n");
		
		add_item(({ "lamp", "iron lamp", "thick wrought-iron lamp" }),
			"You see nothing special about the lamp.\n");
		
		add_item(({ "stairs", "spiral stone" }),
			"You see stone stairs spiraling to the floor above.\n");
            
    add_exit(ROOM_DIR + "west_tower",  "up");
    add_exit(ROOM_DIR + "courtyard_south",  "east");

    reset_room();
}

void
reset_room()
{
   ::reset_room();
   
    if ((!guard_npc))
    {
        guard_npc = clone_object(NPC_DIR + "dwarf_guard");
        guard_npc->move(this_object()); 
        guard_npc = clone_object(NPC_DIR + "dwarf_guard");
        guard_npc->move(this_object()); 
        guard_npc = clone_object(NPC_DIR + "dwarf_guard");
        guard_npc->move(this_object());
        guard_npc = clone_object(NPC_DIR + "dwarf_guard");
        guard_npc->move(this_object()); 
    }
}
