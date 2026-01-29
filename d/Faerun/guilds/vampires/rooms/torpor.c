/* /d/Faerun/guilds/vampires/rooms/torpor.c
 *
 * Nerull 2020
 *
 */
inherit "/d/Faerun/guilds/vampires/rooms/std/vampires_std_room";
#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include "../guild.h";


static object *ld_people = ({ });
static int dest_alarm = 0;

/*
 * Function name: create_warlock_room
 * Description  : Constructor, redefine this to configure your room
 */

public void
create_vampires_room()
{
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(TORPOR_ROOM, 1);
    add_prop(CONT_I_LIGHT,-1);
    add_prop(ROOM_I_LIGHT,0);

    set_short("Burrowed somewhere deep in the ground");
    
    set_long("You are burrowed somewhere deep in the ground. To "
    +"escape, you can try to <crawl up>.\n");
    
    reset_faerun_room();
}


int still_ld(object who)
{
    return (who && !interactive(who));
}


/* this function called repeatedly when a vampire ld's
 * while melded.  This function takes care of removing
 * the object when appropriate.
 */
void wait_to_destruct()
{
    ld_people = filter(ld_people, still_ld);
  
    if (!sizeof(ld_people))
    {
        remove_alarm(dest_alarm);
        dest_alarm = 0;
    
        if (!sizeof(all_inventory()))
        {
        remove_object();
        }
    }
}


void leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);
  
  
    /* We want to remove the room if it is empty, but not if
     * someone has linkdied from here.  If we get rid of it in
     * that case, the player will be sent back to his startloc
     * when he revives, and we don't want that.  So, we take
     * precautions so that the room is around as long as there
     * are ld players who might need to use it.
     */
  
    if (!interactive(ob) && IS_SPAWN_MEMBER(ob))
    {
        ld_people += ({ ob });
    }
  
    if (!dest_alarm && !interactive(ob))
    {
        dest_alarm = set_alarm(10.0, 10.0, wait_to_destruct);
        return;
    }
  
    if (!dest_alarm && !sizeof(all_inventory()))
    {
        /* keep the container around for a while in case it's 
         * needed by other functions (enter_env(), for instance)
         */
        set_alarm(2.0, 0.0, remove_object);
    }
}


void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    
    if (interactive(ob))
    {
        object powertoken;
        
        while (powertoken = present("_vampire_powers_unlock_ob", 
        ob))
        {
            powertoken->remove_object();
        }
        
        VAMPIRES_MASTER->add_aging_check(ob->query_real_name());
    }
}


int
do_enter_world(string str)
{
    int diceroll = random(10);
    
    if (str == "up")
    {
        write("\nYou force the last of your willpower and crawl "
        +"yourself back up to the surface!\n\n");

        switch (diceroll)
        {
            case 0:
            this_player()->move_living("M", GRAVEYARDSPOT1, 1);
            tell_room(GRAVEYARDSPOT1, QCTNAME(this_player())
            + " crawls up from the ground!\n", this_player());
            break;
            
            case 1:
            this_player()->move_living("M", GRAVEYARDSPOT2, 1);
            tell_room(GRAVEYARDSPOT2, QCTNAME(this_player())
            + " crawls up from the ground!\n", this_player());
            break;
            
            case 2:
            this_player()->move_living("M", GRAVEYARDSPOT3, 1);
            tell_room(GRAVEYARDSPOT3, QCTNAME(this_player())
            + " crawls up from the ground!\n", this_player());
            break;
            
            case 3:
            this_player()->move_living("M", GRAVEYARDSPOT4, 1);
            tell_room(GRAVEYARDSPOT4, QCTNAME(this_player())
            + " crawls up from the ground!\n", this_player());
            break;
            
            case 4:
            this_player()->move_living("M", GRAVEYARDSPOT5, 1);
            tell_room(GRAVEYARDSPOT5, QCTNAME(this_player())
            + " crawls up from the ground!\n", this_player());
            break;
            
            case 5:
            this_player()->move_living("M", GRAVEYARDSPOT6, 1);
            tell_room(GRAVEYARDSPOT6, QCTNAME(this_player())
            + " crawls up from the ground!\n", this_player());
            break;
            
            case 6:
            this_player()->move_living("M", GRAVEYARDSPOT7, 1);
            tell_room(GRAVEYARDSPOT7, QCTNAME(this_player())
            + " crawls up from the ground!\n", this_player());
            break;
            
            case 7:
            this_player()->move_living("M", GRAVEYARDSPOT8, 1);
            tell_room(GRAVEYARDSPOT8, QCTNAME(this_player())
            + " crawls up from the ground!\n", this_player());
            break;
            
            case 8:
            this_player()->move_living("M", GRAVEYARDSPOT9, 1);
            tell_room(GRAVEYARDSPOT9, QCTNAME(this_player())
            + " crawls up from the ground!\n", this_player());
            break;
            
            case 9:
            this_player()->move_living("M", GRAVEYARDSPOT10, 1);
            tell_room(GRAVEYARDSPOT10, QCTNAME(this_player())
            + " crawls up from the ground!\n", this_player());
            break;
        }
            
        return 1;
    }
    
    return 0;
}


void
reset_faerun_room()
{
    ::reset_faerun_room();
}


void
init()
{
    ::init();

    add_action(do_enter_world, "crawl");
}

