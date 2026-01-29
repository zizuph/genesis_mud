
/*
 * "/d/Ansalon/estwilde/living/brewseeker.c"
 *
 *  Quest-giver for Iron Delving Brewery
 *  ....far from home ... looking for a decent brew  
 *
 *  based on the Iron Delving dwarf guard
 *
 *  resides in the Inn of the Last Home in Solace
 *
 *  Vitwitch 2021
 */

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <wa_types.h>
#include <money.h>
#include "/d/Ansalon/common/brewcraft/brewcraft.h"

#define WEP1 WEP + "iron_axe"
#define ARM1 ARMOUR + "chainmail"
#define ARM2 ARMOUR + "leggings"
#define ARM3 ARMOUR + "i_gauntlets"
#define ARM6 ARMOUR + "i_boots"
#define ARM4 ARMOUR + "shield"
#define ARM5 ARMOUR + "horned_helmet"
#define HORN "/d/Ansalon/estwilde/obj/warning_horn"

#define BREWCRAFTMUG "_brewcraft_beermug"
#define BREWCRAFTVSL "_brewcraft_beer_vessel_full"

#define BREWSEEKER_INTROD "_brewseeker_m_introd"

#define BREWCRAFT_QUEST1 "_brewcraft_quest1"
#define BREWCRAFT_QUEST2 "_brewcraft_quest2"
#define QUEST_DOMAIN "ansalon"
#define QUEST_BITGROUP 1
#define QUEST_BIT1 0
#define QUEST_BIT2 1
#define QUEST_XP1 1000
#define QUEST_XP2 4500

inherit AM_FILE

public void do_answer(string what, object who);
void remove_quest_props(object who);
void calculate_experience(object who);

void
create_krynn_monster()
{
    if(!IS_CLONE)
	return;

    set_living_name("rusty");
    set_name("rusty");
    set_title("Forgewater, Seventh Son, Exile of Iron Delving");
    set_race_name("dwarf");

    set_adj("gruff");
    add_adj("fork-bearded");

    set_gender("G_MALE");
    set_long("This is dwarven warrior of Iron Delving -- " +
      "far from home and out of sorts. He " +
      "looks like he is settled down to drown his sorrows, but does not " +
      "look like the type of person to shy away from a fight.\n");

    set_stats(({200,119,240,89,89,110}));
    set_hp(query_max_hp());
    set_skill(SS_WEP_AXE, 100);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_AWARENESS, 80);
    set_skill(SS_BLIND_COMBAT, 100);

    add_prop(LIVE_I_SEE_DARK, 10);
    remove_prop(NPC_M_NO_ACCEPT_GIVE);

    set_alignment(100);
    set_knight_prestige(-1);

    set_act_time(15);
    add_act("emote stretches his gnarled hands around his mug of brew.");
    add_act("emote grumbles about the quality of the latest batch of Iron Delving Export Brew.");
    add_act("emote looks wistfully at the brew mug in his hands and shakes his head.");
    add_act("emote strokes his greying forked beard.");
    add_act("say Ol' Jade must be in need of some new brewin' talent.");

    set_introduce(1);

    set_default_answer("The dwarf looks at you funnily, as if " +
      "you should already know the answer to that.\n");
    add_ask(({"help","quest","task"}), "@@ask_help");
    add_ask("reward", "@@ask_reward");

    set_cact_time(6);
    add_cact("assist");
    add_cact("assist");
    add_cact("emote roars 'Great Reorx!' in astonishment!");
    add_cact("say curse yas to eternal rust and corrosion!");
    add_cact("emote roars: You doorknob! What ye think yur do'en?");

}

void
arm_me()
{
    seteuid(getuid(TO));
    clone_object(WEP1)->move(TO,1);
    clone_object(ARM1)->move(TO);
    clone_object(ARM2)->move(TO,1);
    clone_object(ARM3)->move(TO,1);
    clone_object(ARM4)->move(TO,1);
    clone_object(ARM5)->move(TO,1);
    clone_object(ARM6)->move(TO,1);
    clone_object(HORN)->move(TO,1);
    command("wield all");
    command("wear all");
}


int
special_attack(object enemy)
{
    int   attacktype,
    pen,
    wloc;

    mixed hitres;

    string *hitloc,
    how,
    weapon;

    object enemy_weapon;
    string wep_string;

    if(!sizeof(query_weapon(-1)))
	return 0;

    attacktype = random(3);

    hitloc = ({ "left arm", "right arm", "body", "left leg", "right leg"});

    weapon = query_weapon(-1)[0]->query_short();
    if(sizeof(enemy->query_weapon(-1)))
    {
	enemy_weapon = enemy->query_weapon(-1)[0];
	wep_string = enemy->query_weapon(-1)[0]->query_short();
    }

    if (attacktype == 1)
    {
	pen = 350 + random(200);

	hitres = enemy->hit_me(pen, W_SLASH, TO, -1);

	wloc = random(5);

	if (hitres[0] <= 0)
	    how = "his " + weapon + " just missing";
	if (hitres[0] > 0)
	    how = "his " + weapon + " grazing the skin of";
	if (hitres[0] > 10)
	    how = "slicing his " + weapon + " deeply into";
	if (hitres[0] > 20)
	    how = "his " + weapon + " deeply penetrating";
	if (hitres[0] > 40)
	    how = "burying his " +weapon+ " deeply into";
	if (hitres[0] > 60)
	    how = "his " + weapon + " splattering blood everywhere " +
	    "as he almost removes";

	enemy->catch_msg(QCTNAME(TO) + " charges at " +
	  "you in a furious attack, " + how + " your "
	  + hitloc[wloc] + ".\n");

	tell_room(E(TO), QCTNAME(TO)+ " charges at "+ QTNAME(enemy)
	  + " in a furious rage, " +how+ " " +QTNAME(enemy)+ "'s" +
	  " " + hitloc[wloc] + ".\n", ({enemy,TO}));

	if (enemy->query_hp() <= 0)
	{
	    enemy->do_die(TO);
	}

	return 1;
    }
    return 0;
}


void
attack_func(object enemy)
{
    if(!CAN_SEE(TO, enemy))
    {
	enemy->catch_msg(QCTNAME(TO)+ " is oblivious to your presence.\n");
	return;
    }
    command("shout Scum! Die ye bastard!");
    command("kill " +enemy->query_real_name());
    command("blow horn");
}


void
attacked_by(object ob)
{
    ob->add_prop(DWARF_ENEMY, 1);
    command("shout Iron Delvi... ahem...");
    command("shout Solace! To Arms!");
    ::attacked_by(ob);
}


void
greet_func(object enemy)
{
    if(!CAN_SEE(TO, enemy))
    {
	enemy->catch_msg(QCTNAME(TO)+ " is oblivious to your presence.\n");
	return;
    }
    if(random(3) == 1)
    {
	if(random(2) == 1)
	{
	    command("say to " +enemy->query_real_name() + " Greetins to ya!");
	    command("emote raises his iron battleaxe in greetings.");
	}
	else
	{
	    command("emote raises his iron battleaxe, saying: " +
	      "Axes high friend!");
	    command("smile dwarvish " +enemy->query_real_name());
	}
    }
}


void
init_living()
{
    ::init_living();
}


int
barred_race( object ob )
{
    if(ob->query_race_name() == "goblin" ||
       ob->query_race() == "goblin" ||
       ob->query_race_name() == "hobgoblin" ||
       ob->query_race_name() == "minotaur" ||
       ob->query_race_name() == "ogre" ||
       ob->query_prop(DWARF_ENEMY) )
        return 1;

    return 0;
}

void
barred_race_hint( object who )
{
    if ( !barred_race(who) ) return;

    who->catch_msg(QCTNAME(TO) + " winks at you conspiratorily.\n");
    say(QCTNAME(TO) + " winks at " + QTNAME(who) + " .\n", who);
    who->catch_msg(QCTNAME(TO) + " says to you: By the looks of "+
         "you... you're a bit of a black sheep like me hey? "+
         "No easy way into Iron Delving for you... you might "+
         "think... Well, you need to use the goblin's bootleg "+
         "tunnel to get to the brewery. Ol' Jade likes all "+
         "cultures more'n every other dwarf in Krynn I'd wager. "+ 
         "She'll be happy to see you... just find the tunnel in "+
         "the fissures in the chasm wall... just after you cross "+
         "the bridge... and you'll be a famous brewer anyday now!\n");
    say(QCTNAME(TO) + " murmurs to " + QTNAME(who) + 
         " loudly.\n", who);
    return;
}


int
is_export_brewer( object who )
{
    string strpat = sprintf("*%s*",who->query_real_name());

    if( wildmatch(strpat,lower_case(BREWCRAFT_SHORT)) )
        return 1;
    return 0;
}

int
is_champion_brewer( object who )
{
    string strpat = sprintf("*%s*",who->query_real_name());

    if( wildmatch(strpat,lower_case(BREWCRAFT_SHORTG)) )
        return 1;
    return 0;
}

public void
add_introduced(string who)
{
    if (!query_attack())
        react_introduce(who);
}

public varargs void
react_introduce(mixed who = 0)
{
    object ob;
    who = lower_case(who);

    if (!(ob = find_player(who)))
        return;

    ob->add_prop(BREWSEEKER_INTROD,1);

    if (!objectp(ob))
    {
        command("introduce me");
        return;
    }
    
    if (environment(ob) != environment() ||
        !CAN_SEE(this_object(), ob))
        return;
    
    command("introduce me to " + OB_NAME(ob));
}

int
is_known( object who )
{
    if ( !(who->query_prop(BREWSEEKER_INTROD)) )
        return 0;
    return 1;
}


public void
do_answer(string what, object who)
{
    if ( !objectp(who) || E(who) != E(TO))
        return;   /* We wont speak if the player is gone */

    switch (what)
    {
    case "task":
    case "quest":
    case "help":

        who->catch_msg(QCTNAME(TO) + " peers at you.\n");
        say(QCTNAME(TO) + " peers at " + QTNAME(who) + ".\n", who);

        if ( !is_known(who) )
        {
            who->catch_msg(QCTNAME(TO) + 
              " lifts a mug of brew towards you, scowling at it.\n");
            who->catch_msg(QCTNAME(TO) + " says to you: And who might you "+
              "be? It's bad enough having to endure this tired brew... "+
              "but to have strangers asking for help as well?\n");
            say(QCTNAME(TO) + " queries " + QTNAME(who) + 
               " dismissively.\n", who);
            return;
        }

        if( who->test_bit(QUEST_DOMAIN,QUEST_BITGROUP,QUEST_BIT1) )
        {
            if( who->test_bit(QUEST_DOMAIN,QUEST_BITGROUP,QUEST_BIT2) )
            {
                who->catch_msg(QCTNAME(TO) + " nods in appreciation at you.\n");
                who->catch_msg(QCTNAME(TO) + " says to you: It's good to see you " +
                    "again... a master brewer of Iron Delving no less! "+
                    "While you're welcome to stay and buy me a drink, "+
                    "I'm all out of jobs for you.\n");
                say(QCTNAME(TO) + " speaks earnestly with " + QTNAME(who)
                     + " for a " + "moment.\n", who);
                return;
            }
            else
            {
                if (who->query_prop(BREWCRAFT_QUEST2))
                {
                    // has started quest 2
                    who->catch_msg(QCTNAME(TO) + " nods in recognition at you.\n");
                    who->catch_msg(QCTNAME(TO) + " says to you: You've brought me a "+
                     "crystal vessel of " + capitalize(BREWCRAFT_SHORTG) + "?!\n");
                    who->catch_msg(QCTNAME(TO) + " starts excitedly.\n");
                    who->catch_msg(QCTNAME(TO) + " says to you: Give it to me and "+
                     "then ask me for your reward!\n");
                    say(QCTNAME(TO) + " speaks with " + QTNAME(who) + " for a " +
                        "moment.\n", who);
                }
                else
                {
                    // has not started quest 2
                    who->add_prop(BREWCRAFT_QUEST2,1);

                    if ( is_champion_brewer(who) ) 
                    {
                        who->catch_msg(QCTNAME(TO) + " bows in admiration of you.\n");
                        who->catch_msg(QCTNAME(TO) + " says to you: You have improved the "+
                         "quality of brew for all time! The finest in all of Iron Delving.\n");
                        who->catch_msg(QCTNAME(TO) + " says to you: "+
                         "If you could "+
                         "find your way to get me a vessel of your best, "+
                         "I'd be mighty pleased. "+
                         "I've heard tell that it comes in crystal.\n");
                        say(QCTNAME(TO) + " speaks with " + QTNAME(who) + " for a " +
                            "moment.\n", who);
                    }
                    else
                    {
                        who->catch_msg(QCTNAME(TO) + " nods in recognition at you.\n");
                        who->catch_msg(QCTNAME(TO) + " says to you: You improved the "+
                         "quality of brew around here... I thank you all nice like...\n");
                        who->catch_msg(QCTNAME(TO) + " bows to you slightly.\n");
                        who->catch_msg(QCTNAME(TO) + " says to you: But you know... "+
                         "I've heard tell of the best brew of all from Iron Delving... "+
                          capitalize(BREWCRAFT_SHORTG) + " ... now that's the stuff! "+
                         "If you could "+
                         "find your way to get me a vessel of that, I'd be mighty pleased. "+
                         "I've heard tell that it comes in crystal.\n");
                        say(QCTNAME(TO) + " speaks with " + QTNAME(who) + " for a " +
                            "moment.\n", who);
                    }
                }
            }
        }
        else
        { 
            // has not completed Quest1

            if (who->query_prop(BREWCRAFT_QUEST1))
            {
                // has started quest 1

                if ( is_export_brewer(who) )
                {
                    who->catch_msg(QCTNAME(TO) + 
                     " looks expectantly at you... "+
                     "and then the bar menu... then at you.\n");
                    who->catch_msg(QCTNAME(TO) + " says to you: "+
                         "Will you buy an old dwarf a mug of your finest? "+
                         "Then we can discuss your reward!\n");
                    say(QCTNAME(TO) + " murmurs to " + QTNAME(who) + 
                         " happily.\n", who);
                }
                else
                {
                    who->catch_msg(QCTNAME(TO) + 
                     " looks on with "+
                     "frustration in his eyes.\n");
                    who->catch_msg(QCTNAME(TO) + " says to you: "+
                         "Boar swill! That's the brew for this month. "+
                         "Weren't you going to go an' fix it?!\n");
                    say(QCTNAME(TO) + " grumbles to " + QTNAME(who) + 
                         " unhappily.\n", who);
                    barred_race_hint(who);
                }
            }
            else
            { 
                // has not started quest 1

                who->add_prop(BREWCRAFT_QUEST1,1);

                if ( is_export_brewer(who) )
                {
                    // existing export brewer -- entitled to quest xp
                    who->catch_msg(QCTNAME(TO) + 
                     " downs a mug of your brew, glugging and nodding.\n");
                    who->catch_msg(QCTNAME(TO) + " says to you: Oh well "+
                         "it's better than what we usually get around here... "+
                         "reminds me of home. Will you buy me a mug "+
                         "and we can discuss your reward for "+
                         "exporting a reminder from home?\n");
                    say(QCTNAME(TO) + " murmurs to " + QTNAME(who) + 
                         " happily.\n", who);
                }
                else
                {
                   // new beginner on quest
                    who->catch_msg(QCTNAME(TO) + 
                   " discretely pours out his mug of brew with a sour look.\n");
                    who->catch_msg(QCTNAME(TO) + " says to you: This brew is "+
                         "boar swill! I don't know what is goin' on in Iron "+
                         "Delvin' since I... left... but ol' Jade is sure brewin' "+
                         "rubbish this month!\n");
                    say(QCTNAME(TO) + " grumbles to " + QTNAME(who) + 
                         " loudly.\n", who);
                    who->catch_msg(QCTNAME(TO) + 
                   " examines you from head to toe. You can hear him sniffing in "+
                   "your vicinity.\n");
                    say(QCTNAME(TO) + " sniffs " + QTNAME(who) + 
                         " discretely.\n", who);
                    who->catch_msg(QCTNAME(TO) + " says to you: I wager "+
                         "even someone such as you could do a better job than "+
                         "whoever inspired this ... this ditchwater! "+
                         "It's settled then! You go to the Iron Delving Brewery "+
                         "and get Jade to brew something good in your name... "+
                         "come back to me and we'll share a mug... "+
                         "and I'll make it worth your while!\n");
                    say(QCTNAME(TO) + " murmurs to " + QTNAME(who) + 
                         " loudly.\n", who);
                    barred_race_hint(who);
                }
            }
        }
        break;
    case "reward":
        if ( !(who->query_prop(BREWCRAFT_QUEST2)) 
               && !(who->query_prop(BREWCRAFT_QUEST1)) )
        {
            who->catch_msg(QCTNAME(TO) + 
               " looks on in exasperation.\n");
            who->catch_msg(QCTNAME(TO) + " says to you: Reward? "+
                 "I don't know anything about that now.\n");
            say(QCTNAME(TO) + " grumbles to " + QTNAME(who) + 
                 " in exasperation.\n", who);
            return;
        } 
        calculate_experience(who);
        break;
    }
}

public string
ask_help()
{
    set_alarm(1.0, 0.0, &do_answer("help", TP));
    return "";
}

public string
ask_reward()
{
    set_alarm(1.0, 0.0, &do_answer("reward", TP));
    return "";
}


void
remove_quest_props(object who)
{
    if (who->query_prop(BREWCRAFT_QUEST1))
        who->remove_prop(BREWCRAFT_QUEST1);
    if (who->query_prop(BREWCRAFT_QUEST2))
        who->remove_prop(BREWCRAFT_QUEST2);
}



void
calculate_experience(object who)
{
    int xp_base1 = QUEST_XP1;
    int xp_base2 = QUEST_XP2;
    string strpat;
    object mug, vessel;
    object reward;


    if ( who->test_bit(QUEST_DOMAIN,QUEST_BITGROUP,QUEST_BIT2) ) return;

    if ( who->query_prop(BREWCRAFT_QUEST2) )
    {
        vessel = present(BREWCRAFTVSL);

        if (!vessel)
        {
            who->catch_msg(QCTNAME(TO) + 
              " looks you up and down expectantly.\n");
            who->catch_msg(QCTNAME(TO) + " says to you: I'm hankering for "+
             "you to give me that crystal vessel! Do you have it? "+
             "Hand it over and we'll talk reward!\n");
            say(QCTNAME(TO) + " huffs at " + QTNAME(who) + 
             " excitedly.\n", who);
            return;
        }

        strpat = sprintf("*%s*",lower_case(BREWCRAFT_SHORTG));
//VW
who->catch_msg("strpat " + strpat + "\n");
who->catch_msg("vessel " + lower_case(vessel->query_short()) + "\n");

        if( wildmatch(strpat,lower_case(vessel->query_short())) )
        {
            who->catch_msg(QCTNAME(TO) + 
             " downs the contents of the crystal vessel all at once, "+
                "slaking his thirst. He revels in its taste all the "+
                "way down. He casts the empty vessel aside. It shatters "+
                "into a thousand glittering fragments. They disappear " +
                "from sight as though taken up by an unseen force.\n");
            who->catch_msg(QCTNAME(TO) + " says to you: "+
             "That's the stuff all right!\n\n");
            reward = MONEY_MAKE_PC(50);
            reward->move(TO);
            command("give coins to " + OB_NAME(who));

            who->catch_msg("You feel more experienced.\n");
            tell_room(E(who), QCTNAME(who) + " looks more experienced.\n", who);

            who->add_exp_quest(xp_base2);
            who->set_bit(QUEST_BITGROUP, QUEST_BIT2);

            A_QUEST_LOG("quest", "Iron Delving Brewery Quest 2", who, xp_base2);
            remove_quest_props(who);
        }
        else
        {
//VW messaging
        }

        vessel->remove_object();
        return;
    }

    if ( who->test_bit(QUEST_DOMAIN,QUEST_BITGROUP,QUEST_BIT1) ) return;

    if ( who->query_prop(BREWCRAFT_QUEST1) )
    {
        mug = present(BREWCRAFTMUG);

        if (!mug)
        {
            who->catch_msg(QCTNAME(TO) + 
              " looks you up and down expectantly.\n");
            who->catch_msg(QCTNAME(TO) + " says to you: I'm hankering for "+
             "you to give me that mug of your finest! "+
             "Hand it over and we'll talk reward!\n");
            say(QCTNAME(TO) + " huffs at " + QTNAME(who) + 
             " excitedly.\n", who);
            return;
        }

        strpat = sprintf("*%s*",lower_case(BREWCRAFT_SHORT));
        if( wildmatch(strpat,lower_case(mug->query_short())) )
        {
            who->catch_msg(QCTNAME(TO) + 
             " downs the contents of the mug all at once, "+
                "slaking his thirst. He revels in its taste all the "+
                "way down. He casts the empty mug aside. It smashes "+
                "somewhere in the corner... attracting a scowl from Tika.\n");
            who->catch_msg(QCTNAME(TO) + " says to you: "+
             "That's much better... reminds me of home!\n\n");

            reward = MONEY_MAKE_PC(10);
            reward->move(TO);
            command("give coins to " + OB_NAME(who));

            who->catch_msg("You feel more experienced.\n");
            tell_room(E(who), QCTNAME(who) + " looks more experienced.\n", who);

            who->add_exp_quest(xp_base1);
            who->set_bit(QUEST_BITGROUP, QUEST_BIT1);

            A_QUEST_LOG("quest", "Iron Delving Brewery Quest 1", who, xp_base1);
            remove_quest_props(who);
        }
        else
        {
//VW messaging
        }

        mug->remove_object();
        return;
    }
}

