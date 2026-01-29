inherit "/std/door";

public void
create_door()
{
    set_door_id("_pub_door_");
    set_pass_command(({"w", "west"}));
    set_door_name(({"wooden door", "door"}));
    set_open(0);
    set_other_room("/d/Earthsea/gont/tenalders/village/pub_room");
}
