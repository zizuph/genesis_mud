#pragma save_binary

inherit "/std/object";
#include <macros.h>
#include <stdproperties.h>
#define DIR      "/d/Gondor/common/guild/"

void
create_object()
{
    set_name("scroll");
    add_name("ranger-scroll");
    add_name("ranger_scroll");
    set_short("scroll of the Gondorian Rangers");
    set_long("This scroll was given to you as an introduction to your new guild,\n"+
      "the Gondorian Rangers Guild. There's a lot of text on it, which you\n"+
      "may read.\n");
    add_prop(OBJ_I_VALUE,0);
    add_prop(OBJ_I_WEIGHT,10);
    add_prop(OBJ_I_VOLUME,10);
    add_prop(OBJ_I_NO_DROP,"@@do_destruct");
}

void
init()
{
    add_action("read_scroll","read");
}

int
read_scroll(string str)
{
    if (!str)
    {
        notify_fail("Read what?\n");
        return 0;
    }
    if (str=="scroll" || str == "text" || str == "text on scroll")
    {
        cat(DIR+"txt/rscroll.txt");
        return 1;
    }
    return 0;
}

void
destruct_me()
{
    object room;
    room = environment();
    while (!room->query_prop(ROOM_I_IS))
        room = environment(room);
    tell_room(room,"The scroll suddenly catches fire, and burns to dust in a flash!\n");
    remove_object();
}

int
do_destruct()
{
    set_alarm(2.0, 0.0, destruct_me);
    return 0;
}
