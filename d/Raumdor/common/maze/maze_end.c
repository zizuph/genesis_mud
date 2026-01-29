#include "defs.h"
inherit MAZE_ROOM;

void
create_room()
{
    ::create_room();
    set_short("Within a misty room");
    set_long(
      "You have entered a cramped room. The walls leer above you covered in " +
      "strange spectral mist.\n");
    add_item("walls",
      "The walls are of cold black stone. On the far west one you notice a " +
      "red skull.\n");
    add_item(({"red skull", "skull"}),
      "This skull is embedded in the wall in a small niche.\n");
    add_item(
      "niche", "The niche holds the skull and it looks hollow behind.\n");
    add_cmd_item(({"red skull", "skull"}), "push", "@@skull@@");
    add_cmd_item(({"red skull", "skull"}), "press", "@@skull@@");
    add_exit(MAZE_DIR + "maze03", "northeast");
}

string
skull()
{
    TELL_CAN_SEE(TP, QCTNAME(TP) + " presses something in the wall.\n");

    if (TP->test_bit("Raumdor", 3, 3))
        return "Nothing happens.\n";

    TP->add_exp_quest(2500);
    TP->set_bit(3, 3);
    KLOG("QUEST/maze_quest",
      TP->query_real_name() +
        " completed quest, bit 3,3 awarded 2500 xp by " + file_name(TO) +
        ".\n");
    /*
    tell_room(TO,"From out of nowhere, a "+wep->short()+" floats "+
    "out of the mist and settles on the ground.\n");
    object wep;
    wep = clone_object(RAUM(wep/staff_of_ages));
    wep->move(TO);
    */
    return "You feel more experienced!\n";
}
