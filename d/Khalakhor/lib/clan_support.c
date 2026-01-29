/*
 * clan_support.c
 *
 * Module inheritable into npcs to add sept and clan name support
 * in their creation. This routine has special title generating
 * routines, so the function set_title() may not be called from the
 * upper level npc. To add an 'extra' title, use the function
 * cs_set_title instead.
 *
 * Khail - April 24/97
 *
 * Light refactoring
 * Tapakah, 07/2021
 * Added population DB
 * Tapakah, 08/2021
 */

#pragma no_clone
#pragma strict_types

#include <macros.h>
#include "/d/Khalakhor/sys/paths.h"
#include "/d/Khalakhor/se_speir/population.h"

inherit STDHUMAN;
inherit "/d/Khalakhor/lib/logger";

/* Global vars. */
static string clan_name,
  sept_name,
  title;

/* Prototypes. */
int cs_set_clan(string str);
string cs_query_clan();
int cs_set_sept(string str);
string cs_query_sept();
void cs_set_title(string str);
string cs_query_full_title();
string cs_query_full_clan_name();

/*
 * Function name: cs_set_clan
 * Description  : Sets a clan name.
 * Arguments    : str - The clan name.
 * Returns      : 1;
 */
int
cs_set_clan(string str)
{
  clan_name = capitalize(str);
  this_object()->set_title(cs_query_full_title());
  return 1;
}

/*
 * Function name: cs_query_clan
 * Description  : Returns the clan name.
 * Arguments    : n/a
 * Returns      : Clan name, capitalized and as a string.
 */
string
cs_query_clan()
{
  if (!clan_name)
    return "";
  return clan_name;
}

/*
 * Function name: cs_set_sept
 * Description  : Sets the sept (actual family) of the living.
 * Arguments    : str - Sept name as a string.
 * Returns      : 1
 */
int
cs_set_sept(string str)
{
  sept_name = str;
  this_object()->set_title(cs_query_full_title());
  return 1;
}

/*
 * Function name: cs_query_sept
 * Description  : Returns the sept name.
 * Arguments    : n/a
 * Returns      : Sept name, capitalized and as a string.
 */
string
cs_query_sept()
{
  if (!sept_name)
    return "";
  return sept_name;
}

/*
 * Function name: cs_set_title
 * Description  : Sets the npc's special title, aside from clan titles.
 * Arguments    : str - Title as a string.
 * Returns      : n/a
 */
void
cs_set_title(string str)
{
  if (!str)
    title = "";
  title = str;
  this_object()->set_title(cs_query_full_title());
}

string
cs_query_title ()
{
  return title;
}
/*
 * Function name: cs_query_full_title
 * Description  : Generates a 'full' title of the living's clan, sept,
 *                and any title that was directly set.
 * Arguments    : n/a
 * Return       : The described title as a string.
 */
string
cs_query_full_title()
{
  string ret;

  ret = cs_query_full_clan_name();

  if (title && strlen(title))
    if (strlen(ret))
      ret += ", ";
  ret += title;

  return ret;
}

/*
 * Function name: cs_query_full_clan_name
 * Description  : Returns the living's full clan name, i.e their
 *                sept and clan.
 * Arguments    : n/a
 * Returns      : A string describing the npc's clan names.
 */
string
cs_query_full_clan_name()
{
  string ret;

  if (!sept_name || !strlen(sept_name))
    ret = "";
  else
    ret = capitalize(sept_name);

  if (!clan_name || !strlen(clan_name))
    ret += "";
  else if (sept_name && strlen(sept_name))
    ret += " of the Clan " + capitalize(clan_name);
  else
    ret += "of the Clan " + capitalize(clan_name);

  return ret;
}

nomask varargs int
configure_from_database (string name, int log_fail=0)
{
  string Name = capitalize(name);
  string *found = 0;

  foreach (string *denizen: SE_SPEIR_POPULATION) {
    if (Name == denizen[SE_SP_NAME]) {
      found = denizen;
      break;
    }
  }

  if (! found) {
    if (log_fail)
      log_me("Name " + Name + " not found in population db",
             "warning", "population");
  	return 0;
  }

  string art = sizeof(regexp(({found[SE_SP_LOCATION]}),
                             "^[A-Z].*")) ? "" : "the ";
  set_name(name);
  set_living_name(name);
  if (found[SE_SP_SEPT])
    cs_set_sept(found[SE_SP_SEPT]);
  if (found[SE_SP_CLAN])
    cs_set_clan(found[SE_SP_CLAN]);
  cs_set_title(found[SE_SP_OCCUPATION] + " of " + art + found[SE_SP_LOCATION]);
  return 1;
}

mixed *
query_random_population (int column, string column_value, int size)
{
  mixed *population = ({});
  int population_size = sizeof(SE_SPEIR_POPULATION);

  if (size > population_size)
    return 0;

  foreach (string *citizen: SE_SPEIR_POPULATION) {
    if (column >= sizeof(citizen))
      return 0;
    if (citizen[SE_SP_NAME] == query_name())
      continue;
    if (!column_value || citizen[column] == column_value)
      population += ({ citizen });
  }

  int p_size = sizeof(population);
  if (size > p_size)
    return 0;

  if (size == p_size)
    return population;

  mixed *excerpt = ({});
  int *track = allocate(sizeof(population));
  int e;
  while (sizeof(excerpt) < size) {
    e = random(p_size);
    while (track[e])
      e = random(p_size);
    track[e] = 1;
    excerpt += ({ population[e] });
  }
  return excerpt;
}

string *
get_population_column (mixed population, int column_index)
{
  string *column = allocate(sizeof(population));
  int i, p;
  
  for (i=0, p=sizeof(population); i<p; i++)
    column[i] = population[i][column_index];

  return column;
}
