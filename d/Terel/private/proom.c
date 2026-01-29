inherit "/std/room";

#define BOARD "/d/Terel/private/tboard"

void
create_room()
{
    set_short("Terel Private Room");
    set_long("A doorless circular room. The walls spread out with a " +
             "map of Terel.\n");

    setuid();
    seteuid(getuid());
    clone_object(BOARD)->move(this_object(), 1);
}
