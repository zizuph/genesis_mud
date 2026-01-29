/*  A notebook that gives the hints as to how to make a cure for
    side-effects in the Alchemist quest of Gelan.

    coder(s):   Maniac
    history:
             16.3.95        Created               Maniac
*/

inherit "/std/scroll";
#include <stdproperties.h>
#include "object.h"
#include ALCHEMIST_QUEST

void
read_it(string str)
{
    ::read_it("mread");
}

/* Reset notebook in alchemist's lab if this one is removed */ 
void
remove_object()
{
    seteuid(getuid());
    (GELAN_ROOMS + "alchemist_lab")->reset_notebook(); 
    if (environment(this_object())->query_prop(ROOM_I_IS))
        tell_room(environment(this_object()), "The " + short() +
                  " disappears in a puff of smoke.\n");
    ::remove_object();
}

/* Reset notebook if it's dropped */
void
leave_env(object old, object dest)
{
    ::leave_env(old, dest);
    if (!living(dest))
        set_alarm(1.0, 0.0, "remove_object");
}

void
create_scroll()
{
    set_name("notebook");
    add_name(AQ_BOOK_NAME);
    add_name("book");
    set_adj("old");
    set_short("old notebook");
    set_long("Title: Recovery from bizarre side-effects: " +
             "Index Rav - Stu.\nAuthor: Raspatoon Goldiloon, " +
             "Alchemist Extraordinaire.\n");
    set_file(GELAN_TEXTS + "notebook.txt");
    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_VALUE, 0);
}

