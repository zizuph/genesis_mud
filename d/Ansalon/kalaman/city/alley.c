#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>

inherit CITY_OUT;

void
reset_kalaman_room()
{
    return;
}

create_kalaman_room()
{
    set_long("@@long_descr");
    set_short("A dark and gloomy alley");

    add_item("walls","The walls of these two buildings " +
      "rise up two-stories high. You notice no windows " +
      "open out onto this alley.\n");
    add_item(({"buildings","building"}),
      "The gap between these two buildings makes " +
      "the alley you stand in.\n");
    add_item("shadows","Deep shadows are cast by the " +
      "walls of the buildings here.\n");
    add_item(({"rubbish","piles","large piles","large piles of rubbish"}),
      "Large piles of rubbish seem to have accumulated over " +
      "time here in this alley. Under one such pile you notice " +
      "a rather large grate.\n");
    add_item(({"grate","large grate"}),
      "This grate, used to stop rubbish from entering the sewers, " +
      "looks quite old. You notice a few of its bars are missing, " +
      "and you could quite possible squeeze through it.\n");

    add_exit(CITY + "r31","west",0);
    DARK;

    add_cmd_item(({"through grate","through bars"}),
      "squeeze","@@enter_sewers");


    reset_kalaman_room();

    add_prop(OBJ_S_WIZINFO, "This is the entrance to the sewers of the " +
      "city. This is the main entrance to the prison dungeon if you are " +
      "trying to do the Love or Hate quest, no matter what episode you " +
      "plan on doing, this is the entrance and exit. 20110704:Lunatari\n");
}

string
long_descr()
{
    return "You stand in a rather small alleyway between " +
    "two houses. It is extremely dark here, as it falls within " +
    "the shadows of the buildings two walls facing you. This area seems also to be " +
    "rather neglected, as rubbish has built up over time into " +
    "rather large piles. The only exit is to your west.\n";
}

string
enter_sewers()
{
    if (!TP->query_wiz_level())
    {
    write("You feel that you should have blessing of the immortals " +
      "before you enter this sewer.\n");
    return "";
    }

    write("You squeeze your way through piles of rubbish, " +
      "down through the grate and into the sewer below Kalaman.\n");
    say(QCTNAME(TP) + " burrows " +HIS(TP)+ " way through " +
      "a pile of rubbish and disappears!\n");
    TP->move_living("M",SROOM + "first/s1",1,0);
    return "";
}
