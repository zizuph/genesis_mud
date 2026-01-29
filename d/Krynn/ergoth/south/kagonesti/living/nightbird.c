#pragma strict_types

#include "local.h"
#include "/d/Krynn/common/defs.h"
#include <ss_types.h>
#include <const.h>
#include <macros.h>
#include RND_MEET

#define HUNT_GROUP  3
#define HUNT_BIT    12
#define GIFT_GROUP  3
#define GIFT_BIT    13

inherit M_FILE
inherit "/lib/unique";

void create_krynn_monster()
{
    seteuid(getuid(this_object()));

    set_long("Time has touched the face of this wilder elf, though his racial "
        + "heritage has done much to disguise it. His composure and serene "
        + "expression reflect uncommon knowledge; this must be a chief of "
        + "the Kagonesti.\n");
    set_name("nightbird");
    set_race_name("wilder elf");
    add_name("elf");
    set_adj(({"calm", "elderly"}));
    set_gender(G_MALE);
    set_title("of the Kagonesti");
    set_appearance(80);
    set_height_desc("normal");
    set_stats(({90, 95, 90, 80, 115, 90}));
    set_skill(SS_DEFENCE,       70);
    set_skill(SS_PARRY,         50);
    set_skill(SS_WEP_POLEARM,   70);
    set_skill(SS_WEP_SWORD,     70);
    set_skill(SS_WEP_MISSILE,   70);
    set_skill(SS_AWARENESS,     70);
    set_skill(SS_UNARM_COMBAT,  50);
    set_skill(SS_BLIND_COMBAT,  40);
    set_skill(SS_2H_COMBAT,     50);
    set_skill(SS_LOC_SENSE,     80);
    set_skill(SS_HIDE,          50);
    set_skill(SS_SNEAK,         50);
    set_skill(SS_TRACKING,      80);
    add_prop(LIVE_I_SEE_DARK, 1);
    set_default_answer("shrug unknowingly", 1);
    add_ask(({"task", "help", "quest", "aid"}), "@@get_task@@");
    add_ask(({"carcass", "corpse"}), "@@ask_carcass@@");
    add_ask("prey", "@@ask_prey@@");
}

string ask_carcass()
{
    if(this_player()->query_prop(PLAYER_I_GOT_NIGHTBIRD_HUNT))
        this_object()->command("rsay Yes. Once you've slain your prey, bring "
            + "me its remains.");
    else
        this_object()->command("rsay How are our carcasses any of your "
            + "concern?");
    return "";
}

string ask_prey()
{
    if(this_player()->query_prop(PLAYER_I_GOT_NIGHTBIRD_HUNT))
        this_object()->command("rsay Yes, you must slay an animal that we "
            + "hunt from this forest. As I have said, it will not be easy. "
            + "Anything slow or large does not last long when our hunters "
            + "are near.");
    else if(this_player()->test_bit("krynn", HUNT_GROUP, HUNT_BIT))
        this_object()->command("rsay Yes, you have seen how difficult "
            + "hunting can become once the Kagonesti arrive.");
    else
    {
        this_object()->command("chuckle . ");
        this_object()->command("rsay You would be hard-pressed to find "
            + "much to hunt in these woods, but feel free to try.");
    }
    return "";
}

void converse_command(string cmd, object to)
{
    if(present(to, environment(this_object())))
        this_object()->command(cmd);
}

string get_task()
{
    if(this_player()->query_prop(PLAYER_I_FAILED_NIGHTBIRD_QUEST))
    {
        this_object()->command("rsay You have already failed me.");
    }
    else if(this_player()->query_prop(PLAYER_I_GOT_NIGHTBIRD_HUNT))
    {
        this_object()->command("rsay I have already asked you to bring me "
            + "a carcass of prey from this forest.");
    }
    else if(!this_player()->test_bit("krynn", HUNT_GROUP, HUNT_BIT))
    {
        object ob;

        this_object()->command("hmm");
        set_alarm(2.0, 0.0,
            &converse_command("rsay You are offering aid?", this_player()));
        set_alarm(4.0, 0.0, &converse_command("rsay What reasons do you have "
            +"for helping us, " + this_player()->query_race_name() + "?",
            this_player()));
        set_alarm(8.0, 0.0, &converse_command("rsay No, I cannot give you "
            + "important tasks if I do not know that I can trust you.",
            this_player()));
        set_alarm(11.0, 0.0,
            &converse_command("emote appears deep in thought.",
            this_player()));
        set_alarm(15.0, 0.0, &converse_command("emote nods to himself.",
            this_player()));
        set_alarm(18.0, 0.0, &converse_command("rsay Yes, you will have to "
            + "prove your worth first.", this_player()));
        set_alarm(23.0, 0.0, &converse_command("rsay We have spent many days "
            + "stalking in this forest. The prey that remains would be "
            + "elusive for any outsider.", this_player()));
        set_alarm(27.0, 0.0, &converse_command("rsay Bring me the carcass of "
            + "prey from this forest and I will know your offer is not mere "
            + "words.", this_player()));
        this_player()->add_prop(PLAYER_I_GOT_NIGHTBIRD_HUNT, 1);
        
        if(ob = clone_unique(LIVING + "hare", 1, 0, 0, 100))
            ob->move(GET_RANDOM_ROOM(FOREST), 1);
    }
    else if(this_player()->query_prop(PLAYER_I_GOT_NIGHTBIRD_GIFT))
    {
        this_object()->command("rsay I've already asked you to find me a gift "
            + "of great value.");
    }
    else if(!this_player()->test_bit("krynn", GIFT_GROUP, GIFT_BIT))
    {
        set_alarm(1.0, 0.0, &converse_command("rsay Yes, I could use you for"
            + " something.", this_player()));
        set_alarm(4.0, 0.0, &converse_command("rsay I will be meeting with a "
            + "chief from another village soon. I'd like to surprise him with"
            + " a gift.", this_player()));
        set_alarm(7.0, 0.0, &converse_command("rsay However, I have only a few"
            + " things in my possession that would impress him, and of those, "
            + "none I wish to lose.", this_player()));
       set_alarm(11.0, 0.0, &converse_command("rsay Find me something of great"
            + " worth that I can present to him. Make sure it is of natural "
            + "value, not enchanted or magical.", this_player()));
       this_player()->add_prop(PLAYER_I_GOT_NIGHTBIRD_GIFT, time());
    }
    else
    {
        set_alarm(1.0, 0.0, &converse_command("rsay I would let you perform a "
            + "task for me if only I had one to give.", this_player()));
    }
    return "";
}        
    
public string query_presentation()
{
    return "Chief " + ::query_presentation();
}

void add_introduced(string who)
{
    ::add_introduced(who);

    set_alarm(1.0, 0.0, &converse_command("introduce me", who));
}

void give_object(object ob, object to)
{
    if(ob->query_prop(HEAP_I_IS) && 1 != ob->num_heap())
        this_object()->command("give " + ob->plural_short() + " to "
            + OB_NAME(to));
    else
    {
        this_object()->command("give " + OB_NAME(ob) + " to " + OB_NAME(to));
        if(environment(ob) == this_object())
            this_object()->command("drop " + OB_NAME(ob));
    }
}

void demolish(object ob)
{
    ob->remove_object();
}

void enter_inv(object ob, object from)
{
    ob->set_no_merge(1);
    ::enter_inv(ob, from);
    
    if(from->query_prop(PLAYER_I_GOT_NIGHTBIRD_HUNT)
        && !from->test_bit("krynn", HUNT_GROUP, HUNT_BIT))
    {
        if(ob->id(QUEST_ITEM_HARE_CORPSE))
        {
            string *killer = ob->query_prop(CORPSE_AS_KILLER);
            if(!killer)
            {
                set_alarm(1.0, 0.0, &converse_command("hmm", from));
                set_alarm(5.0, 0.0,
                    &converse_command("rsay Someone has tampered with this "
                        + "carcass. You will not gain my trust with tricks.",
                    from));
                set_alarm(5.5, 0.0, &give_object(ob, from));
                from->remove_prop(PLAYER_I_GOT_NIGHTBIRD_HUNT);
                from->add_prop(PLAYER_I_FAILED_NIGHTBIRD_QUEST, 1);
            }
            else if(killer[0] == from->query_real_name())
            {
                if(from->query_prop(PLAYER_I_KILLED_NIGHTBIRD_HARE))
                {
                    set_alarm(1.0, 0.0,
                        &converse_command("emote nods in approval.",
                        from));
                    set_alarm(5.0, 0.0,
                        &converse_command("rsay I do not think this was easy "
                            + "to catch. I now see that that was some truth "
                            + "in your offer.",
                            from));
                    set_alarm(9.0, 0.0,
                        &tell_object(from, "You feel more experienced!\n"));
                    from->remove_prop(PLAYER_I_GOT_NIGHTBIRD_HUNT);
                    from->set_bit(HUNT_GROUP, HUNT_BIT);
                    from->add_exp_quest(5000);
                    K_QUEST_LOG("quest", "Nightbird Hunt", from, 5000);
                    set_alarm(1.5, 0.0, &demolish(ob));
                }
                else
                {
                    set_alarm(1.0, 0.0, &converse_command("rsay You may have "
                        + "killed this, but not after I asked you to.", from));
                    set_alarm(1.5, 0.0, &give_object(ob, from));
                }
            }
            else
            {
                set_alarm(1.0, 0.0, &converse_command("frown", from));
                set_alarm(4.0, 0.0, &converse_command("rsay You are foolish "
                    + "to think we were not watching. You did not kill this "
                    + "yourself and you will not get another chance any time "
                    + "soon.", from));
                set_alarm(4.5, 0.0, &give_object(ob, from));
                from->remove_prop(PLAYER_I_GOT_NIGHTBIRD_HUNT);
                from->add_prop(PLAYER_I_FAILED_NIGHTBIRD_QUEST, 1);
            }
        }
        else if(ob->query_prop(CORPSE_S_RACE))
        {
            set_alarm(1.0, 0.0,
                &converse_command("rsay This is not prey from this forest.",
                    from));
            set_alarm(1.5, 0.0, &give_object(ob, from));
        }
        else
        {
            set_alarm(1.0, 0.0,
                &converse_command("rsay This isn't what I asked for.", from));
            set_alarm(1.5, 0.0, &give_object(ob, from));
        }
    }
    else if(from->query_prop(PLAYER_I_GOT_NIGHTBIRD_GIFT)
        && !from->test_bit("krynn", GIFT_GROUP, GIFT_BIT))
    {
        int value;
        
        if(!CAN_SEE(this_object(), ob) || !CAN_SEE_IN_ROOM(this_object()))
        {
            set_alarm(1.0, 0.0, &converse_command("rsay Hmm. I cannot see "
                + "this thing you've given me.", from));
            set_alarm(1.5, 0.0, &give_object(ob, from));
        }
        else if(ob->query_prop(HEAP_I_IS) && ob->num_heap() != 1)
        {
            set_alarm(1.0, 0.0, &converse_command("rsay I want just one gift.",
                from));
            set_alarm(1.5, 0.0, &give_object(ob, from));
        }
        else if((value = ob->query_prop(OBJ_I_VALUE)) >= 10000)
        {
            set_alarm(1.0, 0.0, &converse_command("rsay Yes, this seems to be "
                + "worth quite a bit.", from));
            set_alarm(3.0, 0.0, &tell_room(environment(this_object()),
                QCTNAME(this_object()) + " inspects the " + ob->query_short()
                + " closely.\n"));

            if(ob->query_prop(MAGIC_AM_MAGIC) ||
                ob->query_prop(MAGIC_I_ILLUSION) ||
                ob->query_prop(OBJ_I_IS_MAGIC_ARMOUR) ||
                ob->query_prop(OBJ_I_IS_MAGIC_WEAPON))
            {
                set_alarm(7.0, 0.0, &converse_command("frown .", from));
                set_alarm(9.0, 0.0, &converse_command("rsay I said it had to "
                    + "be of natural worth. This is magical.", from));
                set_alarm(9.5, 0.0, &give_object(ob, from));
            }
            else if(ob->query_prop(OBJ_I_ALIGN) < 0)
            {
                set_alarm(7.0, 0.0, &converse_command("shake", from));
                set_alarm(9.0, 0.0, &converse_command("rsay No, I can sense "
                    + "darkness in this. I cannot use this as a gift.",
                    from));
                set_alarm(9.5, 0.0, &give_object(ob, from));
            }
            else if(ob->query_prop(OBJ_I_WEIGHT) >= 25000)
            {
                set_alarm(7.0, 0.0, &converse_command("groan weakly", from));
                set_alarm(9.0, 0.0, &converse_command("rsay I'm afraid this "
                    + "is just too heavy. I could not take it with me.",
                    from));
                set_alarm(9.5, 0.0, &give_object(ob, from));
            }
            else if(ob->query_prop(OBJ_I_VOLUME) >= 25000)
            {
                set_alarm(7.0, 0.0, &converse_command("sigh .", from));
                set_alarm(9.0, 0.0, &converse_command("rsay However, this "
                    + "is much too large for me to be carrying around. You "
                    + "will need to find me something smaller.",
                    from));
                set_alarm(9.5, 0.0, &give_object(ob, from));
            }
            else
            {
                int xp = 2000;
                
                set_alarm(7.0, 0.0, &converse_command("rsay I think this will "
                    + "do nicely. Thank you for your help!", from));
                set_alarm(10.0, 0.0,
                    &tell_object(from, "You feel more experienced!\n"));
                from->set_bit(GIFT_GROUP, GIFT_BIT);

                // Up to 1000 additional XP, depending on value 
                if(value >= 20000)
                    xp += 1000;
                else
                    xp += (value - 10000) / 10;
                    
                from->add_xp_quest(xp);
                K_QUEST_LOG("quest", "Nightbird Gift", from, xp);
                K_QUEST_LOG("gift", file_name(ob), from,
                    time() - from->query_prop(PLAYER_I_GOT_NIGHTBIRD_GIFT));
                from->remove_prop(PLAYER_I_GOT_NIGHTBIRD_GIFT);
                set_alarm(1.0, 0.0, &demolish(ob));
            }
        }
        else
        {
            set_alarm(1.0, 0.0, &converse_command("rsay I do not consider "
                + "this to be of great enough value. I do not think the "
                + "chief would be that impressed either.", from));
            set_alarm(1.5, 0.0, &give_object(ob, from));
        }
    }
    else
    {
        set_alarm(1.0, 0.0,
            &converse_command("rsay Why are you giving me this?", from));
        set_alarm(1.5, 0.0, &give_object(ob, from));
    }
}

