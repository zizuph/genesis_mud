/*
 * Lakeside road that goes to the crossroad of Telberin
 * Based on the kroad files
 * By Finwe
 * January 1997
 */

#include "../default.h"
#include "/d/Emerald/defs.h"

inherit LEAHROAD;


void
create_road()
{
    add_my_desc("A small bridge spans the narrow brook, heading "+
                "north to the gates of the small village.\n");
    add_my_desc("A lovely garden is west of here, tucked " +
      "away in the forest.\n\n"); 

    add_item( ({"bridge", "narrow bridge", "small bridge"}),
             "It is a small, quaint, wooden bridge which spans "+
              "the narrow length of the brook.\n");
    add_item( ({"garden", "lovely garden"}),
      "The garden looks lovely from here. Perhaps you'll see " +
      "more when you reach it.\n");
    add_exit(LROAD + "leroad09", "northeast");
    add_exit(VILLAGE_DIR + "gate", "north", "@@go_bridge@@");
    set_alarm(1.0,0.0,"reset_room");

}

int
go_bridge()
{
    write("You step up onto and walk over the small bridge leading "+
          "to the gates before the village ...\n\n");
}
