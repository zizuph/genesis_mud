/*
Pax Tharkas.

verminaard.c
------------

Coded ........: 95/02/13
By ...........: Jeremiah

Latest update : 2003/07/65
By ...........: Blizzard

Updated July 2005 by Louie
- Commenting out check for quest being completed.  Quest
 - may now be completed repeatedly in the same Krynn cycle.
 - First person to complete it will set the quest_master info.
*/
/* Navarre, February 5 2014, adjust resist values.
 *     Magical Resist from 40 to 30.
 *     Poison Resist from 100 to 50.
 *
 * Arman, November 2018
 * Removed quest age restrictions.
 */

#include <std.h>
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <options.h>
#include <macros.h>
#include <money.h>
#include "/d/Krynn/common/defs.h";
#include "/d/Krynn/pax/local.h";
inherit M_FILE

inherit "/std/act/domove";  /* Allows Verminaard to move */
inherit "/std/act/action";  /* Allows verminaard to act  */
inherit "/lib/unique";

#define       SPLAINS    "/d/Krynn/solamn/splains/obj/"
   
public void   equip_me();
object        weapon;
object        armour;

void
create_krynn_monster()
{
    string str;
   
    set_name("verminaard");
    
    set_living_name("verminaard");
    
    set_race_name("human");
    set_title("the Dragon Highlord of the Red Dragon Army");
    set_long("This human is a very imposing figure. Tall and powerfully " +
        "built. His face is concealed behind the hideous horned " +
        "mask of a Dragon highlord.\n"); 
    add_name(({"human", "highlord"}));
    set_adj("muscular");
    add_adj("tall"); 
    set_gender(G_MALE);
    add_prop(OBJ_I_COLORABLE, 1);
   
    set_stats(({220,280,220,120,150,200}));
    set_skill(SS_DEFENCE,        100);
    set_skill(SS_PARRY,          100);
    set_skill(SS_WEP_CLUB,       100);  
    set_skill(SS_WEP_SWORD,      100);
    set_skill(SS_WEP_POLEARM,    100);
    set_skill(SS_UNARM_COMBAT,    90);
    set_skill(SS_BLIND_COMBAT,    90);
    set_skill(SS_AWARENESS,      100);
    add_prop(LIVE_I_QUICKNESS,   100);
    add_prop(LIVE_I_SEE_DARK,    100);
    add_prop(NPC_I_NO_RUN_AWAY,    1);
    add_prop(OBJ_I_RES_POISON,    50);
      
    trig_new("%w 'ignites' %s", "react_bomb");
    set_alignment(-1200);
    set_knight_prestige(4500);
    set_intoxicated(1000);
   
    set_all_hitloc_unarmed(45);
   
    set_act_time(3);
    add_act("say If those Solamnians get a hint as to where those "
        + "damned disks are, they might try something foolish.");
    add_act("say I hope that miserable rodent, Toede, can handle things " +
        "up north.");
    add_act("growl");
    add_act(({"say Those cursed elves. I can't wait to teach them a " +
                  "lesson. A lesson they will never forget.", "cackle"}));
    add_act(({"emote walks around restlessly.", "say This will not "
                  + "do! I want those disks moved to a safer place."}));
    add_act("shout The last thing we need, are more of those damned " +
        "followers of Paladine.");
    add_act("smile demonically");
   
    set_cact_time(10);
    add_cact("say You fool, do you think you can defeat a servant of " +
        "the dark queen?.");
    add_cact("say say your last prayers pilgrim.");
    add_cact("grin mercilessly");
    add_cact("cackle");
    add_cact("say Time to die whimp.");
    add_cact("laugh all");
   
    set_default_answer("Verminaard says: I have no idea what you are "
        +"babbling about.\n");
   
    add_ask(({"disks", "disks of mishakal", "disks of Mishakal",
                  "Disks of Mishakal", "Disks"}), VBFC_ME("disks_hint"), 1);
   
    add_ask(({"task", "Task", "quest", "Quest"}),
        VBFC_ME("check_quest"), 1);
   
    add_ask(({"reward", "Reward"}), VBFC_ME("check_reward"), 1);

    seteuid(getuid());
    equip_me();   
}

int
query_option(int opt)
{
    if ( opt == OPT_UNARMED_OFF )
        return 1;
}
           
int
query_dragonfear_immunity()
{
    return 1;
}

int react_bomb(string who)
{
    if (who)
    {
        who = lower_case(who);
        if(find_player(who))
        {
            set_alarm(0.0,0.0,"attack_bomber", who);
        }
        return 1;
    }
}

void attack_bomber(string who)
{
    command("say So you like throwing bombs, eh?");
    who = capitalize(who);
    command("say Well then, "+who+", let's see how you like being "+
        "burned!");
    who = lower_case(who);
    command("kill "+who);
    command("smile mercilessly "+who);
}

int
solamnian_knight(object who)
{
    if (who->test_bit("krynn", 1, 0))
        return 1;
   
    if (who->test_bit("krynn", 1, 1))
        return 1;
   
    if (who->test_bit("krynn", 1, 2))
        return 1;
   
    return 0;
}


string
disks_hint()
{
    if (solamnian_knight(TP))
    {
        command("say I have no information I wish to share with "
            + "you.");
        command("say Now depart before I send you out feet first.");
        return "";
    }
   
    command("peer");
    command("say What might your interest in the Disks of Mishakal "
        + "be?");
    command("hmm");
    command("say I do have an important task concerning those "
        + "disks.");
   
    return "";
}


string
check_quest(string str)
{
    object token;
    string who,
        what;
    int    prp;
   
    if (solamnian_knight(TP))
    {
        command("sneer");
        command("say I do not intend to trust you with anything. "
            + "Now leave or I will send you directly to your puny "
            + "God. One way only.");
       
        return "";
    }
   
    if (TP->query_alignment() > -100)
    {
        command("say I do not trust you. Get out of here before I "
            + "break your neck and feed you to the gully dwarves.");
        command("emote motions with his hand for you to leave.");
       
        return "";
    }

  
    if (TP->test_bit("Krynn", 2, 2) && TP->test_bit("Krynn", 2, 13))
    {
        command("say You are of no further use to me. However, I "
            + "might accept your wish to serve our Dark Queen at "
            + "some point in the future.");
        command("say Begone now. I have important matters to take "
            + "care of.");
       
        return "";
    }

/*
    if (REALAGE(TP) < 691200)  
    {
        command("frown");
        command("say I need seasoned people to perform tasks for me.");
        command("say I do not intend to risk anything by leaving "
		+ "important matters in the hands of a youngster like you.");
       
        return "";
    }
*/
  
/** MODIFIED Louie July 2005
    if (QUERY_QUEST("black_dragon"))
    {
        command("say I'm sorry, currently I do not have any more tasks " +
            "for you to do. Please check with me regularly, I have " +
            "a use for a helping hand frequently, just not at this " +
            "time.");
        return "";
    }
****/

    if(!TP->test_bit("Krynn", 2, 2))
    {
      // Give the Evil Disk Quest
      command("say Very well then. I shall allow you to assist me in "
              + "this situation.");
      command("say We have the Disks safeguarded in the ruins of Xak "
	      + "Tsaroth.");
      command("say However, this situation is not satisfactory, "
	      + "and I want them moved to a much safer place, here.");
      command("say You will go to Xak Tsaroth and give this to "
	      + "the black dragon guarding the disks.");
      
      seteuid(getuid());
      token = clone_object(POBJ + "evil_token");
      token->move(TO);
      who = TP->query_real_name();
      what = token->query_name();
      command("give " + what + " to " + who);
      
      command("laugh evil");
      command("say She might not like it, but she will obey my "
	      + "commands.");
      command("say Now go! Bring me those disks, and be swift about "
	      + "it.");
      command("say When you return, ask me for a reward and I will "
	      + "consider it.");
      
      prp = TP->query_prop("_player_i_black_dragon_quest");
      
      /*if you have this prop set you find more money in the treasure chest*/
      TP->add_prop("_player_i_black_dragon_quest",prp | 16);
      
      return "";
    }
    else
    {
      // Give Evil Version of Dragon Lance Quest

/*
	if (REALAGE(TP) < 864000)	
	{
	  command("frown");
	  command("say I need seasoned people to perform tasks for me.");
	  command("say I do not intend to risk anything by leaving "
		  + "important matters in the hands of a youngster like you.");
	  return "";
	}
*/
	command("say We have moved the Disks to a safe place, but my spies tells me "+
                "that the accursed knights are looking for something in the south.");
	command("say They are looking for trace of one of the legendary Dragonlances, "+
                "and I need you to stop them.");
	command("say Even if the Dragonlances will do them little good, we "+
                "cannot allow them to get their spirits up or perform research "+
                "on the Dragonlances.");
	command("say You may be able to find more information of the dragonlance in the "+
                "Palanthas Library.");
	command("say Stop the knights in their search or return the dragonlance to me for your reward.");

	TP->add_prop("_player_i_lance_quest", 1);
	TP->add_prop("_player_m_pal_lib_audition",
		     ({"say Oh, there you are. You are here to see Astinus!",
			 "say Verminaard made sure we would be expecting you.",
			 "say Astinus will see you.", "icewall"}));
      return "";
    }
}

string
check_disk_reward()
{
    object ob;
    int prp, xp = 6000;
   
    if (ob = present("black_item", TP))
    {
        ob->remove_object();
        seteuid(getuid());
        if (!TP->test_bit("krynn", 2, 2))
        {
            if (solamnian_knight(TP))
            {
                command("emote swiftly grabs the Disks of Mishakal.");
                command("say A follower of Paladine delivering the "
                    + "Disks of Mishakal into the hands of Takhisis?");
                command("emote laughs incredulously.");
                command("say I do not reward traitors.");
                command("say I almost feel inclined to send a message "
                    + "to your superiors.");
                command("grin .");
                command("say Leave my premises, and do not return.");
	       
                return "";
            }
	   
            // if(REALAGE(TP) < 691200 || TP->query_alignment() > -100)

            if(TP->query_alignment() > -100)
            {
                command("growl");
                command("emote quickly takes the Disks of Mishakal.");
                command("say Which fool left these in your hands?");
                command("say I cannot believe that anybody would trust "
                    + "you with these items.");
                command("say There simply must have been a mistake "
                    + "somewhere.");
                command("say I better take care of these.");
                command("say You may leave now. And I advise you to do "
                    + "so.");
	       
                return "";
            }
	   
/**** MODIFIED Louie July 2005
            if (QUERY_QUEST("black_dragon"))
            {
                command("say I have already received the Disks of Mishakal. " +
                    "Did you find another copy? Interesting...");
                command("hmm");
                command("say Or did you steal them from us? Well, I can't prove that. " +
                    "Either way, I suggest you contact me about this later, when " +
                    "the time is again right.\n");

                return "";
            }
*******/

            command("emote gently takes the Disks of Mishakal.");
            command("say Excellent!");
            command("emote stares intently at the Disks.");
            command("emote smiles broadly.");
            command("say My Queen will be most pleased with me.");
            command("say You will be rewarded for your services.");
	   
            prp = TP->query_prop("_player_i_black_dragon_quest");
            if (prp & 1) /* means s/he got the bottle him/herself*/
                xp += 10000;
            if (prp & 2) /* means s/he killed the dragon */
                xp += 4000;
            if (prp & 4) /* means s/he filled acid in bottle */
                xp += 2000;
            if (prp & 8) /* means s/he poured acid on lock */
                xp += 2000;
            if (xp >= 20000)
                write("You feel much more experienced!\n");
            else
                write("You feel more experienced!\n");
            TP->add_exp(xp, 0);
            seteuid(getuid(this_object()));
            TP->set_bit(2, 2);
            TP->remove_prop("_player_i_black_dragon_quest");
            K_QUEST_LOG("quest", "Black dragon quest (EVIL)", TP, xp);
        if (!QUERY_QUEST("black_dragon")) {
            DONE_QUEST("black_dragon");
            (ARMYMASTER)->done_quest("black_dragon_evil");
        }
            return "";
        }
        /* Disks present but Quest solved before. */
        if (solamnian_knight(TP))
        {
            command("emote quickly grabs the Disks of Mishakal.");
            command("say You followers of Paladine truly are a "
                + "herd of incompetent fools.");
            command("say These Disks are of great value.");
            command("say I do, however, not reward traitors.");
            command("emote laughs condescendingly.");
            command("say Now get out of my sights, and do it fast.");
            command("sneer");
	   
            return "";
        }
       
        command("emote deftly takes the Disks of Mishakal.");
        command("say Well done.");
        command("say However, I have already rewarded you for this "
            + "once, and I will not do so again.");
        command("say Your willingness to serve our cause has been "
            + "noted.");
       
        return "";
    }
    /* There are no disks to be rewarded for. */
    if (solamnian_knight(TP))
    {
        command("frown");
        command("say I will reward you with death if you do not leave "
            + "immediately!");
        command("point north");
       
        return "";
    }
   
    command("eyebrow");
    command("say A reward? For what? I see nothing that would "
        + "entitle you to a reward.");
    command("say The way out is that way.");
    command("point north");
   
    return "";
}


string
check_lance_reward()
{
  int lance_xp = 15000;
  object ob;

  if(ob = P("dragon_lance", TP))
  {
    ob->remove_object();
    seteuid(getuid(this_object()));

    if(!(TP->test_bit("Krynn", 2, 13)))
    {
/*
      if (REALAGE(TP) < 864000)
      {
	command("say Where did you find this? You are too young " +
                "to have been able to get this by yourself. Come " +
                "back when you are older.\n");
	return "";
      }
*/

      if(!TP->query_prop("_player_i_visited_library"))
      {
	command("say My spies tells me that you never visited the Palanthas Library, "+
		"so you couldn't possible have known how to locate the dragonlance.");
	command("say I smell something fishy. Get out of here!");
	return "";
      }         
      
      if(!TP->query_prop("_player_i_lance_quest"))
      {
	command("say Why are you giving me this? Get lost!");
	return "";
      }

      command("say Surprisingly you managed to snatch one of the legendary "+
              "lances, this will cause a significant setback for the Knights.");

      command("say You have proven a lot more useful than I would have given you credit for. "+
              "You have earned your reward.");

      TP->set_bit(2,13);
      TP->remove_prop("_player_i_lance_quest");
      TP->add_exp_quest(lance_xp);
      write("You feel more experienced.\n");
		    
      K_QUEST_LOG("quest", "Lance quest", TP, lance_xp);
      DONE_QUEST("dragonlance");
      (ARMYMASTER)->done_quest("dragonlance");
      return "";
    }
    command("say Where do you find all these? Get lost, I am not rewarding you again.");
    return "";
  }
}


string
check_reward()
{
  if(!TP->test_bit("Krynn", 2, 2))
  {
    return check_disk_reward();
  }
  else
  {
    return check_lance_reward();
  }
}

public void
equip_me()
{
    switch ( random(3) )
    {
        case 0:
            weapon = clone_unique(PWEAPON + "war_sword", 6, 
                SPLAINS + "bclaymore");
        break;
        case 1:
            weapon = clone_unique(KRWEAPON + "flame_glaive", 3 + random(4),
                SPLAINS + "bclaymore");
        break;
        default:
            weapon = clone_unique(PWEAPON + "nightbringer", 6, 
                SPLAINS + "bclaymore");
        break;
    }

    weapon->move(TO);

    clone_unique(KRARMOUR + "warhelm", 3, PARMOUR + "dragonmask")->move(TO);
   
    armour = clone_unique(PARMOUR + "fullplate", random(3) + 1, 
        PARMOUR + "vdragonarm");
    armour->move(TO, 1);
         
    if ( armour->id("dragonscale") )
    {
        clone_object(PARMOUR + "vshinguard")->move(TO);
        clone_object(PARMOUR + "vbracers")->move(TO);
    }
    
    command("wear all");
    command("wield all");
}

void
return_intro(string who)
{
    object pl = find_player(L(who));
    if ((E(pl) == E(TO)) && !pl->query_met(TO))
	command("introduce myself");
}

void
add_introduced(string who)
{
    set_alarm(4.0, 0.0, &return_intro(who));
}

int
special_attack(object enemy)
{
    int attacktype;
   
    attacktype = random(15);
   
    if (attacktype == 1)
    {
        if ( weapon->id("nightbringer") )
        {
            if(!present("Nightbringer_Blind_Object", enemy))
                command("shout Midnight");
        }
        else
        {
            if(!random(4))
                present("ember", E(TO))->attack_enemy(enemy);
        }   
    }
   
    if (attacktype == 2)
    {
        if(!random(4))
            present("ember", E(TO))->attack_enemy(enemy);
    }
   
    return 0;
}

void
attacked_by(object ob)
{
    object *arr;
    int i;
   
    ::attacked_by(ob);
    arr = (object *)query_team_others();
    for (i = 0; i < sizeof(arr); i++)
    {
      arr[i]->notify_ob_attacked_me(TO,ob);
    }
}

void
notify_ob_attacked_me(object friend, object attacker)
{
    if(query_attack())
        return;
   
    set_alarm(3.0, 0.0, "help_friend", attacker);
}


void
help_friend(object attacker)
{
    if(attacker && !query_attack() && present(attacker,E(TO)))
    {
        command("say Fool!");
        command("kill " + attacker->query_real_name());
    }
}


public void
attack_object(object ob)
{
    if ((ob->query_real_name() == "ember") ||
        (ob->query_real_name() == "pyros"))
    {
        tell_room(E(TO), "Verminaard shakes his head, and stops the "
            + "attack.\n", TO);
      
        return;
    }
   
    ::attack_object(ob);
    present("pyros", E(TO))->transform(ob);
}

public void
do_die(object killer)
{
    // killer->set_alignment(killer->query_alignment() + 450);

    ::do_die(killer);
}

public int
second_life(object killer)
{
    K_KILL_LOG("kills", "Verminaard", killer);
    return 0;
}

varargs public mixed
hit_me(int wcpen, int dt, object attacker,
       int attack_id, int target_hitloc = -1)
{
    object dragon = present("ember", E(TO));
    object enemy = dragon->query_enemy();
    if (dragon && (!enemy || !present(enemy, E(TO))))
    {
      tell_room(E(TO), QCTNAME(dragon)+" joins the fight.\n");
      dragon->attack_enemy(attacker);
    }
    return ::hit_me(wcpen, dt, attacker, attack_id, target_hitloc);
}
