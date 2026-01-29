/*
 * Filename:        bknife.c
 * Description:     Draconian claymore was used as a template to
 *                  create this dagger it is an appendum to splendid
 *                  sword when the draconian clone that.
 *
 * The claymore was created by Aridor 11/30/93
 *
 * This file by Boron Feb. 2000
 */

inherit "/std/weapon";
inherit "/lib/keep";

#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include <tasks.h>

#include "../local.h"

string color = "blue";

/*prototype*/
void set_color(string new_color);

void
create_weapon()
{
    set_name("dagger");
    set_pname("daggers");
    add_pname("weapons");
    set_adj("lethal");
    add_adj("dragon-forged");
    set_short("lethal dragon-forged dagger");
    set_long("@@my_long");
    set_default_weapon(30 + random(8), 35 + random(10), W_KNIFE, W_IMPALE, W_LEFT);
    set_wf(this_object());
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(OBJ_S_WIZINFO,
         "The extremely well balanced weapon lets the wielder " +
         "feel the weapon as an extension of his arm. This magic " +
         "balance allows a very high penetration, even though the hits " +
         "itself are not magically enhanced.\n");
    add_prop(MAGIC_AM_ID_INFO,
         ({"This weapon is magically enchanted.\n", 5,
         "You feel a strong will emanating from " +
         "the dagger that you must overcome.\n", 25,
         "The weapon's balance is subject to the magic, " +
         "allowing better wieldability and a very high " +
         "penetration force.\n", 51}));
    add_prop(MAGIC_AM_MAGIC,({80,"enchantment"}));
    add_prop(OBJ_I_VOLUME, 360);
    add_prop(OBJ_I_WEIGHT, 480);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(49,40) + 1000); /* it is magical! */
}

string
query_recover()
{
    return MASTER + ":" + query_wep_recover() + "&&" + color;
}

void
init_recover(string arg)
{
    string *a = explode(arg,"&&");
    set_color(a[1]);
    init_wep_recover(a[0]);
}

string
my_long()
{

    add_item(({"gem", color + " gem", "gemstone", color + "gemstone"}),
    "With a somewhat appraising look you set to study the " + color + " gemstone, "
    + "when suddenly, with a force of a storm bending a road-side tree, "
    + "your consciousness is wrenched deeper in a dark abyss. Your vision "
    + "narrows, drowning in cascading utter darkness.\nYou feel "
    + "yourself falling into oblivion, falling into a glimmering silhuette of a woman, "
    + "dressed in bright " + color + " clothes and whose beauty "
    + "steals whats left of your breath. You plunge downwards, into "
    + "the sparkling lines, which explode in every direction.\n\n\n"
    + "Ear piercing wails cut through your heart as the souls of "
    + "silver and bronze dragons writhe in unborn torment.\n\n\n"
    + "You tear your eyes away from the " + color +" gem.\n");

    return "This nearly a foot long, left handed dagger looks lethal. "
           + "Its straight, solid blade has been forged with vicious "
           + "teeth set at regular intervals along a razor-sharp "
           + "edge that looks capable of cutting skin and bone in "
           + "the blink of an eye.\nA large " + color + " gem has been mounted "
           + "in a steel dragon claw at the end of the hilt, and "
           + "serves as the counterbalance.\nThe hilt itself has "
           + "been wrapped in the skin of baby dragons. "
           + "The weapon glows with a fierce, unholy light, but what "
           + "unnerves you the most is the fact that the tiny, not "
           + "yet hardened scales on the hilt glow with a silvery "
           + "and bronze sheen, and the abominable artifact seems to "
           + "emit wails of undescribable agony.\n";

}

void
set_color(string new_color)
{
   color = new_color;
}


mixed
wield(object what)
{
  /* Use a resolve_task to see if the player is able to wield the weapon.
   * WIS >= 49 is required to even have a chance. WIS >= 97 ensures success.
   */
  if (this_player()->resolve_task(1800,({ SKILL_WEIGHT, 900, TS_WIS })) > 0)
    {
      write("In deep concentration you throw the dagger up in the air, and it "
            + "easily slips down in the palm of your hand as you catch it.\n");
      return 0;
    }
  this_player()->add_mana(-random(50) - 10);
  return "You throw the dagger up in the air and as you catch it again a sharp pain "
         + "runs up through your arm and into your head as you try to master the dagger."
         + "\n";
}

mixed
unwield(object what)
{
  /* Use a resolve_task to see if the player is able to unwield the weapon.
   * DEX >= 49 is required to even have a chance. DEX >= 97 ensures success.
   */
  if (query_wielded()->resolve_task(1800,({ SKILL_WEIGHT, 900, TS_DEX })) > 0)
  {
      write("You easily let the dagger slip out of your hands.\n");
      return 0;
  }

  query_wielded()->add_mana(-random(50) - 10);
  return "As you disturb the balance of the dagger you feel the evil "
         + "magic flow through your body, ensnaring your brain!\n"
         + "You are unable to unwield the dagger.\n";
}
