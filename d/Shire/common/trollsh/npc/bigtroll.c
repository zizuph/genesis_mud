inherit "/std/monster";

#include <options.h>
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/common/make_money.h"
#include <filter_funs.h>
#include <wa_types.h>
#include <ss_types.h>


string
short() 
{
     return "awesome evil half-troll";
}

string
query_nonmet_name()
{
/*
 * Modification log:
 *   Oct-2014: Changed int/wis from 1/2 to 75/75 (Gorboth)
 */
     return "troll guardian";
}

create_monster()
{
     set_name("guardian");
     set_race_name("troll");
     add_adj("half-troll");
     add_adj("grim");
     add_name("troll");
     
     set_long(
     	 "This is a powerful and very evil troll creature. These half-trolls "
     	+"were made by Sauron as his most powerful servants, except the Balrogs "
     	+"made by Morgoth in his days. "
	+"They usually lead large bands of orcs, and are not common here inside "
     	+"tunnels or caves. It is a very special race, a crossing between the "
     	+"feared Olog-hais and Variags, and they represent the uttermost evil "
     	+"of Saurons army. They are powerful and horrible to fight.\n");
     	      
     set_alignment(-645);

     set_exp_factor(140);
     
     set_gender(G_MALE);
     
     add_prop(CONT_I_WEIGHT, 500*1000);
     add_prop(CONT_I_HEIGHT, 450);
     add_prop(LIVE_I_SEE_DARK, 80);
     set_stats(({300,160,280, 75, 75, 220}));
     set_hp(20000);
     MAKE_MONEY;
     set_act_time(3);
     add_act("emote snarls savagely as blood trickles from his mouth!");
     add_act("scream evil");
     add_act("emote sniffs the air for more blood and guts...");
     add_act(({"emote starts chewing on an old piece of meat...","grin"}));
     add_act("emote stares at you with murder in his red eyes!!! ");
    add_act(({"get coins from corpse","grin"}));
     make_gold(5);
     
     set_cact_time(2);
     add_cact(({"emote laughs pitifully at you.","laugh pit"}));
     add_cact("grin");
     add_cact("say PREPARE TO DIE!");
     add_cact("emote measures you from top to toe...");
     add_cact("emote trembles in his feets thinking of how mighty he is.");
     add_cact("emote almost leaves you here in this boring fight, but decides to stay!");
     add_cact("get coins from corpse","get coins from second corpse","drop copper coins");

     set_skill(SS_WEP_AXE, 70);
     set_skill(SS_WEP_POLEARM, 100);
     set_skill(SS_WEP_SWORD, 70);
     set_skill(SS_DEFENCE, 80);
     set_skill(SS_PARRY, 80);
     set_skill(SS_AWARENESS, 81);
     set_skill(SS_BLIND_COMBAT, 40);
     set_aggressive(1);
     set_attack_chance(100);
     set_alarm(1.0,0.0,"arm_me");
     set_pick_up(100);
     add_prop(LIVE_I_NEVERKNOWN, 1);

}

arm_me()
{
	clone_object(TROLLSH_DIR + "weapon/vic_halb")->move(TO);
	clone_object(TROLLSH_DIR + "arm/troll_torso")->move(TO);
   clone_object(TROLLSH_DIR + "obj/bracelet")->move(TO);
	command("wear all");
	command("wield all");
}

int
query_knight_prestige() 
{
    int i;
  
    i = this_object()->query_average_stat();
    i = i * i / 10;
    return i;
}

static void
tell_watcher(string str, object enemy)
{
    object me,*ob;
    int i;
    
    me = this_object();
    ob = FILTER_LIVE(all_inventory(environment(me))) - ({ me });
    ob -= ({ enemy });
    for (i = 0; i < sizeof(ob); i++)
        if (ob[i]->query_option(OPT_BLOOD))
            ob[i]->catch_msg(str);
}

/*
void 
attacked_by(object ob)
{
    ::attacked_by(ob);
    ob->query_race_name()


}
*/
public void
do_die(object killer)
{

   killer->add_prop("_i_killed_trollshaw_trolls",(killer->query_prop("i_killed_trollshaw_trolls_") + 3) );
    ::do_die(killer);
   killer->catch_msg("You killed the awesome evil half-troll.\n");
}
/*
throw_halberd(object enemy)
{
    int hit;
    int *hitresult;
    object me = this_object();
    
    hitresult = enemy->query_max_hp()/2);
    hit       = random(hitresult)
    if random(5)
        return 0;
    
    if(random(5) = 0)
    {
        write("Just before "+QTNAME(me) +" dies "+QCTNAME(me)+" manages to throw the huge halberd at "+QCTNAME(enemy)+" with an awesome power.\n");
        say(QCTNAME(me) +" throws the huge halberd at "+QCTNAME(enemy)+" with awesome power.\n");
        enemy->heal_hp(-hit);
    }
    else
    say(QCTNAME(me) + " throws the halberd at "+QCTNAME(enemy)+" but misses by a few inches!\n");
  



*/

int 
special_attack(object enemy)
{
    int     npc_str = query_stat(SS_STR);
    object  me = this_object();
    mixed  *hitresult;
    string  how, matter;
                
    /*add_prop(LIVE_O_ENEMY_CLING, enemy); I disabled this because he follows folks even when they call for armie. Odin
*/    
if(random(2))
        return 0;
        
    hitresult = enemy->hit_me(npc_str/1 + random(40)+ 10, W_BLUDGEON, me, -1); 
        
    if (hitresult[0] > 25) /* hitresult[0] yields the % hurt. */    
      how = " causing you to stagger back by the awesome power of the blow.";
    else if (hitresult[0] > 20)
/* Does the hit actually hit the hand??? */
       how = " and you feel like a bowl of jelly.";
    else if (hitresult[0] > 15)    
      how = " making you feel like the whole world fell upon you.";
    else if (hitresult[0] > 10)   
      how = " rocking your body by the impact of his fist!";
    else if (hitresult[0] > 5)   
      how = " causing your head to throb violently.";
    else if (hitresult[0] > 0)   
      how = " making you feel really dizzy.";
    else
        how = " but you didn't feel it";
    me->catch_msg("You punch your fists into "+capitalize(enemy->query_possessive())+
    " head.\n");
/*
enemy->catch_msg("You take "+hitresult+" points of damage from the blow.\n");
*/
    enemy->catch_msg(QCTNAME(me)+" punches his fist right into your face,"+ how +".\n");
    tell_watcher(QCTNAME(me)+" punches his fist into "+QTNAME(enemy)+"'s face.\n",enemy); 

    if(enemy->query_hp() <= 0)
    {
    matter = "brains";
    me->catch_msg("You hammer your fists upon "+QTNAME(enemy)+" with a crushing sound. "+
    	  	  CAP(matter)+" splashes out of "+QCNAME(enemy)+"'s head. "+
    	  	  QCTNAME(enemy) + " falls to the ground with a splashing sound!\n");
    
    tell_room(ENV(me),
    	      QCTNAME(me) + " hammer his fists upon "+QTNAME(enemy)+" with a sick crushing sound!\n"+
      	      CAP(matter)+" splashes out of "+QCNAME(enemy)+"'s head, covering the "+QNAME(me)+"."+
      	      QCTNAME(enemy) + " falls to the ground with a splashing sound, in a puddle of blood and meat!\n"+	  	     
              QCTNAME(enemy) + " dies in a horrible scene of blood and guts!!\n");
    
    enemy->catch_msg(
    	      QCTNAME(me) +" hammers his fists upon you with a crushing sound!\n"+
    	      CAP(matter)+" splashes out of your head, covering "+QTNAME(me)+"."+
    	      "You fall to the ground with a splashing sound, in utter pain!!\n"+
    	      "You die in a utterly horrible scene of blood and guts!!!\n");
    enemy->do_die(me);
    me->command("grin");
    return 1;
    }
}
