/* Vladimir date */

inherit "/std/room.c";
void
create_room()
{
set_name("Temporary");
set_long(
        "This is the temporary room to help a certain wizard "+
        "figure out just how the heck to code a room. On the floor you can "+
        "see lots of failed files, and many errors. In the corner there is "+
        "a large punching bag used for when Vladimir gets frustrated and "+
        "feels like giving up. There is a hole in the floor, you think it "+
        "may be an exit.\n");

add_exit("/d/Roke/vladimir/workroom", "north");

add_exit("/d/Genesis/wiz/flame", "flame");

}
void
init()
{
::init();
write("The room groans softly, then turns to a deafening wail.\n");
}
