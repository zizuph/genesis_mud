
inherit "/std/weapon";
inherit "/lib/keep";

#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"

create_weapon()
{
    set_name(({"broadsword","_flotsam_r_sword_"}));
    add_name("weapon");
    add_name("sword");
    set_pname("broadswords");
    add_pname("swords");
    add_pname("weapons");
    set_adj("solamnian");
    add_adj("metal");  /* it is, isn't it? -Gorboth */
    set_short("solamnian broadsword");
    set_pshort("solamnian broadswords");
    set_long("A keen, two-edged broadsword, " +
      "beautifully tooled with the markings of all three Solamnian " +
      "orders along its blade. This blade is well over 2000 years " +
      "old, yet its edges are still as sharp as if it had been " +
      "forged yesterday.\n");
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC,({ 10, "enchantment"}));
    add_prop(MAGIC_AM_ID_INFO,({"This weapon was crafted " +
	"long ago during the Age of Right, after the formation " +
	"of the order known as the Knights of Solamnia. One " +
	"was crafted for " +
	"each of Vinas Solamnus's generals, this particular blade " +
	"probably coming from the Trueheart or Solanius lines, " +
	"whose family swords were lost during the Third " +
	"Dragonwar. \n", 5, "When wielded by a knight of honour " +
	"this sword becomes more effective in battle.\n", 50}));
    set_default_weapon(35,35,W_SWORD,W_SLASH | W_IMPALE,W_ANYH);
    set_wf(TO);
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_VOLUME, 3600);
    add_prop(OBJ_I_WEIGHT, 3500);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(35,35));
}

void
knight_wield(object who)
{
    who->catch_tell("As you wield the solamnian " +
      "broadsword, you get a feeling of nostalgia " +
      "as you think of all the glorious deeds and " +
      "heroic battles fought by fellow knights of " +
      "ages past.\n");

    set_hit(42);
    set_pen(42);
    who->update_weapon(TO);
}

void
default_wield(object who)
{
    set_hit(35);
    set_pen(35);
    who->update_weapon(TO);
}

void
deside_wield()
{
    object who = query_wielded();
    if (!objectp(who))
	return;

    if (who->query_guild_member("Solamnian Knights"))
	knight_wield(who);
    else
	default_wield(who);
}

mixed
wield(object what)
{
    set_alarm(1.0, 0.0, deside_wield);
    return 0;
}
