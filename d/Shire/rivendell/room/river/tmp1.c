/* tmp placeholder for west bank of ford*/

inherit "/std/room";

create_room()
{
    set_short("placeholder for west bank of ford");
    set_long("Placeholder for west bank of ford.\n");

    add_exit("in_ford", "east");
}
