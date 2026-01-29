/*
 * Lucius May 2009: Cleaned and updated, moved from /d/Terel/dark/
 */
#pragma strict_types

inherit "/std/weapon";
inherit "/lib/keep";

#include <stdproperties.h>
#include <wa_types.h>

public void
create_weapon(void)
{
    set_keep(1);
    set_name("spear");
    set_adj(({ "obsidian", "silver-tipped" }));
    set_short("obsidian silver-tipped spear");
    set_pshort("obsidian silver-tipped spears");
    set_long("A magnificant spear made of obsidian. There are two "+
	"leather grips fastened with silver rings along the shaft. "+
	"The foot long spear head is made of pure silver. Jagged "+
	"rivets run the length of the shaft like lightning bolts "+
	"streaking to the tip.\n");

    set_default_weapon(40, 45, W_POLEARM, W_IMPALE, W_BOTH, this_object());

    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC, ({55, "enchantment"}));
    add_prop(MAGIC_AM_ID_INFO, ({
	"The "+short()+" can only be wielded by those capable of evil.\n",70,
	"The "+short()+" will make the dark clearer for those who can "+
	"wield it.\n", 90}));
    add_prop(OBJ_S_WIZINFO,
	"This spear can only be wielded by neutral or lower " +
	"aligned players. It grants 2 levels of see in dark.\n");
}

public int
wield(object wep)
{
    if (this_player()->query_alignment() > 40)
    {
	this_player()->heal_hp(-5);
	write("The spear glows bright red and burns you.\n");
	return -1;
    }

    wielder->add_prop(LIVE_I_SEE_DARK,
	wielder->query_prop(LIVE_I_SEE_DARK) + 2);

    return 0;
}

public int
unwield(object wep)
{
    wielder->add_prop(LIVE_I_SEE_DARK,
	wielder->query_prop(LIVE_I_SEE_DARK) - 2);

    return 0;
}
