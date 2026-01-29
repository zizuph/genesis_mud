#include "/d/Ansalon/common/defs.h";
#include "/d/Ansalon/taman_busuk/neraka/local.h";

inherit NOUTROOM;

void
create_neraka_room()
{
    set_long("@@long_descr@@");
    set_extra_long("You are now in between to tall walls within the "+
    "inner city of Neraka. The road here is stone, and it bends to "+
    "the northeast. The outergate is off to the west, on the "+
    "southwall, and you can see the dark and forboding gatehouse, "+
    "although it is guarded on the outside, not the inside here. "+
    "To the center, you see the temple of Takhisis. A black stone "+
    "house stands off to the northwest against the north wall.");
    add_item("gatehouse","The gatehouse is tall and consists of two "+
    "towers, in between which sits an iron gate.\n");
    add_item("road","The road is made of cold stone and cobblestone.\n");
    add_item("temple","The twisted and perverse black temple of "+
    "Takhisis.\n");
    add_exit(NINNER+"i17.c","northeast",0,0);
    add_exit(NINNER+"i15.c","west",0,0);
    add_exit(NINNER+"eq_shop1.c","northwest",0,0);
}

