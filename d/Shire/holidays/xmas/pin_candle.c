/*
 * Holiday pin
 * It's a fun litle item with no use other than some emotes.
 * By Finwe, December 2005
 */

inherit "/std/object";
inherit "/lib/wearable_item";
inherit "/cmd/std/command_driver";
inherit "/lib/keep";

#include "/d/Shire/sys/defs.h"
#include <cmdparse.h>
#include <formulas.h>
#include <files.h>
#include <macros.h>
#include <composite.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>

string pin_type = "candle",
    bod_loc = "right breast";

public void 
create_object()
{
    set_name(({"holiday", "pin"}));
    add_name("_shire_candle_pin");
    set_adj(({"small", "candle"}));
    set_short("small candle pin");
    set_long("This is a nice stick pin in the shape of a candle. It is " +
        "red with a yellow flame above it. It looks festive cheery. " +
        "Something is etched on the back of the pin.\n");

    add_item(({"etchings", "back of pin"}),
        "In fine lettering, almost imperceptible to the eye, you " +
        "see the following commands:\n\n"+
        "       pinpolish      polish your " + pin_type + " pin.\n" +
        "       pinjab         jab someone to get their attention.\n" +
        "       pinrub         improve your luck.\n" +
        "       pinbored       show how interested you are.\n" +
        "       pinroll        roll your " + pin_type + " pin " +
        "between your fingers.\n\n");

    add_prop(OBJ_I_VOLUME,  23);
    add_prop(OBJ_I_WEIGHT,  57);
    add_prop(OBJ_I_VALUE,  100);
    set_keep(1); 
    set_slots(A_CHEST);
    set_layers(1);
    set_looseness(20);
    wear_func = this_object();
}

/*
 * Function name: init
 * Description  : Links the commands to the player.
 */
void
init()
{
    ::init();

    add_action("polish", "pinpolish");
    add_action("polish", "xpol");
    add_action("polish", "pinpol");
    add_action("jab",    "pinjab");
    add_action("jab",    "xjab");
    add_action("bored",  "pinbored");
    add_action("bored",  "pinbor");
    add_action("bored",  "xbor");
    add_action("roll",   "pinroll");
    add_action("roll",   "pinrol");
    add_action("roll",   "xrol");
}

/*
 * Function name: wear
 * Description  : This function is called when someone tries to wear
 *                this item. 
 * Arguments    : object obj - The armour we want to wear.
 * Returns      : int  0 - The item can be worn normally.
 *                     1 - The item can be worn, but print no messages.
 *                    -1 - The item can't be worn, use default messages.
 *                string - The item can't be worn, use this message.
 */
public mixed
wear(object obj)
{
    if (wearer != environment(this_object()))
    {
        return 0;
    }

    write("You pin the " + short() + " onto your " + bod_loc + ".\n");
    say(QCTNAME(this_player()) + " pins a " + short() + " onto " +
        this_player()->query_possessive()  + bod_loc + ".\n");

    worn = 1;
    this_player()->add_subloc(file_name(this_object()), this_object());
    return 1;
}


/*
 * Function name: remove
 * Description  : This function is called when someone tries to remove
 *                this item.
 * Arguments    : object obj - The item to remove.
 * Returns      : int  0 - Remove the item normally.
 *                     1 - Remove the item, but print no messages.
 *                    -1 - Do not remove the item, print default message.
 *                string - Do not remove the item, use this message.
 */
public mixed
remove(object obj)
{
    if (wearer != environment(this_object()))
    {
        return 0;
    }

    write("You remove the " + short() + " from your " + bod_loc + ".\n");
    say(QCTNAME(this_player()) + " removes a " + short() + " from " +
        this_player()->query_possessive() +  bod_loc + ".\n");

    worn = 0;
    this_player()->remove_subloc(file_name(this_object()));
    return 1;
}

/*
 * Function name: show_subloc
 * Description  : Shows the specific sublocation description for a living.
 * Arguments    : string subloc  - the subloc to display.
 *                object on      - the object to which the subloc is linked.
 *                object for_obj - the object that wants to see the subloc.
 * Returns      : string - the subloc description.
 */
public string
show_subloc(string subloc, object on, object for_obj)
{

    if (subloc != file_name(this_object()))
    {
	return "";
    }

    if (for_obj != on)
    {
        return (capitalize(on->query_pronoun()) + " is wearing " +
            "a " + short() + " on "+HIS_HER(TP) + 
            bod_loc + "\n");
    }
    else
    {
        return "You are wearing the " + short()+" on " +
            "your " + bod_loc + ".\n";
    }
}


/*
 * Function name: leave_env
 * Description  : When you inherit /lib/wearable_item.c into any object other
 *                than /std/armour.c you MUST also define the function
 *                leave_env() as copy of this function. It MUST make the
 *                call to wearable_item_leave_env(from, to) as well. If
 *                you omit this, then the item will not be automatically
 *                removed when the player drops it, for instance.
 *                PS: This is just a dummy function. It does not exist. You
 *                    must write your own as copy of this one.
 * Arguments    : object from - the environment we are leaving.
 *                object to   - the environment we are entering.
 */
public void
leave_env(object from, object to)
{
    wearable_item_leave_env(from, to);
    ::leave_env(from, to);
}

/*
 * Function name: appraise_object
 * Description  : When you inherit /lib/wearable_item.c into any object
 *                other than /std/armour.c you MUST also define the function
 *                appraise_object() as copy of this function. It MUST make
 *                the call to appraise_wearable_item() as well. If you omit
 *                this, then the player will not be able to appraise this
 *                item properly.
 *                PS: This is just a dummy function. It does not exist. You
 *                    must write your own as copy of this one.
 * Arguments    : int num - the semi-randomised appraise skill.
 */
public void
appraise_object(int num)
{
    ::appraise_object(num);
    appraise_wearable_item();
}

// Emotes


public int
jab(string str)
{
    object *oblist;
    if(!strlen(str)) /* no string supplied */
    {
	write("Jab who with your " + short() + "?\n");
	return 1;
    }

    oblist = parse_this(str, "[the] %l");

    if(!sizeof(oblist))
    {
	write("Jab who with your " + short() + "?\n");
	return 1;
    }
    actor("You jab", oblist, " with your " + short() + ", who " +
        "yelps in surprise and jumps away from you.");
    target(" jabs you with "+HIS_HER(TP)+" "+short()+
        "! You yelp in surprise and jump back away from "+
        HIM_HER(TP)+"!",oblist);
    all2act(" jabs", oblist, " with " +HIS_HER(TP)+" "+
         short()+", who yelps and jumps back in surprise.");
    return 1;
}   

public int
polish(string str)
{

    if(str == "pin" || str == "hoiday pin")
    {
    write("You polish your " + short() + " until it glistens.\n");
    say(QCTNAME(TP) + " polishes "+HIS_HER(TP)+" " + short() + " until it glistens.\n");
    return 1;
    }
    notify_fail("Polish what? Your holiday pin?\n");

}


public int
bored(string str)
{
      object *oblist;
    if(!strlen(str)) /* no string supplied */
    {
	write("Ho hum! You show everyone you're so bored that you " +
        "begin cleaning your nails with your " +short()+".\n");
	all(" is so bored "+HE_SHE(TP)+" begins cleaning his nails " +
        "with "+ HIS_HER(TP) +" " +short()+".",oblist);
	return 1;
    }

    oblist = parse_this(str, "[the] %l");

    if(!sizeof(oblist))
    {
	write("Show you're bored of who?\n");
	return 1;
    }

    actor("Ho hum! You show everyone you're so bored of", oblist, 
        " that you begin cleaning your nails with your " +short()+"."); 
    target(" is so bored with you that " + HE_SHE(TP) +
        " begins cleaning " + HIS_HER(TP)+" nails with " + 
        HIS_HER(TP) +" " +short()+".", oblist);
    all2act(" becomes bored with",oblist," and begins cleaning " + 
        HIS_HER(TP) + " nails with "+HIS_HER(TP)+" "+short()+".",oblist);
    return 1;
}   


int
roll(string str)
{
    object *oblist;
    if(!strlen(str)) /* no string supplied */
    {
	write("You roll the " +short()+" between your fingers. A " +
        "white blur seems to float above your fingers.\n");
	all(" rolls a "+short()+" between " + HIS_HER(TP) + 
        " fingers. A white blur seems to float above "+ 
        HIS_HER(TP) +" fingers.");
	return 1;
    }
}
