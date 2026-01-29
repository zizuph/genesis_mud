/* A hobbit deputy sherriffe deputy out on patrol */

#include "../local.h"
#include <formulas.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>

inherit SHIRE_MONSTER;

#define STUN_OB  EROBJ_DIR + "stun"
//#define WEP_ARR ({ERWEP_DIR + "staff", ERWEP_DIR + "mace", ERWEP_DIR + "spear"})
#define WEP_ARR (ERWEP_DIR + "battlehammer")
static int Sling = 10;

// Prototypes
string get_attitude_desc();
string get_beard_desc();
void assist_friend(object ob);
void get_booze();


void create_deputy() {}

nomask void
create_shire_monster()
{
    set_race_name("hobbit");
    set_gender(G_MALE);
    set_adj(({get_attitude_desc(), get_beard_desc()}));
    set_long("This "+query_nonmet_name()+" is a deputy of the local "+
      "Sherriffes. "+CAP(HE_SHE(TO))+" is dressed in the brown leather "+
      "uniform of the Sherriffes of the Shire, and the star brooch "+
      "worn over the heart identifies"+ HIM_HER(TO) +" as deputy rank. "+
      "This hobbit looks like an capable peace-keeper.\n");

    set_base_stat(SS_STR, 55 + random(20));
    set_base_stat(SS_DEX, 95 + random(40));
    set_base_stat(SS_CON, 80 + random(30));
    set_base_stat(SS_INT, 60 + random(10));
    set_base_stat(SS_WIS, 70 + random(10));
    set_base_stat(SS_DIS, 80 + random(20));

    set_skill(SS_WEP_CLUB, 65 + random(21));
    set_skill(SS_WEP_MISSILE, 70 + random(20));
    set_skill(SS_WEP_POLEARM, 60 + random(16));
    set_skill(SS_PARRY, 50 + random(16));
    set_skill(SS_DEFENCE, 75 + random(16));
    set_skill(SS_AWARENESS, 45 + random(21));

    set_alignment(300 + random(200));
    set_intoxicated(1000);
    add_prop(LIVE_I_NEVERKNOWN, 1);


    //  time for the emotes and chats/cchats
    set_chat_time(15 + random(3));
    add_chat("This brandy is the smoothest I've ever 'ad!");
    add_chat("I hopes we'll be able to carry all that gold home!");
    add_chat("Maybe there'll be some goblins for us to get "+
      "warmed up on along the way.");
    add_chat("Me weapon is polished and I'z itchin for blood!");

    set_act_time(16 + random(4));
    add_act("emote chugs down some of his brandy.");
    add_act("emote strokes his beard.");
    add_act("grumble");
    add_act("hiccup");

    set_cchat_time(13 + random(4));
    add_cchat("Finally some action!");
    add_cchat("You'll pay for this!");
    add_cchat("I'm gunna knock ya head from ya rott'n corpse!");
    add_cchat("HA! is dat the best you can do!");
    add_cchat("To battle and victory lads!");

    set_cact_time(9 + random(8));
    add_cact("emote screams an ancient battle cry!");
    add_cact("knee goblins");
    add_cact("grumble");
    add_cact("emote reaches for another bottle.");
    add_cact("shout Die stinking bastards!");


    create_deputy();
    get_booze();
    if (!sizeof(query_weapon(-1)))
	add_equipment(({ONE_OF(WEP_ARR), ERARM_DIR + "d_boots",
	    ERARM_DIR + "d_chainmail", ERARM_DIR + "d_helm"}));
}

string
get_beard_desc()
{
    return ONE_OF(({"grey-bearded", "long-bearded", "black-bearded",
	"white-bearded","thin-bearded","blond-bearded"}));
}

string
get_attitude_desc()
{
    return ONE_OF(({"old", "grumpy", "grumbling", "stout", "fat",
	"drunken", "big-nosed", "red-nosed"}));
}

void
get_booze() 
{
    object booze;

    booze = clone_object(EROBJ_DIR + "bullet");
    booze->set_heap_size(10);
    booze->move(TO,1);
}

void
attacked_by_hook(object ob) 
{
    command("say "+ONE_OF(({"Alright, about time we got some action!",
	  "Dat was a stupid mistake "+ob->query_race_name()+"!",
	  "To battle lads!"})));
}

void
attacked_by(object ob)
{
    if (!objectp(query_attack()))
    {
	query_team_others()->notify_friend_attacked_by(ob);
	attacked_by_hook(ob);
    }
    ::attacked_by(ob);
}

void
attack_object(object ob)
{
    if (!objectp(query_attack()))
    {
	query_team_others()->notify_friend_attacked_by(ob);
    }
    ::attack_object(ob);
}

void
notify_friend_attacked_by(object ob)
{
    if (!present(ob, environment()) || objectp(query_attack()))
	return;
    set_alarm(itof(random(3) + 1), 0.0, &assist_friend(ob));
}

void
assist_friend(object ob)
{
    if (!present(ob,environment()))
	return;
    else
	command("shout You'll pay for this "+ob->query_nonmet_name()+"!");

    if (!command("kill "+ob->query_real_name()))
	command("assist");
}

int
special_attack(object enemy)
{
    mixed hit_res;
    int pen;
    string text1, text2;
    object weapon, bullets;

    if (random(6))
	return 0;

    if (sizeof(query_weapon(-1)))
	weapon = query_weapon(-1)[0];
    if ((!random(3) || !objectp(weapon)) &&
      (!present("_Shire_chair_stun", enemy)))
    {
	// We fight dirty :)
	
	    bullets = present("_Shire_bullet", TO);
	    if (!objectp(bullets))
		return 0;
	    setuid(); seteuid(getuid());
	    weapon = clone_object(MASTER_OB(bullets));
	    bullets->set_heap_size(bullets->num_heap() - 1);
	    // Tell them he got hit with something.
	    enemy->catch_msg(QCTNAME(TO) + " slips a rock in "+HIS_HER(TO)+
	      " sling and launches a bullet straight for your head!\n");
	    TO->tell_watcher(QCTNAME(TO) + " slips a rock in "+HIS_HER(TO)+
	      " sling and flings a bullet "+QTNAME(enemy)+" at "+HIS_HER(enemy)+
              " head!\n", enemy);

	    pen = weapon->query_prop(HEAP_I_UNIT_WEIGHT) / 20;
	    pen = F_PENMOD(pen, query_skill(SS_WEP_MISSILE));
	    hit_res = enemy->hit_me(pen, W_BLUDGEON, TO, -1, TS_HEAD);

	    // Bullet expended
	    weapon->remove_object();
	    // Is he dead?
	    if (enemy->query_hp() < 1)
	    {
		enemy->do_die(TO);
		return 1;
	    }
	    // If he hit him hard enough we stun him
	    if (hit_res[3] >= 50)
	    {
		clone_object(STUN_OB)->move(enemy, 1);
	    }
    else
    {
	if (!objectp(weapon))
	    return 0;
	}	
	    pen = weapon->query_pen() + SS_DEX / 4;
	    pen = F_PENMOD(pen, (weapon->query_wt() == W_CLUB ?
		query_skill(SS_WEP_CLUB) : query_skill(SS_WEP_POLEARM)));

	    hit_res = enemy->hit_me(pen, W_BLUDGEON, -1, TO);
	    switch (hit_res[0])
	    {
	    case -1:
		text1 = "missing you entirely.";
		text2 = "missing "+QTNAME(enemy)+" entirely.";
		break;
	    case 0:
		text1 = "narrowly missing your "+hit_res[1]+".";
		text2 = "narrowly missing "+QTNAME(enemy)+"'s "+hit_res[1]+".";
		break;
	    case 1..15:
		text1 = "striking your "+hit_res[1]+" with a soft thump.";
		text2 = "striking "+QTNAME(enemy)+"'s "+hit_res[1]+
		" with a soft thump.";
		break;
	    case 16..35:
		text1 = "striking your "+hit_res[1]+" with a solid thump.";
		text2 = "striking "+QTNAME(enemy)+"'s "+hit_res[1]+
		" with a solid thump.";
		break;
	    case 36..55:
		text1 = "brusing your "+hit_res[1]+" slightly.";
		text2 = "brusing "+QTNAME(enemy)+"'s "+hit_res[1]+" slightly.";
		break;
	    case 56..80:
		text1 = "hitting your "+hit_res[1]+" with a crushing blow!";
		text2 = "hitting "+QTNAME(enemy)+"'s "+hit_res[1]+" with "+
		"a crushing blow!";
		break;
	    default:
		text1 = "smashing into your "+hit_res[1]+" with devastating force!!";
		text2 = "smashing into "+QTNAME(enemy)+"'s "+hit_res[1]+
		" with devastating force!!";
		break;
	    
	}
	enemy->catch_msg(QCTNAME(TO) + " swings "+HIS_HER(TO)+" "+
	  weapon->short() +" around, "+ text1 +"\n");
	TO->tell_watcher(QCTNAME(TO) + " swings "+HIS_HER(TO)+ " "+
	  weapon->short() + " around "+ text2 + "\n", enemy);        

    }
    if (enemy->query_wiz_level())
	enemy->catch_tell("DAMAGE: "+hit_res[3]+"\n");
    return 1;
}
