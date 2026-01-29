/* 
 * Standard giant_ant for the anthive project.
 * 
 *
 */

inherit "/std/monster";
inherit "/std/combat/unarmed";   /* Get standard unarmed routines */


#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include "../defs.h"

#include "/d/Sparkle/area/anthive/drops/drop_master.c";
//#include DROP_MASTER;

#define TO this_object()

int size = 20;






void
do_die(object killer)
{
    
    deluxe_drop();
    
    ::do_die(killer);
}

void
adjust_size()
{
	
	  if (environment(this_object())->query_hive_level() == 1)
	  	 {
	  	 	  size = 30;
	  	 	  TO->set_stats(({size, size, size, size, size, size}));
	  	 	  TO->set_exp_factor(EXP_PERCENTAGE);
	  	 	  TO->set_short("brown giant ant");
	  	 }
	  	 
	  if (environment(this_object())->query_hive_level() == 2)
	  	 {
	  	 	  size = 50;
	  	 	  set_short("brown giant ant");
	  	 }
	  	 
	  if (environment(this_object())->query_hive_level() == 3)
	  	 {
	  	 	  size = 70;
	  	 	  set_short("brown giant ant");
	  	 }
	  	 
	  if (environment(this_object())->query_hive_level() == 4)
	  	 {
	  	 	  size = 90;
	  	 	  set_short("brown giant ant");
	  	 }
	  	 
	  if (environment(this_object())->query_hive_level() == 5)
	  	 {
	  	 	  size = 110;
	  	 	  set_short("brown giant ant");
	  	 }
	  	 
}
	  	

create_monster()
{

    set_name("ant");
    set_adj("giant");
    add_name("_hivemonster");
    set_race_name("ant");
    set_short("giant ant");
    set_long("This is a giant version of an ant. Its the size of a an elephant. Six long hairy " +
    "legs stretches out from the middle a body made up of three parts. You can see two black eyes " +
    "above a set of powerful mandibles. Two huge antennas moves " +
    "back and forth on the top of its head.\n");
    set_gender(2);
    set_alignment(0);
    
    
    
    // The spider relies on vibrations and sound to detect its prey, so if its 
    // a solid living object, it can be detected.
    
    add_prop(LIVE_I_SEE_DARK, 99);
    add_prop(LIVE_I_SEE_INVIS, 99);
    
   

    set_act_time(7);
    set_cact_time(4);   
      
    add_act("emote stretches one of its six legs.\n");
    add_act("emote paces around urgently.\n");
    
    add_cact("emote prepares to rush at you.\n");
    add_cact("emote open its powerful mandibles!\n");
    
    

    /* str, dex, con, int, wis, dis */    
    set_stats(({size, size, size, size, size, size}));
    
   // set_default_conf(size);

    set_skill(SS_DEFENCE, 60);

    set_aggressive(1);
    set_random_move(3);


    
              /*           hit/pen           %% on usage per c-round */    
    set_attack_unarmed(0,  50, 50, W_SLASH, 100, "mandibles");
    
    
        
        
        
       /*                 AC  100% */     
    set_hitloc_unarmed(1, 50, 20, "mandibles");
    set_hitloc_unarmed(2, 50, 20, "left antenna");
    set_hitloc_unarmed(3, 50, 20, "right antenna");
    set_hitloc_unarmed(4, 50, 20, "head");
    set_hitloc_unarmed(5, 50, 20, "back body");
    
    

    
    
    set_alarm(1.0,0.0, &adjust_size());
    
   
    
    
}



int
special_attack(object enemy)
{
    object me = this_object();

    mixed *hitresult;
    string how;


/*    tell_watcher("we get here.\n"); */

    /* Only execute the special attack 1 in 10 rounds */
    if (random(4))
    {
/*    tell_watcher("returning 0.\n"); */
        return 0;  /* Continue with the normal attacks */
    }
/*    tell_watcher("getting a special.\n"); */
    hitresult = enemy->hit_me(size + random(size), W_IMPALE, me, -1);
    switch (hitresult[0])
    {
        case 0:
            how = "not hurt at all";
            break;
        case 1..10:
            how = "barely hurt by the bite";
            break;
        case 11..20:
            how = "hurt by the bite";
            break;
        default:
            how = "severly hurt by the bite";
            break;
    }

    enemy->catch_tell(query_The_name(enemy) + " suddenly jumps at you and bites you with its powerful mandibles!\n"+"You are" + how + "!\n");


    tell_watcher(QCTNAME(me) + " suddenly jumps at " + QTNAME(enemy) + " and bites " + enemy->query_pronoun()+ " with its powerful " +
    "mandibles!\n" +
        capitalize(enemy->query_pronoun()) + " is " + how + "!\n", enemy);

    if (enemy->query_hp() <= 0)
    {

        enemy->do_die(this_object());
    }
    
    return 1; /*  Important! Should not have two attacks in a round. */
}
