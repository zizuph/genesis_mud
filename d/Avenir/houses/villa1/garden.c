/*
 * villa1/garden.c
 *
 * Lilith, Feb 2022
 *
 * This is probasbly the most complex room in the villa.
 */

#pragma strict_types

#include "villa1.h"

inherit V1 +"housebase";
inherit "/d/Gondor/common/lib/drink_water.c";
inherit "/d/Avenir/inherit/sair_wall";

#include <macros.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <composite.h>
#include "/d/Avenir/common/city/zigg/zigg.h"
#include "/d/Avenir/common/city/zigg/garden/flowers.h"
#include "/d/Avenir/common/herbs/herbsearch.h"

/* Pick/Pluck limit per person. */
#define LIMIT     5
#define FLOWER    ZIGG +"garden/single"
#define SEE_WEST  ({ V1 +"pool", })
#define SEE_SOUTH ({ V1 +"terrace_c" })

void garden_flowers(void);
void add_fruit(string str);
void add_flower(string str, mixed cols = 0);
static string *fruits = ({});
static mapping picked = ([]), flowers = ([]);
string *vh = HERB_MASTER->query_herbs( ({"garden"}) );

public void
reset_room(void)
{
    ::reset_room();

    picked = ([]);
    set_searched(0);
}

public string 
west_view(void)
{
    object *live = get_view(SEE_WEST);

    if (!sizeof(live))
	return "";
    if (sizeof(live) == 1)
	return ", where "+ COMPOSITE_LIVE(live) + " is soaking";    
    else 
	return ", where "+ COMPOSITE_LIVE(live) + " are soaking";

}

public string
south_view(void)
{
    object *live = get_view(SEE_SOUTH);

    if (!sizeof(live))
	return "";
    if (sizeof(live) == 1)
	return " where "+ COMPOSITE_LIVE(live) + " is standing";  
    else
	return " where "+ COMPOSITE_LIVE(live) + " are standing";
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
	
    room_add_object(HOBJ + "hammock_v1");
    room_add_object(HOBJ + "lounger_n");
	room_add_object(HOBJ + "lounger_s");
	
    add_exit("pool", "pool");
    add_exit("bedroom", "south");
    add_exit("terrace_c", "southwest");

    set_short("private");
    set_long("This is the private garden of the villa. "+
      "It is dominated by a large fruit tree with bright green "+
      "leaves and dark purple fruits which is underplanted with "+
      "flowers and shrubs. There are planting beds with more "+
      "flowers and herbs along the north wall, and between them "+
      "is a hammock. "+
      "Two lounge chairs are situated near a beautiful hot spring "+
      "pool@@west_view@@. "+
      "A stone drinking fountain is midway between the chairs and "+
      "the tree, bubbling with fresh water. "+
	  "A restful view of the Sea of Sybarus is north, where you "+
      "can watch the waves wash up onto a white sand beach. "+
      "South is door to the bedroom, and southwest is the main "+
      "terrace@@south_view@@.\n");

    add_help_topic("here",  "/d/Avenir/houses/help/garden_help");
    add_help_topic("room",  "/d/Avenir/houses/help/garden_help");
    add_help_topic("garden", "/d/Avenir/houses/help/garden_help");

    add_prop(ROOM_I_TYPE, ROOM_BEACH);

    set_items_outdoor();
    set_items_stone();
    add_sair_wall();
    set_sair_dest(({L2+"center", PORT +"port10", OUTPOST +"fort5"}));	
    remove_item(({"plant", "plants"}));
    add_item(({"here", "garden"}), "This is a lovely garden with "+
      "plenty of seating, a fruit tree, and herbs and flowers. "+
      "There is also a drinking fountain with fresh spring "+
      "water.\n");
    add_item(({"pool", "hot spring pool", "bottom", "bottom of pool"}),
      "It is a stunning blue pool of water. Wisps of "+
      "mist float here and there along the surface, evidence "+
      "that it is much warmer than the surrounding air.\n");

    add_item(({"west"}), "The pool lies west of here.\n");
    add_item(({"east"}), "There is natural stone in that direction.\n");
    add_item(({"east wall", "something"}), 
	  "The east wall is natural stone with "+
      "something carved into it. You might need to use your "+
      "hands to figure out what it is.\n");
    add_item(({"north"}), "You see the sea of Sybarus and some of "+
      "the islands.\n");
    add_item(({"south"}), "The bedroom is south of here.\n");
    add_item(({"fountain", "stone fountain", "drinking fountain "+
      "stone drinking fountain", "spring"}), 
      "A stone fountain from which a small spring bubbles.\n"+
      "You can probably drink from it.\n");
	  
    add_item(({"tree","single tree","mangosteen tree"}), 
      "This mangosteen tree has been meticulously groomed into a "+
      "spherical shape. The bark of the tree is rough and almost "+
      "black. The leaves are glossy bright green on top and a "+
      "lighter yellow-green underneath, and beneath them hang "+
      "purple mangosteen fruits. The fruit of the mangosteen "+
      "tree is a delicacy, and the juice of the skin can be "+
      "used as a dye.\n");
    add_item(({"mangosteen","mangosteens","fruit","fruits",}), 
      "Fruits in varying stages of ripeness hang beneath the "+
      "leaves of the mangosteen tree.\n");
    add_item(({"mangosteen blossom","mangosteen blossoms",
      "mangosteen flower","mangosteen flowers"}), 
      "There are no flowers on the mangosteen tree right now.");
    add_fruit("mangosteen");

    add_flower("rose");
    add_flower("moonflower");
    add_flower("dragon flower");
    add_flower("daisy");
    add_flower("forget-me-not");
    add_flower("pansy");
    add_flower("passionflower");
    add_flower("peony");
    add_flower("poppy");
    add_flower("tuberobe");
    add_flower("zinnia");
    garden_flowers();
	add_item(({"flower beds", "flower bed", "herb", "herbs", "planters",
      "planting bed", "planting beds", "plants", "plant", "planter",
      "shrub", "shrubs"}), 
	  "Flowers have been skillfully and artfully interplanted with "+
      "various garden herbs to create a natural aesthetic that softens "+
      "all the stone of the villa.\n");  
    set_up_herbs(({ one_of_list(vh), one_of_list(vh), one_of_list(vh) }),
      ({ "garden", "bed", "planter", "flowerbed", "planting bed", 
      "flowerbeds", "planting beds", "planters" }), 5);	
    
    set_drink_from(({"fountain", "drinking fountain", "spring"}));	
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

void
add_flower(string str, mixed cols = 0)
{
    string *items = m_flowers[str];

    if (!pointerp(items))
	return;

    if (stringp(cols))
	cols = ({ cols });
    else if (!pointerp(cols))
	cols = ({ });

    flowers[str] = cols;
    remove_item(items[0]);
    add_item(items[0], items[1]);
}

void
rem_flower(string str)
{
    if (!flowers[str])
	return;

    m_delkey(flowers, str);
    remove_item(m_flowers[str][0]);
}

string *
query_flowers(void)
{
    return m_indexes(flowers);
}

void
add_fruit(string str)
{
    fruits += ({ str });
}

void
rem_fruit(string str)
{
    if (!IN_ARRAY(str, fruits))
	return;

    fruits -= ({ str });
}

string *
query_fruits(void)
{
    return fruits;
}

void
garden_flowers(void)
{
    string desc;
    int sz;

    remove_item(({"flower","flowers"}));


    sz = m_sizeof(flowers);
    if (!sz)
	return;

    if (sz > 1)
    {
	desc = "The garden is filled with a myriad of colourful "+
	"flowers, among which are "+
	LANG_PWORD(COMPOSITE_WORDS(m_indexes(flowers)));

    }
    else
    {
	desc = "You only see one kind of flower in the area, "+
	m_indexes(flowers)[0];
    }

    add_item(({"flower", "flowers"}), desc + ".\n");
}


int
pluck_flower(string str)
{
    object ob;
    string god, file;
    string verb = query_verb();
    string name = TP->query_cap_name();

    if (!strlen(str))
	return NF(CAP(verb) + " what?\n");

    if (str == "flower" || str == "flowers" ||
      str == "fruit" || str == "fruits")
    {
	write("Try to be more specific on what you wish to "+ verb +".\n");
	return 1;
    }

    if (picked[name] && (picked[name] >= LIMIT))
    {
	write("You get a strange chill as you reach toward the plant. "+
	  "You sense that the goddess Sashluph believes you have "+
	  "already taken as much as you deserve.\n");

	return 1;
    }

    if (!parse_command(str, ({ }), "[a] / [the] %s", str))
	return NF(CAP(verb) + " what?\n");

    if (IN_ARRAY(str, fruits))
    {
	switch(str)
	{
	case "mangosteen": file = (ZIG_FOOD + "mangosteen"); break;
	}
    }
    else if (IN_ARRAY(str, m_indexes(flowers)))
    {
	file = SINGLE;
    }
    else
    {
	return NF(CAP(verb) + " what?\n");
    }

    if (!picked[name])
	picked[name] = 1;
    else
	picked[name]++;

    if (!objectp(ob = clone_object(file)))
    {
	write("You pull and pull, but the "+ str +" refuses "+
	  "to come free.\nYou should contact a wizard about "+
	  "this issue.\n");
	return 1;
    }

    if (ob->is_zig_food())
    {
	str = LANG_ADDART(ob->singular_short());
    }
    else
    {
	if (sizeof(flowers[str]))
	    name = one_of_list(flowers[str]);
	else
	    name = "random";

	ob->set_flower(str, name);
	str = LANG_ADDART(ob->short());
    }

    write("You "+ verb +" "+ str +".\n");
    say(QCTNAME(TP) +" "+ LANG_PWORD(verb) +" "+ str +".\n");

    ob->move(TP);
    ob->force_heap_merge();

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
    sair_init();
    add_action(pluck_flower, "pick");
    add_action(pluck_flower, "pluck");
}
