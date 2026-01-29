// CMDSOUL:  dancing_cmdsoul

    /* Calia Domain

    HISTORY

    [96-03-07] Created by Uhclem from [C:\CALIA\GELAN\SPECIALS\DANCING_.DOC].

    PURPOSE

    This soul provides many dancing emotes to the wearer of the dancing shoes
    sold in Gelan (/d/Gelan/armours/dancing_shoes.c).  */

// INCLUSIONS AND DEFINITIONS

#pragma no_clone
#pragma resident
#pragma strict_types
#pragma save_binary

inherit "/cmd/std/command_driver";

#include <adverbs.h>
#include <cmdparse.h>
#include <const.h>
#include <filter_funs.h>
#include <language.h>
#include <living_desc.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

// FUNCTIONS

// Function:  query_cmd_soul

/*

Purpose:  Identifies this object as a command soul.

Arguments:  none.

Returns:  1.

*/

public int
query_cmd_soul()

    {

    return 1;

    }

// Function:  get_soul_id

/*

Purpose:  Identifies the name of the command soul.

Arguments:  none.

Returns:  string.

*/

public string
get_soul_id()

    {

    return "Dancing Shoes";

    }

// Function:  query_cmdlist

/*

Purpose:  Maps the commands to their functions.  All dances use the same
function.

Arguments:  None.

Returns:  1

*/

mapping
query_cmdlist()

    {

    return([
        "help":"help_dancing",
        "minuet":"special_dance",
        "polka":"special_dance",
        "tango":"special_dance",
        "tarantella":"special_dance",
        "waltz":"special_dance",
        ]);

    }

// Function:  help_dancing

/*

Purpose:  Lists the available dances and describes proper syntax.

Arguments:  string with text typed by the player.

Returns:  0/1

*/

int
help_dancing(string str)

    {

    if(!stringp(str)) return 0;

    if(str != "dancing") return 0;

    write("\n" +
        "     You can do a waltz, tango, minuet, polka, or tarantella\n" +
        "     as long as you have someone to do it with:  " +
        "<dance> <partner>\n\n");

    return 1;

    }

// Function:  special_dance

/*

Purpose:  The command is simple - just type "<dance> <partner>", where <dance>
is one of the dances on the list and <partner> is the name of the person you
want to dance with.

Arguments:  string with text typed by the player.

Returns:  0/1

*/

int
special_dance(string str)

    {

    string dance = query_verb();    /* Name of dance selected by the player. */
    object tp = this_player();
    object pa;    /* The dance partner. */
    object this_room = environment(tp);
    int tp_gender;    /* Player's gender:  0=male, 1=female, 2=neuter. */
    int pa_gender;    /* Partner's gender, as above. */
    object dummy;    /*  General-purpose object.  */
    int i;    /* General-purpose integer. */

    /*  Strings to contain the pronouns for this player and the partner.
        They'll be assigned values only after it has been determined that the
        partner is a living object in the room.  */

    string tp_pro;
    string tp_pos;
    string tp_obj;
    string pa_pro;
    string pa_pos;
    string pa_obj;

    /*  Finally, a selection of actions, determined by gender, that can be
        performed as part of the dance.  */

    string *courtesy = ({"bow", "curtsey", "bow"});
    string *flourish = ({"leap", "twirl", "somersault"});

    if(!stringp(str))    /* Player only typed <dance>. */

        {

        notify_fail("Not without a partner!\n");
        return 0;

        }

    pa = present(str, this_room);

    if(!objectp(pa))  /* Selected partner is not in the room. */

        {

        notify_fail("But " + str + " isn't here!\n");
        return 0;

        }

    if(!living(pa))  /* Selected partner is not a living object. */

        {

        notify_fail("The " + str + " seems reluctant to dance with you.\n");
        return 0;

        }

    if(pa == tp)  /* Selected partner is the player himself! */

        {

        tp->catch_msg("You " + dance + " with yourself.  What fun!\n");

        say(QCTNAME(tp) + " " + dance +
            "s with " + tp->query_objective() + "self for a few seconds," +
            " then stops abruptly and blushes" +
            " when " + tp->query_pronoun() +
            " notices that you are watching.\n");

        return 1;

        }

    /*  Query pronouns for player and partner now so they don't have to be
        repeatedly queried in the tell_room and catch_msg statments.  */

    tp_pro = tp->query_pronoun();
    tp_pos = tp->query_possessive();
    tp_obj = tp->query_objective();
    pa_pro = pa->query_pronoun();
    pa_pos = pa->query_possessive();
    pa_obj = pa->query_objective();

    /*  At this point it is established that the player has selected a living
        object other than himself in the same room to dance with.  That's all
        that's really required to use the dancing emotes, but just to be mean,
        there's a 1% chance that the player will fall flat on his face (and
        maybe take the partner down as well).  */

    if(!random(100))

        {

        /*  We'll decide where to place the blame for messing up the dance
            based on the combinations of genders involved.  By adding the
            integer gender values we get the following variations to work with:

        0 = both male
        1 = one male and one female
        2 = two female OR one male and one neuter
        3 = one female and one neuter
        4 = two neuter

            The following botched-dance routines are entirely the creation of
            Uhclem and do not in any way reflect the opinions or policy of the
            Calia domain.  */

        i = tp_gender + pa_gender;

        switch (i)

            {

            case 0:    /*  Both male.  It's the other guy's fault.  */

            tp->catch_msg("You attempt a friendly " + dance +
                " with " + QTNAME(pa) +
                ", but he trips you, and both you of tumble" +
                " to the ground.\n");

            pa->catch_msg(QCTNAME(tp) +
                " catches you off-guard when he grabs you and begins" +
                " a " + dance +
                ".  You do your best to keep up, but you" +
                " accidentally trip him and the" +
                " two of you go tumbling to the ground.\n");

            tell_room(this_room, QCTNAME(tp) +
                " tries to engage " + QTNAME(pa) +
                " in a friendly " + dance +
                ", but their legs quickly become entangled and the" +
                " two of them soon tumble to the ground in" +
                " a heap.\n", ({tp, pa}));

            break;

            case 1:    /*  Male and female - it's always the male's fault.  */
            case 3:    /*  Female and neuter FALLTHROUGH.                   */

            /*  It's always the male's fault even if the female is the one who
                started the dance!  So if this player is female, we have to do
                a little role reversal.  The females get to know how this feels
                when they dance with a neuter character.  No matter who started
                the dance, if it goes awry it'll always be the female's fault!
                I figure the neuters have enough problems already, so they
                don't get the blame for anything.  */

            if(tp_gender > pa_gender)

                {

                dummy = tp;
                tp = pa;
                pa = dummy;

                /*  Note reuse of variable "str" here.  Once the object
                    reference to the partner is determined, the string variable
                    is no longer needed, so it can be used as a swap field.  */

                str = tp_pro;
                tp_pro = pa_pro;
                pa_pro = str;

                str = tp_pos;
                tp_pos = pa_pos;
                pa_pos = str;

                str = tp_obj;
                tp_obj = pa_obj;
                pa_obj = str;

                }

            tp->catch_msg("You begin to " + dance +
                " with " + QTNAME(pa) +
                " but you clumsily step on " + pa_pos +
                " toe!  " + QCTNAME(pa) +  " stops dancing and" +
                " glares at you indignantly.\n");

            pa->catch_msg(QCTNAME(tp) +
                " begins a " + dance +
                " with you but almost immediately stomps on your" +
                " toe!  You get the feeling " + tp_pro +
                " did it deliberately, stop the dance," +
                " and glare at " + tp_obj +
                " indignantly.\n");

            tell_room(this_room, QCTNAME(tp) +
                " looks like " + tp_pro +
                " is trying to " + dance +
                " with " + QTNAME(pa) +
                ", but " + tp_pro +
                " clumsily steps on " + pa_pos +
                " toe - what a klutz!  " + QCTNAME(pa) +
                " stops dancing and glares at " + tp_obj +
                " indignantly.\n", ({tp, pa}));

            break;

            case 2:    /*  It's the player's own fault.  */

            tp->catch_msg("You try to lead " + QTNAME(pa) +
                " in a " + dance +
                ", but the slippery leather soles of your" +
                " dancing shoes trip you up and you fall flat" +
                " on your face!\n");

            pa->catch_msg(QCTNAME(tp) +
                " approaches you in hopes of leading you in a " + dance +
                ", but the slippery soles of " + tp_pos +
                " dancing shoes trip " + tp_obj +  " and " + tp_pro +
                " falls flat on " + tp_pos +
                " face!\n");

            tell_room(this_room, QCTNAME(tp) +
                " approaches " + QTNAME(pa) +
                " in hopes of leading " + pa_obj +
                " in a " + dance +
                ", but the slippery soles of " + tp_pos +
                " dancing shoes trip " + tp_obj +  " and " + tp_pro +
                " falls flat on " + tp_pos +
                " face!\n", ({tp, pa}));

            break;

            case 4:    /*  Both neuter.  A no-fault dance catastrophe.  */

            tp->catch_msg("You try to perform a " + dance +
                " with " + QTNAME(pa) +
                ", but you both keep trying to lead.  You" +
                " eventually tumble to the ground in confusion.\n");

            pa->catch_msg(QCTNAME(tp) +
                " tries to perform a " + dance +
                " with you, but you both try to lead!  After a" +
                " few seconds of pushing against each other, you" +
                " both tumble to the ground in confusion.\n");

            tell_room(this_room, QCTNAME(tp) +
                " and " + QTNAME(pa) +
                " look like they're trying to perform a " + dance +
                ", but they're both trying to lead!  It isn't" +
                " long before their legs entangle and they fall to" +
                " the ground in confusion.\n", ({tp, pa}));

            }

        return 1;

        }

    /*  If the partner is wearing dancing shoes, player gets a random selection
        of 5 variations on each dance.  If not, only the first three of each
        set of variations is available.  When adding dances to the sections
        below, remember: (1) keep them in alphabetical order and (2) the
        fanciest variations on each dance should be put in cases 3 and 4.  */

    dummy = present("gelan_dancing_shoes", pa);

    i = random(3);
    if(objectp(dummy)) if(dummy->query_worn()) i = random(5);

    switch (query_verb())

        {

        case "minuet":

        switch (i)

            {

            case 0:

            tp->catch_msg("You take " + QTNAME(pa) +
                " by the hand and lead " + pa_obj +
                " in a graceful minuet.\n");

            pa->catch_msg(QCTNAME(tp) +
                " takes you by the hand and leads you" +
                " in a graceful minuet.\n");

            tell_room(this_room, QCTNAME(tp) +
                " takes " + QTNAME(pa) +
                " by the hand and leads " + pa_obj +
                " in a graceful minuet.\n", ({tp, pa}));

            break;

            case 1:

            tp->catch_msg("You " + courtesy[tp_gender] +
                " before " + QTNAME(pa) +
                ", lead " + pa_obj +
                " to an uncluttered spot, and the two of" +
                " you execute an exquisite minuet.\n");

            pa->catch_msg(QCTNAME(tp) +
                " " + courtesy[tp_gender] +
                "s before you, leads you to an uncluttered spot, and" +
                " the two of you execute an exquisite minuet.\n");

            tell_room(this_room, QCTNAME(tp) +
                " " + courtesy[tp_gender] +
                "s before " + QTNAME(pa) +
                ", leads " + pa_obj +
                " to an uncluttered spot, and the two of" +
                " them execute an exquisite minuet.\n", ({tp, pa}));

            break;

            case 2:

            tp->catch_msg("You quietly slip behind " + QTNAME(pa) +
                ", take " + pa_pos +
                " hands in yours, and begin a stately minuet that" +
                " takes the two of you in a great circle, ending up" +
                " in the exact spot where you started.\n");

            pa->catch_msg(QCTNAME(tp) +
                " quietly slips behind you," +
                " takes your hands in " + tp_pos +
                ", and begins a stately minuet that takes the two of" +
                " you in a great circle, ending up in the exact" +
                " spot where you started.\n");

            tell_room(this_room, QCTNAME(tp) +
                " quietly slips behind " + QTNAME(pa) +
                ", takes " + pa_pos +
                " hands in " + tp_pos +
                ", and begins a stately minuet that takes the two of" +
                " them in a great circle, ending up in the exact" +
                " spot where they started.\n", ({tp, pa}));

            break;

            case 3:

            tp->catch_msg("You stand before " + QTNAME(pa) +
                ", " + courtesy[tp_gender] +
                " deeply, and begin the first few steps of a minuet" +
                " in a tight circle around " + pa_obj +
                ", and " + pa_pro +
                " joins you in perfect symmetry as the two of" +
                " you continue the dance in elegant arcs" +
                " and spirals.\n");

            pa->catch_msg(QCTNAME(tp) +
                " stands before you, " + courtesy[tp_gender] +
                "s deeply, and begins the first few steps of a minuet" +
                " in a tight circle around you, and you join " + tp_obj +
                " in perfect symmetry as the two of you" +
                " continue the dance in elegant arcs and spirals.\n");

            tell_room(this_room, QCTNAME(tp) +
                " stands before " + QTNAME(pa) +
                ", " + courtesy[tp_gender] +
                "s deeply, and begins the" +
                " first few steps of a minuet in a tight circle" +
                " around" + pa_obj +
                ", and " + pa_pro +
                " joins " + tp_obj +
                " in perfect symmetry as the two of them continue" +
                " the dance in elegant arcs and spirals.\n", ({tp, pa}));

            break;

            case 4:

            tp->catch_msg("You take " + QTNAME(pa) +
                " by the hand and lead " + pa_obj +
                " in a lively but refined minuet," +
                " reversing direction and switching" +
                " positions several times.  You conclude the dance" +
                " with a fancy " + flourish[tp_gender] +
                " in front of " + pa_obj +
                ", your arms held high over your head.\n");

            pa->catch_msg(QCTNAME(tp) +
                " takes you by the hand and leads you in a" +
                " lively but refined minuet, reversing" +
                " direction and switching positions several times," +
                " and " +  tp_pro +
                " concludes the dance with a fancy " + flourish[tp_gender] +
                " in front of you, " +  tp_pos +
                " arms held high over " +  tp_pos +
                " head.\n");

            tell_room(this_room, QCTNAME(tp) +
                " takes " + QTNAME(pa) +
                " by the hand and leads " + pa_obj +
                " in a lively but refined minuet," +
                " reversing direction and switching positions" +
                " several times.  " + QCTNAME(tp) +
                " concludes the dance with a fancy " + flourish[tp_gender] +
                " in front of " + QTNAME(pa) +
                ", " + tp_pos +  " arms held high over " + tp_pos +
                " head.\n", ({tp, pa}));

            break;

            default:

            write("Your sensitive feet detect a problem" +
                " with the dancing shoes.\n");

            }

        break;

        case "polka":

        switch (i)

            {

            case 0:

            tp->catch_msg("You kick up your heels and lead " + QTNAME(pa) +
                " in a lively polka.\n");

            pa->catch_msg(QCTNAME(tp) +
                " kicks up " + tp_pos +
                " heels and leads you in a lively polka.\n");

            tell_room(this_room, QCTNAME(tp) +
                " kicks up " + tp_pos +
                " heels and leads " + QTNAME(pa) +
                " in a lively polka.\n", ({tp, pa}));

            break;

            case 1:

            tp->catch_msg("You suddenly grab " + QTNAME(pa) +
                " and swing " + pa_obj +
                " about merrily in a boisterous polka!\n");

            pa->catch_msg(QCTNAME(tp) +
                " suddenly grabs you and swings you about" +
                " merrily in a boisterous polka!\n");

            tell_room(this_room, QCTNAME(tp) +
                " suddenly grabs " + QTNAME(pa) +
                " and swings " + pa_obj +
                " about merrily in a boisterous polka!\n", ({tp, pa}));

            break;

            case 2:

            tp->catch_msg("You lead " + QTNAME(pa) +
                " in a giddy, fast-paced polka, and the two" +
                " of you bounce around in a big circle until you" +
                " are nearly out of breath.\n");

            pa->catch_msg(QCTNAME(tp) +
                " leads you in a giddy, fast-paced polka, and the" +
                " two of you bounce around in a big circle until" +
                " you are nearly out of breath.\n");

            tell_room(this_room, QCTNAME(tp) +
                " leads " + QTNAME(pa) +
                " in a giddy, fast-paced polka, and the two" +
                " of them bounce around the room in a big circle" +
                " until they are nearly out of breath.\n", ({tp, pa}));

            break;

            case 3:

            tp->catch_msg("You begin to hum a merry tune and tap" +
                " your foot in time to it.  " + QCTNAME(pa) +
                " joins in, and soon the two of you are engaged" +
                " in a lively polka, skipping and" +
                " bouncing about with abandon.\n");

            pa->catch_msg(QCTNAME(tp) +
                " begins to hum a merry tune and tap " + tp_pos +
                " foot in time, and you soon find yourself" +
                " joining in.  The tapping turns into a lively" +
                " polka, and the two of you skip and" +
                " bounce about with abandon.\n");

            tell_room(this_room, QCTNAME(tp) +
                " begins to hum a lively tune and tap " + tp_pos +
                " foot in time to it.  " + QCTNAME(pa) +
                " happily joins in, and the two of them are soon" +
                " engaged in a lively polka, skipping and" +
                " bouncing about with abandon.\n", ({tp, pa}));

            break;

            case 4:

            tp->catch_msg("You suddenly seize " +  QTNAME(pa) +
                " and dash off with " + pa_obj +
                " in a wild, impulsive polka.  The two of you" +
                " cavort wildly in all directions, and you" +
                " punctuate the dance with an" +
                " occasional " + flourish[tp_gender] +
                ", much to " + pa_pos +
                " surprise and delight!\n");

            pa->catch_msg(QCTNAME(tp) +
                " seizes you and sends you spinning into a polka" +
                " that seemed to have already been in progress" +
                " when you entered it!   As the two of you cavort" +
                " wildly in all directions, " + tp_pro +
                " adds a few impressive " + flourish[tp_gender] +
                "s to the already intricate steps, much to" +
                " your surprise and delight!\n");

            tell_room(this_room, QCTNAME(tp) +
                " seizes " + QTNAME(pa) +
                " and sends " + pa_obj +
                " spinning into a polka that seemed to have" +
                " already been in progress when they entered it! " +
                " As the two of them cavort wildly in all" +
                " directions, " + QTNAME(tp) +
                " adds a few impressive " + flourish[tp_gender] +
                "s to the already intricate steps, much to " + QTNAME(pa) +
                "'s surprise and delight!\n", ({tp, pa}));

            break;

            default:

            write("Your sensitive feet detect a problem" +
                " with the dancing shoes.\n");

            }

        break;

        case "tango":

        switch (i)

            {

            case 0:

            tp->catch_msg("You engage " + QTNAME(pa) +
                " in a seductive tango, gazing deeply into " + pa_pos +
                " eyes as you dance.\n");

            pa->catch_msg(QCTNAME(tp) +
                " engages you in a seductive tango, gazing" +
                " deeply into your eyes as you dance.\n");

            tell_room(this_room, QCTNAME(tp) +
                " engages " + QTNAME(pa) +
                " in a seductive tango, gazing deeply into " + pa_pos +
                " eyes as they dance.\n", ({tp, pa}));

            break;

            case 1:

            tp->catch_msg("You wrap yourself around " + QTNAME(pa) +
                ", guiding " + pa_obj +
                " in a sinuous motion as you tango to the" +
                " rhythm of your heartbeats.\n");

            pa->catch_msg(QCTNAME(tp) +
                " wraps " + tp_obj +
                "self around you, guiding you in a sinuous motion" +
                " as you tango to the rhythm of your heartbeats.\n");

            tell_room(this_room, QCTNAME(tp) +
                " wraps " + tp_obj +
                "self around " + QTNAME(pa) +
                ", guiding " + pa_obj +
                " in a sinuous motion as they tango to the" +
                " rhythm of their heartbeats.\n", ({tp, pa}));

            break;

            case 2:

            tp->catch_msg("You command " + QTNAME(pa) +
                "'s attention with an abrupt snap of your fingers," +
                " draw " + pa_pos +
                " body close against yours, and begin" +
                " the measured but passionate steps of" +
                " a deliberate, seductive tango.\n");

            pa->catch_msg(QCTNAME(tp) +
                " commands your attention with an abrupt snap of " + tp_pos +
                " fingers, draws your body close against " + tp_pos +
                ", and begins the measured but passionate" +
                " steps of a deliberate, seductive tango.\n");

            tell_room(this_room, QCTNAME(tp) +
                " commands " + QTNAME(pa) +
                "'s attention with an abrupt snap of " + tp_pos +
                " fingers, draws " + pa_pos +
                " body close to " + tp_pos +
                " own, and begins the measured but passionate" +
                " steps of a deliberate, seductive tango.\n", ({tp, pa}));

            break;

            case 3:

            tp->catch_msg("You pull a blood-red rose from" +
                " your pocket, clench it in your teeth," +
                " and take " + QTNAME(pa) +
                " in your arms, commanding " + pa_pos +
                " every motion as you glide through a sinuous" +
                " tango.  In the final dip, you toss the rose aside to" +
                " give " + pa_obj +
                " a long, passionate kiss.\n");

            pa->catch_msg(QCTNAME(tp) +
                " pulls a blood-red rose from " + tp_pos +
                " pocket, clenches it in " + tp_pos +
                " teeth, and takes you in " + tp_pos +
                " arms, commanding your every motion as you" +
                " glide through a sinuous tango. " +
                " In the final dip, " + tp_pro +
                " tosses the rose aside to give you" +
                " a long, passionate kiss.\n");

            tell_room(this_room, QCTNAME(tp) +
                " pulls a blood-red rose from " + tp_pos +
                " pocket, clenches it in " + tp_pos +
                " teeth, and takes " + QTNAME(pa) +
                " in " + tp_pos +
                " arms, commanding " + pa_pos +
                " every motion as they glide through a sinuous" +
                " tango.  In the final dip, " + QTNAME(tp) +
                " tosses the rose aside to give " + QTNAME(pa) +
                " a long, passionate kiss.\n", ({tp, pa}));

            break;

            case 4:

            tp->catch_msg("You draw " + QTNAME(pa) +
                " into a firm embrace, and the two of you begin" +
                " to move in perfect unison through the serpentine" +
                " steps of a tango, slow and calculated at" +
                " first, then evolving into a wanton," +
                " undulating motion that flings sweat from" +
                " your brows and sparks from your eyes!\n");

            pa->catch_msg(QCTNAME(tp) +
                " draws you into a firm embrace, and the two of" +
                " you begin to move in perfect unison" +
                " through the serpentine steps of a tango," +
                " slow and calculated at first, then evolving" +
                " into a wanton, undulating motion that flings" +
                " sweat from your brows and sparks from your eyes!\n");

            tell_room(this_room, QCTNAME(tp) +
                " draws " + QTNAME(pa) +
                " into a firm embrace, and the two of them begin" +
                " to move in perfect unison through the serpentine" +
                " steps of a tango, slow and calculated at" +
                " first, then evolving into a wanton," +
                " undulating motion that flings sweat from" +
                " their brows and sparks from their eyes!" +
                "\nGosh, is it getting hot in here?\n", ({tp, pa}));

            break;

            default:

            write("Your sensitive feet detect a" +
                " problem with the dancing shoes.\n");

            }

        break;

        case "tarantella":

        switch (i)

            {

            case 0:

            tp->catch_msg("You spin " + QTNAME(pa) +
                " around and around as the two of you" +
                " perform a dizzying tarantella.\n");

            pa->catch_msg(QCTNAME(tp) +
                " spins you around and around as the two of" +
                " you perform a dizzying tarantella.\n");

            tell_room(this_room, QCTNAME(tp) +
                " spins " + QTNAME(pa) +
                " around and around as the two of them" +
                " perform a dizzying tarantella.\n", ({tp, pa}));

            break;

            case 1:

            tp->catch_msg("You clap your hands in a rapid rhythm" +
                " and " + QTNAME(pa) +
                " joins you in a tarantella.  The two of you kick" +
                " up quite a lot of dust as you perform" +
                " the wild, whirling dance!\n");

            pa->catch_msg(QCTNAME(tp) +
                " claps " + tp_pos +
                " hands in a rapid rhythm and you join " + tp_obj +
                " in a tarantella.  The two of you kick up quite a" +
                " lot of dust as you perform the" +
                " wild, whirling dance!\n");

            tell_room(this_room, QCTNAME(tp) +
                " claps " + tp_pos +
                " hands in a rapid rhythm and " + QTNAME(pa) +
                " joins " + tp_obj +
                " in a tarantella.  The two of them kick up quite a" +
                " lot of dust as they perform the" +
                " wild, whirling dance!\n", ({tp, pa}));

            break;

            case 2:

            tp->catch_msg("You " + courtesy[tp_gender] +
                " graciously before " + QTNAME(pa) +
                ", then startle " + pa_obj +
                " as you suddenly spring into action and" +
                " begin a lively tarantella.  " + QCTNAME(pa) +
                " quickly joins in, and the two of you whirl" +
                " and leap wildly until you collapse from exhaustion.\n");

            pa->catch_msg(QCTNAME(tp) +
                " " + courtesy[tp_gender] +
                "s graciously before you," +
                " then startles you as " + tp_pro +
                " suddenly springs into action and begins" +
                " a lively tarantella.  You quickly join in, and the" +
                " two of you whirl and leap wildly until" +
                " you collapse from exhaustion.\n");

            tell_room(this_room, QCTNAME(tp) +
                " " + courtesy[tp_gender] +
                "s graciously before " + QTNAME(pa) +
                ",  then startles " + pa_obj +
                " as " + tp_pro +
                " suddenly springs into action and begins" +
                " a lively tarantella.  " + QCTNAME(pa) +
                " quickly joins in, and the two of them whirl" +
                " and leap wildly until they collapse" +
                " from exhaustion.\n", ({tp, pa}));

            break;

            case 3:

            tp->catch_msg("You seize " + QTNAME(pa) +
                " by the hands, snatching " + pa_obj +
                " right off " + pa_obj +
                " feet, and whirl " + pa_obj +
                " into a tarantella!  The two of you dance with" +
                " such spirit and energy that your legs seem" +
                " to dissolve into vague blurs against the cloud" +
                " of dust you've raised.\n");

            pa->catch_msg(QCTNAME(tp) +
                " seizes you by the hands, snatching you right" +
                " off your feet, and whirls you into a tarantella! " +
                " The two of you dance with such spirit and" +
                " energy that your legs seem to dissolve" +
                " into vague blurs against the cloud" +
                " of dust you've raised.\n");

            tell_room(this_room, QCTNAME(tp) +
                " seizes " + QTNAME(pa) +
                " by the hands, snatching " + pa_obj +
                " right off " + pa_pos +
                " feet, and whirls " + pa_obj +
                " into a tarantella!  The two of them dance" +
                " with such spirit and energy that their legs" +
                " seem to dissolve into vague blurs against the" +
                " cloud of dust they've raised.\n", ({tp, pa}));

            break;

            case 4:

            tp->catch_msg("You and " + QTNAME(pa) +
                " begin a wild tarantella, spinning and gyrating" +
                " without a care for anything or anyone you" +
                " may knock down. " +
                " You improvise some impressive " + flourish[tp_gender] +
                "s, and " + QTNAME(pa) +
                " adds a few " + flourish[pa_gender] +
                "s of " + pa_pos +
                " own to the already fancy footwork!\n");

            pa->catch_msg(QCTNAME(tp) +
                " and you begin a wild tarantella," +
                " spinning and gyrating without a care for" +
                " anything or anyone they may knock down.  " + QCTNAME(tp) +
                " improvises some impressive " + flourish[tp_gender] +
                "s, and you add a few " + flourish[pa_gender] +
                "s of your own to the already fancy footwork!\n");

            tell_room(this_room, QCTNAME(tp) +
                " and " + QTNAME(pa) +
                " begin a wild tarantella, spinning and gyrating" +
                " without a care for anything or anyone they may" +
                " knock down.  " + QCTNAME(tp) +
                " improvises some impressive " + flourish[tp_gender] +
                "s, and " + QTNAME(pa) +
                " adds a few " + flourish[pa_gender] +
                "s of " + pa_pos +
                " own to the already fancy footwork!\n", ({tp, pa}));

            break;

            default:

            write("Your sensitive feet detect a problem" +
                " with the dancing shoes.\n");

            }

        break;

        case "waltz":

        switch (i)

            {

            case 0:

            tp->catch_msg("You " + courtesy[tp_gender] +
                " before " + QTNAME(pa) +
                ", adopt a regal dancing posture, and begin" +
                " a slow, luxurious waltz with " + pa_obj +
                " that describes a pattern of endlessly widening" +
                " circles on the ground.\n");

            pa->catch_msg(QCTNAME(tp) +
                " " + courtesy[tp_gender] +
                "s before you, adopts a regal dancing posture," +
                " and begins a slow, luxurious waltz with you" +
                " that describes a pattern of endelssly widening" +
                " circles on the ground.\n");

            tell_room(this_room, QCTNAME(tp) +
                " " + courtesy[tp_gender] +
                "s before " + QTNAME(pa) +
                ", adopts a regal dancing posture, and begins" +
                " a slow, luxurious waltz with " + pa_obj +
                " that describes a pattern of endlessly widening" +
                " circles on the ground.\n", ({tp, pa}));

            break;

            case 1:

            tp->catch_msg("With heads held high and arms" +
                " in classic embrace, you and " + QTNAME(pa) +
                " waltz in a fluid spiral, oblivious to anything" +
                " but each other and the euphoric rhythm" +
                " of the dance.\n");

            pa->catch_msg("With heads held high and arms in" +
                " classic embrace, " + QTNAME(tp) +
                " and you waltz in a fluid spiral, oblivious" +
                " to anything but each other and the euphoric" +
                " rhythm of the dance.\n");

            tell_room(this_room, "With heads held high and" +
                " arms in classic embrace, " + QTNAME(tp) +
                " and " + QTNAME(pa) +
                " waltz in a fluid spiral, oblivious to anything" +
                " but each other and the euphoric rhythm" +
                " of the dance.\n", ({tp, pa}));

            break;

            case 2:

            tp->catch_msg("You begin a giddy waltz with " + QTNAME(pa) +
                ", turning " + pa_obj +
                " first in one direction and then the" +
                " other until your surroundings are merely" +
                " a blurred backdrop against " + pa_pos +
                " steady gaze into your eyes.\n");

            pa->catch_msg(QCTNAME(tp) +
                " begins a giddy waltz with you, turning you" +
                " first in one direction and then the other until your" +
                " surroundings are merely a blurred backdrop against" +
                " " + tp_pos +
                " steady gaze into your eyes.\n");

            tell_room(this_room, QCTNAME(tp) +
                " begins a giddy waltz with " + QTNAME(pa) +
                ", turning " + pa_obj +
                " first in one direction and then the other until" +
                " it seems they are aware of nothing but" +
                " their steady gazes into each other's" +
                " eyes.\n", ({tp, pa}));

            break;

            case 3:

            tp->catch_msg("You lead " + QTNAME(pa) +
                " in a waltz, slowly and from a reverent" +
                " arm's-length at first, but drawing " + pa_obj +
                " ever closer as the dance quickens," +
                " transforming the dance steps into a" +
                " mesmerizing spin that ends with a deep dip" +
                " and a final, lingering embrace.\n");

            pa->catch_msg(QCTNAME(tp) +
                " leads you in a waltz, slowly and from" +
                " a reverent arm's-length at first, but drawing" +
                " you ever closer as the dance quickens," +
                " transforming the dance steps into a" +
                " mesmerizing spin that ends with a dip and" +
                " a final, lingering embrace.\n");

            tell_room(this_room, QCTNAME(tp) +
                " leads " + QTNAME(pa) +
                " in a waltz, slowly and from a reverent" +
                " arm's-length at first, but drawing " + pa_obj +
                " ever closer as the dance quickens," +
                " transforming the dance steps into a" +
                " mesmerizing spin that ends with a dip and" +
                " a final, lingering embrace.\n", ({tp, pa}));

            break;

            case 4:

            tp->catch_msg("You " + courtesy[tp_gender] +
                " deeply before " + QTNAME(pa) +
                ", wait for a moment as the air" +
                " fills with mysterious, inexplicable music, then" +
                " lead " + pa_obj +
                " in an enigmatic waltz, neither fast nor slow" +
                " but moved by rhythms from within, and executed" +
                " in steps so light that they make no sound and" +
                " leave no trace upon the ground.\n");

            pa->catch_msg(QCTNAME(tp) +
                " " + courtesy[tp_gender] +
                "s deeply before you, waits for a moment as the" +
                " air fills with mysterious, inexplicable music," +
                " then leads you in an enigmatic waltz, neither" +
                " fast nor slow but moved by rhythms from" +
                " within, and executed in steps so light that" +
                " they make no sound and leave no trace" +
                " upon the ground.\n");

            tell_room(this_room, QCTNAME(tp) +
                " " + courtesy[tp_gender] +
                "s deeply before " + QTNAME(pa) +
                ", waits for a moment as the air" +
                " fills with mysterious, inexplicable music, then" +
                " leads " + pa_obj +
                " in an enigmatic waltz, neither fast nor slow" +
                " but moved by rhythms from within, and executed" +
                " in steps so light that they make no sound and" +
                " leave no trace upon the ground.\n", ({tp, pa}));

            break;

            default:

            write("Your sensitive feet detect a problem" +
                " with the dancing shoes.\n");

            }

        break;

        default:

        write("Your sensitive feet detect a problem" +
            " with the dancing shoes.\n");

        }

    return 1;

    }
