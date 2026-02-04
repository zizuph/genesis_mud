/* greenhouse2.c */
/* janus 930408 */

/*
    Modified: 6 May 2003, by Bleys
        - "pick" without an arg was causing some
            odd behaviour ("You pick up the 0"). Added an
            argument check to do_pick()
        - added two more reasonable actions, "get" and
            "take," because "pick hacksaw" is not
            exactly standard English
        - modernized the includes and standardized the
            inherit
	Modified: 20 January 2017, by Mirandus
		-Removed "get" from the list of actions that invokes
		do_pick() as this prevents people from getting anything
		they may have put down.

*/

#include "/d/Terel/include/Terel.h"

inherit STDROOM;
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>

#define JANUSDIR        DOMAIN_DIR + "janus/"

init()
{
  ::init();
  add_action("do_pick","pick");
  add_action("do_pick","take"); // Added 6 May 2003
}

create_room()
{
  set_short("hothouse");
  set_long(BS("You are inside a large hothouse. The air is warm " +
              "and humid. Standing in neat rows are benches packed "+
             "with claypots. Most of the pots are filled with flowers"+
              ", small bushes, and strange plants. "+
              "There is a small rack and a bench standing in the middle "+
              "of the room. \n"));
  add_exit(JANUSDIR + "garden/ghouse/gh1", "west",0);
  add_exit(JANUSDIR + "garden/ghouse/gh5", "north",0);
  add_exit(JANUSDIR + "garden/ghouse/gh6", "south",0);
  add_prop(OBJ_I_SEARCH_TIME,15);
  add_prop(OBJ_S_SEARCH_FUN,"do_search");
 add_item(({"bench","benches"}),BS("These are large benches made out "+
    "of wood. Almost all of the benches are stacked with pots of all "+
    "kinds. \n"));
  add_item(({"walls","hothouse","glass"}),BS("The water in the humid air has"+
     " condensed on the glass walls, making it impossible to see out " +
     "through the windows. \n"));
  add_item(({"plants","flowers","claypots","pots"}),
            BS("There are a plethora of strange plants in the pots. " +
               "All of the plants seems to be in very good shape. \n"));
add_item(({"bush","bushes"}),BS("These neatly trimmed bushes looks "+
   "like midget trees. The shapes are right but they "+
   "are only about 1 foot high.\n"));
  add_item(({"walls","hothouse","glass","wall"}),
     BS("The water in the humid air has"+
     " condensed on the glass walls, making it impossible to see out " +
     "through the windows. \n"));
  add_item(({"rack","bench"}),
     BS("There are a lot of different tools lying on the bench "+
        "and hanging on the rack. \n"));
  add_item(({"tools","tool"}),
     BS("Of the tools you recognize a hacksaw, a pair of scissors, a "+
        "small rake, and a hammer. \n"));
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
   return BS("You find nothing of value among the plants.\n");
}

do_pick(string tool)
{
  object warning;
  object diploma;
  object ball;
  object ob;
  int test;

  string verb = query_verb(); // Added 6 May 2003

  warning = present("warning",TP);
  diploma = present("diploma",TP);
  seteuid(getuid(TO));
  test = TP -> query_prop("picked_tool");

  // if statement added 6 May 2003
  if ( !tool )
  {
    NF(capitalize(verb) + " what?\n");
    return 0;
  }

  if (test >3 ){
    write(BS("Don't you think you have had your share of tools today. "+
         "Better leave the rest for the gardener. \n"));
    return 1;
  }
  if (diploma ){
    if (tool == "hacksaw" || tool == "up hacksaw" || tool == "small hacksaw"){
      write(BS("You take a hacksaw from the heap.\n"));
      clone_object(JANUSDIR + "garden/hacksaw")->move(TP);
      TP-> add_prop("picked_tool",test + 1);
      say(QCNAME(TP)+" picks up something from the tool heap.\n");
      return 1;
    }
    if (tool == "scissors" || tool == "pair of scissors" || tool == "up scissors" || tool == "up pair of scissors"){
      write(BS("You take a pair of scissors from the heap.\n"));
      clone_object(JANUSDIR + "garden/scissors")->move(TP);
      TP-> add_prop("picked_tool",test + 1);
      say(QCNAME(TP)+" picks up something from the tool heap.\n");
      return 1;
    }
    if (tool == "rake" || tool == "up rake" || tool == "up small rake"){
      write(BS("You take a rake from the heap.\n"));
      clone_object(JANUSDIR + "garden/rake")->move(TP);
      TP-> add_prop("picked_tool",test + 1);
      say(QCNAME(TP)+" picks up something from the tool heap.\n");
      return 1;
    }
    if (tool == "hammer" || tool == "up hammer" || tool == "small hammer"){
      write(BS("You take a hammer from the heap.\n"));
      clone_object(JANUSDIR + "garden/hammer")->move(TP);
    TP-> add_prop("picked_tool",test + 1);
    say(QCNAME(TP)+" picks up something from the tool heap.\n");
    return 1;
    }
    if (tool == "flower" || tool == "plant" || tool == "up flower"){
      write(BS("There are no plants suitable for taking here.\n"));
    return 1;
    }
   write(BS("You can't find that "+ tool +". Examine the rack to see "+
         "what kind of tools that can be taken.\n"));
  return 1;
  }
  if (warning){
    write(BS("When you try to take one of the "+ tool +", a hand appears and "+
     "punches you in the face, VERY HARD ... As if by magic a Ball and "+
     "Chain locks itself around your foot.\n"));
    TP->reduce_hit_point(10);
    clone_object(JANUSDIR + "garden/balls.c")->move(TP);
    say("As "+QCNAME(TP)+" tries to pick a tool, a hand materializes \n"+
    "out of nowhere and punches "+QCNAME(TP)+" right in the face. \n"+
    "As if by magic a Ball and Chain appears around "+QCNAME(TP)+"'s \n"+
    "foot.\n");
    TP->do_die(this_object());
    return 1;
  }
  write( "When you try to take one of the "+ tool +", a hand appears and \n"+
    "slaps your fingers, OUCH. As if by magic something appears in\n"+
    "your pocket.\n");
  TP->reduce_hit_point(2);
  clone_object(JANUSDIR + "garden/ycard.c")->move(TP);
    TP->do_die(this_object());
  return 1;
}

