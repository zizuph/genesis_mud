/*
 * /d/??/??/obj/tomb_chest.c
 *
 *   Loot-chest for the dungeon.
 * - Nerull 2017
 *
 */

inherit "/std/container";
inherit "/std/receptacle.c";

#include "../dungeon_defs.h";
#include <stdproperties.h>
#include <macros.h>

#define GEM_DIR "/d/Genesis/gems/obj/"

#define TO      this_object()
#define TP      this_player()


int open_chest(string str);
int close_chest(string str);
int unlock_chest(string str);
int lock_chest(string str);
int remove_chest(mixed blah);
int empty_out(object ob);


string *rgems = ({"alexandrite","beryl_red","diamond","emerald","ruby"}),
       *mgems = ({"sapphire","jade","pearl","spinel_blue","aquamarine","bloodstone"}),
       *cgems = ({"moonstone","garnet","carnelian","amber","onyx","topaz"}),
       *cgems2 =({"chrysoprase","garnet","turquoise","coral","agate"});

object key;

void
create_container()
{
    setuid();
    seteuid(getuid());

    set_name("chest");
    add_name("_tomb_chest");
    set_short("old battered chest");
    add_adj("old");
    add_adj("battered");
    set_long("@@long_desc");


    add_prop(CONT_I_RIGID,1);
    add_prop(CONT_I_MAX_WEIGHT,250000);
    add_prop(CONT_I_WEIGHT,4000);
    add_prop(CONT_I_MAX_VOLUME,25000);
    add_prop(CONT_I_VOLUME,4000);
    add_prop(OBJ_I_VALUE,0);
    add_prop(CONT_I_LOCK,0);
    add_prop(CONT_I_CLOSED,1);
    add_prop(OBJ_M_NO_GET,1);
    add_prop(OBJ_M_NO_STEAL,1);
    set_pick(random(40));

    reset_container();
}



void
certain_drop(object dropper)
{
	setuid();
	seteuid(getuid());
    
	object drop = dropper;
    
	object random_drop = 0;
    
	// Legendary drops
	if (random(100) < LEGENDARY_DROPCHANCE)
	{
		random_drop = clone_object(DUNGEON_DROPDIRECTORY1 +
        tomb_chest_drop_legendary[random(sizeof(tomb_chest_drop_legendary))]);
    
        random_drop->move(drop, 1);
		
		//CHEST_LOG("tomb_chest_log",
        //"A " + random_drop->query_short() + " dropped from the tomb chest.\n");
		
		return;
	}
	
	// Regular epic drops
	random_drop = clone_object(DUNGEON_DROPDIRECTORY1 +
    tomb_chest_drop_epic[random(sizeof(tomb_chest_drop_epic))]);
    
    random_drop->move(drop, 1);
    
    //CHEST_LOG("tomb_chest_log",
    //"A " + random_drop->query_short() + " dropped from the tomb chest.\n");
	
	return;
}



void
reset_container()
{
    int dice;

    add_prop(CONT_I_LOCK,0);
    add_prop(CONT_I_CLOSED,0);

    seteuid(getuid());

    clone_object(GEM_DIR + rgems[random(sizeof(rgems))])->move(TO);
    clone_object(GEM_DIR + mgems[random(sizeof(mgems))])->move(TO);
    clone_object(GEM_DIR + cgems[random(sizeof(cgems))])->move(TO);
    clone_object(GEM_DIR + cgems2[random(sizeof(cgems2))])->move(TO);

	// Certain drops.
	this_object()->certain_drop(this_object());

    add_prop(CONT_I_CLOSED,1);
}


void
init()
{
    ::init();
    add_action(open_chest,"open");
    add_action(close_chest,"close");
    add_action(unlock_chest,"unlock");
    add_action(lock_chest,"lock");
}


int
empty_out(object ob)
{
    if (ob->move(environment(TO)))
        return 0;

    else
        return 1;
}


int
remove_chest(mixed blah)
{
    tell_room(environment(TO), "The "+short()+
    " rapidly dissolves into nothing.\n",0);

    map(all_inventory(TO), empty_out);
    TO->remove_object();
}


int
open_chest(string str)
{
    if((str == "chest") || (str == "battered chest") || (str == "all"))
    {
        if(query_prop(CONT_I_LOCK) == 1)
        {
            write("You'll need to unlock the chest " +
            "to open it.\n");

            return 1;
        }

        if (present("_tomb_monster_", environment(this_object())))
        {
            write("The chest is guarded by someone!\n");
            return 1;
        }


        if(query_prop(CONT_I_CLOSED) == 1)
        {
            write("You open the chest.\n");
            say(QCTNAME(TP) + " opens the chest.\n");
            add_prop(CONT_I_CLOSED,0);

            set_alarm(30.0, 0.0, "remove_chest");
        }

        else

        {
            write("The chest is already open.\n");
        }

        return 1;

    }

    else
    {
       notify_fail("Open what?\n");
       return 0;
    }

}


int
lock_chest(string str)
{
    if((str == "chest") || (str == "battered chest"))
    {
        if(query_prop(CONT_I_CLOSED) == 0)
        {
             write("You'll need to close the chest before " +
             "you can lock it.\n");
             return 1;
         }

         if(query_prop(CONT_I_LOCK) == 0)
         {
             if(present("_tomb_chest_key",TP))
             {
                 write("You lock the chest.\n");
                 say(QCTNAME(TP) + " locks the chest.\n");
                 add_prop(CONT_I_LOCK,1);
                 return 1;
             }

             write("You'll need the proper key to lock the " +
             "chest.\n");

             return 1;
         }

         else
         {

             write("The chest is already locked.\n");
             return 1;
         }
    }

    else
    {
        notify_fail("Lock what?\n");
        return 0;
    }
}


int
unlock_chest(string str)
{
    if((str == "chest") || (str == "battered chest"))
    {
        if(query_prop(CONT_I_CLOSED) == 0)
        {
            write("The chest is open already.\n");
            return 1;
        }


        if (present("_tomb_monster_", environment(this_object())))
        {
            write("The chest is guarded by someone!\n");
            return 1;
        }

        if(query_prop(CONT_I_LOCK) == 1)
        {
            if(present("_tomb_chest_key",TP))
            {
                key=present("_tomb_chest_key",TP);
                write("You unlock the chest.\n");
                write("The " + key->short() + " breaks as the " +
                "chest is unlocked.\n");
                key->remove_object();
                say(QCTNAME(TP) + " unlocks the chest.\n");
                //write_file(ULOG, TP->query_name()+" " + ctime(time()) + "\n");
                add_prop(CONT_I_LOCK,0);
                return 1;
            }

            write("You'll need the proper key to unlock the " +
            "chest.\n");
            return 1;
        }

        else
        {
            write("The chest is already unlocked.\n");
            return 1;
        }
    }

    else
    {
        notify_fail("Unlock what?\n");
        return 0;
    }
}


int
close_chest(string str)
{
    if((str == "chest") || (str == "battered chest"))
    {
        if(query_prop(CONT_I_CLOSED) == 1)
        {
            write("The chest is already " +
            "closed.\n");
        }

        else
        {
            write("You try to close the chest, but the lid seems to " +
            "be stuck in open position.\n");
            say(QCTNAME(TP) + " tries to close the chest, but fails.\n");
        }

        return 1;

    }

    else
    {
        notify_fail("Close what?\n");
        return 0;
    }
}


string
long_desc()
{
    if(query_prop_setting(CONT_I_CLOSED) == 1)
    {
        return "An old batter chest made of wood.\n" +
        "The chest is closed.\n";
    }

    else
    {
        return "An old battered chest made of wood.\n" +
        "The chest is open.\n";
    }
}
