#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/steppe/local.h"

inherit STEPPE_OUT;

void
reset_steppe_room()
{
    return;
}

create_steppe_room()
{
    set_short("A road passing through a barren steppe");
    set_long("@@long_descr");

    add_item(({"brown scraggly grass","scraggly grass","grass"}),
      "Brown scraggly grass covers most of the surrounding " +
      "steppe all the way up to the road.\n");
    add_item(({"bush","stumpy tree","tree","bird","bird of prey"}),
      "The occasional stumpy tree or bush dot the plains, where " +
      "the often lone bird of prey rests or flushes out its " +
      "dinner.\n");
    add_item(({"plains","plain","steppe","barren steppe"}),
      "Around the road you stand on is a barren plain, mostly " +
      "devoid of life.\n");
    add_item(({"road","dirt road"}),
      "Beneath your feet is a dirt road, the only thing that " +
      "reminds you that you are not the first to travel through " +
      "these lifeless plains.\n");

    add_exit(SROOM + "road9","northeast",0);
    add_exit(SROOM + "road11","southwest",0);

    reset_steppe_room();
}

string
long_descr()
{
    return "You stand upon a road passing through a barren " +
    "steppe. " + tod_descr1() +
    "Brown scraggly grass covers most of the surrounding land. " +
    "The occasional bush or stumpy tree can be seen scattered " +
    "sparsely around the plains.\n";
}
