/*
 * Newbie helper poster
 * TAPAKAH, 05/2005
 *
 * Changed to use pin instead of signing up
 * TAPAKAH, 06/2005.
 * The pin is /d/Genesis/start/newbie/newbie_pin.c
 * Enabled players to restore lost pins
 * Finwe, August 2006
 */

#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include <state_desc.h>
#include "newbie.h"

inherit "/std/object";

#define NO_HELPERS   "| The list is empty, but that will change soon!    |\n"
#define ADD_ERR      "List who? Use 'list me' to be put on helper list.\n"
#define DELETE_ERR   "Unlist who? Use 'unlist me' to be removed from helper list.\n"
#define HELPER_INSTR "| Use 'list me' to receive your newbie helper pin  |\n| or restore a lost one.                           |\n"
#define DELETE_INSTR "| Use 'break pin' to get rid of the newbie pin.    |\n"
#define NEWBIE_INSTR "| Use 'list me' if your newbie pin got lost!       |\n| Use 'examine pin' to learn about your pin.       |\n"
#define ONLINE "(logged on)"

#define TP this_player()

int add_helper(string str);
int read_poster(string str);

string list_helpers();
string show_instructions();

void
create_object()
{
  if(! IS_CLONE)
    return;
  
  ::create_object();

  setuid();
  seteuid(getuid());

  set_name("poster");
  add_name("list");
  add_adj( ({ "friendly", "welcome", "WELCOME" }) );
  set_short("friendly WELCOME poster");
  set_long(
	   "*--------------------------------------------------*\n"+
	   "|                                                  |\n"+
	   "|                  W E L C O M E                   |\n"+
	   "|                                                  |\n"+
	   "|  We are glad to welcome you, the new player, to  |\n"+
	   "|  the realms of Genesis. You are now carrying a   |\n"+
	   "|  pin which allows you to contact people who are  |\n"+
	   "|  willing to help you around.                     |\n"+
	   
	   "@@show_instructions@@"+
	   "|                                                  |\n"+
	   "*--------------------------------------------------*\n"
	   );
  add_prop(OBJ_M_NO_GET,1);
  add_prop(OBJ_I_VOLUME,10000);
  add_prop(OBJ_I_WEIGHT,1000);
  add_prop(OBJ_I_VALUE,0);
}

void
init()
{
  ::init();

  add_action(add_helper,"list");
  add_action(read_poster,"read");
}

void
log_me(string helper, string action)
{
  log_file(HELPER_LOG,ctime(time()) + " " + helper + " " + action + "\n");
}

int
add_helper(string str)
{
  string who;
  string entry;
  mapping helpers;
  
  if(str != "me") 
  {
    notify_fail(ADD_ERR);
    return 0;
  }
  helpers = restore_map(HELPER_FILE);
  entry = TP->query_name();

  if(helpers[entry])
  {
    log_me(entry, "pin restored");
  }

  helpers[entry] = time();
  save_map(helpers, HELPER_FILE);
  clone_object(NEWBIE_PIN)->move(TP);

  if (SD_IS_NEWBIE(TP))
  {
    write("You receive your newbie pin. Use it wisely, start with 'examine pin'.\n");
    command("$wear pin");
    log_me(entry, "newbie");
  }
  else 
  {
    write("You receive your helper pin. Thank you for volunteering.\n");
    log_me(entry, "helper");
  }
  return 1;
}

int
read_poster(string str)
{
  string what;
  
  if(str == "poster")
  {
    TP->command("$examine poster");
    return 1;
  }
  notify_fail("Read what?\n");
  return 0;
}

string
list_helpers()
{
  mapping helper;
  object pl;
  string *ind;
  string list;
  string line;
  int h,sh;
  
  helper = restore_map(HELPER_FILE);
  ind = m_indices(helper);
  sh = sizeof(ind);
  list = "";
  
  if (h == sh) 
  {
    return NO_HELPERS;
  }
  for(h=0;h<sh;h++) 
  {
    pl = find_player(lower_case(ind[h]));
    if(pl && (!pl->query_linkdead()))
      line = ind[h] + ONLINE;
    else
      line = ind[h];
    list += sprintf("|%50|s|\n",line);
  }
  return list;
}

string
show_instructions()
{
  if(SD_IS_NEWBIE(TP))
    return "|                                                  |\n"+ NEWBIE_INSTR;
  else
    return "|                                                  |\n"+ HELPER_INSTR + DELETE_INSTR;
}
