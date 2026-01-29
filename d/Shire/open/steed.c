/*
  /d/Shire/bree/rooms/town/stable/obj/bree_steed.c
 
  Steed object produces randomly described horse or pony for the Bree Stables
 
  By, Palmer
  Date: December 2002
 
  ChangeLog:
  April 28, 2004 - Palmer
   Added logger for killing steeds so they can't rent anymore and
   get booted from Equestrian Club.
  
  May 22, 2004 - Finwe
  Fixed minor typos

  August 6, 2004 - Finwe
  Added more horse adjs

  September 19, 2004
  Added more horse colors, faces, and leg descriptions.
   
  Wish list:
    - Horses leave hoofprints instead of player leaving tracks behind.
    - Horse always nice to owner regardless of hnice status
    -- Finwe, August 2004 
  
  
 */

#include <cmdparse.h>
#include <composite.h>
#include <macros.h>
#include <wa_types.h>
#include <adverbs.h>
#include <const.h>
#include "/d/Shire/sys/defs.h"
#include "../bree_stables.h"
#include "/d/Genesis/steed/new/default.h"
#include "/d/Genesis/steed/new/steed.h"

// inherit "/d/Genesis/steed/new/steed";
inherit "/d/Shire/bree/rooms/town/stable/obj/steed_base.c";
inherit "/std/act/action";
inherit "/std/act/chat";
inherit "/lib/commands";
inherit "/d/Shire/bree/rooms/town/stable/obj/bree_saddlebag";
inherit "/d/Shire/bree/rooms/town/stable/obj/horse_bells";
inherit "/d/Shire/lib/kill_logger";

// Some macros
#define FAIL(x)   { notify_fail(x); return 0; }
#define NF(x)     notify_fail(x)
#define TP        this_player()
#define HE(x)     (x)->query_pronoun()


/* Globals */
int Hgallop;
int Nice = 1; // Horse is nice to people when they touch it
int Hbells;
string desc1, desc2, body_color, tail_color, face_style, leg_color;
string Short_desc;
int face_num = random(5),
    leg_num = random(5);

/* Function prototypes */
public void add_desc();
public void add_acts();
public void pet_horse(object who, string emote);
public string long_desc();   /* Adds saddlebag and ankle bells to long_desc*/
public int hgallop(string str);
public int hnice(string str);
public void stuff_soak();
public string short_old();

void
create_steed()
{
    add_name("_steed_");
    id("_steed_");
    set_gender(random(2));

    set_stats(({180, 150, 250, 40, 40, 150}));
    set_skill(SS_CLIMB, 40);
    set_skill(SS_UNARM_COMBAT, 75);
    set_skill(SS_DEFENCE, 70);
    set_skill(SS_SWIM, 40);
    set_skill(SS_AWARENESS, 40);
    set_skill(SS_LOC_SENSE, 40);
    add_desc();
    set_long(&long_desc());

    set_m_in("comes galloping in");
    set_m_out("gallops");

    set_rider_object_file(BREE_STABLES_OBJ_DIR + "rider_object");
    set_leader_object_file(BREE_STABLES_OBJ_DIR + "bree_leader_object");

    set_allowed_food(({"oats", "apple", "hay", "sugarcube"}));

    allow_mounted_combat(1);
    set_kill_log_name("steed_killers");
    set_kill_log_size(30000);

    set_no_trans(1);
    set_max_riders(1);
    stuff_soak();
    add_acts();
}


/*
  short_old()
  returns this_object->short() without "player riding on him"
  We need this because when you examine the horse with a player
  mounted, the short() looks like "A big white horse with Soandso riding it."

  Arguments:
  Returns:   string
 */

public string
short_old()
{
    return Short_desc;
}


public void
show_clones()
{
    object *ob_list;
    ob_list = object_clones(find_object("/d/Shire/bree/rooms/town/stable/obj/steed"));
    dump_array(ob_list);
}

public void
stuff_soak()
{
    set_stuffed(TO->query_prop(LIVE_I_MAX_EAT));
    set_soaked(TO->query_prop(LIVE_I_MAX_DRINK));

}

/*
 * Concatconates long desc from misc adjectives
 * and random gender from add_desc()
 *
 * Arguments:     None
 * Returns:       Long description of steed
 */

string
long_desc()
{
    string text = "This is a " + short() + " with a " + body_color + 
        " coat. The tail and mane are " + tail_color + ", with the mane " +
        "braided in the style of " + TO->query_real_name() + 
        " from Rohan. The face of the " + TO->query_real_name() + " " + 
        face_style + "Its legs are " + leg_color + "The lustrous coat " +
        "is proof the " + TO->query_real_name() + " is well cared for. ";
    if (Hbells)
    {
     text = text + " Fastened to the ankles are bells that jingle and ring. ";
    }

    if ((TO->query_leader())->query_name() == TP->query_name() ||
        (TO->query_driver())->query_name() == TP->query_name())
    {
        return text + additional_longdesc() + 
            " Do 'hhelp' to see emotes and commands.\n";
    }
    return text + additional_longdesc() + "\n";
}


/*

Generates adjectives for set_adj() and set_short() from misc adjectives
Arguments:     None
Returns:            None

*/

public void
add_desc()
{
    int steed_type;
    string *adj1, *adj2;


    adj1 = ({"fleet-footed", "gentle", "haughty", "high-spirited", "muscular", "noble", "proud", "sleek", "splendid", "swift"});
    adj2 = ({"bay", "brown", "buckskin", "chestnut", "chocolate", "dun", "grullo", "piebald", "sorrel", "tan"});

// so there are more horses than ponies in the corral
    steed_type = random(5);
    if (steed_type == 0)
    {
        set_name(({"pony", "steed"}));
        set_pname(({"ponies", "ponys", "steeds"}));
        remove_name("horse");
    }
    else
    {
        set_name(({"horse", "steed"}));
        set_pname(({"horses", "steeds"}));
    }

    desc1 = adj1[random(sizeof(adj1))];
    desc2 = adj2[random(sizeof(adj2))];

    set_adj(({desc1, desc2}));
    set_short(desc1 + " " + desc2 + " " + TO->query_real_name());


// sets descriptions based on color of steed
    switch (desc2)
    {
        case "brown":
        case "bay":
        case "chocolate":
        case "tan":
        {
            body_color = "brown colored";
            tail_color = "black";
            break;
        }
        case "buckskin":
        {
            body_color = "yellowish colored";
            tail_color = "black";
            break;
        }
        case "chestnut":
        {
            body_color = "dark red";
            tail_color = "brownish-red";
            break;
        }
        case "dun":
        {
            body_color = "gold in color";
            tail_color = "brown";
            break;
        }
        case "grullo":
        {
            body_color = "smoky";
            tail_color = "black";
            break;
        }
        case "piebald":
        {
            body_color = "white with irregular patches of black";
            tail_color = "brown";
            break;
        }
        case "sorrel":
        {
            body_color = "copper-red in color";
            tail_color = "flaxen";
            break;
        }
    }

// sets face color
    switch (face_num)
    {
        case 0: // bald
        {
            face_style = "is white. It extends out and around the eyes, " +
                "extending down to the upper lip and around the nostrils. ";
            break;
        }
        case 1: // star
        {   face_style = "has a white mark on the forehead. ";
            break;
        }
        case 2: // star and strip
        {   face_style = "has a narrow white stripe that runs from " +
                "the white mark on the forehead to the top of the nose. ";
            break;
        }
        case 3: // star, strip and snip
        {
            face_style = "has a narrow white stripe, running from the " +
                "white mark on the forehead to the muzzle. ";
            break;
        }
        case 4: // strip
        {
            face_style = "has a small stripe between the muzzle. ";
            break;
        }        
    }

// leg color
    switch(leg_num)
    {
        case 0: // coronet
        {   leg_color = body_color + " except for a white ring " +
                "above each hoof. ";
            break;
        }
        case 1: // sock
        {   leg_color = "white, which extends from the hoof up to " +
                "the knees. ";
            break;
        }
        case 2: // stocking
        {   leg_color = "white from the hoof up past the knees. ";
            break;
        }
        case 3: // heel spots
        {   leg_color = body_color + ", except for a few large " +
                "white spots on the heels. ";
            break;
        }
        case 4: // zebra
        {   leg_color = body_color + ", with varying sized rings " +
                "of dark hair around the legs. ";
            break;
        }
    }
    
    Short_desc = short();
}

void
has_bells()
{
    Hbells = 1;
    set_long(&long_desc());
}

void
has_no_bells()
{
   Hbells = 0;
   set_long(&long_desc());
}

int
hgallop(string str)
{
    if ((TO->query_driver())->query_name() != TP->query_name())
    {
        return 0;
    }
    if (str != "on" && str != "off")
    {
        notify_fail("hgallop on/off?\n");
        return 0;
    }
    if (str == "on")
    {
        Hgallop = 1;
        write("Your horse will gallop from now.\n");
        query_driver()->steed_is_updated();
        return 1;
    }
    if (str == "off")
    {
        Hgallop = 0;
        write("Your horse will not gallop from now.\n");
        query_driver()->steed_is_updated();
        return 1;
    }
}

int
hnice(string str)
{
    if ((TO->query_driver())->query_name() != TP->query_name())
    {
        return 0;
    }
    if (str != "on" && str != "off")
    {
        notify_fail("hnice on/off?\n");
        return 0;
    }
    if (str == "on")
    {
        Nice = 1;
        write("Your horse will be nice when touched.\n");
        return 1;
    }
    if (str == "off")
    {
        Nice = 0;
        write("Your horse will not be nice when touched.\n");
        return 1;
    }
}

public string
query_rider_m_in(object rider)
{
    if (!Hgallop)
    {
        if (Hbells)
        {
            return "rides in on " + LANG_ADDART(steed_short()) + 
            " with bells jingling";
        }
        return "rides in on " + LANG_ADDART(steed_short());
    }


    if (Hbells)
        {
        return "charges in on " + LANG_ADDART(steed_short()) + 
        " with bells jingling";
        }
    return "charges in on " + LANG_ADDART(steed_short());
}

public string
query_rider_m_out(object rider)
{

    if (!Hgallop)
    {
    if (Hbells)
    {
        return "rides " + rider->query_possessive() + " " + steed_short() + 
        " with bells jingling";
    }
    return "rides " + rider->query_possessive() + " " + steed_short();
    }

    if (Hbells)
    {
    return "charges " + rider->query_possessive() + " " + steed_short() + 
    " with bells jingling";
    }
    return "charges " + rider->query_possessive() + " " + steed_short();
}

void
add_acts()
{
    set_act_time(5);
    add_act("emote suddenly snorts and tosses "+ HIS_HER(TO) + " braided mane.");
    add_act("emote swings "+HIS_HER(TO)+" tail to the side, slapping " +
            HIS_HER(TO)+" flank.");
    add_act("emote stomps "+HIS_HER(TO)+" hoof on the ground, neighing " +
            "softly.");
    add_act("emote lowers " + HIS_HER(TO) + " head, tossing " +
            HIS_HER(TO) + " braided mane from one side to the other.");
    add_act("emote throws back " + HIS_HER(TO) +
            " head and whinnies loudly.");
    add_act("emote tosses "+HIS_HER(TO)+" head around and snorts "+
            "loudly.");
}

void
emote_hook(string emote, object actor, string adverb, object *oblist, int cmd_attr, int target)
{
    // Only make horse react if its the one getting touched
    if (!target)
    {
        return;
    }

    // The person mounted can't be nuzzled or bit by the horse
    if (actor == TO->query_driver())
    {
        return;
    }

    // Make sure its a player. We don't want horses infinitely nuzzling each other.
    if (!interactive(actor))
    {
        return;
    }

    switch(emote)
    {
    case "pet":
    case "snuggle":
    case "nuzzle":
    case "scratch":
    case "ruffle":
    case "hug":
    case "pat":
    case "kiss":
        pet_horse(TP, emote);
    default:
        break;
    }
}


void
pet_horse(object who, string emote)
{
    if (!Nice)
    {
    write("The " + short() + " swiftly moves its head and bites you after you " +
          emote + " it!\n");
    say("The " + short() + " swiftly moves its head and bites " + QTNAME(who) +
        " after " + HE_SHE(TO) + " " + emote + " it!\n");
    }
    else
    {
    write("The " + short() + " nuzzles you playfully.\n");
    say("The " + short() + " nuzzles " + QTNAME(who) + " playfully.\n");
    }

    return;
}


void
mount_hook(object o)
{

    // Make sure an auto-sneaking player doesn't mount horse
    // becaue steed code is bugged and makes horse sneak too.
    if (o->query_autosneak())
    {
        o->catch_tell("The " + short_old() + " rears back on " +
        HIS_HER(TO) + " hind legs, eyes full of fright! Quit sneaking.\n");
        tell_room(environment(TO), "The " + short_old() + " rears back on " +
        HIS_HER(TO) +
        " hind legs, eyes full of fright!\n", o);
        do_dismount(o, 1);
        return;
    }
    ::mount_hook(o);
}


/* Function name: lead
 * Description:   lead this steed somewhere
 * Arguments:     string - the steed to lead
 * Returns:       int 1 if successful
 */

/*
public int
lead(string s)
{
    object *o_list;
    object steed, my_horse;
    int sts, i;

    if (
        (!s) ||
        (!sizeof(
            o_list =
            FIND_STR_IN_ARR(s, all_inventory(environment(this_player()))))
            )
        )
    {
        return 0;
    }

    if (sizeof(o_list) > 1)
    {
        return 0;
    }

    // Palmer says:
    // BAD BAD BAD. It made you lead the first horse in the list every time.
    // steed = o_list[0];

    o_list = filter(o_list[1..], &->is_steed());

    // Try mounting the horse defined in player's property
    // _my_horse which is set when you rent the horse in Bree.
    my_horse = TP->query_prop("_my_horse");
    if (objectp(my_horse))
    {
        for (i = 0; i < sizeof(o_list); i++)
        {
            if (my_horse == o_list[i])
            {
                steed = o_list[i];
                break;
            }
        }
    }
    else
    {
        // If player doesn't own a horse (i.e. have _my_horse set) try
        // mounting the first horse, then the second etc
        for (i = 0; i < sizeof(o_list); i++)
        {
            steed = o_list[i];
            break;
        }
    }

    // check if it's a steed
    if (!steed->is_steed())
    {
        return 0;
    }

    // check if we have a leader already

    if (objectp(steed->query_leader()))
    {
        // Palmer Jan 2003 added check to show that YOU are already leading,
        // not just "someone"
        if ((steed->query_leader()) == this_player())
        {
            FAIL("You're already leading the " + steed->short() + ".\n");
        }
        else
        {
            FAIL("The " + steed->short() + " is already lead by someone.\n");
        }
    }

    //Commented by Trofast Dec 1999 UNCOMMENTED by Palmer
    // Don't allow leading when living is riding a steed
        if (objectp(this_player()->query_prop(LIVE_O_STEED)))
            FAIL("You cannot lead a " + steed->query_race_name() +
            " while you're riding.\n");

    // Don't allow to lead steeds with riders on them
    if (steed->query_has_riders())
    {
        FAIL("You cannot lead a " + steed->query_race_name() +
        " with riders on " + steed->query_objective() + ".\n");
    }

    sts = steed->do_lead(this_player());
    steed->handle_lead_status(sts, this_player());
    if (STEED_STS_FAIL(sts))
    {
        notify_fail("");
    }
    return STEED_STS_SUCCESS(sts);
}
*/

/* Function name: mount
 * Description:   Try to mount a steed, does a syntax check and a check
 *                if the object is a steed (using the is_steed() function)
 *                and then calls do_mount in the steed object
 *                We are masking mount() in steed_base.c so we can now
 *                try to mount TP->query_prop("_my_horse") by default
 *
 * Arguments:     string - the object description
 * Returns:       1 - if successful
 */
public int
mount(string s)
{
    mixed *o_list;
    int i, index;
    int sts;
    object steed_to_mount = 0;
    object my_horse;

    if (CAN_SEE_IN_ROOM(this_player()) <= 0)
    {
        return light_fail("mount");
    }

    if (this_player()->query_prop(LIVE_O_STEED))
    {
        FAIL("You are already mounted.\n");
    }

    if (
        (!s) ||
        (!parse_command(s, all_inventory(environment(this_player())),
            "%l", o_list))
        )
    {
        return 0;
    }

    index = o_list[0];

    if (index == 0)   // don't allow "mount all horses" or "mount horses"
    {
        return 0;
    }
    if (index > 0)    // allow "mount horse"
    {
        if (index > 1) // don't allow "mount two horses"
        {
            return 0;
        }

        o_list = filter(o_list[1..], &->is_steed());

        // Try mounting the horse defined in player's property
        // _my_horse which is set when you rent the horse in Bree.
        my_horse = TP->query_prop("_my_horse");
        if (objectp(my_horse))
        {
            for (i = 0; i < sizeof(o_list); i++)
            {
                if (my_horse == o_list[i])
                {
                    steed_to_mount = o_list[i];
                    break;
                }
            }
        }
        else
        {
            // If player doesn't own a horse (i.e. have _my_horse set) try
            // mounting the first horse, then the second etc
            for (i = 0; i < sizeof(o_list); i++)
            {
                steed_to_mount = o_list[i];
                break;
            }
        }

        if (!steed_to_mount)
        {
            return 0;
        }

    }
    else   // allow "mount second horse"
    {
        if (!o_list[-index]->is_steed())
        {
            return 0;
        }
        steed_to_mount = o_list[-index];
    }
    sts = steed_to_mount->do_mount(this_player());
    steed_to_mount->handle_mount_status(sts, this_player());
    if (STEED_STS_FAIL(sts))
    {
        notify_fail("");
    }
    return STEED_STS_SUCCESS(sts);
}

void
init_living()
{
   add_action("hnice", "hnice");

   /* Saddlebag: */
   add_action(do_fill, "fill");
   add_action(do_empty,"empty");
   add_action(do_strap, "strap");
   add_action(do_unstrap, "unstrap");
   add_action(do_close, "close");
   add_action(do_open, "open");

   /* Ankle bells: */
   add_action("do_fasten", "fasten");
   add_action("do_unfasten", "unfasten");

    ::init_living();
}
