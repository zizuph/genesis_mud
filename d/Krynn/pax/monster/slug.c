/*
 * A nasty slug
 *
 * 950401 by Rastlin
 */

#include "/d/Krynn/solamn/splains/local.h"
#include "/d/Krynn/pax/local.h"
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

inherit C_FILE
inherit "/std/act/domove";
inherit "/std/act/attack";

void
create_creature()
{
    int i;

    set_name("slug");
    set_short("slug");
    set_race_name("slug");
    set_adj("gigantic");
    set_gender(G_NEUTER);

    set_long("It has a great bulk and makes a scraping sound, caused " +
	     "by its gigantic bloated body sliding along the floor. " +
	     "Its eyes, perched atop slender rotating stalks on top " +
	     "of its head, are not of much use, nor does it need them. " +
	     "The slug can find and devour rats in the darkness by " +
	     "sense of smell alone.\n");

    for(i = 0; i < 6; i++)
        set_base_stat(i, 120 + random(30));
    set_base_stat(3, 10);
    set_base_stat(4, 10);

    set_alignment(-100);
    set_knight_prestige(2);

    set_hp(query_max_hp());

    set_skill(SS_DEFENCE, 40 + random(10));
    set_skill(SS_AWARENESS, 50);

    set_attack_unarmed(0, 75, 80, W_IMPALE, 40, "bite");
    set_attack_unarmed(1, 65, 60, W_BLUDGEON, 60, "tail");

    set_hitloc_unarmed(0, 90, 50, "body");
    set_hitloc_unarmed(1, 70, 25, "head");
    set_hitloc_unarmed(2, 60, 25, "tail");

    add_prop(LIVE_I_SEE_DARK, 100);
    add_prop(CONT_I_VOLUME, 50200);
    add_prop(CONT_I_WEIGHT, 73457);

    set_random_move(4);
}

int
special_attack(object enemy)
{
    int i, penet;
    mixed* hitresult;
    string how;
    object me, *wep;

    if(enemy == TO)
        return 1;

    if (!random(30))
    {
	wep = enemy->query_weapon();

	if (!wep)
	    return 0;
	
	i = random(sizeof(wep));

	enemy->catch_msg(BS("The slug spits out a stream of slaiva at you, but " +
		"misses and hits your " + wep[i]->query_short() + ", causing it " +
		"to fizz and smoke, then dissolving in your hand.", 70));

        wep[i]->remove_object();

	return 1;
    }

    if (!random(10))
    {
	me = this_object();

	enemy->catch_msg("The slug spits out a stream of saliva at you.\n");

	penet = 950 + random(600);
	penet -= penet * enemy->query_magic_res(MAGIC_I_RES_ACID) / 100;

	hitresult = enemy->hit_me(penet, W_IMPALE, me, -1);
         
	how = "not harmed";
	if (hitresult[0] > 0)                  
	    how == "barely burned";
	if (hitresult[0] > 10)
	    how = "slightly burned";
	if (hitresult[0] > 20)
	    how = "burned quite badly";
	if (hitresult[0] > 40)
	    how = "burned very badly";
	if (hitresult[0] > 60)
	    how = "badly incinerated";

	enemy->catch_msg("You were " + how + " by the corrosive liquid!\n");
         
	if (enemy->query_hp() <= 0)
	    enemy->do_die(me);

	return 1;
    }
    return 0;
}

public void
do_die(object killer)
{
    if (query_hp() == 0)
        killer->add_prop("_live_i_killed_slug", 1);

    ::do_die(killer);
}
