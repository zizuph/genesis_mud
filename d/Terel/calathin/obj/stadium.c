/* stadium.c: The Tyr arena main stadium */
#include "/d/Terel/include/Terel.h"
inherit STDROOM;
#include <cmdparse.h>
#define SHADOW CALATHIN_DIR+"obj/stadiumshadow"
#define STONE CALATHIN_DIR+"obj/stone.c"

object stone;

create_room()  
{
    set_short("Sparring field of the Silver Hall");
    set_long("You're standing in a grass field enclosed by a wooden "+
                   "fence. Wooden stands surround some parts of the field "+
                   "allowing for spectators to watch the tournaments "+
                   "and practices that take place. You can enter the "+
                   "stands or return back into the Silver Hall.\n");
    add_prop(OBJ_S_WIZINFO, "@@wizinfo@@");
    add_item("ringside","@@ringside@@");
    seteuid(getuid(this_object()));
    stone = clone_object(STONE);
    stone->move(this_object());

    add_exit(CALATHIN_DIR+"obj/ringside.c", "stands", 0, 1);
    add_exit(CALATHIN_DIR+"guild","east",0,1);

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
    int nope;

    ::enter_inv(ob,from);
    if(interactive(ob))
    {    
        object shad = clone_object(SHADOW);

        if (shad->shadow_me(ob) != 1)
        {
            ob->catch_msg("It isn't safe for you to enter here.\n");
            ob->move(from);
            shad->remove_shadow();
        }
    }
}

void
leave_inv(object ob,object to)
{
    ::leave_inv(ob,to);

     /*Remove shadow from player*/
     ob->geds_special_func();
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
