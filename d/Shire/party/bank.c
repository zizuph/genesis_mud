/*
 *
 * Updated bank to handle gems, bank num is 1202
 * -- Finwe January 6 2008
 */
#include "defs.h"

inherit PARTY_BASE;

void
create_party_room()
{
    object deposit = clone_object("/d/Genesis/obj/deposit");

    add_prop(ROOM_S_MAP_FILE, "party.txt");
    
    deposit->set_bank_id(1202, "Party Room");
    deposit->move(this_object(), 1);

    set_short("a small money lenders tent");
    set_long("You are standing within "+query_short()+".  A small "+
      "gnome carefully watches you from his desk, from which he does "+
      "all his paperwork. To the west you can hear fireworks and the "+
      "chatter of party goers.\n");
    add_item(({"tent","small tent"}),
      "The tent is made from a grey canvas material and looks like it could "+
      "withstand a mighty storm if need be.  It is poorly lit, only the light "+
      "from outside the tent illuminates it.\n");
    add_item("desk",
      "This is a wonderfully crafted oak desk, littered with piles "+
      "of papers and legal notices which the gnomes use to keep track "+
      "of all the transactions which occur here.\n");

    add_prop(ROOM_I_INSIDE,1);

    add_exit(PARTY_DIR + "entrance", "west", 0, 1);
    reset_shire_room();
}

void
reset_shire_room()
{
//    if (!present("strongroom",TO))
//	clone_object("/d/Genesis/obj/deposit")->move(TO);
}
