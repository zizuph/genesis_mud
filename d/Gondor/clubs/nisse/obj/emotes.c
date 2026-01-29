/*
 *  /d/Gondor/clubs/nisse/soul/emotes.c
 *
 *  This file is included in nisse_soul.c. It contains the emotes for
 *  the Nisse Ohtar club.
 *
 *  Deagol, February 2003
 */

#pragma save_binary
#pragma strict_types

#include <macros.h>
#include <language.h>
#include <files.h>
#include <composite.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/clubs/nisse/nisse_defs.h"

#define OBHIM   (oblist[0]->query_objective())
#define HIS(x)  ((x)->query_possessive())
#define HIM(x)  ((x)->query_objective())
#define HE(x)	((x)->query_pronoun())
#define OBHIS   (oblist[0]->query_possessive())

/*
 *  Function name: add_paint_subloc
 *  Description  : Adds the Nisse subloc, it's called by nipaint emote
 */
void
add_paint_subloc()
{
    if (living(TP))
    {
        TP->add_subloc(NISSE_SUBLOC_ID, this_object());
    }
}

/*
 *  Function name: remove_paint_subloc
 *  Description  : Removes the Nisse subloc, it's called by niclean emote
 */
void
remove_paint_subloc()
{
    if (living(TP))
    {
        TP->remove_subloc(NISSE_SUBLOC_ID, this_object());
    }
}

/*
 *  Function name: show_subloc
 *  Description  : Shows the specific sublocation description for a living
 *  Arguments    : string subloc  - the subloc to display
 *                 object on      - the object to which the subloc is linked
 *                 object for_obj - the object that wants to see the subloc
 *  Returns      : string - the subloc description
 */
string
show_subloc(string subloc, object carrier, object for_obj)
{
    if (carrier->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS) ||
       (subloc != NISSE_SUBLOC_ID))
    {
        return "";
    }

    return ((for_obj == carrier) ? "You have painted your face with the " +
        "battle markings of the Nisse Ohtar" : CAP(HE(carrier)) +
        " has painted " + HIS(carrier) + " face with the battle markings") +
        ".\n";
}

/*
 *  A simple routine to clone a hawk.
 */
void
clone_hawk()
{
    string birthmark_colour = TP->query_nisse_rank();
    
    write("The air around you seems filled with wings as a " +
        birthmark_colour + " hawk plummets from the sky and " +
        "settles carefully on your wrist.\n");
    say("The air around " + QCNAME(TP) + " seems filled with wings " +
        "as a " + birthmark_colour + " hawk plummets from the sky " +
        "and settles carefully on " + POSSESSIVE(TP) + " wrist.\n");
    clone_object(NISSE_OBJ_DIR + "hawk")->move(TP);
}

/*
 *  Function name: niclasp1
 *  Description  : Nisse emote to greet others
 *  Argument     : string str
 *  Returns      : 1 on success, 0 on failure
 */
int
niclasp1(string str)
{
    object	*oblist;
    string	*how;
    string	gender = "sister";
    
    how = parse_adverb(str, "heartily", 1);

    oblist = parse_this(how[0], "%l");

    if (!sizeof(oblist))
    {
        notify_fail("Clasp who <how>?\n");
        return 0;
    }

    if (oblist[0]->query_gender() == G_MALE)
    {
        gender = "brother";
    }
    
    if (sizeof(oblist) != 1)
    {
        actor("You clasp the forearms of",oblist,", greeting them " +
              how[1] + ".");
        all2act(" clasps the forearms of",oblist,", " + how[1] +
                " intoning: Aaya Seler', Aman'na sul tel' dagora.");
        target(" clasps your forearm and " + how[1] + " intones: Greetings " +
               CAP(gender) + ", Blessed be the winds of battle.", oblist);
        return 1;
    }
    
    actor("You clasp the forearm of",oblist,", greeting your " + gender +
          " " + how[1] + ".");
    all2act(" clasps the forearm of",oblist,", " + how[1] + " intoning: " +
            "Aaya Seler', Aman'na sul tel' dagora.");
    target(" clasps your forearm and " + how[1] + " intones: Greetings " +
           CAP(gender) + ", Blessed be the winds of battle.", oblist);
    return 1;
}

/*
 *  Function name: niclasp2
 *  Description  : Nisse emote to greet others
 *  Argument     : string str
 *  Returns      : 1 on success, 0 on failure
 */
int
niclasp2(string str)
{
    object	*oblist;
    string	*how;
    string	gender = "sister";
    
    how = parse_adverb(str, "heartily", 1);
    
    oblist = parse_this(how[0], "%l");

    if (!sizeof(oblist))
    {
        notify_fail("Clasp who <how>?\n");
        return 0;
    }

    if (oblist[0]->query_gender() == G_MALE)
    {
        gender = "brother";
    }
    
    if (sizeof(oblist) != 1)
    {
        actor("You clasp the forearms of",oblist,", kiss their cheeks " +
              "and greet them " + how[1] + ".");
        all2act(" clasps the forearms of",oblist,", kissing their cheeks " +
                "and " + how[1] + " intoning: Aaya Seler', Aman'na sul " +
                "tel' dagora.");
        target(" clasps your forearm, kissing your cheek " + PRONOUN(TP) +
               " " + how[1] + " intones: Greetings " + CAP(gender) +
               ", Blessed be the winds of battle.", oblist);
        return 1;
    }

    actor("You clasp the forearm of",oblist,", kiss " + OBHIS + " cheek " +
          "and greet your " + gender + " " + how[1] + ".");
    all2act(" clasps the forearm of",oblist,", kissing " + OBHIS + " cheek " +
            "and " + how[1] + " intoning: Aaya Seler', Aman'na sul tel' " +
            "dagora.");
    target(" clasps your forearm, kissing your cheek " + PRONOUN(TP) + " " +
           how[1] + " intones: Greetings " + CAP(gender) + ", Blessed be " +
           "the winds of battle.", oblist);
    return 1;
}

/*
 *  Function name: niembrace
 *  Description  : Nisse emote to embrace others
 *  Argument     : string str
 *  Returns      : 1 on success, 0 on failure
 */
int
niembrace(string str)
{
    object	*oblist;
    string	*how;
    
    how = parse_adverb(str, "happily", 1);
    oblist = parse_this(how[0], "%l");
    
    if (!sizeof(oblist))
    {
        notify_fail("Embrace who <how>?\n");
        return 0;
    }

    if (sizeof(oblist) != 1)
    {
        actor("You " + how[1] + " shake hands with",oblist," and pull " +
              "them into a kind embrace.");
        all2act(" " + how[1] + " shakes hands with",oblist," and pulls " +
                "them into a kind embrace.");
        target(" shakes your hand " + how[1] + " and pulls you into " +
               "a kind embrace.", oblist);
        return 1;
    }

    actor("You shake",oblist,"'s hand " + how[1] + " and pull " + OBHIM +
          " into a kind embrace.");
    all2act(" shakes",oblist,"'s hand " + how[1] + " and pulls " + OBHIM +
            " into a kind embrace.");
    target(" shakes your hand " + how[1] + " and pulls you into " +
           "a kind embrace.", oblist);
    return 1;
}

/*
 *  Function name: ninod
 *  Description  : Nisse emote to nod at enemy
 *  Argument     : string str
 *  Returns      : 1 on success, 0 on failure
 */
int
ninod(string str)
{
    object	*oblist;
    
    oblist = parse_this(str, "[at] %l");
    
    if (!sizeof(oblist))
    {
        notify_fail("Nod at who?\n");
        return 0;
    }

    actor("You nod coldly at",oblist,", uttering: You are less than bull " +
          "spit on the waters, enemy!");
    all2act(" nods coldly at",oblist,", uttering: Lle n'ner puita tel' " +
            "mundo 'no i'alu, goth!");
    target(" nods coldly at you, uttering something you do not understand, " +
           "but you feel very insulted.", oblist);
    return 1;
}

/*
 *  Function name: niwarcry
 *  Description  : Nisse emote to do a warcry
 *  Returns      : always 1
 */
int
niwarcry()
{
    write("You throw yourself in the fray, crying: Blessed be the winds " +
          "of the battle!\n");
    say(QCTNAME(TP) + " throws " + HIM(TP) + "self in the fray, exclaming: " +
        "Aman'na sul tel' Dagora!\n");
    return 1;
}

/*
 *  Function name: nitear
 *  Description  : Nisse emote to show your sorrow
 *  Argument     : string str
 *  Returns      : 1 on success, 0 on failure
 */
int
nitear(string str)
{
    object	*oblist;
                
    if (!strlen(str))
    {
        write("A single tear runs down your cheek.\n");
        say(QCTNAME(TP) + "'s face softens as a single tear runs down " +
            POSSESSIVE(TP) + " cheek.\n");
        return 1;
    }
    
    oblist = parse_this(str, "[to] %l");
    
    if (!sizeof(oblist))
    {
        notify_fail("Tear to who?\n");
        return 0;
    }

    actor("You turn to",oblist," as a single tear runs down your cheek.");
    all2act(" turns toward",oblist,", falling silent for a moment.");
    target(" turns toward you as a single tear runs down " + POSSESSIVE(TP) +
           " cheek.", oblist);
    return 1;
}

/*
 *  Function name: nibackhand
 *  Description  : Nisse emote to backhand somebody
 *  Argument     : string str
 *  Returns      : 1 on success, 0 on failure
 */
int
nibackhand(string str)
{
    object	*oblist;
    string	*how;
    
    how = parse_adverb(str, "roughly", 1);
    oblist = parse_this(how[0], "%l");
    
    if (!sizeof(oblist))
    {
        notify_fail("Backhand who <how>?\n");
        return 0;
    }
    
    if (sizeof(oblist) != 1)
    {
        notify_fail("You can backhand just one person at a time.\n");
        return 0;
    }

    actor("You backhand",oblist," " + how[1] + " for " + OBHIS +
          " insolence, diminishing " + OBHIM + " to dust.");
    all2act(" backhands",oblist," " + how[1] + " for " + OBHIS +
            " insolence, diminishing " + OBHIM + " to dust.");
    target(" backhands you " + how[1] + " for your insolence, " +
           "diminishing you to dust.", oblist);
    return 1;
}

/*
 *  Function name: nikiss
 *  Description  : Nisse emote to kiss others
 *  Argument     : string str
 *  Returns      : 1 on success, 0 on failure
 */
int
nikiss(string str)
{
    object	*oblist;
    string	*how;

    how = parse_adverb(str, "gently", 1);
    oblist = parse_this(how[0], "%l");

    if (!sizeof(oblist))
    {
        notify_fail("Kiss who <how>?\n");
        return 0;
    }

    actor("You kiss",oblist," " + how[1] + ", making a definite impression.");
    all2act(" kisses",oblist," " + how[1] + ".");
    target(" kisses you " + how[1] + ", " + HIS(TP) + " fingertips " +
           "caressing your cheek, leaving you breathless and " +
           "disoriented.", oblist);
    return 1;
}

/*
 *  Function name: nineck
 *  Description  : Nisse emote to snap a head
 *  Returns      : always 1
 */
int
nineck()
{
    write("You crack the bones in your neck, limbering up for the battle " +
          "to come.\n");
    say(QCTNAME(TP) + " snaps " + HIS(TP) + " head left, then right. You " +
        "hear the bones in her neck crack!\n");
    return 1;
}

/*
 *  Function name: nipeer
 *  Description  : Nisse emote to peer at somebody
 *  Argument     : string str
 *  Returns      : 1 on success, 0 on failure
 */
int
nipeer(string str)
{
    object	*oblist;

    oblist = parse_this(str, "[at] %l");

    if (!sizeof(oblist))
    {
        notify_fail("Peer at who?\n");
        return 0;
    }

    actor("You peer coldly at",oblist,", making it clear " + HE(oblist[0]) +
          " is beneath you.");
    all2act(" peers coldly at",oblist," who seems visibly shaken.");
    target(" peers coldly at you leaving you knowing you have been " +
           "weighed, measured and found hopelessly wanting.", oblist);
    return 1;
}

/*
 *  Function name: nigaze
 *  Description  : Nisse emote to gaze at somebody
 *  Argument     : string str
 *  Returns      : 1 on success, 0 on failure
 */
int
nigaze(string str)
{
    object	*oblist;

    oblist = parse_this(str, "[at] %l");

    if (!sizeof(oblist))
    {
        notify_fail("Gaze at who?\n");
        return 0;
    }

    actor("You gaze at",oblist," with fierce eyes flashing, trying to " +
          "decide what to do.");
    all2act(" gazes fiercely at",oblist,", her eyes flashing with fire.");
    target(" gazes at you with fierce eyes flashing, promising instant " +
           "death or eternal delight.", oblist);
    return 1;
}

/*
 *  Function name: niglance
 *  Description  : Nisse emote to glance at somebody
 *  Argument     : string str
 *  Returns      : 1 on success, 0 on failure
 */
int
niglance(string str)
{
    object	*oblist;

    oblist = parse_this(str, "[at] %l");

    if (!sizeof(oblist))
    {
        notify_fail("Glance at who?\n");
        return 0;
    }

    actor("You glance knowingly at",oblist,", hinting at what you want.");
    all2act(" glances at",oblist," silently.");
    target(" shoots you a knowing glance, " + POSSESSIVE(TP) + " passion " +
           "and experience evident.", oblist);
    return 1;
}

/*
 *  Function name: nisigh
 *  Description  : Nisse emote to sigh
 *  Argument     : string str
 *  Returns      : 1 on success, 0 on failure
 */
int
nisigh(string str)
{
    string      *how;

    how = parse_adverb(str, "unhappily", 1);

    write("You sigh " + how[1] + " but compose yourself quickly.\n");
    say(QCTNAME(TP) + " sighs " + how[1] + ", shadow passes over " +
        POSSESSIVE(TP) + " face, then vanishes, leaving no trace of its " +
        "passing.\n");
    return 1;
}

/*
 *  Function name: niglare
 *  Description  : Nisse emote to glare at somebody
 *  Argument     : string str
 *  Returns      : 1 on success, 0 on failure
 */
int
niglare(string str)
{
    object	*weapons = TP->query_weapon(-1);
    object	*oblist;

    oblist = parse_this(str, "[at] %l");

    if (!sizeof(oblist))
    {
        notify_fail("Glare at who?\n");
        return 0;
    }
    
    if (!sizeof(weapons))
    {
        actor("You glare at",oblist,", muscles tensed, poised to strike.");
        all2act(" glares at",oblist,", a savage kick halted just inches " +
            "from " + OBHIS + " groin.");
        oblist->catch_msg("You contemplate your progeny as " +
            TP->query_name() + " glares at you, a savage kick halted " +
            "just inches from your groin.\n");
        return 1;
    }
    
    actor("You glare at",oblist,", your " + weapons[0]->short() +
          " poised to strike.");
    all2act(" glares at",oblist,", " + POSSESSIVE(TP) +
            " " + weapons[0]->short() + " poised at " + oblist[0]->short() +
            "'s groin.");
    oblist->catch_msg("You contemplate your progeny as " + TP->query_name() +
           " glares at you, " + POSSESSIVE(TP) + " " + weapons[0]->short() +
           " poised at your groin.\n");
    return 1;
}

/*
 *  Function name: nisummon
 *  Description  : Nisse emote to summon a hawk, stature or list
 *  Argument     : string str
 *  Returns      : 1 on success, 0 on failure
 */
int
nisummon(string str)
{
    if (!strlen(str))
    {
        notify_fail("Summon what?\n");
        return 0;
    }
    
    if (str == "stature")
    {
        write("You summon your energies to increase your stature.\n");
        say(QCTNAME(TP) + " summons " + HIS(TP) + " energy, appearing to " +
            "grow taller and stronger before your eyes.\n");
        return 1;
    }

    if (str == "hawk")
    {
        setuid();
        seteuid(getuid());
        
        if (present(NISSE_HAWK_ID, TP))
        {
            notify_fail("Your hawk is with you already.\n");
            return 0;
        }
        
        write("You summon your energies to call your hawk.\n");
        say(QCTNAME(TP) + " summons " + HIS(TP) + " energy, " + HIS(TP) +
            " eyes gazing skyward.\n");
        set_alarm(5.0, 0.0, &clone_hawk());
        return 1;
    }

    notify_fail("Summon what?\n");
    return 0;
}

/*
 *  Function name: nihawk
 *  Description  : Nisse emote to make your hawk do some actions with
 *  Argument     : string str
 *  Returns      : 1 on success, 0 on failure
 */
int
nihawk(string str)
{
    string *parts;
    object *oblist;
    string switch_word;
    string hawk_short = present(NISSE_HAWK_ID, TP)->query_short();

    setuid();
    seteuid(getuid());

    oblist = parse_this(str, "[stare] [at] %l");
    
    if (!present(NISSE_HAWK_ID, TP))
    {
        notify_fail("You are not carrying a hawk.\n");
        return 0;
    }

    if (!strlen(str))
    {
        notify_fail("Let your hawk do what?\n");
        return 0;
    }
    
    parts = explode(str, " ");
    switch_word = parts[0];
    str = implode(parts[1..], " ");

    if (parts[0] == "hood")
    {
        if (!present(NISSE_HOOD_ID, TP))
        {
            notify_fail("You do not have a hood.\n");
            return 0;
        }
        
        if (present(NISSE_HAWK_ID, TP)->query_hooded())
        {
            notify_fail("Your hawk is wearing a hood already.\n");
            return 0;
        }
        
        present(NISSE_HOOD_ID, TP)->wear_hood();
        return 1;
    }
    
    if (parts[0] == "unhood")
    {
        if (!present(NISSE_HAWK_ID, TP)->query_hooded())
        {
            notify_fail("Your hawk is not wearing a hood.\n");
            return 0;
        }
        
        present(NISSE_HOOD_ID, TP)->remove_hood();
        return 1;
    }

    if (parts[0] == "attach")
    {
        if (!present(NISSE_JESSES_ID, TP))
        {
            notify_fail("You do not have the jesses.\n");
            return 0;
        }
        
        if (present(NISSE_HAWK_ID, TP)->query_attached())
        {
            notify_fail("Your hawk is attached to your glove already.\n");
            return 0;
        }
        
        present(NISSE_JESSES_ID, TP)->attach_hawk();
        return 1;
    }

    if (parts[0] == "release")
    {
        if (!present(NISSE_HAWK_ID, TP)->query_attached())
        {
            notify_fail("Your hawk is not attached to your glove.\n");
            return 0;
        }
        
        present(NISSE_JESSES_ID, TP)->release_hawk();
        return 1;
    }

    if (parts[0] == "hunt")
    {
        if (present(NISSE_HAWK_ID, TP)->query_hooded())
        {
            notify_fail("Your hawk is wearing a hood. Unhood it first.\n");
            return 0;
        }
        
        if (present(NISSE_HAWK_ID, TP)->query_attached())
        {
            notify_fail("The hawk is attached to your glove. Deattach it " +
                "first.\n");
            return 0;
        }

        NISSE_HAWK->do_hunt();
        set_alarm(20.0, 0.0, &NISSE_HAWK->clone_prey());
        return 1;
    }

    if (parts[0] == "return")
    {
        if (present(NISSE_HAWK_ID, TP)->query_hooded())
        {
            notify_fail("Your hawk is wearing a hood. Unhood it first.\n");
            return 0;
        }

        if (present(NISSE_HAWK_ID, TP)->query_attached())
        {
            notify_fail("The hawk is attached to your glove. Deattach it " +
                "first.\n");
            return 0;
        }
        
        present(NISSE_HAWK_ID, TP)->do_return1();
        return 1;
    }

    if (parts[0] == "feed")
    {
        if (!present(HAWK_FEED_ID, TP))
        {
            notify_fail("You do not have anything to feed your hawk with.\n");
            return 0;
        }

        write("You tear a " + present(HAWK_FEED_ID, TP)->short() + " into " +
            "small pieces and feed your hawk. It shrills happily.\n");
        say(QCTNAME(TP) + " tears a " + present(HAWK_FEED_ID, TP)->short() +
            " into small pieces and feeds " + HIS(TP) + " hawk. " +
            "It shrills happily.\n");
        present(HAWK_FEED_ID, TP)->remove_object();
        return 1;
    }
    
    if (!sizeof(oblist))
    {
        notify_fail(CAP(query_verb()) + " what?\n");
        return 0;
    }
    
    if (parts[0] == "stare")
    {
        actor("Sensing your displeasure the " + hawk_short + " stares " +
            "menacingly at",oblist,".");
        all2act("'s " + hawk_short + " senses a displeasure of its master " +
            "and stares menacingly at",oblist,".");
        oblist->catch_msg("You feel uncomfortable as " + TP->query_name() +
            "'s " + hawk_short + " stares menacingly at you.\n");
        return 1;
    }
    
    return 1;
}

/*
 *  Function name: nistomp
 *  Description  : Nisse emote to stomp
 *  Returns      : always 1
 */
int
nistomp()
{
    write("You stomp your foot, frustrated by the missed chance for " +
        "combat.\n");
    say(QCTNAME(TP) + " stomps " + HIS(TP) + " stomps her foot in " +
        "frustration at having missed the opportunity for battle.\n");
    return 1;
}

/*
 *  Function name: nistifle
 *  Description  : Nisse emote to stifle an amusement
 *  Returns      : always 1
 */
int
nistifle()
{
    write("You look away trying not to laugh in anyone's face.\n");
    say(QCTNAME(TP) + " looks downward, trying desperately to stifle " +
        HIS(TP) + " amusement.\n");
    return 1;
}

/*
 *  Function name: nipaint
 *  Description  : Nisse command to paint her body with a woad
 *  Returns      : 0/1
 */
int
nipaint()
{
    object	player = TP;
    object	woad;
    string      *sublocs;
    int         i;
    int         num_sublocs;

    if (!present(NISSE_WOAD_ID, player))
    {
        notify_fail("You do not have a woad to paint yourself with.\n");
        return 0;
    }

    sublocs = player->query_sublocs();
    num_sublocs = sizeof(sublocs);

    for (i = 0; i < num_sublocs; i++)
    {
        if (sublocs[i] == NISSE_SUBLOC_ID)
        {
            notify_fail("Your face is painted with the battle markings " +
                "already.\n");
            return 0;
        }
    }
    
    woad = present(NISSE_WOAD_ID, player);
    add_paint_subloc();
    woad->remove_object();

    write("You carefully paint yourself with the bright blue woad creating " +
        "patterns. A bright flush colors your cheeks as you prepare for " +
        "the coming battle.\n");
    say(QCTNAME(player) + " carefully paints " + HIM(player) + "self with " +
        "the bright blue woad creating patterns. A bright flush colors " +
        HIS(player) + " cheeks as " + HE(player) + " prepares for the " +
        "coming battle.\n");
    return 1;
}

/*
 *  Function name: niclean
 *  Description  : Nisse command to clean painting from their faces
 *  Returns      : 0/1
 */
int
niclean()
{
    object	player = TP;
    object	room = environment(player);
    string	*sublocs;
    int		i;
    int		num_sublocs;

    sublocs = player->query_sublocs();
    num_sublocs = sizeof(sublocs);
    
    for (i = 0; i < num_sublocs; i++)
    {
        if (sublocs[i] == NISSE_SUBLOC_ID)
        {
            if (room->query_prop(OBJ_I_CONTAIN_WATER))
            {
                write("You wash the battle markings from your skin, your " +
                    "face slowly taking on a look of quite serenity.\n");
                say(QCTNAME(player) + " washes the battle markings from " +
                    HIS(player) + " skin, " + HIS(player) + " face slowly " +
                    "taking on a look of quite serenity.\n");
                remove_paint_subloc();
                return 1;
            }
            
            notify_fail("You look around seeking for water. You cannot " +
                "find any.\n");
            return 0;
        }
    }
    
    notify_fail("Your face is not painted with the battle markings.\n");
    return 0;
}

/*
 *  Function name: nistep
 *  Description  : Nisse emote to stay back away
 *  Returns      : always 1
 */
int
nistep()
{
    write("You step back and look at everyone like they are nuts.\n");
    say(QCTNAME(TP) + " steps back and studies the situation with true " +
        "amusement.\n");
    return 1;
}

/*
 *  Function name: niflex
 *  Description  : Nisse emote to flex the muscles
 *  Argument     : string str
 *  Returns      : 1 on success, 0 on failure
 */
int
niflex(string str)
{
    string      *how;

    how = parse_adverb(str, "tensely", 1);
    write("You stretch your body " + how[1] + ".\n");
    say(QCTNAME(TP) + " stretches " + how[1] + " " + HIS(TP) + " taut " +
        "muscles rippling.\n");
    return 1;
}

/* Function name: niattack
 * Description  : Nisse emote to send a hawk at your enemy and start battle
 * Arguments    : string str - as entered by the player
 * Returns      : 1 on success, 0 on failure
 */
int
niattack(string str)
{
    object	enemy;
    object	*ob;
    string	rname = TP->query_race_name();

    if (!stringp(str))
    {
        enemy = TP->query_attack();
        if (!objectp(enemy))
        {
            TP->command("shout");
            return 1;
        }
        else
        {
            ob = ({ enemy });
        }
    }
    else
    {
        ob = parse_this(str, "%l");
    }

    if (!sizeof(ob))
    {
        write("You look warily around, ready for battle.\n");
        all(" looks warily around, ready for battle.\n");
        return 1;
    }

    if(sizeof(ob) > 1)
    {
        write("You cannot attack " + COMPOSITE_LIVE(ob) + " at the same " +
            "time, so you focus your attack on " +
            ob[0]->query_the_name(this_player()) + ".\n");
         ob = ({ ob[0] });
    }

    if (TP->query_attack() == ob[0])
    {
        actor("You shout out: You attack", ob, " with " +
            "renewed fervour.");
        target(" shouts out: \n" +
            capitalize(this_player()->query_pronoun()) + " attacks you " +
            "with renewed fervour.", ob);
        all2act(" shouts out: !\n" + this_player()->query_pronoun() +
            " attacks", ob, " with renewed fervour.\n", ob);
        return 1;
    }

    actor("You shout out: !\nYou join battle with", ob, ".");
    target(" shouts out: !\n" +
        capitalize(this_player()->query_pronoun()) + " joins battle with you.",
        ob);
    all2act(" shouts out: !\n" +
         capitalize(this_player()->query_pronoun()) + " joins " + "battle with",
        ob, ".");

    this_player()->attack_object(ob[0]);
    return 1;
}
