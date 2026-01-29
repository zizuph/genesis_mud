/*
 *  /d/Gondor/clubs/nisse/npc/trainer.c
 *
 *  The trainer for the Nisse Ohtar club.
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
int	irank;

/*
 *  Prototypes
 */
void	add_acts();
mixed	challenge_me();
void	default_answer();
void	ask_about_nisse();
void	ask_about_help();
void	ask_about_hawkmistress();
void	arm_me();
int	check_hidden();

void
create_gondor_monster()
{
    ::create_gondor_monster();
    
    set_name(({"neit", "trainer", "warrior"}));
    set_adj(({"tall", "brawny"}));
    set_living_name("neit");
    set_race_name("human");
    set_gender(G_FEMALE);
    set_title("the master trainer of Nisse Ohtar");
    set_long("This " + TO->query_nonmet_name() + " lives in the Nisse " +
             "Ohtar camp and works as a trainer here. If you feel strong " +
             "and brave enough, you can challenge her. But be careful, " +
             "when she wins, she will treat you without remorse.\nShe is " +
             "wearing a gold hawk feather in hair.\n");

    set_base_stat(SS_STR, 110);
    set_base_stat(SS_DEX, 90);
    set_base_stat(SS_CON, 110);
    set_base_stat(SS_INT, 250);
    set_base_stat(SS_WIS, 200);
    set_base_stat(SS_DIS, 200);

    set_skill(SS_DEFENCE, 200);
    set_skill(SS_PARRY, 150);
    set_skill(SS_WEP_SWORD, 200);
    set_skill(SS_AWARENESS, 70);

    add_prop(CONT_I_WEIGHT, 100000);
    add_prop(CONT_I_HEIGHT, 250);

    add_prop(OBJ_M_NO_ATTACK, CAP(short()) + " says: If you don't want to " +
        "challenge me, get lost.\n");
    add_prop(OBJ_M_NO_MAGIC_ATTACK, CAP(short()) + " says: If you don't " +
        "want to challenge me, get lost.\n");
    
    set_alignment(0);
    
    setuid();
    seteuid(getuid());

    set_default_answer(VBFC_ME("default_answer"));
    add_ask_item(({"challenge", "fight"}), VBFC_ME("challenge_me"));
    add_ask_item(({"nisse", "nisse ohtar", "join nisse", "club"}),
        VBFC_ME("ask_about_nisse"));
    add_ask_item(({"help"}), VBFC_ME("ask_about_help"));
    add_ask_item(({"hawkmistress", "chief", "estiu"}),
        VBFC_ME("ask_about_hawkmistress"));
 
    arm_me();
    add_acts();
}

/*
 *  Function name: default_answer
 *  Description  : This function is called when a player asks Neit for
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
 *  Function name: arm_me
 *  Description  : This function is called in create_gondor_monster().
 *                 It arms this npc.
 */
void
arm_me()
{
    clone_object("/d/Gondor/common/wep/rndsword")->move(TO);
    clone_object("/d/Gondor/common/arm/rndarmour")->move(TO);
    clone_object("/d/Gondor/common/arm/rndhelmet")->move(TO);
    
    set_alarm(0.1, 0.0, &command("wear all"));
    set_alarm(0.1, 0.0, &command("wield all"));    
}

/*
 *  Function name: challenge_me
 *  Description  : This function is called when a player asks Neit for
 *                 a challenge.
 */
mixed
challenge_me()
{
    if (!check_hidden())
    {
        return 1;
    }
    
    player = TP;
    name = player->query_real_name();
    
    if (!(MANAGER->query_to_graduate(CAP(name))))
    {
        command("say to " + name +
            " You are not yet ready to spar with me.");
        return 1;
    }
    
    command("say to " + name + " Get ready! I'm going to check your skills.");
    set_alarm(5.0, 0.0, &command("kill " + name));

    return 1;
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
    command("flex");
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
    add_act("emote checks all her blades and smiles relieved.");
    add_act("say Don't bother me if you're not ready to challenge me.");
    add_act("say No mercy with cowards.");
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
 *  Function name: hit_me
 *  Description  : Masked version of the original NPC hit_me function. This
 *                 function calls the original hit_me function of the NPC,
 *                 which does the damage checks and things and then checks
 *                 the health of the NPC. If it drops below the set limit,
 *                 it will stop fighting all enemies and say something.
 *  Arguments    : type 'sman hit_me'
 *  Returns      : type 'sman hit_me'
 */
varargs public mixed
hit_me(int wcpen, int dt, object attacker, int attack_id, int
    target_hitloc = -1)
{
    mixed	result;
    object	*enemies;
    object	feather;
    string	birthmark_colour;

    name = player->query_real_name();
    irank = MANAGER->query_nisse_level(name);

    // Call the original hit_me function
    result = ::hit_me(wcpen, dt, attacker, attack_id, target_hitloc);

    // Check if the health is only 50% of the maximum
    if ((query_hp() * 100 / query_max_hp()) < 50)
    {
        enemies = query_enemy(-1);
        feather = present(NISSE_FEATHER_ID, player);

        stop_fight(enemies);
        enemies->stop_fight(this_object());

        if (irank == 0)
        {
            return 0;
        }
        else if (irank == 1)
        {
            MANAGER->remove_to_graduate(name);
            MANAGER->add_nisse(name, "light brown");
            feather->set_short("light brown hawk feather");
        }
        else if (irank == 2)
        {
            MANAGER->remove_to_graduate(name);
            MANAGER->add_nisse(name, "brown");
            feather->set_short("brown hawk feather");
        }
        else if (irank == 3)
        {
            MANAGER->remove_to_graduate(name);
            MANAGER->add_nisse(name, "deep brown");
            feather->set_short("deep brown hawk feather");
        }
        else if (irank == 4)
        {
            MANAGER->remove_to_graduate(name);
            MANAGER->add_nisse(name, "red");
            feather->set_short("red hawk feather");
        }
        else if (irank == 5)
        {
            MANAGER->remove_to_graduate(name);
            MANAGER->add_nisse(name, "gold");
            feather->set_short("gold hawk feather");
        }
        else if (irank == 6)
        {
            MANAGER->remove_to_graduate(name);
            MANAGER->add_nisse(name, "bronze");
            feather->set_short("bronze hawk feather");
        }

        set_alarm(1.0, 0.0, &command("congrat " + name));
        set_alarm(1.2, 0.0, &command("say to " + name + " You proved " +
            "yourself worthy to be promoted to the " +
            player->query_nisse_rank() + " rank."));
        set_alarm(1.5, 0.0, &command("touch " + name));
        set_alarm(1.6, 0.0, &player->catch_msg("You feel strange, " +
            "the blood in your veins flows quickly and suddenly the " +
            "colour of your hawk feather changes.\n"));
        set_alarm(2.3, 0.0, &player->catch_msg("You get calm again.\n"));
        }

    return result;
}

void
init_living()
{
    ::init_living();
    
    add_action(challenge_me, "challenge");
    add_action(challenge_me, "spar");
}
