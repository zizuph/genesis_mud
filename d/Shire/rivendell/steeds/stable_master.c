/*
 /d/Shire/rivendell/steeds/stable_master.c

 The Stable Master of Imladris
 He helps you choose a horse
 By Palmer
 Date January 2003

 To delete a player's horse and move the horse's name back into the available pool:
  Call ridlin remove_horse_name <player's name>


 To add a new horse:
  add <name> <meaning in English>

 To remove a name:
  remove <name>

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

// Fee for new horse. First is free.
#define FEE 172800

/* Function prototypes */
public string list_adjectives();
public string list_names();
public string list_genders();
public int check_valid_owner();
public void remove_horse_name(string player);
public string get_horse_name();
public void restore_horse_data();
public int add_name(string str);

/* Globals */
mapping Steed_owners = ([]);
mapping Horse_data = ([]);
mapping Horse_names = ([]);
string *adjectives1, *adjectives2, *horse_names;

void
create_shire_monster()
{
    ::create_shire_monster();

    setuid();
    seteuid(getuid());

    set_name(({"ridlin", "stable master", "master"}));
    set_adj("tall");
    set_living_name("ridlin");
    set_race_name("elf");
    set_title("Stable Master of Imladris");
    set_long("The stable master of Imladris. He looks proud and ageless but " +
        "still full of mirth and energy. His job is to help you choose a " +
        "horse to your liking. He also makes sure the horses in the " +
        "stables are cleaned, fed, and in good shape.\n");

    set_base_stat(SS_STR, 100);
    set_base_stat(SS_DEX, 99);
    set_base_stat(SS_CON, 100);
    set_base_stat(SS_INT, 75);
    set_base_stat(SS_WIS, 70);
    set_base_stat(SS_DIS, 100);

    set_skill(SS_DEFENCE, 200);
    set_skill(SS_PARRY, 200);
    set_skill(SS_RIDING, 300);
    set_alignment(1200);
    remove_prop(NPC_M_NO_ACCEPT_GIVE);

    Steed_owners = restore_map("/d/Shire/rivendell/steeds/steed_owners");
    restore_horse_data();
    config_default_trade();
    add_ask(({"fee", "pay", "pay fee", "pay a fee"}) ,VBFC_ME("explain_fee"));
    add_ask(({"horses", "horse"}) ,VBFC_ME("explain_horse"));
    add_ask(({"list of adjectives", "adjective list", "adjectives", "adjective"}) , 
        VBFC_ME("list_adjectives"));
    add_ask(({"name list", "list of names", "horse names", "name", "names"}) ,
        VBFC_ME("list_names"));
    add_ask(({"gender", "genders"}) ,VBFC_ME("list_genders"));
}



/*
save_horse_data()
Save mapping of available horse names and adjectives

Map saved as players name with elements as follows ({<adjective1>,<adjective2>, 
<gender> <name of horse>})

Arguments: None
Returns:   None

*/
public void
save_horse_data()
{
    save_map(Horse_data, "/d/Shire/rivendell/steeds/horse_data");
}



/*
save_horse_names()
Save mapping of all horse names and their meanings
Map saved as players name meaning as value

Arguments: None
Returns:   None

*/
public void
save_horse_names()
{
    save_map(Horse_names, "/d/Shire/rivendell/steeds/horse_names");
}




/*
save_owner_data()
Save mapping of horse owners

Arguments: None
Returns:   None

*/
public void
save_owner_data()
{
    save_map(Steed_owners, "/d/Shire/rivendell/steeds/steed_owners");
}

/*

restore_horse_names()
Retrieve saved mapping of all (owned and unowned) horse names and meanings

Arguments: None
Returns:   None

*/

public void
restore_horse_names()
{
    Horse_names = restore_map("/d/Shire/rivendell/steeds/horse_names");
}

/*
restore_horse_data()
Retrieve saved mapping of available horse names and adjectives

Arguments: None
Returns:   None

*/

public void
restore_horse_data()
{
    Horse_data = restore_map("/d/Shire/rivendell/steeds/horse_data");
    adjectives1 = Horse_data["adj1"];
    adjectives2 = Horse_data["adj2"];
    horse_names = Horse_data["names"];
}

/*
get_horse_name()
Get player's horse name from mapping

Arguments: None
Returns:   string - Name of horse

*/
public string
get_horse_name()
{
    string *data, hname;
    data = Steed_owners[TP->query_real_name()];
    if (sizeof(data) != 0)
    {
        hname = data[3];
        return hname;
    }
    else
    {
        return "";
    }
}


/*
remove_horse_name()
Remove player's horse name and add back to available names

Arguments: string - Player's name

*/
public void
remove_horse_name(string player)
{
    string hname;

    hname = capitalize(get_horse_name());
    
    //added for the cases that a Noldor leaves the guild    
    if (hname=="") {return;}
    //without (ever?) having had a horse. 
    //(leaving the guild calls this routine. So this is
    //to check if the player had a horse to begin with.
    //if not (hname=="") the routine is exited. 
    //As it was, the empty string would become
    //one of the names looking like this
    //Ridlin says:, which means, 0  .
    
    // Mayari 04-19-2020    
    
    horse_names = Horse_data["names"];
    // Add name back to horse_data
    horse_names += ({hname});
    Horse_data["names"] = horse_names;
    save_horse_data();

    // Remove owner's horse
    Steed_owners = m_delete(Steed_owners, player);
    save_owner_data();
}



/*
check_valid_owner()
See if player already owns a horse.

Arguments: None
Returns:   1 if player owns horse - 0 if player does not own a horse

*/
public int
check_valid_owner()
{
    string player;
    player = TP->query_real_name();

    if (Steed_owners[player])
        return 1;
    else
        return 0;
}


/* explain_fee()
Response to "ask fee"

*/
string
explain_fee()
{
    command("say You may choose a new horse, but you will need to pay a " +
        "fee of 100 platinum coins.");
    return "";
}


/* explain_horse()
Response to "ask horse"

*/
string
explain_horse()
{
    command("say I can help you choose a horse. Read the poster for help.");
    return "";
}

/*
list_adjectives()
Response to "ask adjectives"
Lists available adjectives for horses.

*/
string
list_adjectives()
{
    string list1, list2;

    list1 = implode(adjectives1, ", ");
    list2 = implode(adjectives2, ", ");
    command("say The list of first adjectives is " + list1 + ".\n");
    command("say The list of second adjectives is " + list2 + ".\n");
    return "";
}

/*
add_name()
Command to add a new horse name and meaning in English.
Only works for wizards.

add <name> <meaning in English>

Arguments: string - name & meaning
*/
public int
add_name(string str)
{
    string *sentence, name, *temp, meaning;

    if (!TP->query_wiz_level())
        return 0;

    if (!stringp(str))
    {
        command("say Syntax: add <name> <meaning>");
        return 1;
    }

    sentence = explode(str, " ");
    if (sizeof(sentence) < 2)
    {
        command("say Syntax: add <name> <meaning>");
        return 1;
    }
    restore_horse_data();
    restore_horse_names();
    name = capitalize(sentence[0]);
    temp = sentence[1..sizeof(sentence)];
    meaning = implode(temp, " ");
    Horse_names[name] = meaning;
    // Add to master list of names (owned and un-owned):
    save_horse_names();
    // Add to available pool of names (un-owned):
    Horse_data["names"] += ({name});
    save_horse_data();
    return 1;
}


/*
remove_name()
Command to remove horse.
Only works for wizards.

remove <name>

Arguments: string - name
*/

public int
remove_name(string str)
{
    string *sentence, name, meaning, player;
    player = TP->query_real_name();
    if (!TP->query_wiz_level())
        return 0;

    if (!stringp(str))
    {
        command("say Syntax: remove <name>");
        return 1;
    }

    Horse_names = restore_map("/d/Shire/rivendell/steeds/horse_names");
    name = capitalize(str);
    Horse_names = m_delete(Horse_names, name);
    save_horse_names();
    Horse_data["names"] -= ({name});
    save_horse_data();
    return 1;
}

/*
list_names()
List available horse names and their meanings in English
in response to "ask names".

Arguments: None
Returns:   None
*/

public string
list_names()
{
    int i, nbr_horses;
    string name, *horses, meaning;
    mapping horse_names;

    horse_names = restore_map("/d/Shire/rivendell/steeds/horse_names");
    horses = Horse_data["names"];
    nbr_horses = sizeof(horses);
    command("say I have horses with the following names:\n");
    i = 0;
    while (i < nbr_horses)
    {
        name = horses[i];
        meaning = horse_names[name];
        command("say " + name + ", which means, " + meaning + ".");
        i++;
    }
    return "";
}

/*
list_genders()
Response to "ask genders"

*/
public string
list_genders()
{
    command("say I have male and female horses.");
    return "";
}


/*
choose_horse()
Command that allows you to choose horse. Also removes name
from available list of horse names.

 choose <adj1> <adj2> <gender> horse named <name>

Arguments: String - see example command above
Returns:   int
*/
int
choose_horse(string str)
{
    object *horses;
    string player, race;
    int animal_handle, riding;

    string adj1, adj2, name, gender;
    string *sentence;
    string *save_data;

    player = TP->query_real_name();

    race = TP->query_guild_name_race();

    if (!CAN_SEE_IN_ROOM(TO) || !CAN_SEE(TO, TP))
    {
        command("say Reveal yourself.");
        command("peer");
        return 1;
    }

    if(race != "Noldor of Imladris")
    {
        command("say to " + player + " My horses are for the Noldor.");
        command("gesture dismis" + player);
        return 1;
    }

    if (check_valid_owner() == 1)
    {
        command("say to " + player + " You already own a horse. Try " +
            "summoning it.");
        command("whisper " + player + " nosummon");
        command("say to " + player + " If you want a different horse, " +
            "you'll have to pay a fee.");
        return 1;
    }

    animal_handle = TP->query_skill(105);
    riding = TP->query_skill(112);

    if (animal_handle < 30)
    {
        command("say to " + player + " You can't handle my steeds. You need " +
            "more animal handling first.");
        return 1;
    }

    if (riding < 28)
    {
        command("say to " + player + " You don't know how to ride. You " +
            "need more riding skills first");
        return 1;
    }

    if (!stringp(str))
    {
        command("say Choose again. Read the poster, it should help you.");
        return 1;
    }

    sentence = explode(str, " "); // Break command line into array
    // choose glimmering white male horse named Hingil
    if (sizeof(sentence) != 6)
    {
        command("say Choose again. Read the poster, it should help you.");
        return 1;
    }


    adj1 = sentence[0];
    adj2 = sentence[1];
    gender = sentence[2];
    name = sentence[5];

    if (member_array(adj1, adjectives1) == -1)
    {
        command("say I don't have a horse with that first adjective. Please " +
            "read the plaque for more information.");
        return 1;
    }

        if (member_array(adj2, adjectives2) == -1)
    {
        command("say I don't have a horse with that second adjective. Please " +
            "read the plaque for more information.");
        return 1;
    }

    if (gender != "male" && gender != "female")
    {
        command("say I have no horse of the gender '" + gender + "'. Please " +
            "read the poster, it should help you.");
        return 1;
    }

    if (member_array(capitalize(name), horse_names) == -1)
    {
        command("say None of my horses has that name. Ask me about names " +
            "for names that are available. If you have suggestions for " +
            "new ones, use <idea> to submit your suggested name and the " +
            "meaning of the name.");
        return 1;
    }

    save_data = ({adj1, adj2, gender, name});

    // Remove horse's name from list of available names.
    horse_names -= ({capitalize(name)});
    Horse_data["names"] = horse_names;
    save_horse_data();


    // Command to select horse should be: choose <adjective1> <adjective2> <gender> horse named <horse's name>

    Steed_owners[TP->query_real_name()] = save_data;
    save_owner_data();


    command("say to " + player + " You may summon your horse now.");
    command("whisper " + player + " Use 'nosummon'");

    return 1;
}


/*
add_introduced()
Introduce myself to players when they introduce themselves.

Arguments: string - player's name
Returns:   None
*/
void
add_introduced(string str)
{
    if (!interactive(TP) || TP->query_met(query_name()))
        return;

    command("introduce me to " + TP->query_real_name() + "");
}

/*
pay_fee()
Pay fee if you want a new horse.

Arguments: string - "fee"
Returns:   None
*/
int
pay_fee(string str)
{
    int *money;
    string player, hname, race;

    player = TP->query_real_name();

    if (!CAN_SEE_IN_ROOM(TO) || !CAN_SEE(TO, TP))
    {
        command("say Do you want to pay a fee? Reveal yourself.");
        return 0;
    }

    race = TP->query_guild_name_race();
    if(race != "Noldor of Imladris")
    {
        command("say to " + player + " My horses are for the Noldor.");
        command("gesture dismis" + player);
        return 1;
    }

    if (str != "fee")
    {
        notify_fail("Pay what? A fee?\n");
        return 0;
    }

    if (check_valid_owner() == 1)
    {
        hname = get_horse_name();
        if (find_living(lower_case(hname)))
        {
            notify_fail("Your horse needs to be sent home before you can " +
            "new one. Use <nograze> to send it home.\n");
            return 0;
        }
        money = pay(FEE, TP);
        if (sizeof(money) == 1)
        {
            command("say to " + player + " When you have enough money, I'll " +
                    "be happy to help you.");
            return 1;
        }

        say(QCTNAME(TP) + " pays the fee.\n");
        write("You pay the fee.\n");
        command("say to " + player + " Thank you. You may now choose a new horse.");
        remove_horse_name(player); // Remove horse, add name back into available list.
        return 1;
    }
    else
    {
        command("say to " + player + " You don't need to pay a fee. You " +
            "may choose a horse.");
        return 1;
    }
}



/*
attacked_by()
Stop fight if player attacks.

Arguments: object - person attacking
Returns:   None

*/

void
attacked_by(object attacker)
{
    TO->command("frown");
    TO->command("emote mumbles a prayer.");
    attacker->stop_fight(TO);
    TO->stop_fight(attacker);
}

void
init_living()
{
    ::init_living();
    add_action(choose_horse, "choose");
    add_action(pay_fee, "pay");
    add_action(add_name, "add");
    add_action(remove_name, "remove");
}