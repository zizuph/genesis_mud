// file name: /d/Avenir/common/dead/obj/spectral_orb.c
// creator(s): Lilith & Zizuph Aug 2021
// purpose:    Eye of a Spectral guardian who can see through walls,
//             see in the dark, see invis, etc. Considered "lucky". 
// note:       When held, this will grant dark vision 
//             and a bit of 'luck' (+20 defence)
// updates: 

// ZIZ: add functionality _live_i_see_dark when held. 
//      also add ALTER_SKILL(tp, SS_DEFENCE, 20);

inherit "/std/object";
inherit "/lib/keep";
inherit "/lib/item_expiration.c";
inherit "/lib/holdable_item";
#include <files.h>
#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>
#include "../dead.h"


void
create_object()
{
    set_name("orb");
	set_adj("spectral");
	set_short("spectral orb");
	set_pshort("spectral orbs");
    set_long("This orb is actually an eyeball from a spectral "
	    +"guardian. It has a faint greenish glow to it. You "
		+"wonder what would happen if you <held> it in your hand.\n");
	set_keep(1);
	set_slots(W_ANYH);
	set_item_expiration();
//	add_prop(OBJ_S_WIZINFO, /*Will fill this in when it is finalized */ );
//	add_prop(MAGIC_AM_ID_INFO, ({ /*Will fill this in when it is finalized */}));
	add_prop(MAGIC_AM_MAGIC, ({ "death", 50}));
    add_prop(OBJ_I_VALUE, 4000);
    add_prop(OBJ_I_VOLUME, 250);
    add_prop(OBJ_I_WEIGHT, 50);

}



public mixed
hold()
{
	// add prop live i see dark
	// add some defence skills for luck
    return 0;
}

public mixed
release()
{
     // remove the live i see dark prop and the defence skill.
    return 0;
}

void leave_env(object from, object to)
{
    ::leave_env(from, to);

    holdable_item_leave_env(from, to);
}

void appraise_object(int num)
{
    ::appraise_object(num);
    appraise_holdable_item();
}

string query_recover()
 {
    return MASTER + ":" + query_item_expiration_recover();
 }

void init_recover(string arg)
{
    init_item_expiration_recover(arg);
}
