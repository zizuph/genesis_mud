#include "../default.h"
inherit CVAN_ROOM;

void
create_cvan_room()
{
    set_short("Servant street");
    set_long("You are travelling along Servant Street, a narrow road with "+
      "many crowded buildings lining the southern side. Sprawling to the "+
      "north is Caravan Lot, a large muddy field filled to capacity with "+
      "the wagons, pack animals and retinues of travelling merchants. To "+
      "the east an intersection can be seen. Animal refuse litters the "+
      "ground here.\n");

    add_item(({ "street", "road" }),
      "All you can see is hard packed dirt, as well as a few partially "+
      "covered cobblestones. It seems this roadway was once paved with "+
      "cobbles but was never repaired, allowing it to deteriorate into "+
      "little more than a large dirt pathway.\n");

    add_item(({ "buildings" }),
      "They are so tightly packed together that a few appear to stretch out "+
      "over the road itself, in a vain effort to add more room inside. Most "+
      "of the wooden structures show the harsh effects of time and weather, "+
      "that along with the poverty of its inhabitants leaves them in need "+
      "of serious repairwork.\n");

    add_item(({ "caravan lot", "lot", "large muddy field", "muddy field", "field" }),
      "It seems quite large, since it appears capable of holding dozens of "+
      "wagons and animals, along with the merchants that own them.\n");

    add_item(({ "wagons" }),
      "A myriad of colorful wagons with various merchant-house symbols "+
      "occupy the entire Caravan Lot.\n");

    add_item(({ "pack animals", "animals" }),
      "A whole host of animals are visible, with horses, oxen and camels "+
      "most common.\n");

    add_item(({ "animal refuse", "refuse" }),
      "The droppings apparently come from the many animals kept in the "+
      "Caravan Lot.\n");

    add_exit(CVAN + "servant/s4", "west");
    add_exit(CVAN + "beggar_serv", "east");

    add_npc(NPC + "rabdog", 2);
}


