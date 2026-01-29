/* A Guard Dog for Waymeet
 * 
 * Raymundo, Feb 2020
 *
 * Modification Log:
 *  - updated "me" variable to point to this_object() in special_attack
 *    (Petros, May 2020)
 */

inherit "/std/creature";
inherit "/std/act/attack";
inherit "/std/act/domove";
inherit "/std/combat/unarmed";   /* This gets us standard unarmed routines */
//inherit "/d/Shire/open/assist_friend.c";

#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>
#include "/d/Shire/common/lib/goodkill.h"
#include "/d/Shire/eastroad/western/local.h"
#include "/d/Shire/common/defs.h"
#include "/d/Shire/waymeet/defs.h"



#define A_BITE  1
#define A_LCLAW 2
#define A_TAIL	3
#define A_RCLAW 4

#define H_HEAD 1
#define H_BODY 2

//Setting up some adjectives for  the dogs.
#define ADJ_1	({"vicious", "nasty", "snarling", "drooling", "growling", "mean"})
#define ADJ_2	({"tawny", "brindle", "brown", "gray", "black"})
#define C_ADJ_1 ({"ankle-biting", "vicious", "agressive", "yappy", "tea-cup"})
#define C_ADJ_2 ({"brown", "tan", "dark-brown", "light-brown", "white", "black"})
#define P_ADJ_1	({"angry-looking", "protective", "hostile", "crazed", "muscular"})
#define P_ADJ_2 ({"spotted", "black-and-white", "tan", "black", "grey", "gray", "white"})
#define D_ADJ_1 ({"noble", "watchful", "crafty", "alert", "careful"})
#define D_ADJ_2 ({"black", "brown"})

#define HOBBIT_KILLER   "_i_kill_hobbits_"


#define KENNEL	WAYM_ROOM_DIR + "kennel"
string adj1, adj2, name;
int home_alarm;
void go_home();



create_creature()
{
	setup_dog();
	
	
    set_name("_guard_dog_");
	add_name("dog");
	add_name("puppy");
    set_race_name("dog");
	set_gender(random(2));
    set_long("@@my_long@@");
	
	set_monster_home(WAYM_ROOM_DIR + "kennel");
	set_restrain_path(({WAYM_DIR, EAST_R_DIR})); 

    set_skill(SS_DEFENCE, 80);
	set_skill(SS_UNARM_COMBAT, 80);
    set_skill(SS_SWIM, 80);
	
	add_prop(LIVE_I_SEE_DARK, 100); //Dogs have good night vision, so this seems reasonable.
	add_prop(LIVE_I_QUICKNESS, 100);
	add_prop(LIVE_I_NEVERKNOWN, 1);
	add_prop(NPC_I_NO_FEAR, 1);

    
    set_attack_unarmed(A_BITE,  20, 30, W_IMPALE, 40, "jaws");
    set_attack_unarmed(A_LCLAW, 40, 20, W_SLASH,  30, "left paw");
    set_attack_unarmed(A_RCLAW, 40, 20, W_SLASH,  30, "right paw");
	set_attack_unarmed(A_TAIL, 40, 40, W_BLUDGEON, 40, "tail");
   

    set_hitloc_unarmed(H_HEAD, ({ 15, 25, 20,}), 20, "head");
    set_hitloc_unarmed(H_BODY, ({ 10, 15, 30,}), 80, "body");
	
	 
}

int
special_attack(object enemy)
{
    object me = this_object();
    mixed *hitresult;
    string how;

    
    if (random(3))
    {
	return 0;  /* Continue with the normal attacks */
    }

    hitresult = enemy->hit_me(20+random(30), W_IMPALE, me, -1);
    switch (hitresult[0])
    {
        case 0:
            how = "unwounded";
            break;
        case 1..10:
            how = "barely wounded";
            break;
        case 11..20:
            how = "wounded";
            break;
        default:
            how = "seriously wounded";
            break;
    }

    enemy->catch_tell(me->query_The_name(enemy) + " tears into your throat!\n"+
		     "You are " + how + ".\n");
    tell_watcher(QCTNAME(me) + " tears into " + QTNAME(enemy) + "!\n" +
        capitalize(enemy->query_pronoun()) + " is " + how + ".\n", enemy);

    if (enemy->query_hp() <= 0)
    {
	enemy->do_die(this_object());
    }
    
    return 1; /*  Important! Should not have two attacks in a round. */
}


	void
setup_dog()
{
	
	int x;
	x = random(4);
	switch(x)
	{
		case 0:
		name = "chihuahua";
		
		adj1 = ONE_OF_LIST(C_ADJ_1);
	
		adj2 = ONE_OF_LIST(C_ADJ_2);
		add_name(name);
		set_short(adj1 + " " + adj2 + " " + name);
		set_adj( ({adj1, adj2, "guard"}) );
		
		/* str, con, dex, int, wis, dis */
		set_stats(({ 30, 40, 100, 5, 5, 80}));
		
		
		break;
		return;
		
		case 1:
		name = "pitbull";
		add_name("terrier");
		adj1=ONE_OF_LIST(P_ADJ_1);
		adj2=ONE_OF_LIST(P_ADJ_2);
			if(adj2=="black-and-white")
			{
				add_adj("black");
				add_adj("white");
				add_adj("black and white");
			}
		add_name(name);
		set_short(adj1 + " " + adj2 + " " + name);
		set_adj( ({adj1, adj2, "guard"}) );
		
		/* str, con, dex, int, wis, dis */
		set_stats(({ 80, 100, 40, 5, 5, 80}));
		break;
		return;
		
		case 2:
		name = "doberman";
		
		adj1=ONE_OF_LIST(D_ADJ_1);
		adj2=ONE_OF_LIST(D_ADJ_2);
		add_name(name);
		set_short(adj1 + " " + adj2 + " " + name);
		set_adj( ({adj1, adj2, "guard"}) );
		
		/* str, con, dex, int, wis, dis */
		set_stats(({ 70, 100, 50, 5, 5, 80}));
		break;
		return;
		
		case 3..4:
		name = "mastiff";
		
		adj1=ONE_OF_LIST(ADJ_1);
		adj2=ONE_OF_LIST(ADJ_2);
		add_name(name);
		set_short(adj1 + " " + adj2 + " " + name);
		set_adj( ({adj1, adj2, "guard"}) );
		
		         /* str, con, dex, int, wis, dis */
		set_stats(({ 120, 100, 120, 5, 5, 80}));
		break;
		return;
	}
}	

string
my_long()
{
	return("This " + query_short() + " looks ready to protect its "
		+ "owner. A " + name + " like this is not something to be "
		+ "trifled with!\n");
}

public void
enter_env(object dest, object old)
{
    string	destname,
		tmpstr;

    ::enter_env(dest, old);
    if (home_alarm)
    {
	return;
    }

    destname = file_name(dest);
    if ((sscanf(destname, (WAYM_DIR + "%s"), tmpstr)) ||(sscanf(destname, (EAST_R_DIR + "er12"), tmpstr)))
    {
	return;
    }

    home_alarm = set_alarm(30.0, 0.0, go_home);
}

public void
go_home()
{
    string	here = file_name(environment(this_object()));

    home_alarm = 0;
    if (here != KENNEL)
    {
    	log_file("guard_dog",
	    ctime(time()) + " moved from " + here + " to kennel.\n");
		say("The " + TO->query_short() + " realizes that " + HE_SHE(TO)
			+ " is too far from the hobbits of Waymeet to protect them, "
			+ "so " + HE_SHE(TO) + " returns to " + HIS_HER(TO) 
			+ " kennel.\n");
	move_living("M", KENNEL);
    }
}
void
check_combat()
{
	
	if(!TO->query_attack())
	{
		say("The " + TO->query_short() + " loses the scent of " 
			+ HIS_HER(TO) + " prey, and so returns to the "
			+ "kennel--for now.\n");
		remove_object();
		return;
	}
	else
	{
		set_alarm(30.0, 0.0, check_combat);
	}
}

/*
 * Function name:   attack_object
 * Description:     Start attacking, the actual attack is done in heart_beat
 * Arguments:       The object to attack
 */
public void
attack_object(object ob)
{
    ::attack_object(ob);
	//start_follow(ob);
	check_combat();
	add_prop(LIVE_O_ENEMY_CLING, ob);

}
