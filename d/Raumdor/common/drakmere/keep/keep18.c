#include "defs.h"
inherit KEEP_ROOM;
/* The Drakmere Keep, by Sarr */

/*
   Valen, Jul 2004 - fixed minor but vicious bug,
   eating random things when 'return' command is used,
   the faulty code is moved here to provide an example
   how important small details are ...

    for(i=0;i<sizeof(pinv);i++)
    {
        if(pinv[i]->query_name() == "_raumdorbook_");
        {
            write("You return the "+pinv[i]->query_short()+".\n");
            pinv[i]->remove_object();
            return 1;
        }
    }
*/

object ob, door;
void reset_room();

void
create_room()
{
    ::create_room();

    set_short("Inside the Keep of Drakmere");
    set_long(
      "You are in the library of Drakmere. There are many books shelved " +
      "along the walls. However, the south wall has no book shelves along " +
      "it, for covering it is a large vault.\n");
    add_exit(KEEP_DIR + "keep17", "west", "@@check");
    add_item("books",
      "Many hundreds of books line the walls of this room. A small sign is " +
      "on one of the shelves.\n");
    add_cmd_item("sign", "read", "@@sign");
    add_item("sign", "It has readable words on it.\n");
    door = clone_object(KEEP_OBJ_DIR + "vault_door_outside");
    door->move(TO, 1);
    reset_room();
}

void
reset_room()
{
    if (!ob)
    {
        ob = clone_object(DRAKMERE_NPC_DIR + "librarian");
        ob->move_living("xxx", TO);
    }
    if (!sizeof(FILTER_PLAYERS(LIVE(TO))))
        door->query_other_room()->reset_vault();
}

int
check()
{
    object *pinv;
    int     i;
    pinv = deep_inventory(TP);
    for (i = 0; i < sizeof(pinv); i++)
    {
        if (pinv[i]->query_name() == "_raumdorbook_")
        {
            write("You must return the borrowed book first!\n");
            return 1;
        }
    }
    return 0;
}

string
sign()
{
    return
        "Raumdor Library:\n" +
        "You can borrow books here. " +
        "To borrow the first on the list, just 'borrow #1'.\n" +
        "Remember to 'return book' after you are done.\n" +
        "\n" +
        "The titles currently available:\n" +
        "1. The Undead of Raumdor\n" + 
        "2. The History of Raumdor\n";
}

void
init()
{
    ::init();
    add_action("do_borrow", "borrow");
    add_action("do_return", "return");
}

int
do_return(string str)
{
    int     i;
    object *pinv;
    NF("Return what?\n");
    if (str != "book")
        return 0;
    pinv = deep_inventory(TP);
    for (i = 0; i < sizeof(pinv); i++)
    {
        if (pinv[i]->query_name() == "_raumdorbook_")
        {
            write("You return the " + pinv[i]->query_short() + ".\n");
            pinv[i]->remove_object();
            return 1;
        }
    }
    NF("You don't have a book to return.\n");
    return 0;
}

int
do_borrow(string str)
{
    NF("Borrow what book number?\n");
    if (!str)
        return 0;
    if (str == "1")
    {
        clone_object(KEEP_DIR + "book1")->move(TP);
        write("You are given a black book.\n");
        return 1;
    }
    if (str == "2")
    {
        clone_object(KEEP_DIR + "book2")->move(TP);
        write("You are given a purple book.\n");
        return 1;
    }
    NF("There is not such book available: " + str + ".\n");
    return 0;
}
