/**********************************************************************
 * - drew.c                                                         - *
 * - /d/Khalakhor/sw_speir/samorgan/room/gshop.c                    - *
 * - Created by Damaris@Genesis 08/2005                             - *
 **********************************************************************/
#pragma strict_types
#include "/d/Khalakhor/sys/defs.h"

#include <language.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <const.h>   // for G_FEMALE
#include <macros.h>  // for OB_NAME
#include <files.h>
#include <std.h>
#include "npc.h"
#define TUNIC "/d/Khalakhor/sw_speir/samorgan/arm/tunic"
#define KILT "/d/Khalakhor/common/kilts/kilt_morgan"

inherit STDHUMAN;
inherit "/d/Khalakhor/lib/knowledge_base";
inherit "/d/Khalakhor/lib/clan_support";
inherit "/d/Khalakhor/se_speir/port/npc/help_me";

static mapping remembered = ([]), failed = ([]);
#define TIQRN        this_interactive()->query_real_name()
object shop;
object last_attacker;
int return_alarm_id,
  attacker_alarm_id,
  has_armed;
void
create_khalakhor_human()
{
  set_name("drew");
  set_title("Flannagan, shop keeper");
  add_name(({"shopkeeper","keeper", "woman"}));
  set_race_name("human");
  set_gender(G_MALE);
  add_adj(({"grey-haired", "elderly"}));
  set_long("He is an elderly shopkeeper who has seen many "+
           "years pass.\n"+
           "He has stark grey eyes.\n"+
           "He has smooth light skin.\n"+
           "His hair is shoulder length, light red with streaks of grey "+
           "along the sides.\n");
  set_all_hitloc_unarmed(50);
  set_stats(({70,70,70,70,70}));
  add_prop(CONT_I_WEIGHT,48000);
  add_prop(CONT_I_HEIGHT,190);
  add_prop(NPC_I_NO_RUN_AWAY,1);
        
  set_alignment(100);
  set_mm_in("arrives brushing a stray lock of hair from his face.");
  MONEY_MAKE_SC(random(40))->move(this_object());
  set_act_time(15);
  seteuid(getuid());
        
  clone_object(TUNIC)->move(TO);
  clone_object(KILT)->move(TO);
  command("wield all");
  command("wear all");

  add_act("ponder");
  add_act("smile profession");
  add_act("whistle");
  add_act("emote hums a tune.");
  add_act("say Take a look around.");
  add_act("say Not much too look at I know, but I do my best.");
  add_act("emote sighs: I wish I knew when they will open the "+
          "fishing pier again.");
  add_ask(({"undead", "wraith", "undeads", "wraiths"}),
          "say Thou had better just watch thy step they might hear "+
          "thy words and seek thee out.", 1);
  add_ask(({"elves", "elf"}),
          "say Elves? Either buy something or be on thy way.", 1);
  add_ask(({"human", "humans"}),
          "say Humans? Either buy something or be on thy way.", 1);
  add_ask(({"goblin", "goblins", "hobgoblin", "hobgoblins"}),
          "say Goblins! Hide everything! Quickly! Pray they not be "+
          "coming back!", 1);
  add_ask(({"samorgan", "fishing village", "village"}),
          "say SaMorgan is a nice fishing village.", 1);
  add_ask(({"help"}),
          "say I could always use a bit of help, but not today.",1);
  add_ask(({"task"}),
          "say I have no tasks for you to do.", 1);
  add_ask(({"quest"}),
          "say Ahh now there is something I did when I was a young "+
          "lad. I have not much time nor the young bones to be out "+
          "questing.", 1);
  add_ask(({"dwarf", "dwarves"}),
          "say I've seen a dwarf or too in my time, but what has that "+
          "got to do with my shop?", 1);
  add_ask(({"hobbit", "hobbits"}),
          "say Hobbits! Yes yes. A wonderful lot they are, I've enjoyed "+
          "watching them try to fit all dem stranged breakfasts in me "+
          "baskets.", 1);
  add_ask(({"minotaur", "minotaurs"}),
          "say Thou mean the cow... err uhh... Just never mind all that. "+
          "Buy something or be on thy way.", 1);
  add_ask(({"gnome", "gnomes"}),
          "emote groans and says: I have seen enough to last me a "+
          "lifetime. They make things go boom or haven't you heard? ", 1);
  add_ask(({"half-elf", "half-elves"}),
          "say Of course I know a few half-elven folk. They do exist "+
          "around here after all.", 1);
  add_ask(({"half-human", "half-humans"}),
          "say Yes, yes. There are those that are considered half-human. "+
          "But what has that to do with my shop?",1);
  add_ask(({"kender"}),
          "say I haven't met too many kender in my lifetime.",1);
  add_ask(({"orc", "orcs", "ogre", "ogres"}),
          "say What is that?",1);
}
/*********************************************************************
 * - Function name: hook_return_intro                              - *
 * - Description  : Called when someone introduces themselves.     - *
 * - Arguments    : str - Name of the player introducing.          - *
 * - Returns      : 1                                              - *
 *********************************************************************/
public int
hook_return_intro(string str)
{
  if (SECURITY->query_wiz_rank(TIQRN) >= WIZ_ARCH)
    {
      command("asay devoted Blessed be my soul!");
      present(str, environment(TO))->add_introduced("drew");
      command("kneel " + str);
      command("asay devoted Greetings to thee, " +
              capitalize(str) +
              ". I am " + query_name() + " " + query_title() + 
              ", thy humble servant.");
      command("asay devoted Ask anything of me and I shall do "+
              "my best to please thee.");
      remembered[str] = "nice";
    }
  else if (SECURITY->query_wiz_rank(TIQRN, "Khalakhor"))
    {
      command("asay devoted Greetings to thee, " + 
              capitalize(str) +
              ". I am " + query_name() + " " + query_title() + 
              ". I am most pleased that thee has graced me with "+
              "thy pressence. How may I serve thee?");
      present(str, environment(TO))->add_introduced("drew");
      command("kneel " + str);
      remembered[str] = "nice";
    }
  else if (!remembered[str])
    {
      command("say Greetings to thee, " + capitalize(str) +
              ", I am " + query_name() + " " + query_title() +
              ". A pleasure to make thy acquaintance.");
      present(str, environment(TO))->add_introduced("drew");
      command("bow " + str);
      remembered[str] = "nice";
    }
  else if (remembered[str] == "bad")
    {
      command("growl sof");
      command("say I remember thou very well. So be on "+
              "thy way!");
    }
  else
    {
      command("emote beams with pleasure.");
      command("say I remember thee very well from thy "+
              "last visit, " + capitalize(str) + ". How could I "+
              "ever forget thee.");
      command("bow " +str);
      command("say I hope thou art faring well, and "+
              "enjoying our fine village?");
    }
  return 1;
}
public void
add_introduced(string who)
{
  kb_add_introduced(who);
}

public void
init_living()
{
  ::init_living();
  kb_init_living();
}

public void
enter_env(object to, object from)
{
  ::enter_env(to, from);
  kb_enter_env(to, from);
}
