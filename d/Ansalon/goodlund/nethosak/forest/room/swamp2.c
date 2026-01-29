#include "/d/Ansalon/goodlund/nethosak/forest/local.h"
#include "/d/Ansalon/common/defs.h"
#include <stdproperties.h>
#include <macros.h>

inherit MITHAS_OUT;

void
create_mithas_room()
{

    set_short("Next to a dark cave");
    set_long("@@long_descr");

    add_exit(MROOM + "swamp1","northeast","@@cross_swamp");

    add_item(({"rocks", "formation", "rock formation"}),
        "Looking closely at the "+
        "large rock formation, you notice a dark cave entrance "+
        "partially hidden by some large bushes.\n");

    add_item(({"cave", "dark cave"}),
        "You are unable to see what's inside the "+
        "cave, however the foul strench of sulpher that you "+
        "have beem smelling since you entered this place is "+
        "extremely strong here.\n");

    add_cmd_item(({"stream","water","from stream","water from stream"}),
      "drink","@@drink_water");

    add_cmd_item(({"cave","hole","the cave","the hole","dark cave",
                   "dark hole"}),"enter","@@enter_cave");
}

string
drink_water()
{
    write("You can't drink swamp water!\n");
    return "";
}

int
cross_swamp()
{
    if((TP->query_encumberance_weight() >= 26) || (TP->query_stat(0) <= 78))
    {
        write("As you try to move forward, both your feet gets "+
              "stuck in the black-brown mud, and you find yourself "+
              "unable to move in that direction.\n");
        return 1;
    }
    write("You strain you muscles as you pull your feet from "+
          "and black-brown mud and move forward.\n");
    return 0;
}

int
enter_cave()
{
    if (TP->query_stat(5) >= 75)
    {
        write("Taking a deep breath and bravely move forward "+
              "into the dark cave.\n");
        TP->move_living("into the dark cave",MROOM + "dragons_lair",0,0);
        return 1;
    }

    write("Oh no! You don't dare to enter the dark cave.\n");
    return 1;
}

string
long_descr()
{
    return tod_descr()+ "" +season_descr()+
    "You are standing in the middle of a large swamp on "+
    "the isle of Mithas. The trees that once dominated this "+
    "area are lying scattered all over the place, covered "+
    "with fungi and moss. To the south of you a large "+
    "rock formation rises above the tree lines, the "+
    "creatures that live here, seem to refuse to venture "+
    "near this place...\n";
}
