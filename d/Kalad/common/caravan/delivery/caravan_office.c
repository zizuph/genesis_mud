#include "../default.h"
#include "local.h"

inherit DELIVERY_OFFICE;
inherit CVAN_ROOM;

void
create_cvan_room()
{
    set_hear_bell(1);

    add_prop(ROOM_I_INSIDE, 1);

    set_short("The Caravan District delivery office");
    set_long("You find yourself in the Caravan District delivery office. "+
      "The darkened interior coupled with the warm air here provides a "+
      "comfortable atmosphere. Here you can 'ask for delivery tour', or "+
      "'deliver packet' or 'return packet'.\n");

    add_item(({ "office", "interior" }), "Its rather dimly lit, but still "+
      "quite comfortable.\n");
    set_office_name("The Caravan District Office in Kabal");
    set_office_packets_per_reset(5);

    add_exit(CVAN + "beggar_wayfar", "south", 0);
}

void
init()
{
    init_office();
    ::init();
}
