/* Forest base file for Tantallon.
* By Teth, Jan 17 , 1996
*/

#include "../local.h"

inherit OUTROOM; 
inherit HERBSEARCHNEW

#include RND_MEET

string *herbs = HERB_MASTER->query_herbs( ({ "mixedforest", }) );

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
    monster = RANDOM_MEET("/d/Krynn/common/rndtables/tbltantforest");
    monster->move(TO);
    }
}

public void
create_forest()
{ 
}

nomask void
create_tant_room()
{
   set_place(FOREST);
   set_long_desc("The forest surrounds you, cloistering you from the " +
       "outside world. Animal paths run helter-skelter throughout the " +
       "forest.");
   AI("forest","You are in the forest, complete with trees.\n");
   AI("trees","The trees are diverse, some are coniferous while others " +
       "others are deciduous.\n");
   AI(({"conifers","coniferous trees","coniferous tree"}),"The coniferous " +
       "trees have sharp needle-like leaves.\n");
   AI(({"deciduous trees","deciduous tree"}),"The deciduous trees have " +
       "broad leaves, usually.\n");
   AI(({"paths","animal paths"}),"The animal paths lead here and there " +
       "throughout the forest.\n");
   AI("owl","The owl must be hidden here somewhere!\n");

   OUTSIDE;
   
   seteuid(getuid(TO));
   set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
       ONE_OF(herbs) }), ({ "forest", }), 3);

   set_tell_time(400);
   add_tell("You can hear a slight rustle nearby.\n");
   add_tell("WHOO-Hoo-HOO! utters a nearby owl.\n");
   add_tell("A partridge erupts from the forest floor in front of you! " +
       "It flies off into the distance, with a WHIRR of wingflaps.\n");
   add_tell("A vole skitters by, and quickly goes out of sight.\n");
   add_tell("Something moves behind you!\n");

   create_forest();
   reset_tant_room();
   
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
 
    if (interactive(ob))
    start_room_tells();
}

