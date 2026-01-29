#pragma strict_types

inherit "/std/door";

public object
create_door()
{
    set_door_id("_office_");
    set_door_desc("This is a solid oak door.\n");
    set_pass_command(({"e", "east"}));
    set_door_name(({"wooden door","door"}));
    set_open(0);
    set_other_room("/d/Earthsea/gont/gont_city/rooms/tower_wall");
}
