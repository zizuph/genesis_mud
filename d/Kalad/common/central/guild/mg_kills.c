/*
OBJ:  Merchant Guild kill list
BY:   Sebster
DATE: Aug 28, 1994
PURP: If an NPC who is derived from mg_npc.c is killed by a player,
      His/her name will be stored, and trade penalties result. Maybe there
      will be a quest (which may be done only once) to clear the player's
      record.
CRED: The file IO / list is a modified version of account.c of the GoG.
*/

#include "/d/Kalad/defs.h"

#define SAVE_FILE CENTRAL(guild/mg_kills)

mapping kills;

/*
Function: create()
Purpose: creates the mg_kills object
*/
void
create()
{
  seteuid(getuid(this_object()));
  if(!restore_object(SAVE_FILE)) kills = ([ ]);
}

/*
Function: query_kills(string person)
Returns: the array of kills made by person
*/
int *
query_kills(string person)
{
  if (!kills[person]) return 0;
  return kills[person];
}

/*
Function: query_sp_kills(object person, int kill_type)
Returns: the number of kill sof kill_type
*/
public int
query_sp_kills(object person, int kill_type)
{
  string pl_name = person->query_real_name();
  int *num_kills = query_kills(pl_name);
  if (!sizeof(num_kills)) return 0;
  return num_kills[kill_type];
}

/*
Function: set_kills(string person, int *num_kills)
Purpose: set the kills made by a person
*/
void
set_kills(string person, int *num_kills)
{
  if (!sizeof(num_kills))
    kills = m_delete(kills, person);
  else
    kills[person] = num_kills;
  seteuid(getuid(this_object()));
  save_object(SAVE_FILE);
}

/*
Function: inc_kills(string person, int kill_type)
Purpose: increase the number killed of kill_type
*/
void
inc_kills(string person, int kill_type)
{
  int *num_kills = query_kills(person);
  num_kills[kill_type] = num_kills[kill_type] + 1;
  set_kills(person, num_kills);
}

/*
Function: query_killers()
Returns: a list of all the killers in the game
*/
string *
query_killers()
{
  return m_indexes(kills);
}

/*
Function: remove_object()
Purpose: remove the mg_kills object from memory
*/
int
remove_object()
{
  destruct();
  return 1;
}
