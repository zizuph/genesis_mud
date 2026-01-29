/*  We just inherit the std door for now... maybe some day down the
 *  road we'll develop this door  -Igneous-
 * Converted to Cypress
 * -- Finwe, June 2001
 */

inherit "/std/door.c";

void create_cypress_door() {}

nomask void
create_door()
{

    create_cypress_door();
}
