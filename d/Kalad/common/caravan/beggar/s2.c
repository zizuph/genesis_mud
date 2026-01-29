#include "../default.h"
inherit CVAN_ROOM;

void
create_cvan_room()
{
    set_short("Beggar's alley");
    set_long("You are travelling along Beggar's Alley, so named because "+
      "of the many beggars said to dawdle here. To the west is Caravan Lot, "+
      "a large muddy field filled to capacity with the wagons and pack "+
      "animals of travelling merchants and their retinues. Many cramped "+
      "buildings line the street to the east, while Beggar's Alley heads "+
      "north and south to an intersection. Animal refuse litters the ground "+
      "here.\n");

    add_item(({ "caravan lot", "lot", "field" }),
      "You see many crowded stalls where merchants along with their laborers "+
      "reside. The field is so clogged with wagons, animals and people that "+
      "little detail can be made out of individual objects, it all just seems "+
      "to blur together.\n");

    add_item(({ "wagons", "wagon" }),
      "You can see many different types of wagons, a lot of them are brightly "+
      "colored and decorated with the individual symbols of merchants and "+
      "any merchant companies they happen to belong to.\n");

    add_item(({ "animals", "pack animals" }),
      "A wide variety of animals can be seen, the most prominent are horses, "+
      "oxen and camels.\n");

    add_item(({ "buildings", "building" }),
      "Most of the buildings are built of wood and look in need of serious "+
      "repair work. Some look as if they might collapse at any moment.\n");

    add_item(({ "animal refuse", "refuse" }),
      "Looking closer at the animal feces you deduce that it originates from "+
      "the many pack animals in the Caravan Lot, to the west.\n");

    add_exit(CVAN + "beggar/s1", "north");
    add_exit(CVAN + "beggar_serv", "south");
}
