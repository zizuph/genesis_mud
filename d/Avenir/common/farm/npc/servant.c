
# pragma strict_types
# include "/d/Avenir/common/common.h"
# include "/d/Avenir/include/relation.h"
# include "../defs.h"
# include <ss_types.h>
# include <money.h>
# include <macros.h>

inherit "/std/monster";
inherit "/d/Avenir/inherit/quest";

#define LABAL "_friendly_status_labal"
#define RING_BITS 2, 0
#define FARM_BITS 2, 1
#define TROUT_BITS 2, 2
#define FARM_QUEST_LOG "/d/Avenir/log/quest/farm_quest"
#define RING_QUEST_LOG "/d/Avenir/log/quest/labals_ring_quest"
#define TROUT_QUEST_LOG "/d/Avenir/log/quest/trout_quest"
#define SERVANT_LOG "/d/Avenir/log/quest/servant_log"
#define FALSE_Q_LOG "/d/Avenir/log/quest/false_questions"
#define RING_EXP 150
#define TROUT_EXP 250
#define FARM_EXP 30000
#ifndef SCROLLING_LOG
#define SCROLLING_LOG(file, entry)   ((file_size(file) > 5000) ? \
    (rm(file) && write_file(file, ctime(time()) + ": " + entry + "\n")) : \
        (write_file(file, ctime(time()) + ": " + entry + "\n")))
#endif

void found_ring(object obj, object from);
void gave_trout(object obj, object from);
void gave_letter(object obj, object from);
int bug_off(object obj);
int remove_bugged();
int bugged = 0;
int bugged_alarm;
int call_cat();

void
create_monster()
{
    set_name(({"labal","housekeeper","keeper",}));
    set_race_name("elf");
    set_adj("scarred");
    add_adj("old");
    add_name("_labal");
    set_living_name("labal");
    set_long("@@desc_long");
    set_stats(({175, 135, 150, 127, 127, 157}));
    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    set_default_answer("@@default_answer", 1);
    add_ask(({"manor","house","mansion"}),"@@tell_manor@@", 1);
    add_ask(({"master","master Berion","Berion","berion"}),"@@tell_master@@", 1);
    add_ask(({"rose","the rose","the Rose","Rose"}),"@@tell_rose@@", 1);
    add_ask(({"ceasar","bull","Ceasar"}),"@@tell_bull@@", 1);
    add_ask(({"task","job","quest","help"}),"@@tell_task", 1);
    add_ask("letter","@@tell_letter", 1);
    add_ask("lily","@@tell_lily", 1);
    add_ask(({"fish","fishing"}), "@@tell_fish", 1);
    add_ask(({"tibalsek","Tibalsek"}), "@@tell_tibalsek", 1);
    add_ask(({"reason","mood"}), "@@tell_reason", 1);
    add_ask(({"trout","trouts"}), "@@tell_trout", 1);
    add_ask("lake","@@tell_lake", 1);
    add_ask("can","@@tell_can", 1);
    add_ask("chest","@@tell_chest", 1);
    add_ask("stable","@@tell_stable", 1);
    add_ask(({"shed","tool shed"}),"@@tell_shed", 1);
    add_ask(({"maggots","bait","maggot"}),"@@tell_maggots", 1);
    add_ask("ring","@@tell_ring", 1);
    add_ask(({"night","last night"}), "@@tell_night", 1);
    add_ask(({"middle","lake middle"}), "@@tell_middle", 1);
    add_ask(({"middle of lake","middle of the lake"}), "@@tell_middle", 1);
    add_ask("middle of the lake","@@tell_middle", 1);
    add_ask(({"tower","tower room"}),"@@tell_tower", 1);
    add_ask(({"wasp","wasps"}), "@@shudder", 1);
    clone_object(THIS_DIR + "obj/dull_knife")->move(this_object());
    this_object()->command("wield knife");
    add_act("emote carves on a wooden stick.");
    set_act_time(30);
}

string
desc_long()
{
    string text;

    text = "This old elf seems to be in a sad mood, sometimes " +
           "mumbling things to himself. He looks like a servant " +
           "of sorts. ";

    if (this_player()->query_prop(LABAL) > 1)
        text += "He flashes a bright smile in your direction " +
                "before going back to his usual busines.\n";

    if (this_player()->query_prop(LABAL) < 1)
        text += "He stares right at you with a wild expression " +
                "in his eyes.\n";

    if (!(this_player()->query_prop(LABAL)))
        text += "He looks at you suspiciously.\n";
    return text;
}

/*
    Labal answers questions depending on his mood towards the player.
    If the player introduces, he gets "_friendly_status_labal" = 1.
    If he returns Labals ring he gets a 2.
    If he gives Labal a trout he gets a 3.
    Theese numbers will increase the chances to get a hint how to continue
    the quest from Labal.
    If the player atatcks him they get a -1 and Labal wont answer anymore
    questions from this player.
*/


void
add_introduced()
{

    if (this_player()->query_prop(LABAL) < 0)
    {
            set_alarm(2.0, 0.0, &command("fume"));
            return;
    }

    if (!(this_player()->query_prop(LABAL)))
    {
        this_player()->add_prop(LABAL, 1);
        set_alarm(2.0, 0.0, &command("nod suspiciously"));
        set_alarm(3.0, 0.0, &command("introduce myself"));
        set_alarm(4.0, 0.0, &command("say Im the keeper " +
            "of this manor and I dont like strangers " +
            "sneaking around."));
        SCROLLING_LOG(SERVANT_LOG, capitalize(TP->query_real_name()) +
            " did introduce him/herself.");
        return;
    }

    this_object()->command("say Hello again.");
    this_object()->command("introduce myself");

}


void
shudder()
    {
        this_object()->command("say What about them? I just hate them and so does Ceasar.");
    }

void
smirk_ceasar()
{
    this_object()->command("say Didn't I say that Ceasar is a mean " +
        "son of a bitch?");
}

string
default_answer()
{

    SCROLLING_LOG(FALSE_Q_LOG, capitalize(TP->query_real_name()) +
        " asked " + query_question() + ".");

    if (this_player()->query_prop(LABAL) > 2)
    {
        return "say I really wish I could help but I " +
            "do not know what you are looking for.";
    }

    if (this_player()->query_prop(LABAL) > 1)
    {
        return "say I do not know what you are talking about.";
    }

    int i = random(4);

    switch (i)
    {
        case 0:
            return "say Go away and do not disturb me with " +
                "silly questions.";
        case 1:
            return "say Hey. Did you do something for me? " +
                "If not, why do you expect me to help you?";
        case 2:
            return "say Oh, come on. Im not here to answer " +
                "silly questions.";
        case 3:
            return "say What about this and what about that? " +
                "Give me a good reason to answer your petty " +
                "little questions and I might. But until you " +
                "do, I have no time or reason to answer.....";
        default:
            return "Leave me alone.";
    }
}

string
tell_middle()
{
    if (this_player()->query_prop(LABAL) < 0)
        return "say Go to hell wretch!";
    if (!(this_player()->query_prop(LABAL)))
        return "say Why do you ask stranger?";
    if (this_player()->query_prop(LABAL) > 2)
        return "say The middle of the lake, yes. Best place " +
            "to catch the trout, Master Berion told me. I know " +
            "he had a way to figure out exactly when he was " +
            "in the very middle. Had something to do with " +
            "landmarks he could see or not see. I also think " +
            "the lake is a bit more shallow there as well. If " +
            "you ever get there you might catch a glimpse of " +
            "the bottom which is impossible elsewhere in the " +
            "lake.";
    return "say The middle of the lake is where Master Berion " +
        "and I used to fish for trout.";
}

string
tell_reason()
{
    if (!(TP->test_bit("Avenir", RING_BITS)))
        return "say Why bother, but if you find my ring I will be " +
            "grateful.";
    return "say Why bother?";

}

string
tell_tower()
{
    if (!(this_player()->query_prop(LABAL)))
        return "say Why do you ask stranger?";
    if (this_player()->query_prop(LABAL) > 2)
        return "say The tower, yes. Master Berion told me to " +
            "not to tell anyone, but as you have been so kind " +
            "I might make an exception. Try the secret door " +
            "in the potato cellar on the east side of the house.";
    if (this_player()->query_prop(LABAL) > 1)
            TO->command("emote points at the tower");
            return "say What about it? It is there but Master " +
                "Berion dont want anyone up there.";
    if (this_player()->query_prop(LABAL) < 0)
        return "say Go to hell wretch!";
    return "say Hmmm. What do I know.";
}

string
tell_chest()
{
    if (!(this_player()->query_prop(LABAL)))
        return "say Why do you ask stranger?";
    if (this_player()->query_prop(LABAL) > 1)
        return "say The chest yes. Master Berion never told " +
            "me about it, but I am pretty sure there is a way to " +
            "unlock it with a key if you can get rid of that coin " +
            "that is put above the keyhole. Look all over the tower " +
            "as I believe there is a trick involved.";
    return "say Hmm. What do I know about a chest?";
}
string
tell_lake()
{
    if (this_player()->query_prop(LABAL) < 0)
        return "say Go to hell wretch!";
    if (this_player()->query_prop(LABAL) > 2)
        "say I think you know all there is to " +
        "know about it. I used to fish a lot myself " +
        "but since Master Berion left, I did not go " +
        "down there anymore.";
    if (this_player()->query_prop(LABAL) > 1)
    return "say The lake is east of the farm. Best way to " +
        "take a look, is to walk through the gate in " +
        "the hedge, east of the manor. If you are lucky " +
        "you might catch a fish if you try. The lake " +
        "is good for fishing.";
    return "say The lake is east of the farm. Best way to " +
        "take a look, is to walk through the gate in " +
        "the hedge east of the manor.";
}

string
tell_night()
{
    if (this_player()->query_prop(LABAL) < 0)
        return "say Go to hell wretch!";
    if (!(this_player()->query_prop(LABAL)))
        return "say Why do you ask stranger?";
    if (this_player()->query_prop(LABAL) > 2)
        return "say The last I saw of him was the very last " +
            "night when he went out with Rose. The light " +
            "was shimmering in the lake and I saw them " +
            "from the tower window. Rowing in circles he was. " +
            "Rowing, rowing around the middle of the lake " +
            "as if he was looking for something. I really " +
            "wish he gave me that letter so that I knew " +
            "what happened to him.";
    return "say There are many things that happens here during " +
        "night.";
}

string
tell_task()
{
    if (this_player()->query_prop(LABAL) < 0)
        return "say Go to hell wretch!";
    if (!(this_player()->query_prop(LABAL)))
        return "say Why would I answer a stranger?";
    if (this_player()->query_prop(LABAL) > 1)
        return "say Thank you for asking but there was " +
               "a long time ago this place needed any help. " +
               "Now its only me left waiting for my Master to " +
               "return.";

    return "say I dont like people I dont know very well " +
        "sneaking around like you are. Please move on and leave " +
        "me and this place alone.";

}

string
tell_can()
{
    if (!(this_player()->query_prop(LABAL)))
        return "say Why would I answer a stranger?";
    if (this_player()->query_prop(LABAL) > 1)
        return "say A can? I have no idea where you can " +
            "find one. Maybe in the stable. Or the kitchen. " +
            "If you want to go fishing, you better find one " +
            "for your maggots though.";
    if (this_player()->query_prop(LABAL) < 0)
        return "say Go to hell wretch!";
    return "say I dont like people I dont know very well " +
        "sneaking around like you are. Please move on and leave " +
        "me and this place alone.";

}

string
tell_tibalsek()
{
    return "say Tibalsek? Was a long time I saw him I " +
        "must admit. Rumours say he sails between Balifor and Sybarus " +
        "on a passenger ship. If you see him, pls give him " +
        "a greet from me.";
}

string
tell_manor()
{
    if (!(this_player()->query_prop(LABAL)))
        return "say Why do you ask stranger?";
    if (this_player()->query_prop(LABAL) > 1)
        return "say This is Master Berions house. I bid you " +
            "welcome to enter.";
    if (this_player()->query_prop(LABAL) > 0)
        return "say Its really none of your business, but " +
            "its the house of my Master Berion, and he " +
            "told me to keep people away from it.";
    if (this_player()->query_prop(LABAL) < 0)
        return "say Go to hell wretch!";
    return "say I dont like people I dont know sneaking " +
           "around like you are. Please move on and leave " +
           "me alone.";
}

string
tell_maggots()
{
    if (this_player()->query_prop(LABAL) > 1)
    {
        this_object()->command("point dung heap");
        return "say There are good maggots there. Master Berion always " +
            "said they are the best for catching a trout. But remember " +
            "to put them in a can. Else they will die and no fish will " +
            "bite them.";
}
    if (this_player()->query_prop(LABAL) < 0)
        return "shout Go to hell wretch!!";

    return "say I dont like strangers sneaking around here.";
}

string
tell_trout()
{
    if (this_player()->query_prop(LABAL) < 0)
        return "shout Go to hell wretch!!";

    if (TP->test_bit("Avenir", TROUT_BITS))
        return "say Thank you, I already got " +
            "a trout from you once which I " +
            "appreciated highly. The best place to " +
            "catch them is in the middle of the lake " +
            "Master Berion always told me.";

    if (this_player()->query_prop(LABAL) > 1)
    {
        return "say Ahh. Yes, if you are lucky you might " +
            "catch a trout in the lake. Master Berion " +
            "always told me they are the very best and I " +
            "completely agree with him there. If you could " +
            "find one of those for me I will be very grateful.";
    }

    return "say I dont like strangers sneaking around here.";
}

string
tell_fish()
{
    if (this_player()->query_prop(LABAL) > 1)
    {
        return "say There are some good fish to catch " +
            "in the lake. I lost my fishing pole " +
            "but if you can find it, I am sure you can " +
            "also get some fish with it. Perhaps even a " +
            "trout.";
}

    if (this_player()->query_prop(LABAL) < 0)
        return "shout Go to hell wretch!!";
    return "say I dont like strangers sneaking around here.";
}

string
tell_stable()
{
    if (this_player()->query_prop(LABAL) > 1)
    {
        this_object()->command("point stable");
        return "say The stable is right there. Please enter " +
            "if you want to take a look inside";
}
    if (this_player()->query_prop(LABAL) < 0)
        return "shout Go to hell wretch!!";
    return "say I dont like strangers sneaking around here.";
}

string
tell_shed()
{
    if (this_player()->query_prop(LABAL) > 0)
    {
        this_object()->command("point shed");
        return "say The shed is right there. Please enter " +
            "if you want to take a look inside";
}
    if (this_player()->query_prop(LABAL) < 0)
        return "shout Go to hell wretch!!";
    return "say I dont like strangers sneaking around here.";
}


string
tell_letter()
{
    if (this_player()->query_prop(LABAL) < 0)
        return "shout Go to hell wretch!!";

    if (TP->test_bit("Avenir", FARM_BITS))
        return "say Thank you, but I already got " +
            "my letter from you once.";

    if (this_player()->query_prop(LABAL) > 1)
        return "say He told me he wrote a letter " +
            "with instructions about ....\n" +
            "Hmm. I really shouldnt say anything more " +
            "but if you find the letter I would be very " +
            "grateful.";

    return "say What letter are you talking about?";
}

string
tell_master()
{
    if (!(this_player()->query_prop(LABAL)))
        return "say Why do you ask stranger?";
    if (this_player()->query_prop(LABAL) > 3)
        return "say The letter you gave me told what his " +
            "plans were when he left. But I do not know " +
            "if he ever managed to fulfill them. Maybe " +
            "the future will tell.";
    if (this_player()->query_prop(LABAL) > 2)
        return "say The last I saw of him was the very last " +
            "night when he went out with Rose. The light " +
            "was shimmering in the lake and I saw them " +
            "from the tower window. Rowing in circles he was. " +
            "Rowing, rowing around the middle of the lake " +
            "as if he was looking for something. I really " +
            "wish he gave me that letter so that I knew " +
            "what happened to him.";

    if (this_player()->query_prop(LABAL) > 1)
            return "say He is gone. I cant really understand " +
                "why he left, but it has been a long time now " +
                "that he is gone. He told me to stay and " +
                "watch over things, so here I remain. Wish he " +
                "would have given me the letter he told me he " +
                "wrote before he left though.";
    if (this_player()->query_prop(LABAL) < 0)
        return "say Go to hell wretch!";
    return "say Its really none of your business, but " +
       "he isnt here at the moment and you have to " +
           "be satisfied with that.";
}

string
tell_lily()
{
    if (!(this_player()->query_prop(LABAL)))
        return "say Why do you ask stranger?";
    if (this_player()->query_prop(LABAL) > 2)
        return "say The Lily was usually the boat I used " +
            "when Master Berigon and I went out fishing, " +
            "as he always prefered Rose. After they left I " +
            "have never been out on the lake again.";
    if (this_player()->query_prop(LABAL) > 1)
        return "say What about her? As far as I know " +
            "she is tied up safe and sound in her place.";
    if (this_player()->query_prop(LABAL) < 0)
        return "say Go to hell wretch!";
    return "say Hmmm. What do I know.";
}

string
tell_ring()
{
    if (this_player()->query_prop(LABAL) < 0)
        return "say Go to hell wretch!";
    if (!(this_player()->query_prop(LABAL)))
        return "say Why do you ask stranger?";
    if (TP->test_bit("Avenir", RING_BITS))
        return "say I think you know all about my ring " +
            "already. At least I told you before about " +
            "it and there is really nothing more to know.";
    else
        return "say My ring, yes.\n" +
            "I lost it a few weeks ago and now I can not " +
            "find it, no matter how hard I look.";
}

string
tell_rose()
{
    if (!(this_player()->query_prop(LABAL)))
        return "say Why do you ask stranger?";
    if (this_player()->query_prop(LABAL) > 2)
        return "say I remember it like yesterday.... Master " +
            "Berion went out in the Rose in the middle of " +
            "the night. Yes, I saw them out there in the very " +
            "middle of the lake. Rowing in circles he did. " +
            "Rowing rowing .....\nI dont know exactly what he " +
            "was doing but after that night I havent seen " +
            "the Rose in her place again.";
    if (this_player()->query_prop(LABAL) > 1)
            return "say What about her? She is gone and I dont " +
            "know where she is.\n";
    if (this_player()->query_prop(LABAL) < 0)
        return "say Go to hell wretch!";
    return "say Hmmm. What do I know.";
}

string
tell_bull()
{
    if (!(this_player()->query_prop(LABAL)))
        return "say Why do you ask stranger?";
    if (this_player()->query_prop(LABAL) > 1)
        return "say Oh, old Ceasar. He is a mean " +
               "son of a bitch, he is. Nothing, and I mean " +
               "nothing can scare him away. The only time " +
               "I saw him on the run was when he got stung " +
               "by a swarm of killer wasps. He simply hates " +
               "even the smell of them.";
    if (this_player()->query_prop(LABAL) < 0)
        return "say Go to hell wretch!";
    return "say Hmm. I wouldnt go close to him " +
               "if I were you.";

}

public void
enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);

    if (!living(from))
        return;
    if (this_player()->query_prop(LABAL) < 0)
    {
        set_alarm(2.0, 0.0, &command("drop " +OB_NAME(obj)));
        TO->command("say Go to hell wretch!");
    }

    if(obj->id("_trout"))
    {
        if (TP->test_bit("Avenir", TROUT_BITS))
        {
            SCROLLING_LOG(TROUT_QUEST_LOG, capitalize(from->query_real_name()) +
                " gave yet another trout.");
            set_alarm(1.0, 0.0, &command("say A trout " +
                "again! Thank you for bringing " +
                "me another one."));
            set_alarm(2.0, 0.0, &obj->remove_object());
            return;
        }
        set_alarm(1.0, 0.0, &gave_trout(obj, from));
        return;
    }

    if(obj->id("_fish"))
    {
        SCROLLING_LOG(SERVANT_LOG, capitalize(from->query_real_name()) +
            " gave a fish to Labal.");
        TO->command("say A fish!! Thank you, even if I prefer trouts.");
        set_alarm(1.5, 0.0, &call_cat());
        set_alarm(2.0, 0.0, &obj->remove_object());
        return;
    }


    if(obj->id("_labals_ring"))
    {
        if (TP->test_bit("Avenir", RING_BITS))
        {
            SCROLLING_LOG(RING_QUEST_LOG, capitalize(from->query_real_name()) +
                " gave Labals ring a second time.");
            TO->command("say My ring again! Thank you for returning " +
                "it again.");
            set_alarm(2.0, 0.0, &obj->remove_object());
            return;
        }
        set_alarm(1.0, 0.0, &found_ring(obj, from));
        set_alarm(2.0, 0.0, &obj->remove_object());
        return;
    }

    if(obj->id("_berions_letter"))
    {
        if (TP->test_bit("Avenir", FARM_BITS))
        {
            set_alarm(1.0, 0.0, &command("say Oh. You " +
                "found my letter again. I must have " +
                "dropped it. Thank you for returning it."));
            set_alarm(1.5, 0.0, &command("shake " +
                from->query_real_name()));
            SCROLLING_LOG(FARM_QUEST_LOG, capitalize(TP->query_real_name()) +
               " gave the letter a second time");
            set_alarm(2.0, 0.0, &obj->remove_object());
            return;
        }

        set_alarm(1.0, 0.0, &gave_letter(obj, from));
        return;
    }

    set_alarm(1.5, 0.0, &command("say I dont want this."));
    set_alarm(2.0, 0.0, &command("drop " +OB_NAME(obj)));
    return;
}

public void
attacked_by(object attacker)
{
    ::attacked_by(attacker);
    attacker->add_prop(LABAL, -1);
    return;


}

void
gave_trout(object obj, object from)
{

    string name = from->query_real_name();
    string thing = obj->query_short();

    if (!(this_player()->query_prop(LABAL)))
    {
        this_object()->command("say I dont accept things from " +
            "strangers. Not even a trout.");
        set_alarm(1.5, 0.0, &command("drop " + thing));
        return;
    }

    if (from->query_prop(LABAL) > 0)
    {
        from->add_prop(LABAL, 3);
        set_alarm(1.0, 0.0, &command("say A trout! Thank you!\n" +
            "Was a long time ago since I tasted of them together " +
            "with Master Berion.\n"));
        set_alarm(3.0, 0.0, &command("say Hrrm. I must apologize " +
            "for being a bit ... grumpy, but this gift of yours " +
            "will change all that."));
        set_alarm(2.0, 0.0, &obj->remove_object());
        // quest name, questor, bits, exp, align, prestige
        reward_quest("Trout Quest", from, TROUT_BITS, TROUT_EXP, 0, 0);
        SCROLLING_LOG(TROUT_QUEST_LOG, capitalize(from->query_real_name()) +
            " gave a trout and was rewarded.");

        if (living(from))
            set_alarm(3.5, 0.0, &command("shake " + name));
        return;
    }
}

void
gave_letter(object obj, object from)
{

    string name = from->query_real_name();
    string thing = obj->query_short();

    set_alarm(1.0, 0.0, &command("say My letter! Where did " +
        "you find it? I have been hoping for a letter " +
        "or some kind of explanation to what happened " +
        "since the day he left."));
    if (!(obj->query_seal()))
    {
        set_alarm(0.5, 0.0, &command("say Its broken! " +
            "Someone broke the seal on the letter."));
        if (from->query_prop("_broke_labals_seal"))
        {
            set_alarm(1.0, 0.0, &command("emote notices " +
                "the blue stains on your hand from " +
                "breaking the seal on the letter."));
            set_alarm(1.5, 0.0, &command("say You swine! " +
                "You read my letter. Leave here at once " +
                "and never return again!!"));
            obj->remove_object();
            from->add_prop(LABAL, -1);
            return;
        }
    }

    // quest name, questor, bits, exp, align, prestige
    reward_quest("Farm Quest", from, FARM_BITS, FARM_EXP, 0, 10);
    SCROLLING_LOG(FARM_QUEST_LOG, capitalize(from->query_real_name()) +
    " gave the letter and was rewarded.");
    set_alarm(1.0, 0.0, &command("emote quickly browses through the " +
        "the letter."));
    set_alarm(1.5, 0.0, &command("say Thank you for bringing me my " +
        "letter. Now I can live on with the knowledge what Master " +
        "Berion did."));
    from->add_prop(LABAL, 4);
    obj->remove_object();
    if (living(from))
            set_alarm(2.5, 0.0, &command("shake " + name));
    return;
}

void
found_ring(object obj, object from)
{

    string name = from->query_real_name();
    string thing = obj->query_short();

    if (!(this_player()->query_prop(LABAL)))
    {
        this_object()->command("say I dont accept things from " +
            "strangers.");
        set_alarm(1.5, 0.0, &command("drop " + thing));
        return;
    }
    if (from->query_prop(LABAL) < 2)
        from->add_prop(LABAL, 2);
    // quest name, questor, bits, exp, align, prestige
    reward_quest("Labals Quest", from, RING_BITS, RING_EXP, 0, 10);
    SCROLLING_LOG(RING_QUEST_LOG, capitalize(from->query_real_name()) +
        " gave Labals ring and was rewarded.");
    set_alarm(1.0, 0.0, &command("say My ring! Where did " +
        "you find it? It has been lost for many years."));
    set_alarm(3.0, 0.0, &command("say Hrrm. I must apologize " +
        "for being a bit ... grumpy, but there are many " +
        "strangers sneaking around here without permission."));
    if (living(from))
        set_alarm(3.5, 0.0, &command("shake " + name));
    return;
}

int
bug_off(object obj)
{

    if (bugged)
        return 0;
    if (!(CAN_SEE(TO, obj)))
        return 0;
    bugged = 1;
    bugged_alarm = set_alarm(120.0, 0.0, &remove_bugged());
    command("say Bugg off. I do not like strangers " +
        "around here!");
    SCROLLING_LOG(SERVANT_LOG, capitalize(obj->query_real_name()) +
        " was told to bug off.");
    return 1;
}

int
remove_bugged()
{
    bugged = 0;
    return 1;
}

int
query_bugged_alarm()
{
    return bugged_alarm;
}

int
call_cat()
{
    if (!(random(5)))
    {
        tell_room(ENV(TO), QCTNAME(TO) + " throws the fish to the dung " +
            "heap. A cat appears from somewhere behind the stable " +
            "and catches the fish mid air and quickly disappears " +
            "again...\n");
        return 1;
    }
    return 0;
}
