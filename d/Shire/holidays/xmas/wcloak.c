/*
 * Winter cloak for Christmas celebration
 * -- Finwe, November 2001
 */

#pragma save_binary

inherit "/std/armour";
inherit "/cmd/std/command_driver";
inherit "/lib/keep";

#include "/d/Shire/sys/defs.h"
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>
#include <cmdparse.h>
#include <std.h>
#include <ss_types.h>
#include <filter_funs.h>

//#include <options.h>


#define SAC 17
#define SAT A_ROBE
#define SAM ({0,1,0})
#define SNAME "cloak"
#define SADJ "white embroidered"
#define SSHORT "white embroidered cloak"
#define SPSHORT "white embroidered cloaks"

create_armour()
{
    set_name(SNAME);
    add_adj(({"white","embroidered"}));
    set_short(SSHORT);
    set_pshort(SPSHORT);
    set_long("This "+short()+" is full length, reaching to the " +
        "ground. The material is finely spun and very smooth. " +
        "Large, white snowflakes have been embroidered all over " +
        "the outside of the cloak and appear to be falling from " +
        "the head down to the ground. A gold chain is sewn onto " +
        "the cloak to fasten it across the shoulders. A tag is " +
        "sewn into the cloak.\n"); 

    add_item(({"gold chain"}),
        "The chain is made of twisted gold. It reaches from one " +
        "shoulder to the other to hold the cloak on.\n");
    add_item(({"white snowflakes", "white snowflake", "snowflakes", "snowflake"}),
        "The white snowflakes are delicately embroidered with " +
        "white thread. They are intricate and very life like, and " +
        "are scattered all over the cloak.\n");
    add_item("tag", "Some instructions are embroidered onto it. " +
        "Perhaps you should read it.\n");
    add_cmd_item(({"tag","instructions"}), "read", "@@read_sign@@");

    set_default_armour(SAC,SAT,SAM,0);
    add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_ARMOUR(SAC,SAT) + random(101));
    add_prop(OBJ_I_VALUE, 200);

    set_keep(1);
}

void init()
{
    ::init();
    add_action("cloak_spin", "clspin");
    add_action("cloak_spin", "cls");
    add_action("cloak_bow", "clbow");
    add_action("cloak_bow", "clb");
    add_action("cloak_curt", "clcurtsey");
    add_action("cloak_curt", "clc");
    add_action("cloak_pick", "clpick");
    add_action("cloak_pick", "clp");
}

string
read_sign()
{
    return "You may do the following while wearing the cloak:\n" +
        "\t(cls)pin    - Spin around\n" +
        "\t(clb)ow     - Bow before someone\n" +
        "\t(clc)urtsey - Curtsey before someone\n"+
        "\t(clp)ick    - Pick some dirt off your cloak\n";
}


int
cloak_spin() 
{
    if(!query_worn())
    {
        write("You must be wearing the " +short()+".\n");
        return 1;
    }

    write("You spin around, the cloak flaring out behind you in " +
        "a blur of white snowflakes.\n");
    say(QCTNAME(TP) + " spins around, " +HIS_HER(TP)+" " +short()+
        " flaring out behind " +HIM_HER(TP)+" in a blur of white " +
        "snowflakes.\n");
    return 1;
}

int
cloak_curt(string str)
{
    object *oblist;

    if(!query_worn())
    {
        write("You must be wearing the " +short()+".\n");
        return 1;
    }
    
    if(!strlen(str)) /* no string supplied */
    {
    	write("You smile demurely while stepping forward with one " +
            "foot, bending your knees briefly before everyone.\n");
	    all(" smiles demurely while stepping forward with one foot, " +
            "bending " +HIS_HER(TP)+" knees before you briefly.");
	    return 1;
    }

    oblist = parse_this(str, "[before] %l");

    if(!sizeof(oblist))
    {
    	write("Curtsey to who?\n");
	    return 1;
    }

    actor("You smile demurely while stepping forward with one foot, "+ 
        "bending your knees briefly before",oblist,".");
    target(" smiles demurely while stepping forward with one foot, " +
        "bending at the knees before you.", oblist);
    all2act(" smiles demurely while stepping forward with one foot, " +
        "bending at the knees before",oblist,".");
    return 1;
}

int
cloak_bow(string str)
{
    object *oblist;

    if(!query_worn())
    {
        write("You must be wearing the " +short()+".\n");
        return 1;
    }
    
    if(!strlen(str)) /* no string supplied */
    {
    	write("You smile broadly, and flourish a magificent bow " +
            "before everyone.\n");
	    all(" smiles broadly and flourishes a magnificent bow " +
            "before you.");
	    return 1;
    }

    oblist = parse_this(str, "[before] %l");

    if(!sizeof(oblist))
    {
    	write("Bow to who?\n");
	    return 1;
    }


    actor("You smile broadly and flourish a magnificent bow before",
        oblist,".");
    target(" smiles broadly and flourishes a magnificent bow " +
        "before you.", oblist);
    all2act(" smiles broadly and flourishes a magnificent bow " +
        "before",oblist,".");
    return 1;
}

int
cloak_pick() 
{
    if(!query_worn())
    {
        write("You must be wearing the " +short()+".\n");
        return 1;
    }

    write("You pick some dirt off of your "+short()+" and flick " +
        "it away from you.\n");
    say(QCTNAME(TP) + " picks some dirt off " +HIS_HER(TP)+" " +
    short()+" and flicks it away from "+HIM_HER(TP)+"self.\n");
    return 1;
}