/*******************************************************************************
 *  NCAMP_ROOM + "post.c"
 *
 *  A post office.
 *
 *  Last modified by Alto, 23 November 2002
 *
 */
inherit "/d/Gondor/common/lib/post";

#include "/d/Gondor/defs.h"
#include <language.h>
#include <macros.h>
#include <stdproperties.h>
#include "../ncamp_defs.h"

#define PIGEON_VALUE 12

void
create_room()
{
    set_short("A rudimentary post office");
    set_long("This room is little different from the other huts in the "
        + "settlement. It is crude with almost no furniture. A sign "
        + "on the wall, however, reads: 'Post Office'. Even in the "
        + "backwaters of the Kingdom, the people of Gondor can rely "
        + "upon the mail service. There is a small poster on the wall "
        + "with instructions.\n");

    set_poster_name("small poster");

    add_item(({"room"}), "There isn't much in here to examine.\n");
    add_item(({"floor"}), "The floor is made from rough-cut timber. It "
        + "is devoid of furniture.\n");
    add_item(({"wall", "walls"}), "The walls are made from rough-cut "
        + "timber. With the exception of the small poster, they are "
        + "unadorned.\n");
    add_item(({"ceiling"}), "The ceiling is made from rough-cut "
        + "timber. It seems sturdy and will probably not fall on your "
        + "head in the next few minutes.\n");
    add_item(({"sign"}), "As you already noticed it has two words "
        + "written upon it: 'Post Office'.\n");

    create_post();

    add_exit(NCAMP_ROOM + "camp9", "out", 0);

}
 
string
exa_poster()
{
   return "Check the mailreader for instructions.\n";
}
