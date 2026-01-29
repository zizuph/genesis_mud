inherit "/std/room";
#include "defs.h"

/* Prototypes */
void sentance2(object ob);
void sentacne3(object ob);

void
create_room()
{
   set_short("This is a place of shame and dishonour.\n");
   set_long(break_string(
         "This is a place of shame and dishonour. It is where "+
         "dishonourable pirates are sentanced to their deaths. "+
         "Keel-hauling is the typical sentance. Your sentance "+
         "shall arrive shortly.\n",74));
}

void
enter_inv(object ob,object from)
{
   if(!living(ob))
      return;
   set_alarm(10.0, 0.0 &sentance(ob));
   return;
}

void
sentance(object ob)
{
   tell_room(TO,break_string(
         "You hear the sound of wood crashing on wood echoing "+
         "through the room.\n",74));
   set_alarm(2.0, 0.0, &sentance2(ob));
}

void
sentance2(object ob)
{
   tell_room(TO,"You hear a multitude of voices murmuring "+
      "in the distance.\n");
   set_alarm(4.0, 0.0, &sentance3(ob));
}


void
sentance3(object ob)
{
   tell_room(TO,"You hear a voice ringing through the room. "+
      "The voice is loud and clear.\n"+
      "The voice says:\n"+
      "You have been found guilty of treason and dishonour.\n"+
      "You have broken the pledge of piracy.\n"+
      "This is blasphemous and intollerable!\n"+
      "You shall receive the maximum penalty... \n"+
      "Death by keel-hauling!\n");
   set_alarm(14.0, 0.0, &to_the_ship(ob));
}

void
to_the_ship(object ob)
{
   tell_room(TO,"You fall through a trap door.\n");
   ob->move_living("M",THIS_DIR+"keel_hauler");
}
