inherit "/d/Kalad/std/weapon";
#include "/d/Kalad/defs.h"
#include <poison_types.h>
int poison_used;
/* by Antharanos */
/* fixed a wrong syntax in MAGIC_AM_ID_INFO, Cherek July 2016 */

void
create_weapon()
{
	::create_weapon();
	set_name("whip");
	set_adj("large");
	add_adj("three-headed");
	add_adj("snake");
	set_long("@@long_desc");
	set_hit(25);
	set_pen(25);
	set_wf(TO);
	set_wt(W_CLUB);
	set_dt(W_BLUDGEON);
	add_prop(OBJ_M_NO_BUY,1);
	add_prop(OBJ_I_IS_MAGIC_WEAPON,1);
	add_prop(OBJ_S_WIZINFO,"This whip, found on the matron mother of "+
	"House Kilsek in the drow city of Undraeth "+
	"(/d/Kalad/common/wild/pass/drow/npc/h5_matron) "+
	"will, if wielded by a female with wisdom over 132 "+
	"and club over 49, have its hit/pen increased from its "+
	"normal 25/25 to 40/40. When it isn't wielded "+
	"or is wielded by anyone else, it will only have its normal "+
	"hit/pen. Also, this player will be shocked for 750hp "+
	"of damage.\n");
	add_prop(MAGIC_AM_ID_INFO,({"The whip is magical.\n", 5, "The "+
	"whip's aura indicates something concerning gender, wisdom and "+
	"clubs.\n", 25, "Only those of superior gender, great wisdom and "+
	"great skill may reap the benefits of this whip.\n", 51}));
	add_prop(MAGIC_AM_MAGIC, ({ 50, "enchantment" }));
	add_prop(OBJ_I_VALUE,2000);
	add_prop(OBJ_I_WEIGHT,6000);
	add_prop(OBJ_I_VOLUME,6000);
	poison_used = 0;
}
string
long_desc()
{
	if(poison_used)
	return "A vicious-looking whip that possesses living snakes "+
	"in place of hardened leather! The handle itself is composed of "+
	"solid adamantine, which has been decorated with numerous "+
	"carvings depicting the Spider Queen, Lolth.\n";
	else
	return "A vicious-looking whip that possesses living snakes "+
	"in place of hardened leather! The handle itself is composed of "+
	"solid adamantine, which has been decorated with numerous "+
	"carvings depicting the Spider Queen, Lolth. Snake venom can be "+
	"seen dripping from the mouths of the spiders.\n";
}
public varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit)
{
	object poison;
	if (!poison_used && !random(6))
	{
		setuid(); seteuid(getuid());
		poison = clone_object("/std/poison_effect");
		if (poison)
		{
			if (random(3))
			poison_used = 1;
			poison -> move(enemy);
			poison -> set_time(1200);
			poison -> set_interval(50);
			poison -> set_strength(300);
			poison -> set_damage(({POISON_HP, 300, POISON_STAT, SS_CON}));
			poison -> start_poison();
			return 0;
		}
		else
		write("Failed to load poison for some reason.\n");
	}
	return 0;
}
mixed
wield(object what)
{
	if(TP->query_gender() == 1)
	if(TP->query_base_stat(SS_WIS) > 132)
	if(TP->query_skill(SS_WEP_CLUB) > 49)
	{
		write("The large three-headed snake whip momentarily "+
		"flashes with a brilliant red light.\n");
		say(QCTNAME(TP) + "'s large three-headed snake whip "+
		"momentarily flashes with a brilliant red light.\n");
		what -> set_hit(40);
		what -> set_pen(40);
		E(TO)->update_weapon(TO);
		return 0;
	}
	write("The snakes on the large three-headed snake whip come "+
	"alive and attack you, inflicting deleterious wounds!\n");
	say(QCTNAME(TP) + " is suddenly attacked by the snakes from "+
	"" + TP->query_possessive() + " large three-headed snake whip!\n");
	TP->heal_hp(-750);

/*
   TP->catch_msg("You notice something terribly wrong with yourself...\n"+
      "It appears as if you are no longer the person you once were.\n");
   TP->set_gender(2);
*/

        if(TP->query_hp() <= 0)
        TP->do_die(TO);
        what -> set_hit(25);
        what -> set_pen(25);
        E(TO)->update_weapon(TO);
        return 0;
}
mixed
unwield(object what)
{
	what -> set_hit(25);
	what -> set_pen(25);
	E(TO)->update_weapon(TO);
	return 0;
}
