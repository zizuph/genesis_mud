/*
 * File:     shirt.c
 * Created:  Lilith, Feb 1999
 * Purpose:  Monk garment
 * Log:
 * todo----add bow emote
 */

#pragma strict_types
#pragma save_binary
#pragma no_inherit

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

inherit "/std/object.c";
inherit "/lib/wearable_item";
inherit "/cmd/std/command_driver";

void
create_object ()
{
    config_wearable_item(A_BODY, 1, 15, this_object());

    set_name("shirt");
    add_name(({"tunic", "garment", "clothing"}));
    set_pname(({"shirts", "garments", "clothes", "clothing"}));

    // add the file name as a name for easy use with present()
    add_name(MASTER_OB(this_object()));

    set_adj(({"simple","woven","gray", "grey","monk"}));
    set_short("simple gray shirt");
    set_long("This is a simple shirt, woven from coarse flax fibers "+
        "and dyed a plain, unassuming gray. It resembles a short coat, "+
        "one designed so that the sides overlap at the front "+
        "and are secured at the waist by a belt.  The sleeves are wide "+
        "and terminate just above the wrist, allowing the wearer un"+
        "restricted movement.  It is entirely unadorned, and elegant "+
        "in its simplicity and functionality.\n");

    add_prop(OBJ_I_VALUE,    50);
    add_prop(OBJ_I_WEIGHT,  750);
    add_prop(OBJ_I_VOLUME, 1000);

}

mixed
wear(object ob)
{
    object tp = environment(this_object());

    if ((tp != this_player()) || (ob != this_object()))
        return -1;
         
    /* Successful wear */
    write("You slip the "+ short() +" over your bare shoulders and "+
        "fold it over in the front.\n");
    tell_room(environment(tp), QCTNAME(tp) + " slips the " + 
        short() +" over "+ tp->query_possessive() +" shoulders "+
        "and folds it over in front.\n", tp);
    return 1;
}

void
leave_env(object from, object to)
{   
    /* If I don't call this func, and people drop or put this while 
     * it is worn, it looks like it is still in the players inventory
     */
    wearable_item_leave_env(from, to);    

    ::leave_env(from, to);
}

int
bow(string str)
{
    object *oblist;
    string his = this_player()->query_possessive();
    if (!query_worn()) 
        return 0;
      
    if (!strlen(str))
    {
        write("You tuck your hands into the wide sleeves "+
            "of your "+ short() +" and incline your head "+
            "and shoulders in a formal bow.\n");
        allbb(" tucks "+ his +" hands into the wide sleeves "+
            "of "+ his +" "+ short() +" and inclines "+ his +
            "head and shoulders in a formal bow.");
        return 1;
    }
   
    oblist = parse_this(str, "[to] / [before] [the] %i");
   
    if (!sizeof(oblist))
    {
        notify_fail("What or whom wouldst thou bow to?\n");
        return 0;
    }
   
    actor("You tuck your hands into the wide sleeves "+
       "of your "+ short() +" and incline your head "+
       "and shoulders to", oblist, " in a formal bow.");
    all2actbb(" tucks "+ his +" hands into the wide sleeves "+
       "of "+ his +" "+ short() +" and inclines "+ his +
       "head and shoulders to", oblist, " in a formal "+
       "bow.");
    targetbb(" tucks "+ his +" hands into the wide sleeves "+
       "of "+ his +" "+ short() +" and inclines "+ his +
       "head and shoulders to you in a formal bow.", oblist);
    return 1;
}


void
appraise_object(int num)
{
    ::appraise_object(num);
    appraise_wearable_item();
}

