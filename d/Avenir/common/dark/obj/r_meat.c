// Piece of rotten meat, part of rat trap quest
// Produces food poisoning when consumed.
// Made by Boriska@Genesis, Nov 1994

inherit "/std/food";

#include "/d/Avenir/common/dark/dark.h"
#include "/d/Avenir/include/rat_trap.h"

create_food()
{
  if ( !IS_CLONE)
    return;
  
  seteuid(getuid());
  set_name ("meat");
  set_amount (10);
  add_name (MEAT_ID);
  set_short ("piece of rotten meat");
  add_name("a piece of rotten meat");
  set_pshort ("pieces of rotten meat");
  add_adj ("rotten");
  set_long ("Piece of rotten meat, stinking like... rotten meat.\n" +
	    "Think twice before eating it.\n");	    
  add_prop (OBJ_I_VALUE, 10);
  set_alarm (10.0, 180.0, "stink");
} 

// this enables special effect for the meat, poisoning.
void
special_effect(int amnt)
{
    int i;
    for (i = 0; i < amnt; i++)
        clone_object(OBJ + "fp")->move(this_player());
}
       
void
stink()
{
  object obj;
  
  if ( living(obj = environment()) )
    {
      obj->catch_msg ("An awful stench rises from the rotten meat.\n");
      tell_room (environment(obj),
	  "An awful stench rises from the rotten meat carried by " +
	  QCNAME (obj) + ".\n", obj);
      return ;
    }
  
  tell_room (obj, "An awful stench rises from the rotten meat.\n"); 
}

void
decay ()
{
  object env = environment();

  if (env)
      tell_room (env, "The rotten meat decays, leaving nothing.\n");
  remove_object(); // in any case
}



