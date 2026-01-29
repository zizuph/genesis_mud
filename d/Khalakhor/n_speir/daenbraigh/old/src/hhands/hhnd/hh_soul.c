/*
 * Hammerhands soul
 * TAPAKAH, 11/2005
 */

#pragma strict_types

inherit "/cmd/std/command_driver";
#include <macros.h>

#include "hh_guild.h"
#include "../hhands.h"

inherit HHANDS_DIR + "hh_emotes";
inherit HHANDS_DIR + "hh_attacks";
inherit HHANDS_DIR + "hh_help";

void
create()
{
  setuid();
  read_help_dir(HHANDS_DIR + "help/");
  set_help_type(({"hammerhand", "hammerhands","hh"}));
}
string
get_soul_id()
{
  return HHANDS_NAME + " soul";
}

int
query_cmd_soul()
{
  seteuid(getuid());
  return 1;
}

int
hh_help(string str)
{
  write("Available commands are: \n");
  write(implode(m_indices(query_cmdlist())," ")+"\n");
  return 1;
}
mapping
query_cmdlist()
{
  return ([
	   "hhswing" : "hh_swing",
	   "hhjab"   : "hh_jab",
	   "hhjoint" : "hh_joint",
	   "hhhook"  : "hh_hook",
	   "hhwwind" : "hh_whirlwind",
	   "hhhelp"  : "hh_help",
	   ]);
}

