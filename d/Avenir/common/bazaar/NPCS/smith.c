// Bazaar Smith (/d/Avenir/common/bazaar/NPCS/smith.c)
// creator(s):   Lilith, Mar 98
// last update:
//               Lilith, Spet 2014: Mudlib update to ask made this guy buggy. Fixed.
// purpose:      cloned to /bazaar/intr/armr.c
// note:         quest npc for the falchion quest
/*
 * Revisions:
 * 	Lucius, Aug 2017: Fixups for union/defs.h changes.
 *   Cotillion, Jan 2019: Fixed coal removal
 */
#pragma strict_types

inherit "/d/Avenir/inherit/quest";
inherit "/d/Avenir/common/bazaar/NPCS/call_for_help";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Avenir/union/defs.h"
#include "/d/Avenir/include/macros.h"

#define F_EXP		1500
#define FALCHION_BITS	0, 19
#define F_QUEST_LOG	"/d/Avenir/log/quest/falchion_quest"

string what_me();

void
create_monster()
{
    set_name("blacksmith");
    set_short("dwarven blacksmith");
    set_race_name("dwarf");
    add_name(({"smith", "sybarite", "faithful"}));
    add_adj(({"dwarven", "blacksmith"}));
    set_long("Shrouded in shadow, all that you can make out clearly " +
        "are the muscles bulging upon his forearms as he pounds " +
	"his hammer against the anvil, and the sheen of sweat upon " +
        "his skin.\n");

    default_config_npc(200);
    set_all_attack_unarmed(25, 10);
    set_all_hitloc_unarmed(20);
    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    add_prop(NPC_I_NO_LOOKS, 1);

    set_act_time(10);
    add_act("emote retrieves some glowing-red metal from the firepit.");
    add_act("emote swings his hammer methodically against the anvil.");
    add_act("emote folds a thin sheet of steel and hammers it thin again.");
    add_act("emote wipes the sweat pouring from his forehead.");
    add_act("emote examines his work and smiles with satisfaction.");
    add_act("emote grips something with his tongs and puts it in the "+
        "firepit.");
    add_act("emote gestures to his apprentice, who pumps the bellows "+
        "harder.");
    add_act("emote mumbles something about needing more coal for the fire.");

    set_cact_time(5);
    add_cact("say With my dying breath I shall call for the guards, and "+
        "my dead eyes shall feast with delight upon your misery at "+
        "the pillory. This do I vow!");

    set_default_answer(VBFC_ME("what_me"));
    add_ask(({"[do] [you] [have] / [need] [a] 'task'/ 'job' / 'quest' / 'help' [for] [me]"}),
		VBFC_ME("quest_ask"));
    add_ask(({"[about] 'falchion' / 'falchions'"}), VBFC_ME("falchion_ask"));
    add_ask(({"'runed' 'falchion' / 'falchions'"}), VBFC_ME("runed_ask"));
    add_ask(({"[about] [the] 'pool' [of] [silver]"}), VBFC_ME("pool_ask"));
    add_ask(({"material", "artifact"}), VBFC_ME("mat_ask"));
    add_ask(({"[about] [the] [goddess] 'aclolthayr'"}), VBFC_ME("aclo_ask"));
    add_ask(({"[do] [you] [need] 'coal' [for] [the] / [your] [fire]"}),
        "say I could use a few more pieces of coal from the Utterdark. "+
		"Most people mine for it, which is time-intensive hard work.", 1);
	add_ask(({"[how] [do] [you] 'mine' [for] 'coal' [in] [the] [utterdark] / [underdark]"}),
		"say I usually find a good spot and then do mine here with pick "+
		"or similar tool. If there is coal, I find it.", 1);
    add_ask(({"ingot", "akrams dagger", "hephamenios", "coal sack"}), VBFC_ME("ukku_ask"));
	add_ask(({"[ingot] [of] 'ukku' [steel]"}), VBFC_ME("ukku_ask"));
	add_ask(({"'sack' [of] 'coal'"}), VBFC_ME("ukku_ask"));
	add_ask(({"west", "armoury", "armory", "armorer"}),
			"say You have to earn access to the armoury.",1);

    setuid();
    seteuid(getuid());

}

string
quest_ask()
{
    if (TP->test_bit("Avenir", FALCHION_BITS))
    {
        command("say I can always use more coal for the fire.\n");
        return "";
    }

    command("frown");
    command("whisper "+ TP->query_real_name() +" My days and nights "+
        " are haunted by the goddess Aclolthayr.");
    command("whisper "+ TP->query_real_name() +" She wants me to make"+
        "...an artifact...for her, but none of my previous attempts have "+
        "been satisfactory.");
    command("shudder");
    command("whisper "+ TP->query_real_name() +" I think it is because "+
        "I haven't found the material She wants me to make it with...");
    command("whisper "+ TP->query_real_name() +" If you would help me "+
        "find what I need, I would be very grateful.");
    SCROLLING_LOG(F_QUEST_LOG, capitalize(TP->query_real_name()) +
	" asked Smith for a quest.");
    return "";
}

string
falchion_ask()
{
    command("say A good weapon, the traditional sword for Hunters.");
    command("say I've heard some of them are runed, and made with "+
        "enchanted steel.");
    command("shrug .");
    SCROLLING_LOG(F_QUEST_LOG, capitalize(TP->query_real_name()) +
        " asked Smith about the falchion.");
    return "";
}

string
aclo_ask()
{
    command("shiver");
    command("whisper "+ TP->query_real_name() +" She is the Patron "+
        "of the Hunt, a great and terrible Spider Goddess. There is "+
        "something she wants of me, but I do not know how to do as "+
        "She Wills me to.");
    command("whisper "+ TP->query_real_name() +" I think though ...I "+
        "think that what she wants somehow involves those runed "+
        "falchions.");
    SCROLLING_LOG(F_QUEST_LOG, capitalize(TP->query_real_name()) +
        " asked Smith about Aclolthayr.");
    return "";
}

string
runed_ask()
{
    command("whisper "+ TP->query_real_name() +" They are very rare, "+
        "made only with the blessing of Aclolthayr.");
    command("whisper "+ TP->query_real_name() +" She has been visiting "+
        "me in my dreams...I see Her with a runed falchion dripping "+
        "blood, astride a pool of silver.");
    SCROLLING_LOG(F_QUEST_LOG, capitalize(TP->query_real_name()) +
        " asked Smith about Runed falchions.");
    return "";
}

string
mat_ask()
{
    command("whisper "+ TP->query_real_name() +" I think that I am "+
        "supposed to make the artifact with the same material that "+
        "the runed falchions are made from.");
    command("say But I don't know what it is, nor where it came from.");
    command("emote sighs despairingly.");
    return "";
}

string
pool_ask()
{
    command("whisper "+ TP->query_real_name() +" It gleams silver-"+
	"bright in my dreams, reflecting the underbelly of a spider.");
    SCROLLING_LOG(F_QUEST_LOG, capitalize(TP->query_real_name()) +
        " asked Smith about Pool of silver.");
    return "";
}

string
ukku_ask()
{
    object sack;
    if (IS_TORNU(TP))
    {
        seteuid(getuid(TO));
        command("say Ahhh....");
        command("say Heph sent you, hmm?");
        command("say I can get you what you need, but I want "+
            "something in return.");
        command("say I am low on coal and without it, I'm out of "+
            "business.");
        command("say Give this sack back to me filled with coal, "+
            "and you'll have your ukku.");
        sack = clone_object("/d/Avenir/union/obj/coal_sack");
        sack->move(TO);
        command("give sack to "+ TP->query_real_name());
        return "";
    }
    command("frown fierce");
    command("say Such is forbidden to you. I would not ask again.");
    return "";
}
string
what_me()
{
    command("emote ignores you and swings his hammer with renewed vigor.");
    return "";
}

void
remove_it(object ob)
{
    if (ob->id("_aclolthayrs_gift_for_smith"))
        ob->remove_object();
}

int
give_back(object obj, object from)
{
    if (!from)
    {
        set_alarm(1.0, 0.0, &obj->remove_object());
        return 0;
    }
    command("say to "+ from->query_name() +" This isn't what I wanted "+
        "from you!");
    command("drop "+ obj->query_name());
    return 1;
}
void
done_quest(object ob, object from)
{
    object metal, token;
    string str;

    if (from->test_bit("Avenir", FALCHION_BITS))
    {
        command("thank "+ from->query_real_name());
        command("say I can always use another one of these.");
        SCROLLING_LOG(F_QUEST_LOG, capitalize(from->query_real_name()) +
            " gave Smith the metal -again-.");
        set_alarm(30.0, 0.0, &remove_it(ob));
        return;
    }

    if (from->query_prop("_on_falchion_quest"))
    {
        command("say What is this?");
        command("brighten");
        command("say This just may be what I need to fulfill the Will "+
            "of Aclolthayr!");
        command("thank "+ from->query_real_name());
        command("whisper "+ from->query_real_name()+ " I grant you "+
            "access to the Custom Armourer just west of here.");
        SCROLLING_LOG(F_QUEST_LOG, capitalize(from->query_real_name()) +
            " gave Smith the metal and was rewarded.");
        from->remove_prop("_on_falchion_quest");
                /* quest name, questor, bits, exp, alignment, prestige */
        reward_quest("Falchion Quest", from, FALCHION_BITS, F_EXP, 0, 10);
        set_alarm(30.0, 0.0, &remove_it(ob));

        /* Lets give a syb coin in appreciation */
        token = clone_object("/d/Avenir/common/obj/syb_coin");
        token->move(from);
        str = token->short();
        from->catch_msg(QCTNAME(TO) + " digs into a pocket and "+
            "gives you " + str + ".\n");
        tell_room(ENV(TO), QCTNAME(TO) + " digs into his pocket "+
            "and gives "+ str +" to " + QTNAME(from) + ".\n", ({ from }));
        return;
    }
    else
        give_back(ob, from);
    return;

}

/* Coal must be mined in the Utterdark.
 * It takes time, etc, so lets give a
 * little general exp.
 */
void
do_ukku(object ob, object from)
{
    object ingot;
    if (IS_TORNU(from))
    {
        if (ob->test_it() < 1)
        {
            command("say I said it should be full.");
            command("say If you want your ukku, you'll bring it back, full.");
            set_alarm(4.0, 0.0, &give_back(ob, from));
            return;
        }
        else
        {
            command("say Very good. The armourers and I will truly benefit "+
                "from this.");
            command("say Here is your ukku. Give my regards to Hephamenios.");
            ingot = clone_object("/d/Avenir/union/obj/ukku");
            ingot->move(TO);
            command("give ukku to "+ from->query_real_name());
            from->add_exp_general(100 + random(50));
            from->catch_msg("You feel a bit more experienced in general.\n");
            set_alarm(30.0, 0.0, &remove_it(ob));
            return;
        }
    }
    else
        set_alarm(4.0, 0.0, &give_back(ob, from));
    return;
}

void
do_coal(object obj, object from)
{
    command("say Good, good. I was getting low.");
    /* Lets give some general exp for doing the task */
    from->add_exp_general(100 + random(50));
    from->catch_tell("You feel a bit more experienced in general.\n");
    /* Lets give a syb coin in appreciation */
    if (!(random(10)))
    {
        clone_object("/d/Avenir/common/obj/syb_coin");
        command("give sybarun coin to "+ from->query_real_name());
    }

    obj->remove_object();
}

public void
enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);

    if (!living(from))
        return;
    if(obj->id("_Aclolthayrs_gift_for_smith"))
    {
        set_alarm(1.0, 0.0, &done_quest(obj, from));
        return;
    }
    if(obj->id("coal"))
    {
        set_alarm(1.0, 0.0, &do_coal(obj, from));
        return;
    }
    if(obj->id("_smith_coal_sack"))
    {
        set_alarm(1.0, 0.0, &do_ukku(obj, from));
        return;
    }
    set_alarm(4.0, 0.0, &give_back(obj, from));
    return;
}
