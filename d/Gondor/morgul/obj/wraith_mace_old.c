/* An elf-slaying and human-slaying mace
 * Last Modification: Olorin, July 1994
 * Mod log: 14-Sep-94, Olorin: moved the destruction on dropping the mace
 *                             from the VBFC of OBJ_M_NO_DROP to leave_env, as
 *                             a query_prop(OBJ_M_NO_DROP) doesn't not
 *                             necessarily mean that someone is actually
 *                             dropping it!
 * 
 * Modification log:
 * Olorin 04-Sep-1996     Made keepable 
 * Rohim  2002-11-09      Modified did_hit to handle parries as dodges.
 * 
 */
#pragma strict_types

inherit "/std/weapon";
inherit "/lib/keep";

#include <filter_funs.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"

#define HIS(x)		x->query_possessive()

void
create_weapon()
{
  set_name("mace");
  add_name("weapon");
  set_adj(({"black", "heavy"}));
  set_short("black heavy mace");
  set_pshort("black heavy maces");
  set_long(BSN("This is a large black mace, ice-cold to the touch, "+
    "made from some strange metal unknown to you. Veins of inlaid "+
    "gems line the spiked head."));
  add_item(({"gems","veins"}),
    "There are red gemstones inlaid in the spiked head of the mace.");
  add_item("head",BSN(
    "The head of the mace holds nasty spikes, and veins of red gems "+
    "inlaid in between the spikes."));

  set_default_weapon(40,40,W_CLUB,W_BLUDGEON,W_BOTH,0);
  add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(40, 40)+random(1000)-500);
  add_prop(OBJ_I_WEIGHT,
	(F_WEIGHT_DEFAULT_WEAPON(50, W_CLUB) + random(2000) + 500));
  add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 5);
  add_prop(GONDOR_M_MORGUL_NO_SELL, 1);
  add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
  add_prop(MAGIC_AM_MAGIC,({ 40, "enchantment" }));
  add_prop(OBJ_S_WIZINFO, BSN(
    "This mace is a nasty magical weapon wielded by evil wraiths in "+
    "Minas Morgul, the city of evil in Gondor. The wraith is in file "+
    "/d/Gondor/morgul/npc/ithil_wraith.c and is a nasty opponent to "+
    "meet. Especially for humans and elves, since this mace is elf- and "+
    "human-slaying! And there is only a small chance that the mace is "+
    "actually possible to get, if you can kill the wraith, for it will "+
    "most often dissolve when the wraith loses its grip on it. "+
    "The mace is WC 40, but does between 1.5x and 2x damage on elves "+
    "and on humans."));
  add_prop(MAGIC_AM_ID_INFO,
    ({ "The black mace seems to be magical.\n",1,
       "It is a mace of Elf- and Man-slaying!\n",50 }));
}

varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit, int dam)
{
  if (enemy->query_race_name()!="elf" && enemy->query_race_name()!="human")
    return 0;
  if (phurt == -1 || phurt == -2)
  {
    query_wielded()->catch_msg(
      "You swing the black mace with all your might - through open air.\n");
    enemy->catch_msg("You deftly duck as "+QTNAME(query_wielded())+" swings "+
      query_wielded()->query_possessive()+" black mace at you.\n");
    wielder->tell_watcher(QCTNAME(wielder)+" swings the black mace with all "+
      HIS(wielder) + " might - through open air.\n", enemy);
  }
  else if (phurt == 0)
  {
    query_wielded()->catch_msg("Your black mace just barely misses "+
      QTNAME(enemy)+"!\n");
    enemy->catch_msg("The black mace of "+QTNAME(query_wielded())+
      " just barely misses your head!\n");
    wielder->tell_watcher(QCTNAME(wielder)+" just barely misses "+QTNAME(enemy)+
      " with "+HIS(wielder)+" black heavy mace.\n", enemy);
  }
  else
  {
    wielder->tell_watcher(QTNAME(wielder)+"'s heavy black mace falls on "+
      QTNAME(enemy)+" with a bone breaking sound!\n", enemy);
    query_wielded()->catch_msg("The black mace falls down on the puny "+
      enemy->query_race_name()+" with a mighty crush!\n");
    enemy->catch_msg("The black mace falls upon you with a mighty crush!\n");
    enemy->heal_hp(-(random(dam/2)+dam/2));
  }
  return 1;
}

public void
leave_env(object from, object to)
{
    ::leave_env(from, to);

    if (!objectp(from) || !objectp(to) || !living(from))
        return;

    if (!to->query_prop(ROOM_I_IS))
        return;

    if (random(4))
        return;

    tell_room(to, "The black mace turns to dust as it hits the ground!\n");
    set_alarm(0.0, 0.0, "remove_object");
}
