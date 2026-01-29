#pragma strict_types
#pragma no_inherit
#pragma no_clone

#include "defs.h"

inherit "/cmd/std/command_driver";
inherit "/d/Earthsea/lib/help";

inherit (GARDENER_DIR+"commands/lfind");
inherit (GARDENER_DIR+"commands/lcomment");
inherit (GARDENER_DIR+"commands/lcopy");
inherit (GARDENER_DIR+"commands/ldisplay");

public void
create()
{
   set_help_type(({"gardener"}));
   read_help_dir(GARDENER_HELP);
}

public int
query_cmd_soul()
{
   return 1;
}

string
get_soul_id()
{
   return "Gardeners_of_Gont";
}

public mapping
query_cmdlist()
{
   return ([
      "lfind" : "_lfind",
      "lcomment" : "_lcomment",
      "lcopy" : "_lcopy",
      "ldisplay" : "_ldisplay",
   ]) + help_cmdlist();
}
