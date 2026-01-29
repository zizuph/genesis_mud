/*
 * Base file for soldiers in the camp
 * Tapakah, 09/2021
 */

#pragma no_clone
#pragma strict_types

#include "macros.h"
#include "ss_types.h"
#include "wa_types.h"
#include "stdproperties.h"

#include "../defs.h"

inherit KSTDHUMAN;
inherit "/d/Khalakhor/std/npc/help-me";

int *base_stats = ({70, 70, 70, 55, 35, 95});
int _level = 0;
int _drag;
string _clan = "Macunknown";
string *names = ({
  "courier", "soldier", "standard-bearer",
  "sergeant", "lieutenant", "captain"
});
string *equipment = ({});
string *adjs1 = ({ });
string *adjs2 = ({ });
string name   = "";

void
equip_me ()
{
  object item;
  foreach (string file: equipment) {
    if(file_size(file + ".c") > 0) {
      item = clone_object(file);
      item->move(TO, 1);
    }
  }
  command("wield all");
  command("wear all");
}

int
is_camp_warrior ()
{
  return 1;
}

int
query_level ()
{
  return _level;
}

int
query_drag ()
{
  return _drag;
}

string
query_clan ()
{
  return _clan;
}

void
set_clan (string clan)
{
  if (_clan && _clan != "Macunknown")
    return;
  _clan = clan;
}

string
query_colors ()
{
  if (_clan == "Maccrimmon")
    return "green and blue";
  else if (_clan == "Macdunn")
    return "black and blue";

  return "undescribable hue";
}

string
my_long ()
{
  return "Override me\n";
}

void
create_camp_warrior (int level)
{
  ::create_khalakhor_human();

  add_name("warrior");
  set_race_name("human");
  set_pname(query_name() + "s");
  _level = level;

  int bonus, unit, s;
  for (s=0; s<6; s++) {
    unit = base_stats[s] / 5;
    bonus = unit * level * 130 / 100 + random(unit);
    set_base_stat(s, base_stats[s] + bonus);
  }
  
  set_skill(SS_DEFENSE,      30 + 10*level + random(10));
  set_skill(SS_PARRY,        25 +  8*level + random(10));
  set_skill(SS_ACROBAT,      20 +  6*level + random(10));
  set_skill(SS_BLIND_COMBAT, 15 +  4*level + random(10));
  switch (level) {
  case LEVEL_COURIER:
    set_skill(SS_AWARENESS, 50);
    set_skill(SS_WEP_KNIFE, 60 + random(10));
    break;
  case LEVEL_SERGEANT:
    set_skill(SS_WEP_POLEARM, 70);
    break;
  case LEVEL_SOLDIER:
    set_skill(SS_WEP_POLEARM, 50 + random(10));
    set_skill(SS_WEP_SWORD,   50 + random(10));
    break;
  default:
    set_skill(SS_WEP_SWORD, 40 + 10*level);
  }
  set_alignment(200 + 50*level);

  add_act("emote probes the blade of his weapon with his thumb.");
  add_act("say The gobbos are going to get it.");
  add_act("say Cala Fasdagh is so beautiful, so powerful and wild.");
  add_act("emote looks longingly in the eastern direction.");
  
  add_ask(({"task", "quest", "tour", "job", "work", "help"}),
          level == LEVEL_CAPTAIN ?
          "say we're still setting the camp. Come again when we are done." :
          "say you should ask the captain about it", 1);
  add_ask(({"goblin", "gobbo", "gobbos", "goblins"}),
          "emote curses colorfully.", 1);
  set_act_time(40);
  set_name(name);
  string adj1 = one_of_list(adjs1);
  string adj2 = one_of_list(adjs2);
  add_adj(({adj1, adj2}));
  set_short(implode(({adj1, adj2, name}), " "));
  set_long(my_long);
  
  set_alarm(0.5, 0.0, equip_me);
}

int
special_attack (object enemy)
{
  if (random(12 - _level))
    return 0;

  if (query_combat_object()->cb_tohit(W_NONE, 40+3*_level, enemy) <= 0) {
    tell_object(enemy, query_The_name(enemy) +
                " attempts to viciously knee you, but misses and stumbles on " +
                "his feet, struggling to regain the balance.\n");
    tell_watcher(QCTNAME(this_object()) + " misses " +
                 QTNAME(enemy) + " with a vicious kneeing attempt " +
                 "and stumbles on his feet, struggling to regain the balance.\n",
                 enemy);
    command("curse wholeheartedly");
    return 0; 
  }
  _drag = 6 + random(5 * _level);
  string how = "";
  if (_drag <= 10)
    how = "slightly ";
  else if (_drag <= 20)
    how = "somewhat ";
  else if (_drag >  30)
    how = "significantly ";
      
  tell_object(enemy, query_The_name(enemy) + " steps sideways and "+
              "knees you viciously.\n");
  tell_object(enemy, "You stumble in pain and begin to move " + how +
              "slower.\n");
  tell_watcher(QCTNAME(this_object()) + " steps sideways and knees "+
               QTNAME(enemy) + " viciously.\n", enemy);
  tell_watcher(QTNAME(enemy) + " stumbles in pain.\n", enemy);

  object drag = clone_object(WARRIOR_DRAG);
  drag->configure(_drag, _level);
  drag->move(enemy, 1);
}

void
attacked_by (object enemy)
{
  object *audience = filter(all_inventory(ETO), &->is_camp_warrior());
  foreach (object member: audience) {
    if (member == TO)
      continue;
    member->command("shout For Macdunn and Maccrimmon!");
    member->command("emote rushes to support his fellow warrior!");
    member->command("$kill " + enemy->query_name());
  }
}

void
enter_env (object to, object from)
{
  object *audience = filter(all_inventory(to), &->is_camp_warrior());
  ::enter_env(to, from);
  object  enemy;
  foreach (object member: audience)
    if (enemy = member->query_attack()) {
      command("emote notices his fellow warrior is under attack!\n");
      command("shout For Macdunn and Maccrimmon!");
      command("$kill " + enemy->query_name());
      break;
    }
}
