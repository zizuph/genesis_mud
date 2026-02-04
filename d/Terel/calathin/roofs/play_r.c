/*
 * po_r.c
 * Roof of the post office of Calathin.
 * Shinto 8/99
 *
 */

#include "/d/Terel/include/Terel.h"
inherit STDROOM;

#include <macros.h>
#include <stdproperties.h>

public void
create_room()
{
    set_short("The roof of the post office");
    set_long("You're on the roof of the Calathin post office. "+
                  "To the east you can see the spring that provides "+
                  "some of the water used by the people of Calathin. "+
                  "The roof is made of wood and supports your weight "+
                  "easily. To the southwest is the Silver Tree Inn and "+
                  "the playhouse is to the north. The town square "+
                  "spreads out to your west.\n");
    OUTSIDE;
    
    add_item("roof","The roof is made of wood taken from the "+
                    "forests that surround the town.\n");
    add_item(({"inn","silver tree","silver tree inn"}),
                "You can see the second floor of the inn clearly. "+
                    "The second floor isn't as big as the first, so "+
                    "there is open roof above parts of the building.\n");
    add_item("playhouse","The playhouse roof can be see to the "+
                    "north. A rather large building designed to hold a "+
                    "good portion of the town at once.\n");
    add_item("spring","The spring can be seen to the east. A "+
                    "good sized pool of water used for various things.\n");

    add_cmd_item("down","climb","@@climb");
    add_cmd_item("to playhouse roof","jump", "@@jump_play");
    add_cmd_item("to inn roof","jump","@@jump_inn");
}

int
climb()
{
    write("You carefully slide down to the ground below.\n");
    TP->move_living("down",CALATHIN_DIR + "square4_4");
    return 1;
}

int
jump_play()
{
    write("You leap across to the roof of the playhouse!\n");
    say(" leaps across to the roof of the playhouse!\n");
    TP->move_living("X",CALATHIN_DIR + "roofs/play_r");
    return 1;
}

int
jump_inn()
{
    write("You leap across to the roof of the inn!\n");
    say(" leaps across to the roof of the inn!\n");
    TP->move_living("x",CALATHIN_DIR + "roofs/inn_r");
    return 1;
}
