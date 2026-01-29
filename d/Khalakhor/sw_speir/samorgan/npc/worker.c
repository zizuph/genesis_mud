/*
 * Construction worker
 * Damaris 03/2001
 */
#pragma strict_types

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>
#include <wa_types.h>
#include <formulas.h>
#include <cmdparse.h>
#include <composite.h>
#include "/d/Khalakhor/sys/random.h"
#include "../defs.h"

inherit STDHUMAN;

/*
 * Function name: hook_return_intro
 * Description  : Called when someone introduces to us by the
 *                add_introduced hook in the knowledge base.
 *                Defined here only to prevent the guard from
 *                introducing himself (as he's a neverknown
 *                npc with no name.)
 * Arguments    : str - lowercase name of whoever intro'd.
 * Returns      : 1.
 */
public int
hook_return_intro(string str)
{
  return 1;
}

public string
act_2()
{
  object *others;

  others = filter(all_inventory(environment()), &->id("worker"));
  others -= ({TO});

  if (!sizeof(others)) 
    command("emote looks around carefully, apparently " +
            "unformfortable about being alone.");
  else {
    command("say to " + OB_NAME(others[0]) + " I think I'm going to "+
            "head to SaKeller's for an ale when the shift is over, " +
            "feel like coming along?");
    others[0]->command("say If you're buying, sure.");
    others[0]->command("grin");
  }
  return "";
}

public string
act_3()
{
  object *masters,
    *others;

  masters = filter(all_inventory(environment()),
                   &->is_khalakhor_blademaster());
  others = filter(all_inventory(environment()), &->id("worker")) - ({TO});

  if (!sizeof(masters)) {
    command("say I wonder if some day I'll be good enough " +
            "with a sword to claim the title of Blademaster.");
    if (!sizeof(others))
      return "";
    else
      others->command("laugh");
    command("grumble");
    return "";
  }

  string whisper = sizeof(masters) == 1 ? "A Blademaster" : "Blademaster";
  masters->catch_msg(QCTNAME(TO) + " stares at you in awe and " +
                     "whispers: " + whisper + "!\n");
  tell_room(environment(), QCTNAME(TO) + " stares at " +
            COMPOSITE_LIVE(masters) + " in awe and whispers: " + whisper,
            masters);
  return "";
}

public void
arm_me()
{
  clone_object(WEP + "hammer")->move(TO);
  clone_object(ARM + "lgloves")->move(TO);
  clone_object(COM_ARM + "vest_leather")->move(TO);
  clone_object(COM_ARM + "belt")->move(TO);
  clone_object(COM_KILTS + "kilt_macdunn")->move(TO);
  clone_object(ARM + "wboots")->move(TO);
  command("wield all");
  command("wear all");
  command("lace vest");
}
/*
 * Function name: create_khalakhor_human
 * Description  : Turns this object into a worker.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
create_khalakhor_human()
{
  set_name("worker");
  add_name("_samorgan_worker");
  add_name("man");
  add_name("worker");
  set_gender(G_MALE);
  set_adj(RANDOM_DETAILED_ADJS(TO));
  set_long("This man appears to be one of the village " +
           "construction workers. He's not a terribly formidable sight, " +
           "but the workers of Khalakhor are skilled with their hammers. "+
           "He has been sent here from Port Macdunn.\n");

  default_config_npc(40 + random(40));
  set_skill(SS_AWARENESS, 50);
  set_skill(SS_UNARM_COMBAT, 50);
  set_skill(SS_DEFENCE, 50);
  set_skill(SS_PARRY, 50);
  set_skill(SS_WEP_CLUB, 70);

  set_alignment(200 + random(200));

  add_prop(LIVE_I_NEVERKNOWN, 1);
  set_stats(({80 + random(20),
              60 + random(5),
              60 + random(10),
              60 + random(5),
              60 + random(5),
              60 + random(10)}));
  set_random_size_descs();
  set_act_time(random(30));
  add_act("ponder");
  add_act(VBFC_ME("act_2"));
  add_act(VBFC_ME("act_3"));
  add_act("peer");
  add_ask(({"eil-galaith", "sanctuary"}),
          "say I heard Eil-Galaith is what the elves are calling sanctuary. "+
          "Something about a tower..",1);
  add_ask(({"tower"}),
          "say Well I'm not so sure. Maybe you mean that tower the elves are "+
          "calling Sanctuary Tower.",1);
  add_ask(({"sanctuary tower"}),
          "say Well I'm no elf, but I heard they call it Eil-Galaith.",1);
  add_ask(({"samorgan"}),
          "say It's a small village in the southwest speir "+
          "but lately there has been a lot "+
          "of visitors. I heard there used to be a boat from SaMorgan "+
          "that takes you to Galaith isle.",1);
  add_ask(({"galaith"}),
          "say Hmm Galaith isle is close to the southwest speir.",1);
  add_ask(({"macdunn", "port macdunn"}),
          "say That's home. That's where I am going after our job is done.", 1);
}

public void
come_assist_me(object victim, object attacker, string where)
{
  string *rooms, *cmds;
  int index;

  if (query_attack())
    return;

  if (!environment(TO))
    return;

  if (where != file_name(environment(TO))) {
    rooms = environment(TO)->query_exit_rooms();
    cmds = environment(TO)->query_exit_cmds();
    
    index = member_array(where, rooms);
    
    if (index < 0)
      return;
    
    command(cmds[index]);
  }
  command("kill " + OB_NAME(attacker));
}
        
