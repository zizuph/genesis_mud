#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

#include "../../std/defs.h"
#include "/d/Earthsea/quest_handler/quest_handler.h"

inherit ISL_DIR+"/std/room";

#define WALKED_AROUND_TREE "_walked_around_tree"

void create_island_room()
{
 set_short("Dead end");
 set_long("You are at the dead end in the forest. You are surrounded "+
   "by massive trees, that cover all exits but west. There is some "+
   "kind of glade here , and one tree in the middle of it , that "+
   "stands aside of other trees.\n");

 add_exit(FROOMS+"/spath4","west");

 add_item(({"trees","forest"}),
   "The trees on the both sides make the path so "+
   "narrow that it is hardly seen. You have an "+
   "instant feeling of beeing watched.\n\n");

 add_item(({"ground","path","track"}),
   "The track is crossed by gnarled roots here and "+
   "there. False trails lead in every direction. "+
   "You can see animal tracks, some of them quite "+
   "fresh.\n\n");

 add_item("glade","Glade with green soft grass on it. In the middle "+
   "of the glade you see lonely tree. You wonder how could it stand "+
   "aside of others tree right in the middle of the glade.\n");

 add_item("tree","It looks really wierd. Maybe you should come closer "+
   "and walk around it to take a closer look.\n");

 add_item("branch","@@exa_branch");
}

string random_forest()
{
 write("Oh, no! You are lost now! You can wander here FOREVER!\n\n");
 return "forest"+random(20);
}

void init()
{
 ::init();
 add_action("walk","walk");
 add_action("pull","pull");
}

void leave_inv(object ob,object to)
{
 ob->remove_prop(WALKED_AROUND_TREE);
}

int walk(string str)
{
 NF("Walk around the tree maybe?\n");
 if(!str) return 0;
 if(str!="around tree" && str!="around the tree") return 0;

 write("You walk around the tree, studying it closely...\n");
 say(QCTNAME(TP)+" walks around the tree, studying it closely.\n");

 if(!TP->query_prop(HAS_TREE_HINT) &&
    !QH_QUERY_QUEST_COMPLETED(TP,"tricksters_entrance"))
  {
   write("Nothing... it looks like usual tree.\n");
   return 1;
  }

 write("Your eyes suddenly stop on little branch on the other side "+
   "of the tree, it doesn't look like natural part of the tree. It "+
   "looks more like a ... lever!\n");
 TP->add_prop(WALKED_AROUND_TREE,1);
 return 1;
}

string exa_branch()
{
 if(!TP->query_prop(WALKED_AROUND_TREE)) return "You find no branch.\n";
 return "It doesn't look natural on this tree. You guess it's kind of "+
   "lever.\n";
}

int pull(string str)
{
 if(!TP->query_prop(WALKED_AROUND_TREE)) return 0;

 NF("Pull what?\n");
 if(!str || str!="branch") return 0;

 write("You pull the lever.\nTrapdoor under your legs open and you "+
   "fall down!\n");
 say(QCTNAME(TP)+" suddenly disapprears from site!\n");
 TP->move_living("M","/d/Earthsea/tricksters/entrance");
 tell_room(ENV(TP),QCTNAME(TP)+" falls from above.\n",TP);

 if (!QH_QUERY_QUEST_COMPLETED(TP,"tricksters_entrance"))
  {
   write("Congratulations! You have found Tricksters hidden lair!\n");
   write("You feel little more experienced!\n");
   QH_QUEST_COMPLETED(TP,"tricksters_entrance");
  }

 return 1;
}

