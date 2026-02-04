/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/weapon";

#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>

#define TO   this_object()
#define TP   this_player()

#define ALIGN_LIM  -25

public void
create_weapon()
{
   set_name("broadsword");
   set_adj("mystical");
   add_name("mystic_sword");
   add_name("sword");
   add_name("blade");
   set_long(
      "This spectacular blade shimmers and glows, its length coated "
      +"with many mystical runes and letters, sharp and deadly. It is "
      +"fashioned of some strange metal, silvery and sparkling "
      +"and surrounded by an aura of green.\n"
   );
   set_wt(W_SWORD);
   set_dt(W_SLASH);
   set_hit(35);
   set_pen(29);
   add_cmd_item(({"runes", "mystical runes", "letters"}),
      "read", "Glory by Wisdom\n");
   add_item(({"runes", "mystical runes", "letters"}),
      "They are engraved upon the length of the sword.\n");
   add_prop("mystic_weapon", 1);
   add_prop(OBJ_I_IS_MAGIC_WEAPON, 25);
   add_prop(OBJ_I_VALUE, 1104);
   add_prop(MAGIC_AM_MAGIC, ({ 20, "conjuration" }));

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
   if (TP->query_prop("blessed")) {
      write("The " + short() + " radiates a greenish glow as you wield it.\n");
      say("The " + short() + " radiates a green glow in the hands of " +
          QTNAME(TP) + " as " + TP->query_pronoun() + " wields it.\n");
      return 1;
   }
   return "The " + short() + " resists you.\n";
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
    if (phurt > 1 && enemy->query_alignment() < ALIGN_LIM) {
        query_wielded()->catch_msg("Your " + short() +
                                   " radiates a burning green glow.\n");
        enemy->catch_msg("The green glow from the " + short() + " " +
                         QTNAME(query_wielded()) + " holds, burns you!\n");
        tell_room(environment(enemy), "A green glow emanates from the " +
                  short() + " as " + QTNAME(query_wielded()) + 
                  " aims it at " + QTNAME(enemy) + ".\n",
                  ({query_wielded(), enemy}));
        enemy->heal_hp(-1);
    }
    return 0;
}

public string
query_recover()
{
    return 0;
}

