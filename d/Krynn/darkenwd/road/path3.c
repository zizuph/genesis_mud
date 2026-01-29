/* Path3 coded by Teth
 * April 2, 1996
 * last updated Oct 26, 1996
 */

#include "local.h"

inherit ROADOUT;

inherit HERBSEARCHNEW

string *herbs = HERB_MASTER->query_herbs( ({ "mixedforest", }) );
object snake;

void
reset_darkenwd_room()
{
    set_searched(random(2));

    if(!objectp(snake))
    {
      snake = clone_object("/d/Krynn/tant/npc/snake");
      snake->move(TO);
    }
}

void
create_darkenwd_room()
{
    set_place(PATH);

    set_long_desc("This narrow path runs between the shores of Crystalmir " +
                  "Lake and the road between Solace and Haven. Due to the "+
                  "undergrowth here, movement is quite tiring. Forest "+
                  "surrounds you on all sides now. The path extends both "+
                  "to the northeast and to the south. A mound of dirt seems "+
                  "recently made along the side of the path. An opening in "+
                  "the forest leaves east.");
    AI(({"path","narrow path","trail","game trail"}),"The path is an old "+
        "game trail. However, it is now covered with tangleshoot vines and "+
        "poison ivy, and movement is difficult.\n");
    AI("opening","It seems like someone has cleared it.\n");
    AI(({"undergrowth","poison ivy","tangleshoot","ivy","vines",
        "tangleshoot vines"}),"These plants cover the path, hinting that "+
        "this trail has not been used for a long time.\n");
    AI("forest","The forest is thick, letting little light penetrate the "+
        "forest floor.\n");
    AI(({"forest floor","floor"}),"It is covered with thick vegetation, "+
        "struggling for light.\n");
    AI(({"mound of dirt","dirt","mound"}),"This mound of dirt seems freshly "+
        "made. It may be the home of a packrat gopher.\n");
    add_search(({"mound of dirt","dirt","mound"}),4,
        KROBJECT + "t_silver_spoon",-1);

    add_exit(TDIR + "path2", "northeast",0,4,1);
    add_exit(TDIR + "forest12", "east",0,4,1);
    add_exit(TDIR + "forest3", "south",0,4,1);
   
    set_tell_time(120);
    add_tell("A rustling sound can be heard in the forest to the "+
             "south.\n");
    add_tell("An extremely fragile breeze touches your face.\n");
    add_tell("Sounds seem to deaden within a few metres of you.\n");
    
    seteuid(getuid(TO));
    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
        ONE_OF(herbs) }), ({"forest","herbs","undergrowth","path",
        "trail",}), 7);
       OUTSIDE;  /* An outside room */

    reset_darkenwd_room();   
}

void
enter_inv (object ob, object from)
{
  ::enter_inv(ob, from);
 
  if (interactive(ob))
    start_room_tells();
}




