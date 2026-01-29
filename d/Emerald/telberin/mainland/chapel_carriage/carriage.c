/*
 * EMERALD's MAIN CARRIAGE LINe
 * Alaron March 1997
 *
 * Updated to serve as temp transport to the chapel.  Do
 * not use this code for any other purpose.
 */

#include "/d/Emerald/defs.h"

inherit "/d/Emerald/std/carriage";

void
create_carriage()
{
    seteuid(getuid());
    set_deck("/d/Emerald/telberin/mainland/chapel_carriage/deck");
    
    set_places_to_go(({ "/d/Emerald/telberin/dock/ferry_dock",
                         CHAPEL_DIR   + "carriage_path",
                         CHAPEL_DIR   + "carriage_path",
                         CHAPEL_DIR   + "carriage_path",
                         CHAPEL_DIR   + "carriage_path",
                         CHAPEL_DIR   + "carriage_path",
                         CHAPEL_DIR   + "carriage_path",
                         CHAPEL_DIR   + "carriage_path",
                         CHAPEL_DIR   + "carriage_path",
                         CHAPEL_DIR   + "carriage_path",
                         CHAPEL_DIR   + "carriage_path",
                         CHAPEL_DIR   + "outside",
                         CHAPEL_DIR   + "carriage_path",
                         CHAPEL_DIR   + "carriage_path",
                         CHAPEL_DIR   + "carriage_path",
                         CHAPEL_DIR   + "carriage_path",
                         CHAPEL_DIR   + "carriage_path",
                         CHAPEL_DIR   + "carriage_path",
                         CHAPEL_DIR   + "carriage_path",
                         CHAPEL_DIR   + "carriage_path",
                         CHAPEL_DIR   + "carriage_path",
                         CHAPEL_DIR   + "carriage_path", }));

    set_time_between_stops(({ 45, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                              45, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, }));

    set_name("carriage");
    set_adj("emerald");
    
    set_short("gold-trimmed emerald carriage");
    set_long("   This horse-drawn carriage is in impeccable condition. The "+
	     "amazingly beautiful, emerald-green stain on the thick, heavy "+
	     "wood of the carriage is accented by the gold-painted, metal "+
	     "framing which covers all joints and corners on the entire "+
	     "carriage. It looks like it could hold quite a few people.\n\n");

    add_item(({"horse", "horses"}),
	     "They are the horses responsible for pulling the carriage. "+
	     "They are tall, powerful steeds.\n");

    add_item( ({"wood", "green" ,"emerald", "gold", "framing"}),
	     "The trims and touches on the outside of this carriage "+
	     "are amazing. A lot of work must go into maintaining and "+
	     "keeping this in proper condition.\n");

	board_enabled = 1;
}

/*
* Function name: init
* Description  : Add commands to the player presend outside the ship
*/
public void
init()
{
	::init();
	add_action(board, "board");
	add_action(board, "enter");
}
