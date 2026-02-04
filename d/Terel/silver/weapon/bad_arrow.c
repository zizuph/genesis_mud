/* File         : /d/Terel/silver_new/weapon/bad_arrow.c
* Creator      : Udana
* Date         : March 2006
* Purpose      : Burr Arrow
* Related Files:
* Comments     :
* Modifications: Modified by Pasqua
*                Cleaned up and changed damage for balance, Petros, 8/09
*                Capped the damage output, and removed the object when
*                a player dies, Arman, 08/20
*/

inherit "/std/object";
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>
#include <cmdparse.h>
#include "../include/defs.h"
#include <filter_funs.h>
#include "/d/Terel/include/Terel.h"
#define VIC E(TO)
#define ORIGINAL_ARROW WEAPON + "burr_arrow"
#define MOVEMENT_HP_LOSS    20
#define BREAKAGE_HP_LOSS    100
#define HP_LOSS_MAX         50
#define WOUND_INTERVAL      60

inherit "/std/object";

// Global Variables
int         hid; // hit location id
string      responsible_living; // person who shot the arrow
//alarm for occasional damage
int         alarm_id;
//is the arrow broken
int         arrow_broken = 0;
//for syntax help purpouse
int         attempts = 0;
// wound object
object wound_obj;

// Prototypes
public string   hid_name(int hid);
// sanity check
public int      san_check();
//returns hid name (already modified by hid_name f-ction)
public string   query_hid_name();
//1 if it is a bad arrow - 0 otherwise
public int      is_bad_arrow();
/* next two functions are handling player pulling out or breaking bad arrow. */
public int      pull_arrow(string a);
/* called occasionally - damages a player from bleeding. */
public void     do_bad_stuff();
/* this function is called by originall arrow when it hits. before that method
is called the arrow does nothing. */
public void     land(object archer, int hitlocid, int reloading);
// that is supposed to happen.
public void     player_kill();
/* sometime an arrow pulled from your chest is still intact. Then reward is
called and players gets it */
public void     reward_arrow();


void 
create_object()
{
    add_name("arrow");
    add_adj("bad");
    add_adj("burr-headed");
    set_short("burr-headed arrow");
    set_long("@@my_long");
    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VOLUME, 100);
    set_no_show_composite(1);
}

string 
my_long()
{
    if (arrow_broken)
    {
        return QCTNAME(VIC) + " broke an arrow in " + VIC->query_possessive() 
            + " " + query_hid_name() + ". It's gonna be much harder to pull "
            + "it out now, but at least it doesn't hurt as much to move "
            + "around now.\n";
    }
    
    return "An arrow is piercing " 
        + (TP == VIC ? "your" : VIC->query_possessive()) + " " 
        + query_hid_name() + ". It looks pretty bad. One could try to "
        + "pull it out, or simply break it.\n";
}

int san_check()
{
    if(!living(VIC))
    {
        SEND("SANITY FAILED");
        return 0;
    }
    return 1;
}

public void init()
{
    ::init();
    add_action("pull_arrow", "pull");
    add_action("break_arrow", "break");
}

string hid_name(int hitloc)
{
    object player;

    if (!hitloc)
    {
        return "chest";
    }

    player = environment(this_object());
    mixed hitloc_results =
        player->query_combat_object()->query_hitloc(hitloc);

    if (pointerp(hitloc_results))
    {
        switch (hitloc_results[2])
        {
        case "body":
            return "chest";
        case "legs":
            return "leg";
        default:
            return hitloc_results[2];
        }
    }

    return "chest";
}

string query_hid_name()
{
    return hid_name(hid);
}

int querry_arrow_broken()
{
    return arrow_broken;
}

int is_bad_arrow()
{
    return 1;
}

public int 
pull_arrow(string a)
{
    if(!san_check())
    {
        remove_alarm(alarm_id);
        remove_object();
    }
    object arrow = PARSE_COMMAND_ONE(a, 0, "[the] %i [from] [" 
                                   + hid_name(hid) + "]");
    if (arrow != this_object())
    {
        switch(attempts)
        {
        case 0:
            attempts++;
            notify_fail("Pull what from what?\n");
            break;
        case 1:
            attempts++;
            notify_fail("You've got an arrow pierced through your " 
                + hid_name(hid) + ". If you <pull> it out it is likely " 
                + "to cause a bleeding wound, but if you <break> it "
                + "first it will stop the bleeding.\n");
            break;
        default:
            notify_fail("syntax: <pull arrow from " + hid_name(hid) + ">\n");
            break;
        }
        return 0;
    }
    
    remove_alarm(alarm_id);
    // Pulling out an arrow causes blood loss. We represent this
    // by creating a wounding object.
    setuid();
    seteuid(getuid());

    int wnd_dmg = min(HP_LOSS_MAX, (VIC->query_max_hp() / 8));
    wound_obj = clone_object("/d/Genesis/specials/std/wounding_obj_base");
    wound_obj->set_wounding_hitloc(hid);
    wound_obj->set_wounding_damage(wnd_dmg);
    wound_obj->set_wounding_interval(WOUND_INTERVAL);
    wound_obj->set_wounding_time(300); // 5 minutes, so 5 wound rounds
    wound_obj->move(VIC, 1);
    wound_obj->start();
    VIC->catch_msg("With great effort, you pull the arrow from "
        + "your " + hid_name(hid) + ", leaving the wound wide "
        + "open.\n");
    tell_room(E(VIC), QCTNAME(VIC) + " pulls out an arrow from "
        + VIC->query_possessive() + " " + hid_name(hid) + ".\n", 
          ({VIC}), VIC);
    VIC->command("scream");
    reward_arrow();
    if (VIC->query_hp() <= 0)
    {
        player_kill();
    }
    else
    {
        remove_object();
    }
    return 1;
}

public int break_arrow(string a)
{
    if(!san_check())
    {
        remove_alarm(alarm_id);
        remove_object();
    }
    object arrow = PARSE_COMMAND_ONE(a, 0, "[the] %i [in] [" 
                                   + hid_name(hid) + "]");
    if (arrow != this_object())
    {
        switch(attempts)
        {
        case 0:
            attempts++;
            notify_fail("Break what in what?\n");
            break;
        case 1:
            attempts++;
            notify_fail("You've got an arrow pierced through your " 
                + hid_name(hid) + ". If you <pull> it out it is likely " 
                + "to cause a bleeding wound, but if you <break> it "
                + "first it will stop the bleeding.\n");
            break;
        default:
            notify_fail("syntax: <break arrow in " + hid_name(hid) + ">\n");
            break;
        }
        return 0;
    }
    if(arrow_broken)
    {
        notify_fail("That arrow is already broken.\n");
        return 0;
    }
    remove_alarm(alarm_id);
    VIC->heal_hp(-BREAKAGE_HP_LOSS);
    arrow_broken = 1;
    VIC->catch_msg("You break an arrow piercing your " + hid_name(hid) 
        + ". It won't hurt you with every move now.\n");
    tell_room(E(VIC), QCTNAME(VIC) + " breaks an arrow in "
        + VIC->query_possessive() + " " + hid_name(hid) + ".\n", ({VIC}), VIC);
    VIC->command("roar wild");
    if (VIC->query_hp() <= 0)
    {
        player_kill();
    }
    return 1;
}


void do_bad_stuff()
{
    if (!san_check())
    {
        remove_alarm(alarm_id);
        remove_object();
        return;
    }

    if(VIC->query_ghost())
    {
        remove_alarm(alarm_id);
        remove_object();
        return;
    }
    
    if (!interactive(VIC))
    {
        VIC->command("break arrow in " + hid_name(hid));
    }
    
    if (!arrow_broken)
    {
        VIC->heal_hp(-MOVEMENT_HP_LOSS);
        string mesg;
        switch (random(3))
        {
        case 0:
            mesg = "The unbroken arrow piercing you in the " + hid_name(hid) 
                + " causes you a lot of pain with every movement you "
                + "make.\n";
            break;
        case 1:
            mesg = "Even breathing causes you pain from the "
                + "unbroken arrow piercing your " + hid_name(hid) + ".\n";
            break;
        case 2:
            mesg = "Excruciating pain from the unbroken arrow in your "
                + hid_name(hid) + " almost threatens to knock you "
                + "unconscious.\n";
            break;
        }
        VIC->catch_msg(mesg);
        tell_room(E(VIC), "The wound from the arrow in " + QTPNAME(VIC) 
            + " " + hid_name(hid) + " bleeds.\n", ({VIC}), VIC);
    }
    
    if(VIC->query_hp() <= 0)
    {
        player_kill();
    }
}

void player_kill()
{
    if(alarm_id)
    remove_alarm(alarm_id);
    tell_object(VIC, "You cough noisily. You feel a warm liquid running "
        + "down your chin, but you're dead before you realize it's "
        + "blood.\n");
    tell_room(E(VIC), QCTNAME(VIC) + " collapses, overcome by the arrow wound "
        + "in " + VIC->query_possessive() + " " + hid_name(hid) + ".\n", 
        ({VIC}), VIC);
    VIC->do_die(this_object());
    remove_object();
}

/*
* Function name: log_player_death_extra_info
* Description  : This function is called to query extra information about the
*                object that was responsible for the player death. We use it
*                to report more about the person/object responsible.
* Returns      : string - the information.
*/
string
log_player_death_extra_info()
{
    string log_msg;

    if (strlen(responsible_living))
    {
        log_msg = "Responsible living: " + responsible_living + "\n";
    }
    return log_msg;
}

/* Code here is a bit tricky couse of that heap mechanizm, I recommend
/std/launch_weapon exemples */
void reward_arrow()
{
    FIX_EUID;
    object stack_burr;
    object single_burr;
    stack_burr = clone_object(ORIGINAL_ARROW);
    stack_burr->split_heap(1);
    single_burr = stack_burr;
    stack_burr = stack_burr->make_leftover_heap();
    single_burr->move(VIC, 1);
    if (arrow_broken)
    {
        single_burr->set_broken(1);
    }
    else
    {
        VIC->catch_msg("The arrow is all covered with blood, but beside "
            + "that it's in a fine condition.\n");
    }
    stack_burr->remove_object();
}

void land(string archer, int hitlocid, int reloading = 0)
{
    hid = hitlocid;
    responsible_living = archer;
    if (!arrow_broken)
    {
        // We set the alarm if the arrow isn't broken.
        alarm_id = set_alarm(1.0, itof(WOUND_INTERVAL), &do_bad_stuff());
    }
    VIC->catch_msg("Your " + hid_name(hid) + " is pierced with an "
        + "arrow!\n");
    VIC->add_subloc("arrow_subloc" + alarm_id, TO);
}

/* I know it's recommended strongly not to use that - but it's better then
leave unhandled alarms, now isn't it?:) */
public void linkdeath_hook(object player, int linkdeath)
{
    if(linkdeath)
    {
        remove_alarm(alarm_id);
    }
    else if (!arrow_broken)
    {
        alarm_id = set_alarm(1.0, itof(WOUND_INTERVAL), &do_bad_stuff());
    }
}


/* Quiting wont help ya smartass */

/* Disabling temporarily as it saves the item in death

public string query_auto_load()
{
    return MASTER + ":" + hid + "," + arrow_broken + ","
        + responsible_living;
}
*/

/* Recovers the arrow - and makes it land again. It will also display the
landing message again - but that's ok since player might forgot:) */

public void
init_arg(string arg)
{
    string file, new_hid, archer;

    if (!strlen(arg))
    return;

    sscanf(arg, "%d,%d,%s", new_hid, arrow_broken, archer);

    set_alarm(3.0, 0.0, &land(archer, new_hid, 1));
}

string show_subloc(string subloc, object me, object for_obj)
{
    string resoult;
    if (for_obj == me)
    {
        resoult = "Your";
    }
    else
    {
        resoult = capitalize(me->query_possessive());
    }
    resoult += " ";
    
    
    /* what is pierced? */
    resoult += query_hid_name();
    resoult += " is pierced with an arrow.";
    if (arrow_broken)
    {
        resoult += " The arrow has been broken, the wound looks very bad.";
    }
    resoult += "\n";
    return resoult;
}
