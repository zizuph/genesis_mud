#pragma strict_types

inherit "/cmd/std/command_driver";

#include "skillcache.h"

#include "commands/kdefend.c"

public int
query_cmd_soul()
{
   return 1;
}

string
get_soul_id()
{
   return "BladeMasterDefense";
}

public mapping
query_cmdlist()
{
   return ([
      "kdefend" : "kdefend",
      "addbm" : "addbm",
      "rembm" : "rembm",
   ]);
}


int addbm(string str) {
   object s;

   if(this_player()->query_real_name() != "rhyn") return 0;

   setuid();
   seteuid(getuid());
   s = clone_object((DIR + "shadow"));
   s->shadow_me(this_player());
   write("Added.\n");
   return 1;
}

int rembm(string str) {
   if(this_player()->query_real_name() != "rhyn") return 0;

   this_player()->remove_bm_defense_shadow();
   write("Removed.\n");
   return 1;
}
