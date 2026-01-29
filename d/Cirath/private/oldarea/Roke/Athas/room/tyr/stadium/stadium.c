inherit "/std/room";

#include "/d/Roke/common/defs.h"
#define SHADOW "/d/Roke/Athas/obj/stadiumshadow"
#define STONE  "/d/Roke/Athas/room/tyr/stadium/stone"

object stone;

create_room()	
{
    set_short("Stadium");
    set_long("You have entered the gladitorial arena. It "+
	     "is a very magnificent sight, indeed. There are seats "+
	     "surrounding the actual arena for spectators to sit "+
	     "and view the battles between their favourite gladiators."+
	     " You can see a demon standing in the middle of the arena. "+
	     " The arena itself is huge and capable of supporting many "+
	     "fights at once.\n");
    add_item("demon","The demon is guarding the fighters so that they can't die.\n");
    add_prop(OBJ_S_WIZINFO, "@@wizinfo@@");
    add_item("ringside","@@ringside@@");
    seteuid(getuid(this_object()));
    stone = clone_object(STONE);
    stone->move(this_object());

    add_exit("/d/Roke/Athas/room/tyr/stadium/ringside","seats",0);
   add_exit(TYR+"stadium/p3","down");

}

reset_room()
{
    if (stone && !present(stone,this_object())) stone->remove_object();

    if (!stone)
    {
	stone = clone_object(STONE);
	stone->move(this_object());
    }
}
  
string wizinfo()
{
    return "This room adds a special shadow to all interactives who enters.\n"+
	   "If the shadow can't be removed from the player he can't exit\n"+
	   "this room and he will need help.\n"+
	   "What you can do to help him as wizard is do:\n"+
	   "Call player remove_autoshadow "+SHADOW+"\n";
}
	   
enter_inv(object ob,object from)
{
    object shad;

  ::enter_inv(ob,from);
    shad=clone_object(SHADOW);
  if(interactive(ob))
  {    
      if(shad->shadow_me(ob)!=1)
      {
	  ob->catch_msg("It isn't safe for you to enter here.\n");
	  ob->move(from);
      }
  }
}

leave_inv(object ob,object to)
{
    ::leave_inv(ob,to);

	/*Remove shadow from player*/
    if(interactive(ob))
    {
	ob->geds_special_func();
    }
}

