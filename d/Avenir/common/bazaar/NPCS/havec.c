// file name:	havec.c
// creator(s):  Ilyian
// purpose:     To be shopkeeper for the sackmaker stall.
// last update: Lilith Nov 1996
//
// ****	Lucius Mar 2009: Re-written for new custom packs & sacks by Havec.
//
#pragma strict_types

#include "/d/Avenir/common/bazaar/bazaar.h"

#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>

inherit "/d/Avenir/inherit/monster";
inherit "/d/Avenir/inherit/craftsman";

public void
create_monster(void)
{
    set_name("havec");
    add_name(({"shopkeeper","keeper"}));
    set_race_name("gnome");
    set_title("Sackmaker");

    add_adj("middle-aged");
    set_long("This gnome looks to be rather prosperous. " +
      "He appears to be a respectable merchant turning " +
      "a healthy profit with wares of his own making.\n");

    set_gender(0);
    set_alignment(0);

    set_stats(({70,70,70,70,70}));
    set_all_hitloc_unarmed(50);
    set_knight_prestige(-2);

    set_skill(SS_UNARM_COMBAT,50);
    set_skill(SS_BLIND_COMBAT,100);
    set_skill(SS_PARRY,50);
    set_skill(SS_DEFENCE,65);
    set_skill(SS_AWARENESS,50);
    set_skill(SS_WEP_SWORD,50);
    set_skill(SS_WEP_POLEARM,50);
    set_skill(SS_WEP_CLUB,50);
    set_skill(SS_WEP_KNIFE,50);

    add_prop(NPC_I_NO_RUN_AWAY, 1);

    set_chat_time(20);
    add_chat("My packs are simple to use. Just 'fill pack' and "+
      "'empty pack' to save yourself time during your travels.");
    add_chat("These are the highest-quality sacks you can find.");
    /*
     * Craftsman bits.
     */
    prefer_speech(1);
    craftsman_set_max_user_orders(2);
    craftsman_set_sold_item_names(({
	"pouch", "belt", "scrip", "knapsack", "sack",
    }));
}

public void
arm_me(void)
{
    MONEY_MAKE_SC(random(40))->move(this_object());

    clone_object(WORN + "pshirt")->move(TO, 1);
    clone_object(WORN + "ppants")->move(TO, 1);
    clone_object(WORN + "pshoes")->move(TO, 1);
    clone_object(WORN + "pbelt")->move(TO, 1);
}

private object hbase;
private string *descs, *fabrics;

private void
update_attrs(void)
{
    if (!objectp(hbase))
    {
	hbase = (WORN + "havec_base")->get_this_object();
	descs = hbase->query_m_descs();
	fabrics = hbase->query_m_fabrics();
    }
}
/*
 * Craftsman portion.
 */
public void
craftsman_configure_order(int id, string arg)
{
    // the file for the item to clone
    craftsman_set_item_file(id, WORN + "havec_" + arg);

    // time in seconds to complete creation of the item
    craftsman_set_time_to_complete(id, 45 + random(61));

    update_attrs();

    // orderable attributes
    craftsman_add_attribute(id, "desc", descs);
    craftsman_add_attribute(id, "fabric", fabrics);

    // add this for future use
    craftsman_add_selection(id, "_style", arg);
}

public void
craftsman_configure_item(object ob, mapping attrs, int id)
{
    ob->set_desc(attrs["desc"]);
    ob->set_fabric(attrs["fabric"]);
    ob->set_style(attrs["_style"]);

    ob->create_tailored();
}

public int
craftsman_calc_item_cost(object ob, int id)
{
    return ob->query_prop(OBJ_I_VALUE);
}

public void
craftsman_check_receive_order_hook(object ob, int id)
{
    ::craftsman_check_receive_order_hook(ob, id);
    /*
     * We left the lot; Depreciate!
     * (We want to ensure a small resale value)
     */
    int value = ob->query_prop(OBJ_I_VALUE);
    ob->add_prop(OBJ_I_VALUE, value / 3);
}

public void
init_living(void)
{
    ::init_living();
    craftsman_init();
}
