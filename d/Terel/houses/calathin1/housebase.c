/*
 * /d/Terel/houses/calathin1/housebase.c
 *
 * Base file for townhouse1
 *
 * Lilith March 2022
 *
 */

#pragma strict_types

#include "h1.h"

inherit GEN_HOUSE;
inherit "/lib/help";

#include <macros.h>
#include <stdproperties.h>
#include <filter_funs.h>

void set_items_bedroom();
void set_items_kitchen();
void set_items_living();
void set_items_outdoor();
void set_items_wood();
void set_items_stone();


/*
 * Function name:        create_house_room
 * Description  :        Use create_house_room() to make rooms in
 *                       player houses across Genesis.
 */

void create_house_room() 
{
}

nomask void create_room() 
{

    create_house_room();

    set_house_name(HOUSE_NAME);
    set_junkyard_room(JUNK_ROOM);
    set_tell_time(random(600) + 200);
    add_prop(NO_COFFIN_PLACEMENT, 1);
    add_prop(ROOM_M_NO_TELEPORT_TO, block_teleport);
    add_prop(ROOM_I_INSIDE, 1);

    add_help_topic("owner",     HELP + "for_owner");
    add_help_topic("townhouse", HELP + "for_owner");
    add_help_topic("house",     HELP + "for_owner"); 
	
}

public void hook_notify_item_returned(object ob, object to)
{
    //This can be replaced by custom messaging if desired.
    ::hook_notify_item_returned(ob, to);
}

public void hook_notify_item_tossed(object ob, object junkyard)
{
    //This can be replaced by custom messaging if desired.
    ::hook_notify_item_tossed(ob, junkyard);
}

public void hook_notify_item_destroyed(object ob)
{
    //This can be replaced by custom messaging if desired.
    ::hook_notify_item_destroyed(ob);
}


public object *
get_view(string *arr)
{
    object *inv = ({});

    foreach(string path: arr)
    {
	object room = find_object(path);
	if (objectp(room))
	    inv += all_inventory(room);
    }

    if (sizeof(inv))
	inv = FILTER_CAN_SEE(FILTER_LIVE(inv), this_player());

    return inv;
}

/*
 * Function name:        set_items_outdoor
 * Description  :        Items added to house rooms when you include
 *                       the line set_items_outdoor(); 
 *                       May also add room specific tells in here.
 *                       Use for yards of houses
 */

public void
set_items_outdoor()
{
    add_item(({"air", "breeze", "wind"}), "The wind claws with icy "+
        "fingers. It smells of woodsmoke and pine.\n");
    add_cmd_item(({"air", "breeze", "wind"}), ({"smell", "sniff"}),
        "The air smells of a mixture of woodsmoke and pine sap.\n");
    add_item( ({"sky", "up"}), 
        "The sky is a clear, deep blue with no sign of dragons.\n");				
    add_item(({"townhouse", "walls", "logs"}), 
        "This is a two-story townhouse built of silver pine logs, "+
        "with pretty white-clay chinking.\n");
    add_item(({"chinking", "chink", "clay", "white clay"}), 
        "The chinks between the logs have been filled in with a "+
        "mixture of white clay and straw.\n");
    add_item(({"view", "surroundings"}),
        "To the west is a stunning view of jagged, snow-capped "+
        "mountains. South is a river flowing sluggishly east. "+
        "The town square lies east, while north is dense forest.\n");
    add_item(({"north", "forest", "dense forest", "silver pine forest"}),
        "Calathin has slowly encroached upon the forest of silver "+
        "pines that lies north of the river and extends all the "+
        "way up into the high hills of the icy mountains. The "+
        "forest here has been cut back and thinned out, as "+
        "evidenced by the numerous stumps scattered throughout.\n");
    add_item(({"tree stumps", "stumps"}), "Trees have been logged "+
        "extensively in this section of Calathin, and numerous "+
        "stumps can be seen.\n");
    add_item(({"river", "south" }), "Some distance south of here, "+
        "a river makes it's way to the east, carrying water from "+
        "the mountains to the sea.\n");		
    add_item(({"mist", "ice mist"}), 
        "The mist is just the effect of the chill weather on the "+
        "water vapor in the air.\n");
    add_item(({"ground", "floor", "down"}),
        "The ground is covered in a thin layer of ice and snow. "+
        "It never seems to warm up enough to completely melt.\n");
    add_item(({"ice", "snow"}), "It is ubiquitous. Ice and snow "+
	    "everywhere. It wouln't be Calathin without it.\n");
    add_item(({"west", "mountains", "mountain range"}),
        "These mountains are beautiful.  Snow capped and majestic.  "+
        "Breathtaking. And terrifying.\n");
    add_item(({"east", "town", "town square", "building", "buildings"}), 
        "The number of buildings increases toward the east, where the "+
        "center of town lies.\n");	
    add_item(({"terrace", "stone terrace", "slate terrace", "slate"}), 
        "The terrace is made of pieces of slate fitted together "+
        "with a handspace between.\n");
		
		
    start_room_tells();
    add_tell("A blast of cold air freezes your eyebrows.\n");
    add_tell("A pleasant pine scent teases your nose.\n");
    add_tell("The sky is a beautiful cerulean blue color.\n");
    add_tell("A puff of ice mist drifts by.\n");	
    add_tell("A change in the direction of the wind brings a "+
        "strong scent of woodsmoke.\n");
    add_tell("The boughs of the pines sway in the wind.\n");
    add_tell("Something large flies by far overhead.\n");
    add_tell("You hear a commotion to the east.\n");
	add_tell("Some thumping and shouts announce the opening "+
        "and closing of the West Gate.\n");

}

/*
 * Function name:        set_items_wood
 * Description  :        Items added to wooden houses when you
 *                       include the line set_items_wood(); 
 *                       May also add room specific tells in here.
 *                       Use for houses made of wood
 */

public void
set_items_wood()
{
    add_item(({"floor", "wood floor", "pine floor", "pine boards",
        "pine floor", "boards", "ground", "down"}),
        "The floor is made of pine boards about the width of your "+
        "hand. They have been sanded fairly smooth, and polished "+
        "to a mellow sheen with beesewax.\n");
    add_item(({"walls", "log walls"}),
        "The walls of this townhouse are made of pine logs that "+
        "have been peeled and sanded smooth. White clay chinking "+
        "fills the spaces between the logs and brightens up the "+
        "interior.\n");
    add_item(({"chinking", "chink", "clay", "white clay", "chinks"}), 
        "The chinks between the logs have been filled in with a "+
        "mixture of white clay and straw to keep the wind out.\n");
    		
}

/*
 * Function name:        set_items_stone
 * Description  :        Items added to stone houses when you include
 *                       the line set_items_stone(); 
 *                       May also add room specific tells in here.
 *                       Use for houses made of stone
 */

public void
set_items_stone()
{
	add_item(({"fireplace", "grate", "brick"}),
        "The fireplace is made of brick and faced in dark slate. "+
        "it absorbs and radiates heat pretty well, keeping the "+
        "everpresent wintery chill at bay.\n");
    add_item(({"stone", "slate" }),
        "Most of the stone here is slate. The stone is dark gray "+
        "and soft enough to cut easily, but still durable.\n");

}



/*
 * Function name:        set_items_bedroom
 * Description  :        Items added to house rooms when you include
 *                       the line set_items_bedroom(); 
 *                       May also add room specific tells in here.
 *                       Use for bedrooms in houses
 */

public void
set_items_bedroom()
{
    add_item(({"bedroom", "bed room", "loft"}),
        "This is the bedroom of the house, where the owner "+
        "sleeps. It is a loft area, open to the living "+
        "room below.\n");
    add_item(({"chimney", "brick", "brick chimney"}),
        "The brick chimney rises up from the kitchen below, carrying "+
        "the smoke of burning wood, and radiating heat into "+
        "the loft area here, where the owner sleeps.\n");
    add_item(({"north", "north wall" }), 
        "North is a wall with a small window and a wardrobe.\n");
    add_item(({"west", "west wall", "east wall", "east"}), 
        "The wall is the sleeply slanting roof of the "+
        "townhouse. It is made of pine logs, like everything "+
        "else.\n");		
    add_item(({"ceiling", "roof", "up"}),
        "The ceiling and roof of this townhouse also form the "+
        "east and west walls of the loft.\n");
    add_item(({"south", "south wall", "south windows"}),
        "South is a railing that marks where the loft ends. "+
        "Beyond it are two windows that let in light.\n");
    add_item(({"railing", "rail" }),
        "The railing keeps people from falling off of the edge "+
        "of the loft. It might be possible to jump over it, "+
        "if you don't mind the risk of injury.\n");
    add_item(({"window", "windows", "north window", "south window",
        "south windows", "trees", "buildings", "sky", "small window"}),
        "Through the window you see the tops of other buildings, "+
        "blue sky, and trees. Lots and lots of trees.\n");		
    add_item(({"stairs"}),
        "There is a set of stairs in the northeast corner of the "+
        "room. It leads down into the kitchen.\n");
		
    set_items_wood();
	
    start_room_tells();
    add_tell("A blast of wind causes the house to creak.\n");
    add_tell("A shaft of sunlight sets the pine floor aglow.\n");
    add_tell("A slight cool draft puffs past you.\n");
	add_tell("You can feel heat radiating from the chimney.\n");
    add_tell("A feeling of peace and comfort settles upon you.\n");
    add_tell("The warmth of this home is a welcome respite from "+
        "the bitter cold outside.\n");	

}

/*
 * Function name:        set_items_kitchen
 * Description  :        Items added to house rooms when you include
 *                       the line set_items_kitchen(); 
 *                       May also add room specific tells in here.
 *                       Use for kitchens in houses
 */

public void
set_items_kitchen()
{
    add_item(({"kitchen", "dining"}),
        "This is the kitchen of the townhouse. It opens south to "+
        "the living room and north to the icy garden. Stairs in the "+
        "northeast corner lead up to the second floor.\n");
    add_item(({"stairs"}),
        "There is a set of stairs in the northeast corner of the "+
        "room. It leads up into the loft on the second floor.\n");
    add_item(({"ceiling", "up"}),
        "The ceiling of the kitchen is pine boards, much like "+
        "the floors.\n");
    add_item(({"window", "windows", "north windows", "trees", 
	    "buildings", "sky"}),
        "Through the window you see a fence surrounding the "+
        "garden, blue sky, and trees. Lots and lots of trees.\n");		
      	  
    set_items_wood();
	set_items_stone();

    start_room_tells();
    add_tell("A wood knot pops in the fireplace.\n");
    add_tell("You hear a bubbling sound from the cauldron.\n");
    add_tell("A slight cool draft puffs past you.\n");
	add_tell("You can feel heat radiating from the chimney.\n");
    add_tell("A strong gust of air rattles the door.\n");
    add_tell("A feeling of peace and comfort settles upon you.\n");
    add_tell("The warmth of this home is a welcome respite from "+
        "the bitter cold outside.\n");
    add_tell("The scent of the stew is mouth-watering.\n");	
}

/*
 * Function name:        set_items_living
 * Description  :        Items added to house rooms when you include
 *                       the line set_items_living(); 
 *                       May also add room specific tells in here.
 *                       Use for living rooms in houses
 */

public void
set_items_living()
{
    add_item(({"living room", "living", "lounge", "lounging room"}),
      "This is the main living room of the townhouse. The front "+
      "door is south and to the north is the kitchen.\n");
    add_item(({"ceiling", "up"}),
        "The ceiling of the living room is open all the way to "+
        "the steep-sided pine board roof. You can see a loft "+
        "above.\n");
     add_item(({"north", "north wall", "north windows"}), 
        "North the entrance to the kitchen.\n");
    add_item(({"east wall", "east"}), 
        "The walls are made of peeled pine logs, like everything "+
        "else, with bright white chinking.\n");		
    add_item(({"west wall", "west"}), 
        "The walls are made of peeled pine logs, like everything "+
        "else, with bright white chinking.\n");		
    add_item(({"south", "south wall", "south windows"}),
        "South the front door, flanked by two windows.\n");
		
    set_items_wood();
}
