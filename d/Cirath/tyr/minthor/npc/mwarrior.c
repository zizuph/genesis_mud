inherit "/std/monster";
#include <wa_types.h>
#include "/d/Cirath/common/defs.h"
#include "/d/Cirath/quest_handler/quest_handler.h"
#include "/d/Cirath/common/introfnc.h"
#define _QUEST_AMULET_ "_quest_amulet_"

mixed attackers;
int amulet;
string long;
object mwarrior;
#define RNDWEP ({"rkaxe","rkaxe2","kaxe","kaxe","kaxe","mbiaxe",\
		"kaxe","kaxe","kaxe"}) [random(10)]

void
create_monster ()
{
    set_name("kranj'k");
    set_title("Master Warrior of Athas");
    set_race_name("human");
    set_adj("lean");
    add_adj("disciplined");
    set_long("A powerful warrior once in the service of Kalak, Kranj'k "
   +"is now a warrior for hire, selling out his fighting skills to anyone "
   +"with a big purse. Legend has it, that he trained Lyden, and was the "
   +"first gladiator to escape from the slave pits. Why he was spared is "
   +"a mystery.\n");
   set_stats(({ 170, 185, 200, 130, 130, 140}));
    set_skill(SS_WEP_AXE, 100);
    set_skill(SS_BLIND_COMBAT, 100);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_PARRY, 100);
    set_alignment(0);
    add_prop(NPC_M_NO_ACCEPT_GIVE,0);
   add_prop(LIVE_I_QUICKNESS,100);
   add_prop(LIVE_I_SEE_DARK,5);
    add_ask(({"minthor","minthors"}),"Kranj'k says: I work for them. "
	+"They pay me well.\n");
    add_ask(({"help","task","quest"}),"Kranj'k says: When I was a slave "
	+"they kept me in the slave pits.  Upon winning my release, I was "
	+"so anxious to leave that I left behind something very important "
	+"to me.\n");
    add_ask(({"something","what"}),"I left behind my good luck amulet.\n");
    add_ask("amulet","It wasn't much, but it was mine. Its in the slave "
	+"pits.  If you get it for me, I might let you into Lord Minthor's "
	+"chambers.\n");
    set_act_time(3);
    add_act("emote casually catches a small bug in his mouth.");
    add_act("emote stretches his long limbs.");
    add_act("roar");
    add_act("shout I am the greatest warrior in the world!");
    add_act("say I trained Lyden, and you thought he was tough.");
     add_act("say You should not be here, leave or I will kill you.");
    add_act("say I won't waste the water killing you.");
    set_cact_time(3);
    add_cact("say You fools never learn.");
    add_cact("say I have killed worms tougher than you!");
    add_cact("say That kind of tickles, do it again.");
    add_cact("emote sticks his finger into your eye.");
    add_cact("emote smiles grimly.");
}

void
arm_me()
{
   clone_object("/d/Cirath/tyr/minthor/wep/"+RNDWEP)->move(TO);
  clone_object("/d/Cirath/tyr/minthor/arm/k_greaves2")->move(TO);
   clone_object("/d/Cirath/tyr/minthor/arm/k_helm2")->move(TO);
   clone_object("/d/Cirath/tyr/minthor/arm/k_gloves2")->move(TO);
   clone_object("/d/Cirath/tyr/minthor/arm/k_plate2")->move(TO);
   clone_object("/d/Cirath/tyr/minthor/arm/k_boots2")->move(TO);
   clone_object("/d/Cirath/tyr/minthor/arm/k_bracers2")->move(TO);
    command("wield all");
    command("wear all");
}

/*
void
attacked_by(object ob)
{
    ::attacked_by(ob);
    if (!pointerp(attackers)) attackers = ({});
    if (member_array(ob,attackers) == -1) attackers += ({ob});
	environment(TO)->help_func();
}

varargs public mixed
hit_me(int wcpen, int dt, object attacker, int attack_id, int target_hitloc=-1)
{
	environment(TO)->rescue_func(attacker);
	return ::hit_me();
}
*/

int
special_attack(object enemy)
{
    object me;
    mixed* hitresult;
    string how;
    me=this_object();

   if(random(6))  return 0;

    hitresult = enemy->hit_me(350 + random(250), W_BLUDGEON, me, -1);
    how = "untouched";
    if (hitresult[0] > 0) how = "barely touched";
    if (hitresult[0] > 15) how = "a little bruised";
    if (hitresult[0] > 30) how = "hurt";
    if (hitresult[0] > 50) how = "incredibly hurt";
    if (hitresult[0] > 75) how = "numb all over";

    enemy->catch_msg(QCTNAME(me) + " strikes you with "+
                     HIS_HER(me) + " forearm smash.\n");
    enemy->catch_msg("You feel " + how + ".\n");

    tell_watcher(QCTNAME(me)+" strikes "+QCTNAME(enemy)+
                 " with " + HIS_HER(me) + " forearm smash.\n",
                 me, enemy);

    if(enemy->query_hp() <= 0) enemy->do_die(me);

    return 1;
}

amulet_return()
{
    amulet = 1;
}
public void
enter_inv(object ob, object from)
{      	
   	::enter_inv(ob,from);

    	if (!from) return;

    	if (ob->query_prop(_QUEST_AMULET_))
        	set_alarm(1.0, 0.0, "got_amulet", ob, from);
   	else
        	set_alarm(1.0, 0.0, "got_else", ob, from);
}

void
got_amulet(object ob, object from)                  
{   
    	if (!interactive(from))
        	return;
   
        set_this_player(from);
        if (QH_QUERY_QUEST_COMPLETED(from, "mwarrior"))
    	{
        	write(query_The_name(from) + " looks puzzled.\n");
        	TP->catch_msg("You don't feel more experienced.\n");
        	ob->remove_object();
    	}
    	else 
    	{
        	write("Kranj'k smiles at you and winks conspiratorily.\n");
        	TP->catch_msg("You feel more experienced.\n");
        	QH_QUEST_COMPLETED(from,"mwarrior");
        	ob->remove_object();
        	set_alarm(2.0,0.0,"remove_the_object",ob);
    	}        
}

void
remove_the_object(object ob)
{
    	command("emote turns and walks down the hall.");
    	if(mwarrior = present("kranj'k", environment(TP)))
    	{
        	mwarrior -> remove_object();
    	}
}

void
got_else(object ob, object from)
{
    	command("say What is this?");
    	command("drop "+ob->query_name());
}

