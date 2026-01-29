/* An orc-slayer sword */
inherit "/std/weapon";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/d/Gondor/defs.h"
#include "/d/Gondor/elessar/lib/presence.h"
#define SLAY_RACES ({"orc","uruk-hai","goblin","half-orc","uruk","hobgoblin","hob-goblin"})

int glow_status;

create_weapon() {
  set_name("sword");
  add_name("weapon");
  add_name("broadsword");
  set_adj("bright");
  set_long("@@long_func");
  set_default_weapon(50,50,W_SWORD,W_SLASH,W_RIGHT,0);
  add_prop(OBJ_I_IS_MAGIC_WEAPON,1);
  add_prop(OBJ_S_WIZINFO,"This is going to be an orc-slayer sword.\n"+
    "It is not yet finished, but I hope it will be some day.\n"+
    "If a mortal is found carrying this - remove it! It\n"+
    "is not available to mortals yet.\n");
  add_prop(MAGIC_AM_MAGIC,({ 50, "enchantment" }));
  add_prop(MAGIC_AM_ID_INFO,({ 
    "The broadsword is practically radiating magic!\n",1,
    "It is an Orc-slaying sword!\n",50 }));
  add_prop(OBJ_I_WEIGHT,14500);
  add_prop(OBJ_I_VOLUME,7400);
  add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(50,50)+random(200)-100);
}

did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit, int dam)
{
  string race;
  race = enemy->query_race_name();
    if (member_array(race,SLAY_RACES) < 0)
    return 0;
  if (phurt == -1) {
    query_wielded()->catch_msg("The blue-glowing sword swings through open air.\n");
    enemy->catch_msg("You deftly duck as "+QTNAME(query_wielded())+" swings "+
      query_wielded()->query_possessive()+" blue-glowing sword at you!\n");
    }
  else
  if (phurt == 0) {
    query_wielded()->catch_msg("Your blue-glowing sword just barely misses "+
      QTNAME(enemy)+"!\n");
    enemy->catch_msg("The blueglowing sword of "+QTNAME(query_wielded())+" just barely misses you!\n");
    }
  else {
    query_wielded()->catch_msg("You swing the blue-glowing broadsword at "+
      enemy->query_race_name()+" with great force!\n");
    enemy->catch_msg("You scream as the blue-glowing sword hits you painfully!\n");
    enemy->heal_hp(-dam); /* The sword does double damage on certain races! */
    say(QCTNAME(enemy)+" screams of pain as the blue-glowing sword hits!\n",({enemy,query_wielded()}));
    }
  return 1;
}

long_func()
{
  string txt;
  txt = "The sword looks magnificent, with runes engraved along the blade.\n";
  if (races_present(ENV(TO), SLAY_RACES)) txt = txt +"The broadsword is glowing brightly blue!\n";
  else if (races_near(ENV(TO), SLAY_RACES)) txt = txt+"The broadsword is glowing faintly blue.\n";
  else txt = txt+"It seems to be made of mithril.\n";
  return txt;
}

check_for_enemies()
{
  if (races_present(ENV(TO), SLAY_RACES)) {
    if (query_wielded()) {
      query_wielded()->catch_msg("Your bright broadsword glows brightly blue!\n");
      say(QCTNAME(query_wielded())+"'s broadsword glows brightly blue!\n",query_wielded());
      add_prop(OBJ_I_LIGHT,2);
      }
    else if (ENV(TO)->query_prop(ROOM_I_IS)) { say("The broadsword glows brightly blue!\n");
      add_prop(OBJ_I_LIGHT,2); }
    else add_prop(OBJ_I_LIGHT,0);
    }
  else if (races_near(ENV(TO), SLAY_RACES)) {
    if (query_wielded()) {
      query_wielded()->catch_msg("Your broadsword glows faintly blue.\n");
      say(QCTNAME(query_wielded())+"'s broadsword glows faintly blue.\n",query_wielded());
      add_prop(OBJ_I_LIGHT,1);
      }
    else if (ENV(TO)->query_prop(ROOM_I_IS)) { say("The broadsword glows fainly blue.\n");
      add_prop(OBJ_I_LIGHT,1); }
    else add_prop(OBJ_I_LIGHT,0);
    }
  else add_prop(OBJ_I_LIGHT,0);
  if (query_wielded()) ENV(query_wielded())->update_light();
  call_out("check_for_enemies",5);
}

check_light_level()
{
  if (races_present(ENV(TO), SLAY_RACES)) return 2;
  else if (races_near(ENV(TO), SLAY_RACES)) return 1;
  return 0;
}

void
enter_env(object dest, object old)
{
    ::enter_env(dest, old);
    set_alarm(5.0, 0.0, "check_for_enemies");
}

