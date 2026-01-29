/* File         : /d/Khalakhor/se_speir/plains/room/tfor_g_12.c
 * Creator      : Zima@Genesis
 * Date         : ??-??-??   
 * Purpose      : UAINE_PINE found here - needed for incense quest
 * Related Files: 
 * Comments     :
 * Modifications: Modified by Darragh 01-01-23
 */

#pragma strict_types

#include <macros.h>
#include "plains.h"

inherit "/d/Khalakhor/se_speir/plains/room/tforbase";

int num_ambers = 0;

void reset_room() { num_ambers = 3; }

void create_khalakhor_room()
{
   create_tforest();

   set_long("You are in a light forest, populated mostly with "
          + "tall straight pines which tower above you, blocking "
          + "the sunlight. The floor of the forest is covered "
          + "with dead needles and branches, which crunch softly "
          + "beneath your feet. It looks as if it is possible to "
          + "travel in nearly all irections from here. A particularly "
          + "strong pine scent permeates the air.\n");
   add_item(({"trees"}),
            "They are tall and straight, mostly pine, their "
          + "branches stretching out in all directions high "
          + "above. A unique looking pine with black bark and "
          + "needles grows here amongst the common pines.\n");
   add_item(({"pines","pine"}),
              "The pines are tall and straight with dark brown "
            + "bark and long green needles. A few pine cones "
            + "hang from a few of the branches high above. One "
            + "unique looking pine with black bark and needles "
            + "grows here amongst the common pines.\n");
   add_item(({"unique pine","black pine","uaine pine","uaine",
              "unique looking pine"}),
              "This unique pine has black bark and long black "
            + "needles, in contrast to the brown bark and green "
            + "needles of its surrounding cousins. Sap on this "
            + "strange tree seeps plentifully from its bark, some "
            + "hardened solid, other still a syrup, and the rest " 
            + "in between.\n");
   add_item(({"amber","sap"}),
              "The sap of the black pine ouzes plentifully from "
            + "its dark bark, some hardened to an amber, some syrupy, "
            + "and some in between. You think you could pull some of "
            + "the hardened sap amber from the pine.\n");
   add_item("needles",
            "The pine needles are long and green, at least those "
          + "still living on the trees. Those carpeting the floor "
          + "have turned brown, while those of the black-barked "
          + "pine are strangely black but living.\n");

   add_exit(PLAINS + "tfor_g_11","west",0,1,1);
   add_exit(PLAINS + "tfor_f_11","northwest",0,1,1);
   add_exit(PLAINS + "tfor_f_12","north",0,1,1);
   add_exit(PLAINS + "tfor_f_13","northeast",0,1,1);
   add_exit(PLAINS + "tfor_g_13","east",0,1,1);
   add_exit(PLAINS + "tfor_h_13","southeast",0,1,1);
   add_exit(PLAINS + "tfor_h_12","south",0,1,1);
   add_exit(PLAINS + "tfor_h_11","southwest",0,1,1);

   reset_room();
}
int pull(string cmd) 
   {
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
