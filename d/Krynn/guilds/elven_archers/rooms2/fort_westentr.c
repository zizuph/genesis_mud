/*
 * Room in the Archer Guild
 *
 * Navarre November 23th 2007.
 *
 * Vitwitch - updated November 2020
 * 
 */
    
#include <macros.h>
#include <composite.h>
#include <filter_funs.h>

#include "/d/Krynn/common/defs.h"
#include "../guild.h"

inherit "/d/Krynn/guilds/elven_archers/rooms2/baseroom_fort";
#define GUILDROOMS "/d/Krynn/guilds/elven_archers/rooms2/"
#define VIEWDEST "/d/Krynn/guilds/elven_archers/rooms2/joinroom"

void
reset_krynn_room()
{
}

void
create_krynn_room()
{

    set_short("An antechamber to a treetop fortress");    

    set_long(gBlurbPfx +
             " An elder oak dominates the antechamber allowing access to the ground. "+
             gBlurbSfx +
             " An opening to the southeast leads into the fortress proper.\n");

    add_item(({"oak", "elder oak", "big oak"}), "The broad trunk of an elder "+
          "oak stands right in the centre of this room. Climbing down it "+
          "will allow you to reach the ground. You can view the ground about "+
          "the base of the trunk before venturing down.\n");

    add_item(({"fort","fortress","treetop fortress"}),"@@fort_purpose");
    add_item(({"treetops","whispering treetops","branches"}),"@@fort_description");
    add_item(({"walls","wall"}),"@@fort_walls");
    add_item(({"stakes","stakes","strands","strand"}),"@@fort_stakes");
    add_item(({"loopholes","loophole","window","windows","ground","ground below"}),"@@fort_vantage");
    add_item(({"foliage"}),"@@fort_foliage");

    add_cmd_item(({"down", "ground", "loophole", "window"}), "view", "@@view_down");
    set_tell_time(250);
    add_tell("Branches creak and leaves flutter in the gently shifting treetops.\n");


    gViewFallDest = VIEWDEST;

    INSIDE

    add_exit(GUILDROOMS + "fort_reservoir", "southeast", 0);

    reset_room();
}


/**
 * The function that lets the player climb down to the ground
 */
int climb_down(string args)
{
    if(!args)
    {
        notify_fail("Climb what?\n");
        return 0;
    }

    if(args != "down" && args != "tree" && args != "elder tree" &&
       args != "big tree" && args != "oak" && args != "the oak" &&
       args != "elder oak" && args != "down the tree" &&
       args != "down the oak" && args != "the tree")
    {
        notify_fail("Climb what? Down?\n");
        return 0;
    }
   TP->catch_tell("You climb down the tree.\n");
   tell_room(environment(TP), QCTNAME(TP)+" climbs down the elder oak.\n", TP);
   TP->move_living("M", JOINROOM, 1, 0);
   return 1;
}


public void init()
{
  ::init();
  add_action(climb_down, "climb");
}

