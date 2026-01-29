#pragma strict_types

inherit "/cmd/std/command_driver";
#include <adverbs.h>
#include <cmdparse.h>
#include <composite.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <filter_funs.h>
#include "/d/Krynn/common/defs.h"

public int query_cmd_soul() { return 1; }
public string get_soul_id() { return "Kender Soul"; }

public mapping
query_cmdlist()
{
   return ([
         "khelp" : "khelp",
         "klook" : "klook",
]);
}

#include "/d/Krynn/morrigan/kender/kender_emotes.h" /* Emotes */

/*------------------------==< Help files >==--------------------------*/

int
khelp(string str)
{
   if (!str)
      {
      write("This will be the kender general help file.\n");
      return 1;
   }
   
   write("So far there are no topics of help, this is just in testing.\n");
   return 1;
   
}

