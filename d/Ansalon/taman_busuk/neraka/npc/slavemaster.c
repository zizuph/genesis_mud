/* slavemaster by Ashlar, based on Kernan */

#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>
#include "/d/Ansalon/common/defs.h"
#include "../local.h"

inherit AM_FILE
inherit "/lib/unique";

#define WEP  NWEP + "whip"
#define ARM1 NARM + "lbelt"
#define ARM2A NARM + "ring1"
#define ARM2B NARM + "ring2"

void arm_me();

void
create_krynn_monster()
{
    if(!IS_CLONE)
	return;

    set_name("kordhek");
    add_name("slavemaster");
    //set_living_name("kordhek");
    set_title("the Slavemaster of Neraka");
    set_introduce(1);
    
    set_race_name("human");
    set_adj("huge");
    add_adj("brawny");
    set_gender(G_MALE);
    set_long("This man guards the slavepens of Neraka. His massive " +
        "body is as hairless as his shaved head. His mouth is set " +
        "in a cruel sneer and he glares at everyone with equal " +
        "contempt.\n");

    set_scar(random(256));
    add_prop(CONT_I_HEIGHT, 200);
    add_prop(CONT_I_WEIGHT, (140+random(20))*1000);

    set_stats(({155,130,145,90,100,180}));
    set_hp(query_max_hp());

    set_skill(SS_WEP_CLUB, 90);
    set_skill(SS_DEFENCE, 80);
    set_skill(SS_PARRY, 70);
    set_skill(SS_BLIND_COMBAT, 90);
    set_skill(SS_AWARENESS, 70);
    //set_skill(SS_UNARM_COMBAT, 70);

    set_all_hitloc_unarmed(10);

    set_alignment(-500);
    set_knight_prestige(500);

    set_act_time(0);

    add_act(({"whip slave", "grin sadist"}));
    add_act("burp");
    add_act("emote scratches his armpit.");

    set_cact_time(0);
    add_cact("shout I'll show you!");
    add_cact("emote spreads his arms wide and roars like a bull.");
    add_cact("growl");

    set_default_answer(QCTNAME(TO) + " growls: I have no idea what you " +
    "are talking about!\n");

    add_ask(" [for] 'quest' / 'task' / 'assignment' ",
    "say Hmm... I have nothing at the moment but something usually " +
    "comes up sooner or later.", 1);
    
    add_ask(" [for] [a] 'whip' / 'whipping' ",VBFC_ME("give_whip"));

    add_ask(" [for] 'key' ","say Like I would give you the key? I don't " +
    "think so!", 1);

/*
    add_ask(({"quest","task","assignment"}), "give_quest", 2);
    add_ask(({"slaves","slave","slavepens"}),
        "say I guard the slaves, and will trample any pitiful attempt at " +
        "rebellion beneath my feet.", 1);
    add_ask("escape","say Hah, they wish!", 1);
    add_ask("work","say For me, work is it's own reward!", 1);
*/

}

void
qt1(string h, int n)
{
    switch(n)
    {
        case 1:
            command(h + "Yes, there is something you could do for me..");
            break;
        case 2:
            command(h + "It seems some of the slaves are planning to escape.");
            break;
        case 3:
            command(h + "It is easy to stop that.. However, they must " +
                "be aided by someone on the outside.");
            break;
        case 4:
            command(h + "I need to find out who the traitors are that are " +
                "willing to help the slaves escape.");
            break;
        case 5:
            command(h + "Give me their names and evidence of their guilt, " +
                "and you shall be rewarded.");
            break;
        default:
            return;
    }
    set_alarm(1.5,0.0,&qt1(h,n+1));
}
    
string
give_quest(object tp)
{
    string h;

    h = "whisper to " + tp->query_real_name() + " ";

    set_alarm(1.0,0.0,&qt1(h,1));

    return "nod";
}

string
give_whip(object tp)
{
    command("say You want to taste my whip, eh? Suit yourself then!");
    command("whip " + tp->query_real_name());
    return "";
}

int
special_attack(object enemy)
{
    int     attacktype,
    pen;

    mixed hitres;

    string *how;

    attacktype = random(5);

    if (attacktype == 0)
    {
        pen = (query_prop(CONT_I_WEIGHT) - enemy->query_prop(CONT_I_WEIGHT)) / 250 + random(200);
        if (pen < 50)
            pen = 50;
	    hitres = enemy->hit_me(pen, W_BLUDGEON, TO, -1);

	    /*
	    Kordhek rushes at you, but you manage to avoid him.
        Kordhek rushes at you, striking you a glancing blow on the chin.
        Kordhek makes a frantic rush at you, hitting you with a blow that makes you reel.
        Using all his weight, Kordhek crushes you against the wall.
	    Kordhek rushes at you, then at the last moment jumps and tackles you. You fall
	      down with him landing on top of you, crushing you to the floor with his
	      awesome weight.
        */

	    if (hitres[0] <= 0)
	        how = ({ QCTNAME(TO) + " rushes at you, but you manage to avoid " +
	            "him.",
	            QCTNAME(TO) + " rushes at " + QTNAME(enemy) + ", who " +
	            "manages to avoid him."});
	            
	    if(hitres[0] > 0)
	        how = ({ QCTNAME(TO) + " rushes at you, striking you a glancing " +
	            "blow on the chin.",
	            QCTNAME(TO) + " rushes at " + QTNAME(enemy) + ", striking " +
                "the latter a glancing blow on the chin." });
                
	    if(hitres[0] > 20)
	        how = ({ QCTNAME(TO) + " makes a frantic rush at you, hitting " +
	            "you with a blow that makes you reel.",
	            QCTNAME(TO) + " makes a frantic rush at " + QTNAME(enemy) +
	            ", hitting " + OBJECTIVE(enemy) + " with a blow that " +
	            "makes " + OBJECTIVE(enemy) + " reel." });

	    if(hitres[0] > 40)
            how = ({ "Using all his weight, " + QTNAME(TO) + " crushes you " +
                "against the wall.",
                "Using all his weight, " + QTNAME(TO) + " crushes " +
                QTNAME(enemy) + " against the wall." });
	    
	    if (hitres[0] > 60)
	        how = ({ QCTNAME(TO) + " rushes at you, then at the last moment " +
	            "he jumps and tackles you. You fall down with him landing " +
	            "on top of you, crushing you to the floor with his awesome " +
	            "weight.",
	            QCTNAME(TO) + " rushes at " + QTNAME(enemy) + ", then at " +
	            "the last moment he jumps and tackles his enemy. " +
	            QCTNAME(enemy) + " falls down with " + QTNAME(TO) +
	            " landing of top of " + OBJECTIVE(enemy) + ", crushing " +
	            OBJECTIVE(enemy) + " to the floor." });

        enemy->catch_msg(how[0] + "\n");
        tell_room(E(TO), how[1] + "\n", enemy);

	    if (enemy->query_hp() <= 0)
	    {
	        enemy->do_die(TO);
	    }

	    return 1;
    }

    return 0;
}

void
arm_me()
{
    setuid();
    seteuid(getuid(this_object()));

    clone_object(WEP)->move(this_object(),1);
    command("wield all");

    clone_object(ARM1)->move(this_object(),1);
    clone_unique(ARM2A,4,ARM2B)->move(this_object(),1);
    command("wear all");
    
}

int
second_life(object killer)
{
    object *others;
    int i;

    others = FILTER_LIVE(all_inventory(E(TO)) - ({ TO, killer }));
    for (i = 0; i < sizeof(others); i++)
    {
        if ( (others[i]->query_attack() == TO) &&
        !others[i]->query_prop(NERAKA_I_KILLED_KORDHEK) )
        {
            others[i]->add_prop(NERAKA_I_KILLED_KORDHEK, -1);
        }
    }

    killer->add_prop(NERAKA_I_KILLED_KORDHEK, 1);
    if (function_exists("set_key_among_straw",E(TO)))
    {
        tell_room(E(TO), "The huge brawny human falls backwards with a final, " +
            "gasping breath. As he does so, something falls out of his " +
            "belt, and lands among the straw with a tinkling sound.\n", TO);
        E(TO)->set_key_among_straw();
    }

    setuid();
    seteuid(getuid());
    A_KILL_LOG("pot/npckills","Kordhek Slavemaster",killer);

    return 0;
}

