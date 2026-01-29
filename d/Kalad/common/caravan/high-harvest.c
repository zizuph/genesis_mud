#include "default.h"
inherit CVAN_ROOM;

object aylmer;

void reset_room();

void
create_cvan_room()
{
    set_short("Intersection of High and Harvest");
    set_long("You've reached the intersection of High Street and Harvest "+
      "Way. From here, High Street heads north and south towards the "+
      "Central District. Harvest Way, also known as Farmer's Way, travels "+
      "west-east. Following Harvest Way westward eventually leads to the "+
      "fertile farmlands just outside of Kabal. Lining the entire "+
      "intersection are many buildings, save towards the northwest where a "+
      "large stand of trees, a park in the adjacent Upper Class district, "+
      "are. Just visible far to the southwest is a massive citadel and to "+
      "the southeast, a large circular structure, the arena. Animal refuse "+
      "litters the ground here.\n");

    add_item(({ "intersection", "high street", "harvest way", "farmer's way" }),
      "Both High Street and Harvest Way are paved in slate-grey cobblestones "+
      "that appear worn and slightly cracked, though in good condition for "+
      "such heavily-travelled roadways. The only major difference between "+
      "the two streets is High Street is much more tidy, there being "+
      "considerably less filth lying on its surface. In contrast Harvest "+
      "Way is a bit filthy, due to the droppings left behind by animals "+
      "brought into Kabal by farmers.\n");

    add_item(({ "buildings" }),
      "The majority of the structures are of wood, though a few are made of "+
      "stone. While the buildings along Harvest Way are small and crowded "+
      "together, the ones lining High Street to the north are more spaced "+
      "and of better construction.\n");

    add_item(({ "trees", "park" }),
      "Gazing into the shadowy depths of the small forest, it strikes you "+
      "as being the perfect hideout for thieves, murderers and other "+
      "brigands.\n");

    add_item(({ "citadel" }),
      "Little can be made out from here, save for the immense size of the "+
      "building.\n");

    add_item(({ "arena" }),
      "Little can be made out from here, save for the immense size of the "+
      "building.\n");

    add_item(({ "animal refuse", "refuse" }),
      "It appears to be the animal droppings of many types of animals. It "+
      "is scattered across the intersection.\n");

    add_exit(NOBLE + "farmer/s1", "west", 0);
    add_exit(CVAN + "high/s4", "north");
    add_exit(CVAN + "harvest/s1", "east");
    add_exit(CENTRAL + "high-gladiator", "south");
    add_exit(CENTRAL + "promenade/s1", "southwest");

    clone_object(CVAN + "anth_stat")->move(TO);

    reset_room();
}

void
reset_room()
{
    if(!objectp(aylmer))
    {
	seteuid(getuid(this_object()));
	aylmer = clone_object(NPC + "cmilitia");
	aylmer->move(this_object());
    }
}

int
block()
{
    write("The way is blocked by a barricade.\n");
    return 1;
}
