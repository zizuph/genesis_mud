/*
 * Rack room for BDA HOs
 * -- Navarre April 2007
 */

#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/sanction/local.h"
#include "/d/Ansalon/guild/dragonarmy/guild.h"

#include <macros.h>

inherit SANCINROOM;

object  ho_rack,
        rack_attendant;
    
public object
query_rack_object()
{
    return ho_rack;
}

void
create_sanction_room()
{
    set_short("an opulent room for dragonarmy officers");
    set_long("@@long_descr");

    add_item(({"balcony","large balcony","floor","second floor",
	"area"}),
      "You stand on a balcony that overlooks the ground floor of " +
      "an inn in Sanction. This area has been opulently furnished.\n");
    add_item("furniture",
      "The finest furniture from all over Ansalon, both crafted and " +
      "plundered, has been used to fill this room with comforts fit " +
      "for any king.\n");
    add_item(({"balcony rail","rail"}),
      "A rail runs around the edge of the balcony to stop people " +
      "from falling to the floor below.\n");
    add_item("inn","You stand on a balcony in the finest inn in Sanction.\n");
    add_item("ground floor",
      "Beneath the balcony you stand on is the main room of this inn. A " +
      "haughty innkeeper quietly stands waiting for customers.\n");

    add_exit(SCITY + "balcony", "north", 0);
    
    /* Pointless to use the ifs, but copy paste from other code and lazy.
     * Should be in reset_krynn_room, but it has been masked.
     */
    
    if (!ho_rack)
    {
        ho_rack = clone_object(SOBJ + "rack/rack_bda_ho.c");
        ho_rack->set_rack_log_file(SOBJ + "rack/bda_ho_log");
        ho_rack->move(this_object(), 1);
    }
    
    if (!rack_attendant)
    {
        rack_attendant = clone_object(SNPC + "rack_attendant.c");
        rack_attendant->set_color("red");
        rack_attendant->move(this_object(), 1);
    }
}

string
long_descr()
{
    return "You stand on a large balcony, opulently furnished, " +
    "on the second floor of the finest inn in Sanction. This area " +
    "has been set up by the Dragon Highlord Ariakas as a place for " +
    "officers of the various armies " +
    "to gather in comfort. Looking over the balcony " +
    "rail you can see the ground floor of the inn.\n";
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