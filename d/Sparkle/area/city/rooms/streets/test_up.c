inherit "/std/room";

create_room()
{
    set_short("just a test room");
    set_long("Just a test room.\n");

    add_exit("northeast_2d", "down");
}
