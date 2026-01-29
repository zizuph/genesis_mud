/*
 * /d/Shire/bree/rooms/town/stable/npc/stable_master.c
 *
 * The Stable Master of Bree
 * Inspired by Deagol's MM stable master
 * By Palmer
 * Date December 2002
 *
 * Notes:
 *   To get a list of people who rented that day type "renters"
 *
 *   If you update a room with a steed in it, be sure the horse is not wearing
 *   a saddlebag. The saddlebag gets destructed with the horse.
 *
 * ChangeLog
 * Palmer - 08 April 2004 - Added gnomes to pony rider list
 * Finwe - disabled Renters mapping because of long reboots. Checks to see if
 *         player has BREE_HORSE prop set now. 
 */

inherit "/d/Shire/std/monster";
inherit "/std/act/action";
inherit "/std/act/chat";
inherit "/lib/trade";

#include <cmdparse.h>
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <money.h>
#include <const.h>

#include "/d/Shire/sys/defs.h"
#include "../bree_stables.h"

#define FEE_PRICE 86400      /* 50 platinum one-time fee*/
#define RENTAL_PRICE 1728    /*  1 platinum rental fee*/
#define QUEST_NAME "horse"
#define BREE_HORSE  "_my_horse"

/* Function prototypes */
public void add_acts();

/* Globals */
object Steed;
//mapping Renters = ([ ]);
mapping Steed_owners = ([ ]);
int Begin_time = 0;  // Time person starts quest

public void
create_shire_monster()
{
    ::create_shire_monster();

    set_name(({"keleren", "stable master", "master"}));
    set_adj("tall");
    set_living_name("keleren");
    set_race_name("human");
    set_title("Stable Master of Bree");
    set_long("The stable master of Bree. This tall yellow-haired man is " +
       "certainly one of the Rohirrim, master horsemen of Rohan. He's " +
       "tanned and muscular, having taken care of the horses stabled here. " +
       "His job is to be sure the animals in the stable are cleaned, fed, " +
       "and in good shape.\n");

    set_base_stat(SS_STR, 110);
    set_base_stat(SS_DEX, 99);
    set_base_stat(SS_CON, 100);
    set_base_stat(SS_INT, 75);
    set_base_stat(SS_WIS, 70);
    set_base_stat(SS_DIS, 100);

    set_skill(SS_DEFENCE, 200);
    set_skill(SS_PARRY, 200);
    set_skill(SS_RIDING, 300);
    set_alignment(0);
    remove_prop(NPC_M_NO_ACCEPT_GIVE);

    setuid();
    seteuid(getuid());

    config_default_trade();
    Steed_owners = restore_map(BREE_STABLES_LOG_DIR + "steed_owners");
    add_ask(({"ferny", "bill ferny"}) ,VBFC_ME("explain_ferny"));
    add_ask(({"rider", "destination"}) ,VBFC_ME("explain_rider"));
    add_ask(({"horses", "horse", "pony", "ponies"}) ,VBFC_ME("explain_horse"));
    add_ask(({"black horse", "lost", "lost horse", "task", "help", "quest"}),
        VBFC_ME("give_task"));
    add_ask(({"jokes", "horse jokes", "horse joke", "joke"}),
        VBFC_ME("tell_joke"));
    add_acts();
}


/*
  Name: lead_horse
  Desc: Force player to lead steed.

  Args: object - player
  Returns:

*/

public void
lead_horse(object o)
{
    o->command("mount steed");
    o->command("hglance");
    o->command("automount");
    o->command("autodismount");
}



/*
  Name: rent_horse
  Desc: Allows player to rent horse if they have payed the initial fee.

  Args: string - description of horse in corral
  Returns: int - 1

*/

public int
rent_horse(string str)
{
    object      rider, *horses, scroll;
    int         animal_handle, riding, *money;
    string      player, race, horse_type, *desc;

    player = TP->query_real_name();

    if (!CAN_SEE_IN_ROOM(TO) || !CAN_SEE(TO, TP))
    {
        command("gasp");
        command("say Who's there?!");
        return 1;
    }

    // Sanity check in case a player pays fee then becomes goblin later
    race = TP->query_race();

    if(race == "goblin")
        {
        command("say to " + player + " Goblins can't ride horses or ponies.");
        command("gesture dismis" + player);
        return 1;
    }

    animal_handle = TP->query_skill(105);
    riding = TP->query_skill(112);

    if (animal_handle < 30)
    {
        command("say to " + player +
            " You can't handle my steeds. Get some training first.\n");
        return 1;
    }

    if (riding < 28)
    {
        command("say to " + player +
            " You don't know how to ride. Get some training first.\n");
        return 1;
    }


    horses=FIND_STR_IN_OBJECT(str, find_object(BREE_STABLES_DIR + "corral"));

    if (sizeof(horses) == 0)
    {
        command("say I don't have a steed that matches that description. " +
                "Take a better look in the corral.");
        return 1;
    }

    desc = explode(str, " ");
    
    if (sizeof(desc) == 3)
        horse_type = desc[2];
    else
        horse_type = str;
    
    /*
    if (str != "horse" && str != "pony")
    {
        if (sizeof(horse_type) <3)
        {
            command("say Can you give me a better description please?\n");
            return 1;
        }
    }
    */
    
    if(race == "kender" || race=="gnome" || race == "dwarf" || race == "hobbit")
    {
        if(horse_type == "horse")
        {
            command("say to " + player + " A pony would be more your size.\n");
            return 1;
        }
    }

    if(race == "human" || race =="elf" || race=="minotaur")
    {
        if(horse_type == "pony")
        {
            command("say to " + player +" A horse would be more your size.\n");
            return 1;
        }
    }

//    if (Renters[player])
    if (TP->query_prop(BREE_HORSE))
    {
        command("frown confuse " + player + "");
        command("say to " + player + " You've already rented from me today. " +
                "Don't tell me you lost your steed!\n");
        return 1;
    }

    if (!CAN_SEE_IN_ROOM(TO) || !CAN_SEE(TO, TP))
    {
        command("say Fine, I'm hiding too.");
        command("emote pulls a bag over his head.");
        return 1;
    }

    if (!Steed_owners[player])
    {
            command("say to " + player + " You didn't pay me the initial fee "+
                    "yet, so I can't rent you a steed. Read the sign.");
            return 1;
    }
    
    if (str == "horse" || str == "pony")
    {
        command("say to " + player + " Please be more specific. I have many horses and ponies.\n");
        return 1;
    }

    money = pay(RENTAL_PRICE, TP);
    if (sizeof(money) == 1)
    {
        command("say to " + player + " Can't afford it hmmm? " +
                "Well thats my price, you won't find a better deal.");
        return 1;
    }

    command("say to " + player + " I'll be back with your " + str +
        " in a moment, wait here please.");
    command("east");

    // Feed and water horse
    horses[0]->stuff_soak();
    horses[0]->add_prop("__owner", player);
    set_alarm(5.7, 0.0, &command("lead " + str));
    set_alarm(6.5, 0.0, &command("west"));
    set_alarm(7.7, 0.0, &command("unlead " + str));
    set_alarm(8.0, 0.0, &command("emote drapes a saddle over the " +
        str + "."));
    set_alarm(8.2, 0.0, &command("say to " + player + " Here is your steed."));

    // Keep a reference to the players horse. Makes mounting and leading
    // easier when there are more than one in the room.
    TP->add_prop(BREE_HORSE, horses[0]);

    scroll = clone_object(BREE_STABLES_OBJ_DIR + "manual_scroll");
    scroll->move(TO);
    set_alarm(8.3, 0.0, &command("say to " + player + " Read this scroll. " +
        "It contains important information about your steed."));
    set_alarm(8.4, 0.0, &command("give scroll to " + player));
    // Force player to lead the horse so nobody steals it.
    // We pass a pointer because this_player fails sometimes with set_alarm
    rider = TP;
    set_alarm(8.5, 0.0, &lead_horse(rider));
    // Keep stable full
    find_object(BREE_STABLES_DIR + "corral")->add_horse(1);


    // Lets add the time() for debugging purposes 12/21/2002
//    Renters[player] = time();
    return 1;
}


/*
  Name: clear_list
  Desc: Deletes player from list of renters after returning a steed.

  Args: string - Player's name
  Returns:

*/

public public void
clear_list(string player)
{
/*
    if (Renters[player])
    {
        Renters = m_delete(Renters, player);
    }
*/
    if (TP->query_prop(BREE_HORSE))
    {
        player->remove_prop(BREE_HORSE);
    }
}


/*
  Name: stable_horse
  Desc: Take the player's steed back to the corral.

  Args: string - horse's description
  Returns: int - 0/fail 1/success

*/

public int
stable_horse(string str)
{
    string player;

    player = TP->query_real_name();

    Steed = present("steed", environment(this_object()));

    if (str != "horse" && str != "steed" && str!= "pony")
    {
        notify_fail("Stable what? Maybe a horse or pony?\n");
        return 0;
    }
    if (!Steed)
    {
        command("say to " + player + " Go get a horse and I'll be glad to " +
                "stable it.");
        command("chuckle amusedly");
        return 1;
    }
    if (Steed->query_has_riders())
    {
        command("say to " + player + " You'll need to dismount first.");
        return 1;
    }
    if (Steed->query_leader())
    {
        command("say to " + player + " You're leading the horse, I cannot " +
                "stable it. Please, unlead it first.");
        return 1;
    }
    command("say to " + player + " Let me relieve you of your " +
                "steed.");
/*
    if (Renters[player])
    {
        Renters = m_delete(Renters, player);
    }
*/
write (TP->query_prop(BREE_HORSE));

    if (TP->query_prop(BREE_HORSE))
    {
        player->remove_prop(BREE_HORSE);
    }

    set_alarm(1.5, 0.0, &command("lead " + str));
    set_alarm(2.0, 0.0, &command("east"));
    set_alarm(2.1, 0.0, &command("unlead " + str));
    set_alarm(3.0, 0.0, &command("west"));
    return 1;
}


/*
  Name: add_acts
  Desc: Make me chat.

  Args:
  Returns:

*/

public void
add_acts()
{
    set_act_time(15);
    add_act("emote says: I know horse jokes.");
    add_act("emote says: That Ferny is trouble I tell you. " +
        "I'd watch that one.");
    add_act("emote says: That was my last black horse. Where " +
            "did that fool ride off to?");
    add_act("emote says: If I weren't so busy I'd be out looking " +
            "for that black horse.");
}


/*
  Name: add_introduced
  Desc: Introduce myself when someone intros.

  Args: string - Player's name
  Returns:

*/

public void
add_introduced(string str)
{
    if (!interactive(TP) || TP->query_met(query_name()))
        return;

    command("introduce me to " + TP->query_real_name() + "");
}


/*
  Name: enter_env
  Desc: Initialize mappings when this object is created

  Args: object - to, from
  Returns:

*/

public void
enter_env(object to, object from)
{
    ::enter_env(to, from);
/*
    if (!mappingp(Renters))
    {
        Renters = ([ ]);
    }
    if (!mappingp(Steed_owners))
    {
        Steed_owners = ([ ]);
    }
*/
}


/*
  Name: pay_fee
  Desc: Allows player to pay initial fee. After they pay the one-time
        fee they can rent one steed per Armageddon

  Args: string - "fee"
  Returns: int - 0/fail 1/succeed

*/

public int
pay_fee(string str)
{
    int *money;
    string player;
    string race;

    race = TP->query_race();
    if(race == "goblin")
    {
        command("say to " + player + " Goblins can't ride horses or ponies.");
        command("gesture dismis" + player);
        return 1;
    }
    player = TP->query_real_name();

    if (str != "fee")
    {
        notify_fail("Pay what? A fee?\n");
        return 0;
    }

    if (!CAN_SEE_IN_ROOM(TO) || !CAN_SEE(TO, TP))
    {
        notify_fail("Do you want to pay a fee? Reveal yourself.\n");
        return 0;
    }

    if (Steed_owners[TP->query_real_name()])
    {
        command("say to " + player + " You've already paid me. Would " +
                "you like to rent a horse or pony?");
        return 1;
    }

    money = pay(FEE_PRICE, TP);
    if (sizeof(money) == 1)
    {
        command("say to " + player + " When you have enough money, I'll " +
                "be happy to help you.");
        return 1;
    }

    Steed_owners[TP->query_real_name()] = 1;
    save_map(Steed_owners, BREE_STABLES_LOG_DIR + "steed_owners");
    say(QCTNAME(TP) + " pays the fee.\n");
    write("You pay the fee.\n");
    command("say to " + player + " Thank you. From now on " +
            "I can rent you a horse whenever you want.");
    return 1;
}


/*
  Name: explain_ferny
  Desc: Talk about Ferny when asked

  Args:
  Returns:

*/

string
explain_ferny()
{
    command("say Ferny.");
    command("scowl");
    command("say You can usually find him in the Prancing Pony.");
    command("say He's up to no good if you ask me.");
    return "";
}


/*
  Name: explain_horse
  Desc: Talk about horses when asked.

  Args:
  Returns:

*/

public string
explain_horse()
{
    command("say I rent horses. And ponies for the little folk.");
    return "";
}


/*
  Name: explain_rider
  Desc: Talk about the rider for the quest when asked

  Args:
  Returns:

*/

string
explain_rider()
{
    command("say If I knew where the rider went, would I be asking you to " +
        "search for him?");
    command("chuckle");
    return "";
}


/*
  Name: tell_joke
  Desc: Tell a joke when asked

  Args:
  Returns:

*/

public string
tell_joke()
{
    if (random(2) == 1)
    {
        command("say A horse walks into the Prancing Pony.");
        command("say Barliman looks at the horse and says...");
        command("say Why the long face?");
        return "";
    }
    command("say I had a horse once that was afraid of daylight...");
    command("say She was a real night mare.");
    return "";

}

/*=====   Quest ===== */


/*
  Name: test_horse_quest
  Desc: If someone kills the black horse and they retrieve the saddle
        tell them I want the horse.

  Args: object - player
  Returns:

*/

public void
test_horse_quest(object player)
{
    command("emote examines the saddle closely.");
    command("say Ah, yes, this is from the black horse I rented out.");
    command("frown");
    command("sigh annoyedly");

    command("hmm");
    command("say But where is the horse?");
    command("say Who gave you this??");
    command("glare");
    return;
}


/*
  Name: reset_quest_timer
  Desc: Reset the timer for the quest. He only gives out the quest to one
        player at a time. See give_task()

  Args:
  Returns:

*/

public void
reset_quest_timer()
{
    Begin_time = 0;
}


/*
  Name: give_task
  Desc: Give the quest to a player

  Args:
  Returns:

*/

public string
give_task()
{
    int align;
    object uruk, orc1, orc2, horse;
    int now;

    if (TP->query_prop("_horse_quest"))
    {
        command("chuckle annoy" + TP->query_name());
        command("say Please go find my black horse!");
        return "";
    }

    if (Begin_time != 0)
    {
        now = time();
        if ((now - Begin_time) < 3600)
        {
            command("say Someone is helping me now. If you check back in a " +
                    "while, I may be able to use your help.");
            return "";
        }
    }

    // Only give quest to good aligned. See Ferny in the Prancing
    // Pony about the evil quest.
    if (!CHECK_QUEST(TP, QUEST_NAME))
    {
        align = TP->query_alignment();
        if (align < 1)
        {
            command ("say I don't need any help from you. You're probably " +
                    "one of Ferny's friends.");
            return "";
        }

        command("say I rented out the last black horse I had.");
        command("sigh miserably");
        command("say The rider was supposed to be back by now, but " +
        "I feel something has gone awry. If you can bring " +
        "back that horse I'd be very grateful.");
        TP->add_prop("_horse_quest", 1);
        Begin_time = time();
        uruk = clone_object(BREE_STABLES_NPC_DIR + "uruk_leader");
        return "";
    }
    else
    {
        command("say I don't need any help right now, thank you.");
        return "";
    }
}


/*
  Name: failed_give
  Desc: Give things back to players if they are handed to me

  Args: object - item, player
  Returns:

*/

public void
failed_give(object obj,object from)
{
    command("say No thank you.");
    write(TO->query_The_name(from)+" gives it back to you.\n");
    obj->move(from);
}



/*
  Name: enter_inv
  Desc: Check to see if someone gave me the saddle from the black horse

  Args: object - saddle, player
  Returns:

*/

public void
enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);
    if (!living(from))
        return;
    if (obj->id("_horse_quest_saddle_"))
        set_alarm(2.0,0.0, &test_horse_quest(from));
    else
        set_alarm(1.5,0.0, &failed_give(obj,from));
}


/*
  Name: attacked_by
  Desc: Jump over corral fence to avoid attack. I'm far too important
        to be killed.

  Args: object - player who attacked
  Returns:

*/

public void
attacked_by(object attacker)
{
    TO->command("scowl");
    set_m_in("arrives climbing over the corral fence");
    set_m_out("leaves climbing over the corral fence");
    TO->command("east");
    attacker->stop_fight(TO);
    TO->stop_fight(attacker);
    set_alarm(120.0, 0.0, &command("west"));
}


/*
  Name: list_renters
  Desc: Give wizard a list of renters for the day.

  Args:
  Returns: int 0/fail 1/succeed

*/


public int
list_renters()
{
    if (TP->query_wiz_level())
    {
//        dump_mapping(Renters, "\t");
        return 1;
    }
    return 0;
}


public void
init_living()
{
    ::init_living();

    add_action(stable_horse, "stable");
    add_action(rent_horse, "rent");
    add_action(pay_fee, "pay");
//    add_action(list_renters, "renters");
}
