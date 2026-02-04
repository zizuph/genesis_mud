/*
 * Herb Shop of Dabaay
 * Proprietor - Anriel
 *
 * Goldberry, October 13, 1999
 */


#include "/d/Terel/include/Terel.h"
inherit STDSHOP;

#pragma strict_types

#define DAB_TOWN DABAAY_DIR + "town/"
#define STORE_ROOM DAB_TOWN + "hstore"
#define DOBJ DABAAY_DIR + "obj/"

void
create_shop() 
{
    set_store_room(STORE_ROOM);
    set_keeper_file(DABAAY_DIR + "npc/anriel");
    set_shop_name("Anriel's House of Herbs");
    set_short("Anriel's House of Herbs");
    set_long(
        "You are inside an aromatic little shop. Scents of various "+
        "plants and herbs assail your senses. On a shelf behind the "+
        "counter are several herb-related objects. "+
        "There is a sign hanging over a rustic table in the back "+
        "of the room.\n");

//    add_item("sign", "Anriel's House of Herbs.\n");
    add_item("table", "A simple table made of rough-hewn planks laid "+
        "on top of worm-eaten tree-stumps. There is a poster with instructions "+
        "written on it, tacked to the front of the table.\n");
    remove_item("poster");
    add_item("poster", "There are instructions printed on it that you should "+
        "read.\n");
    add_cmd_item(({"poster","sign"}),"read", "@@exa_poster");
    add_item("scents", "Sages, mints, and countless other aromas float about "+
        "the room.\n");
    add_item("shelf",
        "A simple wooden shelf, affixed to the back wall on triangular "+
        "braces. You can see several items realted to herbs on it. Of "+
        "particular interest, are a bunch of odd looking glass pipes.\n");
    add_item(({"pipes","pipe","glass pipes","glass pipe"}),
        "The glass pipes are oddly shaped, having the appearance of "+
        "a glass cylinder with a straw sticking out the side of it.\n");
        

    add_prop(ROOM_I_INSIDE, 1);
    add_prop("terel_herb_shop",1);

    hated_race = ({"goblin"});
    favoured_race = ({"human","elf","dwarf","hobbit","gnome"});
    suspected_race = ({"half-elf","kender"});

    add_exit(STORE_ROOM, "south", "@@wiz_check");
    add_exit(DAB_TOWN + "square4_1", "north", 0);
}

int
shop_hook_allow_sell(object ob)
{
    keeper->command("say Sorry, but I only buy herbs here.");
    return 0;
}

string
exa_poster()
{
    return "\n"+
        "Here you may find a <list> of what is for sale in this shop.\n"+
        "You may possibly <buy> items from that list.\n"+
        "The herbalist likely has herbs for sale too. You may "+
        "<purchase herbs> to see what he has to offer.\n\n";
}

