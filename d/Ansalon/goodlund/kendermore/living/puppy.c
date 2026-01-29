/* Puppy in Kendermore, Gwyneth, June 12, 1999 */

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
inherit "/std/act/domove";

/* Randomizes the puppy's colour */

string *colour=({"brown", "grey", "spotted", "black", "white", "tan"});
string gName;
int gChangedName = 0;

public string
add_puppy_name(string colr)
{
    if (query_gender() == G_MALE)
    {
        switch(colr)
        {
        case "brown":
            gName = "chip";
            break;
        case "grey":
            gName = "wolf";
            break;
        case "spotted":
            gName = "spot";
            break;
        case "white":
            gName = "otis";
            break;
        case "black":
            gName = "bandit";
            break;
        default:
            gName = "cookie";
            break;
        }
    }
    else
    {
        switch(colr)
        {
        case "brown":
            gName = "daisy";
            break;
        case "grey":
            gName = "smokey";
            break;
        case "spotted":
            gName = "pebbles";
            break;
        case "white":
            gName = "lilly";
            break;
        case "black":
            gName = "dancer";
            break;
        default:
            gName = "honey";
            break;
        }
    }
 
    return gName;
}

public string
long_desc(string colr)
{
    string pup_his = query_possessive();

    return("This " + colr + " puppy has boundless energy, a perfect " +
        "companion for a kender! Chasing " + pup_his + " tail and barking " +
        "seem to be " + pup_his + " favourite activities. " + 
        capitalize(query_pronoun()) + " has a collar around " + pup_his + 
        " neck, and the tags on it read, '" + capitalize(gName) + "'." +
        (gChangedName ? "" : " Perhaps you can rename the puppy.") + "\n");
}

void
create_creature()
{
    string colr = colour[random(6)];

    set_gender(random(2));
    set_race_name("puppy");
    set_adj(colr);
    add_puppy_name(colr);
    set_name(gName);
    add_name("animal");
    set_long(&long_desc(colr));

    set_stats(({17,17,17,6,6,17}));

    set_hp(2100);
    set_alignment(0);
    set_knight_prestige(-5);

    NEVERKNOWN;

    set_act_time(15);
    add_act("emote wags "+HIS(TO)+" tail.");
    add_act("emote barks playfully.");
    add_act("emote bites at your heels.");
    add_act("emote looks at you, hoping for a scrap of food.");

    set_attack_unarmed(1, 15, 10, W_BLUDGEON, 25, "left paw");
    set_attack_unarmed(1, 15, 10, W_BLUDGEON, 25, "right paw");
    set_attack_unarmed(2, 20, 8, W_IMPALE, 20, "teeth");

    set_hitloc_unarmed(1, 4, 80, "body");
    set_hitloc_unarmed(2, 3, 10, "head");

    set_random_move(20);
    set_restrain_path(KROOM);
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(OBJ_M_NO_GET, 0); /* Can be picked up */
    add_prop(OBJ_M_NO_DROP, 0);
    add_prop(CONT_I_WEIGHT, 700);
    add_prop(OBJ_I_WEIGHT, 700);
    add_prop(CONT_I_VOLUME, 700);
    add_prop(OBJ_I_VOLUME, 700);
    add_prop(NPC_M_NO_ACCEPT_GIVE, " barks loudly and chases "+HIS(TO)+" tail. "+HE(TO)+" " + 
        "seems more interested in chasing "+HIS(TO)+" tail than anything else!\n");
}

public int
rename_pup(string str)
{
    object *oblist;
    object owner = environment(this_object());
    string name;
 
    if(!strlen(str))
    {
        notify_fail("Name your pet what?\n");
        return 0;
    }
 
    str = lower_case(str);
    if (!parse_command(str, all_inventory(owner), "[my] %l %s",
      oblist, name) || !sizeof(NORMAL_ACCESS(oblist, 0, 0)))
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
        notify_fail("Name your pet what?\n");
        return 0;
    } 
    else if (strlen(name) > 11)
    {
        notify_fail("That's not an appropriate name for a pet.\n");
        return 0;
    }
    else if (SECURITY->query_banished(name) ||
      SECURITY->exist_player(name))
    {
        notify_fail(capitalize(name) + " has been banished for use. " +
            "Please choose another name.\n");
        return 0;
    }
 
    write("You change " + short() + "'s collar, and name " +
        query_objective() + " " + capitalize(name) + ".\n");
    say(QCTNAME(this_player()) + " changes " + short() + "'s collar, and " +
        "names " + query_objective() + " " + capitalize(name) + ".\n");
    remove_name(query_name());
    set_name(name);
    gName = name;
    gChangedName = 1;
    return 1;
}

public void
init_living()
{
    ::init_living();

    add_action(rename_pup, "rename");
}
