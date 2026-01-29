#pragma strict_types
#pragma no_clone

inherit "/std/room";
inherit "/sys/global/money";

#include <stdproperties.h>

#define PRICE 25
#define HARREKKI "/d/Earthsea/gont/gont_city/liv/harrekki"

public void
create_room()
{
    add_prop(ROOM_S_MAP_FILE, "earthsea_map.txt");
    set_short("Harrekki room");
    set_long("The air here has an unusual animal "+
        "odor. It has no windows and is warmed by an iron "+
        "stove, which stands in the middle of the room. You "+
        "see some small cages stacked against the wall, from which "+
        "you hear occasional sounds. There is a sign posted on "+
        "the north wall.\n");
    add_item((({"small cages", "cages"})),
        "The cages are made from wood and have thin slats in them "+
        "to let in air. You cannot see what is inside, however.\n");
    add_item((({"stove", "iron stove"})),
        "An iron stove in the middle of the room provides warmth "+
        "for the animals.\n");
    add_cmd_item("sign", "read", "@@read_sign");
    add_item("sign", "Perhaps you could read it?\n");
    add_prop(ROOM_I_INSIDE, 1);
    add_exit("post_office", "east");
}

public int
buy(string str)
{
    object tp = this_player(), harrekki;

    setuid();
    seteuid(getuid());

    if(str == "harrekki")
    {
        if(take_money(tp, PRICE) == 0)
        {
            return notify_fail("You don't have enough money to buy a " +
                "harrekki.\n");
        }

        harrekki = clone_object(HARREKKI);

        if(harrekki->move(tp))
        {
            write("You pay the fee.\n");
            write("You are too loaded down, and the harrekki "+
                "drops to the floor.\n");
            harrekki->move(this_object(), 1);
        }

        write("You pay the fee and purchase a harrekki.\n");

        return 1;
    }

    return notify_fail("Buy what?\n");
}

public string
read_sign()
{
    return "The sign reads:\n"+
        "Harrekkis for Sale! Imported from the East Reaches! "+
        "\nSyntax: <buy harrekki>\n"+
        "These creatures make excellent messengers or pets, only 25cc!\n";
}

public void
init()
{
    ::init();
    add_action(buy, "buy");
}
