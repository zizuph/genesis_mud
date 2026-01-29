/*
 *	/d/Gondor/pelargir/docks/shipmastr.c
 *
 *	Modification log:
 *	12-Feb-1997, Olorin:	Added the sign.
 *  31-May-2009, Tapakah: Added the timetable, edited the sign.
 */
#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

static object  HMaster;

public int	test_blocked();

private string
read_sign()
{
    return "\n" + 
	"\t/======================================================/|\n" +
	"\t|                                                      ||\n" +
	"\t|  Destination   Captain                        Price  ||\n" +
	"\t|  ~~~~~~~~~~~   ~~~~~~~                        ~~~~~  ||\n" +
	"\t|  Circle Line   Grosso the Strong              Free   ||\n" +
	"\t|  Harlond       Hothronduin the River Captain  20 cc  ||\n" +
	"\t|  Solace(N)     Earendil the Mariner           30 cc  ||\n" +
	"\t|  Sparkle       Dirhavel the Seafarer          30 cc  ||\n" +
	"\t|  Gelan-Kalaman Sardon the Sailor               1 gc  ||\n" +
	"\t|                                                      ||\n" +
	"\t\\======================================================\\|\n" +
	"\n";
}

public void
reset_room()
{
    HMaster = clone_npc(HMaster, PELAR_DIR + "npc/hmaster");
}

public void
create_gondor()
{
  object timetable;
  set_short("the office of the Harbour Master");
    set_long(BSN("This is the office of the Harbour Master of "
      + "Pelargir. The room seems to be intended to look like a "
      + "captain's cabin. On the wall are some charts and maps, "
      + "and a large sign. The window is even shaped to look "
      + "like a ship's porthole. In front of the window is a "
      + "desk. A doorway is leading out to the east."));

    add_prop(ROOM_I_INSIDE,1);

    add_item("desk","This desk is old and cluttered with maps of oceans.\n");
    add_item(({"charts","maps"}), BSN("These are mostly odd maps and "
      + "charts of stars and sea. How these sailors ever get anywhere "
      + "using these is beyond you."));
    add_item(({"porthole","window"}), BSN("Through it you can look out "
      + "past the docks to the great river Anduin."));
    add_item(({"dock", "docks", }), "The docks are outside.\n");
    add_item(({"river", "river anduin", "anduin", }), BSN(
        "From here, all you can see of the Anduin is the bay in which "
      + "the harbour of Pelargir is situated. Docks line the bank as "
      + "far as you can see."));
    add_item( ({ "sign", "plaque", }), read_sign());
    add_cmd_item( ({ "sign", "plaque", }), "read", read_sign());

    add_exit(PELAR_DIR + "streets/shipwright03", "east", test_blocked);
    timetable = clone_object("/d/Khalakhor/inisi/roke/nyreese/gs_office/timetable");
    timetable->set_timetable_domain("Pelargir");
    timetable->move(TO);
    timetable->set_no_show_composite(0);

    reset_room();
}




/*
 * Function name:	test_blocked
 * Description	:	block exit if player is fighting carastur or
 *			guards
 */
public int
test_blocked()
{
    object attacker = TP->query_attack();
    if (objectp(attacker) &&
	attacker->id("_Pelargir_soldier"))
    {
        TP->catch_msg(QCTNAME(attacker) + " blocks your way out!\n");
        return 1;
    }
    return 0;
} /* test_blocked */
