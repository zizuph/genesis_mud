#pragma strict_types
// file name:        port12.c
// creator(s):       Ilyian
// purpose:        THIS IS NOW THE MARINER'S LANDING POINT
// revision history: Boriska Aug 95 added sailor NPC
//		     Denis, Sep'96: Changes due to the port inheritance recode.
//           Tapakah, 05/2009: cancelled ship to Shire.
//           Lilith Feb 21, 2014: updated room desc to remove shipline info
//           Lilith, Sep 2021: Added fishing prop.
//           Lilith, Mar 2022: Converted to Mariner's landing pier.

#include "/d/Avenir/common/port/port.h"
#include "/d/Avenir/common/sea/defs.h"
inherit "/d/Avenir/common/sea/lib";
// inherit PORT_ROOM;

int
query_standard_water_room ()
{
  return 0; 
}

public void
create_room(void)
{	
    add_exit("port11", "east");
    add_exit(OUTPATH + "n1", "north");
    add_exit("port13", "west");
	add_row_exit(AVENIR_PORT, "south", no_go, 1);
	
    set_sailing_difficulty(NORMAL_DIFFICULTY);
    set_sailing_fail_message(sprintf("You feel uncomfortable departing the "+
      "safety of the berth here at the Port of Sybarus.\n"));
    set_sailing_difficulty_message(sprintf("You navigate into the " +
      "rushing waters of the Rift of Sybarus.\n"));
 
    set_short("Mariner's berth at the Port of Sybarus");
    set_long("You are on a wide ledge between the cavern wall to " +
             "the north and the churning waters of the rift lake "+
			 "to the south. " +
             "Mist seems to cling everywhere, making your footing " +
             "unsteady. "+
             "This is the berth reserved for Mariners and other "+
             "sailing hobbyists. "+			 
             "Berths for ships line the ledge, which narrows "+
             "to the west, and continues easterly, toward the amenities "+
		     "of the Port of Sybarus. To the north, an "+
             "opening has been broken into the rock face, leading "+
			 "downwards into darkness.\n");

    IN
    LIGHT
	add_prop(ROOM_I_TYPE, ROOM_BEACH);
	add_prop("_live_i_can_fish", "saltwater");
    add_prop("_live_s_can_fish", "saltwater");	

    add_item("mist",
	    "The white, flowing mist that fills the cavern rushes " +
        "around you in ghostly tendrils, making eerie shapes appear " +
        "before your eyes.\n");

    add_item(({ "water", "waters", "lake" }),
        "The churning water of this underground lake is a shade of " +
        "blue so deep it is almost black. Its surface is distorted by " +
        "the waves, and it all moves slowly from the great rift on the " +
        "west end of the cavern to the waterfall at the east ledge.\n");

    add_item(({ "floor", "ground" }),
	    "The ground beneath you is smooth and wet from " +
        "the mist that clings to everything. It appears to be man made, " +
        "hewn from the natural rock.\n");
    add_item(({ "ledge", "north ledge"}),
        "The ledge narrows to the west, and continues east toward some "+
	    "buildings which mark the port facilities of Sybarus.\n");
    add_item(({"rift", "lake", "rift lake" }),
        "The rift in the west wall of the cavern is " +
        "immense, and through it flows massive amounts of water " +
        "and wind, creating the mist that you see around you. It is " +
        "difficult to tell from here, but you think you can detect a " +
        "hint of sunlight on the water near the rift.\n");
			 
    add_item(({ "wall", "walls" }),
        "These rough hewn walls of the cavern " +
        "appear to be man made, hewn from the natural rock. They are " +
        "wet from the mist and spray of the stormy port, and rivulets " +
        "of water run down them to the floor.\n");

    add_cmd_item(({ "water", "ledge", "off", "into" }),
		({"dive", "jump", "leap" }),
        "The water is too rough here, it would be suicide.\n");
    add_cmd_item(({ "lake", "water" }),
		({ "swim", "enter" }),
		"It is too rough to swim in the water here.\n");			 

    add_prop(ROOM_I_NO_CLEANUP, 1);

    add_npc(PORT + "mon/sailor", 1);
}
