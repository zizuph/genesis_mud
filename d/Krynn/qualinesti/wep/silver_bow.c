/* silver_bow.c
 * A longbow used by Qualthas.
 *
 * Blizzard, 12.05.2003
 * 24.6.2004 various fixes and cleaning by Milan
 *
 * Arman 02/2022
 * Added the bow as a spell enhancer.
 */

#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>
#include "/d/Krynn/common/defs.h"
#include "../local.h"

inherit WEP+"elven_bow";
inherit "/d/Genesis/specials/new/lib/spell_enhancer";

public void
create_bow()
{
    add_name("longbow");
    set_adj(({"slender", "long", "elven", "silvery"}));
    set_short("slender silvery longbow");
    set_long("This beautifully-made longbow appears to be made of " +
        "glimmering Silverwood, a sure sign of Elven orgin. It has " +
        "elegant, sinuous runes carved into its length, and although it " +
        "is tightly strung, it is remarkably easy to draw.\n");
    add_item("runes",
        "The longbow has elegant runes carved into its length. However, " +
        "they seem to be only decoration.\n");
        
    add_prop(OBJ_I_WEIGHT, 800);
    add_prop(OBJ_I_VOLUME, 3000);
    add_prop(OBJ_I_VALUE, 2100);
    set_wf(TO);
    add_prop(OBJ_S_WIZINFO,
        "This is a longbow wielded by Qualthas as a replacement for " +
        "singing elven lonbow. It doesnt really have any special powers but " +
        "because bows made by Qualinesti elves are very deadly " +
        "they may be considered magical. It will dull a bit slower too.\n");

    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 30, "enchantment" }) );
    add_prop(MAGIC_AM_ID_INFO,
        ({ "This longbow has been made by Qualinesti elves. It is really " +
        "deadly.\n", 10,
        "Qualinesti elves are familiar with magic, so weapons of their " +
        "making are very often enchanted.\n", 20 }) );

    set_hit(46);
    set_magic_spellpower(47);
    set_pen(48);
    set_likely_dull(5);
    set_likely_break(6);

    seteuid(getuid(TO));
}

void
wield_check()
{
    if ( query_wielded()->query_npc() )
    {
        set_hit(54);
        set_pen(56);
        query_wielded()->update_weapon(TO);
    }
}

mixed
wield(object ob)
{
    if ( !interactive(TP) )
    {
        set_alarm(1.0, 0.0, wield_check);
        set_secondary_wep_cmd("elf_wield_sec_weapon");
    }
	return 0;
}
  
mixed
unwield(object what)
{
    set_hit(46);
    set_pen(48);
    query_wielded()->update_weapon(TO);
    return 0;
}
