#pragma no_clone
#pragma no_inherit
#pragma strict_types

#include <std.h>
#include <macros.h>

/* by this we lower rank_stat of all members every boot */
#define LOWER_ALL    5
/* this is max allowed rising of rank_stat per boot */
#define MAX_JUMP    50
/* bonus for having rank - makes ranks more stable */
#define RANK_BONUS   100

#define THIS_DIR  "/d/Rhovanion/common/shield_guild/"
#define VOTE_ROOM   (THIS_DIR+"vote")
#define SAVE_FILE   THIS_DIR+"S_C_TITLES"

static string *Titles = ({ "Footman", "Standard Bearer", "Corporal",
                 "Sergeant", "Warrant Officer", "Lieutenant", "Captain" });
static int *Factors = ({ 1, 3, 6, 10, 16, 25, 1 });
static int *Stat_levels = ({ 0, 200, 400, 650, 900, 1200, 1400 });

/*
 * Army has fixed structure and so number of positions available
 * depends on number of members. This limits number of position from
 * the top. Note that one position for every level is always available
 * Here are top limits:
 *
 *  Footmen         - no restrictions
 *  Standard Bearer - (sum of members) / Factors[1]
 *  Corporal        - (sum of members) / Factors[2]
 *  Sergeant        - (sum of members) / Factors[3]
 *  Warrant Officer - (sum of members) / Factors[4]
 *  Lieutenant      - (sum of members) / Factors[5]
 *  Captain         - 1
 *
 *  note (sum of members) is only up to a given level
 *
 * This title system should be more exciting for players - in order to
 * get better title (if there is no place available) one have to be better
 * then other player on that level which will result in promotion of this
 * one and demotion of other one.
 */

/*
 * The index to the name_title mapping is the name and it will return
 * title of player.
 *
 *  mapping name_title = ([ "name" : "title", ... ]);
 *
 * The index to the title_name_stat mapping is title and it will return an
 * array of arrays containing name of the player with this title and his stat
 * that determines the title.
 *
 * mapping title_name_stat = ([
 *       "title1" : ({ ({"name1","stat1"}),({"name2","stat2"}),...}),
 *       "title2" : ({ ({"name3","stat3"}),({"name3","stat3"}),...}),
 *           ...             ]);
 */

/*
 * Global variables, they will be saved.
 */
private mapping name_title      = ([ ]);
private mapping title_name_stat = ([ ]);

/*
 * Prototypes
 */
static void check_titles();

/*
 * Function name: create
 * Description  : Function called when object is loaded
 */
void
create()
{
  int i;

  seteuid(getuid());
  if (!restore_object(SAVE_FILE))
  {
    name_title      = ([ ]);
    title_name_stat = ([ ]);
    for(i = 0; i < sizeof(Titles); i++)
      title_name_stat += ([ Titles[i] : ({ }) ]);
  }
  for(i=0; i<sizeof(Titles); i++)
    if(!title_name_stat[Titles[i]])
      title_name_stat[Titles[i]] = ({ });
  set_alarm(0.0, 0.0, check_titles);
}

static void
set_new_title(mixed names, string new_title, string old_title)
{
  int i, j, s;
  mixed old_title_name_stat = title_name_stat[old_title];

  for(i = 0; i < sizeof(names); i++)
    name_title[names[i]] = new_title;

  s = sizeof(old_title_name_stat);
  for(i = 0; i < s; i++)
    if(member_array(old_title_name_stat[i][0], names) != -1)
    {
      title_name_stat[new_title] += ({ old_title_name_stat[i] });
      title_name_stat[old_title] -= ({ old_title_name_stat[i] });
    }
}

/*
 * Function name: demote_council
 * Description  : We demote council members (no Lieut or Cap.) ant those
 *                who applied for council.
 */
static void
demote_council()
{
  string *names, *council = VOTE_ROOM->query_council() +
                            VOTE_ROOM->query_applied();
  int i, j, s, t;

  t = sizeof(Titles);
  for(i = t-1; i > t-3; i--)
  {
    names = ({ });
    s = sizeof(title_name_stat[Titles[i]]);
    for(j = 0; j < s; j++)
      if(member_array(capitalize(title_name_stat[Titles[i]][j][0]),
                      council) != -1)
        names += ({ title_name_stat[Titles[i]][j][0] });
    set_new_title(names, Titles[t-3], Titles[i]);
  }
}

/*
 * Function name: lower_all_stats
 * Description  : We lower all stats so not logging players are not on top
 */
static void
lower_all_stats()
{
  string *names;
  int i, j, s;

  for(i=0; i<sizeof(Titles); i++)
    for(j = 0; j < sizeof(title_name_stat[Titles[i]]); j++)
    {
      title_name_stat[Titles[i]][j][1] -= LOWER_ALL;
      if(title_name_stat[Titles[i]][j][1] < 0)
        title_name_stat[Titles[i]][j][1] = 0;
    }
}

/*
 * Function name: demote_for_low_stat
 * Description  : We demote everyone who lost somehow stats
 */
void
demote_for_low_stat()
{
  string *names;
  int i, j, s;

  for(i = sizeof(Titles)-1; i > 0; i--)
  {
    names = ({ });
    s = sizeof(title_name_stat[Titles[i]]);
    for(j = 0; j < s; j++)
      if(title_name_stat[Titles[i]][j][1] < Stat_levels[i])
        names += ({ title_name_stat[Titles[i]][j][0] });
    set_new_title(names, Titles[i-1], Titles[i]);
  }
}

/*
/*
 * Function name: promote_for_high_stat
 * Description  : Now we promote eneryone with stat high enough
 */
void
promote_for_high_stat()
{
  string *names;
  int i, j, s;

  for(i = 0; i < sizeof(Titles)-1; i++)
  {
    names = ({ });
    s = sizeof(title_name_stat[Titles[i]]);
    for(j = 0; j < s; j++)
      if(title_name_stat[Titles[i]][j][1] > Stat_levels[i+1])
        names += ({ title_name_stat[Titles[i]][j][0] });
    set_new_title(names, Titles[i+1], Titles[i]);
  }
}

/*
 * Function name: how_many_to_remove
 * Arguments    : title - title (string)
 * Returns      : how much more names is on this level then it should be or
 *                -1 - this should never happen!
 */
static int
how_many_to_remove(string title)
{
  int i, num_of_all, num, num2;

  if(title == Titles[sizeof(Titles)-1])
  {
    if(sizeof(title_name_stat[title]))
     return (sizeof(title_name_stat[title]) - 1);
    return 0;
  }
  num_of_all = 0;
  for(i = 0; i < sizeof(Titles); i++)
  {
    num = sizeof(title_name_stat[Titles[i]]);
    num_of_all += num;
    if(title == Titles[i])
    {
      if(num < 2) return 0;
      num2 = num - (num_of_all / Factors[i]);
      if(num2 == num) num2--;
      num = num2;
      if(num < 1) return 0;
      return num;
    }
  }
  return -1;
}

int
my_sort_function(mixed a, mixed b)
{
  return a[1]-b[1];
}

/*
 * Function name: demote_no_place
 * Description  : we may have promoted too many...
 */
static void
demote_no_place()
{
  int i, j, r;
  string *names;
  for(i = sizeof(Titles)-1; i > 0; i--)
  {
    title_name_stat[Titles[i]] = sort_array(title_name_stat[Titles[i]],
                                            "my_sort_function");
    names = ({ });
    r = how_many_to_remove(Titles[i]);
    if(r>0)
    {
      for(j = 0; j < r; j++)
        names += ({ title_name_stat[Titles[i]][j][0] });
      set_new_title(names, Titles[i-1], Titles[i]);
    }
  }
}

/*
 * Function name: remove_entry
 * Description  : Removes name from record (player left guild...)
 * Argument     : name (string)   name to be removed
 *                titles.
 */
void
remove_entry(string name)
{
  int i;
  string title = name_title[name];
  mixed tmp = title_name_stat[title];
  mixed tmp2 = ({ });

  /***  check if this name has a record  ***/
  if(member_array(name, m_indices(name_title)) == -1) return;

  name_title = m_delete(name_title, name);

  for(i = 0; i < sizeof(tmp); i++)
    if(tmp[i][0] != name)
      tmp2 += ({ tmp[i] });

  title_name_stat[title] = tmp2;

  save_object(SAVE_FILE);
}

static void start_five()
{ demote_no_place(); save_object(SAVE_FILE); }
static void start_four()
{ demote_council(); set_alarm(0.0, 0.0, start_five); }
static void start_three()
{ promote_for_high_stat(); set_alarm(0.0, 0.0, start_four); }
static void start_two()
{ demote_for_low_stat(); set_alarm(0.0, 0.0, start_three); }
static void start_one()
{ lower_all_stats(); set_alarm(0.0, 0.0, start_two); }

/*
 * Function name: check_titles
 * Description  : Every time this object is loaded into memory, this function
 *                is called. It removes nonexistant players and updates
 *                titles.
 */
static void
check_titles()
{
  string *names, title;
  int i, s;

  /*** first remove nonexistant players ***/
  names = m_indices(name_title);
  for(i = 0; i < sizeof(names); i++)
  {
    if(!SECURITY->exist_player(names[i]) ||
       SECURITY->query_wiz_level(names[i]) ||
       (explode(names[i]+"#", "jr#")[0]+"jr" == names[i]))
      remove_entry(names[i]);
  }

  /*** now remove players with zero AA stat (idle too long) ***/
  names = ({ });
  title = Titles[0];
  s = sizeof(title_name_stat[title]);
  for(i = 0; i < s; i++)
    if(title_name_stat[title][i][1] == 0)
      names += ({ title_name_stat[title][i][0] });
  for(i = 0; i < sizeof(names); i++)
    remove_entry(names[i]);

  /*** finally sort them all out ***/
  set_alarm(0.0, 0.0, start_one);
}

/*
 * Function name: update_entry
 * Description  : This function should be called every time when player
 *                logs in. It updates player stat and returns his present
 *                title.
 */
string
update_entry(object who)
{
  string title, name = who->query_real_name();
  int s_c_stat = who->query_s_c_stat();
  int i, s;

  if(!name || !s_c_stat) return "";

  for(i = 0; i < sizeof(Titles); i++)
    if(!title_name_stat[Titles[i]])
      title_name_stat[Titles[i]] = ({ });

  if ((THIS_DIR+"s_c_updated")->query_updated(name)) return name_title[name];

  if(member_array(name, m_indices(name_title)) == -1)
  {
    name_title += ([ name : Titles[0] ]);
    title_name_stat[Titles[0]] += ({ ({ name, MIN(MAX_JUMP, s_c_stat) }) });
  }
  else
  {
    title = name_title[name];
    s = sizeof(title_name_stat[title]);
    for(i = 0; i < s; i++)
      if(name == title_name_stat[title][i][0])
      {
        title_name_stat[title][i][1] =
                   (RANK_BONUS * member_array(title, Titles)) +
                   MIN(s_c_stat, title_name_stat[title][i][1] + MAX_JUMP);
        i = s;
      }
  }
  /* save the new values */
  save_object(SAVE_FILE);

  (THIS_DIR+"s_c_updated")->set_updated(name);
  return name_title[name];
}

/*
 * Function name: query_players_with_title
 * Description  : Returnd list of names with this title
 */
string *
query_players_with_title(string title)
{
  string *names = ({ });
  int i;

  if(member_array(title, Titles) == -1) return ({ });
  for(i = 0; i < sizeof(title_name_stat[title]); i++)
    names += ({ title_name_stat[title][i][0] });
  return names;
}

/*
 * Function name: query_members
 * Description:   Returns list of names of members
 */
string *
query_members()
{
  return m_indexes(name_title);
}
