/*
 * nagrogh.c
 *
 * The Hooded figure you may find in a secret cave near Kurinost.
 *
 * Copyright (C): Kellon, october 2012
 *
 */
#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>
#include "/d/Krynn/common/defs.h"
#include "local.h"
#include "/d/Krynn/guilds/sohm/defs.h"

inherit M_FILE

#define TASK_NUMBER "_kurinost_raxx_task_number"
#define TENT_NUMBER "_kurinost_outpost_tent"
#define TYBERUS_KILLED "_kurinost_raxx_task_killed_tyberus"
#define RAZOGH_KILLED "_kurinost_raxx_task_killed_razogh"

public void
create_krynn_monster()
{
    set_name("raxx");
    add_name("hobgoblin");
    add_name("figure");
    add_adj("dark");
    add_adj("hooded");
    set_race_name("hobgoblin");
    set_title("Durkaa, Former Sergeant of the Green Dragonarmy, Deserter");

    set_long("Hidden quite well in the darkness of the cave, it " +
        "is fairly difficult to see the dark figure from down " +
        "here. Once you have spotted him though, even his hooded " +
        "cloak cannot hide his features and you easilly recognize " +
        "the distinct features of a hobgoblin. As he moves to " +
        "face you, you notice his red eyes reflecting the pale " +
        "light comming from outside. He seems lean, almost thin, " +
        "short and not very muscular and you hear nothing as he " +
        "moves, suggesting that he is not using metal armours.\n");

    set_stats(({45,50,50,55,50,40}));

    set_skill(SS_WEP_CLUB, 45);
    set_skill(SS_DEFENCE, 40);
    set_skill(SS_PARRY, 25);
    set_skill(SS_HIDE, 100);
    set_skill(SS_SNEAK, 100);
    set_skill(SS_AWARENESS, 100);

    set_alignment(-400);
    set_knight_prestige(85);

    add_prop(CONT_I_WEIGHT, 85000);
    add_prop(CONT_I_HEIGHT, 160);
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(OBJ_M_NO_ATTACK, "Hidden in the darkness on the " +
        "ledge, the dark figure is too far away to attack. You " +
        "would not be able to hit him from here.\n");
    remove_prop(NPC_M_NO_ACCEPT_GIVE);

    add_ask(({"silvanesti forest","hedge","hedge wall","wall"}),
        "say A hedge wall surrounds the Silvanesti forest. It is almost " +
        "impossible to break through.", 1);
    add_ask(({"draconian forces","forces"}),
        "say We had a draconian force that I sent through the hedge wall " +
        "into the Silvanesti forest. They never returned. Razogh blamed me!", 1);
    add_ask(({"razogh","first lieutenant"}),
        "say Razogh was the First Lieutenant of our patrol. I was his second-" +
        "in-command. He blamed me for the loss of our draconian forces, and I " +
        "am afraid he will report that back to High Commander Tyberus!", 1);
    add_ask(({"tyberus","high commander","high commander tyberus"}),
        "say High Commander Tyberus leads the invasionary forces of the Green " +
        "Dragonarmy here in Silvanesti. If he thought I was to blame for the " +
        "loss of his draconian forces he would hunt me to the end of the " +
        "continent!", 1);
    add_ask(({"green dragonarmy"}),
        "say I was second-in-command of a patrol for the invasionary forces " +
        "of the Green Dragonarmy here in Silvanesti.", 1);
    add_ask(({"help","help each other"}),"@@help_answer");
    add_ask(({"spellbook","spells"}),"@@spellbook_answer");
    add_ask(({"tracks","cover tracks","cover","cover my tracks"}),"@@tracks_answer");
    add_ask(({"ingredients","new message","forge a new message","ingredient","seal",
        "blank parchment","pear","prickly pear","egg","yoke","seagull egg","braid"}), 
        "@@ingredient_answer");
    add_ask(({"message"}), "@@message_answer");
    add_ask(({"messenger"}), "@@messenger_answer");
    set_default_answer("@@default_answer");


    setuid();
    seteuid(getuid());
}

string
help_answer()
{
    if ((this_player()->query_guild_name_occ() != "School of High Magic") &&
       (this_player()->query_guild_name_occ() != "Wizards of High Sorcery"))
    {
        command("say You cannot help me I do not think! Leave my cave!");
        return "";
    }

    if(SOHM_MANAGER->query_scribed_spell(this_player(), "iniksuaco") &&
       SOHM_MANAGER->query_scribed_spell(this_player(), "jennufethos"))
    {
        command("stare thankful " +TP->query_real_name());
        command("say You have helped me enough. Leave me to my cave before " +
            "you blow my cover!");
        return "";
    }

    command("introduce myself");
    command("say Yes, you may be able to help me!");
    command("say If you can cover my tracks, there is a spellbook I have " +
        "that I will give you!");

    return "";
}

string
spellbook_answer()
{
    if ((this_player()->query_guild_name_occ() != "School of High Magic") &&
       (this_player()->query_guild_name_occ() != "Wizards of High Sorcery"))
    {
        command("emote moves deeper into the shadows.");
        return "";
    }

    if(SOHM_MANAGER->query_scribed_spell(this_player(), "iniksuaco") &&
       SOHM_MANAGER->query_scribed_spell(this_player(), "jennufethos"))
    {
        command("say I gave you spellbook! Leave me be!");
        return "";
    }

    command("say I was part of a patrol at the edge of the Silvanesti forest with " +
        "a force of draconians and hobgoblins.");
    command("say When elves attacked us, an arrow slew one of our bozak draconians " +
        "right near me!");
    command("say He blew up, leaving behind nothing but his spellbook.");
    command("say Later we lost the rest of our draconian forces. Razogh, our " +
        "first lieutenant, blamed me! So I fled.");
    command("say If you can help cover my tracks, I will give you that spellbook!");

    return "";
}

string
tracks_answer()
{
    if ((this_player()->query_guild_name_occ() != "School of High Magic") &&
       (this_player()->query_guild_name_occ() != "Wizards of High Sorcery"))
    {
        command("emote moves deeper into the shadows.");
        return "";
    }

    if(SOHM_MANAGER->query_scribed_spell(this_player(), "iniksuaco") &&
       SOHM_MANAGER->query_scribed_spell(this_player(), "jennufethos"))
    {
        command("say You covered my tracks well! Now leave!");
        return "";
    }

    command("say I was second-in-command of a patrol trying to break through " +
        "the hedge wall protecting the Silvanesti forest.");
    command("say It is no normal hedge! You cut it, it grows back. You burn it, " +
        "it grows back.");
    command("say One time it didn't grow back. I sent our draconian forces " +
        "through...");
    command("say ...and the hedge grew back. The draconian force never came back.");
    command("say My commander Razogh was furious! He was going to send a messenger " +
        "to High Commander Tyberus of our failure, blaming me!");
    command("say I fled. I need you to help cover my tracks by firstly intercepting " +
        "that messenger and bring me what Razogh has sent to Tyberus.");

    return "";
}

string
messenger_answer()
{
    if ((this_player()->query_guild_name_occ() != "School of High Magic") &&
       (this_player()->query_guild_name_occ() != "Wizards of High Sorcery"))
    {
        command("emote moves deeper into the shadows.");
        return "";
    }

    if(SOHM_MANAGER->query_scribed_spell(this_player(), "iniksuaco") &&
       SOHM_MANAGER->query_scribed_spell(this_player(), "jennufethos"))
    {
        command("say You found the messenger! I gave you the spellbook! Now leave!");
        return "";
    }

    command("say Razogh's messenger wasn't well liked at the outpost.");
    command("say He usually had to sneak past the draconians, so I think " +
        "he may not have reached Tyberus yet.");
    command("say If you can't find him on his way from the Silvanesti forest to " +
        "the outpost, he may be hiding somewhere in the camp until he can sneak " +
        "past the draconians when they are drunk.");
    command("say If he has reached Tyberus, I am as good as dragon bait!");
    command("say Bring me his message. It should be carried in a green leather " +
        "satchel.");

    return "";
}

string
message_answer()
{
    if ((this_player()->query_guild_name_occ() != "School of High Magic") &&
       (this_player()->query_guild_name_occ() != "Wizards of High Sorcery"))
    {
        command("emote moves deeper into the shadows.");
        return "";
    }

    if (!TP->query_prop(TASK_NUMBER))
    {
        command("say The messenger carries his missives in a green " +
            "leather satchel.");
        command("say Seek the messenger out in the outpost south of here!");
        return "";
    }

    command("stare questioning " +TP->query_real_name());
    command("say I don't know why you are asking me about that!");

    return "";
}

string
ingredient_answer()
{
    if (!TP->query_prop(TASK_NUMBER))
    {
        command("stare fearful " +TP->query_real_name());
        command("say I don't know why you are asking me about that!");
        return "";
    }

    if(TP->query_prop(TASK_NUMBER) == 1)
    {
        command("say To begin with, I need a blank parchment that messengers " +
            "for the Green Dragonarmy normally write their orders and messages " +
            "on.");
        command("say You should be able to find a blank parchment in one of " +
            "the tents at the outpost.");
        command("say Bring me back a blank parchment and I'll tell you what " +
            "next I need.");

        int tent = random(4) + 1;
        TP->add_prop(TENT_NUMBER, tent);
        return "";
    }

    if(TP->query_prop(TASK_NUMBER) == 2)
    {
        command("say I need to make an authentic-looking seal for the fake " +
            "message.");
        command("say I can make a plausible one out of a few ingredients.");
        command("say I can use the wax from the prickly pear that grow around " +
            "the cliffs. Bring me one of those.");
        return "";
    }

    if(TP->query_prop(TASK_NUMBER) == 3 || TP->query_prop(TASK_NUMBER) == 4)
    {
        command("say To make the seal bond with the parchment I need to yoke " +
            "from a seagull egg.");
        command("say Bring me one of those.");
        return "";
    }

    if(TP->query_prop(TASK_NUMBER) == 7)
    {
        command("say Bring me Razogh's braid!");
        return "";
    }

    command("stare questioning " +TP->query_real_name());
    command("say I don't know why you are asking me about that!");
    return "";
}

string
default_answer()
{
    command("stare fearful " +TP->query_real_name());
    command("say I don't know that!");

    return "";
}


/*
 *  FUNCTION : react_to_intro
 *  Arguments: who - name of the player who introduced to me.
 *  Returns  : void
 * 
 *  Called from alarm, reaction to a players introduction.
 *
 */
public void react_to_intro(string who)
{
    object pl = find_player(lower_case(who));
    string race = pl->query_race_name();

    if (!present(pl, environment(TO)))
    {
        // Player is gone!
        command("shout What! You go already?!");
        return;
    }
    else if (!CAN_SEE(TO, pl))
    {
        command("emote shuffles nervously about, unable to see where the " +
             "introduction came from.");
        return;
    }    
    else
    {
        if (race == "elf")
        {
            command("say to " + who + " What?! An elf? Here?!");
            command("peer concern " + who);
            command("say Nevermind.");
        }

        if ((this_player()->query_guild_name_occ() == "School of High Magic") ||
            (this_player()->query_guild_name_occ() == "Wizards of High Sorcery"))
        {
            command("emote moves to disappear back further into the shadows of the " +
                "cave, but suddenly stops.");
            command("say Magi! Maybe we can help each other!");
            return;
        }

        command("say to " + who + " Go away " + race + "! You will blow my cover " +
            "if I am caught!");
        command("emote moves deeper into the shadows of the cave.");
    }
}


/*
 *  FUNCTION : add_introduced
 *  Arguments: string - name of the player who introduced to me.
 *  Returns  : void
 * 
 *  Reactions to introductions.
 *
 */
public void add_introduced(string who)
{
    set_alarm(1.0, 0.0, &react_to_intro(who));
}

void
give_it_back(object ob, object from)
{
    string what, who;
 
    if (ob->query_no_show())
	return;

    what = L(ob->query_short());
    who = from->query_real_name();

    command("peer suspicious " + who);
    command("emote hides the " +what+ " away deep in the shadows.");
    ob->remove_object();

}

void
return_give_message(object ob, object from)
{
    string who, what;

    what = L(ob->query_short());
    who = from->query_real_name();

    if(ob->id("_kurinost_camp_secret_satchel_"))
    {
        command("frown suspic");
        command("drop satchel");
        command("say Just give me the message from Razogh!");
        return;
    }

    command("say Ah! This is the sort of missive Razogh would send!");

    if(!ob->query_seal())
    {
        command("say I see you didn't read it...");
        command("break seal");
    }

    command("read parchment");
    command("scream");
    command("say If High Command Tyberus reads this he will hunt " +
        "me to the ends of the continent!");
    command("say Before I give you the spellbook, I need you to " +
        "help me forge a new message to give Tyberus!");
    command("say And to do that, I need you to get me some ingredients.");
    from->add_prop(TASK_NUMBER, 1);
    ob->remove_object();

    return;   

}

void
return_give_ingredient1(object ob, object from)
{
    string who, what;

    what = L(ob->query_short());
    who = from->query_real_name();

    command("say Yes! This is the sort of parchment that the Green " +
        "Dragonarmy use for their messages!");
    command("emote hastily scrawls a message on it with a piece of coal.");
    command("say Now, for it to be authentic it needs a seal.");
    command("say I can make a plausible one out of a few ingredients.");
    command("ponder");
    command("say I can use the wax from the prickly pear that grow around " +
        "the cliffs. Bring me one of those.");
    from->add_prop(TASK_NUMBER, 2);
    ob->remove_object();

    return;   
}

void
return_give_ingredient2(object ob, object from)
{
    string who, what;

    what = L(ob->query_short());
    who = from->query_real_name();

    command("emote winces in pain and drops the " +what+ ".");
    command("say Are you trying to maim me? For a magi you are dull! ");
    command("say Go get me another one, but cut the thorns off this " +
        "time!");
    ob->remove_object();

    return;   
}

void
return_give_ingredient3(object ob, object from)
{
    string who, what;

    what = L(ob->query_short());
    who = from->query_real_name();

    command("say Nice nice! The colouring is almost the same as a Dragonarmy " +
        "seal, and it will bond perfectly with the parchment with one " +
        "last ingredient.");
    command("say The yoke from an egg should do it. Get me an egg from one " +
        "of the many seagull nests along the cliffs.");
    from->add_prop(TASK_NUMBER, 3);
    ob->remove_object();

    return;   
}

void
return_give_ingredient4(object ob, object from)
{
    string who, what;

    what = L(ob->query_short());
    who = from->query_real_name();

    command("emote looks at the " +what+ " hungrily.");
    command("break egg");
    command("eat egg");
    command("burp");
    command("say Yes that will do nicely to bond the seal! Bring " +
        "me another?"); 
    from->add_prop(TASK_NUMBER, 4);

    return;   
}

void
return_give_ingredient5(object ob, object from)
{
    string who, what;
    object parchment = clone_object(RSOBJS + "dc_document_fake");

    what = L(ob->query_short());
    who = from->query_real_name();

    command("say Well done magi...");
    command("break egg");
    command("emote mixes the yoke of the " +what+ " with a dark " +
        "waxy substance, and moulds it on to a folded piece of parchment."); 
    command("say A masterpiece! Here... take this fake message and give it " +
        "to High Commander Tyberus.");
    from->catch_tell("You are given a folded parchment.\n");
    parchment->move(from, 1);
    command("say And when you have done that return to me quickly! There " +
        "is one last thing you will need to do for this ruse to work.");
    
    from->add_prop(TASK_NUMBER, 5);

    return;   
}

void
return_give_ingredient6(object ob, object from)
{
    string who, what;
    setuid();
    seteuid(getuid());

    object spellbook = clone_object(RSOBJS + "spellbook");
    spellbook->move(TO, 1);

    what = L(ob->query_short());
    who = from->query_real_name();

    if(!from->query_prop(RAZOGH_KILLED))
    {
        command("say What is this?");
        command("emote narrows his eyes suspiciously.");
        command("say It looks like the braid of Razogh, but you " +
            "don't have the look of someone who battled him!");
        command("say You need to kill Razogh! Not give him a hair " +
            "cut! Go and personally make sure he is dead!");
        command("drop braid");
        return;
    }

    command("cheer");
    command("say I can't believe it! You did it! Razogh is dead!");
    command("say I can now return to the outpost a hero!"); 
    command("chortle");
    command("say And here is your reward as promised!");

    if(CAN_SEE(TO, from))
    { 
        command("give tome to " +OB_NAME(from));
        from->add_prop(TASK_NUMBER, "_finished_spellbook_task_for_raxx");
    }
    else
    { 
        command("drop tome");
        from->add_prop(TASK_NUMBER, "_finished_spellbook_task_for_raxx");
    } 

    command("emote scurries out the cave entry.");
    TO->remove_object();

    return;   
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!interactive(from))
	return;

    if(ob->id("_kurinost_camp_secret_document_") || 
       ob->id("_kurinost_camp_secret_satchel_"))
    {
	set_alarm(1.0, 0.0, &return_give_message(ob, from));
	return;
    }

    if(ob->id("_kurinost_blank_parchment") &&
       (TP->query_prop(TASK_NUMBER) == 1))
    {
	set_alarm(1.0, 0.0, &return_give_ingredient1(ob, from));
	return;
    }

    if(ob->id("uncut_prickly_pear") &&
       (TP->query_prop(TASK_NUMBER) == 2))
    {
	set_alarm(1.0, 0.0, &return_give_ingredient2(ob, from));
	return;
    }

    if(ob->id("cut_prickly_pear") &&
       (TP->query_prop(TASK_NUMBER) == 2))
    {
	set_alarm(1.0, 0.0, &return_give_ingredient3(ob, from));
	return;
    }

    if(ob->id("_kurinost_gull_egg") &&
       (TP->query_prop(TASK_NUMBER) == 3))
    {
	set_alarm(1.0, 0.0, &return_give_ingredient4(ob, from));
	return;
    }

    if(ob->id("_kurinost_gull_egg") &&
       (TP->query_prop(TASK_NUMBER) == 4))
    {
	set_alarm(1.0, 0.0, &return_give_ingredient5(ob, from));
	return;
    }

    if(ob->id("_kurinost_razogh_braid") &&
       (TP->query_prop(TASK_NUMBER) == 7))
    {
	set_alarm(1.0, 0.0, &return_give_ingredient6(ob, from));
	return;
    }

    set_alarm(1.0, 0.0, &give_it_back(ob, from));
    return;
}

public void
alert_magi(object enemy)
{
    if(!TP->query_prop(TASK_NUMBER))
        command("say Psst! Magi! Over here!");

    return;
}

public void
killed_tyberus(object enemy)
{
    write("You report back to " +TO->short()+ " on your " +
        "delivery of the message to Tyberus, how he accused you " +
        "of being a spy, and of how you slew him.\n");
    say(QCTNAME(enemy) + " reports something to " +
        TO->short()+ ".\n");

    command("say You BROKE the seal we spent so much time making, " +
        "and then gave the report to the High Commander? What were you " +
        "thinking?");
    command("boggle");
    command("say And people think hobgoblins are stupid!");
    command("ponder");
    command("say Still, Tyberus won't be hunting me down from the " +
        "grave!");
    command("giggle malevol");
    command("say So I suppose you have earnt what I promised. Here.");

    setuid();
    seteuid(getuid());

    object spellbook = clone_object(RSOBJS + "spellbook");
    spellbook->move(TO, 1);
    
    if(CAN_SEE(TO, TP))
    { 
        command("give tome to " +OB_NAME(enemy));
        enemy->add_prop(TASK_NUMBER, "_finished_spellbook_task_for_raxx");
    }
    else
    { 
        command("drop tome");
        enemy->add_prop(TASK_NUMBER, "_finished_spellbook_task_for_raxx");
    }    

    command("emote vanishes in to the shadows at the back of the cave.");

    TO->remove_object();
    return;
}

public void
final_task(object enemy)
{
    write("You report back to " +TO->short()+ " on your " +
        "delivery of the message to Tyberus.\n");
    say(QCTNAME(enemy) + " reports something to " +
        TO->short()+ ".\n");

    command("say Tyberus bought it? Hah!");
    command("chortle");
    command("say Well, that makes me look good! He now thinks I was a " +
        "hero and Razogh has taken a mortal wound!");
    command("say With Razogh dead, I could return to the camp and " +
        "likely get a promotion!");
    command("say But I need Razogh dead. As your final task, go " +
        "down to the edge of the forest and kill him. Cut the " +
        "braid from his head and bring it to me as proof.");

    enemy->add_prop(TASK_NUMBER, 7);

    return;
}

void
init_living()
{
    if(CAN_SEE(TO, TP))
    { 
        if(this_player()->query_guild_name_occ() == "School of High Magic" ||
           this_player()->query_guild_name_occ() == "Wizards of High Sorcery")
        {
            set_alarm(3.0, 0.0, &alert_magi(TP));
        }

        if(TP->query_prop(TYBERUS_KILLED) && (TP->query_prop(TASK_NUMBER) == 5))
        {
            set_alarm(3.0, 0.0, &killed_tyberus(TP));
        }

        if(TP->query_prop(TASK_NUMBER) == 6)
        {
            set_alarm(3.0, 0.0, &final_task(TP));
        }
    }

    ::init_living();
}
