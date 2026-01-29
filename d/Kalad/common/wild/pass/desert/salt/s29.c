/* by Antharanos */
#include "/d/Kalad/defs.h"
#include <macros.h>
#include <filter_funs.h>
#include <ss_types.h>

#define KALAD_FOUND_SALT_EXIT "_kalad_found_salt_exit"

inherit "/d/Kalad/std/room";

object ob1;

public void
create_kalad_room()
{
    add_prop(ROOM_NO_TIME_DESC,1);
    set_short("On the salt flat");
    set_long("The flat, empty landscape of the Great Salt Flat spreads "+
      "out before you, stretching to the distant horizon. The ground below "+
      "is smothered by a thick layer of salt crystals, which blindingly "+
      "reflect the harsh light of the Kaladian sun. Nothing grows here, for "+
      "this place is truly a wasteland.\n");
    add_item(({"flat landscape","empty landscape","landscape","great salt flat","great flat","salt flat","flat"}),
      "A burning hot wasteland within the greater wasteland of the Great Kalad "+
      "Waste.\n");
    add_item(({"distant horizon","horizon"}),"A thin line far in the distance.\n");
    add_item(({"ground"}),"Littering the ground are hundreds upon "+
      "hundreds of salt crystals, glinting in the harsh light.\n");
    add_item(({"thick layer","layer","salt crystals","salt crystal","crystals","crystal"}),
      "The formations of salt cover the ground in every direction you "+
      "look. Perhaps centuries ago, this was the site of a lake or other body "+
      "of water. Now however, it is nothing but a wasteland.\n");
    add_item(({"kaladian sun","sun"}),
      "As you gaze up at it, you are nearly blinded by its brilliance!\n");
    add_prop(OBJ_S_SEARCH_FUN,"search_ground");
    add_exit(CPASS(desert/salt/s28),"west",0,4);
    add_exit(CPASS(desert/salt/s35),"north",0,4);
    add_exit(CPASS(desert/salt/s30),"east",0,4);
    add_exit(CPASS(desert/salt/s20),"south",0,4);
    add_exit(CPASS(desert/salt/l1), "down", "@@exit_down", 1, 1);
    set_alarm(1.0,0.0,"reset_room");
}

int
exit_down()
{
    object *witnesses;
    if (TP->query_prop(KALAD_FOUND_SALT_EXIT))
    {
        witnesses = filter(FILTER_CAN_SEE_IN_ROOM(AINV(E(TP)) - ({TP})),
                TP->check_seen);
        foreach (object witness: witnesses)
        {
            if (!witness->query_prop(KALAD_FOUND_SALT_EXIT))
            {
                witness->add_prop(KALAD_FOUND_SALT_EXIT, 1);
                witness->catch_msg(QCTNAME(TP) + 
                    " uses a passage hidden in the salt crystals!\n");
            }
        }
        return 0;
    }
    write("There is no obvious exit down.\n");
    return 1;
}

public string
search_ground(object me, string arg)
{
    if(arg != "ground")
	    return "";
    if(TP->query_skill(SS_AWARENESS) < 30)
	    return "";
    TP->add_prop(KALAD_FOUND_SALT_EXIT, 1);
    return "After carefully searching through the salt crystals, you "+
    "discover a way down!\n";
}

reset_room()
{
    if(!ob1)
    {
        ob1 = clone_object("/d/Kalad/common/wild/pass/npc/s_snake");
        ob1 -> move_living("M",TO);
        tell_room(TO,"A salt snake burrows out of some salt crystals.\n");
    }
}
