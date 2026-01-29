inherit "/std/weapon";
inherit "/lib/keep";

#pragma strict_types;
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>
#include <formulas.h> 
#include <filter_funs.h>
#include <composite.h>
#include "/d/Shire/sys/defs.h"

#undef DEBUG_WHO
#ifdef DEBUG_WHO
#define DEBUG(s)  DEBUG_WHO->catch_msg(s + "\n")
#else
#define DEBUG(s)
#endif

string long_func();

int
find_bad_races(mixed where)
{
    object *livings = ({}), *baddies = ({}), room;
    setuid(); seteuid(getuid());
    if (stringp(where))
    {
    room = find_object(where);
    if (!objectp(room))
        catch(call_other(where, "??"));
    if (!objectp(room = find_object(where)))
        return 0;
    }
    if (objectp(where))
    room = where;
    if (!objectp(room) || !room->query_prop(ROOM_I_IS))
    return 0;
    DEBUG("Searching "+file_name(room));
    // Now we Search :)
    livings = FILTER_LIVE(all_inventory(room));
    if (!sizeof(livings))
    return 0;
    DEBUG("Filtering "+COMPOSITE_LIVE(livings));
    baddies += FILTER_RACE(livings, "orc");
    baddies += FILTER_RACE(livings, "goblin");
    baddies += FILTER_RACE(livings, "uruk");
    DEBUG("Returning "+(sizeof(baddies) ? COMPOSITE_LIVE(baddies) : "nothing"));
    if (!sizeof(baddies))
    return 0;
    return 1;    
}
string
long_func()
{
    string desc;
    object player = query_wielded();
    if (!objectp(player))
    player = TP;
    desc="LONG_DESC";
    if (!living(player))
        return desc;
    if (find_bad_races(ENV(player)) || 
      sizeof(filter(ENV(player)->query_exit_rooms(), find_bad_races)))
    desc += "The edges of the "+short()+" are shining brightly.\n";
    return desc;
}