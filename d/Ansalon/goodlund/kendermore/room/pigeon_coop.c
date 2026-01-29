/* Vingaard pigeon hut by Teth
* Modified to Kendermore pigeon room by Gwyneth, May 22, 1999
*/

#include "../local.h"
#include <macros.h>
#include <money.h>
#include "/d/Ansalon/common/defs.h"

inherit KENDERMORE_OUT;

#define FEATHER KOBJ + "w_feather"

int feather_no = 0;
object mop; 

void
reset_kendermore_room()
{
    if (!P("mop", TO))
        clone_object(KNPC + "mop")->move_living("xx", TO);
    feather_no = 0;
}

void
create_kendermore_room()
{
    set_short("By a tree full of pigeons");
    set_long("@@long_descr");
    add_item("pigeons", "They seem to be very well trained, since you see " + 
        "nothing that would keep them here.\n");
    add_item("feathers", "Perhaps you could borrow a few.\n");
    add_item("sign", "The sign reads:\n\npIjeNs 2 copur\n\n");
    add_item("branches", "There must be a dozen pigeons on each branch!\n");
    add_item(({"tree", "trees"}), "They are tall, and their branches spread " + 
        "out to shade the surrounding area generously.\n");

    add_cmd_item(({"pigeon", "pigeons"}), ({"get", "take", "pick"}), "The " + 
        "pigeons are too high to reach.\n");
    add_cmd_item("feathers", "borrow", "@@borrow_feathers");
    add_cmd_item("sign", "read", "The sign reads:\n\npIjeNs 2 copur\n\n");
    add_cmd_item(({"tree", "trees"}), "climb", "You try to climb the trees, " + 
        "but decide against it after getting hit in the head by pigeon " + 
        "droppings.\n");

    add_exit(KROOM + "po", "northeast", 0);

    reset_kendermore_room();
}   

string
long_descr()
{
    return(tod_descr() + season_descr() + "This is an open area behind " + 
        "the Post Office. The branches of several trees groan under the " + 
        "weight of dozens of cooing pigeons. There is a crudely drawn sign " + 
        "stuck in the ground, surrounded by several stray pigeon feathers.\n");
}

void
reset_feather()
{
    feather_no = 0;
}

/* Allows players to pick up four feathers from the ground. */

string
borrow_feathers()
{
    if(feather_no)
    {
        write("A strong breeze blows the feathers from your grasp as you " + 
            "try to pick them up. Maybe it will be less breezy later.\n");
        return "";
    }

    write("You borrow a few feathers from the ground. Nobody will notice.\n");
    say(QCTNAME(TP)+ " picks something up from the ground and slips it " + 
        "in " + HIS(TP) + " pocket.\n");
    clone_object(FEATHER)->move(TP);
    clone_object(FEATHER)->move(TP);
    clone_object(FEATHER)->move(TP);
    clone_object(FEATHER)->move(TP);
    feather_no = 1;
    set_alarm(600.0, 0.0, "reset_feather");
    return "";
}

init()
{
    ::init();
    ADA("buy");
}

buy(str)
{

    object pig, who;
    NF("What did you want to buy?\n");
    if (!str || (str != "pigeon"))
        return 0;

    NF ("There is no one here to sell you a pigeon.\n");
    if (!P("mop", TO))
        return 0;

    NF("Mop holds up two fingers and says: That not two!\n");
    if (!MONEY_ADD(TP, -99))
        return 0;

    write("You pay significantly more than two coppers to the gully " + 
        "dwarf. He reveals large gaps in his teeth as he smiles.\nMop " + 
        "gives a little whistle and a pigeon lands on his shoulder.\nHe " + 
        "hands the pigeon to you and says: Two pigeons.\n");
    say(QCTNAME(TP) + " receives a pigeon from the gully dwarf.\n");

    who = TP;
    pig = clone_object("/d/Krynn/solamn/vin/npc/pigeon");
    pig->set_owner(who);
    pig->move(who);
    return 1;
}


