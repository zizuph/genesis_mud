// temp forest room - Zima
// UAINE_PINE found here - needed for incense quest
#include "plains.h"
#include <macros.h>
inherit "/d/Khalakhor/se_speir/plains/room/tforbase";

int num_ambers = 0;

void reset_room() { num_ambers = 3; }

void create_khalakhor_room()
{
   create_tforest();
   set_long("You are in a light forest, populated mostly with tall straight "+
            "pines which tower above you, blocking the sunlight. The floor "+
            "of the forest is covered with dead needles and branches, which "+
            "crunch softly beneath your feet. A particularly strong pine "+
            "scent permeates the air here.\n");

   add_item("trees",
      "They are tall and straight, mostly pine, their branches blocking "+
      "most of the sunlight. A unique looking pine with black bark and "+
      "needles grows here amongst the common pines.\n");
   add_item(({"pines","pine"}),
      "The pines are tall and straight with dark brown bark and long "+
      "green needles. A few pine cones hang from a few of the branches "+
      "high above. One unique looking pine with black bark and needles "+
      "grows here amongst the common pines.\n");
   add_item(({"unique pine","black pine","uaine pine","uaine",
              "unique looking pine"}),
      "This unique pine has black bark and long black needles, in "+
      "contrast to the brown bark and green needles of its surrounding "+
      "cousins. Sap on this strange tree seeps plentifully from its "+
      "bark, some hardened solid, other still a syrup, and the rest "+
      "in between.\n");
   add_item(({"amber","sap"}),
      "The sap of the black pine ouzes plentifully from its dark bark, "+
      "some hardened to an amber, some syrupy, and some in between. You "+
      "think you could pull some of the hardened sap amber from the pine.\n");
   add_item("needles",
      "The pine needles are long and green, at least those still living "+
      "on the trees. Those carpeting the floor have turned brown, while "+
      "those of the black-barked pine are strangely black but living.\n");

   add_exit(PLAINS+"tfor_a_6","southeast");
   reset_room();
}

int pull(string cmd) {
   object TO=this_object();
   object TP=this_player();

   notify_fail("Pull what from what?\n");
   if (!stringp(cmd)) return 0;
   if (!(parse_command(cmd,({(environment())}),
      "'sap' / 'amber' 'from' [black] [dark] [uaine] [unique] 'pine' / 'tree'"
      )))
      return 0;
   if (num_ambers <= 0)
      {
      write("The remaining sap amber is stuck too hard for you to pull.\n");
      write("Perhaps you should wait awhile until some is ready.\n");
      }
   else
      {
      write("You pull a piece of sticky sap amber from the dark pine.\n");
      tell_room(TO,QCTNAME(TP)+" pulls a piece of sticky sap amber from the "+
                   "dark pine.\n",TP);
      (clone_object("/d/Khalakhor/common/herbs/uaine_pine"))->move(TP);
      num_ambers--;
      }
   return 1;
}

public void
init()
{
   ::init();
   add_action(&pull(), "pull");
}
