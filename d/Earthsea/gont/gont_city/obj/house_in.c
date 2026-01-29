#pragma strict_types

inherit "/std/door";

public object
create_door()
{
    set_door_id("_house_");
    set_pass_command(({"w", "west"}));
    set_door_name(({"wooden door","door"}));
    set_open(0);
    set_other_room("/d/Earthsea/gont/gont_city/rooms/yard");
}
