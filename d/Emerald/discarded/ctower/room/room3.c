inherit "/d/Emerald/ctower/room/ctower_base";
 
#include "../ctower.h"
#include <stdproperties.h>

void wait_phase(object ob);
void wait_move(object ob);
 
void
create_ctower_room()
{
  object door;
 
  set_short("Daemon's Cell");
 
  set_long( "This cell unlike most cells is fairly large "+
     "and completely empty.  It is deathly quiet and you have a feeling "+
     "of complete isolation.  You may be here for a long time.\n" );
 
  add_item(({"wall", "floor", "ceiling"}), "The walls are made of a "+
     "milky crystal that is cold to the touch.\n");
 
  add_item(({"door","crystal_door"}),  "The door is made "+
     "of an opaque crystal that looks fragile but isn't.\n" );

  door = clone_object(CTOWER_OBJ + "door1_b");
  door->move(this_object(), 1);
  door->set_key("phase_quest_key");

}

init() 
{
  ::init();

  set_alarm(60.0, 0.0, &wait_phase(this_player()));
}
 
void
wait_phase(object ob)
{
  if (!present(ob))
  {
    return;
  }

  ob->catch_msg( "After a wait of what seems like "+
      "hours, a willowy alabaster-skinned female "+
      "sprite coalesces out of a swirling vortex of "+
      "energy and introduces herself as Phase, "+
      "Mistress of Reflection.\n" );
  ob->catch_msg("Phase says: You have released the daemon from "+
      "it's prison.\n");
  ob->catch_msg("Phase says: Now I will have to track him down "+
      "and imprison him again.\n");
  ob->catch_msg("Phase sighs deeply.\n");

  set_alarm(10.0, 0.0, &wait_move(ob));
}
 
void
wait_move(object ob)
{
  if (!ob || !present(ob)) 
  {
    return;
  }

  ob->catch_msg("Phase says: Well, off to where you started. "+
      "And remember this:\n");
  ob->catch_msg("Phase says: In the Crystal Tower you cannot "+
      "always trust your senses.\n");
  ob->catch_msg("Phase gestures, and you feel yourself magically "+
      "transferred.\n");
  
  say(QCTNAME(ob) + " sparkles and winks out of existance.\n");

  ob->move_living("M", VILLAGE_DIR + "tower", 1);

  say(QCTNAME(ob) + " arrives in a shower of sparks.\n");
}
