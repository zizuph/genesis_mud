/*
 * Path in the Mere of Dead Men
 * -- Finwe, July 2006
 */
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <stdproperties.h>
#include <terrain.h>

inherit BASE_MERE;

string extraline = "A road runs along the border of the mere.";

void
create_mere()
{

    set_short("Near the edge of the mere");
    set_extraline(mere_descr3(extraline));

    add_road();
    add_std_herbs("mere");

    reset_faerun_room();
    
    add_exit(HR_DIR + "srd04", "northeast");
    add_exit(ROOM_DIR + "me03", "northwest");
    add_exit(ROOM_DIR + "me11", "southeast");
    add_exit(ROOM_DIR + "me10", "southwest");



}

public void
init()
{
    ::init();
//    if (interactive(this_player()))
//        catch(call_other("/d/Faerun/mere/npcs/clone_handler.c", "??"));

}

void
reset_faerun_room()
{
    set_searched(0);
}
