inherit "/std/monster";
inherit "/d/Emerald/lib/train.c";

#include "../guild.h"
#include <macros.h>

void create_trainer() { }
void set_up_skills() { }

nomask void create_monster()
{
  set_up_skills();

  if (IS_CLONE)
  {
    create_trainer();
  }
}

public int query_init_master() { return 1; }

init_living()
{
  ::init_living();
  init_skill_raise();
}

int query_skill(int skill)
{
  return (skill < 25 ? 100 : ::query_skill(skill)); 
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


    
