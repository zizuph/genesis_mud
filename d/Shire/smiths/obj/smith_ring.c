// ringslap -- backhand, slap leaves bruises on target
// ringmark -- leaves a mark on items.

/* Special ring given to Smiths who wone the 
 * "Guess the necklace level" contest.
 * Ringmark is a modified version of the smith mark
 * Finwe, January 2002
 */

#pragma save_binary

inherit "/std/object";
inherit "/lib/wearable_item";
inherit "/lib/keep";

#include <cmdparse.h>
#include <macros.h>
#include <stdproperties.h>
#include <composite.h>
#include <wa_types.h>
#include <filter_funs.h>
#include <formulas.h>
#include <language.h>
#include <std.h>
#include "/d/Shire/sys/defs.h"

#define SUBLOC "smith_ring"

// Global Vars
object find_item(string str,string error);

void
create_object()
{
    set_name("ring");
    add_adj(({"white" ,"gold"}));
    add_name("_smith_ring_reward");
    add_name("band");
    set_short("white gold ring");
    set_long("The ring is a band of white gold, perfectly smooth " +
        "and polished. On the top of the ring is a hammer " +
        "striking a forge with a border of a twining ivy leaves. " +
        "It was won in a special Smiths guild contest for " +
        "learning the levels of the necklace. There are some " +
        "engravings inside the ring.\n");

    add_item(({"leaves", "twining ivy leaves", "ivy leaves"}),
        "The ivy leaves are golden replicas of trailing ivy. It " +
        "is hammered onto both edges of the ring, running around " +
        "the outside of the ring.\n");

    add_item("engravings", "They are small letters that have been " +
        "etched inside the ring with some instructions. Perhaps you " +
        "should read them.\n");
    add_cmd_item( ({"engravings", "letters", "small letters", 
            "instructions", "faint engravings"}),
        "read", "@@read_inscription@@");

    set_slots(A_ANY_FINGER);
    set_layers(0);
    set_looseness(2);

    add_prop(OBJ_I_WEIGHT,  20);
    add_prop(OBJ_I_VOLUME,  50);
    add_prop(OBJ_I_NO_DROP,  1);
    add_prop(OBJ_M_NO_STEAL, 1);
    add_prop(OBJ_M_NO_GIVE,  1);

}

void
init()
{
    ::init();
    add_action("flip",     "riflip");
    add_action("flip",     "rifl");
    add_action("idle",     "riidle");
    add_action("idle",     "riid");
    add_action("mark",     "rimark");
    add_action("mark",     "rima");
    add_action("mutter",   "rimutter");
    add_action("mutter",   "rimu");
    add_action("patience", "ripatience");
    add_action("patience", "ripa");
    add_action("polish",   "ripolish");
    add_action("polish",   "ripo");
    add_action("roll",     "riroll");
    add_action("roll",     "riro");  
    add_action("rub",      "rirub");
    add_action("rub",      "riru");
}

string
read_inscription()
{
    return "On the inside of the ring you read:\n"+
        "\n\tAwarded to "+TP->query_name()+" for winning the Smiths Guild Contest\n\n" +
        "You also see the following words etched elsewhere inside the ring:\n"+
        "\t(rifl)ip, (riid)le, (rima)rk, (rimu)tter, \n"+
        "\t(ripa)tience, (ripo)lish, (riro)ll, (riru)b\n";
}

void
enter_env(object to, object from)
{
    if (living(to))
	to -> add_subloc(SUBLOC, this_object());
    ::enter_inv(to, from);
}


public void
leave_env(object from, object to)
{
    ::leave_env(from, to);
    if (living(from))
	from -> remove_subloc(SUBLOC);
    wearable_item_leave_env(from, to);
}

/*
 * We need to override appraise_object() so that we can be sure that the
 * player can appraise it properly.
 */
void
appraise_object(int num)
{
    ::appraise_object(num);

    appraise_wearable_item();
}

/*
 * Function name: show_subloc
 * Description  : Shows the specific sublocation description for a living.
 * Arguments    : string subloc  - the subloc to display.
 *                object on      - the object to which the subloc is linked.
 *                object for_obj - the object that wants to see the subloc.
 * Returns      : string - the subloc description.
 */
string
show_subloc(string subloc, object me, object for_obj)
{
    string str;
    if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
	return "You are wearing your Smiths Guild contest ring.\n";

    if (for_obj == me)
		return "You are wearing your Smiths Guild contest ring.\n";

    else
	str = capitalize(me->query_possessive()) + " wears ";
    return str + "a " + short()+" on "+HIS_HER(me)+" finger, declaring "+
        HIM_HER(me)+" a winner in the Smiths Guild contest.\n";
}

/*
 * Function name: query_auto_load
 * Description  : Return the filename of this module to allow it to be
 *                autoloadable.
 * Returns      : string - the filename of this module.
 */
public string 
query_auto_load() 
{
    return MASTER + ":"; 
}


/****************************************************************
 * Ring Emotes                                                  *
 ****************************************************************/
/*
 * flip - flip the ring up in the air
 */
int
flip()
{
    if(query_worn())
    {
        write("You must remove the " +short()+" first.\n");
        return 1;
    }


    write("You flip the "+short()+" up in the air. It spins, " +
        "twinkling in the light, before you deftly catch it in " +
        "the air.\n");
    say(QCTNAME(TP) + "flips "+HIS_HER(TP)+" "+short()+
        ". It spins, twinkling in the light, before "+HE_SHE(TP)+
        " deftly catch it in the air.\n");
    return 1;
}

/*
 * idle - idly do something with the ring
 */
int
idle()
{
    if(!query_worn())
    {
        write("You must be wearing the " +short()+".\n");
        return 1;
    }
    
    write("You idly spin the "+short()+" around your finger.\n");
    say(QCTNAME(TP) + " idly spins "+HIS_HER(TP)+" "+short()+
        " around "+HIS_HER(TP)+" finger.\n");
    return 1;
}

/*
 * mark - special mark for armours and weapons
 */

int
mark(string str) 
{
    object obj;
    string marked="obj_has_rimark";

    if(!query_worn())
    {
        write("You must be wearing the " +short()+".\n");
        return 1;
    }

    obj=find_item(str,"mark");

    if (obj==0) return 1;

    if (obj->query_prop(marked))
    {
	write("You have already marked this item once.\n");
	return 1;
    }

    if (!IS_ARMOUR_OBJECT(obj) && !IS_WEAPON_OBJECT(obj))
    {
        write("You can only mark weapons and armours.\n");
        return 1;
    }
/*
    if ((obj->query_prop(OBJ_I_IS_MAGIC_WEAPON)) 
      || (obj->query_prop(OBJ_I_IS_MAGIC_WEAPON)))
      {
	write("This item is too valuable to receive your mark.\n");
	return 1;
    }
*/
    write("You mark the item with your personal mark.\n");
    obj->set_long(obj->query_long()+"It is marked with an " +
        "impression of a hammer striking an anvil. The name "+
        TP->query_name()+" is stamped underneath the anvil. " +
        "Half circles of twining ivy are at the top and bottom " +
        "of the mark.\n");
    obj->add_prop(marked,1);

    return 1;
}


/*
 * mutter - mutter something under your breath
 */
int
mutter()
{
    write("You mutter something under your breath.\n");
    say(QCTNAME(TP) + " mutters something under "+HIS_HER(TP)+
        " breath.\n");
    return 1;
}

/*
 * patience - urge everyone to have patience
 */
int
patience()
{
    write("You advise everyone to be patient, like you when you " +
        "forge as a Smith.\n");
    say(QCTNAME(TP) + " advises you to be patient, like "+HE_SHE(TP)+
        " is when forging as Smith.\n");
    return 1;
}

/*
 * polish - polish the ring
 */
int
polish()
{
    write("You polish the "+short()+". It gleams and " +
        "twinkles in the light.\n");
    say(QCTNAME(TP) + " polishes "+HIS_HER(TP)+" "+short()+
        ". It gleams and twinkles in the light.\n");
    return 1;
}

/*
 * roll - roll the ring across the fingers
 */
int
roll()
{

    if(query_worn())
    {
        write("You must remove the " +short()+" first.\n");
        return 1;
    }
    
    write("You roll the "+short()+" across your fingers " +
        "absentmindedly.\n");
    say(QCTNAME(TP) + " rolls "+HIS_HER(TP)+" "+short()+
        " across "+HIS_HER(TP)+" fingers absentmindedly.\n");
    return 1;
}

/*
 * rub - rub the ring remembering the contest
 */
int
rub()
{
    write("You rub the "+short()+", wistfully recalling the " +
        "contest you won to get the ring.\n");
    say(QCTNAME(TP) + " rubs "+HIS_HER(TP)+" "+short()+
        ", wistfully recalling the contest "+HE_SHE(TP)+" won to " +
        "get the ring.\n");
    return 1;
}


/****************************************************************
 * Miscellaneous routines                                       *
 ***************************************************************/

/*
 * find_item - called by ring mark
 */

object find_item(string str,string error)
{
    object obj;
    object *to_mark;

    notify_fail(CAP(error)+" what?\n");
    if (!strlen(str))
    {
	    return obj;
    }

    if ((!parse_command(str, TP, "[the] %i", to_mark)) ||
      (!sizeof(to_mark = NORMAL_ACCESS(to_mark, 0, 0))))
    {
	    return obj;
    }

    if (sizeof(to_mark) != 1)
    {
	    write("Please select only one item to "+error+".\n");
	    return obj;
    }
    else
    {
	    obj = to_mark[0];
    }

    return obj;
}
