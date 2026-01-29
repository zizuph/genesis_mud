/*
 * Gate to broad07 from Smiths guild
 * -- Finwe, April 2002
 */

inherit "/std/door";
#include "/d/Shire/sys/defs.h"
#include "defs.h"

create_door()
{
    set_door_id("smiths_gate");
    set_pass_command(({"e","east"}));
    set_door_name(({"ornate steel gate","steel gate", "gate"}));
    set_other_room(ROAD_DIR + "broad07");
    set_open(0);
    set_door_desc(
        "This is an ornate steel gate. It was crafted by skilled " +
        "smiths to mark the entrance to their guild.\n");
}
