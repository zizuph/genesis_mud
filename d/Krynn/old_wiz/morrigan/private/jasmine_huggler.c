inherit "/cmd/std/command_driver";

#include "/d/Krynn/common/defs.h"

string get_soul_id() { return "Jasmine's Huggler"; }

int query_cmd_soul() { return 1; }

mapping
query_cmdlist()
{
   return ([ "huggle" : "huggle", ]);
}

int
huggle(string str)
{
   object *oblist;
   
   if (!strlen(str))
      {
      NF("Huggle who??\n");
      return 0;
   }
   
   oblist = parse_this(str, "[at] [the] %l");
   oblist -= ({ this_player });
   
   if (!sizeof(oblist))
      {
      notify_fail("Huggle who??\n");
      return 0;
   }
   
   actor("You huggle", oblist, " in a way only you can.");
   targetbb(" huggles you in a way only she can.", oblist);
   all2actbb(" huggles", oblist, " in a way only she can.");
   return 1;
}
