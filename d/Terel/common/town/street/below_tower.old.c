// This was once used by the Terel Vampires as a secondary guild hall.

inherit "/std/room";
// inherit "/d/Emerald/common/guild/vamp/lib/lair";

#include <language.h>
#include <filter_funs.h>
#include <language.h>
#include <stdproperties.h>

void
create_room()
{
    set_short("Underground floor of the tower");
    set_long("Like the rest of the tower, this area gives no " +
        "indication of its intended purpose.  @@barren_desc@@\n");

    add_prop(ROOM_M_NO_TELEPORT, 1);
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, -1);
//    add_prop("_room_i_free_vamp_dvis", 2);

    add_exit("tower1", "up");

//    add_coffins();
}

string
barren_desc()
{
    int i;
    string str;

    if ((i = sizeof(filter(all_inventory(), &->id("coffin")))) > 0)
    {
        str = "the " + LANG_WNUM(i) + " coffins";
    }
    else
    {
        str = "";
    }
   
    if ((i = sizeof(FILTER_DEAD(all_inventory())) - i) > 0)
    {
        str += (strlen(str) ? " and other " : "a few ") + "items";
    }

    if (!strlen(str))
    {
        return "This underground level is barren.";
    }

    return "Apart from " + str + ", this underground level is barren.";
}

/* 
void
init()
{
    ::init();
    init_lair();
}
*/
