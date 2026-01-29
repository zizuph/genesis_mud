inherit "/d/Rhovanion/milan/open/mapserver/mapserver";

#include <ss_types.h>

/*
 * VITAL !!!!!
 */
mixed
query_file_with_map()
{
  return "/d/Rhovanion/milan/open/mapserver/my_map";
}

int
this_is_room(string arg)
{
  if(arg == "m") return 0;
  return ::this_is_room(arg);
}

void
set_up_room(string str)
{
  switch (str)
  {
    case "x":
	set_short("x room");
	set_long("x room\n");
	break;
    case "p":
	set_short("p room");
	set_long("p room\n");
        add_exits();
  }
  return;
}

int
query_map_fatigue(string here)
{
  if(here == "x") return 10;
  return ::query_map_fatigue(here);
}

string *query_paths()
{
  return ({ "p" });
}

string
path_desc_start(string arg)
{
  return "You can see a path. It goes ";
}

string
path_desc_end(string arg)
{
  return " from here";
}

string *query_show()
{
  return ({ "p", "m" });
}

string
neighbour_desc_start(string from, string to)
{
  if(to == "m")
    if(from == "p")
      return "You clearly see great hill to the ";
    else
      return "You spot some hill to the ";
  if(to == "p")
    return "You spot path ";
  return ::neighbour_desc_start(from, to);
}

string
neighbour_desc_end(string from, string to)
{
  if(to == "p")
    return " from here";
  return ::neighbour_desc_end(from, to);
}

int
player_see_surrounding(object who, string from, string to)
{
  if((who->query_skill(SS_AWARENESS) < 20) && (from != "p"))
    return 0;
  return ::player_see_surrounding(who, from, to);
}

int
player_is_lost(object who, string where)
{
  if(who->query_skill(SS_LOC_SENSE) < random(51))
    return 1;
  return 0;
}

