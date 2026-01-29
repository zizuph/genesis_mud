/*
 *   /d/Gondor/ithilien/poros/npcs/captain.c
 *
 *   This is the captain and quest giver of the pirate crew.
 *
 *   Talisan,  February 1996
 *
 *   April 1996, by Sir Boron of Mordor:
 *   Added a special attack which can when wielding an axe break helmets
 *   and it hurts extra if the attack hits your head and you wear no helmet.
 *   He now also calls for guards to jump between him and an attacker, and
 *   when loosing he calls for help from guards who poison.
 *
 *   Gwyneth November 10, 2000
 *   add_ask about silver dust
 *   Gwyneth December 21, 2000
 *   Restored the mithril axe (/d/Gondor/ithilien/poros/weapons/mithril_axe)
 *     to be cloned alternating with a more common axe with clone_unique
 *     (/d/Gondor/ithilien/poros/weapons/alt_axe)
 *   Serif July 1, 2001
 *   Cleaned up typos
 */

#pragma strict_types

inherit "/d/Gondor/ithilien/poros/npcs/corsair_master";
inherit "/lib/unique.c";

#include <stdproperties.h>
#include <composite.h>
#include <formulas.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/bits.h"
#include "/d/Gondor/private/gondor_admin.h"

#define DID_CALL "_i_gondor_called_for_help"

//	 Protoypes
void     get_key();
void     information(object helper);
void     got_no_answer();
//varargs  mixed skewer(object victim);

//	Global variables
static int     Alarm_id,
               Answer_alarm,
               Inform_alarm;

static object  *Guard = allocate(2),
               *assister = allocate(4),
               axe,
               Informing,
               Report;

mixed
hit_me(int wcpen, int dt, object attacker, int attack_id)
{
    if(attack_id == -1)
    {
        /* This behaviour should have been implemented by using try_hit.
	 * At any rate, if hit_me() fails it should give an array of 0's
	 * and not just 0. */
        if(objectp(Guard[0]) && objectp(Guard[1]) )
        {
            attacker->catch_msg("The guard stops you from reaching "
                   + QTNAME(TO) + "!!\n");
            say("Tries to reach " + QTNAME(TO) + " with a deadly assault "
                   + "but is firmly hindered by the guard\n");
            return ({ 0, 0, 0, 0, 0 });
        }

        special_attack(attacker);
    }

    if(objectp(Guard[0]) )
        attacker->attack_object(Guard[0]);
    else if(objectp(Guard[1]))
        attacker->attack_object(Guard[1]);

    return ::hit_me(wcpen, dt, attacker, attack_id);

}

public int
special_attack(object victim)
{
    int i = random(3);

    object *enemies = FILTER_PRESENT_LIVE(query_enemy(-1));
    object earmour;
    mixed  *sdam;
    int    wloc = random(5);
    int    pen = 50;
    string *hitloc;
    string hurt;

    if (!objectp(victim))
        return 0;

    /*
     *  Special attack each third combat round.
     */
    if(!i == 0)
        return 0;

    hurt = "hurts";

    hitloc = ({ "neck", "right shoulder", "left shoulder",
                "head", "head" });

    set_intoxicated((intoxicated_max()));


    if (!sizeof(query_weapon(-1)))
    {
        if (!query_skill(SS_UNARM_COMBAT))
        {
            set_skill(SS_UNARM_COMBAT, 100);
            return 0;
        }
        return 0;
    }

    if (query_skill(SS_UNARM_COMBAT))
        remove_skill(SS_UNARM_COMBAT);

    if(!axe->query_wielded())
        return 0;

    if (!objectp(victim) && !sizeof(enemies))
        return 1;

    if (!objectp(victim))
        victim = enemies[random(sizeof(enemies))];

    if (ENV(victim) != ENV(TO))
        return 1;

    earmour = victim->query_armour(TS_HEAD);

    if(!earmour && hitloc[wloc] == "head")
        pen = 80;

    sdam = victim->hit_me(F_PENMOD(pen, 100), W_SLASH, TO, -1);

    if(sdam[0] >= 40 && hitloc[wloc] == "head"  && objectp(earmour))
    {
         victim->catch_msg("Your helmet cracks as the axe hits it.\n");
         say(QCTNAME(victim) +"'s helmet cracks as the axe hits it.\n");
         earmour->add_prop(OBJ_I_BROKEN, 1);
         earmour->remove_broken(1);
    }

    if (victim->query_hp() == 0)
    {
        victim->catch_msg("\nThe captain moves his right foot back...\n\n "
          + "Oh no! He reconsiders, with a speedy move his right foot "
          + "is placed only half a meter from you.\n\nAck! while "
          + "concentrating on his moves, he moved his axe above his head."
          + "\n\nA split second to late you see the axe come down "
          + "upon you with extreme speed, the axe is planted "
          + "right between your eyes.\n\nEverything goes dark!\n\n");
        say(QCTNAME(TO) +" moves close in at "+QTNAME(victim)
          + " and with extreme "
          + "speed and superior mastering of his axe he plants it "
          + "right between the eyes of "+QTNAME(victim)+".\n\n"
          + CAP(POSSESSIVE(victim)) + " skull splits instantly in "
          + "two.\n\n");
        victim->do_die(TO);
        command("cackle evil");
        command("get coins from corpse");
        command("shout Bring the next fool!");
    }

    if (!objectp(victim))
	return 1;

    switch(sdam[0])
    {
        case 0:
            victim->catch_msg("Throwing yourself backwards through the air, "
              + "you just barely avoid the axe!\n");
            say("Swinging the axe at " + QTNAME(victim) + " the captain,"
              + " misses " + victim->query_objective() + " as "
              + QTNAME(victim) + " throws " + victim->query_objective()
              + "self backwards through the air!\n", victim);
            break;
        case 1..9:
            hurt = "barely scratches";
            break;
        case 10..29:
            hurt = "scratches";
            break;
        case 30..59:
            hurt = "penetrates";
            break;
        case 60..79:
            hurt = "smashes";
            break;
        case 80..94:
            hurt = "slams";
            break;
        case 95..99:
            hurt = "violently slams";
            break;
        default:
            victim->catch_msg("You feel extreme pain as the axe "
              + "penetrates into your skull!!!\n");
            say("The captain's axe penetrates into the head of "+ QTNAME(victim)
              + ".\nYou wonder if "+ QTNAME(victim) + " will survive!\n");
    }

   victim->catch_msg(QCTNAME(TO) + " swings his axe wildly at you.\nIt "
      + hurt + " your " + hitloc[wloc] + "!\n");

   say(QCTNAME(TO) + " swings his axe wildly at " + QTNAME(victim)
      + "\nIt " + hurt + " " + POSSESSIVE(victim) + " " +hitloc[wloc]
      + "!\n", victim);

   command("close door");

   return 1;
}


public void
attacked_by(object ob)
{
    int i = random(2);
    int x = random(4);

    object guard1 = Guard[0];
    object guard2 = Guard[1];

    ::attacked_by(ob);
    TELL_ADMIN("[Gaerhir attacked by " + ob->query_cap_name() +
    "("+ob->query_average_stat()+") at " + ctime(time()) + "]");
// the Next four lines is for debugging purpose!!!
/*
    find_living("talisan")->catch_msg("\nGaerhir is being attacked, by "
          + CAP(ob->query_real_name()) + " with avg stat "
          + ob->query_average_stat()+".\n\n");
*/
    command("close door");

    if (!objectp(guard1) && !objectp(guard2) && !objectp(assister[x]) )
    {
        command("say You think you can kill me? Those guards were only fools!");
        command("say Now the real battle will commence!");
        command("grin");
    }
    else
    {
        command("say You thought you could get to me? Think again!");
        command("cackle");
        command("emote screams: You will die now, " + ob->query_race_name());
        command("shout Guards, break "+ POSSESSIVE(TP) +" neck!!");

        if( i == 0 && objectp(guard1) )
            ob->attack_object(guard1);
        else if( i == 1 && objectp(guard2) )
            ob->attack_object(guard2);
        else if( objectp(assister[x]) )
            ob->attack_object(assister[x]);

    }

}

public void
create_corsair()
{
    set_name("gaerhir");
    add_name(({"pirate", "leader", "captain", "corsair"}));
    set_adj(({"towering", "black-numenorean"}));
    set_title("the Captain of the Black Drake Corsairs");
    set_long(BSN("This towering Black Numenorean is the leader of "
      + "the Black Drake corsairs. His manner indicates that "
      + "he is a man of little patience. Looking weary of paperwork "
      + "the powerful Captain seems to long for battle, plunder, "
      + "and the sea."));

    default_config_npc(105+random(5));
    set_base_stat(SS_STR, 130+random(10));
    set_base_stat(SS_DEX, 120+random(10));
    set_base_stat(SS_CON, 150+random(10));
    set_skill(SS_WEP_AXE, 100);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_BLIND_COMBAT, 95+random(5));
    set_skill(SS_AWARENESS, 85+random(15));

    set_alignment(-250);
    set_living_name("gaerhir");
    set_whimpy(35);

    add_prop(LIVE_I_QUICKNESS, 100);
    add_prop(CONT_I_HEIGHT, 200 +random(50));
    add_prop(CONT_I_WEIGHT, 75000 +random(30*500));
    add_prop(CONT_I_VOLUME, 80000 +random(30*500));
    add_prop("_ranger_m_no_disarm_drop", 1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);

    remove_prop(LIVE_I_NEVERKNOWN);

    set_chat_time(4 +random(3));
    add_chat("I hate this damn paperwork!");
    add_chat("We have captured a Gondorian naval officer. The results of "
      + "his interogation were splendid indeed!");
    add_chat("I could use someone who knows their way around Minas Morgul for a job.");
    add_chat("Let me tell you, nothing beats plundering in the heart of Gondor!");
    add_chat("Have you ever been to the Havens of Umbar?");
    add_chat("I have no need of cowards helping me! Only ask if you're up for a hard task.");
    add_chat("Oh, how I would love to rip somebody's head off right now...");
    add_chat("If anybody has a problem with the orders, that is their problem!");
    add_chat("Our ships are sleek enough where we can raid up the major rivers as well!");
    add_chat("Someday I'll command all of the corsairs!");
    add_chat("I think Umbar and Minas Morgul should join against Gondor.");


    set_cchat_time(2 +random(2));
    add_cchat("Die, you rancid dog!");
    add_cchat("Your head will soon be on a pole!");
    add_cchat("Looks like we have another slave!");
    add_cchat("For Umbar!");
    add_cchat("Death to Gondor!");
    add_cchat("Long live the Corsairs!");
    add_cchat("Castamir Lives!");


    set_default_answer(VBFC_ME("default_answer"));

    add_ask(({"job", "about job", "task", "about task", "help",
        "about help", "quest", "about quest", "assignment",
        "about assignment"}),
        VBFC_ME("quest_inform"));

    add_ask(({"dust", "silver dust", "silver"}), "say I think " +
        "you're too curious for your own good!", 1);

    add_ask(({"umbar", "about umbar"}),
        VBFC_ME("umbar_inform"));

    add_ask(({"corsairs", "about corsairs", "pirates",
      "about pirates", "black drake", "about black drake",
        "black drake corsairs", "about black drake corsairs"}),
        VBFC_ME("corsair_inform")),

    add_ask(({"yrchor", "about yrchor", "morgul captain",
        "about morgul captain", "uruk captain", "about uruk captain",
        "uruk", "uruk captain"}),
        VBFC_ME("uruk_inform"));

    add_ask(({"report", "about report"}),
        VBFC_ME("report_inform"));

    FIX_EUID

    TELL_ADMIN("[Gaerhir clone at " + ctime(time()) + "]");
}

void
get_help()
{
    object enemy;
    int  i = sizeof(assister);

    enemy = TO->query_attack();

    while(i--)
    {
      if (!objectp(assister[i]))
      {
        assister[i] = clone_object(POROS_DIR + "npcs/corsair_guard.c");
        assister[i]->arm_me();
        assister[i]->move_living("down", ENV(TO));
        enemy->attack_object(assister[i]);
      }
    }

}


void
get_guards()
{
    int  i = sizeof(Guard);

    while(i--)
    {
      if (!objectp(Guard[i]))
      {
        Guard[i] = clone_object(POROS_DIR + "npcs/guard.c");
        Guard[i]->arm_me();
        Guard[i]->move_living("down", ENV(TO));
      }
    }

}


public void
run_away()
{

    command("shout GUARDS!!! Come to me!!!");

    if(TO->query_prop(DID_CALL))
    {
        set_whimpy(0);
        return;
    }

    TO->add_prop(DID_CALL, 1);
    set_alarm(2.0, 0.0, get_help);

    command("close door");

    return;
}

public void
arm_me()
{
    clone_object(POROS_DIR + "armours/breastplate")->move(this_object());
    clone_object(POROS_DIR + "armours/great_helm")->move(this_object());
    command("wear all");

    axe = clone_unique(POROS_DIR + "weapons/mithril_axe", 5,
        POROS_DIR + "weapons/alt_axe", 0, 65);
    axe->move(this_object(), 1);

    command("wield all");
    clone_object(POROS_DIR + "weapons/guard_dagger")->move(this_object());

    get_money();
    get_key();
    set_alarm(2.0, 0.0, get_guards);
}

void
get_money()
{
    MONEY_MAKE_SC(30 + random(20))->move(TO);
    MONEY_MAKE_GC( 6 + random( 10))->move(TO);
}

void
get_key()
{
    clone_object(POROS_DIR + "obj/key_chest")->move(TO);
}

int
query_knight_prestige() {return 500;}

void
init_living()
{
    ::init_living();
    add_action("accept_job", "nod");
    add_action("refuse_job", "shake");
}

string
default_answer()
{
    command("growl " +TP->query_real_name());
    command("say I have many things to do.");
    command("say So don't waste my time on trivial matters.");
    command("fume");
    command("say Or I may decide to plant my axe in your skull...");
    command("sneer");
      return "";
}

string
umbar_inform()
{
    command("smile");
    command("say Umbar is the greatest of all cities in Middle-earth.");
    command("say Its full of life, and it's women and taverns are the "
      + "finest you'll find anywhere.");
    command("emote remembers fondly his last visit to Umbar.");
    command("I'll have to return there soon, and you should visit it "
      + "if you ever get the chance...");
    command("But alas, I have much work to do, and must be getting "
      + "back to it now.");
    command("emote starts looking through the papers on his desk.");
    command("sigh");
      return "";
}

string
corsair_inform()
{
    command("say We are the most fearsome of all of the "
      + "corsairs in Umbar.");
    command("say We have sunk more Gondorian ships than all the others combined!");
    command("emote thinks of Gondor.");
    command("spit");
    command("say They have been sending out more patrols lately, but "
      + "they'll never catch the Drake, shes too fast!");
    command("say They're much too slow and stupid.");
    command("grin");
    command("say The Black Drake is a sleek vessel alright...");
    command("say Right now she should be returning from a raid near "
      + "Linhir, on the Belfalas.");
    command("say She'll return for a fresh crew, and then head out again "
      + "with her escorts, and hit somewhere else.");
    command("think about being out raiding.");
    command("say Which reminds me, I have work to attend to...");
    command("emote sits down at his desk, and begins writting.");
      return "";
}

string
uruk_inform()
{
    command("say Yrchor is one of the Captains in the Morgul Army.");
    command("say If I ever come across information I think he could "
      + "use, I send a courier up to Minas Morgul with it.");
    command("say We're not aligned with Morgul, but it sure pays in "
      + "our profession to be on their good side...");
    command("say Look for him in Minas Morgul, I can't tell you "
      + "exactly where.");
    command("say I try to stay away from that black dungeon they call "
      + "a city... It reeks of death and dark sorceries.");
    command("shiver");
    command("say I have work to do, so be on your way.");
    command("emote picks up a chart from his desk, and circles a coordinate.");
    command("emote looks at you.");
    command("shout I said go! Now!");
    command("emote gets a fierce gleam in his eyes.");
      return "";
}

string
report_inform()
{
    if (TP->test_bit("Gondor", MORGUL_GROUP, POROS_CORSAIRS_BIT))
    {
        command("say Report? What report?");
        command("peer search " + TP->query_real_name());
        command("say You already delivered it to Yrchor, did you not?");
        command("say It's contents is none of your concern.");
        command("emote waves dismissively.");
        return "";
    }
    command("say It's information we got recently from a captured "
      + "Gondorian naval officer.");
    command("say It contains some information of a quite sensitive nature.");
    command("say But you needn't worry about that... I just need you to take it to Yrchor, in Minas Morgul.");
    command("say Only he will be able to understand it.");
    command("say Now be on your way! or you'll find youself in one of our cells!");
      return "";
}

string
quest_inform()
{
    string  who = TP->query_real_name();

    if (TP == Informing)
	return "";
    if (objectp(query_attack()))
    {
	command("sneer " + who);
	return "";
    }
    if (TP->test_bit("Gondor", MORGUL_GROUP, POROS_CORSAIRS_BIT))
    {
        command("eyebrow " + TP->query_real_name());
        command("say You again?");
        command("say Listen, I'm pleased that you helped me earlier.");
        command("say But right now, I'm busy, and I have no need for you.");
        command("wave wearily");
        return "";
    }
    if (TP->query_prop("_gondor_i_corsair_quest"))
      {
        command("say I already gave you the report?");
        command("shout Now get going, and give it to Yrchor!");
        return "";
    }
    Informing = TP;

    if (Answer_alarm && sizeof(get_alarm(Answer_alarm)))
	remove_alarm(Answer_alarm);
    Answer_alarm = set_alarm(60.0, 0.0, "got_no_answer");
    command("introduce me to "+who);
    command("say I need someone to serve as a courier "
	    + "for me.");
    command("say My corsairs would be a bit too conspicious, so I need "
	    + "someone like you.");
    command("say If your're interested in the job, "
	    + "just 'nod' to accept it, and I'll fill you in on the details.");
    return "";
}

void
got_no_answer()
{
    command("say I'm a busy man, and have no time for idle "
      + "chat, If you can't help me, then get out of here.");
    command("emote begins sorting through some papers on his desk.");
    command("emote looks at you.");
    command("shout Now!");
    Informing = 0;
    Answer_alarm = 0;
}

int
accept_job()
{
    object tp = TP;

    if (Informing != TP)
      return 0;
    if (Answer_alarm && sizeof(get_alarm(Answer_alarm)))
    {
      remove_alarm(Answer_alarm);
      Answer_alarm = 0;
    }
    say(QCTNAME(tp)+" nods solemnly at "+QTNAME(TO)+".\n",tp);
    write("you nod at Gaerhir.\n");

    if (objectp(query_attack()))
    {
      command("sneer "+TP->query_real_name());
      return 1;
    }
    if (Inform_alarm && sizeof(get_alarm(Inform_alarm)))
      return 0;

    command("say Ah, good, I was hoping someone like you would come along");
    command("smile evil");
    command("say Ok, now be sure to listen to this carefully, Its not "
      + "that difficult to follow, and I won't repeat myself...");
    Inform_alarm = set_alarm(3.0, 0.0, "information", Informing);
    START_QUEST(TP, "CORSAIR CAPTAIN REPORT");
    return 1;
}

int
refuse_job()
{
    if (Informing != TP)
      return 0;

    say(QCTNAME(TP)+" shakes "+TP->query_possessive()+"head.\n",TP);
    write("you shake your head, declining Gaerhir's task.\n");
    command("say Very well, be on your way then.");
    command("say I am too busy for idle chat...");
    command("say And thank you for wasting my time.");
    command("smirk");
    command("emote spreads a chart out upon his desk and begins to look at it carefully.");
    Informing = 0;
    return 1;
}

void
information(object helper)
{
    string  name;
    Inform_alarm = 0;
    if (!objectp(helper))
      return;

    name = helper->query_real_name();

    command("say Alright, here is what I need you to do...");
    command("say Deliver this report to Yrchor in Minas Morgul.");
    command("say He is an Uruk Captain in the Morgul Army.");
    command("say He controls the troops stationed in the city, and will know what to do.");
    command("say Once you give it to him you will be rewarded for your efforts.");
    command("say Ok, now here's the report, don't lose it!");
    command("say You won't be getting another chance.");
    command("say Now get going!");
    helper->add_prop("_gondor_i_corsair_quest", 1);
    Report = clone_object(POROS_DIR + "obj/report");
    Report->move(TO);
    command("give report to "+helper->query_real_name());
    Informing = 0;
}
