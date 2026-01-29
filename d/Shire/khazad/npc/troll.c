inherit "/d/Shire/orcmaker/orcmaker";
inherit "/std/act/domove";
#include "/d/Shire/common/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>
#include "/d/Shire/common/lib/evilkill.h"
#include "/d/Shire/common/make_money.h"

void create_monster()
{
  ::create_monster();
  remove_adj(query_adj());
  remove_adj(query_adj());
  set_adj(({"scaly", "green-skinned" }));
  set_name("trollman");
  add_name("troll");
  set_race_name("cave troll");
  set_long("Beady white eyes dart around searching for the next meal. "+
           "The dirty greenish skin of this abomination resembles "+
           "thick leather, long worn and creased with lines. While not "+
           "as tall as other trolls you've encountered this one is very "+
           "stocky and bulging with muscles. A reaking stench clings to "+
           "the troll spoiling the air whereever it goes.\n");
  set_alignment(-700-random(150));
  set_monster_home("/d/Shire/khazad/deeps/deeps79");
  set_restrain_path("/d/Shire/khazad/deeps");
  set_random_move(10);
  set_attack_chance(0);
  set_base_stat(SS_STR,230+random(60));
  set_base_stat(SS_CON,240+random(60));
  set_base_stat(SS_DEX,160+random(40));
  set_base_stat(SS_DIS,160+random(30));
  set_base_stat(SS_INT,70+random(30));
  set_base_stat(SS_WIS,70+random(30));
  set_skill(SS_DEFENCE,80+random(20));
  set_skill(SS_AWARENESS,60+random(25));
  set_skill(SS_BLIND_COMBAT,80+random(15));
  set_skill(SS_UNARM_COMBAT,100+random(5));
  set_skill(SS_WEP_CLUB,60+random(10));
  add_prop(LIVE_I_SEE_DARK, 5); 
  add_prop(LIVE_O_ENEMY_CLING, TP->query_enemy());
  make_gold(random(36));
  make_platinum(random(5));
}
