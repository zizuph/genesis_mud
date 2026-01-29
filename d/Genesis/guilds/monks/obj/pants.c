/*
 * File:     pants.c
 * Created:  Lilith, Feb 1999
 * Purpose:  Monk garment
 * Log:
 *
 */

#pragma strict_types
#pragma save_binary
#pragma no_inherit

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

inherit "/std/object.c";
inherit "/lib/wearable_item";

void
create_object ()
{
    config_wearable_item(A_LEGS, 1, 15, this_object());

    set_name("trousers");
    add_name(({"pants", "garment", "clothing"}));

    // add the file name as a name for easy use with present()
    add_name(MASTER_OB(this_object()));

    set_pname(({"trousers", "garments", "clothes", "clothing"}));
    set_adj(({"loose", "woven", "gray", "grey", "monk", "draw-string"}));
    set_short("pair of gray draw-string trousers");
    set_pshort("pairs of gray draw-string trousers");
    set_long("These are loose-fitting trousers made of coarsely-woven "+
        "flax fibers and dyed a plain, unassuming gray.  They are held "+
        "in place with a draw-string which can be tightened to fit "+
        "most waistlines.  The wide-legged pants end a finger's width "+
        "or two above the ankle, allowing the wearer full and unrest"+
        "ricted range of motion.  This is a simple garment for a "+
        "person of simple needs.\n");

    add_prop(OBJ_I_VALUE,    75);
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
    write("You slip into the "+ short() +" and knot the string "+
        "loosely about your waist.\n");
    tell_room(environment(tp), QCTNAME(tp) + " slips into the "+
        short() +".\n", tp);
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


void
appraise_object(int num)
{
    ::appraise_object(num);
    appraise_wearable_item();
}

