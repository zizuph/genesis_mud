/*
 * Whip used by Aysha of the Brix gang.
 *
 * Mortis 05.2006
 *
 * 2021-01-30 - Cotillion
 * - Removed command_driver inherit
 */

inherit "/std/weapon";
inherit "/lib/keep";
inherit "/lib/commands";

#include "../../local.h"
#include <wa_types.h>
#include <macros.h>

create_weapon()
{
	set_name("whip");
	add_name("bullwhip");
	set_adj("short");
	add_adj("leather", "bull");
	set_short("short leather whip");
	set_long("Capable of delivering loud, painful slashes, this common "
	+ "bullwhip has been braided from rough leather into a usable weapon.\n");

	set_hit(30);
	set_pen(15);
	set_wt(W_CLUB);
	set_dt(W_SLASH);
	set_hands(W_ANYH);
}

void
init()
{
    ::init();
    ADA("whip");
}

int
whip(string str)
{
    string *how, wnoise, wloc, wshort = short();
    object *oblist, amiwielded;

    how = parse_adverb_with_space(str, "loudly", 1);
    oblist = parse_this(how[0], "%l");
    wnoise = one_of_list(({"WHAP", "CRACK", "WHIPPOW", "SMACK", "SNAKK"}));

    NF("You must be wielding your " + wshort + " in order to make with "
        + "the whipping et al.\n");
    if (!(amiwielded = query_wielded()))
        return 0;

    if (!sizeof(oblist))
    { 
        write("You crack your whip" + how[1] + " in the air.\n"	+ wnoise
            + "!\n");
        allbb(" cracks " + HIS(TP) + " whip" + how[1] + " in the air.\n"
            + wnoise + "!");
        return 1;
    }

    actor("You whip", oblist, how[1] + " with your " + wshort + ".\n" + wnoise
        + "!");
    target(" whips you" + how[1] + " with " + HIS(TP) + " " + wshort + ".\n"
        + wnoise + "!", oblist);
    all2act(" whips", oblist, how[1] + " with " + HIS(TP) + " " + wshort +
        ".\n" + wnoise + "!"); 

    return 1;
}
