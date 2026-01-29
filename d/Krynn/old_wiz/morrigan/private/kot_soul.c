inherit "/cmd/std/command_driver";

#include "/d/Krynn/common/defs.h"

string get_soul_id() { return "Knights of Takhisis"; }

int query_cmd_soul() { return 1; }

mapping
query_cmdlist()
{
   return ([ "grant" : "grant" , "kgrin" : "kgrin" ]);
}

int
grant(string str)
{
   object *oblist;
   string reaction = "";
   
   if (TP->query_name() != "morrigan" &&
         TP->query_name() != "Morrigan")
   {
      write("What?\n");
      return 1;
   }
   
   if (!strlen(str))
      {
      notify_fail("Grant whom permission to enter the Tower?\n");
      return 0;
   }
   
   oblist = parse_this(str, "[to] [the] %l");
   if (!sizeof(oblist) > 1)
      {
      write("Only one person may receive the charm.\n");
      return 1;
   }
   
   if (oblist[0]->query_alignment() <= -300)
      reaction = "You feel pleasant feeling surge through your veins "+
   "as the spell is cast.";
   else
      reaction = "You feel a singing pain on your forehead as the "+
   "spell is cast.";
   
   actor("You close your eyes, muttering a few words in the spidery "+
      "language of magic, and kiss", oblist," gently on the "+
      "forehead.\n");
   target(" closes his eyes and kisses you softly on the forehead, "+
      "muttering a few strange words. "+reaction+"\n", oblist);
   all2act(" closes his eyes and kisses", oblist, " gently on the "+
      "forehead, muttering some strange words under his breath.");
   oblist[0]->add_prop("_i_may_pass_the_grove", 1);
   return 1;
}

int
kgrin(string str)
{
   object *oblist;
   
   if (!strlen(str))
      {
      write("You grin in a lopsided, cynical way.\n");
      all(" grins in a lopsided, cynical way.");
      return 1;
   }
   
   oblist = parse_this(str, "[at] [the] %l");
   oblist -= ({ this_player });
   
   if (!sizeof(oblist))
      {
      notify_fail("Kgrin at who??\n");
      return 0;
   }
   
   actor("You grin at", oblist, " in a lopsided, cynical way.");
   targetbb(" grins at you in a lopsided, cynical way.", oblist);
   all2actbb(" grins at", oblist, " in a lopsided, cynical way.");
   return 1;
}
