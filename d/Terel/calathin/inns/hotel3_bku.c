/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * hotel3.c
 *
 * A hotel room.
 */

#include "/d/Terel/include/Terel.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <cmdparse.h>
#include <composite.h>
#include <filter_funs.h>

inherit CALATHIN_DIR + "inns/hotel_room";
int start_here(string str);
public string sign_info();

#define PEEPHOLE    CALATHIN_DIR + "inns/inn_main"
#define LOBBY   ({ CALATHIN_DIR + "inns/inn_main" })

object chest;
string trapdoor;

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_short("Lodging room");
  
    add_item(({"peephole","hole"}),"A small hole has been drilled " +
       "into the door to allow you to view the lobby. You might " +
      "try: <use peephole> here.\n");
    add_item(({"floor","trapdoor"}),"You see the square outline of a " + 
       "trap door in the floor.\n");

    add_cmd_item(({"here"}),({"begin","start"}),start_here);
    add_cmd_item(({"sign"}),({"read"}),sign_info);
    add_cmd_item(({"door","trapdoor","trap door"}),
                  ({"lift","open"}),"@@trapdoor");
   add_cmd_item(({"peephole","peep","hole"}),(({"use"})),
                   "@@exa_lobby");


    chest = clone_object(CALATHIN_DIR + "inns/chest");
       chest->move(TO);



    add_exit(CALATHIN_DIR + "inns/inn_main", "west", 0);
}
query_prevent_snoop() { return 1;}


int
start_here(string str)
{
   
        TP->set_default_start_location(CALATHIN_DIR + "inns/hotel3");
        TP->catch_msg("You shall now begin each day anew in the comfort of our room.\n");
   
      return 1;
}


/*
 * Function name: sign_info
 * Description:   returns what is written on the sign
 * Returns:       see above
 */
public string
sign_info()
{
    return "The sign reads:\n" + 
        "Type 'start here' and you will make this room your " +
            "permanent starting location next time you login.\n";
}


public string
exa_lobby()
{
  object *inv, *live, room;
  int i;

  inv = ({});
  for (i = 0; i < sizeof(LOBBY); i++)
    if ((room = find_object(LOBBY[i])))
      inv += all_inventory(room);

  if (sizeof(inv)) {
    live = FILTER_LIVE(inv);
    live = FILTER_CAN_SEE(live, TP);
    if (sizeof(live))
      return "  peering through the peephole you see " +
        COMPOSITE_LIVE(live) + " standing there.\n";
  }
  return "  The lobby outside, looks barren.\n";
}


public mixed
trapdoor()
{

    object ring;
    ring = TP->query_prop("_live_i_am_explorer");

    if(!ring) 
    {
        write("You cant find any way to open the trap door!\n");
        return 1;
    }

    write("You push open the trapdoor below you and climb through it.\n");
    say(QCTNAME(TP) + " lifts open a trapdoor in the floor, then " +
       "climbs through. The trapdoor closes behind " + HIM_HER + ".\n");

    tell_room(CALATHIN_DIR + "tunnel/tunnel_01", QCTNAME(TP) + 
       " climbs through a trapdoor in the floor. Then closes it behind " +
       HIM_HER +".\n");
        TP->move_living("M",CALATHIN_DIR + "tunnel/tunnel_01",1,0);
        return 1;
}
