/* stadium.c: The Tyr arena main stadium */
inherit "/std/room";
#include "defs.h"
#include <cmdparse.h>
#define SHADOW TYR_STADIUM+"stadiumshadow2"
#define STONE1 TYR_STADIUM+"stone1.c"
#define STONE2 TYR_STADIUM+"stone2.c"

object stone1;
object stone2;

create_room()   
{
    set_short("the Tyr Gladiatorial Stadium");
    set_long("You stand in the south end of a huge rectangular combat "+
             "field, the section commonly used for sparring. Save for "+
             "a tunnel leading under the stands to the south, the only "+
             "exit is a makeshift path into the seats. Templars and "+
             "necromancers stand by to aid those that fall, but take "+
             "that as no guarantee. Their powers are strong, but when "+
             "you enter the arena of Tyr you fight at your own risk.\n");
 
    add_item(({"templar", "templars", "necromancer", "necromancers"}),
             "Pray that you don't need help from such a being.\n");
    add_prop(OBJ_S_WIZINFO, "@@wizinfo@@");
    add_item("ringside","@@ringside@@");
    seteuid(getuid(this_object()));
    stone1 = clone_object(STONE1);
    stone1->move(this_object());
    stone2 = clone_object(STONE2);
    stone2->move(this_object());

    LOAD_ERR("/d/Cirath/tyr/stadium/ringside");

    add_exit(TYR_STADIUM+"ringside.c", "seats", 0, 1);
    add_exit(GLAD+"room/mainhall.c","south",0,1);

}

reset_room()
{
    if (stone1 && !present(stone1,this_object())) stone1->remove_object();
    if (stone2 && !present(stone2,this_object())) stone2->remove_object();

    if (!stone1)
    {
    stone1 = clone_object(STONE1);
    stone1->move(this_object());
    }

    if (!stone2)
    {
    stone2 = clone_object(STONE2);
    stone2->move(this_object());
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
int nope;
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
    object *elist;
    int i;
    ::leave_inv(ob,to);

    if(living(ob))
    {
     elist =(ob->query_enemy(-1) & all_inventory(environment(ob)) );
     for(i=0 ; i < sizeof(elist) ; i++)
     {
         elist[i]->stop_fight(ob);
         ob->stop_fight(elist[i]);
     }
     /*Remove shadow from player*/
     ob->geds_special_func();
    }
}


object
return_in_arena(string what_be_here)
{
    object *thing_list;
    if(!sizeof(thing_list=(FIND_STR_IN_OBJECT(what_be_here, TO))))
        return 0;
    return thing_list[0];
}

mixed
return_obj_in_arena()
{
    return (all_inventory(TO));
}

 
void
init()
{
    ::init();
    add_action("leave", "leave");
}
 
int
leave(string whatleft)
{
    if (whatleft!="gladiator guild")
    {
        return 0;
    }
 
    TP->catch_msg("In the arena? You must be joking.\n");
    return 1;
}
