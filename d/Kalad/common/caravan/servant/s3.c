#include "../default.h"
inherit CVAN_ROOM;

void reset_room();
void create_bugs();

int wood_disturbed;

void
create_cvan_room()
{
    set_short("Servant street");
    set_long("The street you are walking along is extremely narrow, the "+
      "width of the road seems to vary every so often but is mostly "+
      "around fifteen feet. The buildings here are so crowded that a few "+
      "appear to stretch over the road itself, blocking out your view of "+
      "the sky. To the east, an intersection can be seen. You notice "+
      "piles of refuse lying about.\n");

    add_item(({ "sky" }), "The clear skies above are visible only in part, "+
      "since the crowded buildings of this street block out most of the "+
      "view.\n");

    add_item( ({ "street" }),
      "This street is partially paved in cobblestone, it appears that is "+
      "was once entirely paved but over the years the stones have either "+
      "been removed or dislodged and never replaced. The steet is mostly "+
      "hard-packed dirt now.\n");

    add_item( ({ "buildings", "building" }),
      "Almost all the buildings are built out of wood, taking a closer "+
      "look you see that many of the buildings are in poor condition, as "+
      "they clearly bear the mark of weather and termites.\n");

    add_item("wood", "@@exa_wood");

    add_item( ({ "intersection" }),
      "You can't get a clear view of it from where you're standing.\n");

    add_item( ({ "refuse", "piles" }),
      "Examining them further you can see and smell that these are the "+
      "droppings left behind by the animals common in the Caravan district, "+
      "as well as droppings by the unfortunate residents of this street.\n");

    add_exit(CVAN + "servant/s2", "west");
    add_exit(CVAN + "caravan_serv", "east");

    reset_room();
}

void
reset_room()
{
    wood_disturbed = 0;
}

void
create_bugs()
{
    int i;
    wood_disturbed = 1;
    for(i = 0; i < 8; i++)
    {
	clone_object(NPC + "termite")
	->move(TO);
	tell_room(TO, "A huge termite emerges from the hole!\n");
    }
}

string
exa_wood()
{
    if(wood_disturbed)
	return("The wood has been so chewed up by termites that large gaping "+
	  "holes have been opened on the sides of the buildings.\n");
    set_alarm(6.0, 0.0, create_bugs);
    return("As you bend closer to further examine the wood of the "+
      "buildings, you inadvertedly break a small hole in a wall. Without "+
      "warning the hole expands as wood falls out and...\n");
}
