/* Created 29/9/98 by Bishop, of Calia. This is a room in the
gnome village of Rust. It serves as a general store, and it's
heavily inspired by Maniac's shop in the Crystalline Palace */


#pragma save_binary

inherit "/lib/shop";
inherit "/std/room";

#include <defs.h>
#include <stdproperties.h>
#include <macros.h>

object keeper;

void
reset_room()
{
    if (!objectp(keeper)) 
    {
        keeper = clone_object(RUST_NPCS +"shopkeeper_mons"); 
        keeper->move_living("in", TO);
    } 
}

void
create_room()
{
    config_default_trade();

    set_short("Equipment store in gnome village");

    set_long("You have entered a hut that serves as a general" +
        " store in the gnome village." +
        " There is a sign on the counter that" +
        " you can read. The items for sale are stashed on shelves" +
        " behind the counter.\n");

    add_item("sign","It's typed in neat letters, and you can read it.\n");
    add_item("items","To see what items you can buy here, try <list>.\n");
    add_item("shelves","The shelves are used to display the items you" +
        " can buy here.\n");
    add_item("counter","It's solid wood and would reach to the stomach" +
        " of an average gnome.\n");

    
    add_exit(VILLAGE+"village_path9","out",0,1);
    set_store_room(VILLAGE + "village_store_room");

    add_prop(ROOM_I_HIDE, 70);
    add_prop(ROOM_I_INSIDE, 1);

    query_store_room()->load_me(); 

    reset_room();
}

void
init()
{
    ::init();   
    init_shop();
}

int
check_keeper(string arg)
{
    object enemy;

    if (keeper && present(keeper,this_object()))
    {
        if (enemy = keeper->query_attack())
        {
            if(enemy == TP)
            {
                keeper->command("say You want me to help you while you" +
                    " are trying to kill me? Fool!");
            }
            else
            {
                keeper->command("say I can't help you, I'm busy defending" +
                    " myself!\n");
            }
            return 0;
        }
        else
        return 1;
    }
    else {
        TP->catch_msg("You'll have to wait for the shopkeeper to return" +
            " if you want to use the store.\n");
        return 0;
    }
}

int
do_buy(string args)
{
    if(!check_keeper("buy")) return 1;

    return ::do_buy(args);
}

int
do_list(string str)
{
    object tp = this_player();

    if(!check_keeper("list")) return 1;

    return ::do_list(str);
}

int
do_sell(string args)
{
    object tp = this_player();

    if(!check_keeper("sell")) return 1;

    return ::do_sell(args);
}

int
do_value(string args)
{
    object tp = this_player();

    if(!check_keeper("value")) return 1;

    return ::do_value(args);
}

