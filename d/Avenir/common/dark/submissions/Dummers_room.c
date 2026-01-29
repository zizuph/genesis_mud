/*
 * File:          /d/Avenir/common/dark/submissions/Dummers_room.c
 * Creator:       Dummer
 * Date:          Thu Dec 28 19:56:11 2006
 * Note:          This room was auto-generated using
 *                the room creator module inherited by
 *                /d/Avenir/common/dark/mon/foreman#79663
 * Comments:      
 *                Hello
 */
#include "defs.h"
inherit "/std/room";

void
create_room ()
{
    set_short("Dummers room");
    set_long("A magnificent room filled with wonderful things "
        + "like computers, television sets and many books. "
        + "One black one white one brown and one orage "
        + "bookcase fills the room.\n");

    add_item(({"computer.computers.dator.linux.operating system","os"}),
        "A fine computer running Linux - the best operating "
        + "system in the world.\n");
    add_item(({"floor.mat"}),
        "Floor filled with mats of different colours and "
        + "sizes. All different.\n");
    add_item(({"wall","walls"}),
        "Just ordinary walls with a painting of someone "
        + "called Rembrandht.\n");
    add_item(({"rembrandht"}),
        "You have never heard of him. Must be some hack "
        + "painter. Just a picture of a red rose.\n");
    add_item(({"rose"}),
        "The rose is very red.\n");
    add_item(({"book","books","bookcase"}),
        "Its dummers books. Dont touch them.\n");
    add_item(({"computer","computers","dator","linux"}),
        "A fine computer running Linux - the best operating "
        + "system in the world.\n");
    add_item(({"ceiling"}),
        "A black ceiling. Nothing special.\n");
    add_item(({"black"}),
        "Its black like the night.\n");
    add_item(({"night"}),
        "You cant see the night - you are inside.\n");
    add_cmd_item(({"books","bookcase"}),
        ({"touch","feel"}),
        "Lightning strucks you. Dummer is angry at you.\n");
    add_cmd_item(({"computer"}),
        ({"start"}),
        "The computer purrs alive and ask "Password:"\n");
    add_cmd_item(({"computer"}),
        ({"password"}),
        "Sorry wrong password.\n");


}
