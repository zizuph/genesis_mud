/* a pair of bunny slippers  a la Grace */
// converted to /lib/wearable_item by Lilith 09 Jul 1998
//Lilith May 2022: added item_expiration functionality

inherit "/std/object";
inherit "/lib/wearable_item";
inherit "/lib/keep";

#include <wa_types.h>
#include </sys/macros.h>
#include </sys/stdproperties.h>
#include "/d/Avenir/include/defs.h"

void
create_object()
{
    config_wearable_item(A_FEET, 1, 15, this_object());

    set_keep(1);
    if (IS_CLONE)
        set_item_expiration(); 
	
    set_name("slippers");
    set_short("pair of bunny slippers");
    set_long("These slippers are shaped like white rabbits "+
        "with long and floppy ears that drag on the ground and "+
        "can be easily tripped over.\n"+
        "To learn what you can do while wearing these "+
        "slippers, use <help slippers>.\n"+
        "It looks like these can be worn over other kinds of "+
        "footwear.\n");
    set_adj("bunny");
    add_adj("white");
    add_pname(({"clothes", "clothing"})); 

    add_prop("_aod_wear_prop", 1);  // A vanity item ogres can wear.

    add_prop(OBJ_I_VOLUME, 2000);   /* volume 2 litres */
    add_prop(OBJ_I_WEIGHT, 1000);   /* weight of slippers 1 kilo */
    add_prop(OBJ_I_VALUE, 100);

    add_cmd_item("slippers", "help",
       "Here are the emotes associated with the slippers:\n" +
       "    s trip   trip over the ears of the slippers.\n" +
       "    s click  click the heels of the slippers together.\n" +
       "    s pose   strike a child-like posture.\n"+
       "    s toes   wiggle your toes.\n");
}             

int
s_func(string arg)
{
    notify_fail("Do what with the slippers?\n");
    if (!arg) return 0;

    if(!query_worn())
    {
        write("You need to be wearing them, first.\n");
        return 1;
    }

    if (arg == "trip")
    {
        TP->catch_msg("You trod upon the ears of the bunny slippers.\n"+
          "You stagger forward and then spin your arms about in an "+
          "attempt to save yourself from a fall.\n");
        say(QCTNAME(TP) +" trods upon the ears of "+ TP->query_possessive() +
          " bunny slippers.\n" + QCTNAME(TP) + " staggers forward and "+
          "then whirls " + TP->query_possessive() +" arms around, "+
          "somehow managing not to fall on " + TP->query_possessive() + 
          " face!\n");
        return 1;
    }
    if (arg == "click")
    {
        TP->catch_msg("You leap into the air and bring the heels "+
            "of your slippers quickly together, making a loud "+
            "clicking noise.\nThe ears of the bunnies flap like "+
            "wings as you land.\n");
        say(QCTNAME(TP) + " leaps suddenly into the air and clicks "+
            "the heels of "+ TP->query_possessive() +" bunny "+
            "slippers together.\n");
        return 1;
    }
    if (arg == "pose")
    {
        TP->catch_msg("Feeling child-like all of a sudden, you strike "+
            "a pose which leaves you feeling both small and adorable.\n");
        say(QCTNAME(TP) +" strikes a pose which, for a fleeting moment, "+
            "transforms "+ TP->query_objective() +" into a small, adorable "+
            "child.\n");   
        return 1;
    }
    if(arg == "toes")
    {
        TP->catch_msg("You wiggle your toes inside the bunny slippers, "+
            "taking great joy in their comfortable softness.\nThe bunny "+
            "heads bob comically up and down, making you smile.\n");
        say(QCTNAME(TP) + " does something with "+ TP->query_possessive() +
            " feet in the bunny slippers.\nThe bunny heads bob comically "+
            "up and down while "+ QCTNAME(TP) +" smiles joyfully.\n");
        return 1;
    }
}

void
init()
{
    ::init();

    add_action(s_func, "s");
}


/*
 * Function name: leave_env
 * Description:   The clothing is moved from the inventory.
 * Arguments:     from - Where from  to - Destination.
 */
void
leave_env(object from, object to)
{
    wearable_item_leave_env(from, to);
    ::leave_env(from, to);
}


void
appraise_object(int num)
{
    ::appraise_object(num);
    appraise_wearable_item();
}


/*
 * Function name: query_recover
 * Description  : Called to check whether this armour is recoverable.
 *                If, for some reason, you do not want your armour to
 *                recover, you should define the function and return 0.
 * Returns      : string - the default recovery string.
 */
public string
query_recover()
{
    return MASTER + ":"+ query_item_expiration_recover();
}

/*
 * Function name: init_recover
 * Description  : When the object recovers, this function is called to set
 *                the necessary variables. 
 * Arguments    : string argument - the arguments to parse
 */
public void
init_recover(string arg)
{
    init_item_expiration_recover(arg);
}

