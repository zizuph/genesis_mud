inherit "/std/room";

create_room()
{
    set_short("Steed test room 2.");
    set_long("Steed test room 2.\n");
    add_exit("/d/Genesis/steed/test/room1", "in");
    add_exit("/d/Genesis/steed/test/room3", "east");
    clone_object("/d/Genesis/steed/test/s1")->move_living("M", this_object());
    clone_object("/d/Genesis/steed/test/s2")->move_living("M", this_object());
    clone_object("/d/Genesis/steed/test/s3")->move_living("M", this_object());
}
