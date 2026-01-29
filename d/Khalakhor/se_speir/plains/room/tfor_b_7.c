// temp forest room - Zima
// AROMATIC CEDAR found here - needed for incense quest
#include "plains.h"
#include <macros.h>
inherit "/d/Khalakhor/se_speir/plains/room/tforbase";
inherit SR_DIR+"lib/branchcmd";

int num_barks  = 0;

void reset_room() { num_barks = 3;  set_numbranches(2); }

void create_khalakhor_room()
{
   create_tforest();
   set_long("You are in a light forest, populated mostly with tall straight "+
            "pines which tower above you, blocking the sunlight. The floor "+
            "of the forest is covered with dead needles and branches, which "+
            "crunch softly beneath your feet. A particularly strong and "+
            "unique scent permeates the air here.\n");

   add_item("trees",
      "They are tall and straight, mostly pine, their branches blocking "+
      "most of the sunlight. A unique looking tree with scales for leaves "+
      "and a strong scent grows here amongst the pines.\n");

   add_item(({"unique tree","cedar","unique looking tree","aromatic tree",
              "aromatic cedar","cedar tree"}),
      "This tree is very different from the pines of the forest, though "+
      "it too is an evergreen. Its slim branches are covered with "+
      "scales instead of needles, branching out in small branchlets like "+
      "blood veins, identifying it as a cedar tree. It has a very strong "+
      "aromatic scent. You notice that some of the bark has been peeled "+
      "from its trunk.\n");

   add_item("bark",
      "The bark of the cedar has been peeled off in strips, apparently "+
      "with a knife. You think that if too much were removed, the tree "+
      "wouldn't live long.\n");

   add_exit(PLAINS+"tfor_b_4","northwest");
   set_branchnum(7);
   reset_room();
}

int peel(string cmd) {
   object TO=this_object();
   object TP=this_player();
   object knife;
   string kshort;

   notify_fail("Peel what from which tree with what?\n");
   if (!stringp(cmd)) return 0;
   if (!(parse_command(cmd,all_inventory(TP),
      "[strip] [of] 'bark' 'from' [aromatic] 'cedar' [tree] 'with' %o",
      knife)))
      return 0;

   if (!((knife->id("knife"))||(knife->id("dagger")))) {
      write("You must use a knife to peel the bark from the tree.\n");
      return 1;
   }

   kshort = (knife->query_short());

   if (num_barks <= 0)
      write("Peeling more bark from this tree would endanger it.\n");
   else
      {
      TP->catch_msg("You peel a strip of bark from the aromatic cedar "+
                    "with the "+kshort+".\n");

      tell_room(TO,QCTNAME(TP)+" peels a strip of bark from the aromatic "+
                   "cedar with a "+kshort+".\n",TP);
      (clone_object("/d/Khalakhor/common/herbs/arom_cedar"))->move(TP);
      num_barks--;
      }
   return 1;
}

public void
init()
{
   ::init();
   add_action(&peel(), "peel");
   add_action(&break_branch(),"break");
}
