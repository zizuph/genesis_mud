/*
 * Mekillot : Athasian beast. This one is part of a
 * caravan. Has some agression code added. Kick it
 * 6 times and it becomes aggressive. kick it 8 times
 * and it attacks. You can also calm it if you got
 * animal handling over 45.
 *
 * Azazel 2002
 */
#pragma strict_types

#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>
#include <stdproperties.h>
#include <macros.h>

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/action";
inherit "/std/act/attack";

#define A_BITE  0
#define A_TONGUE 1

#define H_HEAD 0
#define H_BODY 1
#define H_UNDER 2
#define H_R_L_LEG 3
#define H_R_R_LEG 4
#define H_F_L_LEG 5
#define H_F_R_LEG 6

/*
 * g_aggr tells how pissed off the mekillot is.
 */
int g_aggr;

string *randadj1, *randemote1, *randemote2;

int aggr();

void
create_creature()
{
    g_aggr = 20; 
	
    randadj1 = ({ "docile", "agressive", "slow", "agitated" });

    if (!random(5))
        add_leftover("/d/Cirath/altaruk/npc/leftover/chitin", "chitin", 1, 0, 1, 1);
    if (!random(5))
        add_leftover("/std/leftover", "skull", 1, 0, 1, 1);
    if (!random(5))
        add_leftover("/std/leftover", "toe", random(5) + 1, 0, 0, 1);
    if (!random(5))
        add_leftover("/std/leftover", "heart", 1, 0, 0, 1);
    if (!random(5))
        add_leftover("/std/leftover", "eye", 2, 0, 0, 0);
    if (!random(5))
        add_leftover("/std/leftover", "kidney", 2, 0, 0, 1);
    if (!random(5))
        add_leftover("/std/leftover", "intestine", 2, 0, 0, 1);

    set_name("mekillot");
    set_race_name("mekillot");
    set_adj("huge");
    add_adj(randadj1[random(sizeof(randadj1))]);
    set_long("These mighty lizards can weigh up to six tons" +
        " and their bodies can be as long as thirty feet." +
        " A thick shell cover its head and body. A mekillot" + 
        " is never realy tame so dont mess with it. ");
    
    add_prop(LIVE_I_NEVERKNOWN,1);
    
    set_aggressive(&aggr());
    
    set_stats(({ 160, 80, 160, 30, 30, 180 }));

    set_skill(SS_UNARM_COMBAT, 75);
    set_skill(SS_DEFENCE, 60);
    
    set_attack_unarmed(A_BITE,  50, 40, W_BLUDGEON, 30, "mouth");
    set_attack_unarmed(A_TONGUE, 30, 20, W_SLASH,  70, "tongue");
 
    set_hitloc_unarmed(H_HEAD, ({ 30, 25, 30,}), 20, "head");
    set_hitloc_unarmed(H_BODY, ({ 30, 20, 50,}), 40, "body");
    set_hitloc_unarmed(H_UNDER, ({ 15, 10, 10,}), 6, "underside");
    set_hitloc_unarmed(H_R_L_LEG, ({ 15, 15, 20,}), 7, "rear left leg");
    set_hitloc_unarmed(H_R_R_LEG, ({ 15, 15, 20,}), 7, "rear right leg");
    set_hitloc_unarmed(H_F_L_LEG, ({ 15, 15, 20,}), 10, "front left leg");
    set_hitloc_unarmed(H_F_R_LEG, ({ 15, 15, 20,}), 10, "front right leg");        

   set_act_time(12);
   add_act("stomp");
   add_act("emote moves its head around and eyes you hungerly.");
   add_act("stomp");
   add_act("emote gives off a low rumbling sound.");
   add_act("blank");
   set_cact_time(6);
   add_cact("roar");
   add_cact("roar loud");
   add_cact("spit enemy");
   add_cact("emote throws its head about and roars out loud!");
   add_cact("emote snaps its mouth at you");
   
   trig_new("%w 'killed' %s", "eat_corpse");
}


public void
emote_hook(string emote, object actor, string adverb = 0)
{
    randemote1 = ({ "happily", "contentedly", "merrily", "joyfully" });
    randemote2 = ({ "angrily", "ill-temperedly", "unhappily", "menacingly" });


    switch (emote)
    {
    case "pet":
    case "cuddle":
    case "ruffle":
    case "pat":
    case "kiss":
    case "lick":
    case "fondle":
    case "hug":
	command ("emote rumbles " +
	    randemote1[random(sizeof(randemote1))] + ".");
	break;
	
    case "poke":
    case "kick":
    case "swear":
    case "spit":
    case "curse":
    case "tackle":
        g_aggr = g_aggr + 15;
	if (g_aggr <= 119)
	command ("emote roars " +
	    randemote2[random(sizeof(randemote2))] + ".");
	else
        command("kill all");
		 
	break;
    }
}

int aggr()
{

    if (g_aggr >= 100)
        return 1;
    return 0;
}

void
init_living()
{
    ::init_living();

    add_action("calm_down", "calm");
}

int
calm_down(string str)
{
    notify_fail ("what do you want to calm down?\n");
    if (str == "mekillot")
    {
    	g_aggr = (g_aggr - this_player()->query_skill(SS_ANI_HANDL) + 45);
    	write ("You use every trick you know on animal handling to" +
    	    " calm the huge lizard.\n");
    	say(QCTNAME(this_player()) + " tries to calm the huge mekillot.\n");
        return 1;
    }
    return 0;
}

void eat_corpse()
{
	int i;
    object *corpse;
    corpse = deep_inventory(environment(this_object()));

    for(i = 0; i < sizeof(corpse); i++)
    {
        command("emote wraps its tongue around the" +
        " corpse and swallows it whole!\n");
        corpse[i]->remove_object();
        
        return;
    }
}
