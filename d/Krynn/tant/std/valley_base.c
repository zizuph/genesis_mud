/* Valley base file for Tantallon.
* By Teth, Jan 17 , 1996
*/

#include "../local.h"

inherit OUTROOM; 
inherit HERBSEARCHNEW

#include RND_MEET

string *herbs = HERB_MASTER->query_herbs( ({ "prairie", }) );

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
    monster = RANDOM_MEET("/d/Krynn/common/rndtables/tbltantvalley");
    monster->move(TO);
    }
}

public void
create_valley()
{
   
}

nomask void
create_tant_room()
{
    set_place(VALLEY);
    set_long_desc("This valley is a flat plain. It is perhaps an old " +
        "riverbed, dating back to before the Cataclysm. Now, it " +
        "is a dry prairie, nestled within the surrounding foothills.");
    AI(({"plain","flat plain"}),"It is just that, level throughout.\n");
    AI("valley","You are standing within the valley.\n");
    AI(({"old riverbed","riverbed"}),"The soft contours " +
        "of the land suggest an old river once ran its course " +
        "through this area.\n");
    AI(({"prairie","dry prairie"}),"The prairie contains " +
        "vegetation adapted to dry conditions.\n");
    AI("vegetation","Among most of the vegetation is a useful " +
        "herb or two.\n");
    AI(({"hills","foothills","surrounding foothills"}),"The " +
        "surrounding foothills look down upon the valley " +
        "in silent vigil.\n");

   OUTSIDE;
   
   seteuid(getuid(TO));
   set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
       ONE_OF(herbs) }), ({ "vegetation", }), 3);

   set_tell_time(400);
   add_tell("A soft breeze flows across the prairie.\n");
   add_tell("In the distance, a coyote yelps.\n");
   add_tell("An insect buzzes by, then out of sight.\n");
   add_tell("A cloud skims by overhead.\n");
   add_tell("A hissing sound can be heard nearby.\n");

   create_valley();
   reset_tant_room();
   
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
 
    if (interactive(ob))
    start_room_tells();
}


