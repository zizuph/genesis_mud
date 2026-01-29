// file name:   /d/Avenir/common/outpost/fort6.c
// creator(s):  Kazz    March 1995
// last update: July 2009 Zielia, description update
//		June 2004 Lilith, exit update.
//		Denis, Jul'96: Removed the traces of the tomato and carts quests
// purpose:     outpost storage room
// note:	pier worker (Jarod) deposits crates here.
// bug(s):
// to-do:       retain pointer to tomatoes? (need?)

#pragma strict_types
#include "/d/Avenir/common/outpost/outpost.h"
#define EXIT_CHECK "_i_found_secret_tunnel"
inherit OUTPOST +"fort_base";

int 
test_sw()
{
    if (TP->query_prop(EXIT_CHECK))
    {
        write("You weave through the crates and fallen stone.\n");
        return 0;
    }
    write("There is no obvious exit southwest.\n");
    return 1;
}	

string
check_corner()
{
	write("The corners of the room are draped in shadow, but "+
        "hidden behind some dusty forgotten crates, you can see "+
        "that more stone has crumbled away from the southwest corner, "+
        "creating an opening of sorts.\n");
    TP->add_prop(EXIT_CHECK, 1);   
}

string 
check_opening()
{
    write("The opening isn't very large, but it does appear "+
        "you have revealed a southwest passage of sorts.\n");    
    TP->add_prop(EXIT_CHECK, 1);		
}	
void create_fort_room()
{
    set_short("a storage room");
    set_long("This storage room is the shape of right triangle, "+
        "with the south wall cutting sharply from southwest to "+
        "northeast. Crates and boxes are strewn about and piled "+
        "against the west wall. The south wall is natural stone, "+
        "some of which has crumbled away in places. It appears that "+
        "frequent attempts have been made to clean up the rubble, "+
        "with the larger pieces of stone cut into blocks and "+
        "stacked for use during future construction.\n");

    add_exit("fort3", "north", 0);
    //add_exit("fort5", "northeast", 0, 0, 1);
    add_exit("secret/tunnel7","southwest", test_sw, 0, 1);
    add_exit("secret/tunnel7","opening", test_sw, 0, 1);
    add_exit("secret/tunnel7","passage", test_sw, 0, 1);

    add_fort_room();
    add_exit_views();

    add_item(({"wall", "north wall", "ceiling"}),
        "The north wall and ceiling are naturally smooth, "+
        "together they curve overhead to the north.\n");
    add_item(({"west wall"}),
        "The west wall is naturally smooth, behind piles of "+
        "boxes and crates.The crates mostly appear to have been recently " +
        "brought here for storage, though you can view a few "+
        "dusty forgotten crates mixed in as well.\n");   
    add_item(({ "crate", "crates", "box", "boxes" }),
        "Many crates and boxes are strewn about or piled near the west "+
        "wall. They have various stamps written on them in many languages "+
        "and are probably imports from the Outlands brought here for "+
        "temporary storage.\n");
    add_item(({"forgotten crates", "dusty crates" }),
	    "Barely viewable amongst the many other crates piled along "+
	    "the west wall, are several crates that look like they "+
	    "have been stored here a long time. They are covered "+
	    "with a thick layer of dust and tucked away into "+
	    "the southwest corner, nearly hiding it from view.\n"); 
    add_item(({"south wall", "southwest wall" }),
        "It is natural stone, some of which has been cut cleanly. "+
        "In contrast, the southwest corner seems to be crumbling.\n");
    add_item(({"stack", "stacks", "stone", "stones", "rubble",
        "natural stone", "blocks" }),
        "Stone blocks have been stacked near the wall that "+
        "slashes across the room from the southwest corner "+
        "to the northeast corner.\n");
    add_item(({"northeast corner"}), "It is crowded with crates.\n");
    add_item(({"southwest corner"}),
        check_corner);
    add_cmd_item(({"southwest corner"}), "search",
        check_corner);	
    add_item(({"opening", "passage"}),
        check_opening);
    add_item(({"cavern"}),
        "The cavern has been used to provide some walls and "+
	    "ceiling for the fort.\n" );
    
  room_add_object(PORT + "obj/std_crate", 6);
  room_add_object(PORT + "obj/crate", 1);
}
