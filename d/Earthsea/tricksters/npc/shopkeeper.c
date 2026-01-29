inherit "/std/monster.c";

#include "../defs.h"

void create_monster()
{
 object shadow;

 set_name("rumple");
 set_long(BS(
   "This alchemist has been hired by the Tricksters to create and "+
   "distribute various alchemical devices to aid members in having "+
   "fun at other peoples expense.\n"));
 set_adj("short");
 add_adj("intelligent");
 set_race_name("human");
 set_title("the Recalcitrant Trickster");
 set_stats(({60,60,60,60,60,60}));

 shadow = clone_object(TRICKSTERS_SHADOW);
 if (shadow->add_trick_shadow(TO)!=1)
   shadow->remove_shadow();
}

void greet(string name)
{
 command("introduce myself");
 command("say Hullo there "+C(name)+"!");
}

void add_introduced(string name)
{
 ::add_introduced(name);
 set_alarm(1.0,0.0,&greet(name));
}

