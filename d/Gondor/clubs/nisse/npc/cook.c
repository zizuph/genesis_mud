/*
 *  /d/Gondor/clubs/nisse/npc/tinker.c
 *
 *  The cook of the Nisse Ohtar club.
 *
 *  Deagol, March 2003
 */

#pragma strict_types
#pragma save_binary

inherit "/d/Gondor/std/monster";
inherit "/std/act/action";
inherit "/std/act/chat";
inherit "/d/Gondor/open/sps";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <money.h>

#include "/d/Gondor/defs.h"
#include "../nisse_defs.h"

/*
 *  Global variables
 */
object	player;
string	name;
int	wash_flag;		/* isn't anybody else washing the dishes? */
int	dishes_flag = 1;	/* are there the dishes to wash? */

/*
 *  Prototypes
 */
void	add_acts();
void	ask_about_nisse();
void	ask_about_help();
void	ask_about_game();
void	ask_about_meal();
void	ask_about_dishes();
void	ask_about_hawkmistress();
void	default_answer();
int	check_hidden();

void
create_gondor_monster()
{
    ::create_gondor_monster();
    
    set_name(({"cerridwen", "cook", "keeper"}));
    set_adj(({"small", "furry"}));
    set_living_name("cerridwen");
    set_race_name("hobbit");
    add_name(NISSE_COOK_ID);
    set_gender(G_FEMALE);
    set_title("Took");
    set_long("This " + TO->query_nonmet_name() + " is the cook of Nisse " +
             "Ohtar. She knows a lot of secret recipes and culinary skills " +
             "are well known among the Nisse. If you have enough money, she " +
             "would gladly help you fill your empty belly.\n" +
             "She is wearing a deep brown hawk feather in hair, a dirty " +
             "cookery apron and a pair of flip-flop shoes.\n");

    set_base_stat(SS_STR, 80);
    set_base_stat(SS_DEX, 90);
    set_base_stat(SS_CON, 70);
    set_base_stat(SS_INT, 80);
    set_base_stat(SS_WIS, 60);
    set_base_stat(SS_DIS, 40);

    add_prop(CONT_I_WEIGHT, 30000);
    add_prop(CONT_I_HEIGHT, 80);

    set_alignment(0);

    setuid();
    seteuid(getuid());

    add_prop(OBJ_M_NO_ATTACK, CAP(short()) + " hits your head with the pan " +
        "she is holding and grumbles.\n");
    add_prop(OBJ_M_NO_MAGIC_ATTACK, CAP(short()) + " hits your head with " +
        "the pan she is holding and grumbles.\n");

    set_default_answer(VBFC_ME("default_answer"));
    add_ask_item(({"hawkmistress", "chief", "estiu"}),
        VBFC_ME("ask_about_hawkmistress"));
    add_ask_item(({"nisse", "nisse ohtar", "join nisse", "club"}),
        VBFC_ME("ask_about_nisse"));
    add_ask_item(({"help"}), VBFC_ME("ask_about_help"));
    add_ask_item(({"meal", "food"}),
        VBFC_ME("ask_about_meal"));
    add_ask_item(({"game", "scissors", "paper", "stone"}),
        VBFC_ME("ask_about_game"));
    add_ask_item(({"dishes", "dirty dishes", "washing dishes", "washing"}),
        VBFC_ME("ask_about_dishes"));

    add_acts();
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
            " Ahh, our Hawkmistress? She is the wise person that knows a " +
            "lot of sayings. She was the very first Nisse and possesses " +
            "a great knowledge.");
        command("say to " + name +
            " She lives not far from here. You should be able to find her " +
            "tent easily.");
        command("smile help");
        return;
    }

    command("say to " + name + " Ahh, good old Estiu. I haven't seen her " +
        "for quite a while. She's probably working on something.");
    command("smile cur");
    return;
}


/*
 *  Function name: default_answer
 *  Description  : This function is called when a player asks Cerridwen for
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
    
    set_alarm(1.0, 0.0, &command("say to " + name + " How should I know " +
        "that?"));
    set_alarm(2.0, 0.0, &command("eyebrow"));
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
            " Have you talked to our Hawkmistress? She is the person " +
            "you are searching for. She lives not far from here.");
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

    if (!dishes_flag)
    {
        command("say to " + name + " You want to help me?");
        set_alarm(1.5, 0.0, &command("say to " + name + " I don't need " +
            "your help right now. Drop in later."));
        set_alarm(2.0, 0.0, &command("smile"));
        return;
    }

    command("say to " + name + " You want to help me?");
    set_alarm(1.5, 0.0, &command("say to " + name + " Over there is a " +
        "heap of dishes."));
    set_alarm(2.5, 0.0, &command("grin misc"));
    return;
}

/*
 *  Function name: ask_about_game
 *  Description  : This function is called when a player asks Neit about
 *                 the scissors, paper, stone game.
 */
void
ask_about_game()
{
    if (!check_hidden())
    {
        return;
    }
    
    player = TP;
    name = player->query_real_name();
    
    command("say to " + name + " Just \"play game <your choice>\". You can " +
        "choose a scissors, paper or stone.");
}

/*
 *  Function name: ask_about_meal
 *  Description  : This function is called when a player asks Neit about
 *                 meal.
 */
void
ask_about_meal()
{
    if (!check_hidden())
    {
        return;
    }
    
    player = TP;
    name = player->query_real_name();
    
    command("point pricelist");
    command("say to " + name + " Order whatever you want. All meals listed " +
        "on the pricelist are fresh.");
}

/*
 *  Function name: ask_about_dishes
 *  Description  : This function is called when a player asks Neit about
 *                 dishes.
 */
void
ask_about_dishes()
{
    if (!check_hidden())
    {
        return;
    }
    
    player = TP;
    name = player->query_real_name();
    
    if (!dishes_flag)
    {
        command("smile");
        command("point basin");
        command("say to " + name + " Fortunately there are no dishes that " +
            "need to be washed.");
        return;
    }
    
    command("chuckle");
    command("say to " + name + " Over there, if you are interested.");
    command("point basin");
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
    add_act("emote yawns softly.");
    add_act("say Are you bored? Let's play a game.");
    add_act("say I can play the scissors, paper, stone game. " +
        "Do you know it?");
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
    command("say to " + tp->query_real_name() + " Hullo, may I serve you " +
            "something, " + tp->query_name() + "?");
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
    if (!interactive(TP) && TP->query_met(query_name()))
    {
        return;
    }

    set_alarm(1.0 + 3.0 * rnd(), 0.0, &react_intro(TP));
}

/*
 *  Function name: set_dishes_flag
 *  Description  : Sets a variable dishes_flag to 1.
 */
void
set_dishes_flag()
{
    tell_room(ENV(TO), "The cook puts another load of dirty dishes into " +
        "the basin. They sink into the suds.\n");
    dishes_flag = 1;
}

/*
 *  Function name: unset_dishes_flag
 *  Description  : Sets a variable dishes_flag to 0.
 */
void
unset_dishes_flag()
{
    dishes_flag = 0;
    /* let the players wash the dishes after 3 minutes again */
    set_alarm(180.0, 0.0, &set_dishes_flag());
}

/*
 *  Function name: set_wash_flag
 *  Description  : Sets a variable wash_flag to 1.
 */
void
set_wash_flag()
{
    wash_flag = 1;
}

/*
 *  Function name: unset_wash_flag
 *  Description  : Sets a variable wash_flag to 0.
 */
void
unset_wash_flag()
{
    wash_flag = 0;
}

/*
 *  Function name: query_dishes_flag
 *  Description  : Says a status of the dishes. It's called from an object
 *                 of the room where this object stands (should be taver.c).
 *                 The players can get an info by examinig the dishes.
 *  Returns      : dishes_flag (0/1)
 */
int
query_dishes_flag()
{
    return dishes_flag;
}

/*
 *  Function name: wash_dishes
 *  Description  : When a player wants to help Cerridwen, he/she can wash
 *                 the dishes.
 *  Arguments    : string str - as entered by the player
 *  Returns      : 0/1
 */
int
wash_dishes(string str)
{
    object paralyze;
    
    if (!strlen(str) || !parse_command(str, ({}), "[the] 'dishes'"))
    {
        notify_fail(CAP(query_verb()) + " what?\n");
        return 0;
    }

    if (wash_flag)
    {
        notify_fail("Somebody else is washing the dishes right now.\n");
        return 0;
    }
    
    if (!dishes_flag)
    {
        notify_fail("The dishes are all washed already.\n");
        return 0;
    }

    set_wash_flag();
    
    paralyze = clone_object("/std/paralyze");
    paralyze->set_stop_object(0);
    paralyze->set_stop_fun(0);
    paralyze->set_remove_time(20);
    paralyze->set_stop_verb(0);
    paralyze->set_fail_message("You cannot do anything else but wash " +
        "the dishes.\n");
    paralyze->set_stop_message("You stop washing the dishes.\n");
    paralyze->move(TP, 1);
    
    MONEY_MAKE_SC(1)->move(TO);
    write("You roll up your sleeves and get to work.\n");
    say(QCTNAME(TP) + " rolls up " + POSSESSIVE(TP) + " sleeves and gets " +
        "to work.\n");
    tell_room(NISSE_ROOM_DIR + "tavern", "Suds splash everywhere!\n");
    set_alarm(5.0, 0.0, &tell_room(NISSE_ROOM_DIR + "tavern",
        "Suds splash everywhere!\n"));
    set_alarm(10.0, 0.0, &tell_room(NISSE_ROOM_DIR + "tavern",
        "Suds splash everywhere!\n"));
    set_alarm(15.0, 0.0, &tell_room(NISSE_ROOM_DIR + "tavern",
        "Suds splash everywhere!\n"));
    set_alarm(20.0, 0.0, &say(QCTNAME(TP) + " stops washing the dishes.\n"));
    set_alarm(21.0, 0.0, &command("give coins to " + TP->query_real_name()));
    set_alarm(22.0, 0.0, &command("smile thank " + TP->query_real_name()));
    set_alarm(20.0, 0.0, &unset_wash_flag());
    set_alarm(20.0, 0.0, &unset_dishes_flag());
    return 1;
}

void
init_living()
{
    ::init_living();
    
    init_sps_game();
    add_action(wash_dishes, "wash");
}
