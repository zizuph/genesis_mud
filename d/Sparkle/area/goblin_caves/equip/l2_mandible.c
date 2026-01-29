/*
 * spider mandible on level 2
 * - Boreaulam, Jan 2015
 */
#pragma save_binary
#pragma strict_types

inherit "/std/weapon";

#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>

int poisoned;

/*
 * Function name:        create_weapon
 * Description  :        constructor for the object
 */
void
create_weapon()
{

    set_name("mandible");
	set_adj("dangerous-looking");
    add_adj("spider");
    set_short("dangerous-looking spider mandible");
    set_long("@@long_desc");

	int wc = 25;
    set_hit(wc);
    set_pen(wc);
    set_wt(W_KNIFE);
    set_dt(W_IMPALE);

    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(wc, wc) + random(200));
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(wc, W_KNIFE));
	
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(OBJ_S_WIZINFO, "This mandible is leftover from the spider " +
	         "located in ../npcs/l2_spider.c. It holds a poison.\n");
    add_prop(MAGIC_AM_ID_INFO,({"This mandible has a magical aura " +
        "surrounding it.\n", 5, "Sometimes the mandible will retain a " +
        "small amount of venom on the tip.\n", 50}));
    add_prop(MAGIC_AM_MAGIC, ({ 75, "enchantment" }));

    set_hands(W_ANYH);
	
	poisoned = 3;
} /* create_weapon */

string
long_desc()
{
	if(poisoned)
		return "This mandible is quite large, so large that you have an " +
            "involuntary shudder thinking about how big the spider must have " +
            "been! You think that you could grasp the mandible in your hand " +
            "like a knife and use it as a weapon if you needed. You also " +
            "notice a small drop of venom coating the tip of the mandible.\n";
	else
		return "This mandible is quite large, so large that you have an " +
            "involuntary shudder thinking about how big the spider must have " +
            "been! You think that you could grasp the mandible in your hand " +
            "like a knife and use it as a weapon if you needed.\n";
}

public varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit, int dam)
{
    object poison;

    if (poisoned && !random(6))
    {
		seteuid(getuid());
		poison = clone_object("/std/poison_effect");
		if (poison)
		{
			object poison = clone_object("/std/poison_effect.c");
			poison->set_strength(15);
			poison->set_time(60);
			poison->set_interval(10);
			poison->move(enemy);
			poison->start_poison();
			enemy->catch_tell("You feel a searing hot flash as your skin is " +
                "scratched by the venom tipped mandible.\nYou have been " +
                "poisoned!");
			poisoned--;
			return 0;
		}
    }
    return ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
}


