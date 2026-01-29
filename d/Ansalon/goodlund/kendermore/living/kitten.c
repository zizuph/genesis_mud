/* Takeable kitten from Kendermore, Gwyneth, June 1999 */

#include "../local.h"
#include "/d/Ansalon/common/defs.h"
#include <cmdparse.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

inherit "/std/act/action";
inherit AC_FILE
inherit "/std/act/attack";

/* Randomly loads a different colour kitten */

string *colour=({"orange-striped", "brown", "grey", "calico", "black", 
    "white", "orange"});
string gName;
int gChangedName = 0;

public string
add_kitty_name(string colr)
{
    if (query_gender() == G_MALE)
    {
        switch(colr)
        {
        case "brown":
            gName = "cocoa";
            break;
        case "grey":
            gName = "stormy";
            break;
        case "black":
            gName = "midnight";
            break;
        case "white":
            gName = "snowball";
            break;
        case "orange":
            gName = "garfield";
            break;
        case "orange-striped":
            gName = "tiger";
            break;
        default:
            gName = "patches";
            break;
        }
    }
    else
    {
        switch(colr)
        {
        case "brown":
            gName = "dusty";
            break;
        case "grey":
            gName = "pussywillows";
            break;
        case "black":
            gName = "ebony";
            break;
        case "white":
            gName = "snowflake";
            break;
        case "orange":
            gName = "gumdrop";
            break;
        case "orange-striped":
            gName = "tiger";
            break;
        default:
            gName = "boots";
            break;
        }
    }

    return gName;
}

public string
long_desc(string colr)
{
    string gender = capitalize(query_pronoun());
    return("A small fluffy " + colr + " kitten. " + gender + " looks " +
        "healthy and loved. " + gender + " has a small collar and nametag. " +
        "On the nametag is written, '" + capitalize(gName) + "'." +
        (gChangedName == 0 ? " Perhaps you can rename it." : "") + "\n");
}

void
create_creature()
{
    string colr = colour[random(7)];

    set_gender(random(2));
    set_race_name("kitten");
    set_adj(colr);
    add_kitty_name(colr);
    set_name(gName);
    add_name("animal");
    set_long(&long_desc(colr));

    set_stats(({5,5,5,2,2,5}));

    set_hp(400);
    set_alignment(50);
    set_knight_prestige(-5);

    NEVERKNOWN;

    set_act_time(10);
    add_act("emote chases after a butterfly.");
    add_act("emote meows loudly.");
    add_act("emote plays with a bug on the ground.");
    add_act("emote pounces on an invisible prey.");

    set_attack_unarmed(1, 11, 8, W_SLASH, 25, "left claw");
    set_attack_unarmed(1, 11, 8, W_SLASH, 25, "right claw");
    set_attack_unarmed(2, 15, 6, W_IMPALE, 20, "teeth");

    set_hitloc_unarmed(1, 4, 80, "body");
    set_hitloc_unarmed(2, 3, 10, "head");
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(OBJ_M_NO_GET, 0); /* Can be picked up */
    add_prop(OBJ_M_NO_DROP, 0);
    add_prop(CONT_I_WEIGHT, 350);
    add_prop(OBJ_I_WEIGHT, 350);
    add_prop(OBJ_I_VOLUME, 350);
    add_prop(CONT_I_VOLUME, 350);
    add_prop(NPC_M_NO_ACCEPT_GIVE, " haughtily ignores you.\n");
}

public int
rename_kitty(string str)
{
    object *oblist;
    object owner = environment(this_object());
    string name;

    if(!strlen(str))
    {
        notify_fail("Name your kitten what?\n");
        return 0;
    }

    str = lower_case(str);
    if (!parse_command(str, all_inventory(owner),
      "[my] %l %s", oblist, name) || !sizeof(NORMAL_ACCESS(oblist, 0, 0)))
    {
        notify_fail("Name what?\n");
        return 0;
    }
    else if (gChangedName)
    {
        notify_fail("The " + short() + " has already had " +
            query_possessive() + " name changed once.\n");
        return 0;
    }
    else if (member_array(this_object(), oblist) == -1)
    {
        notify_fail("Name what?\n");
        return 0;
    }
    else if (!strlen(name))
    {
        notify_fail("Name your kitten what?\n");
        return 0;
    } 
    else if (strlen(name) > 11)
    {
        notify_fail("That's not an appropriate name for a kitten.\n");
        return 0;
    }
    else if (SECURITY->query_banished(name) ||
        SECURITY->exist_player(name))
    {
        notify_fail(capitalize(name) + " has been banished for use. " +
            "Please choose another name.\n");
        return 0;
    }

    write("You change the " + short() + "'s collar, and name " +
        query_objective() + " " + capitalize(name) + ".\n");
    say(QCTNAME(this_player()) + " changes " + short() + "'s collar, and " +
        "names " + query_objective() + " " + capitalize(name) + ".\n");
    remove_name(query_name());
    set_name(name);
    gName = name;
    gChangedName = 1;
    return 1;
}

void
init_living()
{
    ::init_living();

    add_action(rename_kitty, "rename");
}
