// Sarr,
// Fysix, recoded, March 1998

#include "default.h"

inherit NOBLE_ROOM;

#define QUEST "noble_minotaurquest"

int mino;

void
create_noble_room()
{
    set_short("In a hall of the Castle of the High-Lord");
    INSIDE;
    set_long("@@my_long@@");
    add_item(({"statue","marble statue"}),"@@my_statue@@");
    add_item("indentation","@@my_indent@@");
    add_item("carpet","The carpet is soft and warm.\n");
    add_item("torches","They hang on the walls.\n");
    add_item("paintings","The paintings depict scenes of "+
        "the wilderness.\n");

    add_exit(NOBLE + "castle/c20", "north", 0, 0);
    add_exit(NOBLE + "castle/c30", "south", 0, 0);
}

string
my_statue()
{
    if(mino == 0)
        return "It is a sculpture of "+
    "a minotaur, half-man half-bull, made out of marble. He "+
    "holds a nasty looking lochaber axe in one hand. In "+
    "the center of the statue, you see an indentation.\n";
    else
        return "You find no statue.\n";
}

string
my_long()
{
    if(mino == 0)
        return "You now stand on the soft, red carpet that covers "+
    "this long hall leading south. The walls have torches on "+
    "them to give light when needed. The walls here are "+
    "adorned with serene paintings. There is a marble statue "+
    "against one wall.\n";
    else
        return "You now stand on the soft, red carpet that covers "+
    "this long hall leading south. The walls have torches on "+
    "them to give light when needed. The walls here are "+
    "adorned with serene paintings.\n";
}

void
reset_room()
{
    mino = 0;
}



string
my_indent()
{
    if(mino == 0)
        return "The indentation is on the minotaur's "+
    "belt buckle. It appears that there was a giant gem of some "+
    "sorts removed from it....\n";
    else
        return "You find no indentation.\n";
}

int
my_put(string str)
{
    object gem,minot;

    NF("Put what?\n");
    if(!parse_command("put "+str,TP,"'put' %o 'in' 'indentation'",gem))
        return 0;

    NF("It doesn't fit there.\n");
    if(MASTER_OB(gem) != (NOBLE + "obj/blue_gem"))
        return 0;

    NF("There is no indentation!\n");
    if(mino == 1)
        return 0;

    write("You place the gem in the indentation, and it sticks!\n");
    say(QCTNAME(TP)+" puts a gem in the indentation.\n");
    gem->remove_object();

    if(!TP->test_bit("kalad",1,9))
        {
        write("You feel more experienced!\n");
        TP->add_exp(1000);
        TP->set_bit(1,9);
        log_file(QUEST, extract(ctime(time()),4,15) + " "+
            capitalize(TP->query_real_name()) + " rewarded with 1000 xp,"+
            "<"+TP->query_average_stat()+"> average stats.\n");
        tell_room(TO,"The statue suddenly comes alive!\n");
        minot = clone_object(NOBLE + "npc/minotaur");
        minot->arm_me();
        minot->move_living("M",TO);
        mino = 1;
        return 1;
    }
    mino = 1;
    write("The statue turns into dust in front of your eyes.\n");
    return 1;
}

void
init()
{
    ::init();
    add_action(my_put, "put");
}

