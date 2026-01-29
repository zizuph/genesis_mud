#include "/sys/macros.h"
#include "/sys/stdproperties.h"

/* Functions to code:
 * tell_players_in_domain(string domain, string text)
 * tell_players_in_domain_out(string domain, string text)
 * tell_players_in_next_room(object this_room, string text)
 * tell_wizards_in_domain(string wizard, string domain)
 * query_in_domain(object player, string domain)
 */

query_in_domain(string domain, object player)
{
  string s1,s2;
  object room;
  if (!player) return 0;
  if (environment(player))
  room = environment(player);
  else return 0;
  domain = capitalize(lower_case(domain));
  if (sscanf(file_name(room),"/d/%s/%s",s1,s2) != 2) return 0;
  if (s1 == domain) return 1;
  return 0;
}

query_domain(object player)
{
  string s1,s2;
  object room;
  if (!player) return 0;
  if (environment(player))
  room = environment(player);
  else return 0;
  if (sscanf(file_name(room),"/d/%s/%s",s1,s2) != 2) return 0;
  return s1;
}

tell_players_in_domain(string domain, string text)
{
  object *player;
  int n,s;
  player = users();
  while (n<sizeof(player))
    {
      if (query_in_domain(domain,player[n])) player[n]->catch_msg(text);
      n++;
    }
  return 1;
}

tell_players_in_domain_out(string domain, string text)
{
  object *player;
  int n,s;
  player = users();
  while (n<sizeof(player))
    {
      if (query_in_domain(domain,player[n]) && 
	  !environment(player[n])->query_prop(ROOM_I_INSIDE))
	player[n]->catch_msg(text);
      n++;
    }
  return 1;
}

tell_next_room(object this_room, string text)
{
  object room;
  mixed *exit_arr;
  string dir;
  int n,i;
  exit_arr = this_room->query_exit();
  while (n<sizeof(exit_arr)/3)
    {
      tell_room(exit_arr[n*3],text);
      n++;
    }
  return 1;
}

tell_next_room_with_dir(object this_room, string text)
{
  object room;
  mixed *exit_arr, *room_arr;
  string *dir;
  int n,i,s;
  if (!this_room) return 1;
  exit_arr = this_room->query_exit();
  room_arr = ({ });
  dir = ({ });
  room_arr = this_room->query_exit_rooms();
  while (i<sizeof(room_arr))
    {
      if (member_array(MASTER_OB(this_room),room_arr[i]->query_exit()))
	{
	  s = member_array(MASTER_OB(this_room),room_arr[i]->query_exit());
    dir += ({" the "+room_arr[i]->query_exit()[s+1] });
	}
      else dir += ({" somewhere nearby"});
      i++;
    }
  n = 0;
  while (n<sizeof(room_arr))
    {
      tell_room(room_arr[n],text+dir[n]+".\n");
      n++;
    }
  return 1;
}




