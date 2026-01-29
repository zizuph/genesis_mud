/*
 * /d/Genesis/obj/deposit.c
 *
 * This is the deposit of the Gnomes of Genesis. It is a bank that can save
 * money for players. To offer the service, just clone this object into your
 * bank room and everything will be taken care of.
 *
 * Gem storage
 * -----------
 * In order to provide gem storage in a bank, a bank identifier must be set.
 * The routine set_bank_id(int ID, string desc) is to be used for this. This
 * ID value must be unique throughout the realms. It consists of the domain
 * number followed by a sequence number, starting with 01. The domain is
 * responsible for defining this number correctly. It MUST be listed in the
 * document /d/Domain/open/SHOPS to avoid future confusion.
 *
 * Originally coded by Tintin, 1992
 *
 * Version 2.0 by Mercade, July 1995
 * - code cleanup and use of disk cache.
 *
 * Version 3.0 by Mercade, January 2008
 * - moved processing to accounts object.
 * - introduction of gem deposits.
 *
 * Version 3.1 by Leia, April 2011
 * - Reworked the methods for displaying the read command. Makes it so you can pass
 *   in different terms/usage to eliminate the "Gnome Text". Only use this option if
 *   you know what you are doing. Otherwise, deposit will just default to the standard
 *   text.
 * - Also added set_sign_text(string text) function.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/object";

#include <cmdparse.h>
#include <composite.h>
#include <files.h>
#include <language.h>
#include <macros.h>
#include <math.h>
#include <money.h>
#include <options.h>
#include <stdproperties.h>

#include "/d/Genesis/sys/deposit.h"
#include "/d/Genesis/gems/gem.h"

#undef _april_fools

/*
 * Global variables.
 */
static private string  terms;
static private string  usage;
static private int     bank_id = 0;
static private string  bank_desc = "";
static private string  clerk_race = "gnome";
static private string sign_text;

/* Prototype. */
void set_terms_and_usage(string terms, string usage);
void set_sign_text(string text);

/*
 * Function name: create_object
 * Description  : This function is called to create the strongroom.
 */
public void
create_object() 
{
    set_name("strongroom");
    add_name("deposit");
    add_name("hut");

    add_adj("gnome");
    add_adj("money");

    set_short("strongroom");
    set_long("It is a small fort-like hut. It has an opening protected " +
	"with steel bars and a large sign. Behind the opening there is " +
	"small wizened gnome.\n");

    add_item( ({ "sign", "large sign" }),
	"A large sign with large, crooked letters at the top and a lot " +
	"of fine print at the bottom.\n");
    add_item( ({ "letters", "crooked letters" }),
        "GnoMeS oF GenESiS\n");
    add_item( ({ "print", "fine print" }),
        "The fine print contains the terms of deposit and gives " +
        "instructions on using the deposit. They are best read for " +
        "complete understanding.\n");
    add_item( ({ "terms", "terms of deposit" }), 
        "The terms of deposit describe the rules under which money and " +
        "gems may be deposited. They are best read for complete " +
        "understanding.\n");
    add_item( ({ "instructions", "instructions on usage", "usage", }), 
        "The instructions on usage describe command that are available and " +
        "give examples of possible commands. They are best read for " +
        "complete understanding.\n");
    add_item( ({ "gnome", "small gnome", "wizened gnome",
	"small wizened gnome" }),
	"A small, greedy-looking gnome with a large nose.\n");
    add_item( ({ "bars", "bar", "steel bars", "steel bar" }),
    	"The steel bars look like they will not bulge even under great " +
    	"pressure.\n");
    add_item( ({ "opening" }),
	"It is the counter, protected by steel bars. Behind it you find a " +
	"small wizened gnome.\n");

    add_prop(OBJ_M_NO_GET, "It is not just a strongroom, it is a very heavy " +
	"strongroom as well. No way you can lift it.\n");
	
    set_sign_text("The sign reads:\n\n" +
	"GNoMeS oF GeNeSiS\n" +
	"- aBSoLuTeLy SaFe\n" +
	"- FRieNDLy SeRViCe\n" +
	"- aVaiLaBLe eVeRyWHeRe\n" +
	"- aLL iMPoRTaNT PLaCeS aNyWay\n" +
	"- LoW FeeS\n" +
	"- HoBBiTS SPeCiaL RaTeS\n\n" +
	"After that there is a lot of fine print regulating the terms " +
	"of deposit and giving instructions on using the GoG deposit.\n");

    setuid();
    seteuid(getuid());

    /* We want this function called after the bank_id has been set. */
    set_terms_and_usage(GOG_TERMS, GOG_USAGE);
}

/*
 * Function name: process_terms
 * Description  : This routine will process the terms and usage for those
 *                banks that do or do not have a gem deposit. Lines with |
 *                are for all banks, G for gem deposits and B for banks
 *                without it.
 * Arguments    : string text - the text to set.
 * Returns      : string - the filtered text.
 */
public string
process_terms(string text)
{
     string *lines = explode(text, "\n");
     string type = (bank_id ? GOG_LINE_GEMS : GOG_LINE_BANK);

     lines = filter(lines, &wildmatch("[|" + type + "]*"));
     lines = map(lines, &extract(, 1));

     return implode(lines, "\n") + "\n";
}

/*
 * Function name: set_terms
 * Description  : Set the terms of the deposit. The first character of every
 *                line should be marked with |, G or B to indicate whether it
 *                is for common use or for banks with(out) gem deposit.
 * Arguments    : string text - the terms.
 */
public void
set_terms(string text)
{
    terms = process_terms(text);
}

/*
 * Function name: set_usage
 * Description  : Set the usage of the deposit. The first character of every
 *                line should be marked with |, G or B to indicate whether it
 *                is for common use or for banks with(out) gem deposit.
 * Arguments    : string text - the usage.
 */
public void
set_usage(string text)
{
    usage = process_terms(text);
}

/*
 * Function name: set_terms_and_usage
 * Description  : A little relay to set the terms and usage.
 * Arguments    : string terms - the terms
 *                string usage - the usage instructions.
 */
public void
set_terms_and_usage(string terms, string usage)
{
    set_terms(terms);
    set_usage(usage);
}

/*
 * Function name: set_bank_id
 * Description  : Set the gem bank identifier of this gnome depository. This
 *                value must be unique throughout the realms. It consists of
 *                the domain number followed by a sequence number, starting
 *                with 01. The domain is responsible for defining this number
 *                correctly. It MUST be listed in the /d/Domain/open/SHOPS
 *                document to avoid future confusion.
 * Arguments    : int bid - the gem bank identifier
 *                string desc - the location of the bank, max 30 characters.
 *                    It must fit in the sentence "The branch in <desc>."
 */
public varargs void
set_bank_id(int bid, string desc = "")
{
    bank_id = bid;
    bank_desc = extract(desc, 0, 29);

    GOG_ACCOUNTS->register_bank(bank_id, bank_desc);
}

/*
 * Function name: get_bank_id
 * Description  : Find out the gem bank identifier of this gnome depository.
 * Returns      : int - the gem bank identifier
 */
int
query_bank_id()
{
    return bank_id;
}

/*
 * Function name: set_clerk_race
 * Description  : Define the race of the clerk.
 * Returns      : string race - the race of the clerk.
 */
public void
set_clerk_race(string race)
{
    clerk_race = race;
}

/*
 * Function name: query_clerk_race
 * Description  : Find out the race of the clerk.
 * Returns      : string - the race.
 */
public string
query_clerk_race(string str)
{
    return clerk_race;
}

#ifdef _april_fools
/*
 * Function name: april_fools
 * Description  : ACK! On April fools day, all accounts will be stolen!
 * Returns      : int - TRUE when it is April fools.
 */
int
april_fools()
{
    if (ctime(time())[4..9] != "Apr  1")
    {
        return 0;
    }

    write("As you approach the deposit, the gnomish clerk exclaims:\n");
    say("As " + QTNAME(this_player()) +
       " approaches the deposit, the gnomish clerk exclaims:\n");
    tell_room(environment(this_player()),
       "    OH!ItIsTerrible!WeHaveBeenROBBED!AllThoseBeautifulCoinsGONE!\n\n" +
       "The clerk cries out in agony and continues:\n" +
       "    ItHappenedLastNight!TheyWereHoodedAndMasked!AndTheyCarriedSwords!\n" +
       "    AndHeavyHammersToo!TheyFledThatWay!\n\n" +
       "The clerk points out in a hasty gesture and starts to sob silently again.\n");
    return 1;
}
#endif _april_fools

/*
 * Function name: no_deposit_possible
 * Description  : If you want to make some checks before the player deposits
 *                any money, you should mask this routine and if the function
 *                returns true, this means that no deposit is possible. You
 *                should print your own error message.
 * Returns      : int 1/0 - if true, no deposit is possible.
 */
public int
no_deposit_possible()
{
    return 0;
}

/*
 * Function name: no_withdrawal_possible
 * Description  : If you want to make some checks before the player withdraws
 *                any money, you should mask this routine and if the function
 *                returns true, this means that no withdrawal is possible. You
 *                should print your own error message.
 * Returns      : int 1/0 - if true, no withdrawal is possible.
 */
public int
no_withdrawal_possible()
{
    return 0;
}

/*
 * Function name: print_account_banks
 * Description  : Print the locations of the gem deposits of the player.
 * Arguments    : string name - the (lower case) name of the player.
 */
static void
print_account_banks(string name)
{
    int    *bank_ids = GOG_ACCOUNTS->query_accounts(name);
    int     here = IN_ARRAY(bank_id, bank_ids);
    int     value;
    string *locations = ({ });

    if (here)
    {
        bank_ids -= ({ bank_id });
        write("The " + clerk_race + " says: You have a gem deposit here in " +
            bank_desc + ".\n");
    }
    if (sizeof(bank_ids))
    {
        foreach(int id: bank_ids)
        {
            locations += ({ GOG_ACCOUNTS->query_bank_desc(id) });
        }
        write("The " + clerk_race + " says: You " + (here ? "also " : "") +
            "have " + ((sizeof(bank_ids) == 1) ?
                "a gem deposit in " + locations[0] :
                "gem deposits in " + COMPOSITE_WORDS_WITH(locations, "and in")) +
            (here ? "" : ", but not here") + ".\n");
    }

    value = GOG_ACCOUNTS->query_gems_value(name, 0);
    write("The " + clerk_race + " says: The total value of the deposited "+
        "gems is " + (value ? MONEY_TEXT_SPLIT(value) : "a few silvers at best") +
        " as per your latest tally.\n");
}

/*
 * Function name: print_account_coins
 * Description  : Print the contents of an account the the player.
 * Arguments    : string name - the (lower case) name of the player.
 *                int showgems - if true, show info about the gems, too.
 */
static void
print_account_coins(string name, int showgems = 0)
{
    int *coins = GOG_ACCOUNTS->query_account_coins(name);
    int  fee = GOG_ACCOUNTS->query_account_fee(name);
    int  index = SIZEOF_MONEY_TYPES;
    
    write("The " + clerk_race + " says: You have placed the following " +
        "money in our trust:\n");
    while(--index >= 0)
    {
        write(sprintf("%7d %s coins\n", coins[index], MONEY_TYPES[index]));
    }

    write("\nTotal value: " + MONEY_TEXT_NUM_SPLIT(MONEY_MERGE(coins)) + ".\n");
    if (fee)
    {
        write("Fees due   : " + MONEY_TEXT_NUM_SPLIT(fee) + ".\n");
    }

    if (showgems)
    {
        switch(GOG_ACCOUNTS->query_has_gems(name, bank_id))
        {
        case 1:
            write("You have gems in the care of this branch of the GoG, but not elsewhere.\n");
            break;
        case 2:
            write("You have gems in the care of another branch of the GoG, but not here.\n");
            break;
        case 3:
            write("You have gems in the care of this branch and another branch of the GoG.\n");
            break;
        default:
            write("You have no gems in the care of the Gnomes of Genesis.\n");
        }
    }
}

/*
 * Function name: print_account_gems
 * Description  : Print the contents of a gem store the the player.
 * Arguments    : string name - the (lower case) name of the player.
 */
static void
print_account_gems(string name)
{
    mapping gems = GOG_ACCOUNTS->query_account_gems(name, bank_id);
    int     count;
    int     elsewhere = (GOG_ACCOUNTS->query_has_gems(name, bank_id) & 2);
    string *text = ({ });
    int     scrw = this_player()->query_option(OPT_SCREEN_WIDTH);
    int     value;
    int    *bank_ids = GOG_ACCOUNTS->query_accounts(name);
    int     here = IN_ARRAY(bank_id, bank_ids);
    string *locations = ({ });
    string  location;

    if (elsewhere)
    {
        bank_ids -= ({ bank_id });
        if (sizeof(bank_ids))
        {
            foreach(int id: bank_ids)
            {
                locations += ({ GOG_ACCOUNTS->query_bank_desc(id) });
            }
	    location = "at our " + ((sizeof(bank_ids) == 1) ? "Branch" : "Branches") +
	        " in " + COMPOSITE_WORDS_WITH(locations, "and in");
        }
    }
    
    if (m_sizeof(gems))
    {
        write("The " + clerk_race + " says: We hold the following gems for " +
            "you in " + bank_desc + ":\n");
        foreach(string gem: sort_array(m_indices(gems)))
        {
            count = gems[gem];
            text += ({ sprintf("%4d %s", count, 
                ((count == 1) ? gem->query_short() : gem->query_plural_short())) });
        }
        scrw = ((scrw >= 40) ? (scrw - 3) : 77);
        write(sprintf("%-*#s\n", scrw, implode(text, "\n")));

        value = GOG_ACCOUNTS->query_gems_value(name, bank_id);
        write("\nThe " + clerk_race + " says: The value of the gems " +
            "deposited here is " +
            (value ? MONEY_TEXT_SPLIT(value) : "a few silvers at best") +
            " as per your latest tally.\n");
        if (elsewhere)
        {
            write("The " + clerk_race + " says: We also keep gems for you " +
	        location + ".\n");
        }
        else
        {
            write("The " + clerk_race + " says: This is your only deposit " +
                "in the realms.\n");
        }
    }
    else
    {
        write("The " + clerk_race + " says: We are not keeping any gems " +
            "for you here in " + bank_desc +
            (elsewhere ? ", but we do " + location : " or at any other Branch of the Gnomes of Genesis") +
            ".\n");
    }
}

/*
 * Function name: hook_extra_desc
 * Description  : Returns the text that is used in the long description of
 *                the room to show there is a deposit here.
 */
string
hook_extra_desc()
{
    return "There is a branch of the Gnomes of Genesis deposit here.\n";
}

/*
 * Function name: check_not_visible
 * Description  : Makes sure that the player trying to deal with the GoG is
 *                not hidden or invisible.
 */
public int
check_not_visible()
{
    if (this_player()->query_prop(OBJ_I_INVIS) ||
        this_player()->query_prop(OBJ_I_HIDE))
    {
        tell_room(environment(), "The " + clerk_race + " says: I can hear, " +
            "but I cannot see you. Reveal yourself if you want to do " +
            "business.\n");
        return 1;
    }
    return 0;
}

/*
 * Function name: account
 * Description  : When the player wants to know the amount on his account,
 *                this is the command to use.
 * Arguments    : string str - the command line argument.
 * Returns      : int 1/0 - success/failure.
 */
public int
account(string str = "coins")
{
    string name = this_player()->query_real_name();

#ifdef _april_fools
    if (april_fools()) return 1;
#endif _april_fools
    /* Visibility check on the actor. */
    if (check_not_visible()) return 1;

    if (!GOG_ACCOUNTS->query_has_account(name))
    {
        write("The " + clerk_race + " says: Sorry, but you do not seem to " +
            "have an account with us.\n");
        return 1;
    }

    switch(str)
    {
    case "":
    case "coin":
    case "coins":
    case "money":
        GOG_ACCOUNTS->update_fee(name);
        print_account_coins(name, 1);
        break;

    case "gem":
    case "gems":
        print_account_gems(name);
        break;

    case "bank":
    case "banks":
    case "deposit":
    case "deposits":
        print_account_banks(name);
        break;

    default:
        notify_fail("Your account of what? Coins or gems?\n");
        return 0;
    }

    say(QCTNAME(this_player()) + " inquires about " +
        this_player()->query_possessive() +
        " account at the Gnomes of Genesis.\n");
    return 1;
}

/*
 * Function name: consolidate
 * Description  : The player wants to consolidate his gems.
 * Arguments    : string str - the command line argument.
 * Returns      : int 1/0 - success/failure.
 */
int
consolidate(string str)
{
    string name = this_player()->query_real_name();
    string from_name;
    int    from_id;
    int    fee;

#ifdef _april_fools
    if (april_fools()) return 1;
#endif _april_fools
    /* Visibility check on the actor. */
    if (check_not_visible()) return 1;

    if (!bank_id)
    {
        write("The " + clerk_race + " says: This Branch of the Gnomes of " +
            "Genesis is not yet equipped to accept gems. Please petition " +
            "the neighbourhood wizard for a Bank ID for this branch.\n");
        return 1;
    }

    if (!strlen(str) ||
        !parse_command(str, ({ }), "[my] [gems] 'from' %s", str))
    {
        notify_fail("Consolidate your gems from where?\n");
        return 0;
    }

    from_id = GOG_ACCOUNTS->find_bank_by_desc(str);
    if (!from_id)
    {
        notify_fail("The " + clerk_race + " says: I am not familiar with " +
            "a branch office in " + str + ".\n");
        return 0;
    }
    if (bank_id == from_id)
    {
        notify_fail("The " + clerk_race + " says: Uhm, this is the branch in " +
            bank_desc + " already.\n");
        return 0;
    }

    from_name = GOG_ACCOUNTS->query_bank_desc(from_id);
    fee = ((GOG_TRANSIT_FEE * GOG_ACCOUNTS->query_gems_value(name, from_id)) / 100);
    GOG_ACCOUNTS->update_fee(name);
    if (fee > GOG_ACCOUNTS->query_account_value(name))
    {
        write("The " + clerk_race + " says: Consolidation of your gems from " +
            from_name + " to here will cost " + MONEY_TEXT_SPLIT(fee) +
            ". This fee will be taken from your account, but your account " +
            "does not hold enough money. Please make a deposit first.\n");
        return 1;
    }

    if ((this_player()->query_prop(PLAYER_I_CONSOLIDATE_GEMS) + 60) < time())
    {
        this_player()->add_prop(PLAYER_I_CONSOLIDATE_GEMS, time());
        write("The " + clerk_race + " says: Consolidation of your gems from " +
            from_name + " to here will cost " + MONEY_TEXT_SPLIT(fee) +
            ". This fee will be taken from your account.\n");
        write("The " + clerk_race + " says: Please confirm your intention " +
            "to consolidate your gems by typing the same command within one " +
            "minute.\n");
        return 1;
    }

    GOG_ACCOUNTS->consolidate_gems(name, from_id, bank_id, fee);
    write("The " + clerk_race + " does some calculations on an abacus and " +
        "writes something with red ink in a huge ledger.\n");
    write("The " + clerk_race + " says: We will inform the branch office in " +
        from_name + " of your request. When your transport has safely " +
        "reached us, we will let you know. The transfer can take quite some " +
        "time, depending on distance and road safety conditions.\n");
    say(QCTNAME(this_player()) + " orders a transfer of valueables within " +
        "the Gnomes of Genesis.\n");
    return 1;
}

/*
 * Function name: deposit_coins
 * Description  : Called to process the deposit of coins.
 * Arguments    : int *coins - the array of coins to be deposited.
 * Returns      : int 1/0 - success/failure.
 */
int
deposit_coins(int *coins)
{
    string  name = this_player()->query_real_name();
    int     index;
    int     deposit_flag;

    GOG_ACCOUNTS->update_fee(name);

    for (index = 0; index < sizeof(coins); index++)
    {
        if (coins[index] < 1)
	{
            continue;
	}

        if (MONEY_MOVE(coins[index], MONEY_TYPES[index], this_player(), 0))
        {
            write("The " + clerk_race + " says: You don't have that many " +
                MONEY_TYPES[index] + " coins.\n");
            coins[index] = 0;
            continue;
        }

        deposit_flag = 1;
        GOG_ACCOUNTS->add_money(name, index, coins[index]);
    }

    if (!deposit_flag)
    {
        write("The " + clerk_race + " says: No coins deposited.\n");
        return 1;
    }

    if (environment()->hook_deposit_coins(secure_var(coins)))
    {
        write("The " + clerk_race + " says: You deposited " + MONEY_TEXT(coins) + ".\n");
        say(QCTNAME(this_player()) +
            " deposits some coins in the care of the Gnomes of Genesis.\n");
    }
    print_account_coins(name, 1);
    return 1;
}

/*
 * Function name: deposit_gems
 * Description  : Called to process the deposit of gems.
 * Arguments    : object *gems - the array of gem objects to be deposited.
 * Returns      : int 1/0 - success/failure.
 */
int
deposit_gems(object *objs)
{
    string  name = this_player()->query_real_name();
    string  text;
    object *gems;
    int     number;

    if (!bank_id)
    {
        write("The " + clerk_race + " says: This Branch of the Gnomes of " +
            "Genesis is not yet equipped to accept gems. Please petition " +
            "the neighbourhood wizard for a Bank ID for this branch.\n");
        return 1;
    }

    gems = FILTER_GEMS(objs);
    objs -= gems;
    if (sizeof(objs))
    {
        write("The " + clerk_race + " says: We cannot accept " +
            COMPOSITE_DEAD(objs) + ".\n");
    }
    if (!sizeof(gems))
    {
        return 1;
    }

    text = COMPOSITE_DEAD(gems);
    foreach(object gem: gems)
    {
        GOG_ACCOUNTS->add_gem(name, bank_id, MASTER_OB(gem), gem->num_heap());
        gem->remove_split_heap();
    }

    write("The " + clerk_race + " says: You deposited " + text + ".\n");
    print_account_gems(name);
    say(QCTNAME(this_player()) +
        " deposits some gems in the care of the Gnomes of Genesis.\n");
    return 1;
}

/*
 * Function name: deposit
 * Description  : The player wants to make a deposit.
 * Arguments    : string str - the command line argument.
 * Returns      : int 1/0 - success/failure.
 */
int
deposit(string str)
{
    int     index;
    string  except_str;
    int    *coins, *except_coins;
    object *objs;
    object  coin;

#ifdef _april_fools
    if (april_fools()) return 1;
#endif _april_fools
    /* Visibility check on the actor. */
    if (check_not_visible()) return 1;

    if (this_player()->query_wiz_level())
    {
        notify_fail("There is no need for you to deposit money.\n");
        return 0;
    }

    if (!strlen(str))
    {
        notify_fail("The " + clerk_race + " says: What is it you like to deposit?\n");
        return 0;
    }

    /* See if this person can make a deposit. */
    if (no_deposit_possible())
    {
        return 1;
    }

    if (parse_command(str, ({ }), "%s 'except' [for] %s", str, except_str))
    {
        except_coins = MONEY_PARSE_OB(except_str, this_player());
        if (!pointerp(except_coins))
	{
            notify_fail("The " + clerk_race + " says: Except for which coins?\n");
            return 0;
	}
    }
    else
    {
        except_coins = allocate(SIZEOF_MONEY_TYPES);
    }

    /* For some reason MONEY_PARSE_OB doesn't recognise "coin". */
    if ((str == "coin") && objectp(coin = present("coin", this_player())))
    {
        str = coin->singular_short();
    }

    coins = MONEY_PARSE_OB(str, this_player());
    if (pointerp(coins))
    {
        for (index = 0; index < sizeof(coins); index++)
        {
            coins[index] -= min(coins[index], except_coins[index]);
        }
        return deposit_coins(coins);
    }

    objs = FIND_STR_IN_OBJECT(str, this_player());
    if (!sizeof(objs))
    {
        notify_fail("The " + clerk_race + " says: What would you like to deposit?\n");
        return 0;
    }

    return deposit_gems(objs);
}

/*
 * Function name: read
 * Description  : Called when the player wants to read the text on the sign.
 * Arguments    : string str - the command line argument.
 * Returns      : int 1/0 - success/failure.
 */
public int
read(string str)
{
    if (IN_ARRAY(str, ({ "sign", "large sign" }) ))
    {
	write(sign_text);

	return 1;
    }

    if (IN_ARRAY(str, ({ "print", "fine print" }) ))
    {
	write(terms + "\n" + usage);
	return 1;
    }

    if (IN_ARRAY(str, ({ "terms", "terms of deposit" }) ))
    {
        write(terms);
        return 1;
    }

    if (IN_ARRAY(str, ({ "usage", "instructions", "instructions on usage" }) ))
    {
        write(usage);
        return 1;
    }

    notify_fail("Do you want to read the terms of deposit or the instructions on usage?\n");
    return 0;
}

/*
 * Function name: set_sign_text
 * Description  : This fucntion allows for customization of the sign text, to eliminate
 *                gnomish writing.
 * Arguments    : string str - the text for the sign.
 * Returns      : void
 */
public void
set_sign_text(string text)
{
    sign_text = text;
}

/*
 * Function name: retrieve
 * Description  : This fucntion is called whenever the player wants to
 *                retrieve some coins placed in the care of the GoG.
 * Arguments    : string str - the command line argument.
 * Returns      : int 1/0 - success/failure.
 */
public int
retrieve(string str)
{
    string  name = this_player()->query_real_name();
    string  gem_spec;
    int     number;
    object  gem;
    string  gem_file;
    string *gem_files, *match;
    mapping account_gems;
    int     here;

#ifdef _april_fools
    if (april_fools()) return 1;
#endif _april_fools
    /* Visibility check on the actor. */
    if (check_not_visible()) return 1;

    if (!bank_id)
    {
        write("The " + clerk_race + " says: This Branch of the Gnomes of " +
            "Genesis is not yet equipped to handle gems. Please petition " +
            "the neighbourhood wizard for a Bank ID for this branch.\n");
        return 1;
    }

    if (!strlen(str))
    {
        notify_fail("The " + clerk_race + " says: You have to state amount " +
            "and gem type to retrieve.\n");
        return 0;
    }

    if (parse_command(str, ({ }), "[my] 'gem' / 'gems' / 'all'"))
    {
        notify_fail("The " + clerk_race + " says: Please specify the type " +
            "of gem to retrieve, or retrieve all your gems.\n");
        return 0;
    }

    if (parse_command(str, ({ }), "'all' [my] 'gems'"))
    {
        account_gems = GOG_ACCOUNTS->query_account_gems(name, bank_id);
        if (!m_sizeof(account_gems))
        {
            account_gems = GOG_ACCOUNTS->query_account_gems(name, -bank_id);
            write("The " + clerk_race + " says: We do not keep any gems for " +
                "you here" + (m_sizeof(account_gems) ?
                    ", but we do at another" : " or at any other") +
                " branch of the Gnomes of Genesis.\n");
            return 1;
        }

        foreach(string gem_file: m_indices(account_gems))
        {
            gem = clone_object(gem_file);
            number = account_gems[gem_file];

            /* Let's see if the player isn't too encumbered. */
            if ((this_player()->query_prop(CONT_I_MAX_WEIGHT) -
                 this_player()->query_prop(OBJ_I_WEIGHT)) <
                (number * gem->query_prop(HEAP_I_UNIT_WEIGHT)))
            {
                number = ((this_player()->query_prop(CONT_I_MAX_WEIGHT) -
                    this_player()->query_prop(OBJ_I_WEIGHT)) /
                    gem->query_prop(HEAP_I_UNIT_WEIGHT));

                if (number <= 0)
                {
                    write("You are completely encumbered and cannot handle " +
                        "even a single " + gem->query_short() + " extra. " +
                        "None are retrieved.\n");
                    gem->remove_object();
                    break;
                }
    
                write("You cannot carry that many " + gem->query_plural_short() +
                    ". Therefore only " + number + " " +
                    ((number == 1) ? gem->query_short() : gem->query_plural_short()) +
                    " will be given to you.\n");
            }
            gem->set_heap_size(number);
            write("You are handed " + LANG_ASHORT(gem) + ".\n");
            gem->move(this_player(), 1);

            GOG_ACCOUNTS->remove_gem(name, bank_id, gem_file, number);
        }

        here = (GOG_ACCOUNTS->query_has_gems(name, bank_id) & 1);
        if (!here)
        {
            write("The " + clerk_race + " says: " +
                ((number == 1) ? "That was" : "Those were") + " the last gem" +
                ((number == 1) ? "" : "s") + " we had for you at this branch " +
                "of the GoG.\n");
        }
        print_account_gems(name);
        write("The " + clerk_race + " says: Thank you for putting your gems " +
            "in our trust.\n");
        say(QCTNAME(this_player()) +
            " retrieves some gems from the Gnomes of Genesis.\n");
        return 1;
    }

    if (!sscanf(str, "%d %s", number, gem_spec))
    {
        number = -1;
        gem_spec = str;
    }

    gem_files = IDENTIFY_GEMS(gem_spec);
    if (!sizeof(gem_files))
    {
        notify_fail("The " + clerk_race + " says: Which gems do you wish " +
            "to retrieve?\n");
        return 0;
    }
    account_gems = GOG_ACCOUNTS->query_account_gems(name, bank_id);
    /* Match account with wanted gems, if the person has an account here. */
    match = (mappingp(account_gems) ? (gem_files & m_indices(account_gems)) : ({ }) );

    switch(sizeof(match))
    {
    case 0:
        account_gems = GOG_ACCOUNTS->query_account_gems(name, -bank_id);
        /* Match wanted gems with donut-wide account, if any. */
        match = (mappingp(account_gems) ? (gem_files & m_indices(account_gems)) : ({ }) );
        write("The " + clerk_race + " says: We keep no such gems for you here" +
            (sizeof(match) ? ", but we do at another" : " or at any other") +
            " branch of the Gnomes of Genesis.\n");
        return 1;
    case 1:
        gem_file = match[0];
        break;
    default:
        write("The " + clerk_race + " says: Please be specific about the " +
            "gems you wish to retrieve. Do you mean " +
            COMPOSITE_WORDS_WITH(map(match, &->query_plural_short()), "or") +
            "?\n");
        return 1;
    }

    write("The " + clerk_race + " does some calculations on an abacus and " +
        "writes something with red ink in a huge ledger.\n");

    if (number == -1)
    {
        /* If we specify singular, take only one gem. */
        number = (gem_file->id(gem_spec) ? 1 : account_gems[gem_file]);
    }

    gem = clone_object(gem_file);
    /* Make sure the user doesn't get too many gems back. */
    if (number > account_gems[gem_file])
    {
        number = account_gems[gem_file];
        write("The " + clerk_race + " says: You only have " +
            LANG_NUM2WORD(number) + " " +
            ((number == 1) ? gem->query_short() : gem->query_plural_short()) +
            " in our care.\n\n");
    }

    /* Let's see if the player isn't too encumbered. */
    if ((this_player()->query_prop(CONT_I_MAX_WEIGHT) -
         this_player()->query_prop(OBJ_I_WEIGHT)) <
        (number * gem->query_prop(HEAP_I_UNIT_WEIGHT)))
    {
        number = ((this_player()->query_prop(CONT_I_MAX_WEIGHT) -
            this_player()->query_prop(OBJ_I_WEIGHT)) /
            gem->query_prop(HEAP_I_UNIT_WEIGHT));
    
        if (number <= 0)
        {
            write("You are completely encumbered and cannot handle even " +
                "a single " + gem->query_short() + " extra. None are " +
                "retrieved.\n");
            gem->remove_object();
            return 1;
        }
    
        write("You cannot carry that many " + gem->query_plural_short() +
            ". Therefore only " + number + " " +
            ((number == 1) ? gem->query_short() : gem->query_plural_short()) +
            " will be given to you.\n");
    }
    gem->set_heap_size(number);
    write("You are handed " + LANG_ASHORT(gem) + ".\n");
    gem->move(this_player(), 1);

    GOG_ACCOUNTS->remove_gem(name, bank_id, gem_file, number);

    here = (GOG_ACCOUNTS->query_has_gems(name, bank_id) & 1);
    if (!here)
    {
        write("The " + clerk_race + " says: " +
            ((number == 1) ? "That was" : "Those were") + " the last gem" +
            ((number == 1) ? "" : "s") + " we had for you at this branch " +
            "of the GoG.\n");
    }
    print_account_gems(name);
    write("The " + clerk_race + " says: Thank you for putting your gems " +
        "in our trust.\n");
    say(QCTNAME(this_player()) +
        " retrieves some gems from the Gnomes of Genesis.\n");
    return 1;
}

/*
 * Function name: withdraw
 * Description  : This fucntion is called whenever the player wants to
 *                withdraw some money from his/her account.
 * Arguments    : string str - the command line argument.
 * Returns      : int 1/0 - success/failure.
 */
public int
withdraw(string str)
{
    int    *account_coins;
    int     withdraw_flag;
    int     index;
    int     num_coins;
    string  name = this_player()->query_real_name();
    string  coin_spec, except_spec;
    object  money;
    mixed   coins, except_coins;

#ifdef _april_fools
    if (april_fools()) return 1;
#endif _april_fools
    /* Visibility check on the actor. */
    if (check_not_visible()) return 1;

    if (!strlen(str))
    {
        notify_fail("The " + clerk_race + " says: You have to state amount " +
            "and coin type to withdraw.\n");
        return 0;
    }

    if (!parse_command(str, ({ }), "%s 'except' [for] %s", coin_spec, except_spec))
    {
        coin_spec = str;
        except_coins = allocate(SIZEOF_MONEY_TYPES);
    }
    else
    {
        except_coins = MONEY_PARSE(except_spec);
        if (!pointerp(except_coins))
	{
            notify_fail("The " + clerk_race + " says: Except for what?\n");
            return 0;
	}
    }

    coins = MONEY_PARSE(coin_spec);
    if (!pointerp(coins))
    {
        notify_fail("The " + clerk_race + " says: What coins do you wish " +
            "with withdraw?" +
            (bank_id ? " (use 'retrieve' for gems)" : "") + "\n");
        return 0;
    }

    /* If you want to make some checks before the player withdraws any money,
     * you should define the function no_withdrawal_possible() and if the
     * function returns true, this means that no withdrawal is possible.
     * You should print your own error message.
     */
    if (this_object()->no_withdrawal_possible())
    {
        return 1;
    }

    if (!GOG_ACCOUNTS->query_has_account(name))
    {
        write("The " + clerk_race + " says: Sorry, but you do not seem to " +
            "have an account with us.\n");
        return 1;
    }
        
    write("The " + clerk_race + " does some calculations on an abacus and " +
        "writes something with red ink in a huge ledger.\n");
    if (!GOG_ACCOUNTS->remove_fee(name))
    {
        write("The " + clerk_race + " says: The money deposited in your " +
            "account does not even cover our fee. I am forced to close " +
            "your account and register you as having a low reliability. " +
            "We " + LANG_PWORD(clerk_race) + " do not like to deal with " +
            "people who are not solvent!\n");
        return 1;
    }

    account_coins = GOG_ACCOUNTS->query_account_coins(name);
    for (index = 0; index < sizeof(coins); index++)
    {
        if (except_coins[index] == -1)
        {
            /* We don't want to withdraw any coins of this type */
            coins[index] = 0;
	}
        else if (except_coins[index] > 0)
	{
            /* We don't want to withdraw a certain number of coins of this type. */
            coins[index] -= except_coins[index];
	}

        if (account_coins[index] < coins[index])
        {
            write("The " + clerk_race + " says: You don't have that many " +
                MONEY_TYPES[index] + " coins deposited. After fee deduction " +
                "you have the following money in your account:\n");
            print_account_coins(name);
            return 1;
        }
    }

    for (index = 0; index < sizeof(coins); index++)
    {
        if (!coins[index])
	{
            continue;
	}

        if (coins[index] < 0)
	{
            /* All coins of this type are wanted, except a few maybe */
            coins[index] = max(0, coins[index] + account_coins[index] + 1);
	}

        money = clone_object(COINS_OBJECT);
        money->set_coin_type(MONEY_TYPES[index]);

        /* Let's see if the player isn't too encumbered. */
        if ((this_player()->query_prop(CONT_I_MAX_WEIGHT) -
             this_player()->query_prop(OBJ_I_WEIGHT)) <
            (coins[index] * money->query_prop(HEAP_I_UNIT_WEIGHT)))
        {
            coins[index] = ((this_player()->query_prop(CONT_I_MAX_WEIGHT) -
                this_player()->query_prop(OBJ_I_WEIGHT)) /
                money->query_prop(HEAP_I_UNIT_WEIGHT));
    
            if (coins[index] <= 0)
            {
                write("You are completely encumbered and cannot handle even " +
                    "a single " + MONEY_TYPES[index] + " coin extra. None are " +
                    "withdrawn.\n");
                money->remove_object();
                continue;
            }
    
            write("You cannot carry that many " + MONEY_TYPES[index] +
                " coins. Therefore only " + coins[index] + " " +
                MONEY_TYPES[index] + " coin" + ((coins[index] == 1) ? "" : "s") +
                " will be paid out to you.\n");
        }

        withdraw_flag = 1;    
        money->set_heap_size(coins[index]);
        money->move(this_player(), 1);

        GOG_ACCOUNTS->remove_money(name, index, coins[index]);
    }

    if (!withdraw_flag)
    {
        write("No coins withdrawn.\n");
        return 1;
    }

    environment()->hook_withdraw_coins(secure_var(coins));
    write("You are handed " + MONEY_TEXT(coins) + ".\n");

    /* Tell the player whether he has any money left. */
    account_coins = GOG_ACCOUNTS->query_account_coins(name);
    if (SUM_ARRAY(account_coins) > 0)
    {
        print_account_coins(name, 1);
    }
    else
    {
        write("The " + clerk_race + " says: Since you no longer have any " +
            "coins in our trust, I shall close your account.\n");
    }

    write("The " + clerk_race + " says: Thank you for putting your money " +
        "in our trust.\n");
    say(QCTNAME(this_player()) +
        " withdraws some coins from the Gnomes of Genesis.\n");
    return 1;
}

/*
 * Function name: init
 * Description  : This function is called to add the actions to the player
 *                when he enters the room the strongroom is in.
 */
public void
init() 
{
    ::init();

    add_action(account,     "account");
    add_action(consolidate, "consolidate");
    add_action(deposit,     "deposit");
    add_action(read,        "read");
    add_action(retrieve,    "retrieve");
    add_action(withdraw,    "withdraw");
}

/*
 * Function name: enter_env
 * Description  : If we enter a room, let people know that we are here.
 * Arguments    : object dest - the destination of the strongroom.
 *                object old  - where we came from.
 */
public void
enter_env(object dest, object old)
{
    ::enter_env(dest, old);

    dest->add_my_desc(hook_extra_desc(), this_object());
}

/*
 * Function name: leave_env
 * Description  : The strongroom leaves a room, so remove our add-desc.
 * Arguments    : object old  - the room we leave.
 *                object dest - the destination of the strongroom.
 */
public void
leave_env(object old, object dest)
{
    ::leave_env(old, dest);
   
    old->remove_my_desc(this_object());
}
