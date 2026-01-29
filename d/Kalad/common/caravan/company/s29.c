#include "../default.h"
inherit CVAN_ROOM;

void
create_cvan_room()
{
    set_hear_bell(1);

    add_prop(ROOM_I_INSIDE, 1);

    add_prop(ROOM_I_LIGHT, 0);

    set_short("Storage");
    set_long("This must be the storage room.\n"+
      "You can barely see inside this large room. Gazing all "+
      "around you, you see many large wooden crates. The floor here is also "+
      "made of marble, though dustier than other areas of the building.\n");

    add_item(({ "large wooden crates", "wooden crates", "crates" }), "Many "+
      "different kinds of containers can be seen, all being stacked in huge "+
      "piles all over the room. Each crate has the symbol of a gold coin "+
      "with lines radiating from it, the symbol of the Trading Company.\n");

    add_item(({ "floor" }),
      "The ground is covered with pale-white marble tiles. A thin layer of "+
      "dust blankets the floor, also there are numerous scratch marks "+
      "marring the marble tiles.\n");

    add_item(({ "scratch marks", "marks" }), "They were probably made when "+
      "crates were moved in and out of this room.\n");

    add_item(({ "marble tiles", "tiles" }), "You peer more intently at the "+
      "tiles...One in particular looks loose, as you pry it loose you see "+
      "a small opening leading down into the dark.\n");

    set_noshow_obvious(1);

    add_exit(CVAN + "sewers/arcompany", "down", "@@block", -1, 0);

    clone_object(CVAN + "door/stdoor1")->move(TO);
}

int
block()
{
    write("Something dark and heavy seems to block your way down.\n");
    say(QCTNAME(TP) + " tries to go down but fails.\n");
    return 1;
}
