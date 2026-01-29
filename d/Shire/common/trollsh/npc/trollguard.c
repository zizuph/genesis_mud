inherit "/std/monster";

#include "defs.h"
#include "/d/Shire/common/monster/rdefs.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <filter_funs.h>
#include <language.h>
#include "/d/Shire/common/make_money.h"

#define TROLL_HOME "/d/Shire/common/trollsh/shaws16"

#define ADJDESC ({ "red-eyed","brown-eyed","hideous","muscular","grey",\
		   "ghastly","quarrelsome","greedy"})

#define LONGDESC ({\
	"looks fierceful and very powerful, with it's red-eyes "+\
    "which look like they can kill only by sight he would make "+\
    "an awesome enemy if anyone dared to attack!\n",\
	"looks kind of stupid. He surely can not know how to swing a weapon..\n",\
	"looks ugly and has a good reason for being here. His face could make "+\
    "even your mother puke!!\n",\
 	"appears very big and powerful, his arms like a thick tree and his body... "+\
	"if he could get his arms around you...you would not breath for a long time ...\n",\
	"has a grey colored scale and looks very frightening. But his eyes are just "+\
    "rolling round in his head... obviously he must be very stupid!\n",\
 	"is ghastly looking and has a mighty appearance! No one would dare to fight him.\n",\
    "has intestines hanging out of his mouth. He drools when looking at you ..\n",\
	"has some greedy looking eyes. He would not hesitate stealing your "+\
    "money or anything precious he could find.\n" })

#define TROLLSTAT ({ \
  		    ({ 120, 60,100, 40, 20, 90 }),\
  		    ({ 130, 40,130, 40, 30, 85 }),\
  		    ({ 140, 70,170, 60, 20,190 }),\
  		    ({ 150, 30,170, 40, 20, 90 }),\
  		    ({ 100, 60, 90, 50, 40, 70 }),\
  		    ({ 134, 75,135, 50, 32, 65 }),\
  		    ({ 112, 85,152, 32, 45, 78 }),\
  		    ({  96, 60, 85, 45, 67, 84 }) })

/*
int randy(int ran)
{
    return ran-ran/4+random(ran/2)+10;
}
*/

object troll;

create_monster()
{
    seteuid(getuid());
    if(!IS_CLONE)
        return;
    create_troll_guard(random(8));
}

create_troll_guard(int r)
{
    set_name(({"troll guard","guard","wild-troll","_guard_troll_"}));
    set_pname("guards");
    set_short(ADJDESC[r] + " troll guard");
    set_pshort("troll guards");
    set_race_name("troll");
    set_adj(ADJDESC[r]);
    set_long("This is one of the trolls guarding the tunnels under the "
    	    +"trollshaws. The troll, or wild-troll has a black scaly hide "
    	    +"and is extremly tough. They shun sunlight, and most of them "
    	    +"will turn into stone if they are struck by it. They prefer "
    	    +"the illumination of fire to the glistering aura of the moon. "
              +"These trollsoldiers are a horrible enemy as they fear no living "
	    +"thing. This wild-troll " + LONGDESC[r] );
	       
    add_prop(CONT_I_WEIGHT, (300 + random(100)*1000));
    add_prop(CONT_I_HEIGHT, (300 + random(75)));
    	    
    set_stats(TROLLSTAT[r]);
    
    troll->set_restrain_path( ({"shaws1","shaws2","shaws3","shaws4","shaws5",
    			"shaws6","shaws7","shaws8","shaws9","shaws10",
    			"shaws11","shaws12","shaws13","shaws14","shaws15",
    			"shaws16","shaws17","shaws18","shaws19","shaws20",
			"shaws21","shaws22","shaws23","shaws24","shaws25" }));
    set_monster_home(TROLL_HOME);
    set_random_move(random(5));
        
    set_alarm(3.0,0.0,"arm_me");
    set_alignment(-400 -random(150));
    set_aggressive(1);
    set_attack_chance(50);
    set_pick_up(0);
    
    set_skill(SS_UNARM_COMBAT, 100);
    set_skill(SS_DEFENCE, 70);
    set_skill(SS_PARRY, 90);
    set_skill(SS_WEP_CLUB, 50);
    
    MAKE_MONEY;
    
    set_act_time(3);
    add_act("ponder");
    add_act("scream");
    add_act("peek all");
    add_act("emote picks some guts out of his teeth!!");
    add_act("stomp");
    add_act(({"emote screams: Me hopes the sun will stay low!","tremble"}));
    add_act("shouts: I will eat your corpse when i'm done with you!");
      add_act("say Why do I always get stuck outside? I want to be underground.");
    add_act("say You're no match for me!");
    add_act(({"emote screams with a horrible noise!","emote screams: AAAAAARGGGHH!!!"}));
    
    set_cact_time(2);
    add_cact("time");
    add_cact("say This was your worst mistake!");
    add_cact("knee all");
    add_cact("say Why don't you just leave before me eats you???");
    add_cact("scream");
    add_cact("emote punches his fist right into your face.");
    add_cact("emote grabs your head with his huge fist and throws you away!!");
    add_cact("say You'll like it in the underground tunnels.");
    set_alarm(1.0,0.0,"check_time");
    
    
}

arm_me()
{
    clone_object(TROLLSH_DIR + "arm/rudeplate")->move(TO);
    command("wear all");
}    

string
check_time()
{
	if(EO->is_it_sun() && !(EO->query_prop(ROOM_I_INSIDE)) && !random(3))
	{
	    command("scream");
	    command("panic");
	    command("shout DAMN SUN!!!");
	    command("emote looks for a good place to hide from the sun");
	    return "";
	}
}

int
query_knight_prestige()
{
    return 400 + random(200);
}
    
public void
do_die(object killer)
{
killer->add_prop("_i_killed_trollshaw_trolls",killer->query_prop("_i_killed_trollshaw_trolls") + 1);
    ::do_die(killer);
}
