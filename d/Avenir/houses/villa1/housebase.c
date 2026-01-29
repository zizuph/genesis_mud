/*
 * /d/Avenir/houses/villa1/housebase.c
 *
 * Base file for villa1
 *
 * Lilith Nov 2021
 *
 */

#pragma strict_types

#include "villa1.h"

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

    set_house_name("av_villa1");
    set_junkyard_room(JUNK_ROOM);
    set_tell_time(random(350) + 100);
    add_prop(NO_COFFIN_PLACEMENT, 1);
    add_prop(ROOM_M_NO_TELEPORT_TO, block_teleport);
    add_prop(ROOM_I_INSIDE,1);

    add_help_topic("owner",  "/d/Avenir/houses/help/for_owner");
    add_help_topic("villa",  "/d/Avenir/houses/help/for_owner");
    add_help_topic("house",  "/d/Avenir/houses/help/for_owner"); 
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
    add_item(({"air", "breeze", "wind"}),
      "The air is refreshing and scented with flowers and salt-tang "+
      "from the nearby Sea of Sybarus.\n");
    add_cmd_item(({"air", "breeze", "wind"}), ({"smell", "sniff"}),
      "The air smells of a mixture of the sea and flowers.\n");
    add_item(({"cavern", "cavern wall", "cliff"}),
      "The grounds of the villa have been carved out of one of the walls "+
      "of the great cavern of Sybarus. The nearby cavern walls appear to "+
      "be the same pale limestone as the floors.\n");	
    add_item(({"source", "source light", "light", "veins"}),
      "Veins of the Source lace the ceiling of the subterranean cavern "+
      "and cast a benevolent light upon everything below.\n");	
    add_item( ({"ceiling", "sky", "air"}), 
      "There is open air above. You can see the Source glowing "+
      "and the ceiling of the great cavern far overhead.\n");				
    add_item(({"sea", "sea of sybarus", "sybarus sea"}),
      "The sea is dark and rough. It pounds against the shore below.\n");
    add_item(({"shore", "shoreline", "beach"}),
      "The shoreline borders the Sea of Sybarus, whose rough waters "+
      "have pounded the white limestone of this part of the cavern "+ 
      "into powdery white sand.\n");
    add_item(({"sand", "white sand"}), "There is white sand on the "+
      "beach. If you want to know more about it you're going to have "+
      "to go down there.\n");
    add_item(({"fortress", "dark fortress", "underdark"}), 
      "A dark fortress lies to the west of here. It is a barrier "+
      "between the Underdark and the islands of Sybarus.\n");
    add_item(({"island", "islands", "sybarus"}), 
      "You can see the faint outline of some islands with buildings "+
      "in the distance. The glare of the Source on "+
      "the water prevents you from seeing anything more.\n");
    add_item(({"waterfall", "great waterfall", "northwest","ocean", 
	"eastern ocean", "rift", "dragon mountains"}), 
      "To the northwest is a massive waterfall that marks where the "+
      "Eastern ocean pours through the rift in the Dragon Mountains "+
      "and down into the Sybarus cavern. It is a glorious sight "+
      "for your eyes to behold.\n");
    add_item(({"view", "surroundings"}),
      "From here you have an incredible vista: The islands of Sybarus "+
      "look like jewels in a sparkling sea. A dark fortress guards "+
      "the way to the shoreline, preventing access from the under"+
      "dark and the surface. A great waterfall pours through an "+
      "opening in the cavern wall and drops many meters down to the "+
      "Sea of Sybarus. Above it all, the crystalline veins of the "+
      "Source pulse with life-giving light and warmth.\n");		
    add_item(({"water", "pool", "hot spring", "hot spring pool"}), 
      "The water is beautiful, clear, and very inviting.\n");
    add_item(({"wisps", "mist", "wisps of mist" }),
      "Wisps of mist float here and there along the surface of "+
      "the water, evidence that the pool is much warmer than the "+
      "surrounding air.\n");	

    start_room_tells();
    add_tell("A puff of air caresses you as it flows by.\n");
    add_tell("A pleasant floral scent teases your nose.\n");
    add_tell("The Source pulses reassuringly above you.\n");
    add_tell("The sound of the surf rolling against the shore soothes you.\n");	
    add_tell("The scent of something cooking in the kitchen "+
      "reaches your nose.\n");
    add_tell("The breeze ruffles some leaves as it passes by.\n");
    add_tell("Something large flies by far overhead.\n");
    add_tell("The great waterfall catches your attention. What a "+
      "beautiful sight!\n");

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
    // Wood? What wood? We're underground--everything is stone.
    // Wood is a rare luxury.
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
    add_item(({"wall", "walls", "onyx", "white onyx", "slabs"}),
      "The walls of this villa are made from slabs of white onyx " +
      "that are striped with milky opaque and translucent bands " +
      "that glow when light shines through.\n");
    add_item(({"floor", "floors", "ground", "limestone"}),
      "The floor is natural limestone that is off-white in color. Tiny " +
      "grains of cystals glitter in the light, and you can see bits of "+
      "fossilized shells, as well. It is textured and soft underfoot.\n");
    add_item(({"stone", "blocks of stone", "stone blocks"}), 
      "The villa is made almost entirely of stone, mostly white onyx "+
      "and natural limestone.\n");
    add_item(({"terrace", "stone terrace", "limestone terrace"}), 
      "The terrace is solid limestone, an area cut out of "+
      "the cavern wall and cleared. It is quite large, having "+
      "plenty of room for seating areas, a pool, and a small "+
      "garden.\n");
    add_item(({"plant", "plants", "potted plants", "potted plant","bamboo"}),
      "The potted plant looks like bamboo. The culms are "+
      "golden yellow and the leaves are bright green. "+
      "It adds some softness and life to the villa, which "+
      "is mostly stone.\n");		

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
    add_item( ({"bedroom", "bed room"}),
      "This is the bedroom of the house, where the owner sleeps.\n");

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
    add_item( ({"kitchen", "dining"}),
      "This is the kitchen of the house.\n");

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
      "This is the main living room of the villa.\n");

}
