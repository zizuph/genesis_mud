#include "../default.h"
inherit CVAN_ROOM;

void
create_cvan_room()
{
    set_short("Caravan Street");
    set_long("You are travelling along Caravan Street, to your south"+
      "west you can see the intersection of this road with that of "+
      "Servant street. Farther to the northeast lies Wayfarer boulevard. "+
      "Gazing to your east you can see the crowded caravan lot, where many "+
      "wagons of travelling merchants along with their animals reside. "+
      "Directly west of you, there is a small, wooden sign swinging in "+
      "front of a large building. There is a particularly disgusting pile "+
      "of refuse on the side of the street where the caravan lot is.\n");

    add_item( ({ "lot", "caravan lot" }),
      "Many wagons and a variety of pack animals can be seen, however "+
      "you must move closer to the wagons and animals to get a better "+
      "description.\n");

    add_item( ({ "street" }),
      "This street is paved with slate-grey cobblestones, a few of "+
      "which seem loose.\n");

    add_item( ({ "pile", "refuse" }),
      "You examine the pile more closely, wrinkling your nose in "+
      "disgust. Only then do you notice the bleach-white color of bone "+
      "protruding through the rest of the filth.\n");

    add_item( ({ "bone" }),
      "This is the decayed remains of a human being!\n");

    add_exit(CVAN + "caravan/s2", "northeast");
    add_exit(CVAN + "caravan_serv", "southwest");
    add_exit(CVAN + "shop/gshop", "west");
}

string
sign()
{
    return "\n"+
    "                   ********************\n"+
    "                   *      WELCOME     *\n"+
    "                   *     TRAVELLERS   *\n"+
    "                   *        TO        *\n"+
    "                   *      ANTHIOS'    *\n"+
    "                   *      GENERAL     *\n"+
    "                   *       STORE      *\n"+
    "                   ********************\n";
}

void
init()
{
    ::init();
    AA(read_sign,read);
}
