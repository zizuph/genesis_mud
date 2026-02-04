/* garden4.c */
/* janus 920822 */
inherit "/std/room";
#include <ss_types.h>
#include <macros.h>
#include <tasks.h>
#include "/d/Terel/common/terel_defs.h"

#define TP           this_player()
#define BS(message)   break_string(message,70)

reset_room()
{
  object moundi;
  if(present("moundi"))return;
  moundi=clone_object(JANUSDIR + "garden/moundi");
  moundi->move(this_object());
}

create_room()
{
  set_short("Grove");
  set_long(BS("You have entered a beautiful grove. The trees are "+
	      "massive and huge. The air is cooler here than in other parts "+
	      "of the garden. The ground here is mostly covered by grass, but"+
	      " there are a few bushes. \n"));
  add_exit(JANUSDIR + "garden/garden2", "east",0);
  add_item(({"tree","trees"}),BS("Normal healthy trees.\n"));
  add_item(({"bush","bushes"}),BS("Examining the bushes closer" +
	  " you notice a small rabbit hole going down and a small mound. One "+
	  "bush also seems damaged by some vermin. \n"));
  add_item(({"rabbit hole","hole"}),
	   BS("Looks like a normal rabbit hole. If you were 5 inches"+
	      " tall you could enter easily. Otherwise there is nothing you"+
	      " can do, maybe you could stick your hand in there.\n"));
  add_item(({"mound"}), 
	   BS("Looking closer at the mound you see that there are "+
	      "some strange looking insects scurrying to and from the "+
	      "mound. Some insects are carrying pieces of plants.\n"));
  add_item(({"oak tree"}), 
	   BS("A really huge oak. There are plenty of branches and it "+
              "looks like it would be easy to climb this tree.\n"));
  add_item(({"grass","green grass"}), 
	   BS("It seems to be greener on the other side. \n"));
  add_item(({"insects","black instects","small insects"}), 
	   BS("The small tiny black bugs are almost everywhere. Some are "+
              "carrying pieces of leaves and some are carrying other things."+
              " Most of them going to and from the small mound. \n"));
  add_item(({"birch tree"}), 
	   BS("Looking closer at this tree you see that it appears "+
              "to be  climbable. Lots of branches, but not to many so that "+
              "the way is blocked. The crown of the tree is quite large and"+ 
              " and dense, so that you cannot see if there is something or "+
              "or someone hidden up there.\n"));
  add_cmd_item(({ "tree", "trees"}), "climb",
           BS("Which tree are you "+
              "trying to climb ? The climbable ones are an oak and a "+
              "birch tree.\n"));
  add_cmd_item(({ "insects", "insect"}),({"stomp","trample"}),"@@do_stomp");
  add_cmd_item(({ "mound"}),({"stomp","trample"}),"@@do_stomp2");
  add_cmd_item(({ "oak"}), "climb", "@@climb_tree");
  add_cmd_item(({ "birch tree","birch"}), "climb", "@@climb_tree2");
 add_cmd_item(({ "hand in hole","hand into hole"}),"stick"
      ,"@@put_hole");
  reset_room();
}
do_stomp()
{
  write(BS("You start stomping on the mound and the insects. "+
	   "You manage to stomp some to insects to pulp but most of them "+
	   "evade you. \n"));
  say(QCNAME(TP)+" starts stomping around in the grass.\n");
  return 1;
} 
do_stomp2()
{
  write(BS("You start stomping on the mound, but nothing "+
	   "happens. It must be made of tough stuff. \n"));
  say(QCTNAME(TP)+" starts stomping around in the grass.\n");
  return 1;
} 
put_hole()
{
   write(BS("You stick your hand into the rabbit hole and feel around,"+
     " and you find nothing remarkable here. \n"));
   say(QCTNAME(TP)+" examines a rabbit hole closely.\n");
   return 1;
}

climb_tree()
{
  int success;
  int lvl;
  lvl = this_player()->query_skill(SS_CLIMB);
  success = lvl - random(20) - 10;
  if (success < -10) {
    write(BS("You made it to the top. Unfortunately a branch breaks and "+
	     "you make a perfect one point landing on your face.\n"));
    say(QCTNAME(TP) + " climbing the oak but falls after almost \n"+
        "reaching the top. \n");
    TP->reduce_hit_point(50);
    return 1;
  }
  if (success < 0) {
    write(BS("You start to climb, but fall down from a low height.\n"));
    say(QCTNAME(TP) + " tried to climb the tree but failed, and fell.\n");
    return 1;
  }
  if (success < 20) {
    write(BS(
	  "There are plenty of branches so you climb the oak tree easily.\n"));
    TP->move_living("the area by climbing the oak tree with ease.",
		    JANUSDIR + "garden/oak");
    return 1;
  }
  write(BS(
	   "You climb the tree with practised ease.\n"));
  TP->move_living("by climbing up the oak tree with practiced ease",
		  JANUSDIR + "garden/oak");
  return 1;
}
climb_tree2()
{
  int success;
  int lvl;
  lvl = this_player()->query_skill(SS_CLIMB);
  success = lvl - random(20) - 13;
  if (success < -10) {
    write(BS(
	     "You made it to the top. Unfortunately a branch breaks and "+
	     "you make a perfect one point landing on your face.\n"));
    say(QCTNAME(TP) + " by climbing the birch but falls after almost \n"+
        "reaching the top. \n");
    TP->reduce_hit_point(50);
    return 1;
  }
  if (success < 0) {
    write(BS(
	     "You start to climb, but fall down from a low height.\n"));
    say(QCTNAME(TP) + " tried to climb the tree but failed, and fell.\n");
    return 1;
  }
  if (success < 20) {
    write(BS(
	     "There are plenty of branches so you climb the birch tree easily.\n"));
    TP->move_living("by climbing up the birch tree with ease.",
                    JANUSDIR + "garden/birch");
    return 1;
  }
  write(BS(
	   "You climb the tree with practised ease.\n"));
 TP->move_living("by climbing up thebirch tree with practiced ease",
                  JANUSDIR + "garden/birch");
  return 1;
}

