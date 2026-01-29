inherit "/std/room";
/* common routines for all of the wiz island code */

#include <std.h>

#include "def.h"

void
add_default_exits()
{
        add_exit(THIS_DIR + "virtual", "virtual", "@@virtual");
}

int
reality()
{
        write("You are turned outside in!\n" +
                "You feel real again.\n");
        return 0;
}

int
virtual()
{
        write("You are turned inside out!\n");
        return 0;
}

int
openway()
{
        write("You feel transported to another part of Genesis!\n" +
                "You feel the radiation from the mighty Lord's domain.\n");
        return 0;
}

int
blocked()
{
        write("The way is blocked by a force field!\n" +
                "You have reached the end of the Universe!\n");
        return 1;
}

int
construction()
{
        write("The way is blocked by a force field!\n" +
                "These parts are closed due to construction work!\n" +
                "Beyond the field a ghostly assembly crew is working.\n");
        return 1;
}

object
load_board(string bull_file)
{
    object bb;
    string name;

    bb = clone_object("/std/board");

    name = THIS_DIR + "boards";
    if (file_size(name) != -2)
        mkdir(name);

    bb->set_board_name(name + "/" + bull_file);
    bb->set_num_notes(50);
    bb->set_silent(1);  /* Keep the mud tidy RW */
    bb->set_show_lvl(1); /* Wizards may see levels, Mercade. */
    bb->set_keep_discarded(0);
    bb->move(this_object(), 1);
    return bb;
}

object
get_domain_lord(string name)
{
        string lord;

        lord = (string) SECURITY->query_domain_lord(name);
        if(lord) {
                return (object) SECURITY->finger_player(lord);
        } else {
                return 0;
        }
}
