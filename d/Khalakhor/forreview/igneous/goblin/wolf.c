inherit "/d/Genesis/steed/steed";
inherit "/std/act/action";

#include "/d/Shire/sys/defs.h"
#include <wa_types.h>
#include <language.h>
#include <formulas.h>

//#define DEBUG_WHO find_player("igneous")

#ifdef DEBUG_WHO
#define DEBUG(s)  DEBUG_WHO->catch_msg("WARG:  "+ s +".\n")
#else
#define DEBUG(s)
#endif

#define A_BITE  0
#define A_LPAW  1
#define A_RPAW  2

#define H_HEAD  0
#define H_BODY  1
#define H_LPAW  2
#define H_RPAW  3
#define H_LHLEG 4
#define H_RHLEG 5

// Prototypes
string physlooks();
string alignlooks();
void sniff(object player);

// Global Vars
int Sniff_id, gExtras;

void
create_steed()
{
    int ran = random(11);

    set_race_name("wolf");
    set_adj(({physlooks(), alignlooks()}));
    set_long("This animal is known as a warg.  A fearsome creature which "+
      "closely resembles that of a wolf but is much larger and has been "+
      "bread as a mount for orcish riders.  Drool hangs from its "+
      "open maw as it smells battle and the scent of blood.\n");
    set_gender(G_MALE);

    set_stats(({55 + ran, 75 + ran, 70 + ran , 40, 20, 70 + ran}));

    set_skill(SS_DEFENCE, 50 + random(21));
    set_skill(SS_AWARENESS, 80 + random(26));  // Great sense of smell
    set_skill(SS_TRACKING, 60 + random(26));
    set_skill(SS_LOC_SENSE, 50 + random(16));
    set_skill(SS_HUNTING, 80 + random(6));
    set_skill(SS_CLIMB, 40 + random(11));
    set_skill(SS_SWIM, 30 + random(16));

    allow_mounted_combat(1);
    set_max_riders(1);   

    set_stuffed(TO->query_prop(LIVE_I_MAX_EAT));
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_I_NO_FEAR, 1);     // Fearless Animal

    // add some acts and cacts
    set_act_time(10 + random(6));
    add_act("growl mena");
    add_act("emote howls.");
    add_act("sniff caut");

    set_cact_time(12 + random(4));
    add_cact("growl all");
    add_cact("emote eyes blaze at the sight of blood.");
    add_cact("emote howls in delight.");
}

void
configure_steed()
{
    set_attack_unarmed(A_BITE, 35, 30, W_IMPALE | W_SLASH, 50, "bite");
    set_attack_unarmed(A_RPAW, 25, 15, W_SLASH,            25, "right claw");
    set_attack_unarmed(A_LPAW, 25, 15, W_SLASH,            25, "left claw");

    set_hitloc_unarmed(H_HEAD,  20, 10, "head");
    set_hitloc_unarmed(H_BODY,  45, 40, "fur covered body");
    set_hitloc_unarmed(H_LPAW,  25, 15, "left forepaw");
    set_hitloc_unarmed(H_RPAW,  25, 15, "right forepaw");
    set_hitloc_unarmed(H_LHLEG, 15, 10, "left hindleg");
    set_hitloc_unarmed(H_RHLEG, 15, 10, "right hindleg");
}


public int
can_mount(object o)
{
    if (o->query_race() != "goblin")
	return 0;
    if (!gExtras)
    {
	// Okie orc is mounted give him a defence bonus and a small quickness
	// bonus because he is mounted.
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
physlooks()
{
    return ONE_OF(({"large", "fearsome","hairy","ugly","massive",
	"snarling", "drooling","growling"}));
}

string
alignlooks()
{
    return ONE_OF(({"evil", "demonic", "sinister","testy",
	"dark","black"}));
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
    DEBUG("Sniffing "+CAP(player->query_real_name()));
    if (CAN_SEE(TO,player) && player->query_prop(OBJ_I_HIDE))
    {
	player->catch_msg(QCTNAME(TO) +" sniffs around and discovers you!\n");
	say(QCTNAME(TO) + " sniffs around and discovers "+QTNAME(player)+
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

    DEBUG("Rider was killed by "+killer->query_real_name());
    command("emote howls as "+HIS_HER(TO)+" master dies.");
    command("growl at "+ killer->query_real_name());
    if (query_attack() != killer)
	command("kill "+ killer->query_real_name());
    setuid(); seteuid(getuid());
    delay = itof(100 - query_skill(SS_HUNTING)) / 100.0;
    clone_object(HUNT_SHADOW)->hunt(killer, TO, 1, delay);
}

public int
query_not_attack_me(object who, int aid)
{
    if (random(9) || aid == -1)
	return 0;

    who->catch_msg(QCTNAME(TO)+" dodges your attack.\n");
    TO->tell_watcher(QCTNAME(TO)+" dodges away from "+QTNAME(who)+
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
	    how = "scratched";
	    break;
	case 6..10:
	    how = "a little hurt";
	    break;
	case 11..20:
	    how = "slightly injured";
	    break;
	case 21..35:
	    how = "wounded";
	    break;
	case 36..50:
	    how = "injured";
	    break;
	default:
	    how = "heavily wounded";
	    break;
	}
	enemy->catch_tell("The "+query_nonmet_name()+" leaps at your "+
	  hitres[1]+" mauling it with it's tooth-filled maw.  The attack "+
	  "leaves you feeling "+how+" from the "+query_race_name()+"'s "+
	  "vicious bite.\n");
	TO->tell_watcher(QCTNAME(TO) +" leaps at "+QTNAME(enemy)+"'s "+
	  hitres[1]+" mauling it with it's tooth-filled maw.  The attack "+
	  "leaves "+QTNAME(enemy)+" feeling "+how+" from the "+
	  query_race_name()+"'s vicious bite.\n", enemy);
    }
    else
    {
	enemy->catch_tell("The "+TO->query_nonmet_name()+" leaps past you "+
	  "in a failed attempt to maul you.\n");
	TO->tell_watcher(QCTNAME(TO) +" leaps past "+QTNAME(enemy)+
	  "in a failed attempt to maul "+HIM_HER(enemy)+".\n", enemy);
    }
    return 1;
}
