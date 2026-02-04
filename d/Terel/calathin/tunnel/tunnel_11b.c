/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * tunnel_11b.c
 * Calathin Escape Tunnel
 * Tomas  -- July 2000
 */

#include "/d/Terel/include/Terel.h"

inherit CALATHIN_DIR + "tunnel/tunnel_base";

#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <cmdparse.h>
#include <composite.h>
#include <filter_funs.h>

#define  DEFAULT   CALATHIN_DIR + "tunnel/"
#define PEEPHOLE    CALATHIN_DIR + "inns/inn_main"
#define COUPE   ({ CALATHIN_DIR + "farms/farm2h" })

string trapdoor();


/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_short(query_short());
    set_long(query_long() +
	     "The path ends here returning to the west. A trap door " +
           "is above you. You notice a small hole in the middle of " +
           "trap door.\n");

    add_item(({"southwest wall","wall"}),"The wooden trap door looks like " +
               "it can be pushed in order to leave the tunnel.\n");

    
    add_exit(DEFAULT + "tunnel_11a", "west");

    add_cmd_item(({"door","trapdoor","trap door"}),
                  ({"push","open"}),"@@trapdoor");

    add_cmd_item(({"peephole","peep","hole"}),({"use"}),
                   "@@exa_coupe");
    add_item(({"peephole","peep","hole"}),
                   "@@exa_coupe");


    reset_room();
}

public mixed
trapdoor()
{
/* Removed per AoB and AoD, Clubs should not have access to extensive hidden areas.
   Made accessible to all players who can find it. Lilith May 2008

    object ring;
    ring = TP->query_prop("_live_i_am_explorer");

    if(!ring) 
    {
        write("You cant find any way to open the trap door!\n");
        return 0;
    }
*/
    write("You push open the trapdoor above you and climb through it.\n");
    say(QCTNAME(TP) + " pushes open a trapdoor in the ceiling, then " +
       "climbs through. The trapdoor closes behind " + HIM_HER + ".\n");

    tell_room(CALATHIN_DIR + "farms/farm2h", QCTNAME(TP) + 
       " climbs through a trapdoor in the floor. Then closes it behind " +
       HIM_HER +".\n");
        TP->move_living("M",CALATHIN_DIR + "farms/farm2h",1,0);
        return 1;
}


public string
exa_coupe()
{
  object *inv, *live, room;
  int i;

  inv = ({});
  for (i = 0; i < sizeof(COUPE); i++)
    if ((room = find_object(COUPE[i])))
      inv += all_inventory(room);

  if (sizeof(inv)) {
    live = FILTER_LIVE(inv);
    live = FILTER_CAN_SEE(live, TP);
    if (sizeof(live))
      return "Peering through the peephole you see " +
        COMPOSITE_LIVE(live) + " standing in a chicken coop.\n";
  }
  return "  The chicken coop outside looks empty save for some chickens.\n";
}



