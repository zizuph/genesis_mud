inherit "/std/monster";
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/common/make_money.h"

// Prototypes
void help_friend(object ob);

#define ADJARRAY ({ "red-eyed","strong","hideous","grim" })

#define LONG_DESC ({\
	"has some red staring eyes. He looks strong and ready to fight anyone who dares.\n",\
	"looks like he would kill anyone. His face looks wild and you really wonder "+\
	    "what evil he is thinking of.\n",\
	"is large and hideous looking and with a red, hissing tongue which "+\
	    "look like it has eaten strange things...\n",\
	"looks grim and is obviously lurking on something evil. Better stay away from him..\n"})

#define HISHEIGHT ({ 350, 300, 320, 329 })

#define HISWEIGHT ({ 300, 400, 360, 340 })

#define HISSTAT ({\
		({ 150, 80, 125, 80, 60, 120 }), \
		({ 154, 97, 165, 70, 88, 120 }), \
		({ 166, 78, 152, 90, 100, 120 }),\
		({ 140, 69, 133, 77, 94, 120 }), })

create_monster()
{
    seteuid(getuid());
    if(!IS_CLONE)
        return;
    create_guards(random(4));
}

create_guards(int i)
{
    set_name(({"troll guard", "guard", "_troll_guard_","black troll"}));
    set_pname("trolls");
    set_pshort("troll guards");
    set_adj(ADJARRAY[i]);
    set_race_name("troll");
    set_long(
        "This troll very large and evil looking. It's taller " +
        "than a human and has a thick, black hide. Its arms are " +
        "as thick as timbers and towers over everything. The " +
        "troll has a blood-thirsty look in its eyes and " +
        "probably fears nothing. This creature " +LONG_DESC[i]);
    	
    add_prop(CONT_I_WEIGHT, HISWEIGHT[i]);
    add_prop(CONT_I_HEIGHT, HISHEIGHT[i]);
    add_prop(LIVE_I_SEE_DARK, 10);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop("_live_m_no_drain", 1);
    set_stats(HISSTAT[i]);
    set_alignment(-300 - random(150));
    set_aggressive(1);
    set_attack_chance(100);
    set_pick_up(100);
    
    set_skill(SS_WEP_CLUB, 100);
    set_skill(SS_WEP_AXE, 80);
    set_skill(SS_WEP_SWORD, 80);
    set_skill(SS_PARRY, 50);
    set_skill(SS_DEFENCE, 40);
    set_skill(SS_BLIND_COMBAT, 40);
    
    set_act_time(2);
    add_act("say Wat is you dong hrr?????");
    add_act("emote glares stonily at you, watching your every move.");
    add_act(({"say First I will rip your tongue out!!", "say Then I will tear the skin off you!",
    	      "say Me gonna eat your brains!!","say AND at last me will eat around your bones!!"}));
    add_act(({"emote raises his voice up to a horrifying inferno!!!","scream"}));
    add_act("emote looks at you with complete disgust in his eyes!");
    add_act("emote prepares his weapon for combat!");
    add_act("emote carefully inspects his armour.");
    
    set_cact_time(2);
    add_cact("shout You're no good!");
    add_cact("emote attacks you with a blood-thirsty look in his eyes.");
    add_cact("shout That no hurt one bit!");
    add_cact("emote shouts something in a gutteral language.");
    add_cact("stomp");
    add_cact("emote charges you with renewed anger.");
    add_cact("emote screams at you and charges.");
    
    set_alarm(2.0,0.0,"arm_me");
    
}

arm_me()
{
    string arm = ({"rudeplate","leatherpl", "troll_torso", "rudeplate"})[random(4)];
    clone_object(TROLLSH_DIR + "arm/" + arm)->move(TO);
    command("wear all");
    //string wep = ({"tr_scimitar","lost_sword"})[random(2)];
    clone_object(TROLLSH_DIR + "weapon/tr_scimitar")->move(TO);
    command("wield all");

}


void
attacked_by(object ob)
{
    object *arr;
    int    i;
    
    ::attacked_by(ob);

    arr = (object *)query_team_others();
    for (i = 0; i < sizeof(arr); i++)
        arr[i]->notify_ob_attacked_me(TO,ob);
}

void
notify_ob_attacked_me(object friend, object attacker)
{
    if (query_attack())
    	return;
    if (random(3))
        set_alarm(1.0, 0.0, &help_friend(attacker));
}

void
help_friend(object ob)
{
    if (ob && !query_attack() && present(ob, environment()))
    {
    	command("kill "+ lower_case(ob->query_real_name()));
    	switch(random(3))
    	{
    	  case 0:
    	      command("say You pitful mortal, think you can defeat us ????");
    	      break;
    	  case 1:
    	      command("say HAHAHA You got no chance looser!!!");
    	      break;
    	  case 2:
    	      command("shout GEEEZZZZ He is really trying to tickle us, wow!!");
    	      break;
    	}

	command("assist");
    }
}  
public void
do_die(object killer)
{
   killer->add_prop("_i_killed_trollshaw_trolls",killer->query_prop("_i_killed_trollshaw_trolls") + 1);

     ::do_die(killer);

}

int
query_knight_prestige()
{
    int i;

    i = this_object()->query_average_stat();
    i = i * i / 1;
    return i;
}
