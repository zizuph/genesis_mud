// file name:        port18.c
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
# include "/d/Avenir/smis/sys/statserv.h"
inherit PORT_ROOM_SILENT;
inherit "/d/Avenir/inherit/sair_wall";
object wall;

static void
create_port_room()
{
	add_prop("_live_i_can_fish", "saltwater");
    add_prop(ROOM_I_TYPE, ROOM_BEACH);

    set_short("Rift in the carvern wall");
    set_long("You huddle in a hollow in the rift wall in a crevice just "+
			 "beyond the ledge. It is very dim in here but you can "+
			 "see the Great Rift to the outside world through the gap "+
			 "in the rift wall. The water that roars past is terribly "+
			 "loud, and with it comes wind so strong that it buffets you "+
			 "backwards into jagged rocks. Your options are very limited "+
			 "here.\n");

    IN
    BLACK
    add_exit("port17", "southeast");

    add_wall_item();
    add_rift_item();
    add_ceiling_in_item();
    add_item("crevice", "It is an irregular crack that leads deep into "+
	   "the bowels of the mountain. It does not look passable.\n");
    add_tell("The roar from the great rift increases to a thunderous " +
             "climax, and then receeds again.\n");
	add_tell("The wind causes the mouth of the crevice moan eerily.\n");
	
    add_sair_wall();
    set_sair_dest(({DARK +"l1/grotto", DARK+"l2/add/t35", DEAD+"barrow/barrow15"}));
}

int
climb(string str)
{
    if (!strlen(str))
        return 0;

    notify_fail("Climb where?\n");
    if (!parse_command(str, ({}), "[up] [into] [the] 'crevice'"))
        return 0;

    write("It is too slippery and angled too sleeply.\n" +
          "You cannot climb up into the crevice.\n");
    return 1;
}

int
dive(string str)
{
 
    notify_fail(CAP(QVB)+" where?\n");
    if(!strlen(str) ||
       !parse_command(str, ({}), "[off] / [into] / [in] 'down' / 'ledge' / 'water' / 'off'"))
    {
       return 0;
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
    sair_init();
    add_action(climb, "climb");
    add_action(dive, "dive");
    add_action(dive, "jump");
    add_action(dive, "leap");
}

