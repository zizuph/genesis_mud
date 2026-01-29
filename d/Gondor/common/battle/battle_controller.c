/*
 * battle_controller.c
 *
 * Battle controller room
 *
 * Coded by Gwyneth, June 24, 2001
 */
inherit "/d/Gondor/common/room.c";

#include <macros.h>
#include "/d/Gondor/common/battle/battle.h"

string *gBattleFiles = ({});

void startup_battles();

void
create_room()
{
    set_short("Battle Controller");
    set_long("Here is where battles are added to the stream of time. To " +
        "add a battle, create a file which inherits " +
        "/d/Gondor/common/battle/battle.c. See the documentation for " +
        "battle.c " + "for further details. Once you have made that file, " +
        "placed it under the /d/Gondor/common/battle/ directory, you can " +
        "add it here with 'add filename', not the pathname, just the " +
        "filename.\n");
    restore_object(MASTER);
    startup_battles();
}

void
startup_battles()
{
    int i, size;

    for (i = 0, size = sizeof(gBattleFiles); i < size; i++)
    {
        (BATTLE_DIR + gBattleFiles[i])->notify_clock();
    }
}

int
add_battle(string str)
{
    if (member_array(str, gBattleFiles) != -1)
    {
        notify_fail("That battle is already scheduled.\n");
        return 0;
    }

    if (extract(str, -2, -1) != ".c")
        str += ".c";

    if (file_size(BATTLE_DIR + str) < 1)
    {
        notify_fail("No such battle to add. Be sure it is only the file " +
            "name, not the path, and that the file is located in the " +
            "/d/Gondor/common/battle/ directory.\n");
        return 0;
    }

    gBattleFiles += ({ str });

    save_object(MASTER);
    write("You add " + str + " to the battle schedule.\n");
    (BATTLE_DIR + str)->notify_clock();
    return 1;
}

void
init()
{
    ::init();

    add_action(add_battle, "add");
}
