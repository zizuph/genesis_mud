/* Circlet of thorns for Kendermore, Gwyneth, June 1999 */
/* Modified by Morrigan June 2004 to not show messages to */
/*     players who cannot see this player */
/* Milan 22.6.2004 tried to fix runtime errors and alarms */
/* Petros 21.9.2013 reduced the mana amount recovered if using new mana shadow */

inherit "/std/armour";
inherit "/lib/keep";
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"
#include <macros.h>
#include <filter_funs.h>

int worn, pain_alarm;

void
create_armour()
{
    set_name("thorns");
    set_adj("silvery");
    add_adj("woven");
    set_short("intricately woven silvery thorns");
    set_pshort("circlets of silvery thorns");
    set_long("@@query_pain_amt");
    set_at(A_NECK);
    add_prop(OBJ_M_NO_SELL, "The shopkeeper refuses to touch the sharp " + 
        "thorns!\n");
    add_prop(OBJ_I_VALUE, 40000);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_M_NO_GIVE, "You attempt to give the intricately woven " +
        "silvery thorns away, but the thorns are too sharp.\n");
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(MAGIC_AM_MAGIC, ({50, "enchantment"}));
    add_prop(MAGIC_AM_ID_INFO, ({"This circlet of thorns was enchanted by " + 
        "a red robe mage.\n", 10, "The circlet drains some of the life " + 
        "from anyone who wears it.\n", 25, "The thorns reward the wearer " + 
        "with a portion of their life in the form of increased mental " + 
        "strength.\n", 35})); 

    set_af(TO);
    seteuid(getuid(TO));

    worn = 0;
}

/* Function name : Pain amount
 * Description   : Gives a long description dependant on the wearer's current
 *                 hit points as a warning before wearing.
 * Returns       : The long description.
*/

string
query_pain_amt()
{
    string long = ("These thorns are woven in such an intricate " + 
        "pattern that you wonder what its purpose is. Light seems to be " + 
        "drawn inside the thorns instead of reflected off their metallic " + 
        "surface. The sharp tips of the thorns look ");
    if ((TP->query_hp()) < 501)
        return (long + "deadly to the touch.\n");
    if ((TP->query_hp() > 500)&&(TP->query_hp() < 751))
        return (long + "almost deadly to the touch.\n");
    if ((TP->query_hp() > 750)&&(TP->query_hp() < 1501))
        return (long + "very painful to the touch.\n");
    if ((TP->query_hp()) > 1500)
        return (long + "painful to the touch.\n");
    return (long + "painful to the touch.\n");
}

void
wear_pain(object tp)
{
    set_this_player(tp);
    tp->heal_hp(-400-random(100));
    if (tp->query_hp() <= 0)
    {
        write("The silvery thorns seem to come alive. They dig themselves " +
            "deeper into your throat, draining the blood from your body. " +
            "Your vision goes black, and you know your death is coming.\n");
        say(QCTNAME(tp) + "'s eyes widen as the silvery thorns begin to " +
            "move. They work themselves into " + HIS(tp) + " throat, and " +
            HIS(tp) + " face turns a ghastly white. " + QCTNAME(tp) +
            " collapses as " + HIS(tp) + " life is drained away.\n");
        tp->do_die(TO);
    }
}

/* Function name : Cause pain
 * Description   : Lowers the wearer's hit points by 400 + random(100).
 *                 Makes the wearer die if appropriate.
 * Returns       : Null
 */
void
cause_pain(object tp)
{
    object *gaglist = ({ tp });
    object *all;
    int i;

    if (!worn)
        return;

    pain_alarm = set_alarm(30.0, 0.0, &cause_pain(tp));

    /* This routine should NOT fire while the player is LD. TESTING for HP is
     * also NOT good while the person is LD. */
    if (!interactive(tp))
        return;

    set_this_player(tp);
    all = FILTER_LIVE(all_inventory(E(tp))) - ({ tp });
    for (i=sizeof(all)-1; i>=0; i--)
    {
        if (objectp(all[i]) && (!CAN_SEE(all[i], tp) || !CAN_SEE_IN_ROOM(all[i])))
			gaglist += ({ all[i] });
    }
    
    tp->heal_hp(-100-random(100));
    // Due to the changes in mana regeneration in the mana shadow (reduce mana pool
    // by 1/3, increase regeneration by 3x), players in guilds that use the mana
    // shadow already recover mana 9x faster than before. We will reduce the amount
    // by 1/3 in order to have the same effect on these players as players who
    // don't have the mana shadow.
    int mana_heal_amount = 30 + random(20);
    if (tp->has_mana_shadow())
    {
        mana_heal_amount = mana_heal_amount / 3;
    }
    tp->add_mana(mana_heal_amount);
    tp->add_panic(20 + random(10));

    if ((tp->query_hp() <= 500)&&(tp->query_hp() >= 0))
    {
        write("You fall to your knees in pain as the silvery thorns bury " +
            "themselves even deeper into your neck.\n");
        say(QCTNAME(tp) + " falls to " + HIS(tp) + " knees in pain.\n", gaglist);
    }

    if ((tp->query_hp() > 500)&&(tp->query_hp() <= 750))
    {
        write("Pain soars through your body as the silvery thorns bury " +
            "themselves deeper into your neck.\n");
        say(QCTNAME(tp) + " closes " + HIS(tp) + " eyes in pain.\n", gaglist); 
    }

    if ((tp->query_hp() > 750)&&(tp->query_hp() <= 1500))
    {
        write("You feel a bit faint from the pain as the silvery thorns " +
            "bury themselves deeper into your neck.\n");
        say(QCTNAME(tp) + " shuts " + HIS(tp) + " eyes briefly in pain.\n", gaglist);
    }

    if (tp->query_hp() > 1500)
    {
        write("You feel a bit of pain as the silvery thorns bury " +
            "themselves deeper into your neck.\n");
        say(QCTNAME(tp) + " winces slightly in pain.\n", gaglist);
    }

    if (tp->query_hp() <= 0)
    {
        write("The silvery thorns seem to come alive. They dig themselves " +
            "deeper into your throat, draining the blood from your body. " +
            "Your vision goes black, and you know your death is coming.\n");
        say(QCTNAME(tp) + "'s eyes widen as the silvery thorns begin to " +
            "move. They work themselves into " + HIS(tp) + " throat, and " +
            HIS(tp) + " face turns a ghastly white. " + QCTNAME(tp) +
            " collapses as " + HIS(tp) + " life is drained away.\n", gaglist);
        tp->do_die(TO);
        remove_alarm(pain_alarm);
    }
    return;
}

/* Function name : Wear
 * Description   : Gives a description when wearing the object dependant on
 *                 the wearer's current hit points. Subtracts 400 + 
 *                 random 100 hps. Adds 20 + random(20) panic. Adds
 *                 70 + random(20) mana. 
 * Returns       : 0 or 1
 */
mixed
wear(object what)
{
    if (what != TO)
        return 0;

    worn = 1;

    set_alarm(0.5,0.0, &wear_pain(TP));
    pain_alarm = set_alarm(30.0,0.0, &cause_pain(TP));

    if ((TP->query_hp() <= 500))
    {
        write("You fall to your knees in pain as the silvery thorns bury " + 
            "themselves deeply into your neck.\n");
        say(QCTNAME(TP) + " falls to " + HIS(TP) + " knees in pain " + 
            "as " + HE(TP) +
            " wears the intricately woven silvery thorns.\n");
    }

    if ((TP->query_hp() > 500)&&(TP->query_hp() <= 750))
    {
        write("Pain soars through your body as the silvery thorns bury " +
            "themselves deeply into your neck.\n");
        say(QCTNAME(TP) + " closes " + HIS(TP) + " eyes in pain as " + HE(TP) +
            " wears the intricately woven silvery thorns.\n");
    }

    if ((TP->query_hp() > 750)&&(TP->query_hp() <= 1500))
    {
        write("You feel a bit faint from the pain as the silvery thorns " + 
            "bury themselves deeply into your neck.\n");
        say(QCTNAME(TP) + " shuts " + HIS(TP) + " eyes briefly as " + HE(TP) +
            " wears the intricately woven silvery thorns.\n");
    }

    if (TP->query_hp() > 1500)
    {
        write("You feel a bit of pain as the silvery thorns bury " + 
            "themselves deeply into your neck.\n");
        say(QCTNAME(TP) + " winces slightly as " + HE(TP) + " wears the " + 
            "intricately woven silvery thorns.\n");
    }

    return 1;
}

/* Function name : Remove
 * Description   : Gives a message when removing the object, and sets the
 *                 worn status to false.
 * Returns       : 0 or 1
 */
mixed
remove(object what)
{
    if (what != TO || !TP)
        return 0;

    remove_alarm(pain_alarm);
    write("You feel very relieved as you remove the thorns from " +
        "your neck.\n");
    say(QCTNAME(TP) + " removes the intricately woven thorns " +
        "from " + HIS(TP) + " neck, and looks very relieved.\n");

    worn = 0;
    return 1;
}
