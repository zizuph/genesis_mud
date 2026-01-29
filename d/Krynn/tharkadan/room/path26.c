#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>
#include "/d/Krynn/common/clock/clock.h"

inherit THARK_OUT;
inherit HERBSEARCHNEW

string *herbs = HERB_MASTER->query_herbs(({"mountains","hills",}));

void
reset_tharkadan_room()
{
    set_searched(random(2));
}

create_tharkadan_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");

    add_item(({"snow","snow-covered","snow-covered ground",
        "white","snow-covered land","winters snow","winter's snow"}),
        "@@add_item_snow");
    add_item(({"path","trail","pass","valley pass"}),
        "You stand on a well-disguised trail running down to a wooded " +
        "valley to southeast.\n");
    add_item(({"valley","wooded valley"}),"To your southeast is a " +
        "secluded wooded valley. The trail here leads down into it.\n");

    add_exit(ROOM + "path23","west",0);
    add_exit(ROOM + "hvale1","southeast","@@enter_vale");

    seteuid(getuid(TO));
    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
        ONE_OF(herbs), ONE_OF(herbs) }), ({ "pass","ground" }), 6);

    reset_tharkadan_room();
}

string
short_descr()
{
    return "on a well-disguised trail running down to a wooded valley " +
           "in the Tharkadan Mountains";
}

string
long_descr()
{
    return long_mountain_desc()+ "The trail here runs down into a " +
        "secluded wooded valley, and looks like it has been " +
        "well-disguised so that only a skilled or persistent tracker " +
        "would find it.\n";
}

int
enter_vale()
{
   if(TP->query_guild_name_occ() == "Priests of Takhisis" ||
      TP->query_guild_name_occ() == "Dragonarmy" ||
      TP->query_guild_name_lay() == "Templars of Takhisis" ||
      TP->query_alignment() < -500)
   {
      write("As you begin down the path into the wooded valley, you " +
          "feel yourself become befuddled and disoriented, ending up " +
          "at the edge of a canyon.\n");
      say(QCTNAME(TP)+ " starts down the trail to the southeast, but " +
          "seems to become befuddled and disoriented and wanders away " +
          "to the west.\n");
      TP->move_living("M", ROOM + "path24", 0, 0);
      return 1;
   }

   write("A feeling of peace settles over you as you descend into the " +
       "wooded valley...\n");
   return 0;
}
