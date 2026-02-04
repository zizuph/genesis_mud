/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * tunnel_01.c
 * Calathin Escape Tunnel
 * Tomas  -- July 2000
 */

#include "/d/Terel/include/Terel.h"

inherit CALATHIN_DIR + "tunnel/tunnel_base";

#define  DEFAULT   CALATHIN_DIR + "tunnel/"

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
           "Two tunnels join here, one descending slightly to the northeast, " +
           "and the other shooting straight south. "+
           "Above you is a wooden trapdoor leading out of the tunnels.\n");

    add_item(({"ceiling","trap door", "trapdoor"}),"The wooden trap door looks like " +
               "it can be pushed up order to leave the tunnel.\n");

    DARK;
    
    add_exit(DEFAULT + "tunnel_02", "northeast");
    add_exit(DEFAULT + "tunnel_s02", "south");

    add_cmd_item(({"door","trapdoor","trap door"}),
                  ({"push","open", "push up", "climb"}),"@@trapdoor");

    reset_room();
}

public mixed
trapdoor()
{
/* Per AOD and AOB, Clubs cannot have extensive hidden areas for their
   exclusive use. Removed by Lilith May 2008, made accessible to all 
   players who can find it.


    object ring;
    ring = TP->query_prop("_live_i_am_explorer");

    if(!ring) 
    {
        write("You cant find any way to open the trap door!\n");
        return 1;
    }

    write("You push open the trapdoor above you and climb through it.\n");
    say(QCTNAME(TP) + " pushes open a trapdoor in the ceiling, then " +
       "climbs through. The trapdoor closes behind " + HIM_HER + ".\n");

    tell_room(CALATHIN_DIR + "inns/hotel3", QCTNAME(TP) + 
       " climbs through a trapdoor in the floor. Then closes it behind " +
       HIM_HER +".\n");
        TP->move_living("M",CALATHIN_DIR + "inns/hotel3",1,0);
        return 1;
*/
    write("You push up on the trapdoor above you and climb through it.\n");
    say(QCTNAME(TP) + " pushes open a trapdoor in the ceiling, then " +
       "climbs through. The trapdoor closes behind " + HIM_HER + ".\n");

    tell_room(CALATHIN_DIR + "inns/hotel3", QCTNAME(TP) + 
       " climbs through a trapdoor in the floor. Then closes it behind " +
       HIM_HER +".\n");
    TP->move_living("M",CALATHIN_DIR + "inns/inn_main",1,0);
        return 1;
}




