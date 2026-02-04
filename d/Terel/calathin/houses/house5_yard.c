/*  house5a.c 
    Tomas 11/19/1999

    Modified: 13 June 2003, by Bleys
        - Updated log entry.

*/

inherit "/std/room.c";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Terel/include/quest_bits.h"
#include "/d/Terel/include/Terel.h"

object door;
object momma;


public void
reset_room()
{
   if (momma) return;

   momma = clone_object("/d/Terel/calathin/houses/npc/momma");
   momma->move(this_object());
}

public void
create_room()
{
  
  INSIDE;
  set_short("yard");
  set_long("You stand before a modest looking house. " +
     "A stack of firewood rests alongside the house " +
     "in front of a chopping block. A small childs swing " + 
     "hangs from a tree against the western side of the yard.\n");

  add_item(({"chopping block","block","firewood","wood"}),
     "A stack of firewood and its chopping block can " +
     "be seen alongside the house.\n");

  add_item(({"tree","swing"}),
     "A small childs swing hangs on a tree on the west side of the " +
     "yard.\n");


  add_cmd_item(("swing"),
               ({"swing","sit","sit on"}),
               ("The swing looks too fragile for you to sit on.\n"));
           
  add_exit(CALATHIN_DIR + "paths/path_w05", "south", 0,1);

  door = clone_object(CALATHIN_DIR + "houses/obj/house5_door");
       door->move(TO);
       
   reset_room();
}



public void
end_up(object ed)
{
   tell_room(this_object(), QCTNAME(momma) + " and " + QTNAME(ed) +
             " leave.\n", ({ed, momma}));
   momma->remove_object();
   ed->remove_object();
}

public void
do_alt_quest(object ed, object who)
{
   who->catch_msg(QCTNAME(momma) + " looks over you with an air " +
                  "of recognition.\n");
   momma->command("say You know, I am starting to wonder " +
                  "why you keep turning up with my child.");
   momma->command("say You stay away from my son.");
   momma->command("shout GET OUT OF MY YARD!");

   who->catch_msg("You now understand that if you keep finding the " +
         "same lost child too many times, mothers are going to wonder " +
         "why the child gets lost in the first place.\n");
}

public void
do_quest(object ed, object who)
{
   int expnum;

   seteuid(getuid());
   
   if (!who || environment(who) != this_object())
       return;
   if (!ed || environment(ed) != this_object())
       return;
   if (!momma || environment(momma) != this_object())
       return;

   momma->command("say Edward! You're home!");
   ed->command("shout Momma!");
   
   if (who->test_bit("Terel", QUEST_CHILD_GROUP, QUEST_CHILD_BIT))
   {
     do_alt_quest(ed, who);
     end_up(ed);
     return;
   }

   tell_room(this_object(), QCTNAME(momma) + " and " + QTNAME(ed) +
             " hold a heartwarming reunion.\n", ({ed, momma}));

   momma->command("say Thank you for bringing him home.  I wish " +
                  "I had something to reward you with, but I have " +
                  "nothing.");
   who->catch_msg("The gods, who happen to be looking over you, are " +
                  "impressed by your good deed and have decided to " +
                  "reward you with more experience.\n");

   who->set_bit(QUEST_CHILD_GROUP, QUEST_CHILD_BIT);
   expnum = who->query_exp();
   if (expnum > QUEST_CHILD_EXP)
       expnum = QUEST_CHILD_EXP;

   who->add_exp(expnum, 0);
    /*
   write_file(QUEST_LOG, who->query_name() + " solved " +
              "child_quest (" + ctime(time()) + ")\n");
    */
    write_file(QUEST_LOG, who->query_name() + " returned " +
        "a lost child to his mother (child_quest) (" +
        ctime(time()) + ")\n");
   
   end_up(ed);
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    
    if (!ob || !living(ob)) return;
    
    if (ob == present("edward"))
        set_alarm(2.0, -1.0, &do_quest(ob, ob->query_solver()));
}

