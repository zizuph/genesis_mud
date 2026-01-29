#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/sanction/local.h"

#include <macros.h>

inherit SANCTION_OUT;

object ship;
void
add_stuff()
{
    seteuid(getuid(TO));
    if(!ship)
    {
        ship = clone_object(SANCTION + "ship/newports/ship");
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
    set_short("Southern piers in the harbour of Sanction");
    set_extra_long("These solidly built piers have been shattered " +
        "by the violent tremors from the erupting volcanoes. The " +
        "piers stretch further west and east from here. There is " +
        "a signpost here, bearing a sign.");

    add_harbour_items();

    add_prop(ROOM_I_NO_CLEANUP, 1);

    add_item("signpost","The signpost holds a sign.\n");
    add_item("sign","It is made of a few planks of wood with " +
        "letters painted on it.\n");
    add_cmd_item(({"wooden sign","sign"}),"read","@@read_sign");

    add_exit(SCITY + "pier06", "east");
    add_exit(SCITY + "pier08", "west");

    reset_room();
}


string
read_sign()
{
    say(QCTNAME(TP) + " reads the sign hanging from the signpost.\n");
    write("It reads: Troop ferry to Newports. Form a queue behind the " +
    "sign. Price of passage 18 coppers.\n");
    return "";
}
