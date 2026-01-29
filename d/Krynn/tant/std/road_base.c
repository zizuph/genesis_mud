/* Road base file for Tantallon.
* By Teth, Jan 17 , 1996
*/

#include "../local.h"

inherit OUTROOM; 
inherit HERBSEARCHNEW

#include RND_MEET

string *herbs = HERB_MASTER->query_herbs( ({ "hills", }) );

object monster;

public void
reset_tant_room()
{
    set_searched(random(2));
    {
    if (random(2))
      return;
    
    if (monster)
      return;
    monster = RANDOM_MEET("/d/Krynn/common/rndtables/tbltantroad");
    monster->move(TO);
    }
}

public void
create_road()
{
   
}

nomask void
create_tant_room()
{
   set_place(ROAD);
   set_long_desc("Foothills and mountains surround you, although the " +
       "peaks of the mountains are softened by time. Scraggly plants line " +
       "the road.");

   AI(({"peaks","mountain peaks"}),"The mountain peaks are softened, " +
       "and do not have cragged edges.\n");
   AI(({"peak","mountain peak"}),"The mountain peak stands tall against " +
       "the sky.\n");
   AI("sky","It's above you.\n");
   AI(({"road","winding road"}),"This road leads through foothills and " +
       "mountains.\n");   
   AI(({"foothills","hills"}),"The foothills are rolling, and seem to " +
       "melt into the mountains.\n");
   AI("mountains","The mountains to the west are a range of the " +
       "Kharolis mountains, while the mountains to the east are the " +
       "Forsaken Mountains.\n");
   AI("forsaken mountains","The Forsaken Mountains have an aura of gloom " +
       "about them.\n");
   AI("kharolis mountains","The Kharolis Mountains are an extensive " +
       "range of mountains, running south from this region of Abanasinia, " +
       "to the Plains of Dust.\n");
   AI(({"mountain range","range"}),"Which mountain range?\n");
   AI("mountain","Every mountain looks similar to you, and none stand out.\n");
   AI(({"foothill","hill"}),"The hills are alike in most ways, although " +
       "they each have their individual differences, of course.\n");
   AI(({"plants","scraggly plants"}),"Some of the plants may be useful " +
       "herbs.\n");
   AI("plant","This plant may be a useful herb.\n");

   OUTSIDE;
   
   seteuid(getuid(TO));
   set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
       ONE_OF(herbs) }), ({ "scraggly plants", "plant", "plants", }), 3);
 

   set_tell_time(400);
   add_tell("A cool breeze sweeps by you.\n");
   add_tell("The echo of a rock falling down a mountain reaches your ears.\n");
   add_tell("A creature in the distance howls!\n");
   add_tell("Something scurries off the road ahead of you.\n");
   add_tell("You can hear the roar of a distant waterfall.\n");

   create_road();
   reset_tant_room();
   
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
 
    if (interactive(ob))
    start_room_tells();
}
