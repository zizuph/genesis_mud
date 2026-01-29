/*
 * G4.c
 * By Skippern
 */
#pragma strict_types

#include "../erech.h"

inherit E_STD + "vale.c";
inherit E_QUEST + "tasker.c";

#include <macros.h>
#include <stdproperties.h>

#include TERRAIN_TYPES

/* Prototypes */
public void         create_area_room();
public int          enter(string dir);

/*
 * Function name:    create_area_room()
 * Definition   :    Creates the room.
 */
public void
create_area_room()
{
    set_short("In the vale of Erech.");
    set_areatype(AREATYPE_BUSHES); /* Areatype, check ~Gondor/defs.h
				    * for specifications */
    set_area("northern");          /* southern, central or northern */
    set_areadesc("field");         /* jupp */
    set_grass("long");             /* grass description */
    set_areaname("Erech");         /* name of the area */
    set_extraline("To the north the White Mountains towers up, and at " +
        "its foot a road can be seen. To the west a strange hill at " +
        "the end of a ridge can be seen. The field is dark green, some " +
        "bushes and small trees are scatered over the field. A bit to " +
        "the west the sound of running water can be heard. It seems like " +
	"there are some tracks on the ground.");
                                   /* set extra longdesc */
  
    vale_items();
    field_items();
    
    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_ERECH_VALE);

    add_herbs("field");

    if (item_id("bushes"))
        remove_item("bushes");
    add_item("bushes", "Some bushes growing here on the field. It looks " +
	"like some tracks leads under the bushes.\n");
    add_item( ({"tracks", "tracks on the ground" }), "It looks like the " +
        "tracks leads to a cave of some sort.\n");

    add_exit(E_FIELD + "G5.c", "south", &on_field(), 3, 1);
    add_exit(E_VALE + "G3.c", "north", &blocked_path(), 3, 1);
    add_exit(E_FIELD + "F4.c", "west", &blocked_river(), 3, 1);
    add_exit(E_VALE + "H4.c", "east", &blocked_path(), 3, 1);

    reset_room();
}

void
reset_room()
{
    object o;

    o=clone_object(one_of_list( ({ "/d/Gondor/common/npc/rabbit", 
				   "/d/Gondor/common/npc/fox" }) ));
    o->set_random_move(12, 1);
    o->set_restrain_path(E_FIELD);
    o->move(this_object());
}

public void
init()
{
    ::init();
    add_action(enter, "enter");
}

public int
enter(string dir)
{
    int i;

    if (dir)
    {
        switch(dir)
	{
    	    case "cave":
	    case "bushes":
	        write("You crowls through some bushes and into a small " +
		    "cave.\n");
		say(QCTNAME(this_player()) + " crowls into some " +
		    "bushes.\n");
		complete_task(0);
		this_player()->move_living("M", E_QUEST + "cave.c", 1, 0);
		say(QCTNAME(this_player()) + " arrives " +
		    "crawling.\n");
		i = 1;
		break;
	    default:
	        notify_fail("There is no "+dir+" to enter.\n");
		i = 0;
		break;
	}
	return i;
    }
    notify_fail("Enter what?\n");
    return 0;
}



