#include "default.h"
inherit CVAN_ROOM;

void
create_cvan_room()
{
    set_short("Intersection of Beggar and Servant");
    set_long("You find yourself in a cramped, dirty-looking intersection "+
      "between Beggar's Alley and Servant Street. Beggar's Alley heads off "+
      "to the north while Servant Street continues west and east to another "+
      "intersection. Also visible to the east are the massive city walls of "+
      "Kabal. To the northwest, Caravan Lot, a large muddy field filled to "+
      "capacity with the wagons, pack animals and retinues of travelling "+
      "merchants is plainly seen. Crowded buildings line the entire "+
      "intersection. Animal refuse litters the ground here.\n");

    add_item(({ "massive city walls", "city walls", "walls" }),
      "You are too far away to pick out any details other than the wall "+
      "looks to be quite high.\n");

    add_item(({ "caravan lot", "lot", "large muddy field", "muddy field", "field" }),
      "Crowded stalls filled with the wagons of merchant's along with their "+
      "pack animals and laborers can be seen.\n");

    add_item(({ "wagons" }),
      "A myriad of brightly-colored merchant wagons with their individual "+
      "merchant symbols fills the Caravan lot.\n");

    add_item(({ "pack animals", "animals" }),
      "Prominent among the animals visible are horses, oxen and camels, "+
      "although more exotic animals can be seen.\n");

    add_item(({ "buildings" }),
      "The majority of the structures are built out of wood and show the "+
      "harsh effects of time and weather, that along with the poverty of "+
      "its residents leaves the buildings in poor shape.\n");

    add_item(({ "animal refuse", "refuse" }),
      "It litters this entire intersection, considering the proximity of "+
      "the Caravan Lot it is highly likely that most of this filth comes "+
      "from the animals there.\n");

    add_exit(CVAN + "servant/s5", "west");
    add_exit(CVAN + "beggar/s2", "north");
    add_exit(CVAN + "wall_serv", "east");
}
