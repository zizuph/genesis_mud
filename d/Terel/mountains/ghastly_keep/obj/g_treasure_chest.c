/*
 * /d/Terel/mountains/ghastly_keep/obj/g_treasure_chest.c
 *
 * The treasure chest from the ghastly dragon in Ghastly Keep.
 *
 *  Created by Znagsnuf.
 *
 *
 *  Date:                      What is done:                           By whom:            
 *  ---------------------------------------------------------------------------
 *  20/04-17                   Language tweak complete                  Gorboth  
 *  27/04-17                   Updated because of potion names         Znagsnuf
 *  04/05-17                   Making the steed a bit rarer            Znagsnuf
 *  01/11-17           Fixed a bug where the chest didn't despawn      Znagsnuf
 *  16/03-20                   Fixed despawn bug.                     Cotillion
 *  03/05-21                   Nerfed money/gem reward                Cotillion
 */

inherit "/std/container";
inherit "/std/receptacle.c";

#include "defs.h";
#include <stdproperties.h>
#include <macros.h>
#include <money.h>

#define GEM_DIR    "/d/Genesis/gems/obj/"
#define CHEST_ROOM "/d/Terel/mountains/ghastly_keep/rooms/gkeep33"

int unlock_chest(string str);
int lock_chest(string str);
int remove_chest(mixed blah);
int empty_out(object ob);


string *rgems = ( {"alexandrite","beryl_red","diamond","emerald","ruby",
                  "pearl"} ),
       *mgems = ( {"sapphire","jade","pearl","spinel_blue","aquamarine",
	             "bloodstone"} ),
       *cgems = ( {"moonstone","garnet","carnelian","amber","onyx","topaz"} ),
       *cgems2 =( {"tourmaline_pink","alexandrite","diamond_black","sapphire",
                  "emerald"} );

object key;

/*
 * Function name: create_container()
 * Description  : Constructor. Creates the container.
 */
void
create_container()
{
    set_name("chest");
    add_name("_gkeep_treasure_chest");
    set_short("emerald encrusted chest");
    add_adj("emerald");
    add_adj("encrusted");
    set_long("This is a huge chest, decorated with emeralds.\n");

    add_prop(CONT_I_RIGID,1);
    add_prop(CONT_I_MAX_WEIGHT,250000);
    add_prop(CONT_I_WEIGHT,4000);
    add_prop(CONT_I_MAX_VOLUME,25000);
    add_prop(CONT_I_VOLUME,4000);
    add_prop(OBJ_I_VALUE,0);
    add_prop(CONT_I_LOCK, 0);
    add_prop(CONT_I_CLOSED, 1);
    add_prop(OBJ_M_NO_GET,1);
    add_prop(OBJ_M_NO_STEAL,1);
    set_no_pick();
    set_cf(this_object());

    reset_container();
    seteuid(getuid(TO));
}


/*
 * Function name: reset_container()
 * Description  : Resets and determines what should be inside.
 */
void
reset_container()
{
    object gem, gem2, gem3;

    seteuid(getuid(TO));

    MONEY_MAKE(random(20),  "platinum")->move(TO, 1);
    MONEY_MAKE(random(200), "gold")->move(TO, 1);

    gem = clone_object(GEM_DIR + cgems2[random(sizeof(cgems2))]);
    gem->set_heap_size(random(10) + 3);
    gem->move(TO, 1);

    gem2 = clone_object(GEM_DIR + rgems[random(sizeof(cgems2))]);
    gem2->set_heap_size(random(10) + 2);
    gem2->move(TO, 1);

    gem3 = clone_object(GEM_DIR + mgems[random(sizeof(cgems2))]);
    gem3->set_heap_size(random(10) + 1);
    gem3->move(TO, 1);

    if (random(2))
    {
        clone_object(GKEEP_OBJ + "hatred_brew")->move(TO, 1);
    }
    else
    {
        clone_object(GKEEP_OBJ + "icy_brew")->move(TO, 1);
    }

    if (!random(5))
    {
        clone_object(GKEEP_OBJ + "g_steed_summon")->move(TO, 1);
    }

    add_prop(CONT_I_CLOSED, 1);
    add_prop(CONT_I_LOCK,   1);
}

/*
* Function name: init()
* Description  : Enables the commands when a mortal enters.
*/
void
init()
{
    ::init();
    add_action(unlock_chest,"unlock");
    add_action(lock_chest,  "lock");
}

/*
 * Function name: empty_out()
 * Description  : Moves all objects to the environment
 */
int
empty_out(object ob)
{
    if (ob->move(ENV(TO)))
        return 0;
    else
        return 1;
}

/*
 * Function name: remove_chest()
 * Description  : Dissolves the chest leaving behind only items.
 */
int
remove_chest(mixed blah)
{
    CHEST_ROOM->set_chest(0);
    tell_room(ENV(TO), "The " + short() +
                       " rapidly dissolves into nothing.\n",0);
    map(all_inventory(TO), empty_out);
    TO->remove_object();
}

/*
 * Function name: open_chest()
 * Description  : How you open the chest.
 */
int
open(object item)
{
    if (query_prop(CONT_I_LOCK) == 1)
    {
        write("You'll need to unlock the chest " +
                "to open it.\n");

        return 1;
    }

    if (query_prop(CONT_I_CLOSED) == 1)
    {
        write("You open the chest.\n");
        say(QCTNAME(TP) + " opens the chest.\n");
        add_prop(CONT_I_CLOSED,0);

        set_alarm(30.0, 0.0, &remove_chest());
    }
    else
    {
        write("The chest is already open.\n");
    }

    return 1;
}

/*
 * Function name: lock_chest()
 * Description  : How you lock the chest.
 */
int
lock_chest(string str)
{
    if (!strlen(str))
    {
        notify_fail("Lock what?\n");
        return 0;
    }

    if (parse_command(str, ({}), "[emerald] 'chest' [with] [copper] "
        + "[copper-plated] [key]"))
    {
        if(query_prop(CONT_I_CLOSED) == 0)
        {
             write("You'll need to close the chest before " +
             "you can lock it.\n");
             return 1;
         }

         if(query_prop(CONT_I_LOCK) == 0)
         {
             if(present("_gkeep_chest_key",TP))
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

    if (!strlen(str))
    {
        notify_fail("Unlock what?\n");
        return 0;
    }

    if (parse_command(str, ({}), "[emerald] 'chest' [with] [copper] "
        + "[copper-plated] [key]"))
    {
        if(query_prop(CONT_I_CLOSED) == 0)
        {
            write("The chest is open already.\n");
            return 1;
        }

        if(query_prop(CONT_I_LOCK) == 1)
        {
            if(present("_gkeep_chest_key",TP))
            {
                key = present("_gkeep_chest_key",TP);
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

