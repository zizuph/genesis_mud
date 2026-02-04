/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/room";

#include <stdproperties.h>
#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

#define TO                 this_object()
#define TP                 this_player()

object monster;

public void
reset_room()
{
   if (monster) return;
   
   seteuid(getuid());
   monster = clone_object(GUILD_DIR + "initiate");
   monster->move_living("M", TO);
}

public void
create_room()
{
    set_short("Dormitory");
    set_long("Peaceful in its simplicity, this small hall is framed all in " +
             "a deep stained pine. The rich wood forms all the walls and " +
             "even the floor. The ceiling is a low and arched, but made of " +
             "a lighter wood that has been painted. A tapestry hangs from " +
             "the north wall, over which is a symbol. To the north, south, " +
             "and east there are three cells in which you can rest in " +
             "privacy.\n");

    add_prop(ROOM_I_INSIDE, 1);

    add_item(({"ceiling", "painting"}),
             "The ceiling is painted with a small scene of a morning sky, " +
             "with the sun rising. There are a few clouds, but throughout " +
             "them fly dozens of white doves.\n");
    add_item("tapestry", "It is a royal purple and is embroidered with " +
                         "a circle of silver four-pointed stars.\n");
    add_item("symbol", "It is a silver serpentine creature that is " +
                       "intertwined with a star.\n");

    add_exit(GUILD_DIR + "s_hall2", "west",  0);
    add_exit(GUILD_DIR + "cell_n",  "north", "@@check|n@@");
    add_exit(GUILD_DIR + "cell_s",  "south", "@@check|s@@");
    add_exit(GUILD_DIR + "cell_e",  "east",  "@@check|e@@");

    reset_room();
}

public string
get_cell_cmd(string cell)
{
    if (cell == "n" || cell == "north") return "south";
    if (cell == "s" || cell == "south") return "north";
    if (cell == "e" || cell == "east") return "west";
    return "confused";
}

public void
leave_cell(object who, object npc, string cell, object where)
{
    if (!who || environment(who) != TO)
        return;
        
    if (!npc || environment(npc) != where)
        return;
        
    npc->command(get_cell_cmd(cell));
    npc->command("smile at " + who->query_real_name());
}

public int
check(string cell)
{
    int i;
    object room, *obs;

    if (!MEMBER(TP)) {
        write("You are not allowed to use the resting cells.\n");
        return 1;
    }

    room = find_object(GUILD_DIR + "cell_" + cell);

    if (!room) return 0;

    obs = all_inventory(room);

    for (i=0; i<sizeof(obs); i++) {
        if (!living(obs[i])) continue;
        write("That resting cell is already occupied by someone. " +
              "Try another one.\n");
        if (obs[i]->query_npc())
            set_alarm(5.0, -1.0, &leave_cell(TP, obs[i], cell, room));
        return 1;
    }
    return 0;
}
