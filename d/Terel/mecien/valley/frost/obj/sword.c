/*
 * Modified 2021-03-02 by Carnak:
 * - Not sure if this item is in the game, but added a block so that
 *   players are unable to wield it due to it surpassing the limits
 *   allowed.
 */

inherit "/std/weapon";
#include <stdproperties.h>
#include <formulas.h>

#define TP this_player()
#define TO this_object()

query_value(){ return 400; }

create_weapon(){
   set_name("sword");
   set_adj("two-handed");
   set_long(
      "About fifteen feet long, this enormous blade is fashioned from\n"
      + "crude iron, its hilt bound with leather.\n"
   );
   set_hit(75);
   set_pen(65);
   set_hands(W_BOTH);
   set_wt(W_SWORD);
   set_dt(W_SLASH);
   set_wf(TO);
   add_prop(OBJ_I_WEIGHT, 125000);
   add_prop(OBJ_I_VOLUME, 75000);
}

/*
 * Function name: wield
 * Description  : This function might be called when someone tries to wield
 *                this weapon. To have this function called, use the function
 *                set_wf().
 *                Note: - this routine does not actually exist in /std/weapon.
 *                        A trick is used to fool the document maker.
 *                      - this_player() will be set to the wielder during this
 *                        call.
 * Arguments    : object obj - the weapon someone tried to wield.
 * Returns      : int  0 - wield this weapon normally.
 *                     1 - wield the weapon, but print no messages.
 *                    -1 - do not wield the weapon, use default messages.
 *                string - do not wield the weapon, use this fail message.
 */
public mixed
wield(object weapon)
{
    // Prevent users from wielding this weapon.
    if (interactive(this_player()) || this_player()->query_race_name() != "giant")
    {
        return "This weapon is far too cumbersome to wield properly.\n";
    }
} /* wield */