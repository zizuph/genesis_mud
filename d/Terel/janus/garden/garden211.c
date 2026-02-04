/* garden211.c */
/* janus 920817 */
inherit "/std/room";
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include "/d/Terel/common/terel_defs.h"

#define BS(message)    break_string(message, 70)
#define TP             this_player()
#define TO             this_object()

object recipe;
init()
{
  ::init();
  add_action("do_pick","pick");
}

create_room()
{
  set_short("gardeners hut");
  set_long(BS("This small hut contains a plethora of gardening tools and " +
      "equipment. Most of the tools are neatly stacked on shelves, " +
      "but some lie in a big heap on the floor and on the bench. " +
    "A small window in the north wall lets in some light into the hut.\n"));
  add_exit(JANUSDIR + "garden/garden21", "southeast",0);
  add_prop(OBJ_I_SEARCH_TIME,15);
    add_prop(ROOM_I_INSIDE, 1);
  add_prop(OBJ_S_SEARCH_FUN,"do_search");
  add_item(({"window","small window"}),BS("Looking through the small "+
    "window you see a large glass-house to the north. Looking "+
    "closer at the house you see that it is some kind of a "+
    "greenhouse.\n"));
  add_item(({"bench","toolbench"}),BS("This is a small meticously "+
     "clean toolbench. There are a few tools neatly placed on it.\n"));
 add_item(({"shelf","shelves"}),BS("Small wooden shelves neatly "+
    "stacked with gardening implements. \n"));
  add_item(({"tool","tools","heap"}),BS("There are tools of all kinds here, " +
     "you see a hacksaw, a small hammer, a pair of scissors, " +
     "a small hatchet, a small rake, and a strange gizmo. " +
     "If you want to examine them further you need to pick them up.\n"));
}

do_pick(string tool)
{
  object warning;
  object diploma;
  object ball;
  object ob;
  int test;
  warning = present("warning",TP);
  diploma = present("diploma",TP);
  seteuid(getuid(TO));
  test = TP -> query_prop("picked_tool");
  if (test >3 ){
    write(BS("Don't you think you have had your share of tools today. "+
	     "Better leave the rest for the gardener. \n"));
    return 1;
  }
  if (diploma ){
    if (tool == "hacksaw" || tool == "up hacksaw" || tool == "small hacksaw"){
      write(BS("You take a hacksaw from the heap.\n"));
      clone_object(JANUSDIR + "garden/hacksaw")->move(TP, 1);
      TP-> add_prop("picked_tool",test + 1);
      say(QCNAME(TP)+" picks up something from the tool heap.\n");
      return 1;
    }
    if (tool == "hatchet" || tool == "small hatchet" || tool == "up hatchet"){
      write(BS("You take a small hatchet from the heap.\n"));
      clone_object(JANUSDIR + "garden/hatchet")->move(TP, 1);
      TP-> add_prop("picked_tool",test + 1);
      say(QCNAME(TP)+" picks up something from the tool heap.\n");
      return 1;
    }
    if (tool == "scissors" || tool == "pair of scissors" || tool == "up scissors" || tool == "up pair of scissors"){
      write(BS("You take a pair of scissors from the heap.\n"));
      clone_object(JANUSDIR + "garden/scissors")->move(TP, 1);
      TP-> add_prop("picked_tool",test + 1);
      say(QCNAME(TP)+" picks up something from the tool heap.\n");
      return 1;
    }
    if (tool == "gizmo" || tool == "up gizmo"){ 
      write(BS("You take the strange gizmo from the heap.\n"));
      clone_object(JANUSDIR + "garden/gizmo")->move(TP, 1);
      TP-> add_prop("picked_tool",test + 1);
      say(QCNAME(TP)+" picks up something from the tool heap.\n");
      return 1;
    }
    if (tool == "rake" || tool == "up rake" || tool == "up small rake"){     
      write(BS("You take a rake from the heap.\n"));
      clone_object(JANUSDIR + "garden/rake")->move(TP, 1);
      TP-> add_prop("picked_tool",test + 1);
      say(QCNAME(TP)+" picks up something from the tool heap.\n");
      return 1;
    }
    if (tool == "hammer" || tool == "up hammer" || tool == "small hammer"){   
      write(BS("You take a hammer from the heap.\n"));
      clone_object(JANUSDIR + "garden/hammer")->move(TP, 1);
    TP-> add_prop("picked_tool",test + 1);
    say(QCNAME(TP)+" picks up something from the tool heap.\n");
    return 1;
}

   write(BS("You can't find that "+ tool +". Examine the heap to see "+
         "what kind of tools that can be taken.\n"));
  return 1;
  }
  if (warning){
    write(BS("When you try to take one of the tools, a hand appears and "+
     "punches you in the face, VERY HARD ... As if by magic a Ball and "+
     "Chain locks itself around your foot.\n"));
    TP->reduce_hit_point(10);
    clone_object(JANUSDIR + "garden/balls.c")->move(TP, 1);
    say("As "+QCNAME(TP)+" tries to pick a tool, a hand materializes \n"+
	"out of nowhere and punches "+QCNAME(TP)+" right in the face. \n"+
	"As if by magic a Ball and Chain appears around "+QCNAME(TP)+"'s \n"+ 
	"foot.\n");
    TP -> do_die();
    return 1;
  }
  write( "When you try to take one of the tools, a hand appears and \n"+
	"slaps your fingers, OUCH. As if by magic something appears in\n"+
	"your pocket.\n");
  TP->reduce_hit_point(2);
  clone_object(JANUSDIR + "garden/ycard.c")->move(TP, 1);
  say(BS("As "+QCNAME(TP)+" tries to pick a tool, a hand \n"+
	 "materializes out of nowhere and slaps "+QCNAME(TP)+"'s \n"+
	 "hand.\n"));
  TP -> do_die();
  return 1;
} 
do_search()
{
  object ob;
  int i1;
  int i2;
  i1 = TP -> query_skill(SS_AWARENESS);
  i2 = i1- random(15);
  seteuid(getuid(this_object()));
  if (!CAN_SEE_IN_ROOM(TP)){
     return BS("You are blind as a bat in the darkness, so you'd better "+
               "get some light if you want to search here. \n");
  }
  if ( i2 > 0 ){
    seteuid(getuid(this_object()));
        if (!recipe ){
            recipe = clone_object(JANUSDIR + "garden/recipe");
             recipe -> move(TO);
     return BS("You find a small piece of paper among the tools.\n");
         }
   }
   return BS("You find nothing of value among the tools.\n");
}
