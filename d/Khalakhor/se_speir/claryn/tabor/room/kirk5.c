/* Kirk of Tabor Sogh
**
** History:
** Date        Coder       Action
**----------   ----------- ----------------------------------
** 1/9/98      Zima        Created
**
*/
/* inherits/includes */
inherit "/d/Khalakhor/std/room";
#include <macros.h>
#include "kirk.h"
#define TZIMA (find_player("zima"))->catch_tell
#define NUM_MONKS 3
object *monk=allocate(NUM_MONKS);
int    chanting=0;
object altar, book;
 
int   query_chanting()    { return chanting; }
void  set_chanting(int i) { chanting=i; }

void reset_room() {
   int i;
   for (i=0; i<NUM_MONKS; i++)
      if (!monk[i]) {
         monk[i]=clone_object(SR_NPC+"kmonk");
         monk[i]->equip_me();
         if (i>0) // monk[0] guards the altar & does chants
            monk[i]->set_wander(ROOM+"kirk", MASTER_OB(TO), 60);
         monk[i]->move(TO);
         tell_room(TO,QCNAME(monk[i])+" enters the chamber.\n");
      }
}
 
/* room definition */
void create_khalakhor_room() {
   set_short("village kirk");
   set_long(
      "   You are in the central chamber of the village kirk, where "+
      "stone arches lead out to the north, south, east and west. "+
      "A dusty carpet covers the floor here, while small candelabrum in "+
      "the four corners light the room with their flickering candles. The "+
      "thatched ceiling rises to a point in the center of the room. You "+
      "detect the faint smell of sweet incense lingering in the air.\n");
 
   INSIDE;
   add_item(({"wall","walls"}),
      "They are simple stone walls.\n");
   add_item("ceiling",
      "It is a simple thatched ceiling, four triangular sides meeting at a "+
      "point over the center of the room.\n");
   add_item("arches",
      "They are crude stone arches marking the four entrances.\n");
   add_item("carpet",
      "It is an old dusty carpet made of white and green fibers, "+
      "bordered with shamrocks.\n");
   add_item(({"candle","candles","candelabrum","candelabra"}),
      "Four inornate candelabrum stand in the corners of the room, each "+
      "with nine candles set in its brass branches.\n");
 
   add_exit("kirk2","north");
   add_exit("kirk4","south");
   add_exit("kirk3","east");
   add_exit("kirk1","west");
   altar=clone_object(OBJ+"kaltar");
   book=clone_object(SR_BOOK+"canticles");
   altar->move(TO);
   book->move(altar);
   reset_room();
}
 
void do_bow(object ob)
{
      ob->command("emote places his hands together prayerfully and bows "+
                  "deeply toward the altar.");
}
 
void dc(string dir)
{
   object m=monk[0];
   m->command("emote faces "+dir+".");
   m->command("emote turns the page in the "+(book->short())+".");
   m->command("emote chants a canticle in an ancient tounge.");
}
 
void ok_ready() { chanting=0; }
 
void do_chant(int step)
{
   object m=monk[0];
 
   if (!objectp(m)) { chanting=0; return; }
   switch (step)
      {
      case 0:  if (!present(book,altar)) { chanting=0; return; }
               m->command("emote bows deeply toward the altar.");
               m->command("take book from altar");
               m->command("emote opens the "+(book->short())+".");
               break;
      case 1:  m->command("north"); break;
      case 2:  dc("west");          break;
      case 3:  dc("north");         break;
      case 4:  dc("east");          break;
      case 5:  m->command("south"); break;
      case 6:  m->command("east");  break;
      case 7:  dc("north");         break;
      case 8:  dc("east");          break;
      case 9:  dc("south");         break;
      case 10: m->command("west");  break;
      case 11: m->command("south"); break;
      case 12: dc("east");          break;
      case 13: dc("south");         break;
      case 14: dc("west");          break;
      case 15: m->command("north"); break;
      case 16: m->command("emote closes the "+(book->short())+".");
               m->command("put book on altar");
               m->command("emote bows deeply toward the altar.");
               set_alarm(1200.0,0.0,&ok_ready()); // do again? in 20 mins
               return;
      }
   set_alarm(7.0,0.0,&do_chant(step+1));
}
 
void start_chant()
{
   if (chanting||(!objectp(monk[0]))||(ENV(monk[0])!=TO)) return;
   chanting=1;
   do_chant(0);
}
 
void enter_inv(object ob, object from)
{
   if (ob->id(SR_NPC_ID)) set_alarm(3.0,0.0,&do_bow(ob));
   if ((interactive(ob))&& (!chanting)) set_alarm(7.0,0.0,&start_chant());
   ::enter_inv(ob,from);
}
