/*
 * Modified 2021-03-02 by Carnak:
 * - Not sure if this item is in the game, but added a block so that
 *   players are unable to wield it due to it surpassing the limits
 *   allowed.
 */
inherit "/std/weapon";
#include <stdproperties.h>
#include <formulas.h>

query_value(){ return 120; }

create_weapon(){
    set_name("axe");
    set_adj("stone");
  set_long(
  "This is a titanic axe. The haft carved from the trunk of\n"
  +"a tree, the blade cut from a heavy gray stone.\n"
    );
    set_hit(65);
    set_pen(60);
    set_wt(W_AXE);
    set_dt(W_SLASH);
    add_prop(OBJ_I_WEIGHT, 50000);
    add_prop(OBJ_I_VOLUME, 20000);
    
    set_wf(this_object());
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
    if (interactive(this_player()))
    {
        return "This weapon is far too cumbersome to wield properly.\n";
    }
} /* wield */