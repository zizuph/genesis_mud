/* /d/Shire/bree/rooms/town/stable/club/crop.c

 Riding Crop

 Guild object of the Equestrian Society of Bree January 2003

 Snarfed by Palmer from:
 The guild object of the Old Fogey's Club...Dunstable 12/94

*/

#pragma save_binary;

inherit "/std/object";
#include <macros.h>
#include <stdproperties.h>
#include <composite.h>
#include "/d/Shire/common/defs.h"
#include <formulas.h>
#define EQUESTRIAN_SOUL "/d/Shire/bree/rooms/town/stable/club/equestrian_soul"
#define RACE this_player()->query_race()


void
create_object()
{
    set_name("crop");
    add_name("_equestrian_crop_");
    add_adj(({"black","leather"}));
    set_short("riding crop");
    set_long("This riding crop is made from fine leather. The handle "+
      "has 'ehelp' etched into the side.\n");
    add_item(("handle"), "The handle is made of black leather.\n");
    add_prop(OBJ_I_WEIGHT, 20);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_M_NO_DROP,"The riding crop is hanging from your wrist and won't drop.\n");
}

void
enter_env(object inv,object from)
{
    ::enter_inv(inv,from);

    if (!interactive(inv))
        return;
    if (inv->query_ghost())
        return;
    // Below code makes sure the m_in and m_out msgs aren't hardcoded.
    if (!inv->query_equestrian_hobble_shadow())
    {
    if (inv->query_m_out() == "leaves walking bow-legged")
        inv->set_m_out(F_ALIVE_MSGOUT);
    if (inv->query_m_in() == "arrives walking bow-legged")
        inv->set_m_in(F_ALIVE_MSGIN);
    }
    set_alarm(3.0, 0.0, "get_me_soul", inv);
}

string
query_auto_load() { return MASTER + ":"; }

public string
query_recover() { return 0; }

void
get_me_soul(object ob)
{
    int test;
    /*
    if ()
    {
        ob->catch_msg("Hey, your not an equestrian anymore!!\n");
        ob->remove_equestrian_hobble_shadow();
        remove_object();
        return;
    } */

    setuid(); seteuid(getuid());
    test = ob->add_cmdsoul(EQUESTRIAN_SOUL);
    if (test != 1)
        ob->catch_msg("Equestian soul failed. Use <bug crop> to file a report please.\n");
    ob->update_hooks();
}
