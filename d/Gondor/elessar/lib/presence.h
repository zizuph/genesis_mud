#include "/d/Gondor/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"


races_near(object pl, string *races)
{
  object room;
  string *exit_arr;
  int n, race_found;
  if (pl->query_prop(ROOM_I_IS))
    room = pl;
  else if (ENV(TO) != pl)
    return 0;
  else
    room = ENV(pl);
  exit_arr = room->query_exit();
  while (n < sizeof(exit_arr)/3) {
      race_found = check_living_present((exit_arr[n*3]), races);
    n++;
    }
  return race_found;
}

races_present(object pl, string *races)
{
  object room;
  int race_found;
  if (pl->query_prop(ROOM_I_IS))
    room = pl;
  else if (ENV(TO) != pl)
    return 0;
  else room = ENV(pl);
  race_found = check_living_present((room), races);
  return race_found;
}

check_living_present(mixed roomstr, string *races)
{
  object *inv_arr,room;
  int n,i;
  if (!roomstr) return 0;
  seteuid(getuid(TO));
  if (stringp(roomstr))
  {
    catch(roomstr->short());
    if (!find_object(roomstr)) return 0;
    room = find_object(roomstr);
  }
  else
    room = roomstr;
  /*  Initialize the room, to make sure we get an inventory. */
  room->short();
  inv_arr = all_inventory(room);
  while (n < sizeof(inv_arr)) {
    if (living(inv_arr[n])) {
      if (test_for_race(inv_arr[n],races))  i+= 1;
      }
    n++;
    }
  return i;
}

test_for_race(object monster, string *races)
{
  if (member_array(monster->query_race_name(), races) >= 0)
    return 1;
  return 0;
}
