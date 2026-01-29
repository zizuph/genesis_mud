/* Sarr */
inherit "/std/door";

void
create_door()
{
    set_door_id("manhole");
    set_pass_command(({"d","down"}));
    set_door_name(({"iron manhole","manhole"}));
    set_other_room("/d/Raumdor/common/drakmere/mh1");
    set_door_desc("It is a large iron manhole cover. If you open it, "+
        "you could go down below.\n");
    set_fail_pass("The manhole is closed.\n");
    set_open(0);
}
