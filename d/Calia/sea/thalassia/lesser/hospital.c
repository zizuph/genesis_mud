
/*  Hospital in the Lesser Zone of Thalassia

    coder(s):   Jaacar

    In this room you can get scars removed for a fee and some
    hitpoints. The removal will NOT kill anyone (doesn't call
    do_die() ), but it could very well lower someone's hitpoints
    to 0. The amount of hitpoints is costs is set by HP_FEE at
    the beginning of the file. The fee is determined by the following
    formula:

    MAX(MIN_REMOVAL_COST,(MIN(MAX_REMOVAL_COST,avg_stat >= pl_days ? 
        (MIN(300,avg_stat / MIN (300, pl_days) * 150)) : avg_stat * 500)))

    pl_days equals the players age in days, avg_stat equals the
    players average stat. The minimum and maximum fees are set by
    MIN_REMOVAL_COST and MAX_REMOVAL_COST at the beginning of the file.

    history:    15. 7.03    room coded                      Jaacar

*/

#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"
#include SEA_QUESTS

inherit "/lib/trade";
inherit "/d/Calia/std/water_room";
#define have_scar(x) (TP->query_scar() & x)

int scar_price = 0;
int MIN_REMOVAL_COST = 500;
int MAX_REMOVAL_COST = 1500;
int HP_FEE = 500;

void
create_water_room()
{
    set_short("A medical facility");
    set_long("You have entered the medical facility of "+
        "Thalassia. There is a curtain hanging through the "+
        "water from the ceiling blocking your view of the "+
        "western half of this room. There is a sign on the "+
        "wall.\n");

    add_item("sign","The sign has writing on it that you "+
        "can read.\n");

    config_default_trade();
    add_prop(ROOM_I_INSIDE, 1);
    add_swim_exit(THALL+"lesser10","east",0,1);
}

int
do_read(string str)
{
    int avg_stat, pl_days;

    NF("Read what? The sign?\n");
    if (!str || (str != "sign"))
        return 0;
    
    pl_days = TP->query_age() / (30*60*24);
    avg_stat = TP->query_average_stat();
    scar_price = MAX(MIN_REMOVAL_COST,(MIN(MAX_REMOVAL_COST,avg_stat >= pl_days ? 
        (MIN(300,avg_stat / MIN (300, pl_days) * 150)) : avg_stat * 500)));
    scar_price = (scar_price * 3);
    write("The sign reads:\n\nWe offer the following services:\n\n"+
        "Scar Removal - "+ scar_price + " gold coins. (Special "+
        "deal just for you!)\n"+
        "               This procedure is quick and painless!\n\n"+
        "Instructions: Type \"remove <scar>\" where <scar> is "+
        "the location of the scar.\n");
    return 1;
}

int
do_remove(string arg)
{
    int avg_stat, pl_days, scarnum, *payarr;

    if (arg == "left leg") 
        scarnum = 1;
    else if (arg == "right leg") 
        scarnum =2;
    else if (arg == "nose") 
        scarnum = 4;
    else if (arg == "left arm") 
        scarnum = 8;
    else if (arg == "right arm") 
        scarnum = 16;
    else if (arg == "left hand") 
        scarnum = 32;
    else if (arg == "right hand") 
        scarnum = 64;
    else if ((arg == "forhead") || (arg == "forehead")) 
        scarnum = 128;
    else if (arg == "left cheek") 
        scarnum = 256;
    else if (arg == "right cheek") 
        scarnum = 512;

    NF("I'm sorry, but you don't have a scar there.\n");
    if (!have_scar(scarnum)) 
        return 0;

    pl_days = TP->query_age() / (30*60*24);
    avg_stat = TP->query_average_stat();
    scar_price = MAX(MIN_REMOVAL_COST,(MIN(MAX_REMOVAL_COST,avg_stat >= pl_days ? 
        (MIN(300,avg_stat / MIN (300, pl_days) * 150)) : avg_stat * 500))) * 144;
    
    NF("You can't afford our services.\n");
    if (can_pay(scar_price, TP))
    {
        payarr = pay(scar_price,TP);
        write("You hand over your coins and you are led behind "+
            "the curtain. You lay down on a table and a triton "+
            "approaches you. He looks you over, smiling at you. "+
            "He motions for you to close your eyes and you do so. "+
            "You feel a sharp pain on your "+arg+" for a brief "+
            "second (so much for a painless procedure!). Before "+
            "you know it, the scar on your " + 
            arg + " has removed and you are being told you can "+
           "leave. You rise from the table and return back "+
           "through the curtain, closing it behind you.\n");
        TP->set_scar(TP->query_scar() - scarnum);
        TP->heal_hp(-HP_FEE);
        say(QCTNAME(TP)+" is lead behind the curtain. "+
            capitalize(TP->query_pronoun())+" is gone for "+
            "a few moments and then returns through the "+
            "curtain again, rubbing "+TP->query_possessive()+
            " "+arg+".\n",TP);
        return 1;
    }
    else return 0;
}

void
init()
{
    ::init();
    add_action(do_remove,"remove");
    add_action(do_read,"read");
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (ob->query_prop(THAL_W_ADMIN_PROP))
    {
        ob->catch_msg("\n\nYou have successfully found the medical facilities. "+
            "You can return to the west administration office of the "+
            "Royal Palace and ask for your reward.\n\n");
        ob->add_prop(THAL_W_ADMIN_PROP,2);
    }
}


