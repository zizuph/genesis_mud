/* Mortis 12.2005
 *
 * This is the base for packs and weapon holders Daronius
 * crafts in the Arms district of Palanthas.
 *
 * Emotes could use work and expansion.
 *
 * Mortis 09.2014
 * Syntax (if's), grammar, adjective updates.
 *
 * 313, 781 added check if (!art) to prevent wizards who foolishly clone
 * this base file without adjectives or names don't get bugged. Thanks Finwe!
 * -Mortis 03.2015
 *
 * Added a check to see if the object is held before putting it in pack.
 *
 * Cotillion 2019-03-15
 * - Fixed ::prevent_enter() call
 */
 
inherit "/d/Genesis/std/wearable_pack";
inherit "/lib/wearable_item";
inherit "/lib/keep";

#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <language.h>
#include <composite.h>
#include "../guild.h"

inherit "/lib/commands.c";

#define TO this_object()
#define TP this_player()

int weight, volume, value, maxweight, maxvolume, reduce;

string recover_string, cus, col, mat, art, at, cusshort, cusmore, colmore,
    matmore, matlong, collong, artmore, soundmore, ndesc2, artplural;

int cont_alarm = 0;

/* Prototypes */

int adjust_weight(string which);


void
create_wearable_pack()
{
    seteuid(getuid());
	
	weight = adjust_weight("weight");
    volume = adjust_weight("volume");
    value = adjust_weight("value");
    maxweight = adjust_weight("maxweight");
    maxvolume = adjust_weight("maxvolume");
    reduce = adjust_weight("reduce");
	

    set_slots(A_ANY_SHOULDER);
    set_layers(1);   // I don't want layers and looseness to hinder so
    set_looseness(8); // check on these.

    add_prop(CONT_I_WEIGHT, weight);
    add_prop(CONT_I_VOLUME, volume);
    add_prop(OBJ_I_VALUE, value);
    add_prop(CONT_I_MAX_WEIGHT, maxweight);
    add_prop(CONT_I_MAX_VOLUME, maxvolume);
    add_prop(CONT_I_REDUCE_WEIGHT, reduce);

    
    set_name("bandolier");
    set_pname("bandoliers");
    set_adj("black");
    add_adj("leather");
	
	set_short("black leather bandolier");
    set_pshort("black leather bandoliers");
	
	set_long("A black leather bandolier.\n");
    
    set_keep(1);
	
    set_cf(TO);
}


int
close(object obj)
{
    string objname = obj->query_name();

    string arty = obj->short();
        
    write("There is no way to close the " + arty + ".\n");
	
    return 3;
}


int
adjust_weight(string which)
{    
    int wei, vol, val, maxw, maxv, redu;

	wei = 775 + random(50);
	vol = 800 + random(150);
	val = 300;
	maxw = 40000;
	maxv = 40000;
	redu = 195;  // was way way too high 
            
                  
    if (which == "volume")
    { return vol; }
    if (which == "value")
    { return val; }
    if (which == "weight")
    { return wei; }
    if (which == "maxweight")
    { return maxw; }
    if (which == "maxvolume")
    { return maxv; }
    if (which == "reduce")
    { return redu; }
}


/* 
 * Reject containers of any sort. 
 */
int
prevent_enter(object ob)
{
	if(ob->query_band_fit() != 1)
	{
		write("Only certain tiny vials and weapon oils will fit in "
		+"the bandolier.\n");
		return 1;
	}

	if (ob->query_prop(OBJ_I_BROKEN))
	{
		write("The bandolier cannot hold broken items.\n");
		return 1;
	}

    return ::prevent_enter(ob);
}


/* 
 * item_filter, used to filter out certain objects when shifting stuff 
 * in or out of pack, like non-sellables, non-droppables, 
 * containers etc. 
 */
int
item_filter(object ob)
{
    return !((ob->query_band_fit()() !=W_KNIFE) ||
         (ob->query_prop(OBJ_M_NO_GIVE)) ||
         (ob->query_prop(OBJ_M_NO_DROP)) ||
         (!(ob->query_prop(OBJ_I_VALUE))) ||
         (ob->query_prop(CONT_I_IN)) || /* containers */
         (ob->query_worn()) ||
         (ob->query_wielded()) ||
         (ob->query_held()) ||
         (ob->query_prop(LIVE_I_IS)) ||
         (ob->query_prop(OBJ_I_HAS_FIRE)) ||
         (ob->id("message")) ||
         (ob->id("note")) ||
         !CAN_SEE(TP, ob));
}


/*public void
pack_fill_hook(object *moved)
{
    if (art == "bandeleria")
    {
        write("You sheathe " + COMPOSITE_DEAD(moved) + " in your " + short()
        + ".\n");
        tell_room(E(TP), QCTNAME(TP) + " sheathes " + COMPOSITE_DEAD(moved)
        + " in " + HIS(TP) + " " + short() + ".\n", TP);
        return;
    }

    ::pack_fill_hook(moved);
    return;
}


public void
pack_empty_hook(object *moved)
{
    if (art == "bandeleria")
    {
        write("You draw " + COMPOSITE_DEAD(moved) + " from your " + short()
        + ".\n");
		
        tell_room(E(TP), QCTNAME(TP) + " draws " + COMPOSITE_DEAD(moved)
        + " from " + HIS(TP) + " " + short() + ".\n", TP);
        return;
    }

    ::pack_empty_hook(moved);
    return;
}*/


void
init()
{
    ::init();

	return;
}


int move_to(object what)
{
    if (!objectp(what))
      return 0;
  
    if( what->move(TO) != 0 )
      return 0;

    return 1;
}


/* Ensure here that the player removes the pack first if 
 * it leaves his/her inventory. */
void
leave_env(object old, object dest)
{
    ::leave_env(old, dest);

    wearable_item_leave_env(old, dest);
}


// Ensure that the player can properly appraise this item. 
void
appraise_object(int num)
{
    ::appraise_object(num);

//    appraise_wearable_item();
}


string
query_recover()
{
    return MASTER + ":" + recover_string;
}


void
init_recover(string arg)
{
    ::init_keep_recover(arg);
}
