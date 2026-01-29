/* created by Aridor 04/19/94 */

#include "../defs.h"
#include <wa_types.h>
#include <macros.h>
#include <stdproperties.h>

inherit M_FILE

#define STATUE "/d/Krynn/common/monster/stonecorpse.c"

int imdead = 0;

void
create_baaz() { }


void
create_krynn_monster()
{
    int i;

    add_name("baaz");
    set_race_name("draconian");
    add_prop(LIVE_I_NO_CORPSE, 1);
    add_prop(OBJ_I_RES_ACID, 50);
    add_prop(OBJ_I_RES_FIRE, 50);
    add_prop(MAGIC_AM_MAGIC, ({ 100, "transmutation"}));

    set_adj("narrowfaced");

    create_baaz();

    i = query_average_stat();
    i = i*i/10;
    set_alignment((i>950) ? (-1000) : (-i - 50));
    set_knight_prestige(i + 100);

}


public void
do_die(object killer)
{
	object corpse;
        object wep;

	if (imdead || query_hp() > 0)
		return;
	imdead = 1;
	if (!killer)
		killer = previous_object();

	if (!query_combat_object()) combat_reload();
	query_combat_object()->cb_death_occured(killer);

	this_object()->notify_death(killer);
    
	if (living(killer))
	{
	    combat_reward(killer, 0, 1);
	}

	killer->notify_you_killed_me(this_object());

        tell_room(E(TO),"The draconian turns into stone!\n");
	seteuid(getuid(TO));
	corpse = clone_object(STATUE);
        move_all_to(corpse);
	corpse->move(environment(this_object()));

        wep = killer->query_weapon(W_RIGHT);
        if (this_object()->weapon_gone(wep, corpse, killer))
	{
            this_object()->remove_object();
            return;
        }
        wep = killer->query_weapon(W_LEFT);
        if (this_object()->weapon_gone(wep, corpse, killer))
        {
            this_object()->remove_object();
            return;
        }
        wep = killer->query_weapon(W_BOTH);
        if (this_object()->weapon_gone(wep, corpse, killer))
        {
            this_object()->remove_object();
            return;
        }
        this_object()->remove_object();
}

int
weapon_gone(object wep, object corpse, object killer)
{
    string wep_sh;
    if (!wep->query_prop(OBJ_I_IS_MAGIC_WEAPON) &&
	(wep->query_dt() == W_SLASH ||
	wep->query_dt() == W_IMPALE))
       if (random(4) != 1)
       {
          if (wep->move(corpse) == 0)
	    {
	      tell_watcher("Oh no! The weapon is stuck in the stone!\n");
	      wep_sh = wep->short();
	      tell_watcher(QCTNAME(killer) + " lets go of " +
			killer->query_possessive() + " " + wep_sh + ".\n", killer);
	      killer->catch_msg("You let go of your " + wep_sh + ".\n");
	      return 1;
	    }
       }
    return 0;
}

