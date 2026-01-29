/* Ashlar, 10 May 97 - A potion merchant selling suspicious potions */

#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

inherit OUTER_IN;

object merchant = 0;

void
reset_neraka_room()
{
	if (!merchant)
    {
    	merchant = clone_object(NNPC + "potion_merchant");
        merchant->move_living("xxx",TO);
    }
}

void
create_neraka_room()
{
	set_short("strange-smelling shop");
    set_long("You are in a strange-smelling building, which seems to " +
        "be a shop. A rickety wooden table stands in the middle of the " +
        "room, bearing a sign on its battered top. To the north, a curtain " +
        "covers a doorway leading to a back room which seems to be the " +
        "source of the strange smells.\n");
    add_item(({"table","wooden table","rickety table","rickety wooden table"}),
        "The table has definitely seen better days, the top is battered " +
        "and scratched. A sign rests on top of the table.\n");
    add_item("sign","It is a sign of the paper kind, bearing upon its face " +
        "words that can be read.\n");
    add_cmd_item(({"sign"}),({"read"}),({"The sign is printed in crude " +
        "block letters, and reads:\n\n" +
        "Buzlik's Potions!\n" +
        "Guaranteed For Effect! Cheap Prices, Just Ask Us! Buy Today!\n"}));
    add_item(({"curtain","doorway"}),"A dreary brown curtain covers a " +
        "doorway to the north. The doorway leads to a back room, the " +
        "source of the strange smells in this building.\n");

    add_item_inside();
    remove_item("north wall");
    add_item("north wall",
        "There is a curtain covering a doorway set in the north wall.\n");
        
    add_exit("","north","@@msg_north",1,1);
    add_exit(NOUTER+"blue/b9","out","@@msg_out");

    reset_room();
}

int
msg_north()
{
	write("You decide not to risk the smells and you stay away from " +
        "the back room.\n");
    return 1;
}

int
msg_out()
{
	write("You open the door and exit the shop.\n");
    return 0;
}

void
greet_customer(object ob)
{
	if (merchant && CAN_SEE_IN_ROOM(merchant) && CAN_SEE(merchant,ob))
    {
        ob->catch_msg(QCTNAME(merchant) + " grins at you, showing his two " +
            "remaining teeth.\n");
        tell_room(TO,QCTNAME(merchant) + " grins at " + QTNAME(ob) + ", " +
            "showing his two remaining teeth.\n",ob);
    }
}

void
enter_inv(object ob, object from)
{
	::enter_inv(ob,from);
	if (merchant && (ob != merchant))
        set_alarm(2.0,0.0,&greet_customer(ob));
}

