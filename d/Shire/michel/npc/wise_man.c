/*
 * This man changes the dirty orc letter into the neat one to allow
 * players to solve the second half of the letter quest.
 * Cloned by ~Shire/michel/cabin
 */

inherit "/std/monster";

#include "macros.h"
#include <stdproperties.h>
#include "/d/Shire/common/defs.h"
#include "/sys/ss_types.h"
#include "/d/Shire/common/monster/tobacco.h"

#define QUEST_NAME "letter"
#define QUEST_GROUP 0
#define QUEST_BIT1   2
#define QUEST_BIT2   3
#define DOMAIN      "Shire"

//    Prototypes
void all_done(mixed *ob);
void return_letter(mixed *ob);
void return_other(mixed *ob);
void return_introduce(string who);

void
create_monster()
{

  if (!IS_CLONE) return;
  set_name("raston");
  add_name("man");
  set_living_name("_raston_");
  set_adj("old");
  set_race_name("human");
  set_long("This is a man of indeterminable age. He looks at you with grey"
	      + " misty eyes that have seen more years than you can count."
	      + " He looks as if he has read every book that has ever existed."
	      + " He is now sitting on his chair awaiting your next move.\n");

  set_short("old wise man");
  set_stats(({ 58, 24, 45, 50, 50, 97 }));

  add_act("smile");
  set_act_time(10);

  add_chat("What can I do for you?");
  add_chat("This is my humble home.");
  add_chat("I am writing a book about the history of a world called...\n"
	   + "Arda.");
  set_chat_time(5);

  clone_tobacco();

  trig_new("%s 'introduces' %s", "react_introduce");

  remove_prop(NPC_M_NO_ACCEPT_GIVE);

}

return_introduce(who) {
  if (random(4) && present(who, environment())) {
    command("introduce myself to " + who);
   }
  else {
    command("introduce myself");
   }
}

/*
 * Function name:react_introduce
 * Description  :Introduce myself when someone else does it.
 */
react_introduce(who, tmp) {
  set_alarm(itof(random(3) + 2),0.0,&return_introduce(who));
  return 1;
}

/*
* Function name:dont_return_letter
* Description  :keep letter
*/
dont_return_letter(mixed ob) {

  command("say My, what an odd letter. Not often one encounters writing from orcs.");
  command("say Thank you very much.");
  command("shake " + ob[1]->query_real_name());
  ob[0]->self_destruct();
}

/*
* Function name:return_letter
* Description  :return letter
*/
return_letter(mixed ob) {

  command("say Hmmm, this is in orcish. I can make a translation for you.");
  write("The old man gets a clean sheat of paper and starts writing.\n");
  command("nod");
  command("say Well this is it I suppose. I will keep the original.");
  command("smile");
  ob[0]->make_wise();
  command("give " + ob[0]->query_name() + " to " + ob[1]->query_real_name());

}  

/*
* Function name:all_done
* Description  :Well the quest is done no sense in translating.
*/
all_done(mixed ob) {

  ob[0]->self_destruct();
  command("say What a piece of rubbish.");
  command("say I will throw it away for you.");
  command("smile");

}

/*
* Function name:return_other
* Description  :We dont want this.
*/
return_other(mixed ob) {

  command("say What would I do with this?");
  command("give " + ob[0]->query_name() + " to " + ob[1]->query_real_name());
}
/*
* Function name:enter_inv
* Description  :I use this to test if I get something
*/
enter_inv(object ob, object from) {
  ::enter_inv(ob,from);
  
  if((ob->are_u_quest_letter() != 111)) {
    set_alarm(2.0,0.0,&return_other(({ ob , from })));
    return;
  }

  if(!from->test_bit(DOMAIN, QUEST_GROUP, QUEST_BIT1)) {
    set_alarm(2.0,0.0,&return_other(({ ob , from })));
    return;
  }

  if(!from->test_bit(DOMAIN, QUEST_GROUP, QUEST_BIT2)) {
    set_alarm(2.0,0.0,&return_letter(({ ob , from })));
    return;
  }

  set_alarm(2.0,0.0,&all_done(({ ob , from })));
  return;
}

