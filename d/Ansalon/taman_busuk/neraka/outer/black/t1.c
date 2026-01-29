/* Ashlar, 24 May 97 */

#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <money.h>

inherit OUTER_IN;

#define PRICE    144

object d1, d2, black_pass;

void
reset_neraka_room()
{

    if (!objectp(d2))
    	d2 = clone_npc(NNPC+"sivak","black");
	if (!objectp(d1))
    {
    	d1 = clone_npc(NNPC+"aurak","black");
        d1->add_ask("pass",QCTNAME(d1) + " sneers: You want to buy a pass " +
            "to the inner city, eh? Well for you the price is 1 gold coin!\n");
        d1->set_default_answer(QCTNAME(d1) + " looks at you in confusion.\n");

        d1->set_act_time(0);
        d1->clear_act();
        d1->add_act("emote growls: Have you come for a pass? If not, get " +
            "out!");
        d1->add_act("scratch leg");
        d1->add_act("emote searches through his papers.");
        black_pass = clone_object("/d/Ansalon/taman_busuk/neraka/obj/"+
                                  "pass.c");
        black_pass->move(d1,1);
    }
}

void
create_neraka_room()
{
    set_short("Inside a large canvas tent");
    set_long("You have entered a large tent made of black canvas. The " +
        "canvas withstands the harsh weather of the winter in the " +
        "mountains. In the middle of the tent is a fire pit, and a " +
        "table with some chairs are next to the pit. An oil lamp hangs " +
        "above the table, illuminating the tent.\n");
    set_quarter(BLACK);

    add_item(({"tent","canvas","canvas tent","black canvas"}),
        "The thick black canvas is made to withstand the harsh winter " +
        "weather of the mountains.\n");
    add_item(({"exit","flap","tent flap"}),
        "A flap of canvas hangs over the exit, to shield the tent from " +
        "the outside weather.\n");
    add_item(({"pit","fire pit","fire"}),
        "The fire pit has a fire burning, warming the tent.\n");
    add_item(({"lamp","oil lamp"}),
        "The oil lamp is burning, illuminating the tent.\n");
    add_item(({"table","table top"}),
        "The table top contains some papers lying in disarray.\n");
    add_item(({"chair","chairs"}),
        "Rickety wooden chairs, there are four of them placed around " +
        "the table.\n");
    add_item("papers","@@exa_papers");
    add_search("papers",3,NOBJ+"pass",-4);

    add_exit(NOUTER+"black/b17","out","@@msg@@");
    reset_room();
}

int
msg()
{
	write("You pull aside the flap, and exit the tent.\n");
    return 0;
}

mixed
paper_access()
{
    object d;
    d = P("draconian",E(TP));
    if (d)
    {
        say(QCTNAME(d) + " stops " + QTNAME(TP) + " from looking through " +
            "some papers.\n");
        return d->query_The_name(TP) + " stops you from looking through " +
            "the papers.\n";
    }
    return 0;
}

string
exa_papers()
{
    mixed s;

    s = paper_access();
    if (stringp(s))
        return s;
    else
        return "There are lots of papers of different kind, but none catch " +
            "your interest at first glance.\n";
}

int
search_papers(string arg)
{
    string s;
    if (stringp(arg) && (arg == "papers"))
    {
        if (stringp(s = paper_access()))
        {
            write(s);
            return 1;
        }
    }
    return 0;
}

int
do_buy(string arg)
{
    object pass;
    
    if (!P("aurak",TO))
        return 0;

    NF("Buy what?\n");
    if (!stringp(arg) || (arg != "pass"))
        return 0;

    NF("You do not have enough money to pay the price.\n");
    if (!MONEY_ADD(TP,-PRICE))
        return 0;

    pass = clone_object(NOBJ+"pass");

    NF("Oops, we seem to be all out of passes!\n");
    if (!objectp(pass))
        return 0;

    write("You pay the price and get your " + pass->short() + ".\n");        
    if (pass->move(TP))
    {
        write("The " + pass->short() + " is too heavy, and you drop " +
            "it on the ground.\n");
        pass->move(E(TP));
    }    
    return 1;
}

int
do_collect(string str)
{
    object obj;

    if (str == "a pass" || str == "a black pass" ||
        str == "pass" || str == "black pass")
    {
        if (TP->query_guild_name_occ() == "Priests of Takhisis" &&
            TP->query_guild_name_occ() == "Dragonarmy")
        {
            write("You quickly collect one of the black passes "+
                  "from the table.\n");
            say(QCTNAME(TP) + " collects one of the "+
                  "black passes from the table.\n");
            setuid();
            seteuid(getuid());
            obj = clone_object("/d/Ansalon/taman_busuk/neraka/obj/ "+
                        "pass.c");
            obj->move(TP,1);
            return 1;
        }
        else
        if (TP->query_guild_name_occ() != "Priests of Takhisis" &&
            P("aurak",TO))
        {
            write("As you try to collect one of the black "+
                  "passes from the table, the draconian "+
                  "grabs your hand and pushes you away, "+
                  "saying: Only the Priests may collect "+
                  "those.\n");
            say(QCTNAME(TP) + " tries to collect one of the "+
                  "black passes from the table but is stopped "+
                  "by the draconian.\n");
            return 1;
        }
        else
        if (TP->query_guild_name_occ() != "Priests of Takhisis" &&
            !P("aurak",TO))
            {
            write("The black passes on the table are covered with "+
                  "blood, making them unuseable.\n");
                return 1;
        }
    }
    write("Collect what? A black pass?\n");
    return 1;
}

void
init()
{
    ::init();
    add_action(search_papers,"search");
    add_action(do_buy,"buy");
    //add_action(do_collect,"collect");
}
