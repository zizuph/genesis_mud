inherit "/std/room.c";
#include "/d/Rhovanion/defs.h"
#include "/sys/stdproperties.h"
#include <macros.h>
create_room()
{
   set_short ("All you know is that this room is the coolest you've ever been in and stuff.");
   set_long(" This workplace that is Mute's is filled with various and sundry items of "+
      " miscellaneous nature which if you stared at too long would only confuse you "+
      " so you turn away in fright deciding never to look at them again. \n");
   add_prop(ROOM_I_NO_TELEPORT,1,"Request an audience first.");
   add_exit("/d/Rhovanion/mute/closet","east");
   add_exit("/d/Krynn/solamn/vkeep/post","mail");
}
public void
init()
{
   ::init();
   add_action("my_lock", "lock", 0);
   add_action("my_unlock","unlock",0);
}
public int
my_lock(string str)
{
   if (!str || str != "room")
      return notify_fail("Lock what?\n");
   
   if (query_prop("_room_i_master_lock"))
      return notify_fail("The room is already locked");
   
   add_prop("_room_i_master_lock", 1);
   write("You lock the room to everyone.\n");
   return 1;
}
public int
my_unlock(string str)
{
   if (!str || str != "room")
      return notify_fail("Unlock what?\n");
   
   if (!query_prop("_room_i_master_lock"))
      return notify_fail("The room is already unlocked.\n");
   
   remove_prop("_room_i_master_lock");
   write("You unlock the room.\n");
   return 1;
}
public void
enter_inv(object who, object from)
{
   if (!from)
      return;
   
   if (query_prop("_room_i_master_lock") && who->query_real_name() !=
         "mute")
   {
      set_alarm(0.5, 0.0, "fail_msg", who);
      tell_object(find_player("mute"), who->query_name() + " just tried to "
         +
         "enter.\n");
      write_file("/d/Rhovanion/mute/log/blocked",
         who->query_real_name() + " tried to enter at " +
         extract(ctime(time()), 4, 15) + "\n");
      who->move_living("M", from, 0, 0);
      return;
   }
   
   if (who->query_real_name() == "mute")
      {
      who->catch_msg("Welcome, Master!\n");
      add_prop("_room_i_master_home", 1);
      
      if (query_prop("_room_i_unseen_entries"))
         who->catch_msg("You sense that someone's been here in your " +
         "absence.\n");
      remove_prop("_room_i_unseen_entries");
   }
   
   if (!query_prop("_room_i_master_home") &&
         (who->query_real_name() != "mute"))
   {
      write_file("/d/Rhovanion/mute/log/entries",
         who->query_real_name() + " was here on " +
         extract(ctime(time()), 4, 15) + "\n");
      add_prop("_room_i_unseen_entries", 1);
   }
}

public void
leave_inv(object who, object to)
{
   if (who->query_real_name() == "mute")
      remove_prop("_room_i_master_home");
}

public void
fail_msg(object who)
{
   who->catch_msg("\n\nTry an audience.\n\n");
   return;
}
