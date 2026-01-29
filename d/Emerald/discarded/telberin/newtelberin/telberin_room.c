inherit "/d/Emerald/std/room";

void
create_telberin_room()
{
    set_short("Room in Telberin.\n");
    set_em_long("A room in Telberin!\n");
}

nomask void
create_emerald_room()
{
    create_telberin_room();
}
