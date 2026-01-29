/* Sewer base file for Tantallon.
* By Teth, Jan 17 , 1996
*/

#include "../local.h"

inherit INROOM; 
inherit HERBSEARCHNEW

#include RND_MEET

string *herbs = HERB_MASTER->query_herbs( ({ "sewer", }) );

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
    monster = RANDOM_MEET("/d/Krynn/common/rndtables/tbltantsewer");
    monster->move(TO);
    }
}

public void
create_sewer()
{
   
}

nomask void
create_tant_room()
{
   set_short("In the sewers beneath Tantallon");
   set_long("You are in the sewers beneath Tantallon. Raw sewage bubbles " +
       "beneath your feet as it flows. The walls of the sewer " +
       "are actually pipe, covered with slime. ");

   AI(({"sewers","sewer"}),"You are in them, and sometimes you wonder why.\n");
   AI("tantallon","It's the city above you. You can see no way of getting " +
       "there from here.\n");
   AI(({"sewage","raw sewage"}),"The sewage reminds you of human wastes " +
       "and excrement, mainly because that is exactly what it is.\n");
   AI(({"walls","wall","floor","ceiling"}),"Surrounding you entirely is a " +
       "huge metal pipe.\n");
   AI(({"metal pipe","pipe","huge pipe","huge metal pipe"}),"The huge metal " +
       "is covered with slime on the walls and ceiling, and sewage " +
       "flows along the floor.\n");
   AI("slime","The slime on the walls is not very appealing. It is " +
       "fungal in origin, most likely.\n");
   AI("fungi","The fungi is the slime that covers the walls.\n");
   ACI("slime",({"feel","touch"}),"It is slimy to the touch, you expected " +
       "something different, perhaps?\n");
   add_prop(ROOM_S_DARK_LONG, "The dark sewers beneath Tantallon. It " +
       "is impossible to see, even with your eyes wide open! There must " +
       "be an exit here somewhere...\n");
   add_prop(ROOM_S_DARK_MSG, "The darkness of the sewers makes it " +
       "impossible to");
   add_prop(ROOM_I_LIGHT, 0);
   
   seteuid(getuid(TO));
   set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
       ONE_OF(herbs) }), ({ "sewage", "walls", "slime", }), 3);

   set_tell_time(400);
   add_tell("Drip! Drip! DRIP!\n");
   add_tell("Something moves in the sewage beneath your feet.\n");
   add_tell("SCREEEEEEEE---!! A sound of metal scraping on rock, maybe?\n");
   add_tell("Glurg! Glurg! Glurg! bubbles the sewage.\n");
   add_tell("A scream in the distance!\n");
   add_tell("Something rattles nearby.\n");

   create_sewer();
   reset_tant_room();
   
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
 
    if (interactive(ob))
    start_room_tells();
}


