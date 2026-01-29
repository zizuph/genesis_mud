/* created by Aridor 12/21/93 */

#include "../local.h"

inherit "/d/Krynn/std/dragon_base";

#include <ss_types.h>
#include <wa_types.h>
#include "/sys/stdproperties.h"
#include <macros.h>
#include <composite.h>
#include <filter_funs.h>
#define LANDING_SPOT    ROOM + "river1"
#define ON_MY_BACK      LIV + "on_skie"
#define DIS(xx)  xx->query_base_stat(SS_DIS)
#define DEX(xx)  xx->query_base_stat(SS_DEX)
#define DELAY           15 /* 15 / 5 = 3 rounds of delay */

object *warned = ({ });



void
create_dragon_npc()
{
    string str;

    set_living_name("skie");
    set_name("skie");
    set_gender(0);

    set_colour("blue");
    set_age("aged");

    //set_adj("huge");
    set_long("@@my_long");

    set_knight_prestige(5700);

    /*set_stats(({340,60,360,120,120,140}));

    set_alignment(-1000);

    set_skill(SS_DEFENCE, 100);
    set_attack_unarmed(1, 60, 80, W_SLASH,  50, "right claws");
    set_attack_unarmed(2, 50, 100, W_IMPALE, 50, "bite");
    set_attack_unarmed(4, 80, 25, W_BLUDGEON , 50, "left wing");
    set_attack_unarmed(8, 70, 70, W_BLUDGEON, 50, "tail");

    set_hitloc_unarmed(1, 90, 48, "body");
    set_hitloc_unarmed(2, 50, 10, "left leg");
    set_hitloc_unarmed(4, 15, 10, "right wing");
    set_hitloc_unarmed(8, 15, 12, "left wing");
    set_hitloc_unarmed(16,50, 12, "right leg");
    set_hitloc_unarmed(64,50,  2, "tail");
    set_hitloc_unarmed(32,50,  6, "head");

    add_prop(LIVE_I_SEE_INVIS, 5);
    add_prop(CONT_I_WEIGHT, 4000000);
    add_prop(CONT_I_VOLUME, 100000000);

    add_prop(MAGIC_AM_MAGIC, ({ 100, "divination"}));
    add_prop(OBJ_I_RES_ACID, 90);
    add_prop(OBJ_I_RES_FIRE, 100);
    add_prop(OBJ_I_RES_ELECTRICITY, 100);
    add_prop(OBJ_I_RES_MAGIC, 50);

*/

}

string
my_long()
{
    object *mounted;
    string str = "This is Skie, Kitiara's personal dragon. It is a huge " +
      "blue dragon with wings and scales from head to tail.";
    
    (ON_MY_BACK)->load_me();
    mounted = all_inventory(find_object(ON_MY_BACK));
    if (mounted && sizeof(mounted))
      str += " Mounted on its back is " + 
	COMPOSITE_LIVE(FILTER_LIVE(mounted)) + ".";
    return str + "\n";
}

void
fly_away()
{
    command("emote spreads his wings and takes to the sky.\n");
    command("emote flies a loop and then away. You can't even see it " +
	    "anymore, now.");
    (ON_MY_BACK)->drop_everyone_down();
    move_living(0, ROOM + "lair");
    stop_fight(query_enemy(-1));
}

void
init_living()
{
    ADA("mount");
    ::init_living();
}

int
mount(string str)
{
    if (!str)
      return 0;
    if (str != "dragon" && str != "skie")
      return 0;
    if (member_array(TP, warned) != -1)
      {
	  command("emote roars: I told you! You have gone too far!");
	  command("kill " + TP->query_real_name());
	  return 1;
      }
    if ((TP->query_alignment() > 150) && (TP->query_real_name() != "gunthar"))
      {
	  warned += ({ TP });
	  command("emote roars: Stay away from me, " + TP->query_align_text() +
		  " being.");
	  command("emote roars: Don't provoke me, or I'll have to get nasty.");
      }
    else
      TP->move_living("mounting the dragon", ON_MY_BACK);
    return 1;
}

void
fly_to_landing_spot()
{
    move_living("into the sky", LANDING_SPOT);
}


/*define second_life to let everyone fall down from the dragon after death*/
void
second_life(object killer)
{
    object *the_team;
    string str;
    int i;
    (ON_MY_BACK)->everyone_down_im_dead();
    killer->add_prop("_live_i_killed_dragon",1);
    str = "Skie: " + capitalize(killer->query_real_name()) + ", ";
    the_team = killer->query_team_others();
    for (i = 0; i < sizeof(the_team); i++)
      str += capitalize(the_team[i]->query_real_name()) + ", ";
    write_file("/d/Krynn/solamn/splains/log/attack",
	       extract(ctime(time()), 4, 15)
	       + " " + str[0..strlen(str)-3] + ".\n");

    K_KILL_LOG("kills", "Skie", killer);
    return 0; /* no second life */
}


int
is_valid_enemy(object who)
{
    if (E(who) == E(TO) && !who->query_ghost())
      return 1;
    return 0;
}

object *
valid_enemies()
{
    object *ene = query_enemy(-1);
    object *ene_list = ({ });
    int i;
    ene -= ({ TO });
    for(i=0;i<sizeof(ene);i++)
      if (is_valid_enemy(ene[i]))
	ene_list += ({ ene[i] });
      else
	{
	    stop_fight(ene[i]);
	    ene[i]->stop_fight(TO);
	}
    ene_list -= ({ 0 });
    return ene_list;
}

void
breath_weapon1(object victim)
{
    /*lightning bolt*/
    object *ene = valid_enemies();
    object vic1,vic2;
    tell_watcher("The dragon inhales sharply and breathes a bolt of " +
		 "lightning towards you!\n\n");
    if (random(3))
      vic1 = victim;
    else
      vic1 = ene[random(sizeof(ene))];
    vic2 = ene[random(sizeof(ene))];
    set_alarm(1.0,0.0,"breath_weapon12",vic1,vic2);

}

void
my_hurt_it(object livin)
{
    mixed *res;
    int hitp = 600;
    string str;
    if (!is_valid_enemy(livin))
      {
	  tell_room(E(TO),"The lightning bolt shoots off target.\n");
	  return;
      }
    /*hitpoint modifier on RES_FIRE and RES_LIGHT:*/
    hitp -= hitp * livin->query_magic_res(MAGIC_I_RES_FIRE) / 100;
    hitp -= hitp * livin->query_magic_res(MAGIC_I_RES_ELECTRICITY) / 100;
    res = livin->hit_me(hitp,MAGIC_DT, TO, -1);
    hitp = res[0];
    if (hitp < 10)
      str = "a little ";
    else if (hitp < 20)
      str = "partly ";
    else if (hitp < 40)
      str = "badly ";
    else if (hitp < 60)
      str = "very badly ";
    else
      str = "extremely badly ";
    tell_object(livin,"You are hit and " + str + "burnt.\n\n");
    tell_watcher(QCTNAME(livin) + " was struck by the lightning bolt.\n\n",
		 livin);
    if (!livin->query_ghost())
      livin->do_die(this_object());
}

void
breath_weapon12(object ene1, object ene2)
{
    object vic2 = ene2;
    if (ene1 == ene2)
      vic2 = 0;
    if (random(300) > DEX(ene1))
      my_hurt_it(ene1);
    else 
      {
	  tell_object(ene1,"You evade the lightning bolt!\n\n");
	  tell_watcher(QCTNAME(ene1) + " manages to evade the lightning " +
		       "bolt.\n\n",ene1);
	  if (vic2 && (random(200) > ene2->query_base_stat(SS_DEX)))
	    my_hurt_it(ene2);
	  else if (vic2)
	    {
		tell_object(ene2,"You evade the lightning bolt!\n\n");
		tell_watcher(QCTNAME(ene2) + " manages to evade the " +
			     "lightning bolt.\n\n",ene2);
	    }
	  tell_room(E(TO),"The lightning bolt shoots off target.\n");
      }
}

void
breath_weapon2(object victim)
{
    /*sleeping gaz*/

}


void
fly_attack(object victim)
{
    object *enemiess = valid_enemies();
    int i;
    enemiess->add_attack_delay(DELAY,1);
    tell_room(E(TO),QCTNAME(TO) + " spreads its wings and leaps into the " +
	      "air!\n\n");
    set_alarm(1.0,0.0,"fly_attack2",enemiess, victim);
}

void
fly_attack2(object *enemiess, object victim)
{
    int i, amt;
    for (i = 0;i<sizeof(enemiess);i++)
      {
	  amt = 1500 / DIS(enemiess[i]);
	  if (amt > 10)
	    {
		tell_object(enemiess[i], "A great fear emanating from the " +
			    "dragon grabs you and you cannot move!\n\n");
		enemiess[i]->command("shiver");
	    }
	  enemiess[i]->cb_add_panic(amt);
	  enemiess[i]->cb_may_panic("north");
      }
    set_alarm(1.0,0.0,"fly_attack3",enemiess, victim);
}

void
fly_attack3(object *enemiess, object victim)
{
    string damage, how;
    object attacking;
    mixed *res;
    int hurt;
    tell_room(E(TO),"With a great whooshing sound, the dragon swoops back " +
	      "down to the ground.\n");
    if (random(3))
      attacking = victim;
    else
      attacking = enemiess[random(sizeof(enemiess))];
    if (!is_valid_enemy(attacking))
      return;

    res = (attacking->hit_me(300, W_BLUDGEON, TO, 
			     4 + 4 * random(2)));
    hurt = res[0];
    if (hurt > 10)
      how = "crushing ";
    else if (hurt > 0)
      how = "grazing ";
    else
      how = "luckily without touching ";
    if (hurt > 80)
      damage = " extremely badly beneath";
    else if (hurt > 50)
      damage = " really badly beneath";
    else if (hurt > 30)
      damage = " very badly beneath";
    else if (hurt > 18)
      damage = " badly beneath";
    else if (hurt > 10)
      damage = " beneath";
    else 
      damage = " with";
    attacking->catch_msg("The dragon slams down onto you, " + how +
			 "you" + damage + " its wing.\n\n");
    tell_watcher("The dragon slams down onto " + QTNAME(attacking) +
		 ", " + how + attacking->query_objective() + damage + 
		 " its wing.\n\n", attacking);
}

/* let the standard special attack for dragons take over instead.
int
special_attack(object victim)
{
    if (E(victim) != E(TO) || victim->query_ghost())
    {
	TO->stop_fight(victim);
	return 1;
    }
    switch (random(13))
    {
    case 0: breath_weapon1(victim);
	return 0;
    case 1: breath_weapon2(victim);
	return 0;
    case 2:
    case 3: fly_attack(victim);
	return 1;
    default: 
    }
    return 0;
}
*/
