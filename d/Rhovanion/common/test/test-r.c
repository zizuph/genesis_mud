inherit "/d/Rhovanion/common/test/test";

void create_map_room()
{
    set_short("REL");
    set_long("Room with REL exits.\n");
    add_rel_exits();
}
