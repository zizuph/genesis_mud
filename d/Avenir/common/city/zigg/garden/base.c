/*
 *  file name:   base.c
 *  creator:     Lucius & Zielia
 *  purpose:     Standard inherit for ziggurat rooms.
 *
 *  Revisions:
 *    Lucius, Sep 2016: Remove a couple of props to allow magic and exit
 *                      teleportation since the garden is outdoors.
 *    Lilith, Nov 2021: Removed the teleport prop since it's handed in the 
 *                      Zigg room file.
 */
#pragma no_clone
#pragma strict_types

#include "zigg.h"

inherit ZIG_ROOM;

#include <macros.h>
#include <composite.h>
#include <stdproperties.h>

#include "flowers.h"

/* Pick/Pluck limit per person. */
#define LIMIT  4

static void garden_tells(void);
static void garden_items(void);
static void garden_flowers(void);

public static int season;
public static string *fruits = ({});
public static mapping picked = ([]), flowers = ([]);

public void
zig_room(void)
{
    /*
     * Individual room code goes here.
     */
}

public void
reset_room(void)
{
    ::reset_room();

    picked = ([]);
}

static nomask void
create_room(void)
{
    setuid();
    seteuid(getuid());

    /* Temp descs. */
    set_short("terraced garden");

    ::create_room();

    /*
     * Add common code.
     */

    add_zigg();
    garden_tells();
    garden_items();
    garden_flowers();

    add_prop(OBJ_I_CONTAIN_WATER, -1);

    /* No magic props. */
    remove_prop(ROOM_M_NO_MAGIC);
    /* No teleport props. */
//    remove_prop(ROOM_M_NO_TELEPORT_FROM);
//    Above wasn't working because NO_TELEPORT was set in the zigg room file.
//    Removed it and left just NO_TELEPORT_TO, so the above isn't needed.
}

static void
add_ground(string str)
{
    string *items = ({"ground","bed","soil","floor","carpet"});

    remove_item(items);
    add_item(items, str + " " +
      "As you notice some trees growing not far away you realize "+
      "the soil must be exceptionally deep, contained by the black "+
      "stone walls of the terrace below. This is likely the reason "+
      "the ceilings of outmost rooms of the Ziggurat, though extremely "+
      "high, are substantially shorter than the soaring ceilings of "+
      "the inner courtyards.\n");
}

static void
add_views(string str, string str2)
{
    string *items = ({"view","views","panorama","city","forbidden city"});

    remove_item(items);
    add_item(items, "Beyond the narrow aqueduct, railing, the "+
      "Forbidden City of Syb'arus Aveni Idrys sprawls out in three "+
      "circling lobes. "+ str + " Diffuse Sourcelight shines down "+
      "on the "+ str2 +" a hazy dreamlike feel.\n");
}

static void
add_grass(string str)
{
    string *items = ({"grass","grasses",});

    remove_item(items);
    add_item(items, str);
}

static void
add_path(string str)
{
    string *items = ({"flagstone path","flagstones","path","paths"});

    remove_item(items);
    add_item(items, "A path made of white flagstones "+
      one_of_list(({"meanders","winds","snakes"})) +" its way through the "+
      "garden, through bushes, trees and flowers from one arbor to the "+
      "next. Most of the flagstones are flat and naturally shaped. "+
      str +"\n");
}

public string
add_rock(string desc, string gods)
{
    string *items = ({"odd stone","odd rock","odd flagstone"});

    if (!IS_SYBARITE(TP))
    {
	gods = "";
    }
    remove_item(items);
    add_item(items, "It is perfectly flat and square and set slightly away "+
	"from the path as though to keep it from being trod on. It is made "+
	"of white stone, similar to the path, but at the center of the stone "+
	"is "+ desc + gods +".\n");
}


public int
exit_string(void)
{
    switch(random(4))
    {
    case 0:
	write("You wander along the path, through redolent bushes until "+
	    "you reach the next arbor.\n");
	break;
    case 1:
	write("You stroll beneath pretty trees along the flagstone path "+
	    "to the next opening.\n");
	break;
    case 2:
	write("You follow the flower-lined path as it twists through the "+
	    "garden until you reach the next clearing.\n");
	break;
    case 3:
	write("You follow the meandering white path over well-kept grass "+
	    "and past fruit trees and flowers until the next section of "+
	    "garden opens before you.\n");
	break;
    }

    return 0;
}

static void
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

static void
rem_flower(string str)
{
    if (!flowers[str])
	return;

    m_delkey(flowers, str);
    remove_item(m_flowers[str][0]);
}

public string *
query_flowers(void)
{
    return m_indexes(flowers);
}

static void
add_fruit(string str)
{
// fruit descriptions should be added to the rooms.
    fruits += ({ str });
}

static void
rem_fruit(string str)
{
    if (!IN_ARRAY(str, fruits))
	return;

    fruits -= ({ str });
}

public string *
query_fruits(void)
{
    return fruits;
}

/*
 * Common items amongst all garden rooms.
 */
static void
garden_items(void)
{
    add_item(({"cavern","ceiling"}),"The cavern ceiling lies high "+
      "above, veined with long lines of glowing rock that "+
      "provide light for the area.\n");

    add_item(({"source",}),"@@see_source");

    add_item(({"aqueduct","railing","barricade","barrier","channel","water",}),
      "At the edge of the terrace, a thick wall of black stone prevents "+
      "accidental falls. Cut into the top of the wall, a narrow, deep "+
      "channel is filled with steadily running water, circling the entire "+
      "garden before disappearing into hidden channels in the stone walls. "+
      "This aqueduct provides a practical source of water and makes a "+
      "lovely addition to the garden atmosphere.\n");

    add_item(({"ground","bed","soil","floor","carpet"}), "The ground of the "+
      "terrace is made of flat, rich soil and covered with well tended grass. "+
      "As you notice some trees growing not far away you realize the soil "+
      "must be exceptionally deep, contained by the black stone walls of the "+
      "terrace below. This is likely the reason the ceilings of outmost rooms "+
      "of the Ziggurat, though extremely high, are substantially shorter than "+
      "the soaring ceilings of the inner courtyards.\n");

    add_item(({"terrace","terraces","step","garden","gardens","ziggurat",}),
      "The Ziggurat is pyramid shaped with stepped sides. Each terrace "+
      "step is covered by flowered gardens with plants and trees both "+
      "native and foreign to Avenir. The plants create a peaceful and "+
      "popular retreat for the Sybarun nobles as well as a source of "+
      "food.\n");

    add_item(({"plants","plant",}),
      "This terrace garden supports a wide variety of plants including "+
      "flowers, bushes, trees and grasses.\n");

    add_item(({"grass","grasses"}),
      "Thick, soft grass covers the floor of the terrace. It is well "+
      "tended, kept lush and thick but not allowed to get too long or "+
      "grow beyond its borders.\n");

    add_item(({"planter","planters"}),
      "Stone planters made of the same glossy black stone as the Ziggurat "+
      "hold a variety of plants throughout the garden: some stretching "+
      "toward the Source, others spilling over the sides.\n");

    add_item(({"flower bed","flower beds","beds"}),
      "Flowers grow in carefully cultivated beds of rich, black soil.\n");

    add_item(({"wall","walls"}),
      "The walls of the Ziggurat are made of heavy black stone polished "+
      "until they are glossy and slick. An octagon about the size of a "+
      "head has been deeply etched into the stone here.\n");

    add_item(({"octagon","octagons"}),
      "An octagon about the size of your head with eight equal sides "+
      "has been deliberately cut into the Ziggurat wall at about eyelevel.\n");

    add_item(({"flagstone path","flagstones","path","paths","stones","rocks"}),
      "A path made of white flagstones "+
      one_of_list(({"meanders","winds","snakes"})) +" its way through the "+
      "garden, through bushes, trees and flowers from one arbor to the "+
      "next. Most of the flagstones are flat and naturally shaped except "+
      "for one odd one to the side. From here the path travels to the "+
      COMPOSITE_WORDS(query_obvious_exits()) +".\n");
}

static void
garden_flowers(void)
{
    string desc;
    int sz = m_sizeof(flowers);

    remove_item(({"flower","flowers"}));

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

/*
 * Common tells amongst all garden rooms.
 */
static void
garden_tells(void)
{
    clear_tells();
    set_tell_time(900);
    add_tell(({
	"Water trickles melodiously through the black stone aqueduct.",
      }));

#if 0
    switch(season)
    {
    case 2..4:  /* Spring */
	break;
    case 5..7:  /* Summer */
	break;
    case 8..10: /* Fall */
	break;
    default:    /* Winter */
	break;
    }
#endif
}

public void
change_season(int week)
{
    season = week;
    garden_tells();
}

public int
avenir_event(int year, int week, int day, int hour)
{
    if (week != season)
	change_season(week);

    return 1;
}

public string
see_source(string str)
{
    write("You tilt your head back to gaze at the Source.\n\n"+
      "The ceiling of the cavern is covered by throbbing veins of "+
      "a glowing mineral that pulse and shimmer in mesmerizing "+
      "patterns as though possessed of some life of their own.\n");

    switch(random(4))
    {
    case 0:
	say(QCTNAME(TP) +" tilts "+ HIS(TP) +" face up toward the Source "+
	  "letting the soft glow light "+ HIS(TP) +" skin.\n");
	break;
    case 1:
	say(QCTNAME(TP) +" tilts "+ HIS(TP) +" head back, letting the "+
	  "Sourcelight wash the shadows from "+ HIS(TP) +" face.\n");
	break;
    case 2:
	say(QCTNAME(TP) +" tilts "+ HIS(TP) +" head back, letting the "+
	  "Sourcelight wash the shadows from "+ HIS(TP) +" face.\n");
	break;
    case 3:
	say(QCTNAME(TP) +" tilts "+ HIS(TP) +" face toward the Source, "+
	  "allowing the light to brighten its contours.\n");
	break;
    }

    return "";
}

public void
hook_smelled(string str)
{
    int idx, sz;

    if (!(sz = m_sizeof(flowers)))
	return;

    /* No arg, smell the various flowers. */
    if (!strlen(str))
    {
	if (sz > 1)
	{
	    write("You make out the various scents of nearby flowers "+
	      "such as "+ COMPOSITE_WORDS(m_indexes(flowers)) +".\n");
	}
	else
	{
	    write("The scent of "+ m_indexes(flowers)[0] +
		" pervades the area.\n");
	}
    }

    /* Try to smell a specific flower. */
    foreach(string key, mixed data : flowers)
    {
	if (IN_ARRAY(str, m_flowers[key][0]))
	{
	    write(m_flowers[key][2] + "\n");
	    break;
	}
    }
}

public int
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
        if (IS_SYBARITE(TP))
	    god = "Sachluph";
	else
	    god = "some unseen guardian of this garden";

	write("You get a strange chill as you reach toward the plant. "+
	    "You sense that "+ god +" believes you have taken enough "+
	    "from the plants here.\n");

	return 1;
    }

    if (!parse_command(str, ({ }), "[a] / [the] %s", str))
	return NF(CAP(verb) + " what?\n");

    if (IN_ARRAY(str, fruits))
    {
	if (str != "blackberry" && str != "raspberry")
	{
	    switch(season)
	    {
		case 5..7:  /* Summer */
		    return NF("They are not ripe yet.\n");
		case 8..10: /* Fall */
		    break;
		default:    /* Winter */
		    return NF("You find no "+ str +".\n");
	    }
	}

	switch(str)
	{
	    case "peach": 	file = (ZIG_FOOD + "peach");      break;
	    case "pear": 	file = (ZIG_FOOD + "pear");       break;
	    case "cherry": 	file = (ZIG_FOOD + "cherry");     break;
	    case "blackberry":	file = (ZIG_FOOD + "blackberry"); break;
	    case "raspberry": 	file = (ZIG_FOOD + "raspberry");  break;
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

public int
climb_tree(string str)
{
    string god;
    string verb = query_verb();
    string *what;
    int size;

    if (!stringp(str))
	return NF(CAP(verb) + " what?\n");

    what = explode(str, " ");
    size = sizeof(what);

    if (what[(size - 1)] == "tree" | what[(size - 1)] == "trees")
    {
	if (!TO->query_trees())
	    	return NF("There are no trees nearby.\n");

        if (IS_SYBARITE(TP))
        {
	    god = "Sachluph";
	}
	else
	{
	    god = "the unseen Keeper of this garden";
	}
	write("As you approach the "+ what[size - 1] +", an "+
	    "unsettling feeling falls over you, making you stop. You get the "+
	    "sense that "+ god +" would be wroth to have you "+
	    "climb the trees.\n");
	return 1;
    }
    else
    return 0;
}

public int
drink_water(string str)
{
    if(!strlen(str))
    {
	notify_fail("Drink from what?\n");
	return 0;
    }	
	
    if(parse_command(str, ({ }), "[the] [water] [from] [the] %s", str)
    && str == "aqueduct")
    {
        if (TP->drink_soft(TP->drink_max() / 16 , 0))
        {
            write("You cup your hands in the flowing water of the "+
	 	"aqueduct and lift them to your lips, taking a mouthful " +
		"of the cold, refreshing water.\n");
            say(QCTNAME(TP)+" dips "+ HIS(TP) +" cupped hands into the "+
              "flowing water of the aqueduct and raises them to "+
		HIS(TP) +" lips, drinking deeply.\n");
        }
        else
	{
            write("You aren't thirsty at the moment.\n");
	}

        return 1;
    }
}

public void
init(void)
{
    ::init();

    add_action(pluck_flower, "pick");
    add_action(pluck_flower, "pluck");
    add_action(climb_tree, "climb");
    add_action(drink_water, "drink");
}

/* For players that are trapped by Maree. */
public int
unq_move(string str)
{
    if (TP->query_trapped_object())
    {
	write("You try to move, but the thick thorn-covered "+
	  "vines are wrapped tightly about your legs, holding you in "+
	  "place.\n");
	say(QCTNAME(TP) +" struggles to move "+
	  "but "+ HIS(TP) +" legs are firmly bound by thick, thorn-"+
	  "covered vines.\n");
	return 1;
    }

    return ::unq_move(str);
}
