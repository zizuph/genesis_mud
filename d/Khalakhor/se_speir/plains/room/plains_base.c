#pragma strict_types

/* December 8th, 2004
* Modified clone routine for animals/birds
* Since they were creating large amounts of NPCs
* With the long uptimes the new machine has given Genesis
* -Igneous
* - Modified description to allow laying hooks 
* - by Damaris@Genesis 02/2005 
*/

#include <composite.h>
#include <language.h>
#include "plains.h"
#include "/d/Khalakhor/sys/defs.h"
#include "/d/Khalakhor/sys/paths.h"
#include "/d/Khalakhor/sys/terrains.h"

inherit "/d/Khalakhor/std/room";
inherit HERBSEARCH;

mapping proxim;
string extra;
string *road;
int mountains_hidden;
string *herbs; // init in setup_plains_herbs()

public void
reset_room()
{
    string *files;
    object ob;

    set_searched(0);

    if (random(10))
	return;

    if (present("_Khalakhor_wildlife", this_object()))
	return;

    if (present("_Khalakhor_bird", this_object()))
	return;


    reset_euid();
    files = get_dir(NPC + "*.c");
    ob = clone_object(NPC + files[random(sizeof(files))]);
    ob->set_restrain_path(PLAINS);
    ob->move_living("M", TO);
    tell_room(TO, capitalize(LANG_ADDART(ob->short())) 
      + " arrives.\n");
}

public string
reverse_direction(string str)
{
    if (str == "north")
	return "south";
    if (str == "northeast")
	return "southwest";
    if (str == "east")
	return "west";
    if (str == "southeast")
	return "northwest";
    if (str == "south")
	return "north";
    if (str == "southwest")
	return "northeast";
    if (str == "west")
	return "east";
    if (str == "northwest")
	return "southeast";
    return str;
}

public void
setup_plains_herbs()
{
    herbs = HERBMASTER->query_herbs(({TERRAIN_PLAIN,}));
    set_up_herbs(({ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
	ONE_OF(herbs)}), ({"grass","here"}),2);
}

public void
setup_short()
{
    string close,
    temp,
    dir;
    int i;
    if (!proxim)
    {
	if (road)
	    set_short("on a road crossing a grassy plain");
	else
	    set_short("on a grassy plain");
	return;
    }

    for (i = 0; i < m_sizeof(proxim); i++)
    {
	temp = m_indexes(proxim)[i];
	if (!close || proxim[temp][0] < proxim[close][0])
	    close = temp;
    }

    if (proxim[close][0] > 1)
    {
	if (road)
	    set_short("on a road crossing a grassy plain");
	else
	    set_short("on a grassy plain");
	return;
    }

    if (road)
	temp = "on a road crossing a grassy plain ";
    else
	temp = "on a grassy plain ";
    dir = reverse_direction(proxim[close][1]);
    temp += (proxim[close][0] ? "on the " + dir +
      " edge" : "just " + dir);

    if (close == "forest")
	temp += " of a light forest";
    else if (close == "shore")
	temp += " of the shore";
    else if (close == "village")
	temp += " of Port Macdunn";
    else if (close == "t_hills")
	temp += " of some hills";
    else if (close == "river")
	temp += " of a wide river";
    else if (close == "harbour")
	temp += " of the large harbour, Cala Fasgadh";

    set_short(temp);
    setup_plains_herbs();
    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_PLAIN);
}

public void
setup_long()
{
    string temp,
    landmark;
    int i,
    dist;

    if (road)
	temp = "   You are on a road running " +
	COMPOSITE_WORDS(road) + " across ";
    else
	temp = "   You are on ";

    temp += "a wide, grassy plain covered in " +
    "rolling hills dotted with purple heather "+
    "that forms a blanket of comfort that blends so "+
    "well with the lush grass that in some areas "+
    "it is quite inviting for those who are inclined "+
    "to lay upon it. A cool breeze blows from the "+
    "west, carrying with it the scent of salt air. "+
    "Overhead, thick clouds drift effortlessly "+
    "through an otherwise blue sky. ";

    if (!mountains_hidden)
	temp += "Far, far away in the north, you can dimly make " +
	"out the purplish-blue shape of the mountains in " +
	"the Highlands. ";

    if (!proxim)
	set_long(temp + "\n");

    for (i = 0; i < m_sizeof(proxim); i++)
    {
	landmark = m_indexes(proxim)[i];
	dist = proxim[landmark][0];
	if (landmark == "forest")
	    temp += "A light forest stands ";
	else if (landmark == "t_hills")
	    temp += "Low, bramble-covered hills rise ";
	else if (landmark == "village")
	    temp += "The village of Port Macdunn rises ";
	else if (landmark == "shore")
	    temp += "A rocky shore spreads out ";
	else if (landmark == "river")
	    temp += "A wide river cuts across the plains ";
	else if (landmark == "harbour")
	    temp += "The large harbour Cala Fasgadh " +
	    "cuts into the plains ";

	temp += ({"to the immediate", "nearby to the", 
	  "not far away to the", "far to the",
	  "in the distant"})[dist] + " " +
	proxim[landmark][1] + ". ";
    }

    if (extra)
	temp += extra;

    set_long(temp + "\n");
}

public void
setup_add_items()
{
    add_item(({"ground", "grass", "dirt"}),
      "The ground here is comprised mainly of rolling hills " +
      "covered in thick green grass and patches of purple " +
      "heather.\n");
    add_item(({"heather"}),
      "The heather is a bright purple flower which seems " +
      "to thrive here.\n");
    add_item(({"sky", "clouds"}),
      "Several thick, white clouds drift through an otherwise " +
      "bright blue sky.\n");
    add_item(({"mountains", "highlands"}),
      "In the far north, you can dimly distinguish the " +
      "faded, purple-blue tinge of the mountains of the " +
      "Highland region.\n");
    add_item(({"blanket"}),
      "The heather forms a lovely blanket of comfort that blends "+
      "so well with the lush grass.\n");
    
    

    if (!proxim)
	return;

    if (proxim["village"])
	add_item(({"village", "port macdunn", "Port Macdunn"}),
	  "The small port village of Port Macdunn rises " +
	  "to the " + proxim["village"][1] + ".\n");

    if (proxim["t_hills"])
    {
	add_item(({"hills"}),
	  "Several tall hills rise to the " + proxim["t_hills"][1] +
	  ", covered in thistles and brambles too dense to ever " +
	  "hope to penetrate.\n");
	add_item(({"thistles"}),
	  "The thistles are thick bushes full of prickly " +
	  "pods, not something you want to get stuck under " +
	  "your clothing.\n");
	add_item(({"brambles"}),
	  "The brambles are thick bushes covered in little " +
	  "foliage, but with a plethora of thick thorns as " +
	  "long as your thumb.\n");
    }

    if (proxim["river"])
	add_item(({"river"}),
	  "The river, called the Sora cuts across the " +
	  "plains to the " +
	  proxim["river"][1] + ", running more or less " +
	  "in a southwesterly direction.\n");

    if (proxim["forest"])
	add_item(({"forest", "trees"}),
	  "To the " + proxim["forest"][1] + " stands a light " +
	  "forest which spreads out east and west across the " +
	  "plains.\n");

    if (proxim["shore"])
	add_item(({"shore", "beach"}),
	  "To the " + proxim["shore"][1] + ", a wide, rocky " +
	  "shore spreads along the plains where they meet " +
	  "the Lear Min.\n");

    if (proxim["harbour"])
	add_item(({"harbour"}),
	  "The harbour, known as Cala Fasgadh, spreads out " +
	  "to the " + proxim["harbour"][1] + ", a finger " +
	  "of the Lear Min that has reached inland.\n");
}

public void
create_plain()
{
    setup_short();
    setup_long();
    setup_add_items();
    set_alarm(0.0, 0.0, reset_room);
}
