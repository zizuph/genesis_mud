inherit "/d/Emerald/std/room";

void
create_outpost_room()
{
    set_short("Outpost Room");
    set_long("A room in the outpost.\n");
}

nomask void
create_emerald_room()
{
    create_outpost_room();
}
