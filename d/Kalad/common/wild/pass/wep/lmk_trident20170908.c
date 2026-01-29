/* 
 * /d/Kalad/common/wild/pass/wep/lmk_trident.c
 * Purpose    : The lizard king's trident. It is magical, see wizinfo
 * Located    : Used by the lizard king ~pass/npc/liz_king.c
 * Created By : Antharanos  ??.??.??
 * Modified By: 
 * First Modif: 
 */ 

inherit "/d/Kalad/std/weapon";

#include "/d/Kalad/defs.h"
#include <poison_types.h>

int poison_used;

void
create_weapon()
{
    ::create_weapon();
    set_name("trident");
    set_adj("great");
    add_adj("war");
    set_pname("tridents");
    set_short("great war trident");
    set_pshort("great war tridents");
    set_long("@@long_desc");
    set_hit(36);
    set_pen(36);
    set_wf(TO);
    set_hands(W_BOTH);
    set_wt(W_POLEARM);
    set_dt(W_IMPALE);
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(OBJ_S_WIZINFO, "This trident, found on the lizard man king "+
      "(/d/Kalad/common/wild/pass/npc/liz_king) will, when wielded by "+
      "someone with strength greater than 125, have its hit/pen increased "+
      "from its normal 36/36 to 48/48. Resultantly, when the weapon is "+
      "not wielded or is wielded by someone with a strength of 125 or less, "+
      "it will only have its normal hit/pen. Anyone with strength less than "+
      "126 will also be shocked for 500 hp of damage, if they attempt to "+
      "wield the trident.\n");
    add_prop(MAGIC_AM_ID_INFO,({"The trident is magical.\n", 5,
	"The trident's aura indicates something concerning strength.\n", 25,
	"Only the powerful will gain full usage of the trident's power.\n", 51}));
    add_prop(MAGIC_AM_MAGIC, ({ 75, "enchantment" }));
    add_prop(OBJ_I_VALUE, 960);
    add_prop(OBJ_I_WEIGHT, 9000);
    add_prop(OBJ_I_VOLUME, 9000);
    add_prop(OBJ_M_NO_BUY, 1);

    poison_used = 0;
}

string
long_desc()
{
    if (poison_used)

	return "A huge three-tyned trident of war, forged from some powerful "+
	"alloy of steel. The obsidian shade of the weapon seems almost "+
	"unnatural in origin.\n";
    else
	return "A huge three-tyned trident of war, forged from some powerful "+
	"alloy of steel. The obsidian shade of the weapon seems almost "+
	"unnatural in origin. A colorless liquid coats the three tynes of "+
	"the trident.\n";
}

public varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit, int dam)
{
    object poison;

    if (!poison_used && !random(6))
    {
	seteuid(getuid());
	poison = clone_object("/std/poison_effect");
	if (poison)
	{
	    if(random(3))
		poison_used = 1;
	    poison->move(enemy);
	    poison->set_time(300);
	    poison->set_interval(50);
	    poison->set_strength(300);
	    poison->set_damage(({POISON_FATIGUE, 400, POISON_STAT, SS_CON}));
	    poison->start_poison();
	    return 0;
	}
	else
	    write("Failed to load poison for some reason.\n");
    }
    return ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
}

mixed
wield(object what)
{
    if(TP->query_base_stat(SS_STR) > 125)
    {
	write("The great war trident seems to pulse within your grip.\n");
	say(QCTNAME(TP) + "'s great war trident seems to pulse in " + TP->query_possessive() + " grip.\n");
	what->set_hit(48);
	what->set_pen(48);
	E(TO)->update_weapon(TO);
	return 0;
    }
    write("The great war trident shocks you!\n");
    say(QCTNAME(TP) + " is shocked by " + TP->query_possessive() + " great war trident.\n");
    TP->heal_hp(-500);
    what->set_hit(36);
    what->set_pen(36);
    return 0;
}

mixed
unwield(object what)
{
    what->set_hit(36);
    what->set_pen(36);
    return 0;
}

public string
query_recover()
{
    return MASTER + ":" + sprintf("%d", poison_used) + query_wep_recover();
}

public void
init_recover(string arg)
{
    string s1, s2;

    sscanf(arg, "%s#%s", s1, s2);
    poison_used = atoi(s1);
    init_wep_recover(s2);
}
