/*
 * bk_tree_base.c
 *
 * Base file for up in a tree of the bee keeper's grove
 *
 * Zima - May 16, 98
 */
#pragma strict_types
#include <macros.h>
#include <wa_types.h>
#include "/d/Khalakhor/sys/defs.h"
#include "/d/Khalakhor/sys/paths.h"
#include "/d/Khalakhor/sys/terrains.h"
#include "room.h"
#define  BEES_PER_SWARM  10
#define  MAX_SWARMS      3
#define  MAX_COMBS       5
 
inherit "/d/Khalakhor/std/room";
inherit "/d/Khalakhor/guilds/sean-rhian/lib/branchcmd";
 
string grove_rm=(ROOM+"bk_grove_base");
string home_rm=ROOM+"bk_tree_base";
int    numbees;
int    numcombs;
 
//
// general set and query functions
//
public void   set_grove_rm(string s) { grove_rm=s; }
public string query_grove_rm()       { return grove_rm; }
public object query_pointer()        { return TO; }
public void   return_bee()           { numbees++; }
public void   leave_bee()            { numbees--; }
public int    query_numbees()        { return numbees; }
public int    query_numcombs()       { return numcombs; }
public void   set_bee_home(string s) { home_rm = s; }
public string query_bee_home()       { return home_rm; }
 
//
// reset_room
//
public void reset_room()
{
   set_numbranches(1);
   numbees  = BEES_PER_SWARM * MAX_SWARMS;
   numcombs = MAX_COMBS;
}
 
 
//
// create_tree_rm
//
public void
create_tree_rm()
{
   set_short("In a tall tree");
   set_long("   You are sitting in the branches of a tall tree, one "+
      "of five in a grove on a hill. You have a spectacular view of "+
      "all around you...the rolling grassy plains to the north and east, "+
      "the waters of Lear Min on the horizon to the west, and the village "+
      "of Tabor Sogh to the south. You can also see the thatched roof of "+
      "the nearby farm house. The dark branches of the tree are lushly "+
      "filled with oblong dark green leaves, shading you as you sit "+
      "in your perch. There is a rather large beehive here, buzzing "+
      "with activity on the inside.\n");
 
   BEES; // bees will follow victim into tree rooms
 
   add_item(({"grove","hill","plain","plains"}),
      "The tree you are sitting in is situated on top of a hill "+
      "in the middle of the grassy plains. The plains roll out in "+
      "all directions, low rolling hills covered with short grass, "+
      "meeting the shores of the sea to the west.\n");
   add_item(({"village","Tabor Sogh","buildings"}),
      "To the south and a little west, you see the thatched roofs "+
      "of the low stone buildings which make up the village. Smoke "+
      "wafts from several of the chimneys of the buildings.\n");
   add_item(({"house","home","dwelling","farm house"}),
      "Just below you, a little to the southwest at the base of "+
      "the hill, you see the rural home of a local farmer, probably "+
      "a bee keeper, as you now surmise. Its low stone walls and "+
      "thatched roof is very unassuming.\n");
   add_item(({"hills","area"}),
      "The area around the grove consists of low grassy hills, "+
      "tree-less and rolling, leading out to the sea far to the "+
      "west.\n");
   add_item(({"water","waters","Lear Min","sea"}),
      "You can see the waters of Lear Min on the horizon to the west, "+
      "its choppy waters rippled with large waves crashing on the "+
      "shore.\n");
   add_item("trees",
      "There are five tall trees in this grove, set neatly and "+
      "evenly apart. You are sitting in the branches of one of them, "+
      "the branches filled with green leaves.\n");
   add_item("tree",
      "The tree you are sitting in, like its brothers and sisters "+
      "nearby, seems to be a tall ash tree. Its bark is gray-black "+
      "and rough, and it has oblong leaves with saw-toothed "+
      "edges. Just in front of you there is a beehive, the hum of "+
      "its inhabitants a constant noise. Small blocks nailed to the "+
      "trunk of the tree form a crude ladder down which you can climb.\n");
   add_item(({"blocks","ladder","side","side of tree"}),
      "Small long blocks have been nailed horizontally up the "+
      "side of a tree forming a crude ladder. You could can climb down "+
      "on them.\n");
   add_item("leaves",
      "They are oblong leaves which end in a sharp narrow point, "+
      "dark green on one side and greenish-brown on the other. "+
      "They have serrated or saw-toothed edges.\n");
   add_item(({"hive","beehive"}),
      "About five times the size of your head, this hive is made of "+
      "dead branches and leaves, bonded together with beeswax. There "+
      "is a large hole at the base of the hive, which seems to have "+
      "been artificially cut, though the inhabitants don't seem to "+
      "mind using it. Inside, you see honey-coated combs of beeswax, "+
      "the product of those who live inside, and who would probably "+
      "be irritated if you disturbed them, though the honeycombs "+
      "are very enticing.\n");
   add_item(({"comb","honeycomb","combs","honeycombs","hole","entrance"}),
      "Just inside the hole of the hive, you see combs of wax soaked "+
      "with sweet honey. The hole seems to have been cut to allow "+
      "access to the combs, though you ponder who would be so foolish "+
      "as to attempt to take the prize of the bees.\n");
   add_cmd_item(({"comb","comb from hive","honeycomb","honeycomb from hive"}),
      ({"take","get","pick","steal"}),"@@take_comb");
 
   set_branchnum(1); // ash tree branches available here
   reset_room();
}
 
//
// do_get_comb - player gets a comb, if any left
//
void do_get_comb()
{
   object comb;
   if (numcombs>0)
      {
      comb=clone_object(OBJ+"honeycomb");
      write("You reach into the beehive and pull out a sticky honeycomb.\n");
      tell_room(TO,QCTNAME(TP)+" reaches into the beehive and pulls out a "+
                   "sticky honeycomb.\n",TP);
      if (comb->move(TP))
         {
         write("You drop the honeycomb in the branches.\n");
         tell_room(TO,QCTNAME(TP)+" drops the honeycomb in the branches.\n",
                   TP);
         comb->move(TO);
         numcombs--;
         }
      }
   else
      write("None of the remaining combs can be taken.\n");
}
 
//
// do_swarm() - swarm of bees comes out of the hive, if any left
//
void do_swarm()
{
   object bee;
   int    i, num=BEES_PER_SWARM;
 
   if (num>numbees) num=numbees;
   if (num>0)
      {
      tell_room(TO,"A swarm of bees flies angrily out of the hive!\n");
      for (i=0; i<num; i++)
         {
         bee=clone_object(NPC+"bee");
         bee->set_monster_home(home_rm);
         bee->move(TO);
         }
      numbees -= num;
      }
}
 
//
// bk_protected - is this player protected from bee stings?
//
int bk_protected (object tp)
{
  string worn_objects = tp->show_worn();
  int res = wildmatch("*beekeepers suit*", worn_objects);
  return res;
}
 
//
// take_comb - player tries to take a honeycomb from the hive
//
string take_comb()
{
   if (bk_protected(TP))
      do_get_comb();
   else
      {
      write("You stick your hand into the beehive...\n"+
            "You are stung and pull it out with a yelp!\n");
      tell_room(TO,QCTNAME(TP)+" sticks "+HIS_HER(TP)+" hand into the "+
                   "beehive...\n"+QCTNAME(TP)+" is stung and pulls "+
                   HIS_HER(TP)+" hand out with a yelp!\n",TP);
      }
   if (numbees>0) do_swarm();
   return "";
}
 
//
// do_climb - msg when player does "down"
//
int do_climb() {
   write("You climb down the tree on the ladder of blocks.\n");
   return 0;
}
 
//
// climb - allow player to use "climb" to get down tree
//
int climb(string cmd)
{
   notify_fail("Climb what?\n");
   if (!stringp(cmd)) return 0;
   if ((!parse_command(cmd,all_inventory(TO),"'down' / 'ladder' / 'tree'"))&&
      (!parse_command(cmd,all_inventory(TO),"[down] / 'ladder' / 'tree'")))
      return 0;
   write("You climb down the tree on the ladder of blocks.\n");
   TP->move_living("climbing down the tree",grove_rm);
   return 1;
}
 
//
// init - add actions
//
void init()
{
   ::init();
   add_action(&break_branch(),"break");
   add_action(&climb(),"climb");
}
