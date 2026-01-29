#pragma save_binary

inherit "/std/creature";

#include "/d/Roke/common/defs.h"
#include "/d/Roke/common/qbits.h"
#include <macros.h>
#include <ss_types.h>
#include "../guild.h"

/* fierce drooling dragon protecting us from vampyrs entering the
   building */

#include <wa_types.h>

inherit "/std/combat/unarmed";
inherit "/std/act/action";

#define HOOKED_EMOTIONS ({ "hug" , "sigh" })
#define CHECK_ACTOR if (!present(actor, environment())) { return; }

void
default_config_npc(int i)
{
    int j;
    for(j=0;j<6;j++)
	set_base_stat(j,i);
}

void
create_creature()
{
    set_name("dragon");
    add_name("ddd");
    add_name("kaheda_dragon_quest");
    set_long("He belongs to the monks, who like\n"+
	     "to have him as their pet.\n");
    set_race_name("dragon");
    set_adj("cute");
    add_adj("drooling");
    set_alignment(500);
    default_config_npc(162);
    
    set_skill(SS_UNARM_COMBAT,100);
    set_skill(SS_DEFENCE,100);
    
    add_notify_meet_interactive("optiskfiberanka");
    
    add_leftover(CARISCA+"obj/skin","skin",1,"",1,1);
    
    set_attack_unarmed(0,  100, 100, W_IMPALE, 50, "jaws");
    set_attack_unarmed(1, 100, 100, W_BLUDGEON, 50, "heavy tail");
    set_hitloc_unarmed(0, ({ 100 }), 10, "head");
    set_hitloc_unarmed(1, ({ 100 }), 80, "body");
    set_hitloc_unarmed(2, ({ 100 }), 10, "tail");
    
    set_fatigue(9000);
    set_hp(40000);
    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    
}

int
query_knight_prestige()
{
    return -2;
}

#define QD(ob,x) (ob->test_bit("Roke",MAYORGROUP,x))

int
mayor(object ob) /* return current quest number of player */
{
    return 8*QD(ob,MAYORBIT1)+4*QD(ob,MAYORBIT2)+2*QD(ob,MAYORBIT3)+
	QD(ob,MAYORBIT4);
}

void
sigh()
{
    command("sigh");
    command("emote looks very lonely.");
}

void
emote_hook(string emote, object actor, string adverb)
{
    if (emote == "hug")
    {
       set_alarm(1.5, 0.0, &command("hug " + OB_NAME(actor)));
	return;
    }

    if (emote == "sigh")
    {
        set_alarm(2.0, 0.0, &sigh());
	return;
    }
}

void
emote_hook_onlooker(string emote, object actor, string adverb, object *targets)
{
    if (emote == "hug")
    {
       set_alarm(1.5, 0.0, &sigh());
	return;
    }
}

/* optiskfiberanka - takes care of some growling to vampyrs etc */

void eat();
void goaway();
void returnme();

void
enter_inv(object ob,object from)
{
    ::enter_inv(ob,from);
    
    if(function_exists("set_amount",ob)=="/std/food")
	if (mayor(TP)>4)
	    set_alarm(1.0, 0.0, eat);
	else
	    set_alarm(1.0, 0.0, goaway);
}

void
eat()
{
    command("eat all");
}

void
goaway()
{
    command("emote flies away to eat the food.");
    move_living("M",MONKS+"tree");
    command("eat all");

    set_alarm(30.0, 0.0, returnme);
}

void
returnme()
{
    move_living("home",query_prop(LIVE_O_LAST_ROOM));
}

kahedan_arrived(object who)
{
    if (!who || E(who) != environment()) return;

    switch (random(50))
    {
    case 0:
	command("lick " + OB_NAME(who));
	break;
	/* Maybe some more stuff here ? */
    }
}

optiskfiberanka()
{
    //if(TP->query_guild_name_occ()=="Vampyr guild") 
    if(TP->query_prop("_live_i_undead"))
	set_alarm(1.0, 0.0, &command("growl"));
    
    if (IS_MEMBER(TP))
	set_alarm(4.0, 0.0, &kahedan_arrived(TP));
    return;
}

init_living()
{
    ::init_living();
    
    add_action("north", "in");
}

int
north(string s)
{
    if(s)
	return 0;
    
    //if(TP->query_guild_name_occ()=="Vampyr guild")
    if(TP->query_prop("_live_i_undead"))
    {
	write("As you try to enter the building, the dragon grabs you\n"+
	      "and gives you a hard kick, making you fly through the air\n"+
	      "and land in a huge tree.\n");
	say("The drooling dragon grabs " + QCTNAME(TP) + " and kicks " +
	    TP->query_objective() + " high up in the air.\n");

	TP->move_living("M", MONKS + "tree");
	return 1;
    }
    return 0;
}

void
notify_you_killed_me(object ob)
{
    ob->catch_msg("You somehow feel that you shouldn't have done that.\n"+
		  "Dragons have parents too, you know.\n");
}
