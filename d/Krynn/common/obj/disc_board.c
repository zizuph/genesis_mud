/*
 * Filename:    disc_board.c
 * Description: This object is the client board that should contain notes
 *              that are important to all players in Krynn/Ansalon.
 *              In order to get it, just clone this object into the room.
 *
 * Please note that this object is not meant to be inherited by a fancy
 * object you make. This discussion board is provided on a take it or leave
 * it basis. Boards are very sensitive and we would not like to have
 * problems with it.
 *
 * This file was inspired by the COMMON board.
 */

#pragma no_inherit   /* no messing with this board */
#pragma save_binary  /* quick loading              */
#pragma strict_types /* you should be tidy         */

inherit "/std/object";

#include <stdproperties.h>

#define MASTER "/d/Krynn/common/obj/krynn_disc"

/*
 * Function name: create_object
 * Description  : This function is called to create the board.
 */
nomask void
create_object()
{
    set_name("board");
    add_name("bulletinboard");
    set_adj("discussion");
    add_adj(({"bulletin", "Krynn", "Ansalon", "Krynn/Ansalon"}));
    set_short("Krynn/Ansalon discussion board");
    add_prop(OBJ_M_NO_GET,  "It's firmly secured to the ground.\n");
    add_prop(OBJ_M_NO_SELL, "No-one is interested in such a thing.\n");
    add_prop(OBJ_I_VOLUME,  50000);
    add_prop(OBJ_I_WEIGHT,  60000);
    add_prop(OBJ_I_VALUE,     250);

    seteuid(getuid());
    MASTER->add_cloned_board(this_object());
}

nomask varargs string
long()
{
    return MASTER->long();
}

nomask void
init()
{
    add_action("new_msg", "note");
    add_action("read_msg", "read");
    add_action("read_msg", "mread");
    add_action("remove_msg", "remove");
    add_action("store_msg", "store");
    add_action("list_notes", "list");
}

nomask varargs int
list_notes(string str)
{
    return MASTER->list_notes(str);
}

nomask varargs int
new_msg(string new_head)
{
    return MASTER->new_msg(new_head);
}

nomask int
read_msg(string what_msg, int mr)
{
    return MASTER->read_msg(what_msg, mr);
}

nomask int
remove_msg(int what_msg)
{
    return MASTER->remove_note(what_msg);
}

nomask int
store_msg(string str)
{
    write("In order to store the messages you have to go to the Krynn domain office.\n");
    return 1;
}

/*
 * Function name: query_prevent_shadow
 * Description  : This function is to make sure that this object is never
 *                shadowed.
 * Returns      : 1 - always.
 */
nomask int
query_prevent_shadow()
{
    return 1;
}
