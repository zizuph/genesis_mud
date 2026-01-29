/*
 *  /d/Gondor/clubs/nisse/npc/tinker.c
 *
 *  The shopkeeper of the Nisse Ohtar club.
 *
 *  Deagol, March 2003
 */

#pragma strict_types
#pragma save_binary

inherit "/d/Gondor/std/monster";
inherit "/std/act/action";
inherit "/std/act/chat";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>

#include "/d/Gondor/defs.h"
#include "../nisse_defs.h"

/*
 *  Global variables
 */
object	player;
string	name;

/*
 *  Prototypes
 */
void	add_acts();
void	default_answer();
void	ask_about_nisse();
void	ask_about_help();
void	ask_about_hawkmistress();
int	check_hidden();

void
create_gondor_monster()
{
    ::create_gondor_monster();
    
    set_name(({"bridget", "tinker", "shopkeeper"}));
    set_adj(({"agile", "brown-eyed"}));
    set_living_name("bridget");
    set_race_name("dwarf");
    set_gender(G_FEMALE);
    set_title("the Tinker of the Nisse Ohtar");
    set_long("This " + TO->query_nonmet_name() + " is the tinker of Nisse " +
             "Ohtar. If you have anything nice to sell, she will trade " +
             "with you with pleasure.\n" +
             "She is wearing a deep brown hawk feather in hair.\n");

    set_base_stat(SS_STR, 110);
    set_base_stat(SS_DEX, 90);
    set_base_stat(SS_CON, 110);
    set_base_stat(SS_INT, 250);
    set_base_stat(SS_WIS, 200);
    set_base_stat(SS_DIS, 200);

    add_prop(CONT_I_WEIGHT, 70000);
    add_prop(CONT_I_HEIGHT, 120);

    set_alignment(0);

    setuid();
    seteuid(getuid());

    add_prop(OBJ_M_NO_ATTACK, CAP(short()) + " fumes angrily and " +
        "shouts: Get of my sight!\n");
    add_prop(OBJ_M_NO_MAGIC_ATTACK, CAP(short()) + " fumes angrily " +
        "and shouts: Get off my sight!\n");

    set_default_answer(VBFC_ME("default_answer"));
    add_ask_item(({"nisse", "nisse ohtar", "join nisse", "club"}),
        VBFC_ME("ask_about_nisse"));
    add_ask_item(({"hawkmistress", "chief", "estiu"}),
        VBFC_ME("ask_about_hawkmistress"));
    add_ask_item(({"help"}), VBFC_ME("ask_about_help"));

    add_acts();
}

/*
 *  Function name: default_answer
 *  Description  : This function is called when a player asks Bridget for
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

    command("say to " + name +
        " You want to help me? I don't need your help.");
    return;
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
    add_act("say Have you found anything useful to sell?");
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
