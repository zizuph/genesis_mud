
/* Haystack to make the stable worth entering */
/* Very similar to the ashes in the Mansion   */

inherit "/std/object.c";

#include "/d/Terel/common/terel_defs.h"
#include <stdproperties.h>
#include <macros.h>

#define BS(s)   break_string(s,70)
#define TP      this_player
#define TO      this_object

int needle_gone = 0;

void
init()
{
    ::init();
    seteuid(getuid(TO()));
}

create_object()
{
    set_name("hay");
    add_name(({"haystack", "bale"}));
    set_short("large bale of hay");
    set_pshort("large bales of hay");
    set_long(BS("This pile of hay has obviously been left here as a " +
                "winter reserve for the horses in the stable below.\n"));

    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_M_NO_GET,"The hay would be too awkward to carry.\n");
    add_prop(OBJ_S_SEARCH_FUN, "do_search");
}

string
do_search()
{
    object needle;
    string str;
    
    if (!needle_gone)  {
        needle_gone = 1;
        needle = clone_object(TOWNDIR + "stable/needle.c");
        str = "You amazingly find a needle in the haystack!\n";
        if (needle->move(TP()))  {
            needle->move(environment(TP()));
            str = str + "The needle is so sharp it pricks your finger ";
            str = str + "forcing you to drop it.\n";
        }
        say(QCTNAME(TP()) + " finds something in the hay.\n");
        return str;
    }
    else
        return BS("You search reveals nothing.  Perhaps looking for a " +
                  "needle in a haystack isn't such a good idea.\n");
}

reset_object()
{
        needle_gone = 0;
}
