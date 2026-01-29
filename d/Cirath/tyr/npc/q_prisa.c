/*
* Created by: Luther
* Date: 13 August 2001
*
* File: /d/Cirath/tyr/npc/q_pris.c
* Comments: Slave prisoner in the Jail of Tyr part of Jail quest
*           used lyden.c as a template to making 
*/
 
#pragma strict_types
 
inherit "/d/Cirath/std/monster.c";
#include <wa_types.h>
#include "defs.h"
 
void
create_monster ()
{
    set_living_name("dale");
    set_name("dale");
    set_title("Poor merchant of Tyr");
    set_race_name("human");
    set_adj("skinny");
    add_adj("bonny");
    set_long("Once a wealthy merchant in Tyr, this bonny prisoner looks "
            +"ragged and worn down. By the looks of his clothes he must "
            +"have been here for quite some time. His arms and legs are "
            +"chained to the wall, giving him little movement. He still "
            +"looks like he can fight being chained up to the wall. You "
            +"should probably leave him alone, surely a prisoner who has "
            +"been here this long wouldn't even recognize Tyr now.\n");
   
    	set_stats(({75,75,75,100,100,75}));
    	set_all_hitloc_unarmed(50);
    	set_skill(SS_BLIND_COMBAT, 50);
    	set_skill(SS_DEFENCE, 60);
    	set_skill(SS_PARRY, 40);
    	set_skill(SS_UNARM_COMBAT,80);
    	set_alignment(-250);
   
    	set_act_time(3);
    	add_act("emote glares at you wishing he was free.");
    	add_act("emote tries to break his chains.");
	add_act("emote rattles his chains.");
	add_act("emote mumbles painfully.");
	add_act("emote ponders when the leftovers will arrive.");
	add_act("' I don't like being a prisoner.");
    	add_act("emote stares at the dead body against the wall.");
    	add_act("shout let me out of here!");
    	add_act("' No one can help me.");
    	
    	set_cact_time(3);
    	add_cact("shout Guards, Help me!");
    	add_cact("' But i dont know where it is! I swear!");
    	add_cact("' These chains hinder me or you would die alot faster.");
    	add_cact("emote tries to break the chains.");
    	add_cact("emote almost breaks his chains.");  
}
 
void
arm_me()
{
    clone_object(TYR_ARM+"d_gloves")->move(TO);
    clone_object(TYR_ARM+"d_shirt")->move(TO);
    command("wear all");
}
 
void
attacked_by(object ob)
{
    ::attacked_by(ob);
}
 
void
do_die(object killer)
{
    ::do_die(killer);
}
 
/* **************** LYDEN CHARGES! ******************** */
int
special_attack(object enemy)
{
    object me;
    mixed* hitresult;
    string how;
 
    me=this_object();
 
    if(random(8)) return 0;
 
    hitresult = enemy->hit_me(200 + random(200), W_BLUDGEON, me, -1);
    how = "amazed by such a feeble attack";
    if (hitresult[0] > 0) how = "dazed";
    if (hitresult[0] > 15) how = "injured";
    if (hitresult[0] > 30) how = "hurt";
    if (hitresult[0] > 50) how = "severely hurt";
    if (hitresult[0] > 75) how = "on the verge of collapse";
 
    enemy->catch_msg(QCTNAME(me) + " strikes you with "+
                     HIS_HER(me) + " leaping charge.\n");
    enemy->catch_msg("You feel " + how + ".\n");
 
    tell_watcher(QCTNAME(me)+" strikes "+QCTNAME(enemy)+
                 " with " + HIS_HER(me) + " leaping charge.\n",
                 me, enemy);
 
    if(enemy->query_hp() <= 0) enemy->do_die(me);
 
    return 1;
}
