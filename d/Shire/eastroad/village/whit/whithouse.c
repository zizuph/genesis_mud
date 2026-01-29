inherit "/d/Shire/std/room";
#include "/d/Shire/common/defs.h"

void create_house() {}

void
create_shire_room()
{
    add_item(({"bed","beds"}),"The beds in this room are small and " +
      "comfortable, as you would expect from the bed of a hobbit. " +
      "The mattresses are thick, and there are warm quilts to "+
      "keep the cold out at night.\n");

    add_item(({"mattress","mattresses"}),"The mattresses are thick and " +
      "comfortable, stuffed with soft hay.\n");

    add_item(({"quilt","quilts"}),"The quilts look wonderfully soft " +
      "and warm, full of goose down.\n");

    add_item(({"chair","chairs"}),"These chairs are tiny, although " +
      "they are sturdy, as the chair of a hobbit should be.\n");

    add_item(({"cupboard","cupboards"}),"The cupboards in this room " +
      "hold various items of clothing, and other household goods.  " +
      "All of the items look fairly old and worn, and wouldn't be "+
      "worth taking.\n");

    add_item("window","The window in this room is small and round, " +
      "and painted a nice bright white colour.  The window overlooks the " +
      "lane, and you can see the houses across the other side of the lane.\n");

    add_item("table","The table has various stains on it from years " +
      "of use, and is set for a meal with bowls, mugs and spoons.\n");

    add_prop(ROOM_I_INSIDE,1);
    create_house();
}

