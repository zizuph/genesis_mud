#include "../default.h"
inherit CVAN_ROOM;

void reset_room();
void create_thugs();
int shadows_disturbed;

void
create_cvan_room()
{
    set_short("Street of chains");
    set_long("This gloomy road you are travelling on is the Street of "+
      "Chains, so named because future slaves are brought and held in "+
      "the dark, crowded buildings lining this road. A large intersection "+
      "can be seen to the north. A wooden fence to your "+
      "west blocks off any view you might have had of a collection of "+
      "buildings there. However, you notice a small dirt path that heads "+
      "west along the fence, which turns west at this point. The rest of "+
      "the fence heads northward. Animal refuse litters the road.\n");

    add_item(({ "road", "street of chains" }),
      "This roadway seems to have been paved in cobblestones at one point "+
      "in time. However little evidence of that remains besides the "+
      "occasional fragment of a cobblestone visible beneath the dirt-covered "+
      "street.\n");

    add_item(({ "buildings" }),
      "Dark wooden structures that visibly sag in appearance, as if the "+
      "gloominess of their surroundings weighs upon them like a physical "+
      "weight. A mass of dark shadows is visible near one building to the "+
      "east.\n");

    add_item("shadows", "@@exa_shadows");

    add_item(({ "wooden fence", "fence" }),
      "A sturdy looking fence that surrounds a collection of buildings to "+
      "the northwest. There doesn't seem any easy way over it.\n");

    add_item(({ "collection" }),
      "All you can make out from here are a few, squat buildings and what "+
      "appears to be a raised platform near the center.\n");

    add_item(({ "small dirt path", "dirt path", "small path", "path" }),
      "A narrow dirt-covered pathway that follows the fence westward. "+
      "Judging from the amount of tracks on it, the path must be well-used.\n");

    add_item(({ "animal refuse", "refuse" }),
      "There are piles of animal dung all over the street. The smell is so "+
      "overwhelming that you cannot bring yourself to look at it closer.\n");

    add_exit(CVAN + "chains_serv", "north");
    add_exit(CVAN + "slave/s1", "west");
    add_exit(CVAN + "chains_harvest", "south");

    reset_room();
}

void
reset_room()
{
    shadows_disturbed = 0;
}

void
create_thugs()
{
    int i;

    shadows_disturbed = 1;
    for(i = 0; i < 5; i++)
    {
	clone_object(NPC + "bthug")->move(TO);
	tell_room(TO, "A thug leaps from the shadows!\n");
    }
}

string
exa_shadows()
{
    if(shadows_disturbed)
	return("The shadows are dark and foreboding, but you can find nothing "+
	  "within them.\n");
    set_alarm(6.0, 0.0, create_thugs);
    return("Moving closer to the shadows you begin to see movement. "+
      "Something jumps out at you!\n");
}
