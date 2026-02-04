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
             "The tunnel descends sharply to the east. There is a distinct "+
             "chill in the air. "+
             "Above you is a wooden trap door leading out of the tunnels.\n");

    add_item(({"trap door"}),"The wooden trap door looks like " +
               "it can be pushed in order to leave the tunnel.\n");

    DARK;
    
    add_exit(DEFAULT + "tunnel_n02", "east");

    add_cmd_item(({"door","trapdoor","trap door"}),
                  ({"push","open"}),"@@trapdoor");

    reset_room();
}

public mixed
trapdoor()
{
    write("With a huge heave, you push open the trapdoor above you "+
        "and climb through it into a cold and blinding whiteness.\n");
    say(QCTNAME(TP) + " pushes open a trapdoor in the ceiling, then " +
       "climbs through. The trapdoor closes behind " + HIM_HER + 
       "leaving behind a fair amount of snow.\n");
       TP->move_living("M","/d/Terel/silver/road/road02",1,0);
        return 1;
}




