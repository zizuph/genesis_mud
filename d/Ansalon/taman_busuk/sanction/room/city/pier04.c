#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/sanction/local.h"
#include <stdproperties.h>
#include <macros.h>

inherit SANCTION_OUT;

object ship;
void
add_stuff()
{
    seteuid(getuid(TO));
    if(!ship)
    {
	ship = clone_object(SANCTION + "ship/balifor/ship");
	ship->start_ship();
    }
}

void
reset_sanction_room()
{
    add_stuff();
}

void
create_sanction_room()
{
    set_short("West end of pier in the harbour of Sanction");
    set_extra_long("This is the west end of a pier stretching from " +
      "the waterfront of Sanction and westwards, out here, into " +
      "the center of the harbour basin. Numerous small ships lie " +
      "randomly scattered along the piers. Vast clouds of steam " +
      "obscure the view to the shores along the harbour. A sign " +
      "hangs from a signpost here.");

    add_harbour_items();

    add_prop(ROOM_I_NO_CLEANUP, 1);

    add_item("signpost","The signpost holds a sign.\n");
    add_item("sign","It is made of a few planks of wood with " +
      "letters painted on it.\n");
    add_cmd_item(({"wooden sign","sign"}),"read","@@read_sign");

    add_exit(SCITY + "pier03", "east", 0, 0);

    reset_room();
}


string
read_sign()
{
    say(QCTNAME(TP) + " reads the sign hanging from the signpost.\n");
    write("It reads: The courier ship to Port Balifor docks here. Passage " +
      "can be arranged for 28 copper coins.\n");
    return "";
}

