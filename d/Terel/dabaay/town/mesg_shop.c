#include "/d/Terel/include/Terel.h"
inherit STDSHOP;

#pragma strict_types

#define DAB_TOWN DABAAY_DIR + "town/"
#define STORE_ROOM DAB_TOWN + "mstore"
#define DOBJ DABAAY_DIR + "obj/"

void
create_shop() 
{
    set_store_room(STORE_ROOM);
    set_keeper_file(DABAAY_DIR + "npc/shan");
    set_shop_name("Dabaay's Menagerie of Messengers");
    set_short("Dabaay's Menagerie of Messengers");
    set_long(
        "You are inside a rustic little shop.  Judging by the smells, "+
        "this must be a place where several varieties of animals are "+
        "kept.  There is a sign hanging over a short counter in the back "+
        "of the room.\n"+
        "Wooden cages line the wall behind the counter.\n"); 

//    add_item("sign", "Dabaay's Menagerie of Messengers.\n");
    add_item("counter", "A simple counter made of rough-hewn planks laid "+
        "on top of old animal cages.  There is a poster with instructions "+
        "written on it, tacked to the front of the counter.\n");
    add_cmd_item(({"poster","sign"}),"read", "@@exa_poster");

    add_item("cages", "Cages of various sizes, holding a variety of creatures "+
        "trained in the art of delivery.\n"+
        "You may <list> what creatures are available to <buy>.\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop("terel_mesg_shop",1);

    hated_race = ({"goblin"});
    favoured_race = ({"human","elf","dwarf","hobbit","gnome"});
    suspected_race = ({"half-elf","kender"});

    add_exit(STORE_ROOM, "south", "@@wiz_check");
    add_exit(DAB_TOWN + "square3_4", "east", 0);
}

int
shop_hook_allow_sell(object ob)
{
    if(ob->query_prop("terel_messenger"))
        return 1;
    NF("");
    keeper->command("say This not one of my lil' friends!");
    return 0;
}

string
exa_poster()
{
    return "\n"+
        "Here you may find a <list> of what messengers are for hire.\n"+
        "You may also <buy> a limited-use messenger, or possibly <sell> "+
        "one to the proprietor.\n\n";
}
