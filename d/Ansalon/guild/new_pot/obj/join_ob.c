/* Stralle @ Genesis 010408
 *
 * A simple join object
 */

#pragma strict_types

inherit "/std/object";

#include "../guild.h"

void
create_object()
{
    set_name("foobar");
    set_long("This is a join object. Simply type 'join the guild' " +
        "to join it.\n");
}

nomask private int
join(string str)
{
    int err;
    object sh;

    if (!str && str != "the guild")
    {
        notify_fail("Join what?\n");
        return 0;
    }
    
    if (!wildmatch("*jr", this_player()->query_real_name()))
    {
        notify_fail("But you are not a jr.. Where did you get " +
            "hold of this, eh?\n");
        return 0;
    }
    
    setuid();
    seteuid(getuid());
    sh = clone_object(POTSHADOW);
    if ((err = sh->add_occ_shadow(this_player())) != 0)
    {
        write("Err: " + err + "\n");
        return 1;
    }

    write("You successfully joined the guild.\n");
    return 1;
}

void
init()
{
    ::init();
    
    add_action(join, "join");
}
