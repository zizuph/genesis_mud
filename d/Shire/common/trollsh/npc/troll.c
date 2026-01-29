inherit "/std/monster";
#include "/d/Shire/sys/defs.h"
#include "/d/Shire/common/trollsh/tunnel/local.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include "/d/Shire/common/make_money.h"

#define ARM "/d/Shire/common/trollsh/arm/"
#define WEP "/d/Shire/common/trollsh/weapon/"

// Prototypes
void help_friend(object ob);

create_monster()
{
    seteuid(getuid());
    if(!IS_CLONE)
        return;
    create_guards(random(4));
}


create_guards(int i)
{
    object wep, arm;
    int y,z;
    string *color, *troll_type;

// sets up arrays for different adjectives and types of trolls
 
    color  = (({"evil", "ferocious", "deadly", "horrible", "terrifying","snarling", "blood-thirsty", "powerful","terrible"}));
    troll_type  = (({"young", "large", "warrior",}));
 
 
// randomly chooses adjectives and type of troll to create

    y = random(sizeof(color));
    z = random(sizeof(troll_type));
 
    add_adj(color[y]);
    add_adj(troll_type[z]);
    add_prop(LIVE_I_NEVERKNOWN, 1);
 
    set_name("troll");
    add_adj(color[y]);
    add_adj(troll_type[z]);
    set_short(color[y] + " " + troll_type[z] + " troll");
    set_race_name("troll");
    set_long("This is a "+short()+". It is one of many trolls " +
        "that inhabit the Trollshaws and a terror to travellers. " +
        "It has thick skin and a terrible look about it. The " +
        "troll towers over you and looks very powerful and evil.\n");
     	      
    set_alignment(-500);
    set_gender(G_MALE);
    set_exp_factor(200);
     
    add_prop(CONT_I_WEIGHT, 500*1000);
    add_prop(CONT_I_HEIGHT, 450);
    add_prop(LIVE_I_SEE_DARK, 80);

    switch (troll_type[z]) // set's stats based on size
    {
        case "young": // young
        {
            set_stats(({100+random(50),
                100+random(50), 
                100+random(50), 
                90+random(20),  
                90+random(20), 
                100}));
            break;
        }

        case "large": // large
        {
            set_stats(({130+random(50),
                130+random(50), 
                140+random(50), 
                90+random(20),  
                90+random(20), 
                100+random(20)}));
            break;
        }
        case "warrior": // warrior
        {
            set_stats(({150+random(50),
                150+random(50), 
                150+random(50), 
                90+random(20),  
                90+random(20), 
                100+random(20)}));
            break;
        }
    }

//    set_hp(20000);
//    MAKE_MONEY;
    set_act_time(3);
    add_act("emote snarls savagely as blood drips from his mouth!");
    add_act("scream evil");
    add_act("emote sniffs the air for trespassers.");
    add_act("emote looks you up and down dangerously.");
    add_act("emote stares at you with hate in his eyes!");
    add_act("command extinguish pitch");
    make_gold(1+random(5));
     
    set_cact_time(2);
    add_cact("emote laughs pitifully at you.");
    add_cact("grin");
    add_cact("emote attacks you with added hate in his eyes.");
    add_cact("command extinguish pitch");

    set_skill(SS_WEP_AXE, 90);
    set_skill(SS_WEP_POLEARM, 90);
    set_skill(SS_WEP_SWORD, 90);
    set_skill(SS_WEP_CLUB, 90);
    set_skill(SS_WEP_KNIFE, 100);
    set_skill(SS_2H_COMBAT,90);
    set_skill(SS_DEFENCE, 95);
    set_skill(SS_PARRY, 100);
    set_skill(SS_AWARENESS, 81);
    set_skill(SS_BLIND_COMBAT, 100);
    set_aggressive(1);


    add_prop(LIVE_I_NEVERKNOWN, 1);
    

// Armours
    
    if(troll_type[z] == "warrior")
        arm = ({"rudeplate","leatherpl", "troll_torso", "rudeplate", "shield"})[random(5)];
    else
        arm = ({"rudeplate","leatherpl", "troll_torso", "rudeplate"})[random(4)];

    clone_object(ARM_DIR + arm)->move(TO);
    
    arm = ({"troll_helm", "troll_helm_steel", "troll_helm_iron"})[random(3)];
    clone_object(ARM_DIR + arm)->move(TO);
    
    arm = ({"greaves_steel", "greaves_steel2", "greaves_iron"})[random(3)];
    clone_object(ARM_DIR + arm)->move(TO);
    
    arm = "wgaunt";
    clone_object(ARM_DIR + arm)->move(TO);

// Weapons
    wep = ({"nastyclub","tr_scimitar","trollclub","trollaxe","trollmstar","trollhalb"}) [random(6)];
    clone_object(WEP_DIR + wep)->move(TO);

    command("wear armours");
    command("wield weapons");

    
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
//    if (query_attack())
//    	return;
//    if (random(3))
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
    	      command("emote snarls and attacks with inhuman strength.");
    	      break;
    	  case 1:
    	      command("snarl: You will taste good in a pot!");
    	      break;
    	  case 2:
    	      command("snarl: You should have never attacked us!");
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


int
special_attack(object enemy)
{
   object me;
   mixed* hitresult;
   string how;
   me = TO;
   if (random(5))
      return 0;
   hitresult = enemy->hit_me(200 + random(150), W_BLUDGEON, me, -1);
   how = " with a little effect";
   if (hitresult[0] > 0)
      how == " lightly";
   if (hitresult[0] > 5)
      how = " with his claws, leaving traces of blood behind";
   if (hitresult[0] > 10)
      how = " with his claws, gouging the flesh";
   if (hitresult[0] > 15)
      how = " with his claws, shredding flesh as he goes";
   if (hitresult[0] > 20)
      how = " with his claws, ripping flesh from the body";
   if (hitresult[0] > 25)
      how = " with his claws so hard, that blood runs from the wounds";
   if (hitresult[0] > 30)
      how = " with his claws, ripping large chunks of flesh and spraying blood everywhere";
   enemy -> catch_msg(QCTNAME(me) + " slashes you" + how + ".\n");
   tell_watcher(QCTNAME(me) + " slashes " + QTNAME(enemy) + " hard!\n"+
      capitalize(enemy->query_pronoun()) + " is slashed"+
      how + ".\n", enemy);
   if (enemy->query_hp() <= 0)
      enemy->do_die(me);
   return 1;
}
