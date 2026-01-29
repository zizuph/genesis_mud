/*
   log.c
   
   Object that logs strings.
   
   Fysix@Genesis, Dec 1997
 */
#pragma strict_types
#pragma save_binary
#pragma no_clone

// Where to log?
#define LOG_FILE "/d/Kalad/std/steed/log"

// Globals
string *Logged_str = ({ });

// Add a string to the log
void
add_log_string(string s)
{
   if (member_array(s, Logged_str) >= 0)
      return;
      
   Logged_str += ({ s });
   save_object(LOG_FILE);
}

// Remove a string from the log
void
remove_log_string(string s)
{
   Logged_str -= ({ s });
}

string *
query_log()
{
   return Logged_str + ({ });
}

void
create()
{
   setuid();
   seteuid(getuid());
   restore_object(LOG_FILE);
}
