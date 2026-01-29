#pragma strict_types

#include <composite.h>
#include <language.h>
#include "defs.h"
#include "/d/Khalakhor/sys/defs.h"
#include "/d/Khalakhor/sys/paths.h"
#include "/d/Khalakhor/sys/terrains.h"

inherit "/d/Khalakhor/std/room";
inherit HERBSEARCH;

mapping proxim;
string extra;
string *path;
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
	files = get_dir(MON + "*.c");
	ob = clone_object(MON + files[random(sizeof(files))]);
	ob->set_restrain_path(ROOM);
	ob->move_living("M", TO);
	tell_room(TO, capitalize(LANG_ADDART(ob->short())) 
	+ " arrives.\n");
}
    
public string
reverse_direction(string str)
{
	if (str == "north")
	return "south";
	if (str == "south")
	return "north";
	if (str == "east")
	return "west";
	if (str == "west")
	return "east";
	if (str == "northwest")
	return "southeast";
	if (str == "northeast")
	return "southwest";
	if (str == "southwest")
	return "northeast";
	if (str == "southeast")
	return "northwest";
	return str;
}
 
public void
setup_forest_herbs()
{
	herbs = HERBMASTER->query_herbs(({TERRAIN_MIXEDWOOD,}));
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
		if (path)
		set_short("on a path crossing through a dense forest");
		else
		set_short("a dense forest");
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
		if (path)
		set_short("on a path crossing through a dense forest");
		else
		set_short("in a dense forest");
		return;
	}
	if (path)
	temp = "on a path crossing through a dense forest ";
	else
	temp = "in a dense forest ";
	dir = reverse_direction(proxim[close][1]);
	temp += (proxim[close][0] ? "on the " + dir +
	" edge" : "just " + dir);
	
	if (close == "forest")
	temp += " of a dense forest";
	else if (close == "shore")
	temp += " of the shore";
	else if (close == "tower")
	temp += " of the sanctuary tower";
	else if (close == "meadow")
	temp += " of a lush meadow";
	else if (close == "stream")
	temp += " of an ethereal stream";
	else if (close == "harbour")
	temp += " of the quiet harbour";
	
	set_short(temp);
	setup_forest_herbs();
	add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_FOREST);
}

public void
setup_long()
{
	string temp,
	landmark;
	
	int i,
        dist;
        if (path)
        temp = "   This is a path running " +
            COMPOSITE_WORDS(path) + " across ";
            
            else
            temp = "   This is ";
            
            temp += "a quiet dense forest area that is filled with sweet "+
            "grass and honeysuckle. Through the thick trees overhead "+
            "are billowing clouds that drift smoothly through a sultry "+
            "blue sky. ";
            
            if (!proxim)
            set_long(temp + "\n");
            
            for (i = 0; i < m_sizeof(proxim); i++)
            {
		    landmark = m_indexes(proxim)[i];
		    dist = proxim[landmark][0];
		    if (landmark == "forest")
		    temp += "A dense forest stands ";
		    else if (landmark == "tower")
		    temp += "The sanctuary tower rises majestically ";
		    else if (landmark == "meadow")
		    temp += "A quiet, lush meadow stretches ";
		    else if (landmark == "shore")
		    temp += "A rocky shore spreads out ";
		    else if (landmark == "stream")
		    temp += "An ethereal stream cuts across the dense forest ";
		    else if (landmark == "harbour")
		    temp += "The quiet harbour cuts into the meadow ";
		    
		    temp += ({"to the immediate",
		    "nearby to the",
		    "not far away to the",
		    "far to the",
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
        "The ground here is comprised mainly of small hills " +
        "covered in dense sweet grass and patches of sweet honeysuckle.\n");
        add_item(({"honeysuckle"}),
        "The honeysuckle is quite fragrant and seems " +
        "to thrive here despite the weeds and overgrowth of vegetation.\n");
        add_item(({"sky", "clouds"}),
        "Billowing white clouds drift through a sulty blue sky.\n");
        add_item(({"mountains", "highlands"}),
        "In the far north, you can dimly distinguish the " +
        "faded, purple-blue tinge of the mountains of the " +
        "Highland region.\n");
        add_item(({"tree", "trees"}),
        "There are many different shaped trees here. Quite "+
        "fragrant and tall.\n");
        if (!proxim)
        return;
        
        if (proxim["tower"])
        add_item(({"tower", "eil-galaith", "eilgalaith"}),
        "The sanctuary tower is large and mysterious. "+
        "It is like a beacon that majestically rises " +
        "to the " + proxim["tower"][1] + ".\n");
        
        if (proxim["t_hills"])
        {
		add_item(({"hills"}),
		"Several tall hills rise to the " + proxim["t_hills"][1] +
		", covered in thistles and brambles too dense to ever " +
		"hope to penetrate.\n");
		add_item(({"thistles"}),
		"The thistles are dense bushes full of prickly "+
		"pods, not something you want to get stuck under "+
		"your clothing.\n");
		add_item(({"brambles"}),
		"The brambles are dense bushes covered in little "+
		"foliage, but with a plethora of dense thorns as "+
		"long as your thumb.\n");
	}
	if (proxim["stream"])
	add_item(({"stream"}),
	"The stream, called the Silinia cuts across the "+
	"forest to the "+
	proxim["stream"][1] + ", running more or less "+
	"in a southwesterly direction.\n");
	
	if (proxim["forest"])
	add_item(({"forest", "trees"}),
	"To the " + proxim["forest"][1] + " stands a dense " +
	"forest which spreads out east and west across the " +
	"meadow.\n");
	
	if (proxim["shore"])
	add_item(({"shore", "beach"}),
	"To the " + proxim["shore"][1] + ", a rocky " +
	"shore spreads along the meadow.\n");
	
	if (proxim["harbour"])
	add_item(({"harbour"}),
	"The harbour spreads out " +
	"to the " + proxim["harbour"][1] + ".\n");
}

public void
create_forest()
{
	setup_short();
	setup_long();
	setup_add_items();
	set_tell_time(45);
        add_tell(({
		"A beautiful bird's song echos through the forest.\n",
		"A small beam of sunlight shimmers through the "+
		"leaves far above you.\n",
		"A small leaf falls slowly from above to rest on "+
		"the ground a short distance away.\n",
		"Colorful butterflies flitter past in frantic yet "+
		"playful motion.\n",
		"A gentle breeze caresses your skin.\n",
		"A soft chirping sound from high above you reaches "+
		"your ears.\n",
		}));
	set_alarm(0.0, 0.0, reset_room);
	register_room();
}
