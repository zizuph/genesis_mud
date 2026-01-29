// file name  :  altar_jazsis.c
// creator(s) :  lucius + zielia
// revision(s):
// purpose    :  Altar for the Ziggurat
// note       :  May bless the mortal with temporary resistance to 
//		 fire (RES: 15) and cold (RES: 15) see js_flush.c
// bug(s)     :
// to-do      :
#pragma strict_types

#include "zigg.h"
#include "/d/Avenir/include/deities.h"

#include <macros.h>
#include <stdproperties.h>

inherit (ZIG_LIB + "altar");

#define PROP_I_INSIDE    "_moved_past_curtains"
#define PRAYER_PROP        "_live_i_prayed_at_jazsis_altar"


/*
 * set_id_long(string)      - Identified long desc.
 * set_unid_long(string)    - Unidentifed long desc.
 * set_altar_short(string)  - Short desc.
 * set_god(string *)        - God(s) of altar.
 * set_altar_hour(int)      - Hour of the God.
 * set_offer_max(int)       - Max offerings.
 * set_altar_name(string)   - True name of altar.
 * set_offering_prop(*string)   - Acceptable offerings have these props.
 ** ADD ACTIONS BELOW **
 * set_bless_command(string *)     - Accepted commands to bless altar.
 * set_defile_command(string *)    - Accepted commands to defile altar.
 * set_repair_command(string *)    - Accepted commands to repair altar.
 * set_destroy_command(string *)   - Accepted commands to destory altar.
 * set_offer_command(string *)     - Accepted commands to make offerings.
 * set_pray_command(string *)      - Accepted commands to pray at altar.
 */

public void
create_altar(void)
{
    set_god(({"jazur", "sisera"}));
    set_altar_hour(12);
    set_altar_name("ziggurat::jazur:sisera");
    set_altar_short("two triangular braziers burning atop a black stone altar");

    add_name(({"brazier", "braziers"}));
    set_adj(({"triangular", "burning", "black", "stone"}));

    set_unid_long("Two triangular braziers burn atop a black stone altar "+
        "The braziers are arranged tip to tip, their apexes kissing. "+
        "The western-most brazier is alight with a blue black flame. The "+
        "eastern one glows with a scintilating ruby fire which fumes faint, "+
        "fragrant smoke.");
    set_id_long("Two triangular braziers burn atop a black stone altar. "+
        "The braziers are arranged tip to tip, their apexes kissing. "+
        "Jazur's brazier is alight with a blue black flame. Sisera's "+
        "glows with a scintilating ruby fire which fumes faint, "+
        "fragrant smoke.");

    set_offering_prop(({JAZUR_OFFERING,SISERA_OFFERING,UNIVERSAL_OFFERING}));

    set_offer_command(({"offer", "sacrifice"}));
    set_pray_command(({
    "pray", "petition", "worship", "respect", "revere", "celebrate"
    }));

    set_bless_command(({"bless", "sanctify"}));
    set_defile_command(({"desecrate", "defile"}));
    set_repair_command(({"repair", "restore"}));
    set_destroy_command(({"destroy", "break"}));

    set_offer_max(20);
    set_no_show_composite(1);  //don't want it to show up in room desc.
    add_prop(OBJ_M_NO_GET, "The altar is far too heavy to be gotten.\n");
}

public void
do_wind(void)
{
    if (!TP->query_prop(PROP_I_INSIDE))
    {
        write("You wind your way through the scarlet curtains, weaving between "+
            "layers of silk to stand before the altar. ");
        say(QCTNAME(TP) +" winds "+ HIS(TP) +" way through the silk panels "+
            "weaving between several layers until "+ HE(TP) +" reaches the "+
            "center of the reliquary.\n");
        TP->add_prop(PROP_I_INSIDE, 1);
    }
}

public varargs string
long(string str, object for_obj = this_player())
{
    do_wind();

    return ::long(str, for_obj);

}

public int
do_pray(string str)
{
    do_wind();

    return ::do_pray(str);

}

public int
do_offer(string str)
{
    do_wind();

    return ::do_offer(str);

}

public int
do_bless(string str)
{
    do_wind();

    return ::do_bless(str);

}

public int
do_defile(string str)
{
    do_wind();

    return ::do_defile(str);

}

public int
do_repair(string str)
{
    do_wind();

    return ::do_repair(str);

}

public int
do_destroy(string str)
{
    do_wind();

    return ::do_destroy(str);

}

public void
altar_result_pos(string verb, string god)
{
    object flush;

    // increment the prayer prop to increase the chance of failure
    // for continual attempts.
    TP->add_prop(PRAYER_PROP, TP->query_prop(PRAYER_PROP) + 1);

    if(random(2 + TP->query_prop(PRAYER_PROP)))
    {
        TP->catch_tell("Your prayers go unheard.\n");
        return;
    }

    write("A feeling of ecstasy uplifts you, as though you can feel "+
        LANG_POSS(god) +" pleasure in your actions.\n");

    say(QCTNAME(TP) +" appears to be momentarily over"+
        "come with ecstacy.\n");

    if (!present("JS::Flush", TP))
    {
	flush = clone_object(ZIG_OBJ +"js_flush");
	flush->move(TP, 1);
    }
}

public void
hook_smelled(string what)
{
    write("Fragrant smoke tickles your nose with a wild, musky, "+
        "exciting scent.\n");
}
