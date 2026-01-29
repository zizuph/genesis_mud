#include "defs.h"

inherit PAV_ROOM;
inherit "/d/Genesis/lib/post";

void
create_pav_room()
{
    set_short("Ceral Island Post Office");
    set_em_long("Here at the side of the pavilion, a small area has been " +
        "set aside where travellers can send and receive posts before " +
        "setting sail.\n");

    // Override some of the default descriptions
    add_item(({ "post", "office", "post office", "postal area" }),
        query_long());

    add_exit("pav6", "southeast");
}
 
void
init()
{
    ::init();
    post_init();
}

void
leave_inv(object ob, mixed to)
{
    ::leave_inv(ob, to);
    post_leave_inv(ob, to);
}
