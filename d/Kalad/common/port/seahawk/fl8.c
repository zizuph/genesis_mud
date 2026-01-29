#include "../default.h"
inherit PORT_ROOM;

object ob1;

void
create_port_room()
{
    set_short("An Office");
    set_long("You find yourself in a surprisingly roomy office. The walls "+
      "are decorated with paintings and have been painted a lighty grey "+
      "in color. Covering the floor is a large red carpet and the room "+
      "is lit by a pair of lanterns hanging from the ceiling. At the far "+
      "end is a large, stylish oak desk and a handsome leather-covered "+
      "chair.\n");
    add_item(({"walls","wall"}),"The ordinarily plain wooden walls of "+
      "the ship have been painted a greyish color here, giving one the "+
      "impression of an overcast day.\n");
    add_item(({"paintings","painting"}),"The artist who created these "+
      "pictures clearly put a great deal of time and effort into them. Rendered "+
      "in a wonderful oil canvas, an image of huge war galleons with "+
      "great flags raised is shown.\n");
    add_item(({"huge war galleons","war galleons","galleons","galleon"}),
      "The ships look similar to the Seahawk itself, though the ones in "+
      "the painting somehow look more threatening.\n");
    add_item(({"great flags","flags","flag"}),"A symbol of a dark sun "+
      "upon a field the color of blood has been painted.\n");
    add_item(({"large red carpet","large carpet","red carpet","carpet"}),
      "It covers all of the floor and is a rich red in color. Symbols of "+
      "dark suns have been sewn into the carpet.\n");
    add_item(({"pair of lanterns","lanterns","lantern"}),"Iron-hooded "+
      "lantern that provide a wan yellow light.\n");
    add_item(({"ceiling"}),"It looks sturdy, despite the age of the "+
      "Seahawk.\n");
    add_item(({"large stylish oak desk","large desk","stylish desk","desk"}),
      "A finely crafted wooden desk, surprisingly enough, it shows no signs "+
      "of decay or damage, leading you to believe that it is a fairly "+
      "new addition to this place.\n");
    add_item(({"handsome leather-covered chair","handsome chair","leather-covered chair","chair"}),
      "A wooden chair that has been covered with supple leather. It looks "+
      "quite comfortable.\n");

    add_prop(ROOM_I_INSIDE,1);

    add_exit(PORT + "seahawk/fl9", "south");

    reset_room();
}

reset_room()
{
    if(!ob1)
    {
	ob1 = clone_object(PORT + "npc/first_mate");
	ob1 -> move_living("xxx",TO);
    }
}

