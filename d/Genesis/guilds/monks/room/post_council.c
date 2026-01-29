/*
 * File:    post
 * Creator: Cirion, 1998.06.14
 * Purpose: post office for the monks guild
 */
#include "defs.h"

#define MAILCHECKER   "/secure/mail_checker"
#define MAILREADER    "/secure/mail_reader"
#define MAILREADER_ID "_reader_"

inherit ROOMBASE;
inherit "/d/Genesis/lib/post";

void
create_room ()
{
    set_short ("small, quiet room");
    set_long ("This is a small, quiet room. There is a wide doorway "
        + "in the north wall, and three oaken writing desks against the "
        + "other three walls.\n    The room is quiet, solemn, a place that "
        + "has a feel of calmness and contemplation.\n");
    WIZINFO("This is the council post office for the monks guild.\n");

    // where, command
    add_exit("council", "south");
}

void
init()
{
    ::init();

    // initialize the standard PO actions
    post_init();
}

void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);
    post_leave_inv(ob, to);
}



/*
 * Wizards don't need to watch people read and
 * write mail here.
 */
public int
query_prevent_snoop()
{
    return 1;
}


