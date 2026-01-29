inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/red_fang/default.h"
/* Sarr */

int open;
object obj;
object obj2;

void
create_room()
{
    ::create_room();
    INSIDE;
    set_short("Guard Room");
    set_long("You are in a dim, torch light room. The walls all around "+
    "are made of smooth rock, and the torch light reflects off them. "+
    "On the walls are painted symbols. On the west wall, you see a small "+
    "handle. This looks like a guard room, as there is a table here where "+
    "guards sit and keep an eye on things.\n");
    add_item("symbols","They are made in bright red, but you cannot make "+
    "anything off them. However, they look brutal.\n");
    add_item("handle","It is a lever which you can pull.\n");
    add_item(({"walls"}),"The walls are all made of smooth rock.\n");
    add_exit(FANG_DIR(rooms/joinroom),"south",0,1,1);
    clone_object(CPASS(goblin/table))->move(TO);
    set_alarm(1.0,0.0,"reset_room");
}

void
reset_room()
{
    if(!obj)
    {
       obj = clone_object(FANG_DIR(obj/f_guard));
       obj->arm_me();
       obj->move_living("M",TO);
       tell_room(TO,"A goblin guard walks into the room from the south.\n");
    }
    if(!obj2)
    {
        obj2 = clone_object(FANG_DIR(obj/f_guard));
        obj2->arm_me();
        obj2->move_living("M",TO);
        tell_room(TO,"A goblin guard walks into the room from the south.\n");
    }
    obj->team_join(obj2);
}
/* To set the "portal" as an exit. */

int
do_portal(string str)
{
    if (member_array(str, ({"portal"})) == -1)

    {
        notify_fail("Enter what? The portal?\n");
        return 0;
    }

     write("You enter the portal.\n");
     say(QCTNAME(this_player())+" enters the portal and in a flash of light "+
       "disappears.\n");

    this_player()->move_living("M", "/d/Raumdor/guilds/fang/room/join", 1, 0);

    say(QCTNAME(this_player())+" suddenly appears through a portal.\n");
    return 1;
}

void
init()
{
    ::init();
    AA(do_handle,pull);
//    AA(do_portal,enter);
}

int
do_handle(string str)
{
    if(str != "handle")
    {
        NF("Pull what?\n");
        return 0;
    }
    write("You pull on the handle.\n");
    say(QCTNAME(TP)+" pulls the small handle.\n");
    set_alarm(2.0,0.0,"open_door");
    return 1;
}

void
open_door()
{
    if(!open)
    {
        tell_room(TO,"The north wall opens apart!\n");
        open = 1;
        add_exit(CPASS(goblin/g18),"north",0,1,1);
        call_other(CPASS(goblin/g18),"open_door");
        set_alarm(60.0,0.0,"close_door");
    }
}

void
close_door()
{
    if(open)
    {
        tell_room(TO,"The north wall closes.\n");
        open = 0;
        remove_exit("north");
        call_other(CPASS(goblin/g18),"close_door");
    }
}
