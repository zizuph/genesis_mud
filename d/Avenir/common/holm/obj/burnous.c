// Red burnous      /d/Avenir/common/holm/obj/burnous.c
// creator(s):      Lilith  01/25/97
// purpose:         To be worn by Holm 'adept' npc
// last update:
// note:
// bug(s):
// to-do:

inherit "/d/Avenir/inherit/cloth_arm";
#include <wa_types.h>
#include "../holm.h"

void
create_armour()
{
    set_name("burnous");
    add_name(({"robe", "mantle", "cape"}));
    set_short("blood-red burnous");
    add_adj(({"blood", "red", "blood-red"}));
    set_long ("This is a hooded mantle which envelops the wearer "+
        "from head to mid-calf. It is made of very finely woven "+
        "wool, and the borders are ornately embroidered with silver "+
        "and gold thread.\n");
    add_item("hood", "The hood of this burnous is automatically "+
        "worn when the burnous is worn. Its function is one of "+
        "protection from the elements, rather than concealment.\n");
    add_item(({"borders", "border", "embroidery", "silver thread",
        "gold thread", "pattern", "lines"}), 
        "This is some of the finest embroidery you have ever seen. "+
        "It has been sewn along the hemlines of the burnous in gold "+
        "and silver thread. There is no discernable pattern, but "+
        "rather a complex non-repeating flow of lines.\n");
    set_at(A_ROBE | A_HEAD);
    set_ac(3 + random (3));
}

