/* A test room */

inherit "/std/room";

create_room()
{
    set_short("A test room.");
    set_long("This room doesn't look very impressive. The wallpaper is" +
             " flaking off, and dust falls from the roof with every step" +
             " you take. Must be the work of an apprentice wizard.\n");
    add_exit("/d/Calia/bishop/workroom", "out",0);

}

    