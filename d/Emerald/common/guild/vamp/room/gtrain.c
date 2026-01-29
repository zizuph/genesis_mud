#pragma save_binary

#include "../guild.h"

inherit VAMP_ROOM_DIR + "vamp_room";
inherit "/d/Emerald/lib/train";

#include "/d/Emerald/sys/skills.h"

#include <ss_types.h>

void set_up_skills()
{
    create_skill_raise();
  
    sk_add_train(SS_AWARENESS, "perceive", "awareness", 0, 100);
    sk_add_train(SS_DEFENSE, "dodge attacks", "defense", 0, 100);

#ifdef SS_VAMP_CELERITY
    sk_add_train(SS_VAMP_CELERITY, "move at an accelerated rate",
        "celerity", 80, 100);
#endif
}

int sk_no_train(object who)
{
    if (!IS_MEMBER(who) && !EMRLD_WIZ(who))
    {
      command("say Only true vampires may train here!");
      return 1;
    }
  
  /*
    if (CHECK_PUNISHMENT(BAR, TP->query_real_name()))
    {
      command("say Sorry " + TP->query_name() + ", but you are " +
	  "considered unworthy to train here.");
      return 1;
    }
  */
  
    return 0;
}

int arch_msg()
{
    write("You pass through the archway back into the training area.\n");
    return 0;
}

void create_vamp_room()
{
    set_short("Recreation area");

    set_long("   Judging from the luxurious appointments in this room, " +
        "it was probably reserved as a recreation room for the temple's " +
        "leaders.  You could use the facilities here to improve your " +
        "own skills as well.\n");

    set_up_skills();

    add_exit("train", "south", arch_msg);
}

void
init()
{
    ::init();
    init_skill_raise();
}
