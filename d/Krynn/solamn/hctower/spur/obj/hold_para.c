// Paralyzes a player who is holding open the door in 2hp7.


#define DA_ROOM "/d/Krynn/solamn/hctower/spur/room/2hp7"

inherit "/std/paralyze";

void
create_paralyze()
{
  ::create_paralyze();
  
  set_stop_verb("close");
  set_stop_fun("do_close");
  set_stop_object(this_object());
  set_fail_message(
    "You are busy holding the door open. You must close it before "+
    "doing anything else.\n");
  set_stop_message(0);
  set_remove_time(200);
  // The paralyze should be removed earlier than that by the 
  // room cloning it. 
}


int
do_close(string str)
{
  object tp = this_player();
    
  if (!str) 
    {
    tp->catch_msg("close what? Close door?\n");
    return 0;
    }
  if (str != "door" || str != "the door")  
    { 
    tp->catch_msg("close what? Close door?\n"); 
    return 0;
    }
  else
    {
    call_other(DA_ROOM, "close_for_me", tp);
    return 1;
    }
}



/*
int
do_close(string str)
{
  object tp = this_player();
    
  if (!str || str != "door" || str != "the door")
    {   
      tp->catch_msg ("close what? Close door?\n");
    return 0;
    }
  call_other(DA_ROOM, "close_for_me", tp);
  return 1;
}
*/

