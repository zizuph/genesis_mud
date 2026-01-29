/*
  No herbs can be eaten during the combat or shortly after.
  by Udana, /06
*/

inherit "/std/herb.c";

#include <stdproperties.h>
#include <macros.h>

/* Flag - 1 if players in combat */
int fight_state = 0;

public void set_fight_flag(int i)
{
	fight_state = (i > 0 ? 1 : 0);
}

public int query_fight_flag()
{
	return fight_state;
}


/* In original /std/herb.c this method displays line like 'You eat/apply/verb herb_name'
 * it has to be overloaded too, since it's displayed before player gets any effects.
 * if the herb can't be eaten due new policy the flag is set
 */
void consume_text(object *arr, string vb)
{
  if(objectp(this_player()->query_attack()))
  {
    write("You can't focus on herbalism in such moment. You could eat something poisonous by an accident.\n");
    arr->set_fight_flag(1);
    return;
  }
  if(!this_player()->query_relaxed_from_combat())
  {
    write("Your hands are still shaking from the recent combat, you need to calm down before using any herbs.\n");
    arr->set_fight_flag(1);
    return;
  }
  ::consume_text(arr, vb);
}

/* If the flag is set during consume_text rutine the herb is not eaten */
void destruct_object()
{
  if(!query_fight_flag())
    ::destruct_object();
  set_fight_flag(0);
}
  