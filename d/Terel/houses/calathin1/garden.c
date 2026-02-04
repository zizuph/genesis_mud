/*
 * calathin1/garden.c
 *
 * Lilith, March 2022
 *
 */

#pragma strict_types

inherit "/d/Terel/houses/calathin1/housebase";
inherit "/d/Gondor/common/lib/drink_water.c";

#include "/d/Terel/include/Terel.h"
#include "/d/Terel/include/herb_arrs.h"
inherit "/d/Terel/std/herbsearch.c";
#include <macros.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <composite.h>

#define BACK_ACCESS   "/d/Terel/calathin/paths/path_s05"
#define SEE_NORTH     ({ BACK_ACCESS })
#define HELP          "/d/Terel/houses/help/"

public void
reset_room(void)
{
    ::reset_room();

    set_searched(0);
}

public string
north_view(void)
{
    object *live = get_view(SEE_NORTH);

    if (!sizeof(live))
	return "";
    if (sizeof(live) == 1)
	return " where "+ COMPOSITE_LIVE(live) + " is standing on the path "+
        "that runs along the forest's edge";  
    else
	return " where "+ COMPOSITE_LIVE(live) + " are standing on the path "+
        "that runs along the forest's edge";
}

/*
 * Function name:        create_house_room()
 * Description  :        Creates a house room from from the base file
 *                       "housebase.c"
 */
void 
create_house_room()
{
    setuid();
    seteuid(getuid());
	
    add_exit("kitchen", "south");

    set_short("enclosed garden");
    set_long("This private garden is part of the townhouse property. "+
	  "It is enclosed by a solid fence of vertically-placed pine "+
      "logs and dominated by a pine tree with snow-covered "+
      "boughs. There are some bushes planted along the fenceline, "+
      "and a couple of garden beds with cold-hardy plants in "+
      "them. "+
      "An ice-encrusted stone fountain is placed in the middle of "+
	  "the space, bubbling with a bit of fresh water. "+
	  "A restful view of the silver forest of Calathin can be seen "+
      "beyond the fence@@north_view@@. "+
      "South is a door back into the house."+
      "\n");

    set_items_outdoor();
    set_items_stone();

    add_item(({"here", "garden"}), "This is a cold-hardy garden "+
        "at the back of the townhouse.\n");
    add_item(({"bush", "bushes", "rose bushes", "hollies", 
	    "holly bushes"}), "A variety of cold-hardy bushes like roses and "+
        "holly have been planted along the perimeter of the fence.\n");
    add_item(({"planting bed", "planting beds", "beds", "plantings",
     	"plants", "herbs", "vegetables", "root vegetables", "garden beds"}),
        "There are some raised garden beds with cold-hardy herbs "+
        "and root vegetables planted in them.\n");		
    add_item(({"fence", "logs"}), "The fence was made by setting pine "+
        "logs into the ground in a stockade formation. There is no gate, "+
        "but you should be able to climb the fence if you need to.\n");		
    add_item(({"tree", "pine tree", "silver pine tree"}),
        "It looks like this tree was spared during the clear-cutting "+
        "spree that opened this part of Calathin to building. It is a "+
        "gorgeous specimen on the younger, smaller side, with full "+
        "boughs of scented pine needles. Its green is vivid against "+
        "the white of the snow and ice.\n");
    add_cmd_item(({"tree", "pine tree"}), "climb", "Climbing the "+
       "tree would cause irreparable damage to it.\n");	
    set_drink_from(({"fountain", "drinking fountain", "spring"}));		
    add_item(({"fountain", "stone fountain", "drinking fountain "+
      "stone drinking fountain", "spring", "ice-covered fountain"}), 
      "An ice-covered stone fountain from which a small spring bubbles.\n"+
      "You can probably drink from it.\n");
	  
	add_help_topic("here",  HELP +"garden_help");
    add_help_topic("room",  HELP +"garden_help");
    add_help_topic("garden", HELP +"garden_help");

    set_up_herbs( ({ one_of_list(FROST_HERBS),
	                 one_of_list(FROST_HERBS),
	                 one_of_list(FROST_HERBS) }),
             ({"here", "garden", "tree", "ground", "bush", "bushes",
               "bed", "beds", "planting beds"}), 3 );

}



/*
 * Function name:        drink_message
 * Description  :        Provides a description for drinking from the river
 */

void
drink_message(string from)
{
    write("Hovering your mouth over the little spring, you take a nice " +
      "long drink of fresh, cool water.\n");
    say(QCTNAME(TP) + " sips water from a little spring.\n");
}



int
do_jump(string str)
{

    if (!strlen(str))
	return 0;

    /* over the railing */
    if (!parse_command(str, ({}), "[over] [the] 'fence' / 'fencing'", str))
    {
	notify_fail(capitalize(query_verb()) +" over what?\n");
	return 0;
    }


    write("You "+ query_verb() +" over the fence and roll down a steep "+
    "embankment.\n");
    say(QCTNAME(this_player()) + " "+ query_verb() +"s over the "+
      "fence.\n");	
    this_player()->move_living("X", BACK_ACCESS, 1, 0);
    return 1;		

}


/*
 * Function name: init
 * Description  : initialize actions
 */
void
init()
{   
    ::init();
    init_drink();
	add_action("do_jump", "jump");
	add_action("do_jump", "leap");
	add_action("do_jump", "climb");
}
