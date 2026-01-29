/*  We just inherit the std door for now... maybe some day down the
 *  road we'll develop this door  -Igneous-
 */

inherit "/std/door.c";

void create_shire_door() {}

nomask void
create_door()
{

    create_shire_door();
}
