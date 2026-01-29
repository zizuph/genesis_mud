/* Minotaur Base, by Aridor 10/94
 * original by Splunge, 1/12/94 
 */

#include "/d/Krynn/common/defs.h"
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>
#include <macros.h>

inherit M_FILE

void
create_minotaur()
{
    add_adj("evil");
    set_long("@@my_long");
    set_act_time(10);
    add_act("emote snorts violently.");
    add_act("emote laughs at you with true amusement.");
    add_act("emote folds his arms across his massive chest.");
    set_alarm(2.0,0.0,"arm_me");
}

void
create_krynn_monster()
{
    set_name("minotaur");
    set_race_name("minotaur");
    set_adj("huge");
    set_stats(({100,85,110,90,50,100}));
    set_skill(SS_PARRY, 50);
    set_skill(SS_DEFENCE, 30);
    set_skill(SS_WEP_SWORD, 65);
    set_skill(SS_WEP_AXE, 90);
    set_skill(SS_AWARENESS, 33);
    set_all_hitloc_unarmed(40);/*thick skin!!*/
    set_alignment(-300 - random(300));
    NEVERKNOWN;
    seteuid(getuid(TO));
    create_minotaur();
    refresh_mobile();
    set_knight_prestige(query_average_stat() * query_average_stat() / 10);
}

string
my_long()
{
    return ("This is an enormous, and very evil minotaur. His face is that " +
	    "of a bull, but he walks upright and is able to use his hands. " +
	    "He seems to be a true servant of Takhisis, and he appears to " +
	    "be guarding something.\n");
}

public void
attacked_by(object ob)
{  
    ::attacked_by(ob);
    command("say My dear " + ob->query_nonmet_name() + ". You should know " +
	    "better than to attack a minotaur.");
    command("emote shakes his head in disappointment.");
}

void
arm_me()
{
    object wep;
    wep = clone_object("/d/Krynn/solace/lake/obj/flamberge1.c");
    wep->move(this_object());
    command("wield weapon");
}

int
special_attack(object enemy)
{
    int attacktype, i, penet;
    mixed* hitresult;
    string how;
    object me=TO;
  
    attacktype = random(4);
    if (attacktype == 1)
      {
	  penet = query_stat(SS_STR);
	  penet += random(3*penet);
	  hitresult = enemy->hit_me(penet, W_IMPALE, me, -1);
	  how = "crashes by, almost embedding his horns into a nearby " +
	    "tree.";
	  if (hitresult[0] > 0)                  
	    how = "scratches with his horns as he charges on";
	  if (hitresult[0] > 10)
	    how = "cuts with his horns, leaving a bloody wound";
	  if (hitresult[0] > 20)
	    how = "hits solidly with the flat of his head, causing a " +
	      "resounding CRACK";
	  if (hitresult[0] > 40)
	    how = "gores deeply, trying to disembowel his opponent";
	  if (hitresult[0] > 70)
	    how = "impales with his horns and thrashes around madly, " +
	      "causing extreme damage";
	  
	  enemy->catch_msg("The minotaur charges directly at YOU and " + how +
			   "!\n");
	  tell_watcher("The minotaur rushes at "+QTNAME(enemy) + " and "
		       + how + "!\n",enemy);    
	  
	  if (enemy->query_hp() <= 0)
	    write("The minotaur shakes his head madly as he throws the " +
		  "lifeless body of " + QTNAME(enemy) + " across the room!\n");
	  return 1;
      }
    return 0;
}
