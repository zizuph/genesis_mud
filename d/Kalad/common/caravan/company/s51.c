#include "../default.h"
inherit CVAN_ROOM;

void
create_cvan_room()
{
    set_hear_bell(1);

    add_prop(ROOM_I_INSIDE, 1);

    set_short("Refuse room");
    set_long("This room is filled with stinking refuse of all kinds and "+
      "smells. Unlike nearly every other place in this building, this place "+
      "is filthy, so dirty in fact that you unconsciously hold your breath "+
      "to avoid smelling the stench.\n");

    add_item(({ "refuse" }), "A myriad amount of trash can be seen, "+
      "everything from decaying food scraps to rusted and broken weapons "+
      "and armour.\n");

    clone_object(CVAN + "door/tcdoor5")->move(TO);
}

void
init()
{
    ::init();
    write("A rush of foul air greets you.\n");
}
