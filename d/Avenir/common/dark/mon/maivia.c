// Maivia, dark elf warrior
// Shinto 3-10-01
/*
 * Lucius, May 2009: Cleaned and updated, moved from /d/Terel/dark/
 * Lilith, Jun 2014: Leader of Dark elves, made a quest npc.
 * Lucius, Jun 2017: Formatting cleanups and typo fixes.
 * Zizpuh, Aug 2012: Migrate special to standard library.
 *
 */
#pragma strict_types

inherit "/std/monster";
inherit "/lib/unique";
inherit "/d/Avenir/inherit/quest";
inherit "/d/Avenir/inherit/intro";
inherit "/d/Genesis/specials/npc/stat_based_specials";

#include "../dark.h"
#include "../maivia_quests.h"

#ifndef SCROLLING_LOG
#define SCROLLING_LOG(file, entry)   ((file_size(file) > 90000) ? \
    (rm(file) && write_file(file, ctime(time()) + ": " + entry + "\n")) : \
    (write_file(file, ctime(time()) + ": " + entry + "\n")))
#endif

#define DEATH_LOG   "/d/Avenir/log/deaths/dark_elf"


/* Maivia gives out quests ot players that are anti-Sybarus/
 * Quests can be solved as instructed, or quest obs can be
 * brought to the Inquisitors in the Kestars for a pro-Sybarus
 * solution. Quest exp is usually less for this option.
 * The reward is given by the recipient, as usual.
 */

private void
give_wangle_quest(object player)
{
    object letter1;

    letter1 = clone_object(OBJ + "maivia_q_ob_1");
    letter1->move(TO);

    if (!letter1)
    {
	command("say Alas, I can't think of any way that "+
	  "you could possibly be of use to me or our cause.");
	command("say Perhaps later. Now Leave me!");
	return;
    }

    player->add_prop(MAIVIA_I_QUEST, 6);

    set_alarm(2.0, 0.0, &command("ponder"));
    set_alarm(4.0, 0.0, &command("say I was wondering who I could spare for a "+
	    "certain task..."));
    set_alarm(6.0, 0.0, &command("say There is a mean-looking guard in the fortress "+
	    "beyond the abyss, a dwarf by the name of Wangle."));
    set_alarm(8.0, 0.0, &command("say He is an exceptionally bitter and nasty "+
	    "looking fellow, even for a dwarf."));
    set_alarm(10.0, 0.0, &command("give "+ M_W_O +" to "+ player->query_real_name()));
    set_alarm(12.0, 0.0, &command("say Give that to him, and make sure no one sees you!"));
    set_alarm(13.0, 0.0, &command("say That letter must never see an Inquisitor's "+
	    "hands, lest our plans be discovered!"));
    SCROLLING_LOG(QUEST_LOG, "Maivia gave Wangle quest to "+ player->query_real_name());
    STATSERV_LOG_EVENT("Utterdark", "Maivia gave out a quest");
}			

private void
give_ogre_quest(object player)
{
    object package;
    /* corpse of a shadow-elf with note complements of Maivia */	
    package = clone_object(OBJ + "maivia_q_ob_2");
    package->move(TO);

    if (!package)
    {
	command("say Alas, I can't think of any way that "+
	  "you could possibly be of use to me or our cause.");
	command("say Perhaps later. Now Leave me!");
	return;
    }

    player->add_prop(MAIVIA_I_QUEST, 7);

    set_alarm(2.0, 0.0, &command("smile evil"));
    set_alarm(4.0, 0.0, &command("say What perfect timing!"));
    set_alarm(6.0, 0.0, &command("say I need someone to take a package to the "+
	    "lair of the ogres."));
    set_alarm(8.0, 0.0, &command("say Not much to it, all you have to do is go "+
	    "down into their lair, drop the package, open it, and then leave."));
    set_alarm(10.0, 0.0, &command("give "+ M_O_O +" to "+ player->query_real_name()));
    set_alarm(12.0, 0.0, &command("say Make sure you don't open it until you "+
	    "are there!"));
    set_alarm(13.0, 0.0, &command("say Beware, too! That package must never "+
	    "see an Inquisitor's hands lest our efforts to destroy Sybarus "+
	    "be uncovered!"));
    SCROLLING_LOG(QUEST_LOG, "Maivia gave Ogre quest to "+ player->query_real_name());
    STATSERV_LOG_EVENT("Utterdark", "Maivia gave out a quest");
}				

private void
give_nochipa_quest(object player)
{
    object letter2;

    letter2 = clone_object(OBJ + "maivia_q_ob_3");
    letter2->move(TO);

    if (!letter2)
    {
	command("say Alas, I can't think of any way that "+
	    "you could possibly be of use to me or our cause.");
	command("say Perhaps later. Now Leave me!");
	return;
    }

    player->add_prop(MAIVIA_I_QUEST, 8);

    set_alarm(2.0, 0.0, &command("clap happ"));
    set_alarm(4.0, 0.0, &command("say You're perfect! No one will suspect you..."));
    set_alarm(6.0, 0.0, &command("say I need you to infiltrate the Bazaar Island and "+
	    "take a letter to the infidel hideout."));
    set_alarm(8.0, 0.0, &command("say Once there, you'll have to locate the leader of "+
	    "the infidels, a white-robed fair-skinned human called Nochipa."));
    set_alarm(10.0, 0.0, &command("give "+ M_N_O +" to "+ player->query_real_name()));
    set_alarm(11.0, 0.0, &command("say Give that to her, that we might form an "+
	    "alliance."));
    set_alarm(11.0, 0.0, &command("say That letter must never see an Inquisitor's "+
	    "hands, lest all our efforts be for naught!"));
    SCROLLING_LOG(QUEST_LOG, "Maivia gave Nochipa quest to "+
	player->query_real_name());
    STATSERV_LOG_EVENT("Utterdark", "Maivia gave out a quest");
}	

public string
ogres_ask()
{
    if (!CAN_SEE(TO, TP))
    {
	command("say I do not answer those whom I cannot see.");        
	return "";
    }
    /*	
    if (TP->query_prop(MAIVIA_I_QUEST) == 7)
    {
	command("say Look for a pony merchant named Amblo, deep down in the "+
		"Utterdark. Near him is a route down into the ogres' lair.");
	command("say Wait to open that package I gave you until after you've "+
		"dropped it, or you'll regret it.");
	return "";
    }
    */	
    command("say Ogres you ask?");
    command("say Foul-smelling creatures they are, but they may yet prove useful.");
    command("say They live in the deepest, darkest levels of the Utterdark.");
    return "";
}

public string			
nochipa_ask()
{
    if (!CAN_SEE(TO, TP))
    {
	command("say I do not answer those whom I cannot see.");        
	return "";
    }

    if (TP->query_prop(MAIVIA_I_QUEST) == 8)
    {
	command("say You'll have to kill the human infidel who sneaks about in "+
	  "the Bazaar. He has the key to the hideout.");
	command("say The infidels are hiding near the Inn that is all closed up. "+
	  "The key he carries will open the door. I hear there is a "+
	  "trapdoor in the floor once you're inside.");
	command("say Get the letter to the human woman at the Altar of Alphum.");
	return "";
    }

    command("say I hear Nochipa is a comely wench -- for a human.");
    command("say She is always at the Altar to Alphum, praying, and surrounded by "+
      "spirits who reportedly come to her aid.");
    return "";
}

public string			
wangle_ask()
{
    if (!CAN_SEE(TO, TP))
    {
	command("say I do not answer those whom I cannot see.");        
	return "";
    }

    if (TP->query_prop(MAIVIA_I_QUEST) == 6)
    {
	command("say That Wangle is dumb as a pole. But even a pole has uses.");
	command("say He's always trying to poison Kilnar. Don't know why, don't"+
	  " care, either.");
	command("say Just get the letter to him. That's all you have to do.");
    }

    command("say He's the meanest, grumpiest dwarf there at the fortress.");
    return "";
}

public string
give_task()
{
    if (!CAN_SEE(TO, TP))
    {
	command("say I do not answer those whom I cannot see.");        
	return "";
    }

    if (!CHECK_QUEST_6(TP))
    {
	command("emote frowns in thought while examining his boot.");
	give_wangle_quest(TP);
	return "";
    }
    /*	
    if (!CHECK_QUEST_7(TP))
    {
	command("emote frowns in thought while scratching under a piece of armour.");
	give_ogre_quest(TP);
	return "";
    }
    */
    if (!CHECK_QUEST_8(TP))
    {
	command("emote frowns in thought while scratching his nose.");
	give_nochipa_quest(TP);
	return "";
    }

    command("say Alas, I can't think of any way that "+
      "you could possibly be of use in our cause.");
    command("say Perhaps later. Now Leave me!");
    return "";
}

/* end quest code */

public string
what_me()
{
    if (!CAN_SEE(TO, TP))
    {
	command("say I do not answer those whom I cannot see.");        
	return "";
    }

    switch(random(5))
    {
    case 0:
	command("say You can't really be expecting me to answer that!");
	break;        
    case 1:
	command("say We must have a language barrier. Common is not my native tongue. "+
	  "Re-word your question if you want an answer.");
	break;
    case 2:
	command("say Really? That's the best you can do?");
	break;
    case 3:
	command("say Are you too stupid to figure out how to ask for a task?");
	break;
    case 4:
	command("say Give me one good reason why I should answer "+
	  "you.");
	break;
    }
    return "";    
}


/* Logging death info. */
void
do_die(object killer)
{
    object *foos = query_enemy(-1);
    string *killers;

    if (query_hp() > 0)
	return 0;

    if (!killer)
	killer = previous_object();

    foos -= ({ killer });
    killers = (foos)->query_name();

    /* Logging death for various reasons */
    SCROLLING_LOG(DEATH_LOG, "Maivia ("+ TO->query_average_stat() +") killed by "+ 
      killer->query_name() +"("+ killer->query_average_stat() +") "+ 
      (sizeof(killers) ? "with "+ COMPOSITE_WORDS(killers) : "solo"));
    STATSERV_LOG_EVENT("Utterdark", "Maivia died");

    ::do_die(killer);
}

public void
equip_me()
{
    object ob = clone_object(OBJ + "war_helm");
    ob->set_ac(38);
    ob->move(TO);

    clone_object(OBJ +"chainmail")->move(TO);
    clone_object(OBJ +"boots")->move(TO);

    if (random(2))
	clone_unique(OBJ + "silver_spear", 7, OBJ + "halberd")->move(TO);
    else
	clone_unique(OBJ + "evil_spear", 7, OBJ + "halberd")->move(TO);

    command("wear all");
    command("wield all");
}

public void
create_monster()
{
    setuid();
    seteuid(getuid());

    set_race_name("dark elf");
    set_name("maivia");
    set_living_name("maivia");
    add_name(({"warrior", "master", "elf", "leader", "drow"}));
    set_adj("dark");
    set_short("dark elf warrior master");
    set_pshort("dark elf warriors");

    set_stats(({ 250, 250, 250, 300, 300, 300 }));

    set_long("He appears to be the leader of the dark elves, those "+
      "evil creatures who are the opposers of all that is light " +
      "and truth. They seek utter darkness for the world. "+
      "He is a dark-skinned being with white hair, his beauty "+
      "drawn from the depths of the Utterdark. They are wicked, "+
      "wicked beings, these dark elves, and not "+
      "to be trifled with.\nThis one is a "+
      query_exp_title() +" sized "+ query_short() +".\n");	

    set_alignment(-1000);

    set_skill(SS_PARRY,		100);
    set_skill(SS_DEFENCE,	100);
    set_skill(SS_SPELLCRAFT,	100);
    set_skill(SS_WEP_SWORD,	100);
    set_skill(SS_WEP_POLEARM,	100);
    set_skill(SS_AWARENESS,	 90);
    set_skill(SS_SNEAK,		100);
    set_skill(SS_HIDE,		100);
    set_skill(SS_BACKSTAB,	100);
    set_skill(SS_PICK_POCKET,	 85);
    set_skill(SS_BLIND_COMBAT,	 85);

    add_prop(LIVE_I_SEE_DARK, 10);
    add_prop(LIVE_I_QUICKNESS, 150);
    add_prop(OBJ_M_HAS_MONEY, ({ 0, 0, 10, 5 }) );

    // set height and weight to align with size and descs
    add_prop(CONT_I_HEIGHT, TO->query_average_stat());
    add_prop(CONT_I_WEIGHT, TO->query_average_stat() * 125);

    set_all_hitloc_unarmed(35);

    // Make beautiful as per set_long
    set_appearance_offset(-45);

    set_chat_time(20 +random(60));
    add_chat("All glory resides in darkness!");
    add_chat("We worship Shadow.");
    add_chat("The sun is a most foul creation.");
    add_chat("It is here that my grandfather made his offerings to the Shadow.");
    add_chat("I shall destroy Sybarus and avenge my grandfather.");
    add_chat("The broken bodies of shadow-elves shall fall before me.");
    add_chat("The ogres are the key to everything. Who shall I send down there?");
    add_chat("We took care of those Mystics two decades ago. "+
	"Soon, the Shadow Warriors.");
    add_chat("We may have to push the trolls back onto the moors. "+
	"It's getting crowded here.");
    add_chat("I know the Halls of Shadow are nearby. We will find them.");
    add_chat("I'm working on a plan to take over the fortress on the other "+
	"side of the abyss.");
    add_chat("Who shall I send to request a parlay with Nochipa?");

    //	set_default_answer(what_me);

    add_ask(({"[where] [is] [the] 'bazaar'"}), 
      "say Go to the edge of the sea inside the fortress and hit the pipe. "+
      "A boat will take you to the Bazaar.", 1);
    add_ask(({"[why] [do] [you] [worship] [the] 'shadow'"}), 
      "say Why do we worship Shadow? Because we feel compelled to.", 1);
    add_ask(({"[about] [why] [the] 'sun' [is] [a] [foul] [creation]"}), 
      "say The sun blinds. It sears with heat. I draws the water from flesh. "+
      "For these reasons it is a most foul creation.", 1);
    add_ask(({"[about] [your] 'grandfather'"}), 
      "say Grandfather lead my people all the way to the shores of Sybarus. "+
      "He was beat back by the undead from the Necronisi or we would have "+
      "triumphed!", 1);
    add_ask(({"[about] [the] 'imps' / 'ghost'"}),
      "say Not far from there, the imps and the ghost reside. There is some "+
      "quest involved with them, though it is up to you to discover it.", 1);
    add_ask(({"[about] [the] 'tolls' / 'hobgoblins'"}),
      "say Foul little creatures, they are. We are thinking of driving them "+
      "away.", 1);
    add_ask(({"[about] [the] 'undead' / 'necronisi'"}), 
      "say Our intelligence-gathering has lead us to believe that the  "+
      "Necronisi, or Isle of the Dead, is where the bodies of the dead, "+
      "both Faithful and Infidel, are disposed. The infidels become undead "+
      "and wait the chance to redeem themselves by answering the call "+
      "to defend Sybarus. They are terrible foes.", 1);
    add_ask(({"[about] [the] 'mystics'"}), 
      "say Oh that was a clever bit of work on our part! And few know "+
      "it was us, nor how we did it.", 1);
    add_ask(({"[about] [the] [plan] [for] [the] 'fortress' / 'fort'"}), 
      "say We've got someone on the inside there. It is only a matter "+
      "of time before we take it over.", 1);
    add_ask(({"[about] [the] [shadow] 'union'"}),
      "say We will destroy the so-called Union. "+
      "My men are scouting out their location as we speak.", 1);
    add_ask(({"[about] [the] 'halls' 'of' 'shadow'"}),
      "say We will destroy the so-called Union. "+
      "My men are scouting out their location as we speak.", 1);
    add_ask(({"[about] [the] 'shadow' 'warriors'"}),
      "say We will destroy those who dare call themselves Shadow Warriors.", 1);
    /* quest asks */
    add_ask(({"[for] [a] 'task' / 'job' / 'quest' / 'help'"}), give_task);
    add_ask(({"[do] [you] [have] / [need] [a] 'task' / 'job' / 'quest' / 'help'"}),
	give_task);	
    add_ask(({"[about] [the] 'plan' / 'letter' / 'scroll' / 'crate'"}), give_task);

    add_ask(({"[about] [how] [to] [help] [with] [the] 'ogres'"}), ogres_ask);
    add_ask(({"[about] 'where' [are] [the] 'ogres' [located]"}), ogres_ask);
    add_ask(({"[about] [how] [to] [help] [with] [the] 'nochipa' 'scroll' [quest]"}),
	nochipa_ask);
    add_ask(({"[about] [who] / [where] [is] 'nochipa'"}), nochipa_ask);	
    add_ask(({"[about] [how] [to] [help] [with] [the] 'wangle' 'scroll' [quest]"}),
	wangle_ask);
    add_ask(({"[about] [who] / [where] [is] 'wangle'"}), wangle_ask);

    equip_me();
}

/*
 * perform a special attack
 */
public int
special_attack(object enemy)
{
    if (random(3))
	return 0;

    mixed *hitresult;
    string how, spattack;

    int dt;
    
    /* Switch between three types of attack, stab, slash, and punch. */
    switch(random(2)) 
    {
    case 0:  
	if (sizeof(TO->query_weapon(-1)))
	{
	    dt = W_IMPALE;
	    spattack = "stabs";
	}
	else
	{
	    dt = W_BLUDGEON;
	    spattack = "punches";
	}
	break;
    case 1:  
	if (sizeof(TO->query_weapon(-1)))
	{
	    dt = W_IMPALE;
	    spattack = "stabs";
	}
	else
	{
	    dt = W_BLUDGEON;
	    spattack = "punches";
	}
	break;
    }

    // Choose power of hit based on mob stat size.
    hitresult = do_stat_based_attack(TO, enemy, dt);
	
	// The attack was evaded
	if (intp(hitresult))
		return 1;


    if (hitresult[0] <= 0)
    {
    /* Describe the attack. */
        enemy->catch_tell(query_The_name(enemy) +" "+ spattack +" at you "+
            "but misses.\n");
        tell_watcher(QCTNAME(TO) +" "+ spattack +"  at "+ QTNAME(enemy) +
            " but misses.\n", enemy);
      return 1;
    }
    

    /* Determine how good a hit and describe it. */
	how = "not hurt";
    if (hitresult[0] > 0)
	how = "slightly hurt";
    if (hitresult[0] > 5)
	how = "rather hurt";
    if (hitresult[0] > 25)
	how = "crushed";
    if (hitresult[0] > 50)
	how = "devastated";

    if (hitresult[0] > 20)
	enemy->add_attack_delay((hitresult[0] / 2), 1);

    /* Describe the attack. */
    enemy->catch_tell(query_The_name(enemy) +" "+ spattack +" you "+
      "in the "+ hitresult[1] +"!\nYou feel "+ how +".\n");
    tell_watcher(QCTNAME(TO) +" "+ spattack +" "+ QTNAME(enemy) +
      " in the "+ hitresult[1]+"!\n", enemy);

    /* Kill the bastard if he's got no hit points. */
    if (enemy->query_hp() <= 0)
	enemy->do_die(TO);

    return 1;
}
