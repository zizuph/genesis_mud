#include "/sys/macros.h"
#include "/sys/stdproperties.h"

tell_players_in_domain(string text)
{
  object pl_arr;
  int n,s;
  pl_arr = users();
