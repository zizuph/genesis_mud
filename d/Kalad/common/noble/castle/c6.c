// Sarr,
// Fysix, recoded, March 1998

#include "default.h"

inherit NOBLE_ROOM;

void
create_noble_room()
{
    set_short("In the reception room of the High-Lord's castle");
    INSIDE;
    set_long("You have entered the reception room of the High-Lord. "+
      "This room is very large, and stretches all the way to the "+
      "west. The walls are decorated with paintings and murals, "+
      "and the room is lighted with candles and torches. The "+
      "ground is covered by a red fur carpet, and it feels soft to the "+
      "touch. There are many leather couches here, all placed "+
      "to make a circle. In the center of the circle, there is a "+
      "large oak chair. The sounds of dining come from the room "+
      "to your south.\n");
    add_item("chair","This is a large oak chair with big, soft "+
      "down-filled cushions on it.\n");
    add_item("murals","They are pictures of dragons, goblins, "+
      "griffins and other mystical creatures.\n");
    add_item("candles","Scented candles burn dimly on the table.\n");
    add_item("torches","Torches on the wall add to the light in the "+
      "room.\n");
    add_item("couches","They are old leather couches with many "+
      "soft cusions.\n");
    add_item("paintings","Many paintings of old battle scenes. "+
      "They depict warriors fighting various demi-humans.\n");
    add_item("tapestries","They are finely woven with many "+
      "ancient symbols on them.\n");
    add_item("carpet","The carpet is soft and warm.\n");

    add_exit(NOBLE + "castle/c2", "north", 0, 0);
    add_exit(NOBLE + "castle/c5", "west", 0, 0);
    add_exit(NOBLE + "castle/c11", "south", 0, 0);
}


