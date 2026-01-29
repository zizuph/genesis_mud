/*
 *  /d/Gondor/clubs/nisse/npc/hawkmistress.c
 *
 *  The hawkmistress of the Nisse Ohtar club.
 *
 *  Deagol, March 2003
 */

#pragma strict_types
#pragma save_binary

inherit "/d/Gondor/std/monster";
inherit "/std/act/action";
inherit "/std/act/chat";
inherit "/lib/trade";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>

#include "/d/Gondor/defs.h"
#include "../nisse_defs.h"

#define	FORTUNE_PRICE 144	/* 1 gc */

/*
 *  Global variables
 */
int	fortune_flag;	/* is Estiu telling a fortune to somebody? */
object	player;
string	name;
string	*saying = ({
    "Genius does what it must, talent does what it should, skill does what " +
        "it can.\n",
    "For as one thinketh in one's heart, so one is.\n",
    "High places have their precipices.\n",
    "It may be a fire today, but tomorrow it will be only ashes.\n",
    "Justifying a fault doubles it.\n",
    "Never attempt to teach a pig to sing because you will ultimately be " +
        "unsuccessful and you will irritate the pig.\n",
    "Embrace life so fear cannot enter your heart.\n",
    "Iron rusts from disuse, stagnant water loses its purity and in cold " +
        "weather becomes frozen; even so does inaction sap the vigors of " +
        "the mind.\n",
    "Knowledge becomes wisdom only after it has been put to practical use.\n",
    "Character is made by many acts; it may be lost by a single one.\n",
    "Crises bring out the best in the best of us, and the worst in the " +
        "worst of us.\n",
    "I count him braver who conquers his desires than him who conquers his " +
        "enemies; for the hardest victory is the victory over self.\n",
    "The man who never alters his opinions is like standing water, and " +
        "breeds reptiles of the mind.\n",
    "Nothing is as amazing as our expectations anticipate.\n",
    "Small minds are rarely accompanied by small mouths.\n",
    "You cannot change others, only yourself.\n",
    "Nobody knows the age of the human race, but everybody agrees that it " +
        "is old enough to know better.\n",
    "Time is that quality of nature which keeps events from happening all " +
        "at once. Lately it doesn't seem to be working.\n",
    "To him that you tell your secret you resign your liberty.\n",
    "We are all novices. Only the dead have nothing left to learn.\n",
    "To fight when you are not afraid is nothing, to not fight when you " +
        "are afraid is nothing, but to fight when you are afraid is " +
        "something.\n",
    "It's hard to make something foolproof because fools are so ingenious.\n",
    "There are two types of people, those who do not understand what they " +
        "rule and those that rule what they do not understand.\n",
    "When someone finally locates the center of the universe, many people " +
        "will be surprised to learn they're not it.\n",
    "Once you begin to understand life, you don't need an excuse to be " +
        "confused!\n",
    "The envious only hate the excellence they cannot reach.\n",
    "No matter what happens, there is always someone who knew it would.\n",
    "When you blame others you give up your power to change.\n",
    "Buy a dwarf a beer and he wastes an hour. Teach a dwarf to brew and " +
        "he wastes a lifetime.\n",
    "People are like stained glass windows. They glow and sparkle when it " +
        "is sunny and bright; but when the sun goes down their true " +
        "beauty is revealed only if there is a light from within.\n",
    "To let a fool kiss you is stupid, to let a kiss fool you is worse.\n",
    "To be educated is to finally discover that there are some questions " +
        "to which nobody has the answer.\n",
    "Our background and circumstances may have influenced who we are, but " +
        "we alone are responsible for who we become.\n",
    "Some people make things happen, some watch while things happen, and " +
        "some wonder 'What happened?'\n",
    "Time exists so everything doesn't happen at once. Space exists so " +
        "everything doesn't happen to you.\n",
    "It isn't the mountains ahead that wear you out, it's the grain of " +
        "sand in your shoe.\n",
    "Never wrestle with a pig. You both get dirty, but the pig likes it.\n",
    "A leader's job is to make it easy to do the right thing and difficult " +
        "to do the wrong thing.\n"});

/*
 *  Prototypes
 */
void	add_acts();
void	ask_about_nisse();
void	ask_about_help();
void	ask_about_runes();
void	ask_about_hawkmistress();
void	default_answer();
int	check_hidden();

void
create_gondor_monster()
{
    ::create_gondor_monster();
    
    set_name(({"estiu", "hawkmistress"}));
    set_adj(({"proud", "noble"}));
    set_living_name("estiu");
    set_race_name("elf");
    set_gender(G_FEMALE);
    set_title("the Hawkmistress of the Nisse Ohtar");
    set_long("This " + TO->query_nonmet_name() + " is the chief of Nisse " +
             "Ohtar camp and works as a hawkmistress here. She was the " +
             "very first Nisse who found the sisterhood of Nisse Ohtar.\n" +
             "She is wearing a bronze hawk feather in hair.\n" +
             "A bronze hawk is sitting on her left wrist.\n");

    set_base_stat(SS_STR, 110);
    set_base_stat(SS_DEX, 90);
    set_base_stat(SS_CON, 110);
    set_base_stat(SS_INT, 250);
    set_base_stat(SS_WIS, 200);
    set_base_stat(SS_DIS, 200);

    add_prop(CONT_I_WEIGHT, 55000);
    add_prop(CONT_I_HEIGHT, 220);

    set_alignment(0);
    
    setuid();
    seteuid(getuid());

    add_prop(OBJ_M_NO_ATTACK, CAP(short()) + " looks at you angrily and " +
        "shouts: How do you dare?! Get lost!\n");
    add_prop(OBJ_M_NO_MAGIC_ATTACK, CAP(short()) + " looks at you angrily " +
        "and shouts: How do you dare?! Get lost!\n");

    set_default_answer(VBFC_ME("default_answer"));
    add_ask_item(({"nisse", "nisse ohtar", "join nisse", "club"}),
        VBFC_ME("ask_about_nisse"));
    add_ask_item(({"help"}), VBFC_ME("ask_about_help"));
    add_ask_item(({"runes", "fortune", "teller", "fortune teller"}),
        VBFC_ME("ask_about_runes"));
    add_ask_item(({"hawkmistress", "chief", "estiu"}),
        VBFC_ME("ask_about_hawkmistress"));
 
    config_default_trade();

    add_acts();
}

/*
 *  Function name: default_answer
 *  Description  : This function is called when a player asks Estiu about
 *                 something she does not know.
 */
void
default_answer()
{
    if (!check_hidden())
    {
        return;
    }

    player = TP;
    name = player->query_real_name();

    if (random(2))
    {
        set_alarm(1.0, 0.0, &command("say to " + name + " How should I " +
            "know that?"));
        set_alarm(2.0, 0.0, &command("eyebrow"));
    }
    else
    {
        set_alarm(1.0, 0.0, &command("say to " + name + " Don't ask me. " +
            "Some things you need to figure out for yourself."));
    }

    return;
}

/*
 *  Function name: ask_about_hawkmistress
 *  Description  : This function is called when a player asks about
 *                 a hawkmistress.
 */
void
ask_about_hawkmistress()
{
    if (!check_hidden())
    {
        return;
    }

    player = TP;
    name = player->query_real_name();

    if (player->query_nisse_level() == 0)
    {
       command("say to " + name +
            " Go straight on, turn right, turn right again, go straight on " +
            "until you meet me again.");
        command("smile help");
        return;
    }

    command("say to " + name + " Are you joking? You don't know your " +
        "superiors? I'm the hawkmistress and the chief of the camp.");
    command("fume");
    return;
}

/*
 *  Function name: ask_about_nisse
 *  Description  : This function is called when a player asks Neit about
 *                 Nisse.
 */
void
ask_about_nisse()
{
    if (!check_hidden())
    {
        return;
    }
    
    player = TP;
    name = player->query_real_name();
    
    if (player->query_nisse_level() == 0)
    {
        command("say to " + name +
            " Seek at the ceremony pool, it's nearby.");
        command("smile help");
        return;
    }

    command("say to " + name + " I hope you enjoy your stay in the camp.");
    command("smile hope");
    return;
}

/*
 *  Function name: ask_about_help
 *  Description  : This function is called when a player asks Neit about
 *                 help.
 */
void
ask_about_help()
{
    if (!check_hidden())
    {
        return;
    }
    
    player = TP;
    name = player->query_real_name();

    command("say to " + name +
        " You want to help me? I don't need your help.");
    command("flex");
    return;
}

/*
 *  Function name: ask_about_runes
 *  Description  : This function is called when a player asks Neit about
 *                 runes.
 */
void
ask_about_runes()
{
    if (!check_hidden())
    {
        return;
    }
    
    player = TP;
    name = player->query_real_name();
    
    command("smile warm");
    command("say Just pay me for a fortune.");
}

/*
 *  Function name: check_hidden
 *  Description  : This function checks if a player is visible to a npc.
 *  Returns      : 1 if a player is visible, 0 if a player is invisible
 */
int
check_hidden()
{   
    if (!CAN_SEE(this_object(), this_player()))
    {   
        command("say I can't see you. Let me see your face.");
        return 0;
    }
    
    return 1;
}

/*
 *  Function name: add_acts
 *  Description  : This function is called in create_gondor_monster() when
 *                 this object is cloned. It adds random acts to this npc.
 */
void
add_acts()
{
    set_act_time(30);
    add_act("emote strokes her hawk on its head.");
    add_act("say Do you want to know your future? I'm sort of a fortune " +
        "teller.");
}

/*
 *  Function name: react_intro
 *  Description  : This function is called in routine add_introduced().
 *                 It contains a reaction when a player introduce him/herself
 *                 to this object.
 *  Arguments    : object tp - this_player()
 */
void
react_intro(object tp)
{
    if (!objectp(tp))
    {
        return;
    }

    command("introduce me to " + tp->query_real_name() + "");
    command("say to " + tp->query_real_name() + " Hello, what can I do " +
            "for you, " + tp->query_name() + "?");
    return;
}

/*
 *  Function name: add_introduced
 *  Description  : It is called when a player introduce him/herself to
 *                 this object.
 *  Arguments    : string str - Name of the introduced living
 */
public void
add_introduced(string str)
{
    if (!interactive(TP) || TP->query_met(query_name()))
    {
        return;
    }

    set_alarm(1.0 + 3.0 * rnd(), 0.0, &react_intro(TP));
}

/*
 *  Function name: set_fortune_flag
 *  Description  : Sets a variable fortune_flag to 1.
 */
void
set_fortune_flag()
{
    fortune_flag = 1;
}

/*
 *  Function name: unset_fortune_flag
 *  Description  : Sets a variable fortune_flag to 0.
 */
void
unset_fortune_flag()
{
    fortune_flag = 0;
}

/*
 *  Function name: pay_fortune
 *  Description  : This function is called when a player pays Estiu, she
 *                 will tell a player one of her sayings.
 *  Arguments    : string str - as entered by the player
 *  Returns      : 0/1
 */
int
pay_fortune(string str)
{
    int		*money;
    object	paralyze;

    player = TP;
    name = player->query_real_name();

    if (!strlen(str) || !parse_command(str, ({}),
        "[estiu] [noble] [proud] [elf] [for] [a] 'fortune' [tell]"))
    {
        notify_fail("Pay what?\n");
        return 0;
    }

    if (fortune_flag)
    {
        notify_fail("The hawkmistress is telling a fortune to " +
            "somebody else.\n");
        return 0;
    }

    if (!CAN_SEE_IN_ROOM(TO) || !CAN_SEE(TO, TP))
    {
        command("say Who's that? Where are you? I can't see you.");
        return 1;
    }

    money = pay(FORTUNE_PRICE, player);

    if (sizeof(money) == 1)
    {
        set_alarm(1.0, 0.0, &command("say to " + name + " I can't work as " +
            "a fortune teller for the poor people like you."));
        set_alarm(1.5, 0.0, &command("comfort " + name + ""));
        set_alarm(2.5, 0.0, &command("say to " + name + " You should hunt " +
            "some enemies down and loot their corpses!"));
        set_alarm(3.0, 0.0, &command("smile help"));
        return 1;
    }

    set_fortune_flag();
    
    paralyze = clone_object("/std/paralyze");
    paralyze->set_stop_object(0);
    paralyze->set_stop_fun(0);
    paralyze->set_remove_time(45); // to be sure the paralyze will be removed
    paralyze->set_stop_verb(0);
    paralyze->set_fail_message("You paid for a fortune, keep silence and " +
        "listen to a fortune teller.\n");
    paralyze->set_stop_message(0);
    paralyze->move(player, 1);

    player->catch_msg("You pay for a fortune.\n");
    say(QCTNAME(player) + " pays for a fortune.\n");
    player->catch_msg(TO->query_The_name(player) + " smiles warmly at you " +
        "then gestures invitingly at one of the two chairs.\n");
    say(QCTNAME(TO) + " smiles warmly at " + QTNAME(player) + " then " +
        "gestures invitingly at one of the two chairs.\n");
    set_alarm(1.0, 0.0, &player->catch_msg("As you sit down, " +
        TO->query_the_name(player) + " decides to join you and sits across " +
        "the table from you. She picks up the small velvet bag and looks " +
        "at you expectantly.\n"));
    set_alarm(1.0, 0.0, &say("As " + QTNAME(player) + " sits down, " +
        QTNAME(TO) + " decides to join " + OBJECTIVE(player) + " and sits " +
        "across the table from " + QTNAME(player) + ". She picks up the " +
        "small velvet bag and looks at " + QTNAME(player) + " " +
        "expectantly.\n"));
    set_alarm(7.0, 0.0, &player->catch_msg(TO->query_The_name(player) + " " +
        "shakes the small velvet bag, then opens it and tilts it toward " +
        "you, instructing you to select three runes, concentrate and " +
        "focus.\n"));
    set_alarm(7.0, 0.0, &say(QCTNAME(TO) + " shakes the small velvet bag, " +
        "then opens it and tilts it toward " + QTNAME(player) +
        ", instructing " + OBJECTIVE(player) + " to select three runes.\n"));
    set_alarm(13.0, 0.0, &player->catch_msg(TO->query_The_name(player) + " " +
        "takes the three runes from you and places them on the table in a " +
        "particular pattern.\n"));
    set_alarm(13.0, 0.0, &say(QCTNAME(TO) + " takes the three runes from " +
        QTNAME(player) + " and places them on the table in a particular " +
        "pattern.\n"));
    set_alarm(20.0, 0.0, &player->catch_msg(TO->query_The_name(player) + " " +
        "closes her eyes, whispering something under her breath in " +
        "quenya. You cannot make out what she is saying.\n"));
    set_alarm(20.0, 0.0, &say(QCTNAME(TO) + " closes her eyes, whispering " +
        "something under her breath in quenya. You cannot make out what " +
        "she is saying.\n"));
    set_alarm(27.0, 0.0, &player->catch_msg(TO->query_The_name(player) + " " +
        "seems to be in a trance of some sort.\n"));
    set_alarm(27.0, 0.0, &say(QCTNAME(TO) + " seems to be in a trance of " +
        "some sort.\n"));
    set_alarm(34.0, 0.0, &player->catch_msg(TO->query_The_name(player) + " " +
        "suddenly opens her eyes, looks directly at you and says: " +
        one_of_list(saying)));
    set_alarm(34.0, 0.0, &say(QCTNAME(TO) + " suddenly opens her eyes, " +
        "looks directly at " + QTNAME(player) + " and tells " +
        OBJECTIVE(player) + " something.\n"));
    set_alarm(41.0, 0.0, &player->catch_msg(TO->query_The_name(player) + " " +
        "takes a deep breath and bids you farewell.\n"));
    set_alarm(41.0, 0.0, &say(QCTNAME(TO) + " takes a deep breath and bids " +
        QTNAME(player) + " farewell.\n"));
    set_alarm(42.0, 0.0, &player->move_living("out", 
        NISSE_ROOM_DIR + "path2", 1));
    set_alarm(41.0, 0.0, &paralyze->remove_object());
    set_alarm(41.0, 0.0, &unset_fortune_flag());
    
    return 1;
}

void
init_living()
{
    ::init_living();
    
    add_action(pay_fortune, "pay");
}
