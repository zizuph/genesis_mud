inherit "/std/door";

public void
create_door()
{
    set_door_id("_h_store_");
    set_pass_command(({"s", "south"}));
    set_door_name(({"wooden door","door"}));
    set_open(0);
    set_other_room("/d/Earthsea/gont/tenalders/village/witch_herb_store");
}
