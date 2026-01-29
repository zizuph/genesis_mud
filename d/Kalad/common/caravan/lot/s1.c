/* Made the room clone manure at room reset - Cherek Nov 6 2019
 *
 * Cotillion - 2020-08-31
 * - Fixed cloning of massive amounts of manure 
 */

#include "../default.h"
inherit CVAN_ROOM;

#define STEP	("@@step:/d/Kalad/common/caravan/step")
#define HORSE	(NPC + "clhorse")
#define OX	(NPC + "clox")
#define CAMEL	(NPC + "clcamel")
#define HAY	(OBJ + "clhay")
#define MANURE	(OBJ + "manure")

void
create_cvan_room()
{
    add_prop(ROOM_I_INSIDE, 1);

    set_short("Animal Tent of Caravan Lot");
    set_long("You enter an enormous tent, clearly the largest tent you "+
      "have ever laid eyes upon. It is quite obvious from the large piles "+
      "of animal refuse that this is where many of the merchants' pack "+
      "animals are kept, that and the overwhelming smell. Many bales of hay "+
      "are stacked on the outer edges of the tent. A large and open tent flap "+
      "lies to the south.\n");

    add_item(({ "animal refuse", "refuse" }),
      "The droppings of countless animals, there is so much of the stuff that "+
      "it is heaped in large, stinking piles.\n");

    add_item(({ "bales", "hay" }),
      "They probably serve as food for the pack animals brought by the "+
      "merchants.\n");

    set_noshow_obvious(1);

    add_exit(CVAN + "lot/s5", "south", STEP);


    add_object(HAY, 1, &->set_heap_size(9));
    add_object(MANURE, 9);
    add_npc(HORSE, 3);
    add_npc(OX, 2);
    add_npc(CAMEL, 2);
    add_npc(NPC + "clsh");
}


