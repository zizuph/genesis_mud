/* created by Aridor 06/21/93
 * adapted by Grace  05/31/94
 *   Knight Spur Entrance     */

#include "../local.h"
inherit SPURRM;
#define VKEEPGUARD "/d/Krynn/solamn/vkeep/mnstrs/guard.c" 

object guard1, guard2; 
void reset_spur_room();	/*prototype added by Lord Majere 8/24/95 */

void
area_conquered(string newarmy, string oldarmy)
{
    object key = clone_object("/std/key");

    key->set_key(237849);
    if (key->move(guard1))
      key->move(guard2);

    if (newarmy == "Knights" ||	newarmy == "Free People")
    {
	guard1->command("unlock doors");
	guard2->command("unlock doors");
	guard1->command("open doors");
	guard2->command("open doors");
    }
    else
    {
	guard1->command("close doors");
	guard2->command("close doors");
	//guard1->command("lock doors");
	//guard2->command("lock doors");
    }
    key->remove_object();
}

void
create_spur_room()
{
    set_short("Outside the entrance to the Knights' Spur");
    set_long("You are just outside the huge steel doors opening "
      +   "into the Knights' Spur on the east side of Westgate Pass. "
      +   "The deserted and closed High Clerist Tower lies directly "
      +   "west across a small stream which pours from the aqueduct "
      +   "running under the Spur. Towards the southeast the Plains "
      +   "of Solamnia stretch out to meet the horizon. "
      +   "The Vingaard Mountains extend to the "
      +   "northeast and south, with the battlements of the Tower and "
      +   "the Spur guarding the entrance to a valley.\n");

    OUTSIDE;

    add_exit(SPLAINS,"southeast",0);
    clone_object(SOBJ + "steeldooro")->move(TO);  

    add_item(({"tower","fortress", "high clerist tower"}), "You look up "
      +   "to the tower but you can barely make out its top. "
      +   "The base of the tower is really a solid fortress, "
      +   "like a silent guardian watching its surroundings.\n");
    add_item("plains", "These plains are vast! You cannot see anything "
      +   "else but plains all the way to the east and south. It seems "
      +   "that brownish grass grows everywhere, making patterns as the "
      +   "wind touches it.\n");
    add_item(({"mountains", "pass"}), "The mountains look fierce and  "
      +   "impassible except for the place where the fortress was built "
      +   "here to guard the only pass through the mountains.\n");
    add_item(({"spur","knight spur","knights spur","knights' spur","wall"}),
      "This wall rises twenty man-lengths above you, the same "
      +   "height as the curtain wall of the High Clerist Tower. "
      +   "You can see very little past the battlements.\n");    
    add_item(({"curtain wall", "curtain"}), "This wall is the height "
      +   "of 20 men and level with the wall of the Knight Spur. "
      +   "The Tower rises impossibly high above the battlements.\n");
    add_item(({"battlement", "battlements", "fortification", "parapets"}),
      "The parapets of this fortification have regularly spaced "
      +   "merlons and crenels interrupting their walls.\n");
    add_item(({"stream", "aquaduct"}),
      "The aquaduct acts as a conduit for funneling the water of "  
      +   "the stream through the center of the Knights Spur "
      +   "and out onto the plains.\n");
    add_cmd_item(({"stream", "aquaduct"}),({"enter", "swim", "cross"}),
      "The water flows too quickly for you to do that here.\n");

    reset_spur_room();

    set_alarm(0.0,0.0,&area_conquered(ARMYMASTER->army_in_area("Western Solamnian Plains"),"Knights"));
}

void
reset_spur_room()
{
    if (!guard1)
	(guard1 = clone_object(SNPC + "guard"))->move(TO);
    if (!guard2)
	(guard2 = clone_object(SNPC + "guard"))->move(TO);
}


