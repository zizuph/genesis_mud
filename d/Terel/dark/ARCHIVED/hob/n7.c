#include "/d/Terel/guilds/vamp/guild.h";
inherit "/d/Terel/guilds/vamp/room/vamp_room";
#include <stdproperties.h>
#include <macros.h>
#define PATH "/d/Terel/dark/"

void
create_room()
{
    set_short("square room at top of stairs");
    set_long("A square room at the top of a set of stairs. "+
        "There is a faint stench in the air.\n");
    add_item(({"walls","wall"}), "The walls are bare, smooth stone.\n");
    add_cmd_item(({"walls","wall"}), ({"push", "pull", "move"}), "@@do_push");
    add_exit(PATH + "hob/n6", "down", 0);

    reset_room();
}

int 
do_push()
{
    if (!IS_VAMP(TP) && !IS_BG(TP))
    {
        notify_fail(capitalize(query_verb()) +" what?\n");
        return 0;
    }       

    TP->catch_msg("There is a whoosh of air as a section of wall swings "+
        "outward.\n");
    say(QCTNAME(TP)+" steps into the dimness where the wall once was.\n");
    TP->move_living("M", "/d/Terel/guilds/vamp/room/storageroom", 1, 0);
    return 1;
}

