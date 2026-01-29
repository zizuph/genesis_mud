/*
 * File         : /d/Genesis/start/hobbit/npc/publican.c
 * Creator      : Seaweed
 * Copyright    : Copyright (C) 1998 Joakim Larsson
 * Date         : 3/6/99
 * Purpose      : 
 * Related Files: 
 * Comments     :
 *        The publican is a big sturdy old hobbit with bad temper which is
 *        unusual for a hobbit. He was one of Tondurs closest men and got
 *        severly wounded in the leg in the last big battle. The pain from
 *        the stiff leg makes his anger sudden.
 * 
 * TODO         :
 *      - Add chat
 *      - Add triggers

 *
 * Modifications:
 *     N.B. This file is generated from templates hosted elsewhere and
 *     if someone corrects something in this file, please mail Seaweed
 * 
 */

/* directives */
#pragma strict_types

/* includes */
#include <stdproperties.h> 
#include <macros.h> 
#include <ss_types.h> 
#include <living_desc.h>
#include <filter_funs.h>
#include <cmdparse.h>
#include <money.h>
#include "../hobbit.h"

/* inherits */
inherit "/std/monster";
inherit "/std/act/action";
inherit "/d/Genesis/lib/intro";
/* defines */
// NPC states (bit values)
#define CLEANING   1

/* prototypes */
void create_monster();
void publican_actions();
void equip_me();
string publican_default_answer();
string sell_fish();

/* global variables */
int     Status;
object  Visitor;

/*
 * Function name: create_monster
 * Description  : set up the humanoid
 */
void
create_monster()
{
    if (!IS_CLONE)
        return;
    set_name("tan");
    set_race_name("hobbit");
    
    set_gender(G_MALE);
    set_long(
      "The publican is a sturdy old hobbit that looks like a warrior " +
      "comming right of a battle. He is limping slightly because of the " +
      "left leg which is stiffened by the knee.\n");
    add_prop(CONT_I_HEIGHT, 115);
    add_prop(CONT_I_WEIGHT, 50000);
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(OBJ_S_WIZINFO, "Made by Seaweed 3/6/99.\n");
    
    set_stats(({90, 80, 80, 50, 40, 110}));
    set_hp(query_max_hp());
    add_name("publican");
    add_adj(({"big", "sturdy"}));
    set_act_time(5);
    add_act("@@publican_actions@@");
    set_default_answer(publican_default_answer);
    add_ask(({"beer", "ale"}),
        "say Yes, we got it. Do you want to buy one?", 1);
    set_scar(SCAR_LEFT_CHEEK | SCAR_RIGHT_HAND | SCAR_LEFT_HAND);
    add_cmd_item(({"fish", "fishes"}), 
        ({"sell","offer", "deliver"}), sell_fish);
    equip_me();
    
    
}

/*
 * Function name: introduce
 * Description  : A player that introduces himself to the NPC for the 
 *                first time will get a respons defined by this function
 * Arguments    : object who - The introduced player object
 */
void
introduce(object who)
{
    command("grin grim");
    command("introduce me");
    command("peer susp at " + who->query_name());
}

/*
 * Function name: greet
 * Description  : A player that has already introduced himself to the NPC 
 *                will get a respons defined by this function.
 * Arguments    : object who - The introduced player object
 */
void
greet(object who)
{
    command("say You don't say!");
    command("pat");
    command("say to " + who->query_name() +
        " I think you have said that already.");
    command("sigh");
}

/*
 * Function name: set_visitor(who)
 * Description  : access method for the Visitor variable
 * Arguments    : object who - the player object visiting us.
 */
public void
set_visitor(object who)
{
    Visitor = who;
}

/*
 * Function name: publican_actions()
 * Description  :  Handles NPC actions
 */
string
publican_actions()
{
    int i;
    if (Visitor && present(Visitor, environment(this_object())))
    {
        i = random(3);
        command("peer quickly at " + Visitor->query_name());
        switch(i)
        {
            case 0: // sigh & say
            {
                command("sigh unhappily");
                command("say to " + Visitor->query_name() + 
                    " What do you want?");
                command("point pricelist");
                break;
            }
            case 1..2: // nothing
            {
                break;
            }
            default:
            {
                command("sigh confused");
                break;
            }
        }
    }
    Visitor = 0;
    i = random(5);
    switch(i)
    {
        case 0:
        {
            command("grins slight");
            break;
        }
        case 1:
        {
            command("mumble unhappily.");
            break;
        }
        case 2:
        {
            command("peer slow");
            break;
        }
        case 3:
        {
            command("scratch nose");
            break;
        }
        case 4:
        {
            command("emote whipes off the counter slightly.");
            break;
        }
        default:
        {
            command("emote does something totally unexpected.");
        }
    }
    return "";
}

/*
 * Function name: publican_default_answer()
 * Description  : Handles the default answer for unknown questions.
 */
string
publican_default_answer()
{
    command("say to " + lower_case(TP->query_name()) + 
        " Who cares about that? Buy a beer and stop wasting my day!");
    return "";
}

/*
 * Function name: equip_me()
 * Description  : create cloths and equipments and wear it.
 */
void
equip_me()
{
    object clone;
    
    seteuid(getuid(TO));
    
    // Make some basic clothes
    clone = clone_object(EX_OBJ + "linnen_pants");
    clone->move(TO);
    clone = clone_object(EX_OBJ + "linnen_shirt");
    clone->move(TO);
    
    // Make some armourfeatured clothes
    clone = clone_object(EX_ARM + "leather_vest");
    clone->move(TO);
    clone = clone_object(EX_ARM + "leather_boots");
    clone->move(TO);
    
    // Put it on!
    command("wear all");
}
/*
* Function name: sell fish
* Description:   Pub owner will pay 3 cc each for fishes.
*/
string
sell_fish()
{
    object *fishes;
    object clone;
    
    //
    // Quest code
    // The publican needs fish for his roasted fish breads 
    // and will pay 3 cc each for them. The fishes could be
    // any fishes from any domain but the 'small dead fish' is
    // provided within the startloc area. The first time any 
    // player will receive some quest experience points.
    //
    // Check if the player got any fishes at all.
    fishes = FIND_STR_IN_OBJECT("fishes", this_player());
    if (sizeof(fishes))
    {
        TO->command("say to " + OB_NAME(TP) +
            " Nice catch! It's a deal, I'll buy it from you.");
        fishes->move(TO);
        clone = MONEY_MAKE_CC(sizeof(fishes) * 3);
        clone->move(TO);
        TO->command("give copper coins to " + OB_NAME(TP));
        
        // Has the player already done this quest?
        if (TP->test_bit(HOBBIT_STARTLOC_DOMAIN,
                         HOBBIT_QBIT_GROUP, SELL_FISH_QBIT) == 0)
        {
            // No the player hasn't done this quest before
            TO->command("say to " + OB_NAME(TP) +
                " Now you know how to make some good money.");
            TP->add_exp_quest(SELL_FISH_QPOINTS);
            TP->set_bit(HOBBIT_QBIT_GROUP, SELL_FISH_QBIT);
            TO->command("smile encourag at " + OB_NAME(TP));
        }
        else // The player has already done this quest
        {
            TO->command("say to " + OB_NAME(TP) +
                " It is nice to make business with you as always.");
            TO->command("say to " + OB_NAME(TP) +
                " Keep up the good work!");
            TO->command("thumb " + OB_NAME(TP));
        }
        TO->command("emote drops the catch into a barrel " +
            "together with a handfull of salt.");
    }
    else // No fishes in the inventory of the player
    {
        TO->command("say to " + OB_NAME(TP) +
            " Are you trying to be funny? You got no fishes!");
        TO->command("pat " + OB_NAME(TP));
    }
    return "";
}

