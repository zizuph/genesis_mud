/*
 * Resting Room for Noldor Guild
 * By Finwe, August 2000
 */
 
#include "/d/Shire/sys/defs.h"
#include "noldor.h"
#include <std.h>
 
inherit BUILDING_BASE;
inherit "/d/Gondor/open/room_chairs/room_chairs";

#include "/d/Gondor/open/room_chairs/room_chairs.h"
#define BENCH_CHAIR	"large wooden bench"
#define WOOD1_CHAIR     "large wooden chair"

public string	look_at(string arg);	/* VBFC for chairs */
public void	leave_inv(object ob, object dest);
public string	look_at(string arg);	/* VBFC for chairs */

void create_guild_room()
{
    set_short("A room of resting");
    set_long("This is a room or resting where elves come to " +
        "relax quietly, discuss quietly among themselves, or to " +
        "simply enjoy a quiet moment to themselves. Some chairs " +
        "and benches are strategically placed about the room and some " +
        "windows on the walls let in some @@daylight_desc@@. " +
        "Free standing lamps fill the room with muted light.\n");

  
    set_extra_wall("Large windows are set in the north wall and " +
        "the eastern wall. They let in lots of @@daylight_desc@@.\n");
    set_extra_window("The windows are set into the north wall.");

    add_item(({"north window", "northern window"}),
         "The valley spreads to the north and up to the mountains.\n");
    add_item(({"east window", "eastern window"}),
         "The valley spreads to the east and up to the mountains.\n");

   add_chair(BENCH_CHAIR,
	          "[down] [on] / [in] [the] [wooden] 'bench'", 4);
    add_item( ({ "bench"}), &look_at(BENCH_CHAIR) );

    add_chair(WOOD1_CHAIR,
	          "[down] [on] / [in] [the] [large] 'chair'", 1);
    add_item( ({ "chair", }), &look_at(WOOD1_CHAIR) );
  
    add_exit(NOLGLD_DIR + "rack_rm", "north");
    add_exit(NOLGLD_DIR + "start_rm", "south");
    add_exit(NOLGLD_DIR + "board_rm", "west");

}

void
init()
{
    ::init();
    init_room_chairs();	/* add chair verbs */

}

public void
leave_inv(object ob, object dest)
{
    ::leave_inv(ob, dest);
    leave_inv_room_chairs(ob, dest);
} /* leave_inv */


/*
 * Function name:	look_at
 * Description	:	VBFC to describe chair/sofa + occupants
 * Arguments	:	string arg -- what's being looked at
 *				      null str -> it's the room
 * Returns	:	string -- the description
 */
public string
look_at(string arg)
{
    /* ok, the descs are a little lame, but you get the idea ... */
    switch ( arg )
    {
    case BENCH_CHAIR:
    case BENCH_CHAIR:
	return "This large wooden bench is made of wide " +
        "slats of oak. It has arm rests on both ends and the " +
        "back is rounded slightly. The back is made of vertical " +
        "slats. The bench looks like it will hold a couple of " +
        "elves comfortably.\n"+
	sitting_on_chair(BENCH_CHAIR, this_player(), 0);
    break;

    case WOOD1_CHAIR:
       return "The large chair is comfortable looking. It is " +
        "made of wide slats of oak. It has arm rests on both " +
        "ends and the back is rounded slightly. The back is " +
        "made of vertical slats and looks like it will seat " +
        "one elf comfortably.\n"+
	sitting_on_chair(WOOD1_CHAIR, this_player(), 0);
    break;


    }
} /* look_at */
