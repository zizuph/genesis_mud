/*
 * /d/Raumdor/common/beach/bountiful/obj/crate.c
 *
 * cargo crate for the ghast that traverses the forest of shadows.
 * Crate may spawn questitem relevant for the spyquest that unlocks 
 * the Bountiful dungeon.
 *
 * - Nerull
 *
 */

inherit "/std/container";
inherit "/std/receptacle.c";
inherit "/lib/unique";

#include "../defs.h";
#include <stdproperties.h>
#include <macros.h>


int open_crate(string str);
int close_crate(string str);
int remove_crate(mixed blah);
int empty_out(object ob);


/*
 * Function name: create_container()
 * Description  : Constructor. Creates the container.
 */
void
create_container()
{

    seteuid(getuid(TO));

        set_name("crate");
        add_name("_ghast_crate");
        set_short("wooden crate");
        set_adj("wooden");
        set_long("@@long_desc");

        add_prop(CONT_I_RIGID,1);
        add_prop(CONT_I_MAX_WEIGHT,250000);
        add_prop(CONT_I_WEIGHT,4000);
        add_prop(CONT_I_MAX_VOLUME,25000);
        add_prop(CONT_I_VOLUME,4000);
        add_prop(OBJ_I_VALUE,0);
        add_prop(CONT_I_CLOSED,1);
        
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
    add_prop(CONT_I_LOCK,0);
    add_prop(CONT_I_CLOSED,0);
    
    object crate_content;
    object crate_content2;

    seteuid(getuid());

    int diceroll = random(100);
    
    switch (diceroll)
    {
        case 0..33:
        crate_content = clone_object(BEACH_DIR + "bountiful/obj/sulphur");
        crate_content2 = clone_object(BEACH_DIR + "bountiful/obj/rusty_nails");               
        break;
        
        case 34..77:
        crate_content = clone_object(BEACH_DIR + "bountiful/obj/obsidian_shard");
        crate_content2 = clone_object(BEACH_DIR + "bountiful/obj/rusty_nails");                       
        break;
        
        case 78..99:
        crate_content = clone_object(BEACH_DIR + "bountiful/obj/mithril_powder"); 
        crate_content2 = clone_object(BEACH_DIR + "bountiful/obj/rusty_nails");                       
        break;
    }
    
    clone_object(BEACH_DIR + "bountiful/obj/int_report")->move(this_object(), 1);
    
    crate_content->move(this_object(), 1);
    crate_content2->move(this_object(), 1);
    
    add_prop(CONT_I_CLOSED,1);
}


/*
* Function name: init()
* Description  : Enables the commands when a mortal enters.
*/
void
init()
{
    ::init();
    add_action(open_crate,"open");
    add_action(close_crate,"close");
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
remove_crate(mixed blah)
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
    set_alarm(600.0, 0.0, "remove_crate");
}


/*
 * Function name: open_chest()
 * Description  : How you open the chest.
 */
int
open_crate(string str)
{
    if((str == "chest") || (str == "wooden chest") || (str == "all"))
    {
        if(query_prop(CONT_I_CLOSED) == 1)
        {
            write("You open the wooden crate.\n");
            
            say(QCTNAME(TP) + " opens the crate.\n");
            
            add_prop(CONT_I_CLOSED,0);

            set_alarm(30.0, 0.0, "remove_crate");
        }
        else
        {
            write("The crate is already open.\n");
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
 * Function name: close_chest()
 * Description  : How you close the chest.
 */
int
close_crate(string str)
{
    if((str == "crate") || (str == "wooden crate"))
    {
        if(query_prop(CONT_I_CLOSED) == 1)
        {
            write("The crate is already " +
            "closed.\n");
        }

        else
        {
            write("You try to close the wooden crate, but the lid is broken.\n");
            
            say(QCTNAME(TP) + " tries to close the wooden crate, but fails.\n");
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
        return "A crate made out of regular wood.\n" +
        "The wooden crate is closed.\n";
    }

    else
    {
        return "A crate made out of regular wood.\n" +
        "The wooden crate is open.\n";
    }
}
