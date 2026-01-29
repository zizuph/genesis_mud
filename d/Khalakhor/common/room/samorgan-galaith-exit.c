/*
 * Avoiding even minimal code replication
 * Tapakah, 09/2021
 */

#pragma strict_types
#pragma no_clone

#define TP this_player()
inherit "/d/Khalakhor/common/npc/quest-npc";

int
check_exit ()
{
  if (quest_done("Eil-Galaith Entrance") 
      || TP->query_prop("__answered_galaith_riddles"))
    return 0;

  write("There is no obvious exit "+ query_verb() +".\n");
  return 1;
}

varargs int
show_exit (object player=TP)
{
  return quest_done("Eil-Galaith Entrance") 
    || player->query_prop("__answered_galaith_riddles") ? 0 : 1;
}

