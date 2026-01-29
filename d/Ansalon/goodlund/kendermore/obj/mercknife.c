/* Special knife for Jane the Mercenary, Gwyneth, June 1999 
 * 
 * Changes:
 * Cotillion - 2018-11-08  
 * 
 */

#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
inherit "/lib/keep";
inherit "/std/weapon";

int knife_offensive = 0;
int knife_defensive = 0;
int knife_normal = 1;
int skill_bonus = 0;

create_weapon()
{
    set_name(({"knife","_jane_knife_","weapon"}));
    set_pname(({"knives", "weapons"}));
    set_adj("long");
    add_adj("narrow");
    set_short("long narrow knife");
    set_pshort("long narrow knives");
    set_long("This is a very fine blade. It's almost as long as a short " + 
        "sword, but narrow like a knife. The hilt is wrapped in leather, " + 
        "and gives a firm grasp. You feel you could fight normally, " + 
        "defensively or offensively.\nThe long narrow knife emits a faint " + 
        "silver glow.\n");
    set_default_weapon(25, 25, W_KNIFE, W_SLASH, W_ANYH); /* Can't wield */
                                                           /* two at once */
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(OBJ_S_WIZINFO, "This knife has three modes of fighting, " +
        "offensive, defensive, and normal. The first mode, offensive, " +
        "sets the hit/pen of the knife to 25 + 1/10 of the wielder's " +
        "knife skill. Sets defence skill ten less than normal, or to 0 if " +
        "defence skill is 10 or less. The second mode, defensive, " +
        "sets the hit/pen of the knife to 25 - (10 - 1/10 of the wielder's " +
        "knife skill). Sets defence skill ten more than normal if skill is " +
        "less than 100. The third mode, normal, resets the knife to normal " +
        "defense, and normal 25/25 hit/pen.\n");
    add_prop(MAGIC_AM_ID_INFO, ({ "This slender blade holds an aura of " +
        "enchantment.\n", 20, "The knife was enchanted long ago to enable " +
        "the owner to fight in three different ways, as normally as one " +
        "can with a fine enchanted blade, with a determination to " +
        "all of one's enemies, and finally, to enable one to block attacks " +
        "attacks much more than usual.\n", 40, "Unfortunately, being so " +
        "blindly determined to obliterate one's enemies leads to a " +
        "slight disregard for one's safety. Also being so complete in one's " +
        "defence leads to few scores on the enemy.\n", 50}));
    add_prop(MAGIC_AM_MAGIC, ({ 75, "enchantment" }));
    add_prop(OBJ_I_WEIGHT, 2000);
    add_prop(OBJ_I_VOLUME, 1000);
    set_keep(1);
    set_wf(TO);
    seteuid(getuid(TO));
}

/* Function name : Wield
 * Description : Sets wielder to the person wielding the knife.
 * Returns : 0
*/

mixed
wield(object what)
{
    object *weapons = TP->query_weapon(-1);
    if (sizeof(filter(weapons - ({ this_object() }), &->id("_jane_knife_"))) > 0)
    {
        return("You don't feel comfortable wielding two long narrow " + 
                "knives at once.\n");
    }

    return 0;
}

/* Function name : Unwield
 * Description : Calls the do_normal function which resets the knife and
 *     defence skill to normal. Unsets the person wielding the knife as
 *     wielder.
 * Returns : Null
*/

mixed
unwield(object what)
{
    TO->do_normal();
}

/* Function name : Normal mode
 * Description : Sets the hit/pen of the knife back to normal, and resets
 *     the defence skill of the wielder to normal. Sets defensive and
 *     offensive status to false, normal status to true.
 * Returns : Null
*/

void
do_normal()
{
    if (knife_normal) 
        return;
    query_wielded()->set_skill_extra(SS_DEFENCE, (query_wielded()->query_skill_extra(SS_DEFENCE) - skill_bonus));
    set_pen(25);
    set_hit(25);
    knife_normal = 1;
    knife_defensive = 0;
    knife_offensive = 0;
}

 /* Function name : Offensive mode
 * Description : Calls the normal mode function to reset hit/pen/defence.
 *     Sets the hit/pen of the knife to 25 + 1/10 of the wielder's
 *     knife skill. Sets defence skill ten less than normal, or to 0 if
 *     defence skill is 10 or less. Sets normal and defensive status to
 *     false, offensive status to true. 
 * Returns : Null
*/

void
do_offensive()
{
    int pen_bonus, hit_bonus;

    if(TP != wielder)
        return;

    do_normal();
    pen_bonus = wielder->query_skill(SS_WEP_KNIFE) /10;
    hit_bonus = wielder->query_skill(SS_WEP_KNIFE) /10;
    if(wielder->query_skill(SS_DEFENCE) > 9)
        skill_bonus = -10;
    if(wielder->query_skill(SS_DEFENCE) < 10)
        skill_bonus = (-1) * wielder->query_skill(SS_DEFENCE);
    wielder->set_skill_extra(SS_DEFENCE,
        wielder->query_skill_extra(SS_DEFENCE) + skill_bonus);

    set_pen(25 + pen_bonus);
    set_hit(25 + hit_bonus);
    knife_offensive = 1;
    knife_normal = 0;
    knife_defensive = 0;
    wielder->update_weapon(TO);
}

/* Function name : Defensive mode
 * Description : Calls the normal mode function to reset hit/pen/defence.
 *     Sets the hit/pen of the knife to 25 - (10 - 1/10 of the wielder's
 *     knife skill). Sets defence skill ten more than normal if skill is
 *     less than 100. Sets normal and offensive status to false, defensive
 *     status to true.
 * Returns : Null
*/

void
do_defensive()
{
    int pen_bonus, hit_bonus;
    if(TP != wielder)
        return;
    do_normal();
    pen_bonus = (100 - wielder->query_skill(SS_DEFENCE)) /10;
    hit_bonus = (100 - wielder->query_skill(SS_DEFENCE)) /10;
    if(wielder->query_skill(SS_DEFENCE) < 100)
        skill_bonus = 10;
    if(wielder->query_skill(SS_DEFENCE) > 99)
        skill_bonus = 0;
    wielder->set_skill_extra(SS_DEFENCE,
        wielder->query_skill_extra(SS_DEFENCE) + skill_bonus);

    set_pen(25 - pen_bonus);
    set_hit(25 - hit_bonus);
    knife_defensive = 1;
    knife_offensive = 0;
    knife_normal = 0;
    wielder->update_weapon(TO);
}

/* Function name : Switch stance
 * Description : Checks to see if knife is wielded, and if the wielder can
 *     switch to the desired stance. Calls the appropriate mode functions
 *     if possible.
 * Returns : 0 or 1
*/

int
switch_stance(string str)
{
    if(!str)
        return 0;

    if(str != "offensively")
        if(str != "defensively")
            if(str != "normally")
                return 0;

    if (TP != query_wielded())
    {
        write("You must be wielding the knife first!\n");
        return 1;
    }

    if (query_wielded()->query_fatigue() < 10)
    {
        write("You are too tired to change fighting stances. It's all you " + 
            "can do to keep on your feet as it is!\n");
        return 1;
    }

    if (str == "offensively")
    {
        if(knife_offensive)
        {
            write("You are already in an offensive stance.\n");
            return 1;
        }
        else
        {
            write("You hold the long narrow knife away from your body in an " + 
                "offensive stance. You feel a bit more vulnerable to " + 
                "attacks now.\n");
            say(QCTNAME(wielder) + " steps forward, " + 
            "holding " + HIS(wielder) + " long narrow knife in a position " + 
            "to attack more readily.\n");
            do_offensive();
            return 1;
        }
    }

    if (str == "defensively")
    {
        if(knife_defensive)
        {
            write("You are already in a defensive stance.\n");
            return 1;
        }
        else
        {
            write("You draw the long narrow knife closer to your body, " + 
                "ready to defend yourself.\n");
            say(QCTNAME(wielder) + " falls back a step, " + 
                "drawing " + HIS(wielder) + " long narrow knife " + 
                "closer to " + HIS(wielder) + 
                " body.\n");
            do_defensive();
            return 1;
        }
    }

    if (str == "normally")
    {
        if(knife_normal)
        {
            write("You are already in a normal stance.\n");
            return 1;
        }
        else
        {
            write("You choose to use the long narrow knife neither " + 
                "offensively nor defensively.\n");
            say(QCTNAME(wielder) + " steps into a normal " + 
                "stance.\n");
            do_normal();
            return 1;
         }
    }
}

/* Function name : Init
 * Description : Adds the command 'fight' to the command list.
 * Returns : Null
*/

void
init()
{
    ::init();
    add_action("switch_stance","fight");
}

