#include "/d/Shire/sys/defs.h"
#include "/d/Shire/sys/terrain.h"

inherit AREA_ROOM;

void create_forest() {}

nomask void
create_area_room()
{
    set_areatype(AREATYPE_FOREST);
    set_land("Rhudaur");
    set_areadesc("trail");
    set_area("just off");
    set_areaname("the East Road");
    set_treetype("beech");
    set_forest_density(25);

    create_forest();
}

string
describe_time(string time)
{
    string desc;

    switch (time)
    {
    case "night":
	desc = "An errie darkness fills the forest now at night.  ";
	switch (CLOCK->query_moon())
	{
	case "full":
	    desc += "The light of the full moon penetrates the forest and "+
	    " barely illuminates the surrounding area.  ";
	    break;
	case "dark":
	    desc += "No starlight is visable through the dark canopy of "+
	    "tress above.  ";
	    break;
	default:
	    desc += "The moon and the stars are barely visable through the "+
	    "canopy of tress above.  ";
	    break;
	}
	break;
    case "afternoon":
	desc = "The light of day filters into the forest as the Sun slowly "+
	"makes her descent into the west.  ";
	break;
    case "morning":
	desc = "The light of day filters into the forest as the Sun "+
	"slowly rises from the east.  ";
	break;
    case "evening":
    case "early morning":
	desc = "Sunlight barely filters into the forest; creating "+
	"long, forbidding shadows.  ";
	break;
    case "noon":
	"The light of the Sun pours down on you as She reaches "+
	"her full height overtop the forest.  ";
    }

    return desc;
}

void add_herbs() {}
