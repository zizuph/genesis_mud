/*
 Horses for the Noldor
 By, Palmer
 Date: December 2002

 Note: To update the adjectives and horse names available to players
 see this primitive tool: /d/Shire/rivendell/steeds/create_data.c

 Horse names can only be used once and should be banished so players
 can't use them.
 */


inherit "/d/Shire/bree/rooms/town/stable/obj/steed_base";
inherit "/std/act/action";
inherit "/std/act/chat";
inherit "/lib/commands";
inherit "/d/Shire/bree/rooms/town/stable/obj/bree_saddlebag";
inherit "/d/Shire/bree/rooms/town/stable/obj/horse_bells";

#include <wa_types.h>
#include <adverbs.h>
#include <const.h>
#include "/d/Shire/sys/defs.h"
#include "imladris_stables.h"

/* Function Prototypes */
public void add_desc(string *saved_data); // Set short, gender, name from owner's saved data
public void add_acts();
public string long_desc(); // Adds saddlebag and ankle bells to long_desc
public void pet_horse(object who, string emote);
public int hgallop(string str);
public int hnice(string str);
public string short_old(); // returns short() without "player riding on him"

/* Globals */
string Desc1, Desc2;
string Short_desc;  // holds short() without "player riding on him"
int Hgallop;        // Sets whether horse is walking or charging
int Hbells;         // Horse is wearing bells
int Nice = 1;       // Horse is nice to people when they touch it


void
create_steed()
{
    add_name(({"_noldor_steed", "_steed_"}));

    set_stats(({180, 150, 250, 40, 40, 150}));
    set_skill(SS_CLIMB, 25);
    set_skill(SS_UNARM_COMBAT, 75);
    set_skill(SS_DEFENCE, 70);
    set_skill(SS_SWIM, 40);
    set_skill(SS_AWARENESS, 40);
    set_long(&long_desc());

    set_m_in("comes galloping in");
    set_m_out("gallops");

    set_rider_object_file("/d/Shire/bree/rooms/town/stable/obj/rider_object");
    set_leader_object_file(IMLADRIS_STABLES_DIR + "imladris_leader_object");

    set_allowed_food(({"oats", "apple", "hay", "sugarcube"}));

    allow_mounted_combat(1);
    set_no_trans(1);
    set_max_riders(1);
    set_stuffed(TO->query_prop(LIVE_I_MAX_EAT));
    set_soaked(TO->query_prop(LIVE_I_MAX_DRINK));
}

/*
  long_desc()
  Concatonates long desc from misc adjectives
  and random gender from add_desc()

  Arguments: None
  Returns:   string - long description of steed
 */

string
long_desc()
{
    string text;

    text = "A " + Desc1 + " " + TO->query_real_name() +
    " with a long flowing mane. A small star is on " + query_possessive() +
    " forehead above intelligent eyes which seem to be " +
    "contemplating your inner being. " + capitalize(query_possessive()) + " lustrous " +
    Desc2 + " coat is well-groomed. This horse possesses a beauty and " +
    "commanding disposition only the Noldor could have bred. ";

    if (Hbells)
    {
     text = text + " Fastened to the ankles are jingly bells.";
    }

    if ((TO->query_leader())->query_name() == TP->query_name() ||
        (TO->query_driver())->query_name() == TP->query_name())
    {
        return text + " Do 'hhelp' to see emotes and commands.\n";
    }
    return text + "\n";
}


/*
  add_desc()
  Sets gender, name, pname from player's saved mapping

  Arguments: string array - Saved data from mapping for horse desc, gender and name
  Returns:   None
 */

public void
add_desc(string *saved_data)
{
    string gender, name;

    Desc1 = saved_data[0];
    Desc2 = saved_data[1];
    gender = saved_data[2];
    name = saved_data[3];
    if (gender == "male")
    {
        set_gender(0);
    }
    else
    {
        set_gender(1);
    }
    set_pname(({"horses", "steeds"}));

    set_adj(({Desc1, Desc2}));
    set_short(Desc1 + " " + Desc2 + " " + TO->query_real_name());
    Short_desc = short();
    add_name(lower_case(name));
    set_living_name(lower_case(name));
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


/*
  has_bells()
  Changes horses long description to show its wearing bells,
  also adds bells to m_out, m_in messages.

  Arguments: None
  Returns: None
 */
void
has_bells()
{
    Hbells = 1;
    set_long(&long_desc());
}


/*
  has_bells()
  Changes horses long description if bells are removed,
  also resets m_out, m_in messages to remove bells.

  Arguments: None
  Returns: None
 */
void
has_no_bells()
{
   Hbells = 0;
   set_long(&long_desc());
}


/*
  hgallop()
  Change your horse's messages to gallop/charge

  Arguments: string (on/off)
  Returns:   0=fail 1=succeed
 */

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


/*
  hnice()
  Make your horse nuzzle someone when touched or bite someong when touched

  Arguments: string (on/off)
  Returns:   0=fail 1=succeed
 */

int
hnice(string str)
{
    if ((TO->query_driver())->query_name() != TP->query_name())
    {
        if ((TO->query_leader())->query_name() != TP->query_name())
        {
            return 0;
        }
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


/*
  query_rider_m_in()
  Sets m_in to ride/gallop with or without bells

  Arguments: object rider
  Returns:   string - the m_in message
 */

public string
query_rider_m_in(object rider)
{
    if (!Hgallop)
    {
        if (Hbells)
        {
            return "rides in on " + LANG_ADDART(steed_short()) + " with bells jingling";
        }
        return "rides in on " + LANG_ADDART(steed_short());
    }


    if (Hbells)
        {
        return "charges in on " + LANG_ADDART(steed_short()) + " with bells jingling";
        }
    return "charges in on " + LANG_ADDART(steed_short());
}


/*
  query_rider_m_out()
  Sets m_out to ride/gallop with or without bells

  Arguments: object rider
  Returns:   string - the m_out message
 */
public string
query_rider_m_out(object rider)
{

    if (!Hgallop)
    {
    if (Hbells)
    {
        return "rides " + rider->query_possessive() + " " + steed_short() + " with bells jingling";
    }
    return "rides " + rider->query_possessive() + " " + steed_short();
    }

    if (Hbells)
    {
    return "charges " + rider->query_possessive() + " " + steed_short() + " with bells jingling";
    }
    return "charges " + rider->query_possessive() + " " + steed_short();
}

/*
  add_acts()
  Sets random add_acts

  Arguments: None
  Returns:   None
 */

void
add_acts()
{
    string act1, act2, act3, act4, act5, act6;
    act1 = "emote suddenly snorts, and tosses "+ query_possessive() + " flowing mane.";

    act2 = "emote swings " + query_possessive() + " tail to the side, slapping " +
            query_possessive() + " flank.";

    act3 = "emote stomps " + query_possessive() + " hoof on the ground, neighing " +
            "softly.";

    act4 = "emote lowers " + query_possessive() + " head, tossing " +
            query_possessive() + " flowing mane from one side to the other.";


    act5 = "emote throws back " + query_possessive() + " head and whinnies loudly.";

    act6 = "emote tosses " + query_possessive() + " head around and snorts "+
            "loudly.";

    set_act_time(5);
    add_act(act1);
    add_act(act2);
    add_act(act3);
    add_act(act4);
    add_act(act5);
    add_act(act6);
}


/*
  emote_hook()
  Catches player's touching horse in order to react to them

  Arguments: string emote, object actor, string adverb, object *oblist, int cmd_attr, int target
  Returns:   None
 */

void
emote_hook(string emote, object actor, string adverb, object *oblist, int cmd_attr, int target)
{
    if (!target) /* Only make horse react if its the one getting touched */
    {
        return;
    }

    if (actor == query_driver())
    {
        return;
    }

    if (!interactive(actor))  /* Only make horse react if its a player touching it */
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


/*
  pet_horse()
  Shows message when horse is touched.

  Arguments: object who, string emote
  Returns:   None
 */

void
pet_horse(object who, string emote)
{
    if (!Nice)
    {
    write("The " + short() + " swiftly moves its head and bites you after you " +
          emote + " it!\n");
    say("The " + short() + " swiftly moves its head and bites " + QTNAME(who) +
        " after " + HE_SHE(who) + " " + emote + " it!\n");
    }
    else
    {
    write("The " + short() + " nuzzles you playfully.\n");
    say("The " + short() + " nuzzles " + QTNAME(who) + " playfully.\n");
    }
    return;
}


/*
  lead_hook()
  We over-ride base_steed's lead message so only Noldor can lead.

  Arguments: object o (Person trying to lead horse.)
  Returns:   None
 */

void
lead_hook(object o)
{
    if(o->query_guild_name_race() == "Noldor of Imladris")
    {
        o->catch_tell("You take the reins of the " + this_object()->steed_short() + ".\n");
        tell_room(environment(this_object()), QCTNAME(o) + " takes the reins " +
        "of the " + this_object()->steed_short() + ".\n", o);
    }
    else
    {
        o->catch_tell("You take the reins and try to lead the " + this_object()->steed_short() +
        " but it rears up and backs away.\n");
        tell_room(environment(this_object()), QCTNAME(o) + " tries to take the reins " +
        "of the " + this_object()->steed_short() + " but it rears up and backs away.\n", o);
        do_unlead(o, 1);
    }
}


/*
  mount_hook()
  We over-rider steed_base's mount to show the Noldor's flash mountint technique,
  or if its a non-Noldor, they fail miserably.

  Arguments: object o (Person trying to mount).
  Returns:   None
 */

void
mount_hook(object o)
{

    // Make sure an auto-sneaking Ranger doesn't mount horse
    // becaue steed code is bugged and makes horse sneak too.
    // TODO: Figure out how to do this for SS, Thieves and Tricksters.

    if (o->query_autosneak())
    {
        o->catch_tell("Your horse rears back on its hind legs, eyes full of fright! Quit sneaking!\n");

        tell_room(environment(TO), "The " + short_old() + " rears back on " + HIS_HER(TO) +
        " hind legs, eyes full of fright!\n", o);

        do_dismount(o, 1);
        return;
    }

    if(o->query_guild_name_race() == "Noldor of Imladris")
    {
        o->catch_tell("You leap into the air and land gracefully on the horse.\n");
        tell_room(environment(this_object()), QCTNAME(o) + " leaps into the air " +
        "and lands gracefully on the " + this_object()->steed_short() + ".\n", o);
    }
    else
    {
        if ((TO->query_driver())->query_guild_name_race() == "Noldor of Imladris")
        {
            o->catch_tell("You climb on the horse.\n");
            tell_room(environment(this_object()), QCTNAME(o) + " mounts the " +
            this_object()->steed_short() + ".\n", o);
        }
        else
        {
            o->catch_tell("You try to climb on the horse but it throws you off.\n");
            do_dismount(o, 1);
            tell_room(environment(this_object()), QCTNAME(o) + " tries to mount the " +
            this_object()->steed_short() + " but it throws " + HIM_HER(o) + " off.\n", o);
        }
    }
}


/*
  dismount_hook()
  Over-ride steed_base's dismount msg if Noldor and show them gracefully slip off the horse.

  Arguments: object o (Person dismounting)
  Returns:   None
 */


void
dismount_hook(object o)
{
    if(o->query_guild_name_race() == "Noldor of Imladris")
    {
        o->catch_tell("You gracefully climb off the " + this_object()->steed_short() + ".\n");
        tell_room(environment(this_object()), QCTNAME(o) + " gracefully climbs " +
        "off the " + this_object()->steed_short() + ".\n", o);
    }
    else // For the less graceful:
    {
        o->catch_tell("You dismount the " + this_object()->steed_short() + ".\n");
        tell_room(environment(this_object()), QCTNAME(o) + " dismounts the " +
        this_object()->steed_short() + ".\n", o);
    }
}



void
init_living()
{
   add_action("hnice", "hnice");

   /* Saddlebag */
   add_action(do_strap, "strap");
   add_action(do_unstrap, "unstrap");
   add_action(do_fill, "fill");
   add_action(do_empty, "empty");
   add_action(do_close, "close");
   add_action(do_open, "open");

   /* Ankle bells: */
   add_action(do_fasten, "fasten");
   add_action(do_unfasten, "unfasten");

    ::init_living();
}
