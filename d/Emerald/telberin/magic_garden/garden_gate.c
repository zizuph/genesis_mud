/* Emerald/Telberin/
 * Magic Garden gate
 * Created by Damaris
 * Updated 05/Y2K
 */
inherit "/d/Emerald/std/door";

void
create_emerald_door()
{
    set_name("gate");
    set_adj(({ "small", "silver", }));
    set_long("You take a closer look at the silver gate. It is a splendid "+
       "silver with etched designs of dark green and dark red which give "+
       "the illusion of vines with red roses covering it.\n");

    set_open(0);
}
