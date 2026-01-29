
/* 	
    This is the pillory room in the town of Gelan. 

    coder(s):   Merlin & Maniac

    history:     11/4/98   pillory object integrated        Maniac
                  8/6/96   WIZ_CHECK used                   Maniac
                13/11/95  pillory code improved             Maniac
                 3/11/95  Actual pillory code added         Maniac
                  7.9.94     description added              Maniac
                20. 2.93    path system                     Merlin
                17. 1.93    new guard system                Merlin
                 9. 1.93    townrooms.h -> room.h           Merlin
                 6.11.92    installed help system           Merlin
                 3.11.92    created                         Merlin

    purpose:    humiliate criminals here
    exits:      all to square

    objects:    none
    npcs:       none

    quests:     none
    special:    none

    bug:        none known
*/


#pragma save_binary

#include "defs.h"
#include "room.h"
#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include <std.h>
#include <time.h>
#include GUARD_INCLUDE

inherit GELAN_BASE_ROOM;

#define MIN_SERVED_TIME_PER_LOGIN 600
#define PILLORY_SAVE "/d/Calia/gelan/texts/pillory_save"

mapping prisoners; 
static mapping prisoner_alarm_ids; 
static mapping time_served_this_login; 
static object *locked_in_pillory;

public void
create_gelan_room()
{
    /* descriptions */

    set_short("Pillory");
    set_long(VBFC_ME("pillory_long"));

	/* properties */

    add_prop(ROOM_M_NO_TELEPORT, 1);
    add_prop(ROOM_I_INSIDE, 0);		/* this room is outside */
    add_prop(ROOM_M_NO_ATTACK, "This is a place to pelt prisoners with " +
                   "rotten fruit and vegetables, not a place to fight.\n");
    add_prop(ROOM_M_NO_MAGIC_ATTACK, "This is a place to pelt prisoners with "+
                   "rotten fruit and vegetables, not a place to fight.\n");
    add_prop(ROOM_M_NO_MAGIC, 1);

    add_prop(OBJ_S_WIZINFO, 
        "A player who has cheated may get " +
        "`sentenced' to x minutes in the pillory. " +
        "The punisher goes to the pillory and types : `lock <player> " +
        "<x>'. The captive is " +
        "disabled from doing anything but speaking and quitting, which " +
        "means that the only other way to leave is going linkdead. " +
        "A temporary start location " +
        "is used to make sure the player begins at the pillory next login. " +
        "Note: A player may be <unlock>ed from the pillory by a wizard " +
        "in the case of emergencies or appeals, but this " +
        "will completely terminate the player's sentence, it doesn't " +
        "just suspend it. The prisoner will be automatically released " +
        "when the sentence has been completed. Players may " +
        "purchase rotten food from the special `pillory store' next door. " +
        "One may check on the time left for all prisoners " +
        "by typing <timeleft> here.\n");

    /* exits */
    add_exit(GELAN_ROOMS + "square_northend_center_e","north",0);
    add_exit(GELAN_ROOMS + "square_central_e","south",0);
    add_exit(GELAN_ROOMS + "pillory_w","west",0);
    add_exit(GELAN_ROOMS + "square_ne","east",0);
    add_exit(GELAN_ROOMS + "square_northend_center_w","northwest",0);
    add_exit(GELAN_ROOMS + "square_northend_e","northeast",0);
    add_exit(GELAN_ROOMS + "square_central_w","southwest",0);
    add_exit(GELAN_ROOMS + "square_mide","southeast",0);

    /* items in the room */

    add_item("pillory", VBFC_ME("pillory_desc"));
    add_item(({"buildings", "building"}), DESC("buildings"));
    add_item(({"square", "floor","ground","bottom","road"}), DESC("floor"));
    add_item("fountain", DESC("fountain"));

    prisoners = ([ ]); 
    prisoner_alarm_ids = ([ ]); 
    time_served_this_login = ([ ]); 
    locked_in_pillory = ({ }); 

    restore_object(PILLORY_SAVE); 
} /* create_room */




private string
player_desc(object ob, object tp)
{
    if (ob == tp)
        return "you";
    else
        return ob->query_art_name(tp); 
}


/* 
   Don't use COMPOSITE_LIVE because the people in the pillory
   have set_no_show_composite() 
 */ 
private string
players_in_pillory()
{
    int i, k; 
    object tp; 
    string ldesc; 

    tp = this_player(); 

    ldesc = player_desc(locked_in_pillory[0], tp); 

    k = sizeof(locked_in_pillory) - 1; 

    if (k > 1) {
        for (i = 1; i < k; i++) 
            ldesc = (ldesc + ", " + 
                     player_desc(locked_in_pillory[i], tp)); 
    } 

    if (k > 0)
        ldesc = (ldesc + " and " + 
                 player_desc(locked_in_pillory[k], tp)); 

    return ldesc; 
}


varargs string
pillory_desc(int prisoners_only)
{
    string str;

    if (!prisoners_only) 
        str = ("The pillory is a huge, it looks like it can hold a lot of " +
               "people if necessary. Prisoners have their hands, feet and " +
               "heads stuck between solid oaken boards. They also have a " +
               "healthy complexion. (Tomatoes are good for your skin, " +
               "aren't they?) ");
    else
        str = ""; 

    locked_in_pillory = filter(locked_in_pillory, objectp); 
    if (!sizeof(locked_in_pillory))
        str += "There are currently no prisoners in the pillory.\n";
    else 
        str += ("The following prisoners are currently locked in the " +
                "pillory: " + players_in_pillory() + ".\n");

    return str;
}



/* Room long description */
string
pillory_long()
{
      object tp = this_player();

      if (!objectp(tp) || 
           (member_array(tp, locked_in_pillory) == -1))
          return ("You are standing in front of the pillory of Gelan. "
               + "From here you can quite easily pelt any poor soul who is " 
               + "locked in its evil clutches with whatever rotten vegetables " 
               + "and other delights that you happen to be carrying " 
               + "(such things are available at the pillory store to " 
               + "your west). "
               + "A fair way to your south is the fountain of Gelan. "
               + "You also see many buildings all around the town square. "
               + pillory_desc(1));
      else
          return ("You are locked in the pillory in Gelan, helpless, and " 
               + "vulnerable to the taunts and squashed tomatoes of " 
               + "any law abiding citizen who happens by. Serves you " 
               + "right, too! After all, if you're locked in here it's " 
               + "because you deserve to be! "  
               + "A fair way to your south is the fountain of Gelan. "
               + "You also see many buildings all around the town square. " 
               + pillory_desc(1));
}


private void
update_pillory_times()
{
    int i, x;
    string *ind;
    mixed a;

    ind = m_indexes(prisoner_alarm_ids); 
    for (i = 0; i < sizeof(ind); i++) {
        if (a = get_alarm(prisoner_alarm_ids[ind[i]])) {
            x = time_served_this_login[ind[i]]; 
            time_served_this_login += 
                    ([ ind[i] : x + prisoners[ind[i]] - ftoi(a[2]) ]); 
            prisoners += ([ ind[i] : ftoi(a[2]) ]); 
        }
    }
}



private void
release(object p, int unlocked)
{
    string pn = p->query_real_name(); 

    locked_in_pillory -= ({ p }); 
    p->unset_no_show_composite(); 
    p->remove_prop(LIVE_I_STUNNED); 
    p->remove_prop(LIVE_M_NO_ACCEPT_GIVE); 

    tell_object(p, "You are released from the pillory by two town guards.\n"); 
    tell_room(this_object(), QCTNAME(p) + " is released from the pillory " +
                             "by two town guards.\n", p); 

    if (unlocked) {
        prisoners = m_delete(prisoners, pn); 
        p->set_temp_start_location(0);
        log_file("pillory", capitalize(pn) + " released at " +
                 ctime(time()) + ".\n"); 
    }

    remove_alarm(prisoner_alarm_ids[pn]); 
    prisoner_alarm_ids = m_delete(prisoner_alarm_ids, pn);  
    time_served_this_login = m_delete(time_served_this_login, pn); 
    update_pillory_times(); 
    save_object(PILLORY_SAVE); 
}



private void
lock_in(object p, int minutes)
{
    int dur; 
    string pn = p->query_real_name(); 

    if (!minutes) {
        dur = prisoners[pn]; 
        if (!dur)
            return;
    }
    else { 
        dur = minutes * 60; 
        prisoners += ([ pn : dur ]); 
    } 

    prisoner_alarm_ids += ([ pn : set_alarm(itof(dur), 0.0, 
                                            &release(p, 1)) ]); 

    tell_object(p, "You are locked in the pillory by two town guards.\n"); 
    tell_room(this_object(), QCTNAME(p) + " is locked in the pillory " +
                             "by two town guards.\n", p); 
    locked_in_pillory += ({ p }); 
    p->set_no_show_composite(1); 
    p->set_temp_start_location(file_name(this_object())); 
    p->add_prop(LIVE_I_STUNNED, 1); 
    p->add_prop(LIVE_M_NO_ACCEPT_GIVE, " is locked in the pillory and " +
                "can therefore not accept gifts.\n"); 
    update_pillory_times(); 
    save_object(PILLORY_SAVE); 
}


/* 
   Action for locking someone in the pillory. 
   Currently only stewards and above may do this.
 */
int
lock(string str)
{
    object tp = this_player();
    object prisoner;
    string pn;
    int t, x;

    t = WIZ_CHECK;

    if ((t != WIZ_KEEPER) && (t != WIZ_ARCH) && (t != WIZ_LORD) &&
        (t != WIZ_STEWARD) && 
        (SECURITY->query_wiz_dom(tp->query_real_name()) != getuid()))
    {
        notify_fail("You don't have the authority to order the locking " +
                    "of someone in the pillory.\n");
        return 0;
    }


    if (!stringp(str) || sscanf(str, "%s %d", pn, x) != 2) { 
        notify_fail("Usage: lock <player> <x> where x is the number " +
                    "of minutes to be locked in the pillory.\n");
        return 0;
    }

    prisoner = find_player(pn = lower_case(pn));
    if (!objectp(prisoner))  {
        notify_fail("Can't find a player by the name of " + pn + 
                    " logged in.\n");
        return 0;
    }

    if (prisoner->query_wiz_level()) {
        notify_fail("Only mortals may be locked in the pillory!\n");
        return 0;
    }
 
    if (prisoner->query_linkdead()) {
        notify_fail("Linkdead players may not be locked in the pillory.\n");
        return 0;
    }
   
    if (prisoner->query_ghost()) {
        notify_fail("Hmm, that player seems to be a ghost, no can do!\n");
        return 0;
    }

    if (member_array(prisoner, locked_in_pillory) > -1) {
        notify_fail("That player is already locked in the pillory!\n");
        return 0;
    }

    if (x < 1) {
        notify_fail("That period of time is too short!\n");
        return 0;
    }

    if (x > 5000) {
        notify_fail("That period of time is too long isn't it?\n");
        return 0;
    }

    if (!present(prisoner, this_object())) {
        prisoner->move_living("X", this_object());
        if (!present(prisoner, this_object())) {
            notify_fail("Hmm, couldn't move the player here for some " +
                        "reason.\n");
            return 0;
        }
    }

    lock_in(prisoner, x); 

    tell_object(tp, "Ok.\n");
    log_file("pillory", capitalize(tp->query_real_name()) + " locked " + 
             capitalize(pn) + " in the pillory, " +
             "sentence was " + x + " minutes, started at " + ctime(time()) +  
             ".\n"); 
    return 1;
}



/* 
   Action for unlocking someone from the pillory. 
   Any wizard is allowed to do this, to allow dealing with bugs,
   but it is logged to prevent someone cheating.
 */
int
unlock(string str)
{
    object tp = this_player();
    object prisoner;

    if (!tp->query_wiz_level()) {
       notify_fail("You don't have the authority to unlock someone " +
                   "from the pillory.\n");
       return 0;
    }

    if (!stringp(str)) { 
        notify_fail("Usage: unlock <player>.\n");
        return 0;
    }

    prisoner = find_player(str);
    if (!objectp(prisoner))  {
        notify_fail("Can't find a player by the name of " + str  + 
                    " logged in.\n");
        return 0;
    }

    if (member_array(prisoner, locked_in_pillory) == -1) {
        notify_fail("That player is not currently locked in the pillory!\n");
        return 0;
    }

    release(prisoner, 1); 
    tell_object(tp, "Ok.\n");

    log_file("pillory", capitalize(tp->query_real_name()) + " unlocked " + 
           capitalize(prisoner->query_real_name()) + " from the pillory.\n");

    return 1;
}


/* Lock in prisoners returning from linkdeath. */
void
enter_inv(object ob, object old)
{
    ::enter_inv(ob, old);
    
    if (!living(ob))
        return;

    if (member_array(ob->query_real_name(), m_indexes(prisoners)) > -1)
        lock_in(ob, 0); 
}


/* Temporarily released prisoners going linkdead */ 
void
leave_inv(object ob, object dest)
{
    ::leave_inv(ob, dest);

    if (!living(ob))
        return;

    if (member_array(ob, locked_in_pillory) > -1) {
        if (objectp(dest) && (file_name(dest) != OWN_STATUE)) { 
            log_file("pillory", capitalize(ob->query_real_name()) + 
                     " moves to " + file_name(dest) + 
                     " while locked in at " + ctime(time()) + ".\n");
            if (this_interactive()->query_wiz_level()) 
                log_file("pillory", 
                         capitalize(this_interactive()->query_real_name()) +
                         " was the wizard causing the move.\n"); 
        }
        release(ob, 0); 
    }
}



/* Reports time left in pillory for prisoners. */
int
timeleft()
{
    object tp, pr;  
    int i, t;
    string str, *ind, stat;

    tp = this_player();

    str = ("Here are the details of the time left for prisoners " +
           "in the pillory:\n");

    ind = m_indexes(prisoners); 

    if (!sizeof(ind)) {
       write(str + "There are no prisoners registered.\n"); 
       return 1;
    }

    update_pillory_times(); 
    for (i = 0; i < sizeof(ind); i++) {
        if (member_array(pr = find_player(ind[i]), locked_in_pillory) > -1)
            stat = "(present)";
        else if (pr->query_linkdead())
            stat = "(linkdead)"; 
        else
            stat = "(absent)"; 

        str += sprintf("%16s %21s %12s\n", capitalize(ind[i]), 
                      TIME2STR(prisoners[ind[i]], 4), stat); 
    }
    write(str); 
    return 1;
}



int
paralyze(string str)
{
    string v;
    object tp = this_player(); 
    int time_to_quit;

    if (member_array(tp, locked_in_pillory) == -1)
        return 0;

    v = query_verb(); 
    if ((v == "say") || (v == "look") || (v[0] == ''')) 
        return 0;
 
    if (v == "quit") {
        if (ARMAGEDDON->shutdown_active())
            return 0;

        update_pillory_times(); 
        time_to_quit = min(prisoners[tp->query_real_name()], 
                           MIN_SERVED_TIME_PER_LOGIN - 
                           time_served_this_login[tp->query_real_name()]); 

        if (time_to_quit > 0) { 
            write("You have to stay in the pillory for " + 
                  TIME2STR(time_to_quit, 4) + 
                  " more before you can quit.\n"); 
            return 1;
        }
        return 0;
    }

    write("You may not do that while you are in the pillory.\n"); 
    return 1; 
}


public void
remove_object()
{
    update_pillory_times(); 
    save_object(PILLORY_SAVE); 
    ::remove_object(); 
}



void
init()
{
    ::init();
    add_action(paralyze, "", 1); 
    add_action(lock, "lock");
    add_action(unlock, "unlock");
    add_action(timeleft, "timeleft");
}

