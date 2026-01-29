#pragma strict_types
#pragma no_clone

public int
_lfind(string str)
{
   object tp = this_player();
   string target = tp->query_lfind_target();

   if(!str || !strlen(str))
   {
      if(target && strlen(target) > 0)
      {
         return notify_fail("You are searching for " + target + ".\n");
      }

      return notify_fail("You are not currently searching for " +
         "anything.\n");
   }

   if(target == str)
   {
      return notify_fail("You are already searching for " + str + ".\n");
   }

   if(str == "stop")
   {
      if(target == 0)
      {
         return notify_fail("You are not searching for anything.\n");
      }

      tp->set_lfind_target(0);
      write("You stop searching for " + target + ".\n");

      return 1;
   }

   if(!tp->set_lfind_target(str))
   {
      return notify_fail("You cannot search for that.\n");
   }

   write("You begin searching for " + str + (target ? " and end your " +
      "search for " + target : "") + ".\n");

   return 1;
}
