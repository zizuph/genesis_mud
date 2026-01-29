/*
 * A travel cloak
 * -- Finwe, September 2002
 * Updated by Gronkas, August 1, 2016 to fix typos
 */

#pragma save_binary

inherit "/std/armour";
inherit "/cmd/std/command_driver";

#include "defs.h"
#include <cmdparse.h>
#include <filter_funs.h>
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <std.h>
#include <stdproperties.h>
#include <wa_types.h>

#define SAC 17
#define SAT A_ROBE
#define SAM ({0,1,0})
#define SNAME "cloak"
#define SADJ "dark travellers"
#define SSHORT SADJ + " cloak"
#define SPSHORT SADJ + " cloaks"

create_armour()
{
    setuid(); seteuid(getuid());

    set_name(SNAME);
    add_adj(({"dark","travellers"}));
    set_short(SSHORT);
    set_pshort(SPSHORT);
    set_long("This "+short()+" is full length, reaching nearly to the " +
        "ground. It is made of heavy, dark fabric and sewn expertly. " +
        "A silver chain is fixed onto the cloak to fasten it across " +
        "the shoulders. A label is sewn into the cloak.\n"); 

    add_item(({"silver chain"}),
        "The chain is made of twisted silver. It stretches from one " +
        "shoulder to the other to hold the cloak fast.\n");
    add_item("label", "Some instructions are embroidered onto it. " +
        "Perhaps you should read it.\n");
    add_cmd_item(({"label","instructions"}), "read", "@@read_sign@@");

    set_default_armour(SAC,SAT,SAM,0);
    add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_ARMOUR(SAC,SAT) + random(101));
//    add_prop(OBJ_I_VALUE, 90);
//    add_prop(OBJ_I_VOLUME,F_VOLUME_ARMOUR);
}

void init()
{
    ::init();
    add_action("cloak_spin", "spin");
    add_action("cloak_pick", "clean");
    add_action("cloak_bow", "bow");

}

string
read_sign()
{
    return "\n" + 
        "=======================================================\n" +
        "|| You may do the following while wearing the cloak: ||\n" +
        "||   spin    - Spin around                           ||\n" +
        "||   clean   - Clean some dirt off your cloak        ||\n" + 
        "||   bow     - Executes a bow to everyone            ||\n" +
        "=======================================================\n\n";
}


int
cloak_spin() 
{
    if(!query_worn())
    {
        write("You must be wearing the " +short()+".\n");
        return 1;
    }

    write("You spin around, the cloak flaring out behind you.\n");
    say(QCTNAME(TP) + " spins around, " +HIS_HER(TP)+" " +short()+
        " flaring out behind " +HIM_HER(TP)+".\n");
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

    write("You clean some dirt off your "+short()+" and flick " +
        "it away from you.\n");
    say(QCTNAME(TP) + " cleans some dirt off " +HIS_HER(TP)+" " +
    short()+" and flicks it away from "+HIM_HER(TP)+"self.\n");
    return 1;
}


int
cloak_bow() 
{
    if(!query_worn())
    {
        write("You bow gracefully.\n");
        say(QCTNAME(TP) + " bows gracefully.\n");
        return 1;
    }

    write("You draw the cloak across your chest and flourish a graceful bow.\n");
    say(QCTNAME(TP) + " draws the " + short() + " across " + HIS_HER(TP) + 
        " chest and flourishes a graceful bow.\n");
    return 1;
}
