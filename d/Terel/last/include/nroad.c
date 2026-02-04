/* This comment tells emacs to use c++-mode -*- C++ -*- */
// Northern road leading from last/lroad09.c 
// Tomas  -- April 2000

#include "/d/Terel/include/Terel.h"
#include <ss_types.h>
#include <cmdparse.h>
#include <composite.h>
#include <macros.h>

inherit STDROOM;
inherit "/d/Terel/std/room_tell.c";

#include <stdproperties.h>

#define DEFAULT    LAST_DIR + "include/nroad/"

object pebble;

init()
{
    ::init();
    add_action("do_smell",  "smell",  0);
    start_room_tells();
}


public string
smell_desc()
{
    return "The air smells of dried grass and sea water.\n";
}


/*
 * Function name: do_smell
 * Description:   Handle the smell action
 * Returns:       1/0
 */ 
public int
do_smell(string str)
{
    NF("Smell what?\n");
    if (!strlen(str))
        return 0;
    
    if (str == "air" || str == "scent" || str == "strange scent") {
        write(smell_desc());
        return 1;
    }
    return 0;
}


public void
create_room()
{
    ::create_room();
    set_short("Dirt road");
    set_long("The dirt road continues northward through a large mist covered " +
       "field of wild grass. To the west, you can barely make out jagged " +
       "peaks of a large mountain range. The dense mist and fog impedes " +
       "your view of the east. However, you sense that the ocean isn't " +
       "far off in that direction. ");


    add_item(({"mountains","range","mountain range","peak","peaks"}),
       "You can just barely make out the tips of a jagged " +
       "mountain range through the mist to the west.\n");

    add_item(({"dirt road","road"}),
       "The dirt road appears to be well trafficked. Deep " +
       "ruts from wagon wheels and horse hoof prints mark " +
       "the road. The road is also devoid of any heavy " +
       "snow fall.\n");

    add_item(({"marks","ruts","ground","hoof prints","prints"}),
       "The road seems have been travelled quite frequently.\n");

    add_item(({"grass","dried grass","yellow grass","wild grass"}),
       "The wavering wild grass stands about two feet. Dried " +
       "from the bitter cold it looks quite brittle.\n");

    add_item(({"fog","mist"}),"The low laying fog blankets " +
       "everything around you.\n");

    set_tell_time(300 + random(200));
    add_tell("You hear the distant roar of waves crashing against " +
      "the rocks to the east.\n");
    add_tell("The wind whips over the grassy fields creating a " +
      "hollow, empty sound..\n");

    add_cmd_item(({"rocks","rock","pebble","pebbles"}),
                 ({"collect","gather","get"}),"@@get_pebble");
    
  
    reset_room();

}


get_pebble()
{
    object pebble;

    seteuid(getuid(TO));
    pebble = clone_object(CALATHIN_DIR + "houses/obj/pebble");
    pebble->move(TP);
    write("You pickup a pebble from the ground.\n");
       say(QCTNAME(TP) + " reaches down and picks up a pebble.\n");
    return 1;
}

