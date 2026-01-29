/*
 * /d/Genesis/obj/donation/brooch.c
 *
 * Genesis is a toroid. Holy is the donut! This item is given to the generous
 * people who contributed to Genesis, making it possible to purchase a machine
 * dedicated to running Genesis.
 *
 * Author: Mercade
 * Date  : August 4, 1998
 */

#pragma no_inherit
#pragma strict_types

inherit "/std/object";
inherit "/lib/wearable_item";

#include "donation.h"
#include <cmdparse.h>
#include <composite.h>
#include <language.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

#define TMP_I_INIT_WEAR "_tmp_i_init_wear"
#define ANONYMOUS       "anonymous"
#define VISIBLE         "visible"
#define FIRST           "first"
#define NO_TOPPING      "no topping"
#define SUGAR           "sugar"

#define TP         (this_player())
#define OBJECTIVE  (TP->query_objective())
#define POSSESSIVE (TP->query_possessive())
#define PRONOUN    (TP->query_pronoun())

#define TOPPING_SHORTS ([ \
    "none" : NO_TOPPING, \
    "choco": "chocolate chips", \
    "cream": "whipped cream", \
    "elf"  : "crunchy elf ears", \
    "jelly": "fruity jelly", \
    "nuts" : "sprinkled nuts", \
    "straw": "whole strawberries", \
    SUGAR  : "powdered sugar" ])

/*
 * Global variables.
 */
static private int    anonymous;
static private string brooch_metal;
static private string topping_metal;
static private string topping_type = "none";
/* Just for efficiency at the cost of some memory. */
static private mapping topping_shorts = TOPPING_SHORTS;

/*
 * Function name: update_description
 * Description  : Called to update the long description to reflect the metal
 *                type, topping and anonymity state.
 */
static nomask void
update_description()
{
    string topping_short = topping_shorts[topping_type];

    set_long("It is a toroid shaped brooch, made of the finest " +
        brooch_metal +
        ", presented to you by the mightiest wizards of Genesis in " +
        "recognition of your generous contribution to the Great Battle. " +
        "When the continued existance of Genesis was at stake, the bravest " +
        "forces of the realms gathered and gained a stunning victory! The " +
        "lands of Genesis shall remain open to travellers and explorers who " +
        "shall fight their own battles within. It is smooth and round, and " +
        "on the back, a clasp is moulded. " +
        ((topping_short != NO_TOPPING) ? ("The donut shaped brooch is " +
        "topped with " + topping_metal + " " + topping_short + ".\n") : "\n") +
        "You can examine \"broochhelp\" to see options and customisations.\n" +
        "The metal type of the brooch, " + brooch_metal + ", is " +
        (anonymous ? "hidden from" : "shown to") + " people who examine you.\n");

    set_short((anonymous ? "" : (brooch_metal + " ")) + "toroid shaped brooch");

    if (topping_type == "none")
    {
        add_item( ({ "topping" }),
            "The donut shaped brooch does not have any topping.\n");
    }
    else
    {
        add_item( ({ "topping", (topping_metal + " topping") }),
            "The donut shaped brooch is topped with some very tasty looking " +
            topping_short + ", modelled in " + topping_metal + ".\n");
    }
}

/*
 * Function name: create_object
 * Description  : Constructor.
 */
nomask void
create_object()
{
    setuid();
    seteuid(getuid());

    set_name("brooch");
    add_name(DONOR_BROOCH_ID);
    set_adj( ({ "toroid", "shaped" }) );
    set_short("toroid shaped brooch");

    set_slots(A_CHEST);
    set_layers(0);
    set_looseness(20);
    set_wf(this_object());

    add_item( ({ "back", "pin", "clasp" }),
        "The pin on the back of the toroid shaped brooch enables you to " +
        "clasp this jewel to your garment.\n");
    add_item( ({ "broochhelp" }),
        "Brooch help\n-----------\n" +
        "flip    - flip the brooch in the air for heads/tails.\n" +
        "polish  - polish the brooch to a shine.\n" +
        "twirl   - twirl the brooch around your finger.\n" +
        "topping - select a topping for your brooch (if you are eligible). The command\n" +
        "          \"topping help\" displays the options for toppings.\n\n" +
        "cover metal type   - cover the metal type of the brooch from the view of others\n" +
        "                     when they examine you.\n" +
        "uncover metal type - show the metal type of the brooch to others when they\n" +
        "                     examine you.\n");

    add_prop(OBJ_I_NO_STEAL,    1);
    add_prop(OBJ_I_NO_TELEPORT, 1);
    add_prop(OBJ_I_WEIGHT,     30);
    add_prop(OBJ_I_VOLUME,     10);
    add_prop(OBJ_I_VALUE,       0);
}

/*
 * Function name: cover
 * Description  : Allows a player to cover and uncover the metal type of
 *                the toroid shaped brooch.
 * Arguments    : string str - the command line argument.
 * Returns      : int 1/0 - success/failure.
 */
int
cover(string str)
{
    if (!strlen(str) ||
        !parse_command(str, ({ }), "[the] 'metal' 'type'"))
    {
        notify_fail(capitalize(query_verb()) +
            " what? The metal type perhaps?\n");
        return 0;
    }

    anonymous = (query_verb() == "cover");
    update_description();

    if (anonymous)
    {
        write("You cover the metal type of the toroid shaped brooch. " +
            "People who look at you only see it as 'toroid shaped brooch' " +
            "from now on, without the adjective '" + brooch_metal + "'.\n");
    }
    else
    {
        write("You uncover the metal type of the toroid shaped brooch. " +
            "People who look at you will again see it as '" + brooch_metal +
            " toroid shaped brooch'.\n");
    }

    return 1;
}

/*
 * Function name: emote
 * Description  : This function handles all emotes possible on the brooch.
 * Arguments    : string str - the command line argument.
 * Returns      : int 1/0 - success/failure.
 */
int
emote(string str)
{
    object *oblist = ({ });
    object item;

    if (strlen(str))
    {
        if (parse_command(lower_case(str), TP, "[the] %i", oblist))
        {
            oblist = NORMAL_ACCESS(oblist, 0, 0);
        }
    }

    switch(sizeof(oblist))
    {
    case 0:
        notify_fail("What do you want to " + query_verb() + "?\n");
        return 0;

    case 1:
        item = oblist[0];
        if (item != this_object())
        {
            notify_fail("You seem unable to " + query_verb() + " " +
                LANG_THESHORT(item) + ".\n");
            return 0;
        }
        break;

    default:
        notify_fail("Please " + query_verb() + " only one thing at a time?\n");
        return 0;
    }

    switch(query_verb())
    {
    case "flip":
        str = (random(2) ? "down" : "on top");
        write("You flip your " + brooch_metal + " toroid shaped brooch into the " +
            "air and deftly catch it again. As you grab it from its flight, " +
            "the brooch appears to fall into your hand with the clasp " + str +
            ".\n");
        say(QCTNAME(TP) + " flips " + POSSESSIVE + " " + short() + " into " +
            "the air and deftly catches it again. As " + PRONOUN + " grabs " +
            "it from its flight, the brooch appears to falls into " +
            POSSESSIVE + " hand with the clasp " + str + ".\n");
        break;

    case "polish":
        write("You polish your " + brooch_metal + " toroid shaped brooch and buff " +
            "it to a brilliant shine. For a moment, you admire and " +
            "appreciate the sparkling reflection of the light on its smooth " +
            "surface.\n");
        say(QCTNAME(TP) + " polishes " + POSSESSIVE + " " + short() + " and " +
            "buffs it to a brilliant shine. For a moment, " + PRONOUN +
            " admires and appreciates the sparkling reflection of the light " +
            "on its smooth surface.\n");
        break;

    case "twirl":
        write("You take your " + brooch_metal + " toroid shaped brooch and twirl " +
            "it around your finger as you smile, remembering your " +
            "contribution to the Great Battle.\n");
        say(QCTNAME(TP) + " takes " + POSSESSIVE + " " + short() + " and " +
            "twirls it around " + POSSESSIVE + " finger as " + PRONOUN +
            " smiles, remembering " + POSSESSIVE + " contribution to the " +
            "Great Battle.\n");
        break;
    }

    return 1;
}

/*
 * Function name: topping
 * Description  : This function handles all actions related to selecting a
 *                topping for this brooch, if you are eligible for one.
 * Arguments    : string str - the command line argument.
 * Returns      : int 1/0 - success/failure.
 */
int
topping(string str)
{
    string *toppings = sort_array(m_indices(topping_shorts));
    int index;

    if (!strlen(str))
    {
        notify_fail("What topping? Do \"topping help\" for more info.\n");
        return 0;
    }

    if (str == "help")
    {
        write("Topping help\n------------\n" +
            "Those who are eligible for a topping may select one for their donut shaped\n" +
            "brooch with the command \"topping select <topping>\". The list of available\n" +
            "toppings is (for more choices, mail with brother Donation):\n\n");
        for (index = 0; index < sizeof(toppings); index++)
        {
            toppings[index] = sprintf("%-5s - %s", toppings[index], topping_shorts[toppings[index]]);
        }
        write(sprintf("%-77#s\n", implode(toppings, "\n")));
        return 1;
    }

    if (!strlen(topping_metal))
    {
        notify_fail("You do not have any topping on your donut. Toppings " +
            "available for repeat donors or those with a sizeable single " +
            "donation.\n");
        return 0;
    }

    if (sscanf(str, "select %s", str) != 1)
    {
        notify_fail("Invalid argument, use \"topping help\" for assistance.\n");
        return 0;
    }

    if (!strlen(topping_shorts[str]))
    {
        write("There is no topping \"" + str + "\" available. Choices are: " +
            COMPOSITE_WORDS(m_indices(topping_shorts)) + ".\n");
        return 1;
    }

    if (str == "none")
    {
        write("You remove the topping from your donut brooch.\n");
    }
    else
    {
        write("You select " + topping_shorts[str] +
            " as topping of choice for your donut brooch.\n");
    }
    topping_type = str;
    update_description();
    return 1;
}

/*
 * Function name: init
 * Description  : Links the commands to the player.
 */
void
init()
{
    ::init();

    add_action(cover,   "cover");
    add_action(emote,   "flip");
    add_action(emote,   "polish");
    add_action(topping, "topping");
    add_action(emote,   "twirl");
    add_action(cover,   "uncover");
}

/*
 * Function name: enter_env
 * Description  : When the brooch enters an environment, we must set the
 *                proper type.
 * Arguments    : object to   - the object we are entering.
 *                object from - the object we are leaving.
 */
nomask void
enter_env(object to, object from)
{
    ::enter_env(to, from);

    /* Self destruct if there already is another brooch. */
    if (sizeof(filter(all_inventory(to),
        &operator(==)(DONATION_BROOCH, ) @
        &function_exists("create_object", ))) > 1)
    {
        set_alarm(0.5, 0.0, remove_object);
        return;
    }
 
    /* Query the metal type from the master. */
    brooch_metal = (string)DONATION_MASTER->query_brooch_metal_type(to->query_real_name());
    topping_metal = (string)DONATION_MASTER->query_topping_metal_type(to->query_real_name());

    /* No metal type means no donation. */
    if (!strlen(brooch_metal))
    {
        if (interactive(to))
        {
            tell_object(to, "As we have no registration of a donation by " +
                "you, the toroid shaped brooch self-destructs. If this is " +
                "not correct, please contact the wizard 'Donation'.\n");
        }

        set_alarm(0.2, 0.0, remove_object);
        return;
    }

    /* Set the adjective, the long and possibly the short description. */
    set_adj(brooch_metal);
    update_description();
}

/*
 * Function name: leave_env
 * Description  : When using the wearable library, we must make this call.
 * Arguments    : object from - the object we are leaving.
 *                object to   - the object we are entering.
 */
void
leave_env(object from, object to)
{
     ::leave_env(from, to);

     wearable_item_leave_env(from, to);
}

/*
 * Function name: appraise_object
 * Description  : when using the wearable library, we must make this call.
 * Arguments    : int num - the semi-randomised appraise skill value.
 */
void
appraise_object(int num)
{
    ::appraise_object(num);

    appraise_wearable_item();
}

/*
 * Function name: wear_brooch
 * Description  : At login, this function make sure the brooch is worn
 *                automatically.
 */
void
wear_brooch()
{
    if (!living(environment()))
    {
        return;
    }

    add_prop(TMP_I_INIT_WEAR, 1);

    set_this_player(environment());
    wear_me();

    remove_prop(TMP_I_INIT_WEAR);
}

/*
 * Function name: wear
 * Description  : This function gags the wear-message if you wear it on login.
 * Arguments    : object to_wear - the item to wear.
 * Returns      : int 0/1 - give/gag message.
 */
varargs int
wear(object to_wear)
{
    add_prop(OBJ_M_NO_DROP,
        "To drop the toroid shaped brooch, remove it first.\n");

    return query_prop(TMP_I_INIT_WEAR);
}

/*
 * Function name: wear
 * Description  : This function gags the remove-message if you remove it when
 *                you quit. Only works if the verb "quit" is used.
 * Arguments    : object to_remove - the item to wear.
 * Returns      : int 0/1 - give/gag message.
 */
varargs int
remove(object to_remove)
{
    remove_prop(OBJ_M_NO_DROP);

    return (query_verb() == "quit");
}

/*
 * Function name: introduce_brooch
 * Description  : When the brooch is given to a player when he is not in the
 *                realms, this function is called when it first touches the
 *                player.
 */
nomask void
introduce_brooch()
{
    tell_object(environment(),
        "\nJust out of nowhere, " + LANG_ASHORT(this_object()) +
        " appears in your hand. When the continued existance of Genesis was " +
        "at stake, the bravest forces of the realms gathered and gained a " +
        "stunning victory! The lands of Genesis shall remain open to " +
        "travellers and explorers who shall fight their own battles within. " +
        "Your generous contribution to the Great Battle has been received. " +
        "A confirmation should be in your mailbox. The mightiest wizards of " +
        "Genesis have the honour of presenting this toroid shaped brooch. " +
        (strlen(topping_metal) ? "Your brooch has a topping. You can change " +
            "the default sugar topping to something of your liking. " : "") +
        "In case something is not correct, please contact the wizard " +
        "'Donation'. Thank you!\n\n");
    if (strlen(topping_metal))
    {
        topping_type = SUGAR;
        update_description();
    }
}

/*
 * Function name: query_auto_load
 * Description  : Called to query the autoload string of this object. We pass
 *                the argument ANONYMOUS if the player desires to have the
 *                metal not showing.
 * Returns      : string - the autoload string.
 */
nomask string
query_auto_load()
{
    return DONATION_BROOCH + ":" + (anonymous ? ANONYMOUS : VISIBLE) + "|" +
        topping_type;
}

/*
 * Function name: init_arg
 * Description  : Called when this object autoloads.
 * Arguments    : string arg - the autoload arguments.
 */
nomask void
init_arg(string arg)
{
    string *words = explode(arg, "|");
    int size = sizeof(words);

    anonymous = ((size > 0) ? (words[0] == ANONYMOUS) : 0);
    topping_type = ((size > 1) ? words[1] : "none");

    if (arg == FIRST)
    {
        set_alarm(5.0, 0.0, introduce_brooch);
    }

    set_alarm(1.5, 0.0, wear_brooch);
}
