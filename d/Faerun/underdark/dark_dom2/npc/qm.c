/*
 * Sample quest NPC. She has lost her silk scarf
 * Coded by Clyptas, modifed for quest by Finwe
 */
inherit "/std/monster";

#include <macros.h>
#include "/d/Faerun/defs.h"

#define QUEST_NAME_PROP "_soul_quest"


create_monster()
{
    set_name("axiom");
    set_race_name("merchant");
    set_adj( ({"distraught"}) );

    set_stats( ({39, 79, 58, 68, 68, 30}) );
    set_alignment(0);
    set_gender(G_MALE);
    set_size_descs("short","lean");

    remove_prop(LIVE_M_NO_ACCEPT_GIVE);
    set_act_time(5);
    add_act("emote croaks in shock.");
    add_act("emote looks around for something.");
    add_act("emote closely examines a broken necklace.");

    set_cact_time(5);
    add_chat("Please help me!");
    add_chat("I've lost it!");
    add_chat("My soul is gone!");

    add_ask(({  "task", 
                "quest", 
                "help", 
                "necklace", 
                "soul",
                "gem",}),
        VBFC_ME("ask_quest"));

/* don't add this to your quest npc. It's here just for testing. 
 * it resets you bit so you can redo the quest for testing purposes.
 */
    add_ask("clear bit", VBFC_ME("clearbit"));


}

public string query_height_desc(){return "short"; }

public string query_width_desc() { return "lean"; }


/* This routine gives out the quest to the player when they ask for it */
string ask_quest()
{

//these are defined in /d/Faerun/sys/qbits.h
// DOMAIN = Faerun
// TEST_QUEST_GROUP = which bit group to use, in this case, GROUP4
// TEST_QUEST_BIT = The bit number to use, in this case, number 1

/* This checks to see if the player has done the quest already. 
 * if they have, they cant do it again
 */
    if(TP->test_bit(DOMAIN, TEST_QUEST_GROUP, TEST_QUEST_BIT))
    {
        command("emote double checks his belongings.");
        command("emote Doesn't appear to need assistance.\n");	    return "";
    }

// QUEST_NAME_PROP is defined at the top here

/* This checks to see if the player has been given the quest already */
    if (TP->query_prop(QUEST_NAME_PROP))
    {
	    command("emote frantically rifles through his belongings.");
	    command("asay wolf My gem is gone!");
	    return "";
    }

/* Here is where the player is given the quest and instructions */
    command("emote empties some rocks out of his boot.");
    command("asay wolf Lost my gem! It's underground!");
    command("emote frets over the loss of his most prized posession.");

/* This adds the prop to the player saying they asked for the quest */
    TP->add_prop(QUEST_NAME_PROP,1);
    return "";

}

void
test_quest(object player, object obj)
{

    if(player->test_bit(DOMAIN, TEST_QUEST_GROUP, TEST_QUEST_BIT))
    {
	    command("emote grunts indifferently.");
	    return;
    }


// has prop?
    if (!player->query_prop(QUEST_NAME_PROP))
    {
        command("emote grunts indifferently.");
        return;
    }

/* The quest is successfully done. 
 * Let's give them exp.
 */
    command("emote jumps excitedly.");
    command("asay wolf At last! You found it!");
    command("asay wolf Thank you! Thank you!");
// this shows the npcs happy and her 'disappearing' when we do remove_object()
    command("emote inspects the gem, then fixes it onto his necklace" +
        ".");
    command("emote runs off.");
    remove_object();

/* We remove the quest prop. */
    player->remove_prop(QUEST_NAME_PROP);
/* We tell them they got exp */
    tell_object(player,"You feel more experienced!\n");
    say(QCTNAME(player) + " was rewarded.\n");

/* We set the bits in the player */
    player->set_bit(TEST_QUEST_GROUP, TEST_QUEST_BIT);

// TEST_QUEST_BIT = the amt of exp this quest is worth. 
// This is also defined in qbits.h
/* We give them exp */
    player->add_exp_quest(TEST_QUEST_EXP);

// TEST_QUEST_LNG = the long descr of the quest
// This is also defined in qbits.h
/* Let's log the quest and exp */
    QUEST_LOG_FILE(TEST_QUEST_LNG, TEST_QUEST_EXP);
    obj->remove_object();
}


/* This routine is here in case players give stuff to the npc that the
 * NPC doesnt need. Naturally, the NPC keeps any money given to them. :)
 */
void
return_object(object from, object obj)
{
    string  obname = OB_NAME(from);

    if (obj->id("coin"))
    {
        command("emote bows thankfully.");
        return;
    }

    command("asay wolf No!");
    command("emote gives it back to you.\n");
    obj->move(from);
    return;
}

/* Rejects any item other than the the scarf*/ 
public void
enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);
    if (!living(from))
	    return;

    if (obj->id("_necro_soulgem"))
	    set_alarm(1.0,0.0, &test_quest(from, obj));
    else
    {
	    set_alarm(1.0,0.0, &return_object(from, obj));
	    return;
    }
}

void
clearbit()
{
    TP->clear_bit(TEST_QUEST_GROUP, TEST_QUEST_BIT);
    write("Bit cleared. \n");
}