/* 
 *  Arman Oct 2016 WoHS robe - based on MM robe
 *
 *  /d/Gondor/guilds/morgulmage/obj/mage_robe.c
 *  Eowul, Februari 2013  
 */
#pragma save_binary
#pragma strict_types

inherit "/std/object";
inherit "/lib/wearable_item";

#include "/d/Krynn/common/defs.h"
#include <files.h>
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "../defs.h"

object hood_shadow;

public int valid_owner();
public void set_robe_colour(string str);

string robe_colour = "dusty";

#include <time.h>
#include <formulas.h>
#include <state_desc.h>

/*
 * Function name: create_object
 * Description:   Creator.
 */
public void 
create_object()
{
    set_name(({ "robe", "cloak" }));
    add_name( "wohs_robe_object" );
    set_adj(({"large", "hooded"}));
    add_item(({"hood", "wide hood", }), "When worn over the head "
        + "the wide hood of the robe will hide the features of the "
        + "person wearing the robe.\n");
    add_item(({"intricate golden runes", "trim", }), "Intricate golden " +
        "runes have been carefully embroidered along the trim of the " +
        "robe.\n");

    add_prop(MAGIC_AM_ID_INFO, ({ "This robe radiates faint traces of " +
        "magic, possibly due to its source and nature.\n", 10 }));
    add_prop(MAGIC_AM_MAGIC, ({ 10, "enchantment" }));

    set_wf(this_object());
    set_slots(A_ROBE);

    // guild objects do not expire over time as normal equipment.
    // this should not be called in an object without AoB approval!
    remove_item_expiration();

    add_prop(OBJ_I_VALUE,     0);
    add_prop(OBJ_I_WEIGHT, 1200);
    add_prop(OBJ_I_VOLUME,  650);
    add_prop(OBJ_I_NO_DROP,   1);
    add_prop(OBJ_M_NO_GIVE,   1);

    set_looseness(20);
    set_layers(1);
}

public mixed remove(object ob)
{    

    if (objectp(hood_shadow)) {
        hood_shadow->remove_hood_shadow();
        hood_shadow = 0;
    }

    return 0;
}

public mixed wear( object ob )
{
    if (ob != this_object())
    {
        return -1;
    }

    if (!valid_owner())
    {
        return -1;
    }

    return 0;
}

/*
 * Function name: valid_owner
 * Description  : Checks whether the owner has the rights to this robe
 */
public int valid_owner()
{
    object user = this_player();

    if ((user->query_guild_name_occ() != WOHS_GUILD_NAME) &&
        (!user->query_wiz_level())) {
        return 0;
    }

    return 1;
}

/*
 * Function name: query_recover
 * Description  : no recovery, since the robe autoloads
 * Returns      : 0
 */
public string query_recover()
{
    return 0;
}

public string
query_robe_hooded_desc()
{
   return robe_colour;
}

public void
set_robe_colour(string str)
{
    robe_colour = str;
    TO->set_adj(str);
    TO->set_short(str + " hooded robe");
    TO->set_long("This is a large " +str+ " robe, with a wide hood. " +
        "It is trimmed with intricate golden runes, and covers you from " +
        "head to foot. When worn you can <hood> and <unhood> yourself.\n");
}

void
enter_env(object from, object to)
{
    object who = this_player();

    if(who->query_wohs_alignment_penalty())
    {
      robe_colour = "grey";
      TO->set_robe_colour(robe_colour);
    }
    else if(WOHS_MANAGER->query_wohs_order_colour(who))
    {
      robe_colour = WOHS_MANAGER->query_wohs_order_colour(who);
      TO->set_robe_colour(robe_colour);
    }

    ::enter_env(from, to);
}

/*
 * Function name: leave_env
 * Description:   remove the hood shadow if the robe leaves its
 *                environment 
 * Arguments:     from - old environment, to - new environment
 */
public void
leave_env(object from, object to)
{
    if (objectp(hood_shadow))
    {
        hood_shadow->remove_hood_shadow();
        hood_shadow = 0;
    }

    ::leave_env(from, to);
}

/*
 * Function name : do_hood
 * Description   : wear the hood
 * Argument      : command verb argument
 * Returns       : 1/0
 */
public int do_hood(string str)
{
    if ((query_verb() == "hood") && (!str || str != "me")) {
        notify_fail("Hood whom?\n");
        return 0;
    }

    if ((query_verb() == "wear") && (!str || str != "hood")) {
        notify_fail("Wear what?\n");
        return 0;
    }

    if (query_worn() != this_player())
    {
        notify_fail("You do not wear your robe!\n");
        return 0;
    }

    if (this_player()->query_hooded())
    {
        notify_fail("You are already wearing your hood!\n");
        return 0;
    }

    write("You pull the hood of your robe over your head, concealing "
        + "your features.\n");
    say(QCTNAME(this_player()) + " pulls the hood of " 
        + this_player()->query_possessive() + " robe over "
        + this_player()->query_possessive() + " head, concealing "
        + this_player()->query_possessive() + " features.\n");

    setuid();
    seteuid(getuid());

    if(TP->query_wohs_alignment_penalty())
      robe_colour = "grey robed";     
    else if(WOHS_MANAGER->query_wohs_order_colour(TP))
      switch(WOHS_MANAGER->query_wohs_order_colour(TP))
      {
        case "white":
        {
           robe_colour = "white-robed";
           break;
        }
        case "red":
        {
           robe_colour = "red-robed";
           break;
        }
        case "black":
        {
           robe_colour = "black-robed";
           break;
        }
        default:
        {
           robe_colour = "grey-robed";
           break;
        }
      }
    else
      robe_colour = "white-robed";

    hood_shadow = clone_object(WOHS_OBJS + "mage_robe_shadow");
    hood_shadow->set_robe_colour(robe_colour);
    hood_shadow->shadow_me(this_player());
    return 1;
}

/*
 * Function name: do_reveal
 * Description:   remove the hood
 * Argument:      str - argument
 *                silent - write no message if 1
 * Returns:       1/0
 */
public int do_reveal( string str, int silent = 0 )
{
    if(str == "me")
        return 0;

    switch (query_verb())
    {
        case "unhood":
        case "reveal":
//            if (!str || str != "me") {
            if (!str) {
                notify_fail(capitalize(query_verb()) + " whom?\n");
                return 0;
            }
            break;
        case "remove":
            if (!str || str != "hood") {
                notify_fail("Remove what?\n");
                return 0;
            }
            break;
    }

    if (!this_player()->query_hooded())
    {
        notify_fail("You are not wearing your hood!\n");
        return 0;
    }

    write("You remove the hood and reveal your face again.\n");
    say(QCTNAME(this_player()) + " removes " 
        + this_player()->query_possessive() + " hood.\n");

    hood_shadow->remove_hood_shadow();
    hood_shadow = 0;
    return 1;
}

public void init()
{
    ::init();

    add_action(do_hood  , "hood");
    add_action(do_hood  , "wear");
    add_action(do_reveal, "reveal");
    add_action(do_reveal, "unhood");
    add_action(do_reveal, "remove");
}
