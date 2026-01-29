/*Created by Macker 10/15/94 */

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include "/d/Krynn/solace/lake/local.h"
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>

#include <macros.h>
inherit M_FILE

void form_team();

void
create_krynn_monster()
{
    string str;

    string * adjlist1 = ({ "savage", "brutal", "mean", "violent",""+
      "ugly", "wild", "ruthless", "deadly", "devastating",""+
      "destructive", "aggressive", "mutilating" });

    set_name("thanoi");
    add_name("m_thanoi");
    set_race_name("thanoi");

    set_adj("dominant");
    set_adj(adjlist1[random(sizeof(adjlist1))]);
    set_long("This is a thanoi, or walrus-man. " +
      "He has humanoid arms " +
      "and legs, evil beady black eyes, and " +
      "a pair of long tusks curved to a sharp point, which send " +
      "chills up and down your spine- as if it wasn't already " +
      "cold enough here! From his motions, grunts, and smell, " +
      "you quickly deduct that this is a very primitive race " +
      "that is probably best left alone or exterminated if " +
      "you are crazy enough to try. Only the strongest " +
      "and the fiercest of thanoi were choosen to serve " +
      "the White Dragon Highlord here, in Icewall Castle, " +
      "and even among those, beasts such as this one reign " +
      "supreme.\n");

    set_stats(({190, 130, 170, 80, 80, 130}));
    set_skill(SS_PARRY, 80);
    set_skill(SS_DEFENCE, 80);
    set_skill(SS_WEP_AXE, 90);

    add_prop(LIVE_I_SEE_DARK, 2);
    set_alignment(-800);
    set_knight_prestige(query_average_stat() * query_average_stat() /9);
    NEVERKNOWN;

    set_act_time(10);
    add_act("emote grunts disgustingly.");
    add_act("emote barks out a most unusual sound and slaps his " +
      "blubbery chest.");
    add_act("snarl all");

    seq_new("do_things");
    seq_addfirst("do_things","@@arm_me");
    set_alarm(1.0, 0.0, form_team); 
    refresh_mobile();
    add_leftover(PLAINS_O + "hide", "hide",1,"",1,1);
    set_exp_factor(120);
    /*  Exp boost due to highly damaging combat special. Fighting
	a team of thanoi makes the tanker loose health much 
	more quickly then usual                                    */

}


void
form_team()
{
    object *others;
    others = FILTER_OTHER_LIVE(all_inventory(E(TO)));
    others = others - ({TO});
    others->team_up(TO);
}
public void
attacked_by(object ob)
{
    ::attacked_by(ob);
    seteuid(getuid(TO));
    command("emote looks pleased that someone has volunteered " +
      "to be his target of destruction.");
    command("grin anxiously");
}

arm_me()
{
    object wep;
    seteuid(getuid(TO));
    wep = clone_object(PLAINS_O + "taxe.c");
    wep->move(this_object());
    command("wield weapon");
}

int
special_attack(object enemy)
{
    int attacktype, i, penet;
    mixed* hitresult;
    string str1, str2;

    attacktype = random(3);
    if (attacktype == 1)
    {
	penet = 200 + random(150);
	hitresult = enemy->hit_me(penet, W_IMPALE, TO, -1);
	if (hitresult[0] > 70)
	{
	    str1 = (QCTNAME(TO) + " drives his stakes of death into " +
	      QTNAME(enemy) + ", causing extreme damage!\nHe " +
	      "then yanks his bloody tusks out and promptly " +
	      "licks them clean");
	    str2 = (QCTNAME(TO) + " drives his stakes of " +
	      "death into you, causing extreme damage!\nHe then " +
	      "yanks his bloody tusks out and promptly licks " +
	      "them clean");
	}
	else if (hitresult[0] > 30)
	{
	    str1 = (QCTNAME(TO) + " slams his lethal tusks home, into " +
	      QTNAME(enemy) + "'s body");
	    str2 = (QCTNAME(TO) + " slams his lethal tusks home, into " +
	      "your body");
	}
	else if(hitresult[0] > 15)
	{
	    str1 = (QCTNAME(TO) + " sticks " + QTNAME(enemy) +
	      " with his long tusks, doing some damage");
	    str2 = (QCTNAME(TO) + " sticks you with his long tusks, " +
	      "doing some damage");
	}
	else if (hitresult[0] > 5)
	{
	    str1 = (QCTNAME(TO) + " slashes into " + QTNAME(enemy) +
	      "'s body with his sharp tusks");
	    str2 = (QCTNAME(TO) + " slashes into your body with his " +
	      "sharp tusks");
	}
	else if (hitresult[0] > 0)
	{
	    str1 = (QCTNAME(TO) + " slightly scratches " +
	      QTNAME(enemy) + " with his tusks");
	    str2 = (QCTNAME(TO) + " slightly scratches you with his " +
	      "tusks and lands right next to you");
	}
	else
	{
	    str1 = (QCTNAME(TO) + " leaps at " + QTNAME(enemy) +
	      " and flies right past " + OBJECTIVE(enemy) +
	      ", landing belly-down on the ground with a " +
	      "mouthful of snow.\nHe quickly gets up, shakes off " +
	      "the powdery snow, and continues fighting");
	    str2 = (QCTNAME(TO) + " flies right past you " +
	      "and lands belly-down on the ground with a " +
	      "mouthful of snow.\nHe quickly gets up, shakes off " +
	      "the powdery snow, and continues fighting");
	}

	enemy->catch_msg(QCTNAME(TO) + " jumps at you while " +
	  "simultaneously rearing his head back in an " +
	  "attempt to drive his tusks into you....\n" + str2 +
	  "!\n");
	if (TO && enemy)
	    tell_watcher(str1 + "!\n", enemy);

	if (enemy->query_hp() <= 0)
	{
	    set_alarm(1.0, 0.0, "victory", enemy);
	    tell_watcher(QCTNAME(enemy) + "'s blood clashes with the " +
	      "purity of the white snow.\n", enemy);
	}
	return 1;
    }
    return 0;
}

void
victory(object enemy)
{
    if(!objectp(enemy))
	return;

    tell_room(E(TO),QCTNAME(TO) + " leaps onto the " +
      "lifeless body of " + QTNAME(enemy) + " and drives his " +
      "bloody tusks in and out of it repeatedly for the " +
      "sheer joy of it!\n");
}


/*The below function is being redefined from
	M_FILE due to the fact that most thanoi do not speak common
*/
void
help_friend(object ob)
{
    if (ob && !query_attack() && present(ob, environment()))
    {
	tell_room(E(TO), QCTNAME(TO) + " grunts something in the " +
	  "thanoi language as he turns " +
	  "toward " + QTNAME(ob) + " to attack.\n", ({ob, TO}));
	ob->catch_msg(QCTNAME(TO) + " grunts something in the thanoi " +
	  "language as he turns toward you to attack.\n");

	command("kill " + lower_case(ob->query_real_name()));
    }
}

public int
second_life(object killer)
{
    (ICE_PLAINS + "plain_8")->reduce_tnum();
    return 0;
}

object
query_folk_here()
{
    int i = 0;
    object *allhere;
    allhere = FILTER_LIVE(all_inventory(E(TO)));
    while(implode((allhere[i])->query_adj(1), " ") != "ice folk")
    {
	if((i+1)>= sizeof(allhere))
	    return 0;
	else
	    i += 1;
    }
    return(allhere[i]);
}


public void
init_attack()
{
    object folk;

    if((implode(TP->query_adj(1), " ") == "ice folk")&&
      (sizeof(FILTER_PLAYERS(all_inventory(E(TO)))) > 0))
	set_alarm(1.5, 0.0, "aggressive_attack", TP);
    folk = query_folk_here();
    if((interactive(TP))&&(folk))
	set_alarm(1.5, 0.0, "aggressive_attack", folk);

    return(::init_attack());
}

