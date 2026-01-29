inherit "/std/room";

void
create_room()
{
    set_long("Nazgul test room, drop location.\n");
    add_exit("/d/Gondor/guilds/morgulmage/npc/test/nazgul_test_room", "north");
}