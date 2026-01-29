/* created by Aridor 12/21/93 
 *
 * Modified by Blizzard, 16.07.2003
 * Added blackened kite-sheild and fullplate.
 *
 * Arman 29/7/2021, Increased stats, increased special
 *                  damage against npcs.
 */

#include "../local.h"

inherit M_FILE
inherit "/lib/unique";

#include TIME_FLOW
#include <std.h>
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <money.h>

#define MINIMUM_DEFENSE_STRENGTH    100
/*sum of stat_avg of all knights present*/

#define LOG                         TDIR + "log/"
#define DRAGON_LAIR                 ROOM + "lair"
#define ATTACK_MASTER               (OBJ + "troop_master")

#define MEM_LIMIT_NO_ATTACK         98
#define WIZ_ALERT(x)                find_player("arman")->catch_msg("[Kitiara] " + x + "\n")


/* don't do the attack if memory > 85% */
#define DEFENDER                    OBJ + "defender_shadow"

/* New unique weapon */
#define WAR_SWORD                   "/d/Krynn/pax/weapon/war_sword"

string color = "blue";
object my_dragon;
object armour, weapon;

void   equip_me();

void
create_krynn_monster()
{
    string str;

    set_living_name("kitiara");
    set_name("kitiara");
    add_name("highlord");
    set_title("Dragon Highlord of the Blue Dragonarmy");
    set_race_name("human");
    set_gender(1);
    add_prop(OBJ_I_COLORABLE, 1);
    set_introduce(1);

    set_adj("curly");
    add_adj("black-haired");
    set_long("This is Kitiara, the dragon highlord and " +
      "commander of the blue dragon army.\n");

    set_stats(({280,300,340,240,240,340}));
    set_skill(SS_DEFENCE,     100);
    set_skill(SS_PARRY,       100);
    set_skill(SS_WEP_SWORD,   120);  
    set_skill(SS_WEP_AXE,     100);
    add_prop(LIVE_I_QUICKNESS, 150);
    add_prop("_ranger_m_not_disarm",1);
    add_prop(CONT_I_WEIGHT, 60000);
    add_prop(CONT_I_HEIGHT, 185);

    set_alignment(-1000);
    set_knight_prestige(4500);

    set_all_hitloc_unarmed(45);

    set_alarm(1.0,0.0, &equip_me());
}

void
set_color(string new_color)
{
    color = new_color;
}

/* return 0 if the attack wasn't started, 1 if it was */
/* Called from common/flow/kitiara */
int
my_strategy()
{
    object *playing;
    int i, mlim, cval, d, this_attack_team_strength;
    string mc, bef, aft;
    int sumstat = 0;

    WIZ_ALERT("Kitiara attack called.");

    if (E(TO) != find_object(DRAGON_LAIR))
	return 0;

    /* Check if the plains are belonging to the Blue Army 
    if (ARMYMASTER->army_in_area("Western Solamnian Plains") != "Blue Dragon Army")
      return 0;
    */
    
    /* Check memory limit of the game */
    mlim = SECURITY->query_memory_limit();
    mc = SECURITY->do_debug("malloc");
    sscanf(mc, "%ssbrk requests: %d %d (a) %s", bef, d, cval, aft);
    if (((100 * (cval / 10)) / (mlim / 10)) > MEM_LIMIT_NO_ATTACK)
	return 0;

    playing = users();
    for(i = 0; i<sizeof(playing); i++)
	if (!(playing[i]->query_wiz_level()) && 
	  ((playing[i]->test_bit("Krynn",1,0)) ||
	    (playing[i]->test_bit("Krynn",1,2))))
	    sumstat += (playing[i]->query_average_stat());

    /* Removing check for knights online */
//    if (sumstat < MINIMUM_DEFENSE_STRENGTH)
//    {
	/*      tell_room(E(TO),"SUM: " + sumstat + "\n");*/
//	return 0;
//    }


    if(!sumstat)
        sumstat = 100;

    if (random(6))
	this_attack_team_strength = sumstat / 100;
    else /* an extra strong attack */
	this_attack_team_strength = sumstat * (1 + random(3)) / 100 + 2 + random(20);

    (LIV + "on_skie")->load_me();
    my_dragon = (LIV + "on_skie")->query_my_dragon();
    command("mount skie");
    my_dragon->fly_to_landing_spot();
    ATTACK_MASTER->my_strategy(my_dragon, this_attack_team_strength);

    WIZ_ALERT("Kitiara commencing attack.");
    return 1;
}

/* Called from common/flow/kitiara */
void
flee_troops_gone()
{
    my_dragon->fly_away();
}

void
equip_me()
{
    weapon = clone_unique(WAR_SWORD, 6, OBJ + "kit_sword");
    weapon->move(TO, 1);
    
    if ( weapon->id("sabre") )
        clone_object(KRARMOUR + "kite-shield")->move(TO, 1);
        
    armour = clone_unique(KRARMOUR + "fullplate", random(3) + 1, 
                          OBJ + "bdragonarm");
    armour->set_color("blue");
    armour->move(TO, 1);
    
    if ( armour->id("dragonscale") )
    {
        clone_object(OBJ + "bdragonhelm")->move(TO);
        clone_object(OBJ + "bshinguard")->move(TO);
    }
    
    MONEY_MAKE_PC(random(3) + 2)->move(TO);
    clone_object(OBJ + "kitring")->move(TO);
    command("wear all");
    command("wield all");
}

int
second_life(object killer)
{
    object *the_team;
    string str;
    int i = 216000;
    if (killer->query_prop("_live_i_killed_dragon"))
      i = 864000;
    killer->add_autoshadow(DEFENDER + ":" + (time() + i));
    clone_object(DEFENDER)->shadow_me(killer);
    killer->catch_msg("You gain the title of 'Defender of Vingaard Keep'.\n");
    str = "Kit : " + capitalize(killer->query_real_name()) + ", ";
    the_team = killer->query_team_others();
    for (i = 0; i < sizeof(the_team); i++)
      str += capitalize(the_team[i]->query_real_name()) + ", ";
    write_file(LOG + "attack",
	       extract(ctime(time()), 4, 15)
	       + " " + str[0..strlen(str)-3] + ".\n");
    
    K_KILL_LOG("kills", "Kitiara", killer);
    
    return 0; /* no second life */
}

int
special_attack(object victim)
{
    mixed *res;
    int hitp;
    string str, str1;
    if (E(victim) != E(TO) || victim->query_ghost())
    {
	find_living("aridor")->catch_msg("KSTOP.\n");
	TO->stop_fight(victim);
	return 1;
    }
    if (!random(7))
    {
	victim->catch_msg(query_The_name(victim) + " thrusts her " +
	  query_weapon(-1)[0]->short()+" toward you.\n");

        if(victim->query_npc())
	    res = victim->hit_me(4500, W_SLASH, TO, 1536);
        else
	    res = victim->hit_me(500, W_SLASH, TO, 1536);
	hitp = res[0];
	if (hitp = 0)
	{
	    str = "but you manage to avoid it";
	    str1 = "fails to hit";
	}
	else if (hitp < 10)
	{
	    str = "and you try to sidestep, but you are tickled";
	    str1 = "tickles";
	}
	else if (hitp < 20)
	{
	    str = "and you try to sidestep, but you are grazed ";
	    str1 = "grazes";
	}
	else if (hitp < 40)
	{
	    str = "and you are hurt";
	    str1 = "hurts";
	}
	else if (hitp < 60)	
	{
	    str = "and you are very badly hurt";
	    str1 = "smashes";
	}
	else
	{
	    str = "and you are massacred";
	    str1 = "massacres";
	}
	tell_object(victim,query_The_name(victim) + " suddenly twists the " +
	  query_weapon(-1)[0]->short()+" "+str+".\n");
	victim->add_attack_delay(hitp/3,1);
	tell_watcher(QCTNAME(TO) + " " + str1 + " " + QTNAME(victim) +
	  " with her "+query_weapon(-1)[0]->short()+".\n", victim);
	if (!victim->query_ghost())
	    victim->do_die(this_object());
    }
    return 0;
}


/* Called from common/flow/kitiara */
void
patrol_vkeep()
{
    /* Here I want to start some code where the dragon flies over
       vingaard keep. From the keep, the shadow of the dragon and
       a dragon high up in the air can be seen.
       */
    object shadow;

    seteuid(getuid(TO));
    shadow = clone_object(OBJ + "dragon_shadow");
    shadow->move(ROOM + "river1");
}

