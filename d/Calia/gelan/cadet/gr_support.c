
/* 

    Support for graduation rings. There used to be only 
    one form of ring, but from April 2001 there are two, 
    so this covers the functionality common to both. 

    Coded by Maniac@Genesis, April 2001 

    History: 
    7/7/01     ensure_graduate_shadow_active function added   Maniac 
    3/7/01     check for cadet before adding shadow           Maniac 
    4/01       Generalised from graduation ring               Maniac 
 */ 

inherit "/lib/wearable_item"; 
inherit "/std/object"; 

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include <std.h>
#include "cadet.h"

string graduation_ring_lettering(); 
private void init_suspension(int duration); 
private void lift_suspension(); 

int losing_it, suspension_count, pardon_time; 
object gr_shadow; 


int
do_lose(string str)
{
    object ob, tp;

    notify_fail("Lose what?\n");
    if (!stringp(str) || !strlen(str) ||
        !parse_command(str, environment(), "[the] %o", ob))
        return 0;

    if (ob != this_object())
        return 0;

    tp = this_player(); 

    if (losing_it) 
    {
        write("You lose the " + this_object()->short() + ".\n");
        say(QCTNAME(this_player()) + " loses " +
            tp->query_possessive() + " " +
            this_object()->short() + ".\n"); 
        seteuid(getuid()); 
        GC_TRAINROOM->unregister_graduate(tp); 
        if (!tp->query_wiz_level()) 
            log_file("cadet", tp->query_real_name() + " loses ring.\n"); 
        if (environment(tp)->gc_query_private_room()) 
            tp->move_living("for the training room", GC_TRAINROOM); 
        set_alarm(0.0, 0.0, &remove_object());
        return 1;
    }
    write("Type the command again to confirm you want to lose " +
          "the " + this_object()->short() + ".\n");
    losing_it = 1;
    return 1;
}


/* 
 *  Function:    set_suspension_count
 *  Description: patch the number of times the player has been suspended. 
 *  Returns:     1 if the previous object had the rights, 0 otherwise. 
 */ 
int
set_suspension_count(int sc) {
    if (SECURITY->valid_write(file_name(this_object()), 
                              previous_object(), 
                              "write_file")) 
    { 
        suspension_count = sc; 
        return 1; 
    } 
    return 0; 
}


/* 
 *  Function:    set_pardon_time
 *  Description: patch the pardon time, the time for the lifting of 
 *               a player's suspension.  
 *  Returns:     1 if the previous object had the rights, 0 otherwise. 
 */ 
int
set_pardon_time(int t) {
    int tm, old_pt; 

    if (t > 0 && 
        SECURITY->valid_write(file_name(this_object()), 
                              previous_object(), 
                              "write_file")) 
    { 
        old_pt = pardon_time; 
        pardon_time = t;
        tm = time(); 
        if (pardon_time > tm) 
            init_suspension(pardon_time - tm);
        else if (old_pt > tm)
            lift_suspension(); 
        return 1; 
    } 
    return 0; 
}


/*
 * Suspend a graduate. The value "level" is added to the suspension 
 * count of the graduate. Duration of the suspension is 6 weeks on 
 * first offense, 12 weeks on the second, 18 weeks on the third 
 * etc. Committing a suspending offense while already suspended results 
 * in the addition of the new suspension to the existing one. 
 */ 
void
suspend(string reason)
{
    int t;
    object e, board; 
    string rn; 

    if (!SECURITY->valid_write(file_name(this_object()), 
                               previous_object(), 
                               "write_file"))
        return; 

    t = time(); 
    e = environment(this_object()); 
    rn = e->query_real_name(); 

    seteuid(getuid()); 
    suspension_count++; 
    if (suspension_count > 3) 
    { 
        tell_object(e, "\nDue to repeated offenses, you have " +
             "lost your graduation ring permanently.\n"); 
        log_file("cadet", ctime(t) + ": " + rn +
                 " loses graduation ring for " + reason + ".\n"); 
        if (objectp(board = present("board", 
                GC_BOARDROOM->get_this_object())))
            board->create_note(capitalize(rn) + "'s graduate status", 
                   "Xorfin", break_string(capitalize(rn) +
                   " lost " + e->query_possessive() +
                   " graduation ring for " + reason + 
                   ", the latest in a line of many offenses.", 70) + 
                   "\n\nXorfin\n"); 
        set_alarm(0.0, 0.0, &remove_object()); 
    } 
    else 
    { 
        if (pardon_time > t) 
            pardon_time += (3628800 * suspension_count); 
        else
            pardon_time = t + (3628800 * suspension_count); 

        tell_object(e, "\nYour graduate status is suspended until " + 
                    ctime(pardon_time) + "!\n"); 
        if (objectp(board = present("board", 
                GC_BOARDROOM->get_this_object())))
            board->create_note(capitalize(rn) + "'s graduate status", 
                   "Xorfin", break_string(capitalize(rn) + " had " + 
                   e->query_possessive() + " graduate status suspended " +
                   "until " + ctime(pardon_time) + " for " + reason + 
                   ".", 70) + "\n\nXorfin\n");     

        init_suspension(pardon_time - t); 
    } 

    GC_TRAINROOM->unregister_graduate(e); 

    if (environment(e)->gc_query_private_room())
        e->move_living("to the cadet training room", GC_TRAINROOM);

    if (e->query_default_start_location() == GC_STARTROOM)
        e->set_default_start_location(e->query_def_start()); 
}


string
graduation_ring_lettering()
{
    string rn;

    rn = environment(this_object())->query_real_name(); 

    return (

    sprintf("%|80s", 
            "Congratulations " + capitalize(rn) + ".") + 
            "\n\n" + 
    sprintf("%|80s",  
            "You have graduated from the Cadets of Gelan.") + 
            "\n\n" +
    sprintf("%|80s","May the golden star bring you strength on your travels.")+
            "\n\n" + 
    sprintf("%|80s", 
            "And may your cast iron stomach serve you well!") + 
            "\n\n" + 
    sprintf("%|80s", 
            "See \"help graduate\" for more information.") + 
            "\n"); 
}


private void 
add_soul(object player) 
{
    player->add_cmdsoul(GC_GRADUATE_SOUL); 
    player->update_hooks(); 
    GC_TRAINROOM->register_graduate(player); 
}


/* 
 * Function:     ensure_graduate_shadow_active 
 * Description:  Ensures the graduate shadow is active for the 
 *               owner graduate. This is called from the cadet 
 *               training room, as well as from this object in 
 *               enter_env. 
 */ 
void 
ensure_graduate_shadow_active(object graduate) 
{ 
    if (!objectp(gr_shadow)) 
    { 
        seteuid(getuid(this_object())); 
        (gr_shadow = clone_object(GC_GRADUATE_SHADOW))->shadow_me(graduate); 
    } 
} 


/* 
 * Function name: enter_env 
 * Description  : This function is called each time this object enters a 
 *                new environment. If you mask it, be sure that you 
 *                _always_ call the ::enter_env(dest, old) function. 
 *                In this case it adds the graduate shadow to the player 
 *                if s/he is not a wizard or a cadet. Also adds graduate 
 *                identifying property and graduate soul. 
 * Arguments    : object dest - the destination we are entering. 
 *                object old  - the location we came from. This can be 0. 
 */ 
void 
enter_env(object dest, object old) 
{ 
    ::enter_env(dest, old); 
    if (living(dest) && !dest->query_wiz_level()) 
    { 
        if (!IS_GELAN_CADET(dest)) 
        { 
            ensure_graduate_shadow_active(dest); 
        } 

        if (pardon_time > time()) 
            return; 

        dest->add_prop(GC_RING_ID, 1); 
        set_alarm(0.0, 0.0, &add_soul(dest)); 
    } 
} 


/* 
 * Function name: leave_env 
 * Description  : This function is called each time this object leaves an 
 *                old environment. If you mask it, be sure that you 
 *                _always_ call the ::leave_env(dest, old) function. 
 *                In this case it calls wearable_item_leave_env and 
 *                removes the graduate identifier. 
 * Arguments    : object old  - the location we are leaving. 
 *                object dest - the destination we are going to. Can be 0. 
 */ 
void 
leave_env(object old, object dest) 
{ 
    ::leave_env(old, dest); 
    wearable_item_leave_env(old, dest); 
    if (living(old)) 
        old->remove_prop(GC_RING_ID); 
} 


/* 
 * Function:      listable_graduate 
 * Description:   Returns 1 if the player is a listable graduate, 
 *                0 otherwise. 
 */ 
int 
listable_graduate(object pl) 
{ 
    return (pl->query_prop(GC_RING_ID) && 
            pl->query_invis() != 100); 
} 


/* 
 * Function:     cglist 
 * Description:  Action function to list graduates in the game. 
 * 
 */ 
int 
cglist(string str) 
{ 
    this_player()->more("The following Graduates are currently playing:\n" + 
        COMPOSITE_WORDS(sort_array(map(filter(users(), listable_graduate), 
                        capitalize @ &->query_real_name()))) + "\n"); 
    return 1; 
} 


/* 
 * Function:     lift_suspension 
 * Description:  Lift the suspension of graduate status from the owner. 
 * 
 */ 
private void 
lift_suspension() 
{ 
    object e = environment(this_object()); 

    this_object()->unset_no_show(); 
    this_object()->unset_no_show_composite(); 

    if (objectp(e)) 
    { 
        update_actions(); 
        tell_object(e, 
            "The suspension of your graduate status has been lifted.\n"); 
        e->add_prop(GC_RING_ID, 1); 
    } 
} 


/* 
 * Function:     init_suspension
 * Description:  Suspend the player for the given duration.
 */ 
private void
init_suspension(int duration)
{
    object e = environment(this_object()); 

    this_object()->set_no_show(); 
    if (duration < 86400)
        set_alarm(itof(duration), 0.0, lift_suspension);

    if (objectp(e)) 
    { 
        e->remove_prop(GC_RING_ID); 
        update_actions(); 
    } 
}


/* 
 * Function:     init_arg 
 * Description:  Called on autoloading to initialise from the 
 *               autoload string. 
 */ 
void
init_arg(string arg)
{
    int t = time(); 

    if (stringp(arg)) 
        sscanf(arg, "#sc#%d#pt#%d", suspension_count, pardon_time); 

    if (pardon_time && ((t = pardon_time - t) >= 0)) 
        init_suspension(t); 
}


void
init()
{
    ::init(); 
    add_action(do_lose, "lose"); 

    if (pardon_time <= time()) 
        add_action(cglist, "cglist"); 
}


string
query_auto_load()
{
    return MASTER + ":#sc#" + suspension_count + "#pt#" + pardon_time; 
}


string
query_recover()
{
    return 0;
}


void
remove_object()
{
    environment(this_object())->gc_remove_graduate_shadow(); 
    ::remove_object(); 
}
