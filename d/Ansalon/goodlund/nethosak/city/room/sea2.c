#include "/d/Ansalon/goodlund/nethosak/city/local.h"
#include "/d/Ansalon/common/defs.h"

inherit MITHAS_OUT;

void
reset_mithas_room()
{
   return;
}

create_mithas_room()
{
   set_short("Swimming in the Bloodsea");
   set_long("You are swimming in the red waters of the Bloodsea "+
            "close to the isle of Mithas. To the east beyond the "+
            "huge rocks that form the beach you see a Imperial city "+
            "of Nethosak, home of the mighty minotaurs. To the southeast "+
            "a small forest stretches itself to the east and south. To the "+
            "west you see the wooden pier. The sea continues in every "+
            "direction.\n");
   add_prop(ROOM_I_TYPE, ROOM_IN_WATER);

   add_item(({"rocks","rock","cave","hole","shadow"}),"As you look "+
        "closer at the rocks you note some dark shadow beneath the water. "+
        "It might be some sort of hole or cave that leads further down...\n");

   add_item(({"water", "sea"}), "The water within the Blood Sea has "+
         "a strange and reddish color. Rumor has it that the color "+
         "is the result of the blood of many victims who lost their "+
         "lives during Krynn's most terrible hour, though it "+
         "could be the clay stirred up from the sea bottom by the "+
         "maelstrom.\n");

   add_cmd_item(({"cave","into cave","in cave",
                  "hole","into hole","in hole"}),
      ({"enter","dive","jump","step","go"}), "@@enter_cave");

   add_invis_exit(MROOM + "nowhere","north","@@no_go");
   add_invis_exit(MROOM + "nowhere","south","@@no_go");
   add_invis_exit(MROOM + "nowhere","east","@@no_go");
   add_invis_exit(MROOM + "nowhere","northeast","@@no_go");
   add_invis_exit(MROOM + "nowhere","northwest","@@no_go");
   add_invis_exit(MROOM + "nowhere","southeast","@@no_go");
   add_invis_exit(MROOM + "nowhere","southwest","@@no_go");
   add_invis_exit(MROOM + "sea1","west",0,4);
   add_invis_exit(MROOM + "nowhere","down","@@no_go");    

   reset_mithas_room();
}

int
no_go()
{
   write("The current is far to strong in that direction, "+
         "it will be too dangerous too swim there.\n");
   return 1;
}

string
enter_cave()
{
    write("You take a deep breath and dive down into the " +
      "turbulent waters of the Bloodsea.\n"+
      "A few seconds after you emerge in an underground cave.\n");

    this_player()->move_living("into the underground cave",
      "/d/Ansalon/guild/pirates/room/underground_cave.c", 1, 0);
    return "";
}

