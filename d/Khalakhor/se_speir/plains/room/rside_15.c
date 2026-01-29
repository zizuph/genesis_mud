/* File         : /d/Khalakhor/se_speir/plains/room/rside_15.c
 * Creator      : Darragh@Genesis
 * Date         : 01-01-24   
 * Purpose      : 
 * Related Files: 
 * Comments     :
 * Modifications:  
 */

#pragma strict_types

#include <macros.h>
#include <stdproperties.h>
#include <language.h>
#include <ss_types.h>
#include "/d/Khalakhor/sys/defs.h"
#include "plains.h"

inherit "/d/Khalakhor/se_speir/plains/room/tforbase";

int climb_ridge();
int swim_river();

int
climb_ridge()
{
    write("You are too unskilled for an attempt like this.\n");

    say(QCTNAME(this_player())+ " looks hesitantly up towards the "
                              + "crest of the ridge.\n");
    return 1;
}
int
swim_river()
{
    write("You are too unskilled to swim across the river.\n");

    say(QCTNAME(this_player())+ " watches the rapid movements of the "
                              + "river intently, then suddenly looks away.\n");
    return 1;
}
void
create_khalakhor_room()
{
   create_tforest();

   add_item(({"ridge"}),
              "The ridge is too steep and unsafe to climb up "
            + "at this point.\n");
   add_item(({"river","water","stream"}),
              "The river is gently flowing southwards, and the "
            + "water looks very deep and cold. The other side "
            + "looks no different from this side, lined with "
            + "tall pine trees.\n");
   add_item(({"underbrush","undergrowth","bush","bushes","ground",
              "floor","forest floor","vegetation","plants"}),
              "The ground you stand on is soft and wet, completely "
            + "covered by dense vegetation. You wonder how deep "
            + "down the actual ground is.\n");

   add_exit(PLAINS + "rside_16","north",0,5,0);
   add_exit(PLAINS + "rside_14","south",0,6,0);

   add_cmd_item("ridge","climb",climb_ridge);
   add_cmd_item("river","swim",swim_river);

   set_short("By a river in a light forest");
   set_long("   You are standing on a narrow strip of mostly dry land "
          + "between a river to the east of you, flowing gently southwards, "
          + "and a high ridge blocking your way west. A few trees grow "
          + "here, among the mass of bushes and heavy undergrowth.\n");

   create_room_tells();
}
void
create_room_tells()
{
   add_tell(({"You can hear something moving in the undergrowth.\n",
              "The treetops sway high above as a strong wind "
            + "rolls in from the north.\n",
              "Something high up on the ridge caused a few pebbles "
            + "to fall down in front of you.\n",
              "The river suddenly becomes very quiet.\n",
              "The sound of the flowing water becomes louder than before.\n",}));

   set_tell_time(400);
}
