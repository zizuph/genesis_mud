/* cv/meeting.c
 * Nerull & Lilith Jan 2022
 * Coven Location #2 for the Faerun Vampires.
 * Any changes to these rooms should be discussed
 * by the GM of the Vamps and the Liege of Avenir.
 *
 * This room is accessed via /d/Avenir/common/dark/l3/ec2
 */

inherit "/d/Faerun/guilds/vampires/rooms/std/vampires_std_room";
inherit "/d/Avenir/inherit/emotes";

#include "/d/Faerun/defs.h"
#include "/d/Faerun/guilds/vampires/guild.h";
#include <stdproperties.h>
#include <composite.h>
#include <filter_funs.h>
#include <macros.h>
#include "/d/Genesis/sys/gem.h"

#define SEATS       "/d/Avenir/common/outpost/obj/seats/"
#define RIVER_PROP  "_confirmed_enter_river"

/* If they are to conduct meetings here, let them be private */
public int query_prevent_snoop()	{ return 1; }

/*
 * Function name: create_vampires_room
 * Description  : Constructor, redefine this to configure your room
 */
 
public void 
create_vampires_room()
{
    seteuid(getuid());
    
    add_prop(ROOM_I_INSIDE, 1);
	add_prop(ROOM_I_LIGHT, 1);
	add_prop("_not_in_flux_zone", 1); //This prevents Source-related room tells.	
    add_prop(OBJ_S_SEARCH_FUN, "do_search");
    add_prop(OBJ_I_SEARCH_TIME, 10);
	
    set_short("meeting place");
    set_long("A chamber has been carved into the living rock by a "
        +"subterranean river that runs swiftly by, depositing small, "
        +"smooth stones to form a beach of sorts. An area nearest the "
        +"wall has been cleared and leveled, and thick carpets piled "
        +"upon it to create a place to meet and relax in comfort. "
        +"A variety of chairs form a circle around a massive "
        +"slab of stone that functions as a table. A statuary "
        +"fountain rests in the center of it, contributing a "
        +"coppery scent of blood to the space. Over by the river "
		+"is a basket swing. A massive candelabra hanging overhead "
        +"suffuses everything in a warm glow.\n");
		
    add_object("/d/Avenir/common/outpost/cv/obj/meeting_table");  
	
	add_object(SEATS +"stool");
    add_object(SEATS +"basket_swing");
	add_object(SEATS +"throne_chair_e");
	add_object(SEATS +"throne_chair_r");	
	add_object(SEATS +"wingback_chair_v");
	add_object(SEATS +"wingback_chair_s");
	add_object(SEATS +"cross_chair_f");
	add_object(SEATS +"cross_chair_w");	
	
    add_exit("/d/Avenir/common/dark/l3/ec2",  "west");

	add_item(({"walls", "wall", "west wall", }),
        "The stone of the walls appears to be a pale limestone that "
        +"has been eroded by water over the eons. The walls are lumpy, "
        +"yet smooth.\n");
    add_item(({"beach","stones", "smooth stones", "shore", "clearing" }),
        "Smooth, glossy stones in myriad shapes and sizes have been "
        +"deposited on the shore of the subterranean river.\n");
    add_item(({"river", "subterranean river", "water"}),
        "This subeterranean river is made of the purest water, water "+
        "that has filtered down through the Dragon Mountains far above. "+
        "The river rushes by very quickly, tumbling small stones as "+
        "it passes through.\n");		
    add_item(({"candelabra", "chandelier", "candles","candlelight"}),
        "A massive candelabra is suspended from the cavern ceiling by a "
        +"thick chain. Hundreds of candles cast a muted, golden light on "
	    +"the space beneath it.\n");
    add_item(({"ceiling","stalactites"}),
        "The ceiling of this chamber is draped in glittering darkness"
        +".\n");
    add_item(({"dark", "darkness"}), "The darkness is so deep that "
        +"your eyes cannot penetrate it.\n");	
    add_item(({"floor", "ground"}),
        "The ground is mostly limestone that has been leveled to provide "
        +"a lounging area. It is covered in thick carpets brought "
        +"here from all over the world.\n");
    add_item(({"carpets", "thick carpets"}),
        "These carpets are layered over each other, making a thick "
        +"and luxurious floor covering.\n");
    add_item(({"fur", "furs", "mink", "ermine", "fox"}),
        "Soft lustrous guard hairs and plush deliciously soft underfur "
        +"are delightful to touch and sink into.\n");
	add_item(({"fountain", "statue", "statuary fountain", "blood",
        "blood fountain", "bowl", "feldspar bowl", "fountain bowl"}),
	    "There is a fountain in the center of the table. The statue "+
		"is humanoid in shape, but indistinct. It is made of white "+
		"feldspar that sparkles in the candlelight. Blood runs "+
		"from the neck of the statue and down over the body, "+
		"forming a thin curtain that contrasts beautifully against "+
		"the pale stone  The blood is captured in a wide, shallow "+
		"bowl made of the same stone.\n");
    reset_faerun_room();
}

string 
do_search(object searcher, string str)
{
    object ob;

	if (str != "beach" && str != "stones" && str != "shore" )
      return "Your search reveals nothing special.\n";
    
	write("There are so many stones to sort through...\n");

    ob = RANDOM_GEM_BY_RARITY(GEM_COMMON); 
    ob->move(searcher, 1); 
    return "You find "+LANG_ASHORT(ob)+" amongst the stones "+
        "and pick it up.\n";
}


public int
f_dive(string str)
{	
	if (!parse_command(str, ({}),
	    "[down] [in] / [into] [the] 'river' / 'water'", str))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }
	
    if (!this_player()->query_prop(RIVER_PROP))
    {
		this_player()->add_prop(RIVER_PROP, 1);
        write("The river is running very fast and you would "+
            "likely be swept away. Are you sure you want to do "+
            "this?\n");
	    return 1;
    }
	if (this_player()->query_prop(RIVER_PROP))
		this_player()->remove_prop(RIVER_PROP);
	string where = one_of_list(({ 
	    "/d/Avenir/common/dark/l1/waters",
	    "/d/Avenir/common/dark/l2/add/t57", 
        "/d/Avenir/common/dark/l3/nc1" })); 
    write("You "+ query_verb() +" into the river which sweeps "+
        "you away and deposits you somewhere else.\n");
    say(QCTNAME(this_player()) + " disappears into the river.\n");
    this_player()->move_living("M", where);


    return 1;
}

public void
init()
{
	::init();
    add_action(f_dive, "dive");
    add_action(f_dive, "jump");
    add_action(f_dive, "swim");
    add_action(f_dive, "enter");
	
	add_action(emote, "emote");
}


public int
query_prevent_snoop(void)       { return 1; }
	