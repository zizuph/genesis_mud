/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * wand.c
 *
 * This is a small strange looking wand that will be a major part
 * of the Evil-Thang quest in Ribos.  It will have one charge left
 * in it, and will be used to make the hand of the player pass through
 * objects, such as the desk.  The result will be that, say there is a
 * locked desk......you wave the wand, and your hand can then retrieve
 * whatever is inside that desk.  This will work only with the desk
 * in the quest, but other desks can be coded to work with this wand.
 *
 * Vader
 * modified by Sorgum 950707
 * changed call_out to set_alarm, Mortricia May 1996
 */

#include "/d/Terel/include/Terel.h"

#include "local.h"
#include <cmdparse.h>
#include <wa_types.h>

inherit STDOBJECT;
inherit "/lib/holdable_item";
inherit "/d/Genesis/specials/new/lib/spell_enhancer";

object p_wand;
int wactive, wandused;
public int wave(string str);

/*
 * Function name: create_object
 * Description:   Default constructor.
 */
public void
create_object()
{
    ::create_object();
    
    set_name("wand");
    set_adj("strange");
    set_long("@@my_long");

    add_prop(OBJ_I_VALUE, 200);
    wandused = 0;
    wactive = 0;
    
    set_slots(W_ANYH);
    set_keep(1);

    //Enable default item expiration
    set_item_expiration();
    
    // This value will affect spell damage for spellcasters.
    set_magic_spellpower(40);    
}

/*
 * Function name: init
 * Description:   Add the 'command items' of this object.
 */
public void
init()
{
   ::init();
   if (environment(this_object()) == this_player())
       add_action(wave, "wave");
}

/*
 * Function name: deactivate
 * Description:   Remove the pass_hands property
 * Arguments:     tp - the player
 */
public void
deactivate(object tp)
{
    if (tp) {
        tp->catch_msg("Your hands feel normal again.\n");
        tp->remove_prop(PASS_HANDS);
    }
    wactive = 0;
}

/*
 * Function name: wave
 * Description:   Handle the wave action
 * Returns:       1/0
 */
public int
wave(string str)
{
    if (!str || !id(str)) {
        NF("Wave what?\n");
        return 0;
    }

    if (wandused == 0) {
        write("You wave the wand on yourself.  Your hands feel " +
              "very strange!\n");
        say(QCTNAME(TP) + " waves a wand on " + TP->query_objective() + "self.\n");

        wandused = 1;
        wactive = 1;
        TP->add_prop(PASS_HANDS, 1);

        set_alarm(600.0, -1.0, &deactivate(TP));
    }
    else
        write("The wand sputters a bit, but does nothing else.\n");

    return 1;
}

public string
my_long()
{
    if (wandused == 0 && wactive == 0) {
        return "It's a strange looking wand.  On the side of it, " +
               "you can see the inscription 'wave wand'.\n";
    } else if (wandused == 1 && wactive == 1) {
        return "It's a strange looking wand.\n";
    } else {
        return "It's a strange looking wand.\n";
    }
}

void 
appraise_object(int num)
{
    ::appraise_object(num);
    appraise_holdable_item();
    write(item_spellpower_desc());
}

 void
 leave_env(object from, object to)
 {
    ::leave_env(from, to);
    holdable_item_leave_env(from, to);
 }

string 
stat_object() 
{
    return ::stat_object() + stat_object_spellpower();
}
