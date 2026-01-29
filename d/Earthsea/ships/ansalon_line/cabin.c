inherit "/d/Genesis/ship/cabin";

#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "defs.h"

#define RAT ANSALON_LINE + "ship_rat"
object rat;

void
room_set()
{
    if (!objectp(rat))
    {
	rat = clone_object(RAT);
	rat->move(TO);
	rat->command("hide");
	rat->command("emote sneaks in.");
    }
}

void
create_cabin()
{
    set_short("Captain's cabin");

    set_long(break_string("Mildew covers old furniture and crates "+
	"and there is a distinct smell of mildew and rot. You see a cot "+
	"and a warped wooden table. The bilge is full of slimy sea "+
	"water from the leaks in the hull. A leftover meal of moldy "+
	"bread and a crust of cheese are on the table.\n", 70));

    add_item((({"water", "bilge", "slimy water"})),
      "Along the keel of the boat the bilge is full of slimy "+
      "green sea water.\n");
    add_item((({"bread", "moldy bread", "crust of cheese" })),
      "You wonder if this is the captain's dinner. Yuk!\n");
    add_item("cot", "A low dirty cot is bolted to the inside "+
      "of the hull.\n");
    add_item((({"table", "wooden table"})),
      "The wood of the table is warped and slightly rotted from "+
      "the damp.\n");

    set_cabin_sound("Slimy water sloshes in the bilge with "+
      "the rolling of the ship.\n");

    add_exit(ANSALON_LINE + "deck", "up");
    room_set();

}
