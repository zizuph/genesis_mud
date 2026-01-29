/* meld_cont.c created by Shiva@Genesis.
 * this room is meant to hold an earthmelded vampire.
 */

inherit "/std/room";

#include "../guild.h"
#include <stdproperties.h>
#include <composite.h>
#include <macros.h>

static object who_melded, *ld_people = ({ });
static int dest_alarm = 0;

void create_room()
{
    set_long("You can't see anything!\nYou may 'rise' to get back "
    +"to the surface.\n");
    set_short("Deep within the earth");
    set_no_show();
  
    add_prop(OBJ_I_NO_GET, 1);
    add_prop(ROOM_I_NO_CLEANUP, 1);
    add_prop(ROOM_M_NO_TELEPORT, 1);
    add_prop(ROOM_M_NO_SCRY, "A dark room.");
    //add_prop(OBJ_I_LIGHT,-1);
    add_prop(ROOM_I_LIGHT,0);
    
    add_prop(ROOM_I_VAMP_MELD, 1);
    
    remove_prop(CONT_I_VOLUME);
    remove_prop(CONT_I_MAX_VOLUME);
    remove_prop(CONT_I_WEIGHT);
    remove_prop(CONT_I_MAX_WEIGHT);
    remove_prop(OBJ_I_VALUE);
  
    add_prop(ROOM_I_INSIDE,1);
    setuid();
    seteuid(getuid());
}


void move_def_start(object ob)
{
    string start;

    if (!strlen(start = ob->query_default_start_location()) &&
        !strlen(start = ob->query_def_start()))
    {
        return;
    }
    
    ob->move_living("M", start, 1);
    
    tell_room(environment(ob), QCTNAME(ob)
           + " rises from the ground!\n", ob);
}


int catch_all(string str)
{
    string cmd = query_verb();
    mixed where_to;
    
    if (cmd == "rise" && !strlen(str))
    {
        if (environment(this_object()))
        {
            if (!this_player()->move_living("M",environment(this_object())))
            {
                tell_room(environment(this_player()), QCTNAME(this_player())
                + " rises from the ground!\n", this_player());
                
                return 1;
            }
        }
        else
        {
            move_def_start(this_player());
            return 1;
        }
    }      
  
    if (this_player()->query_wiz_level())
    {
        return 0;
    }
  
    switch (cmd)
    {
        case "quit":
        case "vmorning":
        case "stats":
        case "commune":
        case "reply":
        case "bug":
        case "sysbug":
        case "praise":
        case "idea":
        case "typo":
        case "help":
        case "vhelp":
        case "who":
        case "vsense":
        case "vprogression":
        case "vagecheck":
        case "vsire":
        case "vtitlelist":
        case "vtitle":
        case "stop":
        case "vampimmortailty":
        case "vampthirst":
        case "vampsun":
        case "vitals":
        case "v":
        case "health":
        case "vtargets":
        case "vnation":
        case "h":   
        case "videa":       
        return 0;
        default:
        write("That is impossible while you are earthmelded.\n");
        return 1;
    }
}

void init()
{
    ::init();
  
    if (present(this_player()))
    {
        add_action(catch_all, "", 1);
    }
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
update_internal(int l, int w, int v)
{
    /* This container shouldn't distribute light */
    ::update_internal(0, w, v);
}


int prevent_enter(object ob)
{
    return !interactive(ob);
}
     
     
void remove_object()
{
    map(deep_inventory(), move_def_start);
    ::remove_object();
}    
