/* cuirasss.c: The gladiator guild Overseer item: Serpine, 4/29/95.
*/


inherit "/std/armour";
#include "defs.h"
#include <wa_types.h>
#define IS_GLAD_OVERSEER "_is_glad_overseer_"

void create_armour()
{

    set_name(({ "cuirasse", CUIR_ID, COUN_CUIR_ID }));
    set_pname("cuirasses");
    set_short("silver cuirasse");
    set_pshort("silver cuirasses");
    add_adj("silver");
    set_long("Made of silver, a rare and expensive metal in Athas, the "+
             "cuirasse shows you to be a Lesser Overseer of the "+
             "Gladiators of Athas.\nYou may use 'help gladiator' "+
             "or 'help overseer' for more information.\n");

    set_default_armour(0, A_NECK);
   
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_M_NO_DROP, "You can't bring yourself to drop it.\n");
    add_prop(OBJ_I_WEIGHT, 670);
    add_prop(OBJ_I_VOLUME, 20); 
}

int
query_recover()
{
    return 0;
}


void enter_env(object env, object from)
{
    ::enter_env(env, from);
    if (!IS_MEMBER(env) && !IS_WIZ(env))
        remove_object();
    set_alarm(4.5, 0.0, "auto_wear");
}

void
auto_wear()
{
    wear_me();
    TP->add_prop(IS_GLAD_OVERSEER,1);
}

init()
{
    ::init();
    add_action("help", "help");
//    add_action("wear_cuirasse", "wear");
}
/*
int
wear_cuirasse(string str)
{
    notify_fail("wear what?\n");
    if (!str)
        return 0;

    if (str == "cuirasse")
    {
        TP->add_prop(IS_GLAD_OVERSEER,1);
        return 1;
    }   

    return 0;
}
*/
int 
help(string str)
{
    if (!(str=="overseer")) return 0;
    seteuid(getuid());
    cat(GLAD_HELP+"c_help");
    return 1;
}

/* report_kill is a legacy stub, to be removed when we know
   things won't explode.                                     */
void report_kill(int which) {}
