#pragma strict_types
// file name:   /d/Avenir/common/holm/obj/hiz_altar.c
// creator(s):  Lilith, March '97
// revision(s): 
// 	Lucius, Jan 2009: Updated blessing to be variable
// 		and be a more globally shared water breathing.
//
// purpose:     Altar to the god Hizarbin
// note:             
// bug(s):           
// to-do:
//
inherit "/d/Avenir/inherit/altar";

#include "../holm.h"
#include "/d/Avenir/include/deities.h"
#include "/d/Avenir/include/water.h"

#include <language.h>
#include <stdproperties.h>

public void
create_altar(void)
{
    setuid();
    seteuid(getuid());

    set_name("altar");
    set_adj("intertidal");
    add_name(({"pool","hizarbin_altar"}));
    set_altar_name("hiz_altar");
    set_altar_hour(11);
    set_god("hizarbin");
    set_altar_short("intertidal pool");    
    set_offer_max(12);

    set_id_long("A beautiful pool, rimmed with green and red algae. "+
      "The mirror-like surface is dark with mystery, reflecting "+
      "the diffuse light of the Source. There is something about "+
      "this pool and the symbols carved into the rocks embracing "+
      "it that lead you to believe that this spot is sacred to "+       
      "Hizarbin, the Lord of the Waters.");
    set_unid_long("A beautiful pool, rimmed with green and red algae. "+
      "The mirror-like surface is dark with mystery, reflecting "+
      "the diffuse light of the Source. Somewhere deep within "+
      "you have a strong conviction that this is more than a "+
      "simple intertidal pool.");
    add_item(({"surface", "surfaces"}), 
      "The surface is oddly smooth and undisturbed by either the "+
      "wind or the saltspray from the sea. The surface is dark "+
      "with mystery, concealing what lies beneath.\n");

    set_bless_command(({"bless", "sanctify"}));
    set_defile_command(({"desecrate", "defile", "deface"}));
    set_offer_command(({"offer", "sacrifice"}));
    set_offering_prop(({ HIZARBIN_OFFERING }));
    set_pray_command("pray");
    set_worship_command("worship");
    set_offer_max(20);
	
    add_prop(OBJ_M_NO_GET, 
      "How does one get such a large body of water?\n");
}                                                                            

#define PRAYER_PROP  "__live_i_prayed_hizarbin_altar"

/*
 * Function name:  altar_result_pos
 * Description:    Here the message is written when the player
 *                 does something Positive to the altar.
 *                 You may redefine it if you wish, to add things 
 *                 like align adjustments, etc.
 * Arguments:      qvb  - The verb used 
 */
public void
altar_result_pos(object pl, string qvb)
{
    int pray = pl->query_prop(PRAYER_PROP),
	prop = pl->query_prop(MAGIC_I_BREATH_WATER);

    if (!prop)
	pl->add_prop(PRAYER_PROP, ++pray);

    if (prop || random(++pray))
    {
	pl->catch_tell("Your prayers go unheard.\n");
	return;
    }

    write("A feeling of ecstasy uplifts you, as though you can feel "+
      capitalize(LANG_POSS(query_god())) +" pleasure in your actions.\n");

    say(QCTNAME(TP) +" appears to be momentarily over"+
      "come with ecstacy.\n");

    object obj = clone_object(MBW_OBJECT);

    if (!objectp(obj))
	return;

    obj->set_time(MBW_HIZARBIN);
    obj->move(pl, 1);

    pl->catch_tell("The air suddenly tastes more refined.\n");
}
