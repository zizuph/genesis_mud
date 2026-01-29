//  CTHULUjr        /d/Avenir/common/dead/mon/cthulujr
//                  partly based on /d/Avenir/common/port/mon/octopus
// creator(s):      Lilith June, 2021
// last update:     Lilith Oct 2021: updated some props and skills
// purpose:         A Lovecraftian and Cthulu-ish BOSS npc
// note:            Cloned to crypt11
//                  The eldritch_cloak has a clone_unique(12)
//                  as a leftover on the corpse.
// Update    Zizuph Dec 2021: moved cloak cloning to use resolve_unique.
//           Lilith Feb 2022: removed magic res now that combat system
//                  calcs it based off AC.
//                  Added logging of skin clones per AoB request.
// bug(s):
// to-do:

inherit "/std/creature";
inherit "/lib/unique";
inherit "/std/combat/unarmed";
inherit "/std/act/action";
inherit "/d/Genesis/specials/npc/stat_based_specials";
#include "/d/Avenir/smis/sys/statserv.h"
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>
#include "../dead.h"

#define DEATH_LOG "/d/Avenir/log/deaths/cthulujr"
#define CLONE_LOG "/d/Avenir/log/eldritch_clones"

#define A_ARM8  0
#define A_ARM1  1
#define A_ARM2  2
#define A_ARM3  3
#define A_ARM4  4
#define A_ARM5  5
#define A_ARM6  6
#define A_ARM7  7

#define H_HEAD 8
#define H_ARM1 1
#define H_ARM2 2
#define H_ARM3 3
#define H_ARM4 4
#define H_ARM5 5
#define H_ARM6 6
#define H_ARM7 7
#define H_ARM8 0

int arms = 8;

void
create_creature()
{
    seteuid(getuid(TO));

    set_living_name("cthulujr");
    set_name("abomination");
    add_name(({"monster", "creature", "_spawn_of_cthlulu"}));
    set_race_name("abomination");
    set_adj(({"eldritch", "tentacled", "bizarre", "otherworldly"}));
    set_short("eldritch abomination");
    set_long("There are no words to adequately describe the horror that "
      +"towers over you in this incomprehensible form. Lumpy and gelatinous, "
      +"with a body covered in scales and something that looks like fins "
      +"or vestigial wings on its back, this creature has dozens of feelers "
      +"and tendrils swarming out from its stumpy head. Like hairy tapeworms,"
      +" the feelers seem to sense you in the air, whilst some of the "
      +"tendrils have forked ends with needle-like projections, looking like "
      +"so many mouths snapping at you. Tentacles like thick, muscular snakes"
      +" covered in suckers unfurl and slide toward you from all around its "
      +"upper body. Its many legs, which is the only thing your mind can "
      +"think to call the crinked, trunk-like projections, cling to the "
      +"slippery limestone around the pool and keep the entire mass upright. "
      +"The abomination is purest white, which somehow makes it seem even "
      +"more otherworldly and bizarre.\n");	

    set_gender(G_NEUTER);
    set_alignment(0); 
    default_config_creature(220);
    set_skill(SS_SWIM,             90); 
    set_skill(SS_SPELLCRAFT,      100); // reduce caster damage
    set_skill(SS_FORM_ABJURATION, 100); // reduce caster damage
    set_skill(SS_AWARENESS,       100);
    set_skill(SS_BLIND_COMBAT,    100);	
    set_skill(SS_DEFENCE,         100); // reduce melee damage 	
    set_skill(SS_ACROBAT,         100); // reduce melee damage
    set_skill(SS_UNARM_COMBAT,    100);
    set_skill_extra(SS_UNARM_COMBAT, 40); // extra attack damage

    // has 160% attack use
    set_attack_unarmed(A_ARM1,  35, 35, W_BLUDGEON, 20, "feeler");
    set_attack_unarmed(A_ARM2,  45, 45, W_BLUDGEON, 20, "tentacle");
    set_attack_unarmed(A_ARM3,  50, 50, W_IMPALE,   20, "tendril");
    set_attack_unarmed(A_ARM4,  45, 45, W_BLUDGEON, 20, "tentacle");
    set_attack_unarmed(A_ARM5,  35, 35, W_BLUDGEON, 20, "feeler");
    set_attack_unarmed(A_ARM6,  35, 35, W_BLUDGEON, 20, "feeler");
    set_attack_unarmed(A_ARM7,  50, 50, W_IMPALE,   20, "tendril");
    set_attack_unarmed(A_ARM8,  45, 45, W_BLUDGEON, 20, "tentacle");

    // native AC is 75
    set_hitloc_unarmed(H_HEAD,  80, 20, "head");
    set_hitloc_unarmed(H_ARM1,  75, 10, "feeler");
    set_hitloc_unarmed(H_ARM2,  75, 10, "tentacle");
    set_hitloc_unarmed(H_ARM3,  75, 10, "tendril");
    set_hitloc_unarmed(H_ARM4,  75, 10, "tentacle");
    set_hitloc_unarmed(H_ARM5,  75, 10, "feeler");
    set_hitloc_unarmed(H_ARM6,  75, 10, "feeler");
    set_hitloc_unarmed(H_ARM7,  75, 10, "tendril");
    set_hitloc_unarmed(H_ARM8,  75, 10, "tentacle");


    add_prop(CONT_I_HEIGHT, (TO->query_average_stat() * 5));
    add_prop(CONT_I_VOLUME, (TO->query_average_stat() * 500));
    add_prop(CONT_I_WEIGHT, (TO->query_average_stat() * 500));
    add_prop(MAGIC_I_BREATH_WATER, 1);
    add_prop(LIVE_I_SEE_DARK,    100);
    add_prop(LIVE_I_QUICKNESS,    50);	// just a little haste
    add_prop(LIVE_I_NEVERKNOWN,    1);
    add_prop(NPC_I_NO_FEAR,        1);
    add_prop(NPC_I_NO_LOOKS,       1);
    add_prop(NPC_I_NO_RUN_AWAY,    1);
    add_prop(OBJ_I_INVIS,          1);

    set_act_time(20);
    add_act("@@do_enemy_check", 1);

    set_cact_time(7);
    add_cact("roar might");
    add_cact("emote lets out a high-pitched screech that hurts your ears.");
    add_cact("emote whips a hairy feeler at you.");
    add_cact("emote unfurls more tentacles from the folds of its massive "+
      "body.");
    add_cact("emote opens its great maw of a mouth, splitting its body "+
      "vertically down the center and revealing row upon row of jagged "+
      "teeth.");
    add_cact("emote causes your mind to boggle over the impossibility of "+
      "its existance.");
    add_cact("emote tries to drag you toward its meatgrinder of a mouth.");
    add_cact("emote swipes a snapping tendril toward you.");
    add_cact("emote shrugs its rippling skin, splattering you with ooze."); 
    add_cact("shout n'gai, n'gha'ghaa bugg-shoggog y'hah!");
    add_cact("shout ya na kadishtu nilgh'ri!"); 
    add_cact("shout fm'latgh mnahn' hlirgh!");
    add_cact("emote infects your mind with incomprehensible imagery.");
    add_cact("@@do_enemy_check");

    string skin = resolve_unique(OBJ + "eldritch_cloak.c", 12);
    
    if (skin)
	{
	    add_leftover(skin, "skin", 1, 0, 0, 1);
        write_file(CLONE_LOG, ctime(time()) +" skin added.\n");	
	}
    else
    {		
	    write_file(CLONE_LOG, ctime(time()) +" resolve_unique = 0.\n");	    
	    add_leftover(OBJ + "tentacle.c", "tentacle", 1 , 0, 0, 1);
    }
    add_leftover(OBJ + "tentacle.c", "tentacle", (1+random(3)), 0, 0, 1);


}

public string
do_enemy_check()
{
    // If under attack make sure no longer invis.
    if(TO->query_attack())
    {
	TO->remove_prop(OBJ_I_INVIS);
	return "";
    }
    // If not under attack, set invis and hide in the pool.
    if(!TO->query_attack())
    { 
	if (TO->query_prop(OBJ_I_INVIS))
	    return "";

	command("emote slips back down into the water, its tentacles "+
	  "sliding against each other in a disturbing way.\n");
	TO->add_prop(OBJ_I_INVIS, 1);		
    }
    return "";
}

/* from the octopus */
public nomask void
cr_got_hit(int hid, int ph, object att, int aid, int dt, int dam)
/*
   hid:   The hitloc id        ph:    The %hurt
   att:   Attacker            aid:   The attack id
    dt:    The damagetype     dam:   The damage in hit points   */

{
    object arm;

    if(arms && dam>50 && dt==W_SLASH)
    {
	arm=clone_object(OBJ +"tentacle");
	arm->move(environment(TO));
	set_alarm(0.1,0.0,"remove_stuff",arms);
	tell_room(ENV(TO), QCTNAME(att) + " cuts a tentacle off the "+
	  "eldritch creature!\n", att, TO);
	att->catch_msg("You cut a tentacle off the eldritch creature!\n");

	ENV(TO)->let_go(att, arms);   
	arms=arms-1;   
    }
    ::cr_got_hit( hid, ph, att, aid, dt, dam);
}

private void
remove_stuff(int n)
{
    remove_hitloc(n);
    remove_attack(n);
}

/*
 * Function name:   do_entangle
 * Description:     Called from special_attack, adds attack delay.
 * Arguments:       player / attacker
 */
public int
do_entangle(object victim)
{
    object robe = victim->query_armour(A_ROBE);

    if(!present(victim, environment(TO)) )
	return 0;


    if (robe->id("_oilskin_cloak_"))
    {
	victim->catch_msg("The "+ short() +" tries to grab you " +
	  "but the tentacles and feelers slip off your cloak.\n");
	return 1;
    }

    victim->add_attack_delay(10);
    victim->catch_msg("The "+short()+" wraps a tentacle around your torso, "+
      "squeezing you tightly.\n");
    return 1;	  
}

/*
 * Function name:   do_push
 * Description:     Called from special_attack, used to reduce # of attackers.
 * Arguments:       victim / attacker
 */
public void
do_push(object victim)
{
    mixed enemies = query_enemy(-1); 
    string *exit_cmds;
    string exit, dest;
    int    ind;

    if (!environment() || !sizeof(enemies))
	return;

    exit_cmds = environment()->query_exit_cmds();
    if (!sizeof(exit_cmds))
	return;

    ind = random(sizeof(exit_cmds));
    exit = exit_cmds[ind];
    dest = (environment()->query_exit_rooms())[ind];

    tell_watcher("One of the "+ short() +"'s huge tendrils slams into "+ 
      QNAME(victim) +", who flies " + exit + "!\n", this_object(), victim);

    victim->catch_msg("You've been struck with a huge tendril! It sends "+ 
      "you flying "+ exit +"!\n");

    /* Move them, make peace with them */
    victim->move_living(exit, dest, 1);
    victim->stop_fight(TO);
}

public int
do_needles(object victim)
{
    mixed * hitresult;
    int avg_stat, hurt;
    string how, hdesc;
    object poison;

    // Choose power of hit based on mob stat size.
    hitresult = do_stat_based_attack(TO, victim, W_BLUDGEON);

    // The attack was evaded
    if (intp(hitresult))
	return 1;

    if (hitresult[0] <= 0)
    {
	// Handle misses.
	query_combat_object()->tell_watcher("One of the mouths at the "+
	  "end of the "+ short() + "'s tendrils tries to "+
	  "bite " + QTNAME(victim) +" but just misses!\n", victim);
	victim->catch_msg("One of the mouths on the "+ short() +"'s "+
	  "tendrils tries to bite you but misses!\n");
	return 1;
    }
    // hitresult as percentage of health
    how = "unharmed";
    if (hitresult[0] > 0)
	how = "a slight scrape of your skin.";
    if (hitresult[0] > 5)
	how = "a prickle where the needles grazed you.";
    if (hitresult[0] > 10)
	how = "a surge of pain where the needles landed.";
    if (hitresult[0] > 25)
	how = "an angry burning pain shooting through you!";
    if (hitresult[0] > 50)
	how = "agony as poison seeps into you from a hundred needles!";

    hdesc = hitresult[1];
    query_combat_object()->tell_watcher(QCTNAME(TO) + " snakes a tendril "+
      "toward "+ QTNAME(victim) + " that sinks needles into "+
      victim->query_possessive() +" "+ hdesc +"\n", victim); 
    victim->catch_msg(QCTNAME(TO) + " snakes a tendril toward you, and the "+
      "needles in its mouth sink into your "+ hdesc +"!\n");
    victim->catch_msg("You feel " + how + "\n");

    //The poison is mostly a nuisance. 
    if (random(5) == 0)
    {
	poison = clone_object(OBJ +"bite_poison");
	poison->reconfig_me(10 +random(40));
	poison->move(victim, 1);
	poison->start_poison();
    }

    return 1;
}

/* which enemies are in the room with me?*/
public mixed
query_p_enemies(void)
{
    return TO->query_enemy(-1) &
    filter(all_inventory(environment(TO)), living);
}

public int
special_attack(object victim)
{
    object *enemies = query_p_enemies();
    object enemy = one_of_list(enemies); 	

    if (ENV(victim) != ENV(TO) || victim->query_ghost())
    {
	TO->stop_fight(victim);
	return 1;
    }

    /* I want to make sure players aren't fighting an invisible monster */
    if (TO->query_prop(OBJ_I_INVIS))
	TO->remove_prop(OBJ_I_INVIS);

    switch(random(5))
    {
    case 0: return 0; 
    case 1: do_entangle(enemy); return 0;
    case 2: do_push(enemy);     return 0;
    case 3: do_needles(enemy);  return 0;
    case 4: return 0;
    default: return 0;
    }

    return 0;
}

public int
do_search()
{
    if (TO->query_prop(OBJ_I_INVIS))
    {
	remove_prop(OBJ_I_INVIS);
	TP->catch_msg("An inconceivably bizarre creature arises from the pool of "+
	  "water, flailing masses of tentacles and feelers toward you.\n");
	if (!TP->query_wiz_level())  
	    command("kill "+ TP->query_name());
	STATSERV_LOG_EVENT("crypt", "Cthulujr awakened");
	return 1;
    }
}

void
attacked_by( object ob )
{
    ::attacked_by(ob);
    if (random(3))
	do_entangle(ob);
}

public void
init_living()
{
    /* triggers the abomination to emerge */
    add_action("do_search","search");
    add_action("do_search", "swim");
    add_action("do_search", "wash");

    /* If the living is a player and player can see me */
    if (interactive(TP) && CAN_SEE(TP, TO))
    {
	/* If player isn't a wizard and isn't a size beneath notice */
	if(!TP->query_wiz_level() && TP->query_average_stat() > 100)  
	    command("kill "+ TP->query_name());
    }

    ::init_living();
}


public void
do_die(object killer)
{
    object gem;
    object *foos = query_enemy(-1);
    string *killers;

    if (query_hp() > 0)
	return;

    if (!present("_av_eldritch_tentacle"))
	clone_object(OBJ +"tentacle")->move(TO, 1);

    gem = clone_object("/d/Genesis/gems/obj/alexandrite");
    gem->set_heap_size(3 +(random(10)));
    gem->move(TO,1); 

    if (!killer)
	killer = previous_object();
    foos -= ({ killer });
    killers = (foos)->query_name();

    STATSERV_LOG_EVENT("crypt", "Cthulujr killed");
    /* Logging death for various reasons */
    SCROLLING_LOG(DEATH_LOG, "Cthulujr ("+ TO->query_average_stat() +") by "+
      killer->query_name() +"("+ killer->query_average_stat() +") "+
      (sizeof(killers) ? "with "+ COMPOSITE_WORDS(killers) : "solo"));

    ::do_die(killer);
}

