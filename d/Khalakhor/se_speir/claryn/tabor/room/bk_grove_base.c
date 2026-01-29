/*
 * bk_grove_base.c
 *
 * Base file for the bee keeper's grove rooms.
 *
 * Zima - May 16, 98
 */
#pragma strict_types
#include "/d/Khalakhor/sys/defs.h"
#include "/d/Khalakhor/sys/paths.h"
#include "/d/Khalakhor/sys/terrains.h"
 
#include "room.h"
 
inherit "/d/Khalakhor/std/room";
inherit "/d/Khalakhor/guilds/sean-rhian/lib/branchcmd";

string tree_rm;

void set_tree_rm(string s) { tree_rm=s; }
string query_tree_rm()     { return tree_rm; }
 
public void reset_room()
{
   set_numbranches(1);
}

public void
create_grove()
{
   set_short("In a grove of trees");
   set_long("   You are on a low hill amongst a sparsely-populated "+
      "grove of trees. Unusual for the surrounding area, these "+
      "trees must have been planted here by a local agrarian. " +
      "Placed neatly and evenly apart, you are standing next to "+
      "one now, while there are four others nearby.\n");
 
   BEES; // bees will follow victim in these rooms.

   set_branchnum(1);
   set_numbranches(1); // ash tree here
   add_item(({"grove","hill"}),
      "This little grove of five trees is situated on one of the "+
      "low hills of the grassy plain. It was obviously planted "+
      "by a local agrarian, the trees spaced neatly and evenly "+
      "apart.\n");
   add_item(({"hills","area"}),
      "The area around the grove consists of low grassy hills, "+
      "tree-less and rolling, leading out to the sea far to the "+
      "west.\n");
   add_item("sea",
      "You can barely see it from here. It is far to the west.\n");
   add_item("trees",
      "There are five tall trees in this grove, set neatly and "+
      "evenly apart. You are standing next to one of them, its "+
      "trunk rising high above you, while the other four are "+
      "nearby.\n");
   add_item("tree",
      "The tree you are standing by, like its brothers and sisters "+
      "nearby, seems to be a tall ash tree. Its bark is gray-black "+
      "and rough, and it has oblong leaves with saw-toothed "+
      "edges. High in the branches you see what looks like a "+
      "large bee hive. You notice blocks of wood have been nailed "+
      "to the side of the tree, forming a crude ladder.\n");
   add_item(({"blocks","ladder","side","side of tree"}),
      "Small long blocks have been nailed horizontally up the "+
      "side of a tree forming a crude ladder. You could probably "+
      "climb up on them.\n");
   add_item("leaves",
      "They are oblong leaves which end in a sharp narrow point, "+
      "dark green on one side and greenish-brown on the other. "+
      "They have serrated or saw-toothed edges.\n");
   add_item(({"hive","beehive"}),
      "It hangs high up in the tree. Climbing up and messing with it "+
      "would probably not be a good idea.\n");
 
   add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_WOODS);
 
}

int do_climb() {
   write("You climb up the tree on the ladder of blocks.\n");
   return 0;
}

int climb(string cmd)
{
   notify_fail("Climb what?\n");
   if (!stringp(cmd)) return 0;
   if (!parse_command(cmd,all_inventory(TO),"[up] 'ladder' / 'tree'"))
      return 0;
   write("You climb up the tree on the ladder of blocks.\n");
   TP->move_living("climbing up the tree",tree_rm);
   return 1;
}

void init()
{
   ::init();
   add_action(&climb(),"climb");
   add_action(&break_branch(),"break");
}
