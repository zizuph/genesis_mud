#include <wa_types.h>
#include <formulas.h>
#include <composite.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <cmdparse.h>
#include <tasks.h>
#include <macros.h>
#include <ss_types.h>
#include "../nov.h";

inherit "/std/monster";
inherit "/std/combat/unarmed";


#define TO this_object()
#define TP this_object()


object PLAYER;
string p_name;

int mspecial_attack();




void
destruct_skeleton()
{
   tell_room(environment(), this_object()->short() +" collapses into a pile of dust!\nThe pile of " +
   "dust fades away!\n");
        remove_object();
}



string
adj_ran()
{
    int i;
    i = random(4);
    switch (i)
    {
    case 0:
        return "";
        break;
    case 1:
        return "wicked brown";
        break;
    case 2:
        return "leering white-boned";
        break;
    default:
        return "loose-jawed stumbling";
        break;
    }
}



void
create_monster() 
{
    string ran;
    
    int AL, UP, s, de, c, i, w, d;
    
   AL = p_name->query_alignment();
   UP = p_name->query_stat(8)/4;
    s = p_name->query_stat(0);
    d = p_name->query_stat(1);
    c = p_name->query_stat(2);
    i = p_name->query_stat(3);
    w = p_name->query_stat(4);
    d = p_name->query_stat(5);
    
    
   
    
    
   // ran = adj_ran();
    set_name("skeleton");
    set_race_name("skeleton");
    //set_adj(ran);
    //set_short(ran+" skeleton");
    set_short("old decaying skeleton");
    set_long("This is an old decaying skeleton mage.\nIt's animated by a necromancer.\n");
    set_gender(G_NEUTER);
    //set_stats(({s,de,c,i,w,d}));
    set_stats(({120,120,120,120,120,120}));
    
    set_skill(SS_DEFENCE, 50);
    set_skill(SS_PARRY, 50);
    
    add_prop(LIVE_I_SEE_DARK, 10);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(OBJ_I_WEIGHT, 6500);
    add_prop(OBJ_I_VOLUME, 3500);
    add_prop(LIVE_I_UNDEAD, UP);   
    set_alignment(AL);
   
   
    set_act_time(6);
    add_act("grin");
    add_act("emote disconnects its skull and begins to toss it in the air.");
    add_act("emote tells a fact: Bravery have killed plenty, but not saved a " +
    "single soul.");
    add_act("emote says: Rangers fits best as orcstew for the forces of Mordor.");
    add_act("say The Calians misunderstood the design of their wolfhead-hats...it was " +
    "supposed to look like a chicken-head.");
    add_act("emote sings: ..And the Knight of Solamnia Bravely ran away, Heehee..HooHooo..Haaahaaa!");
    add_act("emote complains: Why do our Masters always put us to clean the " +
    "halls, removing the cobwebs, lifting heavy objects and other insane " +
    "labours? My back is arching!");
    add_act("emote laughs evilly: MUUUHUHUUHAHAHAAAHAAA!! I am the evil hound of hell, the " +
    "Doombringer of Asmodeus, the Plague of the living! MUUHAHAHAHHAAAA!!");
    add_act("emote mutters something about the fortune it made by giving some of its " +
    "teeth to the tooth-faerie.");
    set_cact_time(1);
    add_cact("say HIIHIIHIHIIIHIHEHEHAAAAHAHAHAAAA!!");
    add_cact("say I love hurting you! Taste my lethal magic, filth!");
    add_cact("say Master, this one is Mine!");
    add_cact("say Master, can I have the skull of this one for my collection?");
    add_cact("say I am a lich! MUUHAAAHAHAHA!!!......Or, I wish I was.");
    set_attack_unarmed(0, 0, 0, W_IMPALE, 10, "left arm");
    set_attack_unarmed(1, 0, 0, W_SLASH, 10, "right arm");
   
    set_hitloc_unarmed(0,5,15,"head");
    set_hitloc_unarmed(1,5,10,"left arm");
    set_hitloc_unarmed(2,5,10,"right arm");
    set_hitloc_unarmed(3,5,45,"body");
    set_hitloc_unarmed(4,5,20,"legs");

    
    set_mm_in("walks in.");
    set_mm_out("walks out.");

    
         setuid();
    seteuid(getuid());
    
   
    set_alarm(9999.0,0.0, &destruct_skeleton());
}



void
notify_you_killed_me(object who)
{
    object *obj;
    command("emote cackles!");
    command("emote yells: HIHIHEHAHAHAA!!  I killed this one, Master!");
    //command("emote kicks the corpse of "+ who->query_name()+ ".");
}

void
do_die(object killer)
{
    command("emote moans: Maasteerr....I doont feel sooo good...");
    command("scream");
    ::do_die(killer);
}




int
cast_skelspell()
{
	if (!this_object()->query_attack())
	{
		this_object()->command("say Assist you with attacking who, Master?\n");
		this_object()->remove_prop(IAMASSISTINGM);
		return 1;
	}
	
	mspecial_attack();
	return 1;
}


int
mspecial_attack()
{
	
    object me, enemy;
    int pen;
    string how;
    me = this_object();

     enemy = PLAYER->query_attack();

     
   /* if (!present(enemy, environment(this_object())))
    {
    	me->command("say Where is the enemy, Master?\n");
    	return 1;
     }*/  

     if (!this_object()->query_prop(IAMASSISTINGM))
     {
     	me->command("say Slowing down, Master.\n");
     	return 1;
     }


     
    pen = 100 + random(200);
     
    enemy->hit_me(pen, MAGIC_DT, me, -1);
 
    tell_watcher(QCTNAME(me)+" yells: AAaaaaHAaahaaa!!!\nWe will be serving "+enemy->query_race_name()+"s " +
    "for dinner tonight, Master!\n",me);
     
    enemy->catch_msg(QCTNAME(me) + " gestures slightly " +
    "with "+me->query_possessive()+" skeletal hands!\n"+QCTNAME(me)+" fries you with a " +
    "lightningbolt!\n");

    tell_watcher(QCTNAME(me)+" gestures slightly with "+me->query_possessive()+ " skeletal " +
    "hands!\n"+QCTNAME(me)+" fries "+QCTNAME(enemy)+" with a lightningbolt!\n",
                 me, enemy);

    if(enemy->query_hp() <= 0) enemy->do_die(me);
    
    set_alarm(10.0,0.0, &cast_skelspell());

    return 1;
}




int
do_skelsay(string str)
{
    
    if(!str)
        { 
        write("skelsay what?\n");
        return 0;
        }
        
    write("Your "+short()+" says: "+str+"\n");
    say("The "+short()+" says: "+
    str+"\n");
    return 1;

}

void
goto_player()
{
    
    if (PLAYER->query_prop("_player_s_ld_in_room"))
    {
    	PLAYER->remove_prop(IHAVESKELPET);
    	destruct_skeleton();
    	return;
    }

	
    if(environment(PLAYER) != environment(TO)) move_living("X", environment(PLAYER));
}


/*int
do_skeleye(string str)
{
    object *ob;
    if(!str)
        return 0;

    ob = parse_this(str,"[the] %l");
    if(!sizeof(ob))
        return 0;
    write("The "+short()+" standing next to you eyes "+
    ob[0]->query_the_name(TP)+" warily.\n");
    tell_room(E(TP),"The "+short()+" standing next to "+QTNAME(TP)+
    " eyes "+QTNAME(ob[0])+" warily.\n",({TP,ob[0]}));
    tell_object(ob[0],"The "+short()+" standing next to "+
    TP->query_the_name(ob[0])+" eyes you warily.\n");
    return 1;
}*/


/*int
do_skelplay(string str)
{
	if (!present(this_object(), "_playob")))
	{
		write("Your skeleton mage dont want to play the shufflegame " +
		"right now.\n");
	
		return 1;
	}
	
	return 1;
}*/


	

int
do_assistm()
{
	
	
	if (this_player()->query_real_name() != p_name)
	{
		write("What ?\n");
		return 1;
	}
	
	if (this_object()->query_prop(IAMASSISTINGM))
	{
		write("Your pet is assisting you already!\n");
		return 1;
	}
	
	this_object()->command("assist "+p_name);
	this_object()->command("say Assisting you, Master!\n");
	
	this_object()->add_prop(IAMASSISTINGM, 1);
	cast_skelspell();
	
	return 1;
}


int
do_skelwith()
{
	
	
	if (!this_object()->query_prop(IAMASSISTINGM))
	{
		write("You order your skeleton mage to withdraw from battle.\n");
		this_object()->command("say I am not currently assisting you in combat, Master.\n");
		return 1;
	}
	
	write("You order your skeleton mage to withdraw from battle.\n");
	this_object()->command("say Withdrawing from combat, Master.\n");
	
	
	this_object()->remove_prop(IAMASSISTINGM);
	
	return 1;
}

int
do_skeldism()
{
	if (this_player()->query_real_name() != p_name)
	{
		write("What ?\n");
		return 1;
	}
	
	this_object()->command("say As you wish, Master.\n");
	destruct_skeleton();
	
	return 1;
}



int
do_skelwear()
{
	
	this_object()->command("say Okay, Master.");
	this_object()->command("wear all");
	
	return 1;
}

int
do_skeldrop()
{
	
	this_object()->command("say Very well, Master.");
	this_object()->command("remove armours");
	this_object()->command("drop armours");
	
	return 1;
}


void
init_living()
{
    ::init_living();
     add_action(do_assistm, "skelassist");
     add_action(do_skeldism, "skeldismiss");
     add_action(do_skelwith, "skelwithdraw");
     add_action(do_skelwear, "skelwear");
     add_action(do_skeldrop, "skeldrop");
     add_action("do_skelsay","skelsay");
}

void
init_pet(object pl)
{
    PLAYER = pl;
    p_name = PLAYER -> query_real_name();
    set_alarm(0.0, 1.0, goto_player);
   
}
