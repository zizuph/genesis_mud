#pragma strict_types

inherit "/std/door";

public void
create_door()
{
    set_door_id("_house_");
    set_pass_command(({"e", "east"}));
    set_door_name(({"wooden door","door"}));
    set_open(0);
    set_other_room("/d/Earthsea/gont/gont_city/rooms/house");
}
