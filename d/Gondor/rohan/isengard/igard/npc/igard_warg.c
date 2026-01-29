/*
 * This file is IGARD_NPC + "igard_warg"
 *
 *  Based on the Shire warg.
 *  Which was coded by Igneous.
 *  Last modified by Alto, 28 October 2001.
 *
 */

#pragma strict_types

inherit "/d/Genesis/steed/steed";
inherit "/std/act/action.c";

#include <language.h>
#include <macros.h>
#include <formulas.h>
#include <wa_types.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "../igard_defs.h"

#define A_BITE  0
#define A_LPAW  1
#define A_RPAW  2

#define H_HEAD  0
#define H_BODY  1
#define H_LPAW  2
#define H_RPAW  3
#define H_LHLEG 4
#define H_RHLEG 5

public string   long_desc();
public void     long_text();
public string   alignlook();
public string   alignlook2();
public void     sniff(object player);

string long_looks;
object actor;
int Sniff_id, gExtras;

string
alignlook() 
{
   string *alignlooks = ({"powerful", "sneaky", "muscular", "insane",
       "rabid", "lanky", "panting", "drooling", "angry", "sinister",
       "mangy","flea-bitten","pacing", "ugly", "fierce","dangerous",
       "skulking", "furtive", "nervous"});
   return ONE_OF_LIST(alignlooks);
}


string
alignlook2() 
{
   string *alignlooks = ({"brown", "grey", "white", "black"});
   return ONE_OF_LIST(alignlooks);
}

void
long_text()
{
    switch (random(3))
    {
    case 0:
       long_looks = CAP(LANG_ADDART(implode(query_adjs()," ")))
       + " warg that stands taller at the shoulder than any wolf known "
       + "to the forests of Gondor. This creature has been specifically "
       + "bred for war in the dens below Isengard. It is long of body "
       + "and lanky of limb, and yet these attributes seem more designed "
       + "for cunning swiftness than the result of undernourishment.\n";
	      break;
    case 1:
       long_looks = CAP(LANG_ADDART(implode(query_adjs()," ")))
       + " warg bred in the warrens below Isengard. It has broad muscular "
       + "shoulders and relatively short limbs with claws that seem "
       + "especially useful for tearing and rending the flesh of its "
       + "its victims. It stares balefully at you with haunting yellow "
       + "eyes.\n";
	      break;
    case 2:
       long_looks = "This " + (implode(query_adjs()," "))
       + " warg looks like a cross between a timberwolf and a mule. "
       + "Its broad triangular head is lowered such that it always "
       + "seems to be looking at you from beneath its eyelids. Strong "
       + "legs descend from a barrel-shaped torso, and a large bushy "
       + "tail points straight outward from behind. Saliva drips from "
       + "its open mouth, and you see many jagged teeth contained "
       + "therein.\n";
	      break;
    default:
        break;
    }
}


public void
create_steed()
{
    int rnd = random(11);

    set_name("warg");
    add_name("wolf");
    add_name("_igard_warg");
    add_name("_igard_monster");
    set_race_name("warg");
    set_pname("wargs");
    add_pname("wolves");
    set_adj(alignlook());
    add_adj(alignlook2());
    long_text();
    set_long(&long_desc());
    set_short(alignlook() + " " + alignlook2() + " warg");

    set_gender(G_MALE);

    set_stats(({55 + rnd, 75 + rnd, 70 + rnd , 40, 20, 70 + rnd}));

    set_skill(SS_DEFENCE, 50 + random(21));
    set_skill(SS_AWARENESS, 80 + random(26));  // Great sense of smell
    set_skill(SS_TRACKING, 60 + random(26));
    set_skill(SS_LOC_SENSE, 50 + random(16));
    set_skill(SS_HUNTING, 80 + random(6));
    set_skill(SS_CLIMB, 40 + random(11));
    set_skill(SS_SWIM, 30 + random(16));

    allow_mounted_combat(1);
    set_max_riders(2);   

    set_stuffed(TO->query_prop(LIVE_I_MAX_EAT));
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_I_NO_FEAR, 1);     // Fearless Animal

    set_alignment(-250 - rnd * 10);

    add_prop(CONT_I_HEIGHT,   160 + rnd / 2);
    add_prop(CONT_I_WEIGHT, 80000 + rnd * 400);
    add_prop(CONT_I_VOLUME, 75000 + rnd * 400);    
    add_prop(LIVE_I_SEE_DARK, 4);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(LIVE_I_SEE_DARK,   2);

    set_act_time(15);
    add_act("emote sniffs the ground carefully.");
    add_act("emote raises his head and howls loudly.");
    add_act("emote stares balefully at you.");
    add_act("growl");
    add_act("emote wags his tail back and forth.");
    add_act("emote smells you curiously.");
    add_act("emote pants loudly.");
    add_act("emote suddenly shakes from head to tail.");

    set_cact_time(2 + random(2));
    add_cact("emote gnashes his teeth and howls angrily."); 
    add_cact("emote rests on his hindlimbs and suddenly springs forward."); 
    add_cact("growl"); 
    add_cact("emote lowers his head and charges."); 
    add_cact("emote cries: Waaaooooo-waaaooooo-waaaoooooooooooooo."); 

    clone_object(IGARD_OBJ + "wargskin")->move(TO);

}


void
configure_steed()
{
    set_attack_unarmed(A_BITE, 35, 30, W_IMPALE | W_SLASH, 50, "gaping jaws");
    set_attack_unarmed(A_RPAW, 25, 15, W_SLASH,            25, "right claw");
    set_attack_unarmed(A_LPAW, 25, 15, W_SLASH,            25, "left claw");

    set_hitloc_unarmed(H_HEAD,  20, 10, "head");
    set_hitloc_unarmed(H_BODY,  45, 40, "barrel-chested body");
    set_hitloc_unarmed(H_LPAW,  25, 15, "left forepaw");
    set_hitloc_unarmed(H_RPAW,  25, 15, "right forepaw");
    set_hitloc_unarmed(H_LHLEG, 15, 10, "left hindleg");
    set_hitloc_unarmed(H_RHLEG, 15, 10, "right hindleg");
}


public int
can_mount(object o)
{
    if (o->query_race() != "orc")
        {
        write("The warg refuses to be mounted by the likes of you!\n");
       	return 0;
        }
    if (!gExtras)
    {
       	MODIFY_PROP(o, LIVE_I_QUICKNESS, 50);
       	ADD_SKILL(o, SS_DEFENCE, o->query_skill(SS_RIDING) / 10);
       	gExtras = 1;
    }
    return 1;
}

int
can_dismount(object o)
{
    if (gExtras)
    {
       	MODIFY_PROP(o,LIVE_I_QUICKNESS, -50);
       	ADD_SKILL(o, SS_DEFENCE, -(o->query_skill(SS_RIDING) / 10));
	       gExtras = 0;
    }
    return 1;
}



string
long_desc()
{
    return long_looks;
}


public int
can_lead(object player)
{
   ::can_lead();
   if (player->query_race() != "orc")
   {
      	return 0;
   }

   player->catch_tell("You grasp the warg by the nape of its neck and "
       + "begin leading it.\n");
   return 1;
}


void
init_living()
{
    ::init_living();
    if (!Sniff_id && sizeof(query_riders()) && TP != query_riders()[0])
	       Sniff_id = set_alarm(1.0,0.0,&sniff(TP));
}

void
sniff(object player)
{
    Sniff_id = 0;
    if (!present(player,environment()))
       	return;

    if (CAN_SEE(TO,player) && player->query_prop(OBJ_I_HIDE))
    {
     	player->catch_msg(QCTNAME(TO) +" puts his nose into the air and "
        + "takes several quick sniffs. He discovers you!\n");
     	say(QCTNAME(TO) + " puts his nose into the air and takes several "
        + "quick sniffs. He discovers "+QTNAME(player)+
   	  "!\n", player);
     	player->reveal_me(1);
     	query_riders()[0]->do_attack(player);
    }
}

void
attacked_by(object ob) 
{
    ::attacked_by(ob);
    if (sizeof(query_riders()))
      	query_riders()->do_attack(ob);
}

void
notify_rider_killed(object killer)
{
    float delay;

    command("emote howls as "+HIS_HER(TO)+" master dies.");
    command("growl at "+ killer->query_real_name());
    if (query_attack() != killer)
	       command("kill "+ killer->query_real_name());
}

public int
query_not_attack_me(object who, int aid)
{
    if (random(9) || aid == -1)
	       return 0;

    who->catch_msg(QCTNAME(TO)+" slips beneath your attack.\n");
    TO->tell_watcher(QCTNAME(TO)+" slips beneath "+QTNAME(who)+
      "'s attack.\n", who);
    return 1;
}

int
special_attack(object enemy)
{
    int pen;
    mixed hitres;
    string how;

    // We have a rider so we let him do the specials
    if (sizeof(query_riders()))
       	return 0;
    if (random(9))
       	return 0;

    // Do the wolf special attack.
    if (query_combat_object()->cb_tohit(-1, 100, enemy) >= 0)
    {
   	pen = (query_stat(SS_STR) / 3 + query_stat(SS_DEX) / 2);
   	pen = F_PENMOD(pen, query_skill(SS_HUNTING));
   	hitres = enemy->hit_me(pen, W_SLASH, TO, -1);

   	switch(hitres[0])
	   {
	   case -1:
	    case 0:
	        how = "unharmed";
	        break;
	    case 1..5:
	        how = "bruised";
	        break;
    	case 6..10:
	        how = "scratched and bleeding";
	        break;
	    case 11..20:
	        how = "painfully lacerated";
	        break;
	    case 21..35:
	        how = "wounded";
	        break;
    	case 36..50:
	        how = "seriously injured";
	        break;
    	default:
	        how = "heavily wounded";
	        break;
	    }
    	enemy->catch_tell("The "+query_nonmet_name()+" leaps at your "+
    	  hitres[1]+". It crashes into you, leaving you "
       +how+" from its onslaught.\n");
	    TO->tell_watcher(QCTNAME(TO) +" leaps at "+QTNAME(enemy)+"'s "+
	      hitres[1]+". It crashes into "+QTNAME(enemy)
       + " leaving " + HIM_HER(enemy) + " " +how+ " from its "
       + "onslaught.\n", enemy);
    }
    else
    {
   	enemy->catch_tell("The "+TO->query_nonmet_name()+" slashes at you "
        + "with his gaping jaws, but misses entirely.\n");
	   TO->tell_watcher(QCTNAME(TO) +" slashes at "+QTNAME(enemy)+
	       " with his gaping jaws, but misses "+HIM_HER(enemy)
        +" entirely.\n", enemy);
    }
    return 1;
}

