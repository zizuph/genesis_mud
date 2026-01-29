inherit "/std/room";
#include "defs.h"

void gag();
void overboard(object ob);

void
create_room()
{
   set_short("An old ship.");
   set_long(break_string(
         "This is the deck of an old ship. It has just gotten underway. "+
         "As soon as you dropped on to its old wooden deck, "+
         "it emerged from a system of caves into the open "+
         "ocean. Where it is headed you can not tell and you "+
         "probably don't want to know.\n",74));
}

enter_inv(object ob, object from)
{
   if(!living(ob))
      return;
   set_alarm(5.0, 0.0, gag);
   set_alarm(12.0, 0.0, &overboard(ob));
   return;
}


void
gag()
{
   tell_room(TO,"You are tied and gagged.\n");
}

void
overboard(object ob)
{
   tell_room(TO,"You are thrown overboard.\n");
   ob->move_living("M",THIS_DIR+"over_board");
}


