 /*    Black gauntlets for the water krougs

    coder(s):   Glykron
    history:
                24. 5.95    changed for water krougs          Digit
                17. 6.94    euid added                      Glykron
                25. 2.92    recovery added                  Glykron
                 9. 2.92    header added                    Glykron

*/

inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

int
detach(string str)
{
    object tp;

    if (str != "gauntlets" && str != "black gauntlets")
	return 0;

    tp = TP;
    move(environment(tp)); /* temporary */
    clone_object(SEA_ARMOURS+"lgauntlet")->move(tp);
    clone_object(SEA_ARMOURS+"rgauntlet")->move(tp);
    remove_object();
    write("Ok.\n");
    return 1;
}

void
init()
{
    ::init();
    add_action("detach", "detach");
    add_action("detach", "divide");
    add_action("detach", "split");
    add_action("detach", "separate");
}

void
create_armour()
{
    set_name("gauntlets");
    set_pname("gauntlets");
    set_adj("black");
    set_short("pair of black gauntlets");
    set_pshort("pairs of black gauntlets");
    set_long("This is a pair of black gauntlets.\n");
    set_ac(20);
    set_at(A_L_HAND | A_R_HAND);
    set_am( ({ 2, 0, -2 }) );
    add_prop(OBJ_I_WEIGHT, 5000);
    add_prop(OBJ_I_VOLUME, 5000);
    seteuid(getuid());
}

string
query_recover()
{
    return MASTER + ":" + query_arm_recover();
}

void
init_recover(string arg)
{
    init_arm_recover(arg);
}
