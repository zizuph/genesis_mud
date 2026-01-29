/* Herb_witch.c coded by Amelia
 * Modified by Marisol (05/02/98)
 * to be Moss the witch in the town of Re Albi. */

inherit "/d/Earthsea/std/monster";
inherit "/std/act/action";
inherit "/d/Earthsea/lib/intro";


#include <wa_types.h>
#include <ss_types.h>
#include "/d/Earthsea/sys/macros.h"
#include <macros.h>
#include <filter_funs.h>
#include <stdproperties.h>



#include "defs.h"


void
create_earthsea_monster()
{
    set_name("auntie");
    set_title("Moss the Witch");
    set_living_name("_herb_witch_");
    set_adj(({"haggish", "filthy-looking"}));
    add_adj("herb");
    add_name("woman");
    set_race_name("human");
    set_gender(G_FEMALE);
    set_long("A haggish, filthy-looking woman. The color of her "+
        "hair is hard to tell. It looks like black with dirty grey. "+ 
        "It is all tangled up and in top of that, many loveknots "+
        "and charms ribbons are tied in it. There is a large mole on "+
        "the left side of her face, about the size of a peach pit. "+
        "She has a very large nose. She smells like someone that "+
        "haven't taken a bath for a long time, together with the "+
        "sharp aroma of chicken poops. Even though her appearance "+
        "and fragant smell, she is a friendly woman, little "+
        "understood. Even though she is old and ungly, there "+
        "is an aura of power that emanate from her.\n");

    set_act_time(40);
    set_chat_time(80);
    /* str, con, dex, int, wis, dis
    */
    set_stats(({90, 90, 90, 20, 50, 75}));


    set_hp(query_max_hp());
    set_all_hitloc_unarmed(50);

    set_skill(SS_DEFENCE, 60);            
    set_skill(SS_WEP_POLEARM, 90);
    set_skill(SS_PARRY, 80);

    add_prop(OBJ_M_NO_MAGIC_ATTACK, (QCTNAME(TO) + " raises "+
        "her hand, palm outward, and shouts: Avert!\n"));
    add_prop(OBJ_M_NO_ATTACK, "The witch is protected "+
      "by unseen powers.\n");
    add_act("emote tosses some corn to the chicken.");
    add_act("emote mutters a charm under her breath.");
    add_act("emote hums a song while she searchs for some herbs.");
    add_chat("Hi dearie! How may I help you?");
    add_act("grins toothless");

    add_equipment(RA_VILLAGE_WEP + "witch_staff");

}                                                      
