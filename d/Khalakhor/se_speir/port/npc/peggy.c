/**********************************************************************
 * - peggy.c                                                        - *
 * - Dress shop owner in SaMorgan.                                  - *
 * - /d/Khalakhor/se_speir/port/room/dshop.c                        - *
 * - Created by Damaris@Genesis 01/2006                             - *
 * - Refactored by Tapakah, 07/2021                                 - *
 **********************************************************************/
#pragma strict_types

#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <const.h>   // for G_FEMALE
#include <macros.h>  // for OB_NAME
#include "npc.h"

inherit BASE_NPC;

void
arm_me ()
{
  armours = ({ "/d/Khalakhor/se_speir/port/arm/dress1" });
  weapons = ({ "/d/Khalakhor/sw_speir/samorgan/wep/dshears" });
  ::arm_me();
}

void
create_khalakhor_human ()
{
  ::create_khalakhor_human();
	add_name(({"shopkeeper","keeper", "woman"}));
	set_gender(G_FEMALE);
	add_adj(({"elderly", "well-dressed"}));
	set_long("She is an elderly seamstress who considers herself "+
           "more a weaver of cloths and shopkeeper.\n"+
           "She has wise blue eyes.\n"+
           "She has aged wrinkled skin.\n"+
           "Her hair is grey with traces of light red still lingering "+
           "at the tips, which is pulled up in a bun atop her head.\n");
  set_all_hitloc_unarmed(50);
  set_stats(({70,70,70,70,70}));
  add_prop(CONT_I_WEIGHT,48000);
  add_prop(CONT_I_HEIGHT,190);
  add_prop(NPC_I_NO_RUN_AWAY,1);
        
  set_alignment(100);
  set_mm_in("arrives brushing a stray lock of hair from her face.");
  MONEY_MAKE_SC(random(40))->move(this_object());
  set_act_time(15);

  add_act("ponder");
  add_act("smile profession");
  add_act("whistle");
  add_act("emote hums a tune.");
  add_act("say Oh I do hope you will be pleased with my "+
          "dresses and gowns.");
  add_act("say All my clothing is intricately sewn "+
          "with care.");
  add_act("emote sighs: Oh I wish I had bought some perfume today.");
  add_ask(({"undead"}),
          "say You had better just watch thy step they might hear "+
          "and seek you out.", 1);
  add_ask(({"elves", "elf"}),
          "say Ahh yes, elves. I've known a few but they do rather "+
          "keep to themselves afterall. I have sold a few dresses "+
          "to some traveling though.", 1);
  add_ask(({"human", "humans"}),
          "say I know quite a few. Port Macdunn's population is "+
          "of humans.", 1);
  add_ask(({"goblin", "goblins", "hobgoblin", "hobgoblins"}),
          "say Goblins! Hide everything! Quickly! Pray they not be "+
          "coming back!", 1);
  add_ask(({"samorgan", "fishing village", "village"}),
          "say SaMorgan I've been told is a nice fishing village, "+
          "but I've not been there myself. I have an apprentice "+
          "seamstress who moved there though. Not seen her in years.", 1);
  add_ask(({"apprentice", "apprentices"}),
          "I've had quite a few apprentices in my day.",1);        
  add_ask(({"help"}),
          "say I could always use a bit of help, but not today.",1);
  add_ask(({"task"}),
          "say I have no tasks for you to do.", 1);
  add_ask(({"quest"}),
          "say Ahh now there is something I wish I could do, and "+
          "that is a quest. If only I could go off and discover "+
          "something.", 1);
  add_ask(({"dwarf", "dwarves"}),
          "say I've had to fit dwarves before. Not an easy fit at "+
          "times. Their shoulders are quite differently proportioned.", 1);
  add_ask(({"hobbit", "hobbits"}),
          "say Hobbits! Yes yes. A wonderful lot they are, I've enjoyed "+
          "fitting them in so many dashing clothes.", 1);
  add_ask(({"minotaur", "minotaurs"}),
          "say You mean the cow... err uhh... No I haven't fitted one "+
          "myself.", 1);
  add_ask(({"clothes", "clothing"}),
          "say I have many clothes for you to choose try to 'list' "+
          "them.", 1);
  add_ask(({"cloth", "cloths", "fabric", "fabrics"}),
          "say I use only the finest fabrics in my clothing.", 1);
  add_ask(({"cloak room", "cloakroom", "shop"}),
          "say I pride myself in having a colourful shop.", 1);
  add_ask(({"gnome", "gnomes"}),
          "emote giggless sweetly as she says: I have fitted a few in "+
          "my lifetime and am grateful to survive such a feat.", 1);
  add_ask(({"half-elf", "half-elves"}),
          "say Of course I know a few half-elven folk. They do exist "+
          "around here after all.", 1);
  add_ask(({"half-human", "half-humans"}),
          "say Yes, yes. There are those that are considered half-human. "+
          "But what has that to do with my dresses and gowns?",1);
  add_ask(({"kender"}),
          "say I haven't met too many kender in my lifetime.",1);
  add_ask(({"orc", "orcs"}),
          "say What is that?",1);
}

void
hook_return_intro_new (string str)
{
  command("say Greetings to thee, " + capitalize(str) +
          ", I am " + query_name() + " " + query_title() +
          ". A pleasure to make thy acquaintance.");
  command("curtsey " + str);
}

void
hook_return_intro_bad (string str)
{
  command("growl sof");
  command("say I remember thou very well. So be on thy way!");
}

void
hook_return_intro_good (string str)
{
  command("emote beams with pleasure.");
	
  command("say Don't you remember me? I am " +
          query_name() + " " + query_title() + ". ");
  command("say I remember thee very well from thy "+
          "last visit, " + capitalize(str) + ". ");
  present(str, environment())->add_introduced("peggy");
  command("curtsey " +str);
  command("say I hope thou art faring well, and "+
          "enjoying our fine town?");
}
