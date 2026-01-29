/*
 * The Mercenary Battlegrounds, by Morrigan Sept 2002
 *     taken from the gladiator arena in Cirath
 *
 * Updated for Sparkle by Lunatari 2006
 */
inherit "/std/room";

#include "../merc.h"
#include "../room/room.h"
#include <cmdparse.h>

#define SHADOW MBATTLE + "shadow"
#define STONE1 MBATTLE + "stone1.c"
#define STONE2 MBATTLE + "stone2.c"

object stone1, overseer;

int enter_hall()
{
    tell_room(find_object(MBATTLE + "stands"), QCTNAME(TP)+" leaves the "+
	"arena, entering the Mercenary Halls to the south.\n");

    write(GREAT_HALL_ENTER);
}

int enter_stands()
{
    tell_room(find_object(MBATTLE + "stands"), QCTNAME(TP)+" carefully "+
	"skirts the edges of the arena and ascends into the stands.\n");

    write("You carefully skirt the edges of the arena, and ascend into "+
	"the stands.\n");
}

string long_desc()
{
    return "You have entered a vast open area which is obviously an arena. "+
	"To the south is the entrance to the Mercenary Halls, and to the north "+
	"are the stands.\n";
}

reset_room()
{
    if (stone1 && !present(stone1,this_object())) stone1->remove_object();

    if (!stone1)
    {
	stone1 = clone_object(MBATTLE + "stone");
	stone1->move(this_object());
    }

    /* Commenting this out. Raddick has left. (Gorboth)
    if (!overseer)
    {
        overseer = clone_object(MNPC + "raddick");
	overseer->move(this_object());
    }
    */

}

create_room()   
{
    set_short("A vast open area");
    set_long("@@long_desc");

    add_prop(OBJ_S_WIZINFO, "@@wizinfo@@");

    add_item("ringside","@@ringside@@");

    seteuid(getuid(this_object()));

    LOAD_ERR(MBATTLE + "stands");

    add_exit(MBATTLE + "stands.c", "stands", "@@enter_stands", 1);
    add_exit(MROOM + "great_hall.c", "south", "@@enter_hall", 1);

    reset_room();
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

    if(living(ob) && sizeof(ob->query_enemy(-1)))
    {
	elist = (ob->query_enemy(-1) & all_inventory(environment(ob)) );

	for(i=0 ; i < sizeof(elist) ; i++)
	{
	    elist[i]->stop_fight(ob);
	    ob->stop_fight(elist[i]);
	}

	/*Remove shadow from player*/
	ob->geds_special_func();
    }

    if (living(ob))
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
