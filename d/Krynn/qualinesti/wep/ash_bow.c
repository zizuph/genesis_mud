/* ash_bow.c
 * A longbow used by Qualinesti elves.
 *
 * Blizzard, 12.05.2003
 * 24.6.2004 various fixes and cleaning by Milan
 */

#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>
#include "/d/Krynn/common/defs.h"
#include "../local.h"

inherit WEP+"elven_bow";

public void
create_bow()
{
    add_name("longbow");
    set_adj(({"sleek", "ashwood", "ash", "long"}));
    set_short("sleek ashwood longbow");
    set_long("This sleek and very light bow is made out of a long branch " +
        "of ash wood. It is tightly-strung, and has a fair amount of " +
        "stopping power. The bows made by elves are especially " +
        "tailored for their warriors, and the process used is carefully " +
        "guarded, but the result is well known: any bow of Qualinesti " +
        "origin can be fired faster than is possible with a normal one.\n"); 

    add_prop(OBJ_I_WEIGHT, 900);
    add_prop(OBJ_I_VOLUME, 3250);
    add_prop(OBJ_I_VALUE, 2000);
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    set_wf(TO);
    add_prop(OBJ_S_WIZINFO,
        "This longbow was made by Qualinesti elves and thus it has " +
        "increased hit and pen.\n");

	add_prop(MAGIC_AM_MAGIC, ({ 20, "enchantment" }) );
    add_prop(MAGIC_AM_ID_INFO,
        ({ "This longbow has been made by Qualinesti elves. It is really " +
        "deadly.\n", 10,
        "Qualinesti elves are familiar with magic, so weapons of their " +
        "making are very often enchanted.\n", 20 }) );

    set_hit(44);
    set_pen(45);
    
    seteuid(getuid(TO));
}

void
wield_check(object ob)
{
    if ( query_wielded()->query_npc() )
    {
        set_hit(54);
        set_pen(55);
        query_wielded()->update_weapon(TO);
    }
}

mixed
wield(object ob)
{
    if ( !interactive(TP) )
    {
        set_alarm(1.0, 0.0, &wield_check(TO));
        set_secondary_wep_cmd("elf_wield_sec_weapon");
    }
    return 0;
}

mixed
unwield(object what)
{
    set_hit(44);
    set_pen(45);
    query_wielded()->update_weapon(TO);
    return 0;
}
