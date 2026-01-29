// file name:        port17.c
// creator(s):       Ilyian
// revision history: Boriska Aug 95: Added sailor NPC
//		     Cirion, May'96: Added logging diving to statserv.
//		     Denis, May'96:  Corrected the wrongness which happens when
//				     one writes just 'dive' wo arguments.
//		     Denis, Sep'96:  Changes due to the port inheritance recode.
//           Lilith, Sep 2021: Added fishing prop.
// purpose:
// note:
// bug(s):
// to-do:

# pragma strict_types
# include "/d/Avenir/common/port/port.h"
#include "/d/Avenir/common/port/bury_bones.h"
# include "/d/Avenir/smis/sys/statserv.h"
inherit PORT_ROOM_SILENT;

static void
create_port_room()
{
    add_prop(ROOM_I_TYPE, ROOM_BEACH);
	add_prop("_live_i_can_fish", "saltwater");
	
    set_short("Northern ledge in Sybarus Port cavern");
    set_long("The ledge narrows here, making any further " +
             "travel to the west impossible. You stand against the " +
             "northern cavern wall, while the waves of the lake to " +
             "the south splash about. The winds here have diminished " +
             "the mist enough to see the great rift to the outside " +
             "world in the western wall of the cavern. The water that " +
             "roars through is almost unbearably loud, and with it " +
             "comes wind so strong that your precarious footing " +
             "is threatened.\n");

    IN
    LIGHT
    add_exit("port16", "southeast");

    add_wall_item();
    add_rift_item();
    add_ceiling_in_item();

    add_tell("The roar from the great rift increases to a thunderous " +
             "climax, and then receeds again.\n");
}

int
climb(string str)
{
    if (!strlen(str))
        return 0;

    notify_fail("Climb where?\n");
    if (!parse_command(str, ({}), "[down] [the] 'ledge'"))
        return 0;

    write("The ledge is too slippery.\n" +
          "You would need to jump or dive down.\n");
    return 1;
}

int
dive(string str)
{
    object sailor2;
 
    notify_fail(CAP(QVB)+" where?\n");
    if(!strlen(str) ||
       !parse_command(str, ({}), "[off] / [into] / [in] 'down' / 'ledge' / 'water' / 'off'"))
    {
       return 0;
    }

    sailor2 = (present("sailor2", TO));
    if (sailor2)
    {
        if (!(TP->query_prop("warned")))
        {
            sailor2->warn_player(TP);
            return 1;
        }
    }
    notify_fail("It is too far down. You don't dare.\n");
    if(TP->query_stat(SS_DIS) < 50)
       return 0;

    say(QCTNAME(TP) + " " + QVB +
	"s off the ledge into the water far below!\n");
    write("You " + QVB + " off the ledge into the water below.\n" +
	  "You hit the water with a splash.\n");
    TP->move_living("M", PORT + "water2");
    STATSERV_LOG_EVENT("port", "Dove into the water");
    return 1;
}

public void
init()
{
    ::init();
    add_action(climb, "climb");
    add_action(dive, "dive");
    add_action(dive, "jump");
    add_action(dive, "leap");
}

