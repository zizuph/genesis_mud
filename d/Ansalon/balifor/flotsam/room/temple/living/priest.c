#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>
#include "/d/Ansalon/balifor/flotsam/local.h"
#include "/d/Ansalon/common/defs.h"

inherit AM_FILE
int wraith_summon = 0;
object wraith;
object wraith2;
object wraith3;

#define ARM TEMP + "obj/"
#define ARM1 ARM + "robe"
#define ARM2 ARM + "sk_helmet"
#define ARM3 ARM + "bone_plate"
#define WEP ARM + "scythe"

void
create_krynn_monster()
{
   if(!IS_CLONE)
      return;
   
   set_name("priest");
   set_adj("evil");
   add_adj("high");
   set_race_name("human");
   set_gender("G_MALE");
   set_short("evil high priest");
   set_long("Before you stands the High Priest of Chemosh, " +
      "and necromancer of this temple. He is surrounded by an " +
      "unholy aura, an aura of power and great evil. \n");
   
   set_stats(({85,85,80,40,80,65}));
   set_hp(10000);
   
   set_alignment(-750);
   set_knight_prestige(500);
   set_skill(SS_WEP_POLEARM, 75);
   set_skill(SS_DEFENCE,60);
   set_skill(SS_PARRY,50);
   set_skill(SS_AWARENESS,60);
   
   set_act_time(5);
   add_act("emote mumbles a prayer to the Lord of Death.");
   add_act("emote says in a hollow voice: What are you doing here?");
   add_act("emote steps up to the altar.");
   add_act("emote looks around for a suitable sacrifice to his " +
      "dark god.");
   
   set_cact_time(5);
   add_cact("emote calls upon the powers of Chemosh. \n" +
      "You are blasted by an unholy energy! \n" +
      "You feel yourself mentally drained.");
   add_cact("say Defilers! Leave this temple!");
   add_cact("say Chemosh! Hear my prayers!");
   
}

void
arm_me()
{
   seteuid(getuid(TO));
   clone_object(WEP)->move(TO,1);
   command("wield all");
   clone_object(ARM1)->move(TO,1);
   clone_object(ARM2)->move(TO,1);
   clone_object(ARM3)->move(TO,1);
   command("wear all");
}


public void
attacked_by(object ob)
{
   ::attacked_by(ob);
   if (wraith_summon)
      {
      return;
   }
   
   seteuid(getuid());
   command("emote screams: Fools! Now feel the wrath of " +
      "the Lord of Death!");
   command("emote raises his hands above his head, and a swirling " +
      "black rift opens up before him.");
   command("shout Chemosh! Answer my prayers! Strike down the " +
      "infidel who invades your unholy temple!");
   wraith = clone_object(TEMP + "living/wraith");
   wraith->move_living("arrives through the dark rift", E(TO));
   wraith->attack_object(ob);
   wraith2 = clone_object(TEMP + "living/wraith");
   wraith2->move_living("arrives through the dark rift", E(TO));
   wraith2->attack_object(ob);
   wraith3 = clone_object(TEMP + "living/wraith");
   wraith3->move_living("arrives through the dark rift", E(TO));
   wraith3->attack_object(ob);
   wraith_summon = 1;
}


void
tell_watcher(string str, object enemy)
{
    object me, *ob;
    int    i;

    me = TO;
    ob = FILTER_LIVE(all_inventory(E(me))) - ({ me });
    ob -= ({ enemy });
    for (i = 0; i < sizeof(ob); i++)
    {
        if (ob[i]->query_see_blood())
        {
            ob[i]->catch_msg(str);
        }
    }
}


int
special_attack(object enemy)
{
    int    drain;

    if (random(5))
        return 0;

    command("emote calls upon the powers of Chemosh.");
    enemy->catch_msg("You are blasted by an unholy energy.\n");
    enemy->catch_msg("You feel yourself drained of life.\n");
    tell_watcher(QCTNAME(enemy) + " is blasted by an unholy energy.\n",
        enemy);
    tell_watcher(QCTNAME(enemy) + " suddenly looks tired.\n", enemy);
    drain = 50 + random(26);
    enemy->heal_hp(-drain);
    if (enemy->query_hp() <= 0)
    {
        tell_room(E(TO), QCTNAME(enemy) + " slumps lifeless to the "
          + "ground.\n", ({ TO }));
        enemy->do_die(TO);
        command("shout Chemosh! Answer my prayers! I summon this "
          + "wretched soul to do your bidding!");
        tell_room(E(TO), "A dark shadow slowly rises from the corpse "
          + "and shapes into a wraith.\n", ({ TO }));
        seteuid(getuid());
        clone_object(TEMP + "living/wraith")->move_living("M", E(TO));
        command("grin");
    }
    TO->heal_hp(drain);
    return 1;
}
