/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/weapon";

#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>

#define TO   this_object()
#define TP   this_player()

#define ALIGN_LIM  700

public void
create_weapon()
{
   set_name("shortsword");
   set_adj("white");
   add_name("mystic_sword");
   add_name("sword");
   add_name("blade");
   set_long(
     "A slender and elegant blade, fashioned of some silvery-white metal "
    +"that gleams brilliantly. The blade is traced and inscribed with "
    +"arcane symbols. The hilt is set with ivory, on which are carved "
    +"faces of saintly looking peoples. The pommel is set with a large "
    +"sapphire.\n"
   );
   set_wt(W_SWORD);
   set_dt(W_IMPALE);
   set_hit(42);
   set_pen(36);
   add_prop("mystic_weapon", 1);
   add_prop(MAGIC_AM_MAGIC, ({ 30, "conjuration"}));
   add_prop(OBJ_I_IS_MAGIC_WEAPON, 30);

   set_wf(TO);
}

/*
 * Function name: wield
 * Description:   Try to wield a weapon.
 * Arguments:     obj - the weapon to try to wield.
 * Returns:       0 - wield this weapon normally.
 *                1 - wield the weapon, but print no messages.
 *                -1 - do not wield the weapon, use default messages.
 *                string - do not wield the weapon, use this fail message.
 */
public mixed
wield()
{
  if (TP->query_alignment() > ALIGN_LIM && TP->query_prop("blessed")) {
      write("As you take hold of the " + short() + ", the feeling of dread" +
            " and awe overtake you.\n");
      say(QCTNAME(TP) + " is surrounded by a pale white light as " +
          TP->query_pronoun() + " wields the " + short() + ".\n");
      return 1;
  }
  return "You cannot seem to grip the " + short() + ".\n";
}

/*
 * Function name: did_hit
 * Description:   Tells us that we hit something. Should produce combat
 *                messages to all relevant parties. If the weapon
 *                chooses not to handle combat messages then a default
 *                message is generated.
 * Arguments:     aid:   The attack id
 *                hdesc: The hitlocation description.
 *                phurt: The %hurt made on the enemy
 *                enemy: The enemy who got hit
 *                dt:    The current damagetype
 *                phit:  The %success that we made with our weapon
 *                dam:   The actual damage caused by this weapon in hit points
 * Returns:       True if it handled combat messages, returning a 0 will let
 *                the normal routines take over
 */
public varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt,
        int phit, int dam)
{
    if (phurt > 1 && enemy->query_prop(LIVE_I_UNDEAD)) {
        query_wielded()->catch_msg("The holy blade glows white.\n");
        enemy->catch_msg("The white light of the " + short() + " burns you!\n");
        enemy->hit_me(30, MAGIC_DT, TP, -1);
        tell_room(environment(enemy), "The " + short() + " " +
                  QTNAME(query_wielded()) + " is holding glows briefly" +
                  " with a whitish light as it is aimed at " + QTNAME(enemy) +
                  ".\n", ({query_wielded(), enemy}));
    }
    return 0;
}

public string
query_recover()
{
    return 0;
}
