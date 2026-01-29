/*	Created by:	Sir Toby, 97-06-24
 *	Purpose:	Fill the sewers with them.
 *	location:	Sewers.
 *	Modified:	Toby, 970722
 *			Toby, 970723
 */

inherit "/d/Kalad/std/monster";
inherit "/std/combat/unarmed"; 

#include "/d/Kalad/defs.h"

//   Define some attack and hitloc id's (only for our own benefit)
 

#define A_BITE  0
#define A_RCLAW 2
#define A_LCLAW 3

#define H_HEAD 0
#define H_BODY 1
#define H_RWING 2
#define H_LWING 3

int i = random(9)+1;

void 
create_monster()
{

    string *descr;

  ::create_monster();

    descr = ({ "small ", "medium ", "quite large ", "large ", "very large ",
              "incredibly large ", "unbelievably large ", "monstrous ", 
              "huge ", "gigantic " });

    set_race_name("bat");
    set_name("demonbat");
    set_pname("demonbats");

    set_short( descr[i] + "demonbat" );
    set_pshort( descr[i] + "bats" );
    set_long("This is a " +descr[i]+ " demonbat. it reveals its sharp "+
	     "teeth as it circles you making rasping sounds.\n");

    set_adj( descr[i] );  
    set_adj("black");
    set_adj("demonic");

    set_stats(({ 15+i*7, 40+(i*7), 20+i*10, i*8, i*7, 30+i*10 }));

    set_alignment(-1200);
    set_knight_prestige(50);   

    set_skill(SS_AWARENESS,65);
    set_skill(SS_BLIND_COMBAT,100);
    set_skill(SS_DEFENCE,65);

    add_prop(LIVE_I_SEE_DARK,100);
    add_prop(LIVE_I_SEE_INVIS,1);
    
    add_prop(LIVE_I_UNDEAD,30);
    add_prop(LIVE_I_NO_CORPSE,1);
    add_prop(LIVE_I_NEVERKNOWN,1);

    set_attack_unarmed(A_BITE, i*9, 45+(i*5)-random(3),W_IMPALE, 80,"teeth");
    set_attack_unarmed(A_RCLAW, i*5, 16+(i*3), W_SLASH, 10, "right claw");
    set_attack_unarmed(A_LCLAW, i*5, 16+(i*3), W_SLASH, 10, "left claw"); 

    set_hitloc_unarmed(H_HEAD, 8+i*2+random(2), 20, "head");
    set_hitloc_unarmed(H_BODY, 15+i*5-random(4), 50, "body");
    set_hitloc_unarmed(H_RWING, 11+i*3+random(3), 30, "right wing");
    set_hitloc_unarmed(H_LWING, 11+i*3+random(3), 30, "left wing");

    set_act_time(35);
    add_act("emote circles above your head.");
    add_act("emote makes a dive and touches your hair.");
    add_act("emote rasps coldy.");
    add_act("emote stares at you with cold red eyes.");
    add_act("emote circles above your head staring at you hungrily.");

}

int
special_attack(object ob)
{
    string phurt;
    mixed *hitres;

    if(random(100) > 75)
    {

    if (query_combat_object()->cb_tohit(-1, 30+random(30)+((i*10)/2), ob) < 1)
        return 0;

    hitres = ob->hit_me(random(100)+i*10, W_IMPALE, TO, -1, A_HEAD);
    phurt = " with hardly any effect";
    switch(hitres[0])
    {
        case 1..20:
            phurt = "";
            break;
        case 21..40:
            phurt = " slightly";
            break;
        case 41..60:
            phurt = " quite hard";
            break;
        case 61..80:
            phurt = " viciously";
            break;
        default:
            phurt = " very hard, the bite leaves an open wound";
    }

    tell_object(ob,query_The_name(ob)+" eys glows red as it makes a dive " +
    		"agains your head, you are bitten " +phurt+ "!\n");
    tell_watcher(QCTNAME(TO)+" eyes glows read as it makes a dive at " +
		QTNAME(ob)+"'s " + "head and " + TP->query_pronoun() + 
		" is bitten" +phurt+ "!\n",ob);

    if(ob->query_hp() <= 0)
        ob->do_die(TO);
    return 1;
    }
return 1;
}
 
