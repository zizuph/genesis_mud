/*
 *  /d/Gondor/clubs/nisse/npc/guard.c
 *
 *  The guard of the Nisse Ohtar camp.
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
#include <filter_funs.h>
#include <wa_types.h>
#include <cmdparse.h>
#include <math.h>

#include "/d/Gondor/defs.h"
#include "../nisse_defs.h"

#define RANGER_I_NOT_BRAWL  "_ranger_i_not_brawl"

/*
 *  Global variables
 */
object	player;
string	name;
mapping	guards_defeaters = ([]);

/*
 *  Prototypes
 */
void	add_acts();
void	default_answer();
void	ask_about_nisse();
void	ask_about_help();
void	arm_me();
int	check_hidden();

void
create_gondor_monster()
{
    ::create_gondor_monster();
    
    set_name(({"aeron", "guard", "warrior"}));
    add_name(NISSE_GUARD_ID);
    set_adj(({"tall", "dangerous"}));
    set_living_name("aeron");
    set_race_name("human");
    set_gender(G_FEMALE);
    set_title("the guard of the Nisse Ohtar camp");
    set_long("This " + TO->query_nonmet_name() + " seems to be guarding " +
        "this place.\n" +
        "She is wearing a red hawk feather in her hair.\n");

    set_base_stat(SS_STR, 180);
    set_base_stat(SS_DEX, 200);
    set_base_stat(SS_CON, 190);
    set_base_stat(SS_INT, 80);
    set_base_stat(SS_WIS, 80);
    set_base_stat(SS_DIS, 120);

    set_skill(SS_DEFENCE, 200);
    set_skill(SS_PARRY, 150);
    set_skill(SS_WEP_SWORD, 200);
    set_skill(SS_AWARENESS, 70);

    add_prop(CONT_I_WEIGHT, 100000);
    add_prop(CONT_I_HEIGHT, 250);
    add_prop(RANGER_I_NOT_BRAWL, 1);
    set_alignment(0);
    
    setuid();
    seteuid(getuid());

    set_default_answer(VBFC_ME("default_answer"));
    add_ask_item(({"nisse", "nisse ohtar", "join nisse", "club"}),
        VBFC_ME("ask_about_nisse"));
    add_ask_item(({"help"}), VBFC_ME("ask_about_help"));

    arm_me();
    add_acts();
}

/*
 *  Function name: default_answer
 *  Description  : This function is called when a player asks Aeron for
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

    if (player->query_nisse_level())
    {
        set_alarm(1.0, 0.0, &command("say to " + name + " Excuse me, but " +
            "I don't know that."));
        set_alarm(2.0, 0.0, &command("smile awk"));
    }

    set_alarm(1.0, 0.0, &command("say to " + name + " How should I know " +
        "that?"));
    set_alarm(1.5, 0.0, &command("say to " + name + " Get of my sight " +
        "since I'm in a good mood."));
    set_alarm(2.0, 0.0, &command("eyebrow"));
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
    clone_object("/d/Gondor/common/wep/lsword")->move(TO);
    clone_object("/d/Gondor/common/arm/gchainmail")->move(TO);
    clone_object("/d/Gondor/common/arm/ghelmet")->move(TO);
    clone_object("/d/Gondor/common/arm/gshield")->move(TO);
    
    set_alarm(1.0, 0.0, &command("wear all"));
    set_alarm(1.0, 0.0, &command("wield all"));    
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
            " Nisse? What the hell is it supposed to be?");
        command("fume");
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
    add_act("say What are you doing here?");
    add_act("say Get out of here!");
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
    
    if (!tp->query_nisse_level())
    {
        command("say to " + tp->query_real_name() + " Get out of here! " +
            "Nobody asked you for introduction!");
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
    object	*players;
    object	feather;
    string	birthmark_colour;
    int		i;
    int		num_players;

    name = attacker->query_real_name();

    // Call the original hit_me function
    result = ::hit_me(wcpen, dt, attacker, attack_id, target_hitloc);

    // Check if the health is only 50% of the maximum
    if ((query_hp() * 100 / query_max_hp()) < 50)
    {
        enemies = query_enemy(-1);

        stop_fight(enemies);
        enemies->stop_fight(this_object());

        guards_defeaters = restore_map(NISSE_LOG_DIR + "guards_defeaters");
        if (!mappingp(guards_defeaters))
        {
            guards_defeaters = ([]);
        }

        players = FILTER_PLAYERS(all_inventory(ENV(TO)));
        num_players = sizeof(players);
        
        for (i = 0; i < num_players; i++)
        {
            name = players[i]->query_real_name();
            guards_defeaters[name] = 1;
            save_map(guards_defeaters, NISSE_LOG_DIR + "guards_defeaters");
        }
        
        tell_room(NISSE_ROOM_DIR + "entrance", QCTNAME(TO) + " gives up " +
            "and flies to the south, revealing a narrow pathway in this " +
            "direction.\n");
        remove_object();
    }

    return result;
}
