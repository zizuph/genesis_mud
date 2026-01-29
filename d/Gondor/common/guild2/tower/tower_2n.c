/*
 * /d/Gondor/common/guild2/tower/tower_2n.c
 *
 * Created: Olorin, 11-jan-1994
 *
 * Modification Log:
 */
#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/morgul/tower/tower.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/guild2/lib/morgul_defs.h"
#include "/d/Gondor/morgul/tower/tower_defs.h"

#define  MORGUL_I_DEATH_WARNING    "_morgul_i_death_warning"

public int  warning();

public void 
create_morgul_tower_room()
{
    set_level(2);
    set_room_type("great hall");
    set_extra_long("The hall is devoid of decorations and furniture " +
        "except for a large black stone slab in the back of the hall " +
        "further north of here. ");

    FLOOR
    NO_ROOF
    WALLS
    add_item(({"stone","stone slab","altar","slab"}), BSN(
        "The stone slab is in the back of the hall north of here. " + 
        "From here it is impossible to make out any details."));
    add_item(({"hall","great hall"}), BSN(
        "Except for the stone slab to the north, the hall is devoid of decorations and " +
        "furniture. The walls are also almost featureless, the seams " +
        "between the stone blocks are hardly visible. The roof is hidden " +
        "in the darkness above. A doorway is leading out of the hall to the south."));
    add_item(({"door","entrance","doorway","exit"}), BSN(
        "The doorway is just a rectangular opening in the south wall of the hall. " +
        "It leads back out onto the staircase."));

    add_prop(ROOM_I_LIGHT,1);

    add_exit(MAGES_DIR + "death_room", "north", warning,  0);
    add_exit(TOWER_DIR + "tower_2c",   "south", 0,  0);
}

public void 
answer_death(string str, object player)
{
    str = LOW(str);
    if (str == "death")
    {
        write(BSN("If you seek death, then go north, and enter " +
            "the service of the Lord of Morgul!"));
        player->add_prop(MORGUL_I_DEATH_WARNING, 1);
    }
    else
        write(BSN("There is nothing but Death to find at the Stone of Blood!"));
}

public void 
give_warning(object player)
{
    write("When you try to go north, you are held back by a powerful evil force.\n" +
          BSN("You feel like a terrible power is turning you inside out, " +
          "examining your deepest secrets and reading your soul like an " +
          "open book.") + 
          "A menacing voice whispers in your head:\n" +
          "    Why do you want to go there, puny mortal?\n" + 
          "    Answer me, what do you seek there?\n> ");
    input_to(&answer_death(, player), 0);
}

public int 
warning()
{
    string  gname;

    gname = TP->query_guild_name_occ();

    if (stringp(gname))
    {
        if (gname == GUILD_NAME)
        {
            write("Welcome home, " + TP->query_morgul_title() + "!\n");
            return 0;
        }
        else
        {
            write("A powerful evil force prevents you from going there!\n");
            return 1;
        }
    }

    if (!MORGUL_MASTER->accept_player(TP))
    {
        write("A powerful evil force prevents you from going there!\n" + 
            "You hear a dark menacing voice telling you:\n" +
            "     You are not worthy to go there!\n");
        return 1;
    }
    if (TP->query_prop(MORGUL_I_DEATH_WARNING))
    {
        write("All Ye Who Enter Here Shall Sacrifice Your Very Being!\n");
        return 0;
    }
    give_warning(TP);
    return 1;
}
