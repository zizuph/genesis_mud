/* The magical hacchak 'The Seeker'
 * By Elmore.
 * Type: Polearm.
 * Info: A quest reward for solving the Jilan Quest in Mithas.
 * 
 */

inherit "/std/weapon";
inherit "/lib/keep";

#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <options.h>
#include <filter_funs.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/goodlund/nethosak/forest/local.h"

#define NORMALHIT 49
#define NORMALPEN 39

#define KENDERHIT 55
#define KENDERPEN 45

create_weapon()
{
    set_name("hacchak");
    add_name("seeker");
    add_name("_jilans_weapon_");
    set_adj("ornate");
    set_short("ornate hacchak");
    set_long("This long weapon, is one of the heaviest of all kender weapons. "+
             "This polearm is over six feet in length where one end has a hammer "+
             "spike and piercing beak. The other end is an axe backed by a hammer head "+
             "and saw blade. The middle of the weapon is wrapped in soft skin, and "+
             "some thick metal rings circle the entire handle. The weapon looks "+
             "sleeker and feels much lighter then any of the known weapons. This "+
             "is truely a magnificent piece of art. The grip around the handle "+
             "might be changed if the wielder should prefer to wield it as a "+
             "different weapon.\n");
    set_hit(NORMALHIT);
    set_pen(NORMALPEN);
    set_wt(W_POLEARM);
    set_dt(W_IMPALE);
    set_hands(W_BOTH);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(NORMALHIT,NORMALPEN) + random(80));
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_WEIGHT, 500);
    set_wf(this_object());
    set_likely_dull(1);
    set_likely_corr(1);
    set_likely_break(1);

    add_prop(OBJ_S_WIZINFO, "This is the kender weapon. "+
     "it has been enchanted by a mage, giving it an improved "+
     "hit and pen. It has the option of being wielded as "+
     "an axe, club or polearm.\n");

    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC,({ 10, "enchantment"}));
    add_prop(MAGIC_AM_ID_INFO,
      ({"The weapon is enchanted.\n", 5,
        "This weapons abilities seems to improve when in kenders hands.\n", 25,
        "It has the ability to change into a different weapon, if the "+
        "wielder would prefer that.\n", 50}));
}



int
change_grip(string str)
{
    if (L(str) == "grip to axe")
    {
        write("You flip your grip around the "+short()+ " and begin to use "+
              "it as an axe.\n");
        set_dt(W_SLASH);
        set_wt(W_AXE);
        wielder->update_weapon(TO);
        return 1;
    }
    if (L(str) == "grip to club")
    {
        write("You flip your grip around the "+short()+ " and begin to use "+
              "it as a club.\n");
        set_dt(W_BLUDGEON);
        set_wt(W_CLUB);
        wielder->update_weapon(TO);
        return 1;
    }
    if (L(str) == "grip to polearm")
    {
        write("You flip your grip around the "+short()+ " and begin to use "+
              "it as a polearm.\n");
        set_dt(W_IMPALE);
        set_wt(W_POLEARM);
        wielder->update_weapon(TO);
        return 1;
    }
    write("Change grip to what? Polearm, axe or club?\n");
    return 1;
}

mixed
wield(object what)
{
    if (this_player()->query_race_name() == "kender")
    {
        set_hit(KENDERHIT);
        set_pen(KENDERPEN);
        wielder->catch_msg("You confidently wrap your small hands around the "+short()+ ".\n");
        wielder->tell_watcher(QCTNAME(wielder)+ " wields " +HIS(wielder)+ " "+short()+ ".\n"); 
        wielder->update_weapon(TO);
        return 1;
    }
    set_hit(NORMALHIT);
    set_pen(NORMALPEN);
    wielder->catch_msg("You wrap your hands around the "+short()+ ".\n");
    wielder->tell_watcher(QCTNAME(wielder)+ " wields " +HIS(wielder)+ " "+short()+ ".\n"); 
    wielder->update_weapon(TO);
    return 1;
}

/*
 * Function name: remove_broken
 * Description  : The weapon got broken so the player has to stop
 *                wielding it.
 * Arguments    : int silent - true if no message is to be genereated
 *                             about the fact that the weapon broke.
 */
varargs void
remove_broken(int silent = 0)
{
    if (calling_function() == "item_expiration_break") 
        ::remove_broken(silent);

     return;
}


/*
 * Function name: set_dull
 * Description:   Use this to increases the dull status on weapons.
 * Arguments:     cond - The new condition we want (can only be raised)
 * Returns:       1 if new condition accepted
 */
int
set_dull(int du)
{
    return 0;
}


void
init()
{
    ::init();
    add_action("change_grip", "change");
}

