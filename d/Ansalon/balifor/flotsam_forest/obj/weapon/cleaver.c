/* Please do not clone this item to any other npc
 * other than Shale. It is to be used in the Neidar
 * guru quest.
 * - Arman.
 */

/* Modified by Navarre 24th June 2006,
 * Added not wieldable by goblins to the magical info
 * 
 * Modified by Navarre 25th July 2007.
 * Removed OBJ_I_NO_SELL prop, as we have a /lib/keep prop.
 * One of them had to go, I don't see why cleavers should
 * have the special treatment of not being sold.
 *
 * Navarre June 28th 2011, Changed query_race to query_race_name
 */

inherit "/std/weapon";
inherit "/lib/keep";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"
#include <ss_types.h>
#include <filter_funs.h>
#include "/d/Ansalon/common/defs.h"

#define WEAPON_HIT 40
#define WEAPON_PEN 40

object wielder;

void
create_weapon()
{
    set_name("cleaver");
    add_name("axe");
    add_pname(({"axes","cleavers"}));
    set_adj("mighty");
    add_adj("dwarven");
    add_adj("metal");  /* added by Gorboth, July 2007 */
    set_short("mighty dwarven cleaver");
    set_long(break_string("A mighty dwarven cleaver. Being " +
	"very sharp and well balanced, this axe is deadly in " +
	"the right hands. This weapon was forged long ago before " +
	"the cataclysm by dwarven priests of Reorx and is " +
	"an item treasured by all the dwarven nations. During " +
	"the Dwarfgate Wars, weapons like this were used by the " +
	"great soldiers of the Daewar clan, and thus many still " +
	"lie with their long dead owners near the site of the " +
	"ruins of Skullcap.",75) + "\n");

    set_hit(WEAPON_HIT);
    set_pen(WEAPON_PEN);
    set_wt(W_AXE);
    set_dt(W_SLASH | W_BLUDGEON);
    set_hands(W_ANYH);
    set_wf(TO);
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC,({50,"enchantment"}));
    add_prop(MAGIC_AM_ID_INFO,({"The mighty dwarven cleaver has been " +
	"enchanted by priests of Reorx long ago. " +
        "Being blessed, this weapon cannot be wielded by goblins. "+
	"The enchantments have made it so that the cleaver " +
	"does the damage of an excellent two-handed waraxe.\n",1}));

    add_prop(OBJ_I_WEIGHT, 8000);
    add_prop(OBJ_I_VOLUME, 4000);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(WEAPON_HIT,WEAPON_PEN));

    seteuid(getuid(TO));
}

void
wield_message1()
{
    if (E(TO) != wielder)
    {
	    return;
    }
    
    if (wielder->query_race_name() != "dwarf")
	{
        return;
    }
    
    wielder->catch_msg("You raise the mighty dwarven cleaver into the air " +
                       "and roar praise to Reorx, God of Dwarves!\n");

    tell_room(E(wielder),QCTNAME(wielder) +
      " raises the mighty dwarven cleaver into the air and roars " +
      "praise to Reorx!\n",wielder);
}

mixed
wield(object what)
{
    if (TP->query_race_name() == "goblin" ||
        TP->query_race_name() == "hobgoblin")
    {
        return "A deep earthy voice enters your head, saying: " +
               "This is a blessed weapon of the dwarves! You cannot " +
               "wield it!\n";
    }
    wielder = TP;
    set_alarm(1.0, 0.0, "wield_message1");

    return 0;
}
