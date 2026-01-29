/*
 * cloak for the Drow
 * -- Finwe, May 2006
 */

#pragma save_binary

inherit "/std/armour";
inherit "/cmd/std/command_driver";

#include "/d/Faerun/defs.h"
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
#define SSHORT "smooth black cloak"
#define SPSHORT "smooth black cloaks"

create_armour()
{
    set_name(SNAME);
    add_adj(({"smooth","black"}));
    set_short(SSHORT);
    set_pshort(SPSHORT);
    set_long("This "+short()+" is full length, reaching nearly to the ground. The cloak is woven from spider silks. It is soft and lightweight, and seems to shimmer in the darkness. A black gold chain holds the cloak on your shoulder. A tag is sewn into the cloak.\n"); 

    add_item(({"gold chain", "black gold chain"}),
        "The chain is made of twisted gold. It reaches from one " +
        "lapel to the other, holding the cloak on.\n");
    add_item("label", "Some instructions are embroidered onto it. " +
        "Perhaps you should read it.\n");
    add_cmd_item("label", "read", "@@read_sign@@");

    set_default_armour(SAC,SAT,SAM,0);
    add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_ARMOUR(SAC,SAT) + random(101));
    add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(SAC) - random(11));
//    add_prop(OBJ_I_VOLUME,F_VOLUME_ARMOUR);
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
}

string
read_sign()
{
    return "\nYou may do the following while wearing the cloak:\n" +
        "\t(cls)pin    - Spin around\n" +
        "\t(clb)ow     - Bow before someone\n" +
        "\t(clc)urtsey - Curtsey before someone\n" +
        "\t(clp)ick    - Pick some dirt off your cloak\n\n";

}


int
cloak_spin() 
{
    if(!query_worn())
    {
        write("You must be wearing the " +short()+".\n");
        return 1;
    }

    write("You spin around, the " + short() + " flaring out behind you.\n");
    say(QCTNAME(TP) + " spins around, " +HIS_HER(TP)+" " +short()+" flaring out behind " +HIM_HER(TP)+" .\n");
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
    	write("You smile demurely, and steps forward with one foot, bending your knees briefly before everyone.\n");
	    all(" smiles demurely and steps forward with one foot, bending " +HIS_HER(TP)+" knees before you briefly.");
	    return 1;
    }

    oblist = parse_this(str, "[before] %l");

    if(!sizeof(oblist))
    {
    	write("Bow to who?\n");
	    return 1;
    }


    actor("You smile demurely and step forward with one foot, bending your knees briefly before",oblist,".");
    target(" smiles demurely and steps forward with one foot, bending at the knees before you.", oblist);
    all2act(" smiles demurely and steps forward with one foot, bending at the knees before",oblist,".");
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


    actor("You smile broadly and flourish a magnificent bow before",oblist,".");
    target(" smiles broadly and flourishes a magnificent bow " +
        "before you.", oblist);
    all2act(" smiles broadly and flourishes a magnificent bow " +
        "before",oblist,".");
    return 1;
}
