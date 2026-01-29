/*
   /d/Kalad/lib/outlaw.c
   
   Database containing outlaws in Kalad.
   
   Fysix@Genesis, Nov 1997
 */
#pragma strict_types
#pragma save_binary
#pragma no_clone
#pragma no_shadow
#pragma no_inherit

#include <std.h>

#define OUTLAW_FILE "/d/Kalad/obj/outlaws"

// Global variables
string *Outlaws = ({ });

public void load()
{  restore_object(OUTLAW_FILE); }

public void save()
{  save_object(OUTLAW_FILE); }

/* Function name: query_outlaw
 * Description:   Is a player an outlaw?
 * Arguments:     mixed living object or name
 * Returns:       int 1 if he is an outlaw
 */
public int
query_outlaw(mixed living)
{
   if (objectp(living))
      return member_array(living->query_real_name(), Outlaws) >= 0;
   if (stringp(living))
      return member_array(lower_case(living), Outlaws) >= 0;
   return 0;
}

/* Function name: add_outlaw
 * Description:   Add an outlaw to the outlaws list.
 * Arguments:     mixed living object or name
 * Returns:       int 1 if successful, 0 if in the list already, or
 *                   wrong argument type, or no such player
 */
public int
add_outlaw(mixed living)
{
string name;

   // Is he an outlaw already?
   if (query_outlaw(living))
      return 0;

   // Type checking
   if (objectp(living))
      name = living->query_real_name();
   else if (stringp(living))
      name = lower_case(living);
   else return 0;

   // Check if the player exists   
   if (!SECURITY->exist_player(name))
      return 0;

   Outlaws += ({ name });

   save();
   return 1;
}

/* Function name: remove_outlaw
 * Description:   Remove an outlaw from the outlaws lsit
 * Arguments:     mixed living object or name
 * Returns:       int 1 if successful, 0 if not in the list already, or
 *                   wrong argument type
 */
public int
remove_outlaw(mixed living)
{
   if (!query_outlaw(living))
      return 0;
   
   if (objectp(living))
      Outlaws -= ({living->query_real_name()});
   else if (stringp(living))
      Outlaws -= ({lower_case(living)});
   else return 0;

   save();
   return 1;
}

/* Function name: query_outlaws
 * Description:   Who are the outlaws of Kalad?
 * Returns:       string * A copy of the outlaws array.
 */
public string*
query_outlaws()
{
   return Outlaws + ({ });
}

/* Function name: purge
 * Description:   Purge outlaws who are no longer existent. Check 20%
 *                of the members at each purge.
 */
public void
purge()
{
int    i, n;
string *temp = Outlaws;

   n = sizeof(temp);

   for (i = 0; i < n; i++)
      if (random(100) < 20)
         if (!SECURITY->exist_player(Outlaws[i]))
            temp -= ({ Outlaws[i] });

   Outlaws = temp;
   save();
}

void
create()
{
   setuid();
   seteuid(getuid());
   load();

   // Start purge after some random time
   set_alarm(1800.0 + itof(random(1800)), 0.0, purge);
}
