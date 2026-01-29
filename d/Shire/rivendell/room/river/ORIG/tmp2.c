/* tmp placeholder for east bank of ford*/

inherit "/std/room";

create_room()
{
    set_short("placeholder for east bank of ford");
    set_long("Placeholder for east bank of ford.\n");

    add_exit("in_ford", "west");
}
