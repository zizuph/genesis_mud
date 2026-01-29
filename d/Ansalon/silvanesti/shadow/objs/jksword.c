#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/silvanesti/shadow/local.h"
#include <macros.h>
#include <stdproperties.h>
#pragma save_binary
#include "/sys/wa_types.h"
#include "/sys/formulas.h"

inherit "/std/weapon";

nomask
create_weapon()
{
  set_name("blooddrinker");
  set_short("jewelled keen blooddrinker");
  set_long("@@long_desc");
  set_default_weapon(40,40,W_SWORD,W_SLASH|W_IMPALE,W_ANYH);
  add_name("sword");
  add_name("longsword");
  add_pname("swords");
  add_pname("longswords");
  set_adj("jewelled keen");
  add_adj("jewelled");
  add_adj("keen");

  add_prop(OBJ_I_VOLUME,2000+random(10)*150);
  add_prop(OBJ_I_WEIGHT,2000+random(10)*150);
  add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(45,45)*2);

  add_prop(OBJ_I_IS_MAGIC_WEAPON,1);
  add_prop(MAGIC_AM_ID_INFO,({
    "The longsword glows with magic.\n",10,
    "The jewels in the hilt seem to be the source of the power.\n",20,
    "The weapon drains health from victims, giving it to the wielder.\n",50}));
  add_prop(MAGIC_AM_MAGIC,({70,"necromancy"}));
  add_prop(OBJ_S_WIZINFO,"Occasionally transfers hp from enemy " +
    "to the wielder.\n");
}

public varargs int
did_hit(int aid,string hdesc, int phurt, object enemy, int dt, int phit, int dam)
{
  object attacker = query_wielded();
  if (phurt < 0)
    return ::did_hit(aid,hdesc,phurt,enemy,dt,phit,dam);

  if (random(5) == 0)
  {
    attacker->catch_msg("Your longsword glows brightly as it thirsts for " +
      "blood.\n");
    tell_room(E(attacker),QCTPNAME(attacker) + " longsword glows brightly " +
      "as it thirsts for blood.\n",attacker);
    if (dt == 1)
       attacker->set_hp(attacker->query_hp() + dam/2);
    else
      attacker->set_hp(attacker->query_hp() + dam/4);
  }
  return ::did_hit(aid,hdesc,phurt,enemy,dt,phit,dam);
}

string
long_desc()
{
  return "An exquisite longsword.\n";
}
