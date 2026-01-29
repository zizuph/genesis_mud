inherit "/d/Cirath/std/gith";
#include "/d/Cirath/common/defs.h"
#include "../defs.h"
#include <wa_types.h>
#include <std.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <money.h>
#include "/d/Cirath/common/teamfnc.h"

#define RNDADJ ({"massive", "muscular", "huge", "lanky", "evil-looking"})
#define RNDADJ2 ({"scaly","grinning","hunchbacked","smelly","powerful"})
#define RNDWEP ({"g_spear3","g_club3","g_axe3","g_sword3"})[random(4)]

mixed attackers;

create_monster()
{

   set_race_name("gith");
   set_adj(RNDADJ2[random(5)]);
   add_adj(RNDADJ[random(5)]);
   set_long("Gith are a strange Athasian race akin to goblins.  There "
   	+"aren't many physical similarities between two, though.  This "
	+"creature looks to be about seven feet tall when standing up "
	+"straight, but thankfully, its hunched disfigured frame only "
	+"allows it to stand five feet tall.  Scaly brownish green skin "
	+"covers its emaciated body, but beneath the surface, rippling "
	+"muscles are obvious.  Small, coal, black eyes stare at you "
	+"from beneath its thick brow.  This is truly a fearsome creature.\n");
   set_aggressive(1);
   set_alignment(-300);
   set_stats(({150,175,165,90,90,140}));
   set_skill(SS_WEP_POLEARM,85);
   set_skill(SS_WEP_SWORD,85);
   set_skill(SS_WEP_AXE,85);
   set_skill(SS_WEP_CLUB,85);
   set_skill(SS_PARRY,65);
   set_skill(SS_AWARENESS,70);
   set_skill(SS_DEFENCE,83);
   set_act_time(6);
   add_act("say That last caravan had lots of goodies.");
   add_act("say Try something, I dare ya.");
   add_act("grin evilly");
   add_act("cackle maniacally");
   set_cact_time(6);
   add_cact("say Die fool!");
   add_cact("growl softly");
   add_cact("roar");
   add_prop(LIVE_I_NEVERKNOWN,1);
   add_prop(LIVE_I_SEE_DARK,5);
}

void
arm_me()
{
   clone_object(GITH_WEP + RNDWEP)->move(TO);
   command("wield all");
   clone_object(GITH_ARM+ "g_body3")->move(TO);
   clone_object(GITH_ARM + "g_helm3")->move(TO);
   clone_object(GITH_ARM + "g_shield")->move(TO);
   command("wear all");
}


int
special_attack(object enemy)
{
    object me;
    mixed* hitresult;
    string how;
    me=this_object();

    if(random(10)) return 0;

    hitresult = enemy->hit_me(250 + random(50), W_IMPALE, me, -1);
    how = "untouched";
    if (hitresult[0] > 0) how = "barely touched";
    if (hitresult[0] > 15) how = "a little bruised";
    if (hitresult[0] > 30) how = "hurt";
    if (hitresult[0] > 50) how = "incredibly hurt";
    if (hitresult[0] > 75) how = "massively injured";

    enemy->catch_msg(QCTNAME(me) + " leaps upon you, striking you "+
          "with "+  HIS_HER(me) +" "+ query_weapon(-1)[0]->short()
                   +".\n");
    enemy->catch_msg("You feel " + how + ".\n");

    tell_watcher(QCTNAME(me)+" leaps upon "+QCTNAME(enemy)+ 
                 ", striking "+ HIM_HER(enemy)+" with " + HIS_HER(me) 
               +" "+query_weapon(-1)[0]->short()+".\n",me, enemy);
                 if(enemy->query_hp() <= 0) enemy->do_die(me);

    return 1;
}


