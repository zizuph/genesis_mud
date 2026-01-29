inherit "/d/Rhovanion/lib/caves";
inherit "/lib/guild_support";
inherit "/lib/skill_raise";

#include "/d/Rhovanion/defs.h"
#include "def.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include <money.h>

void set_up_skills();

object meditate;

create_cave()
{
  set_rock_type("soluble limestone");
  set_cave_name("Thranduil's Caverns");
  set_region("northern");
  set_cave("Mirkwood");
  set_cave_type(2);
  set_long("This is the adventurers guild in Thranduil's care. Here you " +
	   "might want to meditate to find out what your preferenced stats " +
	   "are at the moment, you might also want to learn and/or improve " +
           "to find out what skills are taught here and to what level. The " +
           "only obvious exit is back to the south. \n");
  
  create_guild_support();
  create_skill_raise();
  set_up_skills();
  
  set_noshow_obvious(1);
  add_exit(THIS_DIR + "cave31","south",0,1);
}

void
  set_up_skills()
{
  string me, ot;
  
  me = "use a sword"; ot = me;
  sk_add_train(SS_WEP_SWORD,    ({ me, ot }),       0, 0, 27 );
  me = "know where abouts"; ot = me;
  sk_add_train(SS_LOC_SENSE,    ({ me, ot }),       0, 0, 50 );
  me = "find tracks"; ot = me;
  sk_add_train(SS_TRACKING,     ({ me, ot }),       0, 0, 50 );
  me = "hunt for game"; ot = me;
  sk_add_train(SS_HUNTING,      ({ me, ot }),       0, 0, 30 );
  me = "know what happens around him"; ot = me;
  sk_add_train(SS_AWARENESS,    ({ me, ot }),       0, 0, 50);
}

void
  gs_hook_start_meditate()
{
  write("Slowly you sit down on the soft carpet and close your eyes.\n" +
	"A feeling of great ease and self control falls upon you.\n" +
	"You block of your senses and concentrate solely upon your\n" +
	"own mind. You find yourself able to <estimate> your different\n" +
	"preferences and <set> them at your own desire.\n" +
	"Just <rise> when you are done meditating.\n");
}

void test_tour(object player)
{
  object note;
  if (present("Thranduil_Tour_Note",player)) {
    note = present("Thranduil_Tour_Note",player);
    if (note -> query_tour_no() != 0) return;
    note -> set_tour_done();
    call_out("tour_done",5,player);
    return;
  }
  return;
}

tour_done(player) 
{
  tell_object(player,"This is the place that the Advisor told you to find.\n"+
	      "You can now return to him.\n");
  return 1;
}

void init()
{
  test_tour(TP); 
  init_skill_raise();
  init_guild_support();
  ::init();
}
