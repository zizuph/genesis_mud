/* forest25.c
 * Somewhere in the Qualinesti forest.
 *
 * Blizzard, 01/2003 
 *
 * Modified by Vitwitch, to allow
 * archer access to new guild rooms (High Vantage)
 * Dec 2020
 */

#include "/d/Krynn/common/defs.h"
#include <macros.h>
#include "../local.h"
#define GUILD_ENTR "/d/Krynn/guilds/elven_archers/rooms2/fort_eastentr"

inherit FORESTBASE;
object animal, animal2;

void
reset_qualinesti_room()
{

    if ( !animal )
    {
        animal = random_animal();
        animal->move(TO, 1);
    }
    if ( !animal2 )
    {
        animal2 = random_animal();
        animal2->move(TO, 1);
    }
}

void
create_forest()
{
    add_my_desc("\n");
    
    OUTSIDE;

    add_item(({"oak tree", "large tree"}), "There is a large oak tree here.\n");
    
    add_exit(FDIR + "forest23.c", "northwest", 0, 2);
    add_exit(FDIR + "forest24.c", "north", 0, 2);
    add_exit(FDIR + "forest54.c", "southwest", 0, 2);
    add_exit(FDIR + "path14.c", "west", 0, 2);
    add_exit(FDIR + "nentrance.c", "south", 0, 2);
    add_exit("/d/Krynn/pax/road/road3", "southeast", 0, 2);
    add_exit("/d/Krynn/pax/road/road4", "east", 0, 2);
        
    reset_qualinesti_room();
}

/**
 * The function that lets the player climb down to the ground
 */
int climb_up(string args)
{
    if(!args)
    {
        notify_fail("Climb what?\n");
        return 0;
    }

    if(!(TP->query_guild_name_occ() == "Ansalon Elvish Archers") &&
       !(TP->query_guild_name_lay() == "Ansalon Elvish Archers"))
    {
        notify_fail("Climb what?\n");
        return 0;
    }
    
    if(args != "large tree" && args != "oak tree")
    {
        notify_fail("Climb what? The oak tree?\n");
        return 0;
    }
    TP->catch_tell("You climb up the tree.\n");
    tell_room(environment(TP), QCTNAME(TP)+" climbs up a tree.\n", TP);
    TP->move_living("M", GUILD_ENTR, 1, 0);
    return 1;
}


void
remind(object player)
{
    player->catch_tell("You remember that you can <climb oak tree> " +
                       "or <climb large tree> here to get home.\n");
}

public void init()
{
  add_action(climb_up, "climb");
  // We purposedly do the ::init last, as we have new actions here
  // that would be shadowed by the other, but we don't shadow that one.
  ::init();

  if((TP->query_guild_name_occ() == "Ansalon Elvish Archers") ||
     (TP->query_guild_name_lay() == "Ansalon Elvish Archers"))
  {
      set_alarm(0.0, 0.0, &remind(TP));
  }
}

