#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/goodlund/bloodsea/local.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>

inherit COURRAIN_OUT;

void
reset_courrain_room()
{
    return;
}

create_courrain_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");


    add_item(({"sea", "ocean","courrain ocean"}), 
       "You cannot see the Courrain Ocean from here.\n");
    add_item(({"coastline","estwilde","foothills","rugged foothills",
       "barren coastline","hills", "riverbanks","solamnia"}),
       "To your southeast is the barren coastline of Estwilde, a land of rugged " +
       "foothills, while to your northwest you can just make out the riverbanks of " +
       "Solamnia.\n");
    add_item(({"river","vingaard river"}),
       "You find yourself upon the longest " +
       "river in Krynn, the Vingaard River. You notice a cave has formed in the steep " +
       "cliffs on the Estwilde side of the bank.\n");
    add_item(({"steep banks","banks","bank","high cliffs","cliffs","cliffside"}),
       "The banks of the eastern side of the Vingaard River are quite steep here, to the " +
       "point where high cliffs have formed. You notice a deep cave in the cliffside that " +
       "you could swim out to.\n");
    add_item(({"deep cave","cave"}),
       "Carved into the steep banks here is a deep cave that a strong swimmer could swim " +
       "out to.\n");

    add_cmd_item(({"out to cave","to cave","cave"}),"swim",
       "@@enter_cave");

    add_row_exit(CROOM + "1c", "west", 0, 1);
    add_row_exit(CROOM + "2d", "north", 0, 1);
    add_row_exit(CROOM + "2e", "northeast", 0, 1);


    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);

    reset_courrain_room();

}

int
no_go()
{
    write("You decided not to sail in that direction, as the waters are " +
      "uncharted. Rumour has it that those who do sail too far into the " +
      "Courrain Ocean are never seen of again!\n");
    return 1;
}

int
no_go_saifhum()
{
    write("A great reef surrounds the northern part of the island of Saifhum. " +
          "You will have to find another way to sail to it.\n");
    return 1;
}

void
set_sink_path(string sp)
{
    sink_path = "/d/Ansalon/balifor/flotsam/room/bottom_of_bay";
}

string
enter_cave()
{
   if(TP->query_skill(SS_SWIM) < 55)
       return "You try and swim out to the cave, but the current here " +
              "is too strong. You'd need to be a more powerful swimmer " +
              "to have a chance of making it to the cave.\n";

   write("With powerful strokes, you swim against the current of the river " +
         "to the cave...\n");
   say("With powerful strokes, " +QTNAME(TP)+ " swims against the current of " +
       "the river to the cave on the steep bank of the river.\n");
   TP->move_living("M", "/d/Ansalon/goodlund/bloodsea/cave/cave", 1, 0);

   return "";
}

string
short_descr()
{
    return "the Vingaard River, near a cave within steep banks of Estwilde";
}
 
string
long_descr()
{
    return "You find yourself upon the Vingaard River, " +
       "close to the steep banks that mark the barren lands " +
       "of Estwilde. High cliffs have formed here, and you notice " +
       "a deep cave has formed at the edge of the river. To your west " +
       "you can just make out the green riverbank of Solamnia.\n";

}