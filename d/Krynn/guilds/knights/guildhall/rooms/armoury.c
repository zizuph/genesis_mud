/*  Passage,   Vingaard Keep     */
/*  Coded by Grace, 04/06/94     */

#include "../../guild.h"
#include <ss_types.h>
#include <macros.h>

inherit IN_BASE;

object rack_object, rack_attendant;

public object
query_rack_object()
{
    return rack_object;
}

void
create_vin_room()
{
    set_short("Passage to armoury");
    set_long("A wide room forming a passage between the Hall and the High " +
    "Armoury. It is used chiefly as a repository of excess armours and " +
    "weapons, and as a place for Knights to prepare for combat without " +
    "crowding the Armoury.\n");
    AI(({"ceiling","floor","wall"}),"Grey granite composes this.\n");
    AI("walls","Grey granite compose these.\n");
    AI(({"grey granite","granite"}),"It is a volcanic rock.\n");
    AI("hall","The hall to the south opens into other rooms, and continues " +
    "onwards.\n");
    
    add_prop(ROOM_I_NO_CLEANUP, 1);
    AE(VROOM + "high_armoury", "north", 0);
    AE(VROOM + "north_hallway", "south", 0);
    (VROOM + "high_armoury")->load_me();
    (VROOM + "high_armoury_rack")->load_me();
    reset_room();
}

void
reset_vin_room()
{
    seteuid(getuid());
    
    if (!rack_object)
    {
        rack_object = clone_object(VOBJ + "new_rack.c");
        rack_object->set_rack_log_file(VLOG + "rack_log");
        rack_object->move(this_object(), 1);
    }
    
    if (!rack_attendant)
    {
        rack_attendant = clone_object(VNPC + "rack_attendant.c");
        rack_attendant->move(this_object(), 1);
    }
}

public void
leave_inv(object ob, object to)
{
    object *books;
    
    if (sizeof(books = filter(deep_inventory(ob), &->query_rack_log())))
    {
        if (rack_attendant)
        {
            ob->catch_msg(QCTNAME(rack_attendant) + " runs after you as you "
            + "are about to leave and retrieves the " + books[0]->short() + " "
            + "from your possession.\n");
            rack_attendant->tell_watcher(QCTNAME(ob) + " tries to leave but is "
            + "stopped by " + QTNAME(rack_attendant) + ", forced to return "
            + LANG_ADDART(books[0]->short()) + " before continuing on "
            + ob->query_possessive() + " way.\n", ({ ob }));
        }
        
        books->remove_object();
    }
    
    ::leave_inv(ob, to);
}