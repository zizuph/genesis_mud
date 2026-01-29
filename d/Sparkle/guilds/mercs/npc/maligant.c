/*
 * Maligant, guild leader and trainer of the Mercenaries Guild
 * 	by Morrigan, 11/2001
 *
 * Updated 10/2002 to add bribe functionality by Morrigan
 *
 * Adapted from code by Auberon and Gwyneth
 * Updated for Sparkle by Lunatari 2006
 */
#include "../merc.h"

inherit MERC_KRYNN_NPC
inherit MERC_KRYNN_BRIBE 

#include "attackers.h"
#include "members.h"

#define MALIGANT_I_BRIBE_AMOUNT "_maligant_i_bribe_amount"
#define REMOVE_NOT_ALLOWED 100
#define REMOVE_WARNED 200
#define GET_TO_JOIN 50
#define REDUCE_LEAVE_PENALTY 500
#define NO_LEAVE_PENALTY 1000

public
string give_bribe_info()
{
    int amount;

    if (TP->query_prop(MALIGANT_I_BRIBE_AMOUNT))
    {
        if ((amount = TP->query_prop(MALIGANT_I_BRIBE_AMOUNT)) == 0)
	    return "Just keep throwing away your money, that's fine with me.";

        if (amount == -1)
            return "I've already settled up with you, I'm done doing business "+
	        "for now. Feel free to continue giving me coins, though.";

        if (gBribe_money[lower_case(TP->query_name())] < amount ||
	    amount != GET_TO_JOIN)
            return "I named a price of "+amount+" platinum coins, and "+
	        "I'm sticking to it.";
    }

    if (MJOIN->query_not_allowed(TP->query_name()) && !IS_MERC(TP))
    {
        TP->add_prop(MALIGANT_I_BRIBE_AMOUNT, REMOVE_NOT_ALLOWED);
        return "Looks like you've made yourself a nuisance around "+
	    "here, and now maybe you're wishing you could join us? "+
	    "I suppose I could overlook your past deeds for, say... "+
	    REMOVE_NOT_ALLOWED+" platinum coins?";
    }

    if (MJOIN->query_warned(TP->query_name()) && IS_MERC(TP))
    {
        TP->add_prop(MALIGANT_I_BRIBE_AMOUNT, REMOVE_WARNED);
	return "Ahh, so you're the murderin' bastard that I've "+
	    "been hearing about. I ought to smash you here and now "+
	    "for betraying my generous hospitality. Maybe "+
 	    REMOVE_WARNED+" platinum coins would begin to atone for "+
	    "your stupidity.";
    }

    if (!IS_MERC(TP) && TP->query_average_stat() < 64)
    {
        TP->add_prop(MALIGANT_I_BRIBE_AMOUNT, GET_TO_JOIN);
        return "Hmph. Maybe you are feeling a bit big for your britches? "+
	    "I don't usually let "+TP->query_exp_title()+"s in, but I'll "+
	    "make an exception for about "+GET_TO_JOIN+" platinum coins.";
    }

    if (IS_MERC(TP))
    {
        TP->add_prop(MALIGANT_I_BRIBE_AMOUNT, REDUCE_LEAVE_PENALTY);
        return "You aren't thinkin' of leavin' are ya? Gnimpsh will "+
	    "tear his hair out! Maybe you're scared from all the rumours "+
	    "you hear about me handing out beatings to those who take off "+
	    "too early in their career, and cause me to have wasted my "+
	    "valuable time? I'll have 'em go easy on ya for, say... "+
	    REDUCE_LEAVE_PENALTY+" platinum coins.";
    }

    TP->add_prop(MALIGANT_I_BRIBE_AMOUNT, 0);
    return "I don't mind takin' yer money, so feel free to keep handing "+
	"it over, but I don't think there's much I can do for ya at the "+
	"moment.";
}
    
string bribe_get_to_join()
{
    int amount;

    if ((amount = TP->query_prop(MALIGANT_I_BRIBE_AMOUNT)) == 0)
	    return give_bribe_info();

    if (amount == -1)
        return "I've already settled up with you, I'm done doing business "+
	    "for now. Feel free to continue giving me coins, though.";

    if (gBribe_money[lower_case(TP->query_name())] < amount ||
	amount != GET_TO_JOIN)
        return "I named a price of "+amount+" platinum coins, and "+
	    "I'm sticking to it.";

    TP->add_prop(MALIGANT_I_BRIBE_AMOUNT, -1);
    TP->add_prop(MALIGANT_JOIN_PERMISSION, 1);
 
    gBribe_money = m_delete(gBribe_money, lower_case(TP->query_name()));
    write_file(MERC_BRIBE_LOG, extract(ctime(time()), 4, 15) + " maligant: " +
        TP->query_name() + " bribed to get to join the guild early\n");

     return "All right then. I hope you're not biting off more than you "+
	"can chew. I'll make an exception this one time, but don't dilly "+
	"dally, I might change my mind.";
}

string bribe_remove_not_allowed()
{
    int amount;

    if ((amount = TP->query_prop(MALIGANT_I_BRIBE_AMOUNT)) == 0)
	    return give_bribe_info();

    if (amount == -1)
        return "I've already settled up with you, I'm done doing business "+
	    "for now. Feel free to continue giving me coins, though.";

    if (gBribe_money[lower_case(TP->query_name())] < amount ||
	amount != REMOVE_NOT_ALLOWED)
        return bribe_get_to_join();
    /*
        return "I named a price of "+amount+" platinum coins, and "+
	    "I'm sticking to it.";
    */
    TP->add_prop(MALIGANT_I_BRIBE_AMOUNT, -1);
    MJOIN->remove_not_allowed(TP->query_name());
    gBribe_money = m_delete(gBribe_money, lower_case(TP->query_name()));

    write_file(MERC_BRIBE_LOG, extract(ctime(time()), 4, 15) + " maligant: " +
        TP->query_name() + " bribed to get off the banished list\n");

    return "All right then. I suppose I can forgive your deeds this one "+
	"time. I'll have Gnimpsh take you off the banished list.";
}

string bribe_remove_warned()
{
    int amount;

    if ((amount = TP->query_prop(MALIGANT_I_BRIBE_AMOUNT)) == 0)
	    return give_bribe_info();

    if (amount == -1)
        return "I've already settled up with you, I'm done doing business "+
	    "for now. Feel free to continue giving me coins, though.";

    if (gBribe_money[lower_case(TP->query_name())] < amount ||
	amount != REMOVE_WARNED)
        return bribe_remove_not_allowed();

    /*
        return "I named a price of "+amount+" platinum coins, and "+
	    "I'm sticking to it.";
    */

    TP->add_prop(MALIGANT_I_BRIBE_AMOUNT, -1);
    MJOIN->remove_warned(TP->query_name());
    gBribe_money = m_delete(gBribe_money, lower_case(TP->query_name()));

    write_file(MERC_BRIBE_LOG, extract(ctime(time()), 4, 15) + " maligant: " +
        TP->query_name() + " bribed to get to off the warned list\n");

    return "That's probably the best investment you've ever made, "+
        TP->query_name()+". I usually have no mercy on murdering in my "+
	"camp. I'll pardon you, but I'll be keeping a close eye on you.";
}

string bribe_reduce_leave_penalty()
{
    int amount;

    if ((amount = TP->query_prop(MALIGANT_I_BRIBE_AMOUNT)) == 0)
	    return give_bribe_info();

    if (amount == -1)
        return "I've already settled up with you, I'm done doing business "+
	    "for now. Feel free to continue giving me coins, though.";

    if (gBribe_money[lower_case(TP->query_name())] < amount ||
	amount != REDUCE_LEAVE_PENALTY)
        return bribe_remove_warned();
    /*
        return "I named a price of "+amount+" platinum coins, and "+
	    "I'm sticking to it.";
    */

    TP->add_prop(MALIGANT_I_BRIBE_AMOUNT, NO_LEAVE_PENALTY);
    TP->add_prop(MALIGANT_REDUCED_LEAVE_PENALTY, 1);

    write_file(MERC_BRIBE_LOG, extract(ctime(time()), 4, 15) + " maligant: " +
        TP->query_name() + " bribed for a reduced leaving penalty\n");

    return "If you're insistent on leavin', I'm not gonna stop ya. Since "+
	"you've been so kind in giving me all these coins, I'll have the "+
	"guards go easy on ya when you leave. Heck, for another 500 of 'em "+
	"I might even let you off unharmed.";
}

string bribe_no_leave_penalty()
{
    int amount;

    if ((amount = TP->query_prop(MALIGANT_I_BRIBE_AMOUNT)) == 0)
	    return give_bribe_info();

    if (amount == -1)
        return "I've already settled up with you, I'm done doing business "+
	    "for now. Feel free to continue giving me coins, though.";

    if (gBribe_money[lower_case(TP->query_name())] < amount ||
	amount != NO_LEAVE_PENALTY)
        return bribe_reduce_leave_penalty();
    /*
        return "I named a price of "+amount+" platinum coins, and "+
	    "I'm sticking to it.";
    */
    TP->add_prop(MALIGANT_I_BRIBE_AMOUNT, -1);
    TP->add_prop(MALIGANT_REMOVED_LEAVE_PENALTY, 1);
    gBribe_money = m_delete(gBribe_money, lower_case(TP->query_name()));

    write_file(MERC_BRIBE_LOG, extract(ctime(time()), 4, 15) + " maligant: " +
        TP->query_name() + " bribed for NO leaving penalty\n");

    return "You really are scared of a beating, aren't you "+TP->query_name()+
	"? I never would have figured you for such a coward. But anyway, "+
	"now that my pocket is filled with a thousand of yer hard earned coins "+
	"I suppose I can forget that I've wasted my time on you and let you "+
	"off unharmed. It was a pleasure doing business with ya! Oh, you "+
	"better take advantage of this pretty quickly, I've been known to "+
	"change my mind from time to time.";
}

void
create_krynn_monster()
{
    set_name("maligant");
    add_name("trainer");
    add_name("leader");
    set_title("the Mercenary Lord, Leader of Maligant's Mercenaries");
    set_race_name("dwarf");
    set_long("Very proud and confident, this dwarf regards those around "+
	"him with the wisdom of age. His beard is long and majestic, "+
	"flowing down to his broad waist. You cannot help but notice his "+
	"thick arms and strong hands.\n");
    set_adj(({"broad-shouldered", "stoic"}));

    set_stats(({ 180, 135, 190, 120, 135, 170 }));
    set_skill(SS_WEP_CLUB, 100);
    set_skill(SS_AWARENESS,   60);
    set_skill(SS_DEFENCE,     100);
    set_skill(SS_PARRY,       100);
    set_skill(SS_APPR_MON,    50);
    set_alignment(0);
    add_prop(OBJ_M_NO_ATTACK, "Are you out of your mind? Attacking him "+
	"in the middle of his own camp? You would be slaughtered for sure!\n");
    add_prop(OBJ_M_NO_MAGIC_ATTACK, "Are you out of your mind? Attacking him "+
	"in the middle of his own camp? You would be slaughtered for sure!\n");
    add_ask(({"orcs", "goblins", "hobgoblins", "goblin", "goblin", "orc",
	"hobgoblin" }), "say It's a sacrifice having to "+
	"to put up with miserable goblin-kind, but it's worth the money."+
        " As much as I dislike most stinking goblins, Dalizen "+
	"sure enough dislikes them more!", 1);
    add_ask(({ "specialize", "specialization", "choose", "choosing" }),
	"say Once you've completed your basic training, you can choose to "+
	"specialize in either swords or club here. I can train you to be "+
	"a master of the club, while Dalizen trains the swordsmen to be "+
	"skilled veterans with their blades.", 1);
    add_ask(({"sword", "swords" }), "say It's just a big pointy stick! "+
	"Given the choice, I'll take a club over a steel toothpick any day.", 1);
    add_ask(({"club", "clubs" }), "say My weapon of choice! Nothing beats "+
	"a good strong club.", 1);
    add_ask(({"train", "training", "skills", "skill" }), "say I let "+
	"Dalizen handle most of the training. I only train the skilled to "+
	"be masters of clubs.", 1);
    add_ask(({ "hobbit", "hobbits", "halfling", "halflings", "kender" }),
	"say Oh it's a funny story! I won a little wager with Dalizen, and "+
	"now he has to train all the halfling folk! So you won't see many "+
	"of them with clubs around here. They're too weak to smash anything "+
	"anyway.", 1);
    add_ask(({ "mercenary", "mercenaries" }), "say Well, it "+
	"should be obvious what a mercenary is, but I'll tell ya anyway. A "+
	"mercenary is someone who's decided to live life for their own causes, "+
	"whatever that may be. If you want to be one of my mercenaries, ask "+
	"me about joining the guild. If you're here to hire a mercenary, go "+
	"see Gnimpsh.", 1);
    add_ask(({ "hire", "mercenaries for hire", "hire mercenary" }), 
	"say Go ask Gnimpsh about Mercenaries for hire, he'll "+
	"know who's available.", 1);
    add_ask(({ "join", "joining", "guild", "joining the guild" }), 
	"say We accept all sorts here, but we don't promise them equal "+
	"treatment. In fact, we don't promise them anything. I am the law "+
	"around here, and if you don't like that, you'd best look elsewhere. "+
	"Ask me about our rules, before you go jumping into something you "+
	"don't yet understand. If you think you want to be a mercenary, just "+
	"request my permission to join.", 1);
    add_ask(({ "law", "rule", "rules" }), "say There are only a few rules. "+
	"If someone is here, assume that I want them here, and don't kill them "+
	"or I might kill you. Also, don't come bitching to me with any "+
	"complaints, "+
	"I tell folk plainly what to expect from the get-go. If they still make a "+
	"bad decision, that's their own fault. I can show them the exit easily "+
	"enough.", 1);
    add_ask(({ "gnimpsh" }), "say Oh Gnimpsh? He's an interesting "+
	"sort, good at keeping records, though! Don't kill him!", 1);
    add_ask(({ "dalizen" }), "say Dalizen? He's one of those dark "+
	"elves, you know the kind that get kicked out because they don't follow "+
	"the rules just right? He is my second in command, and despite his "+
	"obvious weakness of being an weak-armed elf, he's halfway decent.", 1);
    add_ask(({ "morgan" }), "say I picked up Morgan in Minas Tirith, I "+
	"think she used to be one of those rangers. She's a fine tracker, and "+
	"not half bad to look at.", 1);
    add_ask( "taryn", "say Taryn was part of a package deal. She's the "+
	"daughter of one of my mercenaries. She's a nuisance, always pestering "+
	"me to teach her to fight.", 1);
    add_ask("soren", "say Soren is a perfect shop-keeper, he keeps his "+
	"mouth shut.", 1);
    add_ask("tarn", "say Tarn is a dwarf, and therefore a good smith by "+
	"default.", 1);
    add_ask(({ "human", "humans" }), "say Humans don't make half-bad "+
	"mercenaries. If they grow out their beards, they even look somewhat "+
	"pretty.", 1);
    add_ask(({ "elf", "elves" }), "say Well, elves are in general too weak "+
	"to do much of anything, but I let them try to learn if they want "+
	"to, mainly out of respect for Dalizen. They still can't swing a club "+
	" worth a damn, though.", 1);
    add_ask(({ "gnome", "gnomes" }), "say In spite of myself, sometimes "+
	"I feel sorry for gnomes. They're odd little folk, but I let them get "+
	"away with more here than I do the halfling folk. They're probably "+
	"more suited to using swords, though, since they're small and weak.", 1);
    add_ask(({ "dwarf", "dwarves" }), "say Ahh! A good dwarf at your side "+
	"in battle, what more can ya ask for? A club is deadly in a dwarf's "+
	"powerful arms. Still, I've seen some dwarves around here using swords, "+
	"they must be confused.", 1);
    add_ask(({ "bet", "wager" }), "say Oh, that! Dalizen bet me that "+
	"swords were just as useful as clubs in every way. So after breaking "+
	"a few dozen trying to smash in a wooden crate, he admitted defeat. He "+
	"sure didn't like it, though!", 1);

    add_ask(({"background", "history", "past" }), "say My past, ya say? "+
	"Well my past is a story that would take more than an evening in the "+
	"pub ta tell, that's fer sure. I learned to fight in an army that was "+
	"far from this land, and no longer exists. We served a King there, "+
	"whose name I won't even speak. I don't want any of them to come "+
	"looking for me, now that I'm so successful here. I like my new life "+
	"just fine, and I don't want any of 'em trying to take it away. 'Course "+
	"there probably aren't even any around these days. Anyway, after that "+
	"army went away, I had to do something, so I figured why not work "+
	"for myself for once, instead of working for someone else.", 1 );

    add_ask(({"money", "bribe", "bribes", "pay"}), "say I might be willing to "+
	"do some business for the right price! How bout a few coins just to "+
	"get me in the mood?", 1);

    add_ask(({"mercs", "members"}), &query_member_list(), 1);

    set_default_answer( ({ "say I couldn't tell ya.",
        "say I have no idea!", "emote tugs on his majestic beard thoughtfully.",
        "say I don't know!" }) );


    set_bribe( ({ 1, "The only thing copper coins are good for is for stuffing "+
			"cheap bastards with before you throw them off a pier.",
                  12, "I once met this begger in Pelargir, he barely had "+
			"enough money to feed himself, and even he wasn't as "+
			"tight with money as you!",
                  144, "Everybody has a price, as the saying goes.",
                  1728, give_bribe_info,
                  86400, bribe_get_to_join,
		  172800, bribe_remove_not_allowed,
                  345600, bribe_remove_warned,
                  864000, bribe_reduce_leave_penalty,
                  1728000, bribe_no_leave_penalty }) );
}

void
init_living()
{
    ::init_living();
    init_bribe();
}

void
intro_me(object name)
{
    command("introduce me to " + OB_NAME(name));
    command("say to " + OB_NAME(name) + " I am Maligant, and while you're in "+
	"my camp, you had best follow my rules!");
}
 
void
add_introduced(string str)
{
    object who = find_living(str);
    if (member_array("Balan", m_indexes(who->query_introduced())) == -1)
        set_alarm(2.8, 0.0, &intro_me(who));
}
