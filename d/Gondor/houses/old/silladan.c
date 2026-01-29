/*
 * Silladan - Real Estate Agent
 *
 * Handles the buying and selling of houses
 *
 * Varian - March, 2020
 */

inherit "/std/monster";
inherit "/std/act/action";
inherit "/std/act/chat";
inherit "/lib/trade";

#include <cmdparse.h>
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <money.h>
#include <const.h>
#include "/d/Gondor/met_defs.h"
#include "defs.h"

#define FEE 100

public string list_adjectives();
public string list_names();
public string list_genders();
public int check_valid_owner();
public void remove_house_name(string player);
public string get_house_name();
public void restore_house_data();
public int add_name(string str);

mapping Deed_owners = ([]);
mapping House_data = ([]);
mapping House_names = ([]);
string *adjectives1, *adjectives2, *house_names;

void
create_monster()
{

    setuid();
    seteuid(getuid());

    set_name(({"silladan", "_real_estate_agent", "agent"}));
    set_living_name("silladan");
    set_adj("slender");
    add_adj("beautiful");
    set_race_name("elf");
    set_title("Real Estate Agent of Genesis");
    set_long("This beautiful looking elf is the real estate " +
        "agent of Genesis. If you want to buy property in " +
        "Genesis, you will have to deal with her!\n");
    set_gender(G_FEMALE);

    set_base_stat(SS_STR, 50);
    set_base_stat(SS_DEX, 120);
    set_base_stat(SS_CON, 50);
    set_base_stat(SS_INT, 250);
    set_base_stat(SS_WIS, 250);
    set_base_stat(SS_DIS, 100);

    set_skill(SS_TRADING, 100);

    set_alignment(0);

    remove_prop(NPC_M_NO_ACCEPT_GIVE);

    Deed_owners = restore_map(HOUSE + "deed_owners");
    restore_house_data();
    config_default_trade();
    add_ask(({"fee", "pay", "pay fee", "pay a fee"}) ,VBFC_ME("explain_fee"));
    add_ask(({"houses", "house"}) ,VBFC_ME("explain_house"));
    add_ask(({"list of adjectives", "adjective list", "adjectives",
"adjective"}) , 
        VBFC_ME("list_adjectives"));
    add_ask(({"name list", "list of names", "house names", "name", "names"}) ,
        VBFC_ME("list_names"));
    add_ask(({"gender", "genders"}) ,VBFC_ME("list_genders"));
}



/*
save_house_data()
Save mapping of available house names and adjectives
Map saved as players name with elements as follows ({<adjective1>,<adjective2>,
<gender> <name of house>})

Arguments: None
Returns:   None

*/
public void
save_house_data()
{
    save_map(House_data, HOUSE + "house_data");
}



/*
save_house_names()
Save mapping of all house names and their meanings
Map saved as players name meaning as value

Arguments: None
Returns:   None

*/
public void
save_house_names()
{
    save_map(House_names, HOUSE + "house_names");
}




/*
save_owner_data()
Save mapping of house owners

Arguments: None
Returns:   None
*/
public void
save_owner_data()
{
    save_map(Deed_owners, HOUSE + "Deed_owners");
}

/*

restore_house_names()
Retrieve saved mapping of all (owned and unowned) house names and meanings

Arguments: None
Returns:   None

*/

public void
restore_house_names()
{
    House_names = restore_map(HOUSE + "house_names");
}

/*
restore_house_data()
Retrieve saved mapping of available house names and adjectives

Arguments: None
Returns:   None

*/

public void
restore_house_data()
{
    House_data = restore_map(HOUSE + "house_data");
    adjectives1 = House_data["adj1"];
    adjectives2 = House_data["adj2"];
    house_names = House_data["names"];
}

/*
get_house_name()
Get player's house name from mapping

Arguments: None
Returns:   string - Name of house

*/
public string
get_house_name()
{
    string *data, hname;
    data = Deed_owners[TP->query_real_name()];
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
remove_house_name()
Remove player's house name and add back to available names

Arguments: string - Player's name

*/
public void
remove_house_name(string player)
{
    string hname;

    hname = capitalize(get_house_name());
    house_names = House_data["names"];
    // Add name back to house_data
    house_names += ({hname});
    House_data["names"] = house_names;
    save_house_data();

    // Remove owner's house
    Deed_owners = m_delete(Deed_owners, player);
    save_owner_data();
}



/*
check_valid_owner()
See if player already owns a house.

Arguments: None
Returns:   1 if player owns house - 0 if player does not own a house
*/
public int
check_valid_owner()
{
    string player;
    player = TP->query_real_name();

    if (Deed_owners[player])
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
    command("say You may choose a new house, but you will need to pay a " +
        "fee.");
    return "";
}


/* explain_house()
Response to "ask house"

*/
string
explain_house()
{
    command("say I can help you choose a house. Read the poster for help.");
    return "";
}

/*
list_adjectives()
Response to "ask adjectives"
Lists available adjectives for houses.

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
Command to add a new house name and meaning in English.
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
    restore_house_data();
    restore_house_names();
    name = capitalize(sentence[0]);
    temp = sentence[1..sizeof(sentence)];
    meaning = implode(temp, " ");
    House_names[name] = meaning;
    // Add to master list of names (owned and un-owned):
    save_house_names();
    // Add to available pool of names (un-owned):
    House_data["names"] += ({name});
    save_house_data();
    return 1;
}

/*
remove_name()
Command to remove house.
Only works for wizards.

remove <name>

Arguments: string - name
*/

public int
remove_name(string str)
{
    string *sentence, name, meaning, player;
    player = this_player()->query_real_name();
    if (!this_player()->query_wiz_level())
        return 0;

    if (!stringp(str))
    {
        command("say Syntax: remove <name>");
        return 1;
    }

    House_names = restore_map(HOUSE + "house_names");
    name = capitalize(str);
    House_names = m_delete(House_names, name);
    save_house_names();
    House_data["names"] -= ({name});
    save_house_data();
    return 1;
}

/*
list_names()
List available house names and their meanings in English
in response to "ask names".

Arguments: None
Returns:   None

*/

public string
list_names()
{
    int i, nbr_houses;
    string name, *houses, meaning;
    mapping house_names;

    house_names = restore_map(HOUSE + "house_names");
    houses = House_data["names"];
    nbr_houses = sizeof(houses);
    command("say I have houses with the following names:\n");
    i = 0;
    while (i < nbr_houses)
    {
        name = houses[i];
        meaning = house_names[name];
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
    command("say I have male and female houses.");
    return "";
}


/*
choose_house()
Command that allows you to choose house. Also removes name

from available list of house names.

 choose <adj1> <adj2> <gender> house named <name>

Arguments: String - see example command above
Returns:   int
*/
int
choose_house(string str)
{
    object *houses;
    string player, race;
    int animal_handle, riding;

    string adj1, adj2, name, gender;
    string *sentence;
    string *save_data;

    player = this_player()->query_real_name();

    race = this_player()->query_guild_name_race();

    if (!CAN_SEE_IN_ROOM(this_object()) || !CAN_SEE(this_object(), this_player()))
    {
        command("say Reveal yourself.");
        command("peer");
        return 1;
    }

    if (check_valid_owner() == 1)
    {
        command("say to " + player + " You already own a house. Try " +
            "summoning it.");
        command("whisper " + player + " nosummon");
        command("say to " + player + " If you want a different house, " +
            "you'll have to pay a fee.");
        return 1;
    }

    animal_handle = this_player()->query_skill(105);
    riding = this_player()->query_skill(112);

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
    // choose glimmering white male house named Hingil
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
        command("say I don't have a house with that first adjective. Please " +
            "read the plaque for more information.");
        return 1;
    }

        if (member_array(adj2, adjectives2) == -1)
    {
        command("say I don't have a house with that second adjective. Please "
+
            "read the plaque for more information.");
        return 1;
    }

    if (gender != "male" && gender != "female")
    {
        command("say I have no house of the gender '" + gender + "'. Please " +
            "read the poster, it should help you.");
        return 1;
    }

    if (member_array(capitalize(name), house_names) == -1)
    {
        command("say None of my houses has that name. Ask me about names " +
            "for names that are available. If you have suggestions for " +
            "new ones, use <idea> to submit your suggested name and the " +
            "meaning of the name.");
        return 1;
    }

    save_data = ({adj1, adj2, gender, name});

    // Remove house's name from list of available names.
    house_names -= ({capitalize(name)});
    House_data["names"] = house_names;
    save_house_data();

    // Command to select house should be: choose <adjective1> <adjective2> <gender> house named <house's name>

    Deed_owners[this_player()->query_real_name()] = save_data;
    save_owner_data();


    command("say to " + player + " You may summon your house now.");
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
    if (!interactive(this_player()) || this_player()->query_met(query_name()))
        return;

    command("introduce me to " + this_player()->query_real_name() + "");
}

/*
pay_fee()
Pay fee if you want a new house.

Arguments: string - "fee"
Returns:   None
*/
int
pay_fee(string str)
{
    int *money;
    string player, hname, race;

    player = this_player()->query_real_name();

    if (!CAN_SEE_IN_ROOM(this_object()) || !CAN_SEE(this_object(), this_player()))
    {
        command("say Do you want to pay a fee? Reveal yourself.");
        return 0;
    }

    if (str != "fee")
    {
        notify_fail("Pay what? A fee?\n");
        return 0;
    }

    if (check_valid_owner() == 1)
    {
        hname = get_house_name();
        if (find_living(lower_case(hname)))
        {
            notify_fail("Your house needs to be sent home before you can " +
            "new one. Use <nograze> to send it home.\n");
            return 0;
        }
        money = pay(FEE, this_player());
        if (sizeof(money) == 1)
        {
            command("say to " + player + " When you have enough money, I'll " +
                    "be happy to help you.");
            return 1;
        }

        say(QCTNAME(this_player()) + " pays the fee.\n");
        write("You pay the fee.\n");
        command("say to " + player + " Thank you. You may now choose a new house.");
        remove_house_name(player); // Remove house, add name back into available list.
        return 1;
    }
    else
    {
        command("say to " + player + " You don't need to pay a fee. You " +
            "may choose a house.");
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
    this_object()->command("frown");
    this_object()->command("emote mumbles a prayer.");
    attacker->stop_fight(this_object());
    this_object()->stop_fight(attacker);
}

void
init_living()
{
    ::init_living();
    add_action(choose_house, "choose");
    add_action(pay_fee, "pay");
    add_action(add_name, "add");
    add_action(remove_name, "remove");
}