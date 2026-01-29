/*
 * Originally coded by Palmer on December 2002
 * Updated for Faerun by Finwe, October 2016
 */

#pragma strict_types
#pragma save_binary

#include "/d/Faerun/defs.h"
#include <cmdparse.h>
#include <const.h>
#include <filter_funs.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <wa_types.h>

inherit FAERUN_NPC_BASE;
inherit "/std/act/action";
inherit "/std/act/chat";
inherit "/lib/trade";

#define FEE_PRICE       172800  /* 100 plats, one-time fee */
#define RENTAL_PRICE    3456    /*   2 plats each-time fee */
#define REHIRE_PRICE    96400   /* 50 plats, to rehire steed if not returned */

#define STABLES_DIR		    "/d/Faerun/thornhold/"
#define D_STABLES_DIR		"/d/Faerun/stables/" /* domain dir where main code sits */
#define STABLES_ROOM_DIR	"/d/Faerun/thornhold/rooms/"
#define STABLES_OBJ_DIR	    STABLES_DIR + "obj/"
#define STABLES_NPC_DIR	    STABLES_DIR + "npcs/"
#define STABLES_STEED_DIR	D_STABLES_DIR + "steeds/"
#define STABLES_LOG_DIR	    STABLES_DIR + "log/"
#define RIDER_OBJECT        D_STABLES_DIR + "rider_object"
#define STABLE_MASTER	    "/d/Faerun/thornhold/npcs/stablemaster.c"

// directions the npc goes into and out of the corral
#define ENTER_CORRAL    "east"
#define EXIT_CORRAL     "west"

/* Function prototypes */

/* Globals */
object Steed;
mapping Renters = ([ ]);
mapping Steed_owners = ([ ]);

public void
create_monster()
{
    ::create_monster();

    set_name(({"torvil"}));
    add_name(({"jassen", "stablemaster", "stable master"}));
    set_living_name("jassen");
    set_title("Torvil Jassen, Stablemaster");
    set_adj("stocky");
    add_adj("muscular");
    set_race_name("human");
    set_long("This is Torvil Jassen, the stablemaster. He is a master of horses, and suntanned from all the time he's been out rounding them up. His dark hair is clipped short and his steel blue eyes sparkle with life.\n");
    set_size_descs("tall", "of normal width");

    set_base_stat(SS_STR, 120);
    set_base_stat(SS_DEX, 90);
    set_base_stat(SS_CON, 100);
    set_base_stat(SS_INT, 60);
    set_base_stat(SS_WIS, 80);
    set_base_stat(SS_DIS, 80);

    set_skill(SS_DEFENCE, 200);
    set_skill(SS_PARRY, 200);
    set_skill(SS_RIDING, 300);
    set_alignment(0);
    // remove_prop(NPC_M_NO_ACCEPT_GIVE);

    setuid();
    seteuid(getuid());

    config_default_trade();
    Steed_owners = restore_map(STABLES_LOG_DIR + 
        "steed_owners");
    add_ask(({"horses", "horse", "pony", "ponies"}) ,VBFC_ME("explain_horse"));
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
        command("say What evil magic is this?!? Reveal yourself!!!");
        return 1;
    }

    // Sanity check in case a player pays fee then becomes goblin later
    race = TP->query_race();

    if(race == "goblin" || race == "minotaur" || race == "ogre" || race == "orc")
    {
        command("say to " + player + " I don't rent my animals to goblins, " +
            "ogres, orcs, or minotaurs. They tend to eat them.");
        command("gesture dismis" + player);
        return 1;
    }

    animal_handle = TP->query_skill(105);
    riding = TP->query_skill(112);

    if (animal_handle < 30)
    {
        command("say to " + player + " You can't handle my steeds. " +
            "Get some training first.\n");
        return 1;
    }

    if (riding < 30)
    {
        command("say to " + player + " You don't know how to ride. " + 
            "Get some training first.\n");
        return 1;
    }

    horses = FIND_STR_IN_OBJECT(str, find_object(STABLES_ROOM_DIR + "corral"));

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
    
    if(race == "kender" || race=="gnome" || race == "dwarf" || race == "hobbit")
    {
        if(horse_type == "horse")
        {
            command("say to " + player + " A pony would be more your size.\n");
            return 1;
        }
    }

    if(race == "human" || race =="elf" || race=="minotaur" )
    {
        if(horse_type == "pony")
        {
            command("say to " + player +" A horse would be more your size.\n");
            return 1;
        }
    }

    if ((time () - Renters[player]) < 86400)  // 24 hours
    //    if(TP->query_prop("_my_horse"))
    {
        command("frown confuse " + player + "");
        command("say to " + player + " You've already rented from me today. " +
                "Don't tell me you lost your steed! You will have to wait " +
                "until tomorrow before I rent you another steed.\n");
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

// Let's go get the steed now
    command(ENTER_CORRAL);

    // Feed and water horse
    horses[0]->stuff_soak();
    horses[0]->add_prop("__owner", player);

    set_alarm(5.7, 0.0, &command("lead " + str));
    set_alarm(6.5, 0.0, &command(EXIT_CORRAL));
    set_alarm(7.7, 0.0, &command("unlead " + str));
    set_alarm(8.0, 0.0, &command("emote pats the " +
        str + "lovingly."));

    set_alarm(8.1, 0.0, &command("say to " + player + " Here is your steed."));
    set_alarm(8.1, 0.0, &command("say to " + player + " After you mount your " + 
        str + ", type <hhelp> for more information,"));
    set_alarm(8.1, 0.0, &command("emote updates the sign."));

    // Keep a reference to the players horse. Makes mounting and leading
    // easier when there are more than one in the room.
    TP->add_prop("_my_horse", horses[0]);

    // Force player to lead the horse so nobody steals it.
    rider = TP;
    set_alarm(8.5, 0.0, &lead_horse(rider));
    // Keep stable full
    find_object(    STABLES_DIR + "corral")->add_horse(1);


    // Lets add the time() for debugging purposes 12/21/2002
    Renters[player] = time();
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
    if (Renters[player])
    {
        Renters = m_delete(Renters, player);
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
    command("say to " + player + " Let me relieve you of your steed.");

    if (Renters[player])
    {
        Renters = m_delete(Renters, player);
    }

    set_alarm(1.5, 0.0, &command("lead " + str));
    set_alarm(2.0, 0.0, &command(ENTER_CORRAL));
    set_alarm(2.1, 0.0, &command("unlead " + str));
    set_alarm(3.0, 0.0, &command(EXIT_CORRAL));
    set_alarm(3.0, 0.0, &command("emote updates the sign."));
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
    if (!interactive(TP) || TP->query_met(query_real_name()))
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

    if (!mappingp(Renters))
    {
        Renters = ([ ]);
    }
    if (!mappingp(Steed_owners))
    {
        Steed_owners = ([ ]);
    }
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
    save_map(Steed_owners,     STABLES_LOG_DIR + "steed_owners");
    say(QCTNAME(TP) + " pays the fee.\n");
    write("You pay the fee.\n");
    command("say to " + player + " Thank you. From now on " +
            "I can rent you a horse whenever you want.");
    return 1;
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
    command("say I rent horses, and ponies for the little folk.");
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
    switch(random(10))
    {
        case 0:
        {
            command("say A horse walks into the Prancing Pony.");
            command("say Barliman looks at the horse and says...");
            command("say Why the long face?");
            break;
        }
        case 1:
        {
            command("say I had a horse once that was afraid of daylight...");
            command("say She was a real night mare.");
            break;
        }
        case 2:
        {
            command("say A weather-beaten traveller went into the Prancing " +
                "Pony, had a beer, and walked outside and found his horse " +
                "has been stolen. He walked back into the bar, angrily " +
                "shouted, 'Which one of you low-life bandits stole my horse?' " +
                "No one answered. 'All right, I'm gonna have one more beer " +
                "and if my horse ain't outside by the time I finish, " +
                "I'm gonna do what I did in Gondor.'");
            command("say He drank another beer, walked outside, and " +
                "his horse was back. So he got on it and was ready to " +
                "ride out away when Barliman walked out of the bar and " +
                "asked, 'Say traveller, what happened in Gondor?' The " +
                "traveller turned to him, and said, 'I had to bloody walk " +
                "home.'");
            break;
        }
        case 3:
        {
            command("say How did the traveller ride into town on Friday, " +
                "stay for three days, and ride out on Friday?");
            command("say His horse's name was Friday!");
            break;
        }
        case 4:
        {
            command("say How do you make a slow horse fast?");
            command("say Stop feeding it!");
            break;
        }
        case 5:
        {
            command("say What did the horse say when it fell?");
            command("say I've fallen and I can't giddyup!");
            break;
        }
        case 6:
        {
            command("say What do you call a horse that lives next door?");
            command("say A neigh-bor!");
            break;
        }
        case 7:
        {
            command("say Where do horses go when they're sick?");
            command("say The horsepital!");
            break;
        }
        case 8:
        {
            command("say Why did the horse eat with its mouth open?");
            command("say Because it had bad stable manners!");
            break;
        }
        case 9:
        {
            command("say Why did the pony have to gargle?");
            command("say Because it was a little hoarse!");
            break;
        }        
    }



// what Keleran does after the joke
    switch(random(5))
    {
        case 0:
        {
            command("laugh uproariously");
            break;
        }
        case 1:
        {
            command("cackle");
            command("say Wanna hear another?");
            break;
        }
        case 2:
        {
            command("emote laughs hard while slapping his knee.");
            break;
        }
        case 3:
        {   command("say That was a good one!");
            break;
        }
        case 4:
        {   command("say That was my father's favorite joke!");
            break;
        }
    }
        
    
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
  Name: failed_give
  Desc: Give things back to players if they are handed to me

  Args: object - item, player
  Returns:

*/

public void
failed_give(object obj,object from)
{
    command("say No, thank you.");
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
        dump_mapping(Renters, "\t");
        return 1;
    }
    return 0;
}


public void
init_living()
{
    ::init_living();

    add_action(stable_horse, "stable");
    add_action(stable_horse, "return");
    add_action(rent_horse, "rent");
    add_action(rent_horse, "hire");
    add_action(pay_fee, "pay");
    add_action(list_renters, "renters");
}
