/* created by Aridor 03/09/94 */

#include "../local.h"
#include <ss_types.h>

inherit ROOM_BASE

void
create_thief_room()
{
    set_short("In a cavern");
    set_long("A deafening noise is right next to your ear. A stream " +
	     "comes from somewhere above and west of you and falls " +
	     "down into nothingness. You are standing in a small " +
	     "cavern south of the stream and light is shining in " +
	     "from somewhere above the water. The cavern extends " +
	     "into safety to the south into the mountain.\n");
    
    add_exit(THEIWAR + "r30","south");
    
    LIGHT;
    
    add_item(({"water","waterfall","stream","hole"}),
	     "The water is making a thunderous noise as it crashes down " +
	     "into a hole right next to you.\n");
    add_cmd_parse("'through' [the] 'water' / 'waterfall' / 'stream' / 'hole'",
		  ({"step","enter","go"}),
		  "@@through_waterfall");
    add_cmd_parse("[through] [into] [in] [the] 'water' / 'waterfall' / 'stream' / 'hole'",
		  ({"jump","leap"}),
		  "@@through_waterfall");
    add_cmd_parse("'into' / 'in' / '' [the] 'water' / 'waterfall' / 'stream' / 'hole'",
		  ({"step","enter","go"}),
		  "@@into_waterfall");
}

string
into_waterfall()
{
    write("You take a step forward and then you faaaaaaaaaaall...\n\n\n");
    TP->move_living("into the waterfall",CAVERN + "in_waterfall",1,1);
    (CAVERN + "in_waterfall")->flush_down(TP);
    return "";
}

string
through_waterfall()
{
    write("You try a huge leap.\n");
    if (random(TP->query_stat(SS_DEX)) < 30)
      return into_waterfall();
    TP->move_living("into the waterfall",CAVERN + "har11",1,1);
    TP->command("$look");
    write("Suddenly, you find yourself in another cavern on the other side " +
	  "of the waterfall.\n");
    return "";
}

