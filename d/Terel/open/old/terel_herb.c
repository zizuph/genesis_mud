/*
  
  by Udana, /06
*/

inherit "/std/herb.c";

#include <stdproperties.h>
#include <macros.h>

int fight_state = 0;

void consume_text(object *arr, string vb)
{
  if(objectp(this_player()->query_attack()))
  {
    write("You can't focus on herbalism in such moment. You could eat something poisonous by an accident.\n");
    fight_state = 1;
    return;
  }
  if(!this_player()->query_relaxed_from_combat())
  {
    write("Your hands are still shaking from the recent combat, you need to calm down before using any herbs.\n");
    fight_state = 1;
    return;
  }
  ::consume_text(arr, vb);
}


void destruct_object()
{
  if(!fight_state)
    ::destruct_object();
  fight_state = 0;
}
  