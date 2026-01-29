#include "defs.h"

inherit MIST_PROMINENCE_BASE;

public int
nonobvious()
{
    return !CAN_SEE_TOWER(this_player());
}

public void
create_prominence_room()
{
    add_exit("prominence04", "northwest");
    add_exit("prominence02", "east");
    add_exit("mist_isle26", "down");
    add_exit("tower_start", "north", 0, 0, nonobvious);
}

/* We don't want people who can't see the tower using the tower exit.
 * We could just block the exit, but then the message might give away
 * that there is something suspicious here.  Of course, we could just
 * use the standard "no obvious exit" message in the block, but then
 * our code would be out of date if that message were changed.  I think
 * this is the best way to ensure that everything looks--and stays--as
 * clean as possible.
 */
public int
unq_move(string str)
{
    if ((query_verb() == "north") && !CAN_SEE_TOWER(this_player()))
    {
        return unq_no_move(str);
    }

    return ::unq_move(str);
}
