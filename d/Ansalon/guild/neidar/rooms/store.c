/*
 * store.c
 *
 * Neidar rack room.
 *
 * Carnak 2017-11-15:   Gave them a rack attendant to handle logging of items.
 * Carnak 2017-12-19:   Added leave_inv to remove the logbook when exiting the
 *                      rack room.
 *  
 */
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/estwilde/local.h"
#include "../guild.h"
#include <macros.h>
#include <stdproperties.h>

inherit DWARF_IN;
object dwarf, cabinet, chest, rack;

public object
query_rack_object()
{
    return rack;
}

void
reset_dwarf_room()
{
    if(!objectp(cabinet))
    {
        cabinet = clone_object(GUILD_OBJS + "rack/new_cabinet");
        cabinet->set_rack_log_file(GUILD_DIR + "log/neidar_rack_log");
        cabinet->move(TO);
    }
    
    if(!objectp(chest))
    {
        chest = clone_object(GUILD_OBJS + "rack/new_armour_chest");
        chest->set_rack_log_file(GUILD_DIR + "log/neidar_rack_log");
        chest->move(TO);
    }
    
    if(!objectp(rack))
    {
        rack = clone_object(GUILD_OBJS + "rack/new_weapon_rack");
        rack->set_rack_log_file(GUILD_DIR + "log/neidar_rack_log");
        rack->move(TO);
    }
    
    if (!objectp(dwarf))
    {
        dwarf = clone_object(GUILD_NPCS + "rack_attendant");
        dwarf->move(this_object());
    }
}

void
create_dwarf_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");

    add_item(({"plain room","room","store room"}),
      "@@long_descr");

    add_exit(GUILD_ROOMS + "board","south",0);

    reset_dwarf_room();
}

string
short_descr()
{
    return "Storeroom in the Hall of Warriors";
}

string
long_descr()
{
    return "This small, plain room is the store room " +
    "for the clan warriors equipment. An exit leads " +
    "out of here to the south.\n";
}

public void
leave_inv(object ob, object to)
{
    object *books;
    
    if (sizeof(books = filter(deep_inventory(ob), &->query_rack_log())))
    {
        if (objectp(dwarf))
        {
            ob->catch_msg(QCTNAME(dwarf) + " runs after you as you "
            + "are about to leave and retrieves the " + books[0]->short() + " "
            + "from your possession.\n");
            dwarf->tell_watcher(QCTNAME(ob) + " tries to leave but is "
            + "stopped by " + QTNAME(dwarf) + ", forced to return "
            + LANG_ADDART(books[0]->short()) + " before continuing on "
            + ob->query_possessive() + " way.\n", ({ ob }));
        }
        
        books->remove_object();
    }
    
    ::leave_inv(ob, to);
}