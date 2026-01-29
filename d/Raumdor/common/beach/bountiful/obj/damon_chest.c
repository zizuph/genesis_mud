/*
 * /d/Raumdor/common/beach/bountiful/obj/damon_chest.c
 *
 * Loot-chest for the Damon Skragg boss on the Bountiful
 * - Nerull
 *
 */

inherit "/std/container";
inherit "/std/receptacle.c";
inherit "/lib/unique";

#include "../defs.h";
#include <stdproperties.h>
#include <macros.h>

#define GEM_DIR "/d/Genesis/gems/obj/"

#define BOUNTIFUL_CHEST_LOG(x,y)  write_file("/d/Raumdor/log/" + x, extract(ctime(time()), \
                                             4, 15) +" "+ y )


int open_chest(string str);
int close_chest(string str);
int unlock_chest(string str);
int lock_chest(string str);
int remove_chest(mixed blah);
int empty_out(object ob);

int chest_key_id;


string *rgems = ({"alexandrite","beryl_red","diamond","emerald","ruby"}),
       *mgems = ({"sapphire","jade","pearl","spinel_blue","aquamarine",
	   "bloodstone"}),
      *cgems = ({"moonstone","garnet","carnelian","amber","onyx","topaz"}),
       *cgems2 =({"chrysoprase","garnet","turquoise","coral","agate"});

object key;


/*
 * Function name: create_container()
 * Description  : Constructor. Creates the container.
 */
void
create_container()
{

    seteuid(getuid(TO));

        set_name("chest");
        add_name("_damon_chest");
        set_short("black wooden chest");
        add_adj("black");
        add_adj("wooden");
        set_long("@@long_desc");


        add_prop(CONT_I_RIGID,1);
        add_prop(CONT_I_MAX_WEIGHT,250000);
        add_prop(CONT_I_WEIGHT,4000);
        add_prop(CONT_I_MAX_VOLUME,25000);
        add_prop(CONT_I_VOLUME,4000);
        add_prop(OBJ_I_VALUE,0);
        add_prop(CONT_I_LOCK,1);
        add_prop(CONT_I_CLOSED,1);
        add_prop(OBJ_M_NO_GET,1);
        add_prop(OBJ_M_NO_STEAL,1);
        set_no_pick();

        reset_container();
        seteuid(getuid(TO));
}

void
set_key_id(int i)
{
    chest_key_id = i;
}


int
query_chest_id(int i)
{
    return chest_key_id;
}


/*
 * Function name: reset_container()
 * Description  : Resets and determines what should be inside.
 */
void
reset_container()
{
    add_prop(CONT_I_LOCK,0);
    add_prop(CONT_I_CLOSED,0);
    
    object chest_reward;

    seteuid(getuid());

    clone_object(GEM_DIR + rgems[random(sizeof(rgems))])->move(TO);
    clone_object(GEM_DIR + mgems[random(sizeof(mgems))])->move(TO);
    clone_object(GEM_DIR + mgems[random(sizeof(mgems))])->move(TO);
    clone_object(GEM_DIR + cgems[random(sizeof(cgems))])->move(TO);
    clone_object(GEM_DIR + cgems[random(sizeof(cgems))])->move(TO);
    clone_object(GEM_DIR + cgems2[random(sizeof(cgems2))])->move(TO);
    clone_object(GEM_DIR + cgems2[random(sizeof(cgems2))])->move(TO);

    int diceroll = random(100);
    
    switch (diceroll)
    {
        case 0..25:
        chest_reward = clone_unique(one_of_list(({
                    BEACH_DIR + "bountiful/chest_rewards/shadowy_platemail.c",
                   })),
        15, BEACH_DIR + "bountiful/chest_rewards/c_vase", 0, 25);    
        break;
        
        case 26..50:
        chest_reward = clone_unique(one_of_list(({
                    BEACH_DIR + "bountiful/chest_rewards/sight_ring.c",
                   })),
        15, BEACH_DIR + "bountiful/chest_rewards/c_globe", 0, 25);    
        break;
        
        case 51..75:
        chest_reward = clone_unique(one_of_list(({
                    BEACH_DIR + "bountiful/chest_rewards/magic_scythe.c",
                   })),
        15, BEACH_DIR + "bountiful/chest_rewards/c_razor", 0, 25);    
        break;
        
        case 76..99:
        chest_reward = clone_unique(one_of_list(({
                    BEACH_DIR + "bountiful/chest_rewards/dis_choker.c",
                   })),
        15, BEACH_DIR + "bountiful/chest_rewards/c_humidor", 0, 25);    
        break;
    }
        
    chest_reward->move(this_object(), 1);
    
    BOUNTIFUL_CHEST_LOG("bountiful_chest_log",
    "The chest of Damon Skragg spawned a "
    +chest_reward->query_name()+".\n");

    add_prop(CONT_I_CLOSED,1);
    add_prop(CONT_I_LOCK,1);
}


/*
* Function name: init()
* Description  : Enables the commands when a mortal enters.
*/
void
init()
{
    ::init();
    add_action(open_chest,"open");
    add_action(close_chest,"close");
    add_action(unlock_chest,"unlock");
    add_action(lock_chest,"lock");
}



/*
 * Function name: empty_out()
 * Description  : Moves all objects to the environment
 */
int
empty_out(object ob)
{
    if (ob->move(environment(TO)))
        return 0;

    else
        return 1;
}


/*
 * Function name: remove_chest()
 * Description  : Dissoloves the chest leaving behind only items.
 */
int
remove_chest(mixed blah)
{
    tell_room(environment(TO), "The "+short()+
    " rapidly dissolves into nothing.\n",0);

    map(all_inventory(TO), empty_out);
    TO->remove_object();
}



/*
 * Function name: despawn_trigger()
 * Description  : Starts the despawn countdown.
 */
int
despawn_trigger()
{
    set_alarm(600.0, 0.0, "remove_chest");
}



/*
 * Function name: open_chest()
 * Description  : How you open the chest.
 */
int
open_chest(string str)
{
    if((str == "chest") || (str == "wooden chest") || (str == "all"))
    {
        if(query_prop(CONT_I_LOCK) == 1)
        {
            write("You'll need to unlock the chest " +
            "to open it.\n");

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

/*
 * Function name: lock_chest()
 * Description  : How you lock the chest.
 */
int
lock_chest(string str)
{
    if((str == "chest") || (str == "wooden chest"))
    {
        if(query_prop(CONT_I_CLOSED) == 0)
        {
             write("You'll need to close the chest before " +
             "you can lock it.\n");
             return 1;
         }

         if(query_prop(CONT_I_LOCK) == 0)
         {
             if(present("_damon_chest_key",TP))
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

/*
 * Function name: unlock_chest()
 * Description  : How you unlock the chest.
 */
int
unlock_chest(string str)
{
    if((str == "chest") || (str == "wooden chest"))
    {
        if(query_prop(CONT_I_CLOSED) == 0)
        {
            write("The chest is open already.\n");
            return 1;
        }


        if (present("_damon_skragg", environment(this_object())))
        {
            write("The chest is guarded by the captain!\n");
            return 1;
        }

        if(query_prop(CONT_I_LOCK) == 1)
        {
            if(present("_damon_chest_key",TP))
            {
                key=present("_damon_chest_key",TP);

                if (key->query_key() != chest_key_id)
                {
                    write("The key does not match.\n");
                    return 1;
                }

                write("You unlock the chest.\n");
                write("The " + key->short() + " breaks as the " +
                "chest is unlocked.\n");
                key->remove_object();
                say(QCTNAME(TP) + " unlocks the chest.\n");

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

/*
 * Function name: close_chest()
 * Description  : How you close the chest.
 */
int
close_chest(string str)
{
    if((str == "chest") || (str == "wooden chest"))
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


/*
* Function name: long_desc()
* Description  : Alters the long descriptor based on state.
*/
string
long_desc()
{
    if(query_prop_setting(CONT_I_CLOSED) == 1)
    {
        return "A sturdy chest made out of black wood.\n" +
        "The chest is closed.\n";
    }

    else
    {
        return "A sturdy chest made out of black wood.\n" +
        "The chest is open.\n";
    }
}
