// OBJECT:  candy_cane

    /* Calia Domain

    HISTORY

    [01-12-22] Created by Uhclem from [C:\CALIA\YULEWARE\CANDY_CA.DOC].

    PURPOSE

    A Christmas treat for visitors to the domain office in the Tower of
    Realms.  Some of the functions in this item are a bit confusing in their
    syntax.  This is intentional, as I have coded up routines to intercept
    likely misuses of the functions and turn them into humorous emotes. */

// INCLUSIONS AND DEFINITIONS

inherit "/std/food";

#include <stdproperties.h>
#include <macros.h>
#include <options.h>

// GLOBAL VARIABLES

string Flavor;
int Charge = random(3) + 3;  /*  Power control for "deck" function.  */

// OBJECT DEFINITION

void
create_food()

{

    /*
     * VARIABLES   
     */

    string *brights = ({"silver", "yellow", "white", "gold"});
    string *darks = ({"blue", "red", "green", "purple"});
    int bright_select = random(sizeof(brights));
    int dark_select = random(sizeof(darks));

    string *flavors = ({"coconut", "clove", "licorice", "espresso coffee",
        "cinnamon", "caramel", "spearmint", "peppermint",
        "apricot", "eggnog", "wintergreen", "butterscotch",
        "chocolate and mint", "chocolate", "root beer",
        "creamed chipped beef"});

    Flavor = flavors[(dark_select * 4) + bright_select];

    /*
     *  DESCRIPTION    
     */

    set_short(darks[(dark_select)] + "-and-" + brights[(bright_select)] +
        " striped candy cane");

    set_name("cane");
    add_name("candy cane");
    add_name("striped candy cane");

    add_name(darks[(dark_select)] + "-and-" + brights[(bright_select)] +
        " cane");

    add_name(darks[(dark_select)] + "-and-" + brights[(bright_select)] +
        " candy cane");

    add_name(darks[(dark_select)] + "-and-" + brights[(bright_select)] +
        " striped candy cane");

    set_adj("candy");
    add_adj("striped");
    add_adj(darks[(dark_select)] + "-and-" + brights[(bright_select)]);

    set_long("It's a little candy cane with vivid " +
        darks[(dark_select)] + " and " + brights[(bright_select)] +
        " stripes, freshly crafted by a master candymaker and" +
        " exuding the distinctive scent of " + Flavor + ". It" +
        " reminds you of an old Calian nursery rhyme:\n\n" +
        "    You can lick it,              You can wave it,\n" +
        "    You can suck it,              You can smell it --\n" +
        "    You can crunch it,            It's a gift, so\n" +
        "    You can tuck it,              Don't you sell it!\n\n" +
        "Just having one of these puts you in a jovial holiday mood," +
        " but remember what your mother told you - don't carol with your" +
        " mouth full!\n");

    /*
     *  PROPERTIES    
     */

    set_amount(1);
    add_prop(OBJ_I_WEIGHT, 25);
    add_prop(OBJ_I_VOLUME, 30);
    add_prop(OBJ_I_VALUE, 5);
    setuid();  /*  "uid" settings required for cloning holly boughs. */
    seteuid(getuid());

    add_prop(OBJ_M_NO_SELL, "A Grinch suddenly appears and bops" +
        " you on the head! He snarls, 'shame on you for trying" +
        " to sell your Christmas present,' then vanishes.\n");

    /*
     *  ITEMS    
     */

    add_item(({"image", "stripe", "stripes",
        darks[(dark_select)] + " stripe",
        brights[(bright_select)] + "stripe"}),
        "As you look closely you can just barely make out a" +
        " tiny image that looks like two Calian warriors having a" +
        " merry time as they deck the halls with boughs of" +
        " holly. It strikes you as odd that anyone would have" +
        " gone to the trouble of decorating a candy cane this way.\n");

    add_item((darks[(dark_select)] + " stripes"),
        "Technically, there is only one " + darks[(dark_select)] +
        " stripe that wraps around the length of the candy" +
        " cane. You could probably examine it now that" +
        " you understand it better.\n");

    add_item((brights[(bright_select)] + " stripes"),
        "Technically, there is only one " + brights[(bright_select)] +
        " stripe that wraps around the length of the candy" +
        " cane. You could probably examine it now that" +
        " you understand it better.\n");

}

// FUNCTIONS

// Function:  cane_carol

/*

Purpose:  sing a yuletide carol, rather badly.  This is a simple function whose
variation is mainly in the perversity of the sung text.  Since there are six
sections and each section has ten possible texts, there are ONE MILLION
variations on this Christmas carol, all of them awful.  However, to provide
additional opporunity for embarrassment, there is a 1/10 chance that the song
will be shouted so that occupants of adjacent rooms will hear it as well as
those in the same room.

Arguments:  none

Returns:  1

*/

int
cane_carol()

{

    string *emotes = ({
        " mutters absentmindedly and mumbles something that" +
            " sounds like a Yuletide carol",
        " suddenly blurts out a boisterous, if inane, holiday carol",
        " bravely attempts a Christmas carol",
        " belts out a Yuletide carol with gusto",
        " carols off-key and in a herky-jerky rhythm",
        " takes a deep breath and lets loose an uninhibited holiday carol",
        " exclaims 'stand back - I'm going to sing!' then" +
            " proceeds to massacre some beloved Yuletide carols",
        " emits a sound that vaguely resembles a Christmas carol",
        " inadvertently invents a new form of holiday song"});

    /*
     *  The carol has six parts.  These parts are randomly assembled from 
     *  various Christmas carols and a few other songs.  Specific religious
     *  references are avoided because the object is to mock the player's
     *  singing ability, not the holiday or the carols.    
     */

    string *part1 = ({
        "Deck the halls with bah and humbug,",
        "It's beginning to look a lot like",
        "Oh tawny bomb, oh tawny bomb,",
        "Oh, you better not pout, you better not cry,",
        "Jingle bells, jingle bells,",
        "Here we come a-caroling,",
        "With every Christmas card I write,",
        "Ho-ho-ho,",
        "Then one foggy Christmas Eve,",
        "On the seventy-fifth day of Christmas,"});

    string *part2 = ({
        " Santa Claus",
        " Frosty the snowman",
        " Rudolph the red-nosed reindeer",
        " a jolly old elf",
        " my true love",
        " Jack Frost",
        " Mama in her kerchief and I in my cap",
        " eight tiny reindeer",
        " Mr. Scrooge",
        " the Grinch"});

    string *part3 = ({
        " pranced on",
        " decked",
        " gave to me",
        " wassailed",
        " hung mistletoe on",
        " stuffed",
        " came down the chimney with",
        " stuffed a stocking with",
        " saw mommy kissing",
        " roasted"});

    string *part4 = ({
        " the roof-top",
        " a partridge in a pear tree",
        " a merry little Christmas",
        " a one-horse open sleigh",
        " chestnuts",
        " sleigh bells",
        " lots of toys and goodies",
        " ten geese a-milking",
        " my two front teeth",
        " the Christmas tree"});

    string *part5 = ({
        " to play a reindeer game,",
        " right down Santa Claus lane,",
        " over the river and through the woods,",
        " with boughs of holly,",
        " in gay apparel,",
        " walking in a winter wonderland,",
        " and settled at last for a long winter's nap,",
        " for Donner and Dasher and Blitzen and Wendell,",
        " to find out if I was naughty or nice,",
        " on an open fire,"});

    string *part6 = ({
        " pa-rum-pum-pum-pum!",
        " fa-la-la-la-la-la-la-la, umm... doo-dah, doo-dah!",
        " fa-la-la-la-la, la-la-la-la!",
        " and to all a good night!",
        " and a happy new year!",
        " do wah diddy diddy dum diddy do!",
        " then settled down for a long winter's nap!",
        " and we'll take a cup o' kindness yet for auld lang syne!",
        " so be good for goodness' sake!",
        " and may all your Christmases be white!"});

    object tp = this_player();
    object to = this_object();
    int e = random(sizeof(emotes));
    int p1 = random(sizeof(part1));
    int p2 = random(sizeof(part2));
    int p3 = random(sizeof(part3));
    int p4 = random(sizeof(part4));
    int p5 = random(sizeof(part5));
    int p6 = random(sizeof(part6));

    /*
     *  SPECIAL WIZARD CAROL: 
     *  This carol is a random parody of the Twelve Days of Christmas.  The
     *  "doers" array contains the names of people or animals doing something
     *  (i.e., geese) and the "doing" array contains their actions (i.e.,
     *  laying).  Note that single-syllable entries in the doers list require
     *  the addition of 'a-' (i.e., to form 'geese a-laying') to fit the
     *  melody, and two-syllable entries need a space at the end.    
     */

    string *doers = ({"lords a-", "ladies ", "pipers ", "drummers ",
        "maids a-", "geese a-", "swans a-", "wizards ", "mages ", "arches ",
        "keepers ", "newbies ", "dwarves a-", "elves a-", "goblins ",
        "gnomes a-", "humans ", "hobbits ", "players "});

    string *doing = ({"leaping", "dancing", "piping", "drumming", "milking",
        "swimming", "laying", "coding", "snooping", "testing", "drinking",
        "questing", "slaying", "running", "eating", "preening", "whining",
        "cheating"});

    /*
     *  The "rings" array contains phrases to substitute for the 5 gold rings 
     *  in the song, phrases for days 4, 3, and 2 are drawn from the "birds",
     *  "hens", and "doves", and the final combination comes from arrays
     *  "partridge" and "peartree".    
     */

    string *rings = ({"gold rings", "platinum coins", "Meg of RAM",
        "chitterlings", "underlings", "network pings", "goldenrods",
        "gold bricks"});

    string *birds = ({"calling birds", "calling cards", "cordless mice",
        "call girls", "cola nuts", "collared birds", "cabbage heads"});

    string *hens = ({"French hens", "French ticklers", "French fries",
        "Frenched hens", "French breads", "French cuffs", "French kisses",
        "French toasts"});

    string *doves = ({"turtle doves", "turtle waxes", "Dove bars",
        "turbaned doves", "turning doves", "turbid doves",
        "turtle gloves", "turbo-doves", "turgid doves",
        "turnip doves", "turtlenecks"});

    string *partridge = ({"partridge", "parsnip", "parasite", "parcel",
        "parchment", "parka", "parody", "parrot", "parakeet", "parson"});

    string *peartree = ({"pear tree", "bare tree", "parfait",
        "rare tree", "square tree", "pair of trees"});

    string dummy;  /*  General-purpose string variable.  */
    int i;  /*  General-purpose counter.  */

    /*
     *  End of special wizard carol variables.    
     */

    if (environment(to) != tp) /* The cane is not in the player's inventory.
        This means that the function is being called from a cane which is lying
        on the ground.  That's hardly a nice way to treat a candy cane! */

    {

        if (random(2))

        {

            write("You are about to sing a Christmas carol when" +
                " you are mesmerized by the sight of a " + query_short() +
                " wriggling along the ground! It slithers" +
                " away as you stand motionless and speechless.\n");

            say("A " + query_short() + " lying on the" +
                " ground suddenly springs to life and slithers away!\n");

        }

        else

        {

            write("You plant your feet firmly, preparing to" +
                " sing, when you suddenly notice that you've" +
                " planted one of them on a " + query_short() + "! " +
                " It's smashed so completely that" +
                " there's absolutely nothing left of it.\n");

            say(QCTNAME(tp) + " stomps on a " + query_short() +
                " that someone left lying on the ground" +
                " and completely destroys it. What's the problem -" +
                " did " + tp->query_pronoun() + " think it was a snake?\n");

        }

        destruct();

        return 1;

    }

    /*
     *  The query_wiz_level disables the shouted carol for mortals.  The 
     *  command "shout" has been changed and no longer accepts long strings as
     *  are used in the carols.  I'll think of an alternate 'special' carol for
     *  mortals and install it later; in the interim, there will be no
     *  shouting.
     *    
     */

    if (random(10) || !tp->query_wiz_level())

    {

        write("You sing a cheerful Yuletide carol: " + part1[p1] + part2[p2] +
            part3[p3] + part4[p4] + part5[p5] + part6[p6] + "\n");

        say(QCTNAME(tp) + emotes[e] + ": " + part1[p1] + part2[p2] + part3[p3]
            + part4[p4] + part5[p5] + part6[p6] + "\n");

    }

    else

    {

        if (!tp->query_wiz_level())  /* Player is mortal. */

        {

            write("You bellow a carol as loud as you can. ");

            if (!tp->query_option(OPT_ECHO)) write("You shout: " + part1[p1] +
                part2[p2] + part3[p3] + part4[p4] + part5[p5] + part6[p6] +
                "\n");

            say(QCTNAME(tp) + " bellows a carol as loud as " +
                tp->query_pronoun() + " can.\n");

            tp->command("shout " + part1[p1] + part2[p2] + part3[p3] +
                part4[p4] + part5[p5] + part6[p6]);

        }

        else  /* Player is wizard - use special wizard carol. */

        {

            /*
             *  Scramble the lists of doers and what they're doing.  Only the 
             *  first seven are needed for the song.    
             */

            for (i = 0; i < 7; i = i + 1)

            {

                p1 = random(sizeof(doers));
                dummy = doers[p1];
                doers[p1] = doers[i];
                doers[i] = dummy;
                p1 = random(sizeof(doing));
                dummy = doing[p1];
                doing[p1] = doing[i];
                doing[i] = dummy;

            }

            write("You sing a special carol that's a" +
                " favorite of Calian wizards:\n");

            say(QCTNAME(tp) + " sings a special carol that's a" +
                " favorite of Calian wizards:\n");

            tell_room(environment(tp),
                "On the twelfth day of Christmas, my true love" +
                " gave to me\n" +
                "  twelve " + doers[0] + doing[0] + "," +
                " eleven " + doers[1] + doing[1] + ",\n" +
                "  ten " + doers[2] + doing[2] + "," +
                " nine " + doers[3] + doing[3] + ",\n" +
                "  eight " + doers[4] + doing[4] + "," +
                " seven " + doers[5] + doing[5] + ",\n" +
                "  six " + doers[6] + doing[6] + "," +
                " five " + rings[random(sizeof(rings))] + ",\n" +
                "  four " + birds[random(sizeof(birds))] + "," +
                " three " + hens[random(sizeof(hens))] + "," +
                " two " + doves[random(sizeof(doves))] + ",\n" +
                "  and a " + partridge[random(sizeof(partridge))] +
                " in a "  + peartree[random(sizeof(peartree))] + "!\n");

        }

    }

    return 1;

}

// Function:  cane_lick

/*

Purpose:  lick the candy cane (may be directed toward a specific player).

Arguments:  object (this cane), [target]

Returns:  0/1

*/

int
cane_lick(string str)

{

    object tp = this_player();
    object to = this_object();
    object target;
    object cane_obj;

    if (!stringp(str)) return 0; /* Player did not specify what to lick; let
    the standard 'lick' command take over. */

    if (parse_command(str, all_inventory(tp) + all_inventory(environment(tp)),
        "%o %o", cane_obj, target))

    {

        if (!living(target)) return 0;  /*  Target is not living.  */
        if (cane_obj != to) return 0; /* Not this cane. */
        if (environment(to) != tp) return 0; /* Not in player inventory. */

        if (target == tp)  /* Player lick cane at himself. */

        {

            write("You make quite a spectacle of yourself," +
                " wrapping your tongue around the " + query_short() +
                " and licking it with long, indulgent" +
                " strokes, delighting in every subtle nuance of the" +
                " " + Flavor + " flavor.\n");

            say(QCTNAME(tp) + " makes quite a spectacle of " +
                tp->query_objective() + "self," +
                " wrapping " + tp->query_possessive() + " tongue around" +
                " the " + query_short() + " and licking" +
                " it with long, indulgent strokes, delighting" +
                " in every subtle nuance of the " + Flavor + " flavor.\n");

        }

        else  /* Player licks cane at somebody else. */

        {

            tp->catch_msg("You capture " + QTNAME(target) + "'s" +
                " attention by walking around " + target->query_objective() +
                " and slowly licking your " + query_short() +
                ", curling your tongue around it, and wafting some of" +
                " the " + Flavor + " scent in " + target->query_possessive() +
                " direction.\n");

            target->catch_msg(QCTNAME(tp) + " captures" +
                " your attention by walking around you and slowly" +
                " licking " + tp->query_possessive() +
                " " + query_short() +
                ", curling " + tp->query_possessive() + " tongue" +
                " around it and wafting some of the " + Flavor +
                " scent in your direction.\n");

            tell_room(environment(tp), QCTNAME(tp) +
                " captures " + QTNAME(target) + "'s attention" +
                " by walking around " + target->query_objective() +
                " and slowly licking " + tp->query_possessive() +
                " " + query_short() +
                ", curling " + tp->query_possessive() + " tongue" +
                " around it and wafting some of the " + Flavor +
                " scent in " + target->query_possessive() +
                " direction.\n", ({tp, target}));

        }

        return 1;

    }

    if (present(str, tp) == to)

    {

        write("You lick the " + query_short() +
            " lustily, obviously enjoying its " + Flavor + " flavor.\n");

        say(QCTNAME(tp) + " licks " + tp->query_possessive() +
            " " + query_short() + " lustily, obviously enjoying" +
            " its " + Flavor + " flavor.\n");

        return 1;

    }

    return 0;

}

// Function:  cane_smell

/*

Purpose:  smell the candy cane, or a player who may have just nibbled on one.

Arguments:  object (this cane), [target]

Returns:  0/1

*/

int
cane_smell(string str)

{

    object tp = this_player();
    object to = this_object();
    object target;
    object cane_obj;
    object temp_obj;

    if (!stringp(str)) /* Player did not specify what to smell. */

    {

        write("You smell.\n");

        say(QCTNAME(tp) + " smells.\n");

        return 1;

    }

    if (parse_command(str, all_inventory(tp) + all_inventory(environment(tp)),
        "%o %o", cane_obj, target))

    {

        /*
         * If two objects are specified for this function, one must be the cane 
         *  and the other can be almost anything.  Flip the order of the
         *  objects if the player puts the candy cane in the second position.
         *    
         */

        if (target == to)

        {

            temp_obj = target;
            target = cane_obj;
            cane_obj = temp_obj;

        }

        if (cane_obj != to) return 0; /* Not this cane. */
        if (environment(to) != tp) return 0; /* Not in player inventory. */

        if (target == tp)

        {

            write("You rub the " + query_short() + " all over your" +
                " body so that you will smell like " + Flavor + ".\n");

            say(QCTNAME(tp) + " rubs the " + query_short() +
                " all over " + tp->query_possessive() +
                " body so that " + tp->query_pronoun() +
                " will smell like " + Flavor + ".\n");

            return 1;

        }

        if (!living(target))  /* Target is inanimate. */

        {

            write("You compare the smells of the " + query_short() +
                " and the " + target->query_short() + ". It's" +
                " a bit unclear which one you prefer.\n");

            say(QCTNAME(tp) + " compares the smells of the " + query_short() +
                " and the " + target->query_short() + ". It's" +
                " a bit unclear which one " + tp->query_pronoun() +
                " prefers.\n");

        }

        else  /* Target is living. */

        {

            tp->catch_msg("You smell " + QTNAME(target) +
                "'s breath to check whether " + target->query_pronoun() +
                " has been nibbling on your " + query_short() + ".\n");

            target->catch_msg(QCTNAME(tp) + " smells your" +
                " breath to check whether you have been nibbling" +
                " on " + tp->query_possessive() +
                " " + query_short() + ".\n");

            tell_room(environment(tp),
                QCTNAME(tp) + " smells " + QTNAME(target) +
                "'s breath to check whether " + target->query_pronoun() +
                " has been nibbling on " + tp->query_possessive() +
                " " + query_short() + ".\n",
                ({tp, target}));

        }

        return 1;

    }

    if (present(str, tp) == to)

    {

        write("You hold the " + query_short() + " under your" +
            " nose and inhale deeply, enjoying the concentrated aroma" +
            " of " + Flavor + ".\n");

        say(QCTNAME(tp) + " holds a " + query_short() +
            " under " + tp->query_possessive() + " nose" +
            " and inhales deeply, rolling " + tp->query_possessive() +
            " head back, drooling slightly, and murmuring, 'mmmmmm... " +
            Flavor + "!'\n");

        return 1;

    }

    return 0;

}

// Function:  cane_crunch

/*

Purpose:  crunch on the candy cane with your teeth, or crunch the candy cane
against another player.  This function will wear out the candy cane quickly.

Arguments:  object (this cane), [target]

Returns:  0/1

*/

int
cane_crunch(string str)

{

    object tp = this_player();
    object to = this_object();
    object target;
    object cane_obj;

    if (!stringp(str)) /* Player did not specify what to crunch. */

    {

        write("You get down on the ground and do an" +
            " abdominal crunch. This exercise will certainly" +
            " work off the extra calories you'll take in" +
            " from eating candy canes!\n");

        say(QCTNAME(tp) + " gets down on the ground and does an" +
            " abdominal crunch, as if this exercise will" +
            " work off the calories in all the candy" +
            " canes " + tp->query_pronoun() + " has been eating!\n");

        return 1;

    }

    if (parse_command(str, all_inventory(tp) + all_inventory(environment(tp)),
        "%o %o", cane_obj, target))

    {

        if (cane_obj != to) return 0; /* Not this cane. */
        if (environment(to) != tp) return 0; /* Not in player inventory. */
        if (!living(target)) return 0;  /* Target is inanimate. */

        if (target == tp)  /* Player crunches cane at himself. */

        {

            write("You grip the " + query_short() + " tightly and" +
                " hear a slight crunch, but it doesn't look" +
                " like it's damaged very badly.\n");

            say(QCTNAME(tp) + " grips a " + query_short() + " tightly and" +
                " hears a slight crunch, but it doesn't look" +
                " like it's damaged very badly.\n");

        }

        else  /* Player crunches cane at somebody else. */

        {

            tp->catch_msg("You attempt to make a point" +
                " about Yule celebrations to " + QTNAME(target) +
                " by poking " + target->query_objective() +
                " with the " + query_short() + ", but when you do" +
                " you hear a slight crunch. Still, the candy" +
                " cane doesn't look like it's badly damaged.\n");

            target->catch_msg(QCTNAME(tp) + " attempts to drive" +
                " home a point about Yule celebrations by poking you with" +
                " a " + query_short() + ", but when " + tp->query_pronoun() +
                " does you hear a slight crunch. Still, the candy" +
                " cane doesn't look like it's badly damaged.\n");

            tell_room(environment(tp),
                QCTNAME(tp) + " attempts to make a point" +
                " about Yule celebrations to " + QTNAME(target) +
                " by poking " + target->query_objective() +
                " with a " + query_short() +
                ", but when " + tp->query_pronoun() + " does you" +
                " hear a slight crunch. Still, the candy" +
                " cane doesn't look like it's badly damaged.\n",
                ({tp, target}));

        }

        if (wildmatch("slightly*", query_short()))

        {

            write("You figure that you'd finish eat your " + query_short() +
                " before it falls apart. ");

            tp->command("eat " + query_short());

        }

        else

        {

            set_short("slightly cracked " + query_short());
            add_name(query_short());

        }

        return 1;

    }

    if (present(str, tp) == to)

    {

        write("You gleefully crunch on your " + query_short() +
            ", thoroughly enjoying the tiny " + Flavor +
            "-flavored bits that pop into your mouth.\n");

        say(QCTNAME(tp) + " gleefully crunches on a " + query_short() +
            " and seems to thoroughly enjoy the taste of the " + Flavor +
            "-flavored bits that pop into " + tp->query_possessive() +
            " mouth.\n");

        if (wildmatch("slightly*", query_short()))

        {

            write("You figure that you'd better eat your " + query_short() +
                " before it falls apart.\n");

            tp->command("eat " + query_short());

        }

        else

        {

            set_short("slightly chewed " + query_short());
            add_name(query_short());

        }

        return 1;

    }

    return 0;

}

// Function:  cane_tuck

/*

Purpose:  tuck the candy cane in a safe place, either on your own person or on
someone else's.

Arguments:  object (this cane), [target]

Returns:  0/1

*/

int
cane_tuck(string str)

{

    object tp = this_player();
    object to = this_object();
    object target;
    object cane_obj;

    if (!stringp(str)) /* Player did not specify what to tuck. */

    {

        write("You drop into a tuck position, crouching over" +
            " your " + query_short() + " so that nobody can take" +
            " it away from you or even look at it.\n");

        say(QCTNAME(tp) + " drops into a tuck position, crouching" +
            " over " + tp->query_possessive() + " " + query_short() +
            " so that nobody can take it away from " +
            tp->query_objective() + " or even look at it.\n");

        return 1;

    }

    if (parse_command(str, all_inventory(tp) + all_inventory(environment(tp)),
        "%o %o", cane_obj, target))

    {

        if (cane_obj != to) return 0; /* Not this cane. */
        if (environment(to) != tp) return 0; /* Not in player inventory. */

        if (target == tp)  /* Player tucks cane at himself. */

        {

            write("You tuck the " + query_short() + " in a place" +
                " where no one will see it.\n");

            say(QCTNAME(tp) + " tucks the " + query_short() + " in a place" +
                " where no one will see it.\n");

        }

        else if (!living(target))  /* Target is inanimate. */

        {

            /*
             * You can tuck the cane into armour unless it's broken.   
             */

            if (target->check_armour())

            {

                if (target->query_prop("OBJ_I_BROKEN"))

                {

                    write("But it's broken!\n");

                    say(QCTNAME(tp) + " tries to tuck a " + query_short() +
                        " into " + tp->query_possessive() + " " +
                        target->query_short() + " but fails.\n");

                }

                else

                {

                    write("You tuck the " + query_short() + " into your " +
                        target->query_short() + " for safekeeping.\n");

                    say(QCTNAME(tp) + " tucks a " + query_short() +
                        " into " + tp->query_possessive() +
                        " " + target->query_short() + " for safekeeping.\n");

                }

            }

            else write("You can't tuck your candy cane there.\n");

        }

        else  /* Player tucks cane onto somebody else. */

        {

            tp->catch_msg("You tuck the " + query_short() + " behind " +
                QTNAME(target) + "'s ear.\n");

            target->catch_msg(QCTNAME(tp) + " tucks a " + query_short() +
                " behind your ear.\n");

            tell_room(environment(tp),
                QCTNAME(tp) + " tucks a " + query_short() +
                " behind " + QTNAME(target) + "'s ear.\n",
                ({tp, target}));

            move(target);

        }

        return 1;

    }

    if (present(str, tp) == to)

    {

        write("You tuck the " + query_short() +
            " behind your ear for safekeeping.\n");

        say(QCTNAME(tp) + " tucks a " + query_short() +
            " behind " + tp->query_possessive() +
            " ear for safekeeping.\n");

        return 1;

    }

    return 0;

}

// Function:  cane_suck

/*

Purpose:  suck the candy cane, making an irritating noise (noise may be
directed at a particular target)

Arguments:  object (this cane), [target]

Returns:  0/1

*/

int
cane_suck(string str)

{

    object tp = this_player();
    object to = this_object();
    object target;
    object cane_obj;

    if (!stringp(str)) /* Player did not specify what to suck. */

    {

        write("You suck.\n");
        say(QCTNAME(tp) + " sucks.\n");
        return 1;

    }

    if (parse_command(str, all_inventory(tp) + all_inventory(environment(tp)),
        "%o %o", cane_obj, target))

    {

        if (!living(target)) return 0;  /*  Target is not living.  */
        if (cane_obj != to) return 0; /* Not this cane. */
        if (environment(to) != tp) return 0; /* Not in player inventory. */

        if (target == tp)  /* Player sucks cane at himself. */

        {

            write("You become totally engrossed in the process" +
                " of sucking all the " + Flavor + " flavor out" +
                " of the " + query_short() + ".\n");

            say(QCTNAME(tp) + " twitches and wriggles with delight" +
                " and makes outrageous slurping noises" +
                " as " + tp->query_pronoun() + " becomes totally" +
                " engrossed in the process of sucking" +
                " all the " + Flavor + " flavor out" +
                " of " + tp->query_possessive() + " " + query_short() +
                " .\n");

        }

        else  /* Player waves cane at somebody else. */

        {

            tp->catch_msg("You walk up next to " + QTNAME(target) +
                " and make loud sucking noises" +
                " with your " + query_short() + " right" +
                " in " + target->query_possessive() + " ear!\n");

            target->catch_msg(QCTNAME(tp) + " walks up next" +
                " to you and makes loud sucking noises" +
                " with " + tp->query_possessive() + " " + query_short() +
                " right in your ear!\n");

            tell_room(environment(tp),
                QCTNAME(tp) + " walks up next" +
                " to " + QTNAME(target) + " and makes loud" +
                " sucking noises with " + tp->query_possessive() +
                " " + query_short() + " right in" +
                " " + target->query_possessive() + " ear!\n",
                ({tp, target}));

        }

        return 1;

    }

    if (present(str, tp) == to)

    {

        write("You make loud obnoxious sucking noises as you" +
            " attempt to extract every last bit of " + Flavor +
            " flavor from your " + query_short() + ".\n");

        say(QCTNAME(tp) + " makes loud obnoxious sucking noises" +
            " as " + tp->query_pronoun() + " attempts to extract" +
            " every last bit of " + Flavor + " flavor" +
            " from " + tp->query_possessive() +
            " " + query_short() + ".\n");

        return 1;

    }

    return 0;

}

// Function:  cane_wave

/*

Purpose:  wave the candy cane around to let other people appreciate its aroma.
You can wave it around in general or under the nose of a particular living
object.

Arguments:  object (this cane), [target]

Returns:  0/1

*/

int
cane_wave(string str)

{

    object tp = this_player();
    object to = this_object();
    object target;
    object cane_obj;

    if (!stringp(str)) return 0; /* Player did not specify what to wave. */

    if (parse_command(str, all_inventory(tp) + all_inventory(environment(tp)),
        "%o %o", cane_obj, target))

    {

        if (!living(target)) return 0;  /*  Target is not living.  */
        if (cane_obj != to) return 0; /* Not this cane. */
        if (environment(to) != tp) return 0; /* Not in player inventory. */

        if (target == tp)  /* Player waves cane at himself. */

        {

            write("You wave the " + query_short() +
                " under your own nose as you savor its" +
                " distinctive aroma of " + Flavor + ".\n");

            say(QCTNAME(tp) + " waves the " + query_short() +
                " under " + tp->query_possessive() + " nose" +
                " as " + tp->query_pronoun() + " savors" +
                " its distinctive aroma of " + Flavor + ".\n");

        }

        else  /* Player waves cane at somebody else. */

        {

            tp->catch_msg("You wave the " + query_short() +
                " under " + QTNAME(target) +
                "'s nose so that " + target->query_pronoun() +
                " can fully appreciate its" +
                " distinctive aroma of " + Flavor + ".\n");

            target->catch_msg(QCTNAME(tp) +
                " waves the " + query_short() +
                " under your nose so that you can" +
                " fully appreciate its distinctive" +
                " aroma of " + Flavor + ".\n");

            tell_room(environment(tp),
                QCTNAME(tp) + " waves the " + query_short() +
                " under " + QTNAME(target) +
                "'s nose so that " + target->query_pronoun() +
                " can fully appreciate its distinctive aroma" +
                " of " + Flavor + ".\n", ({tp, target}));

        }

        return 1;

    }

    if (present(str, tp) == to)

    {

        write("You wave the " + query_short() +
            " around so that everyone" +
            " can fully appreciate its" +
            " distinctive aroma of " + Flavor + ".\n");

        say(QCTNAME(tp) + " waves the " + query_short() +
            " around so that everyone can fully appreciate" +
            " its distinctive aroma of " + Flavor + ".\n");

        return 1;

    }

    return 0;

}

// Function:  cane_deck

/*

Purpose:  deck the halls with boughs of holly.  To be eligible for decking, one
of two conditions must be met:

 The filename of the room fits one            The player using the cane is a
 of the patterns in the "approved"   -or-                 wizard.
            list below.

Mortals are limited to three uses of the "deck" function before their canes
need recharging.  Recharging occurs automatically 60 seconds after the cane is
exhausted.

Arguments:  none

Returns:  1

*/

int
cane_deck()

{

    object tp = this_player();
    object to = this_object();
    object this_room = environment(tp);
    object bough = present("magic_holly_bough", this_room);
    string room_name = file_name(this_room);
    int x = random(5);

    if (environment(to) != tp) /* The cane is not in the player's inventory.
        This means that the function is being called from a cane which is lying
        on the ground.  That's hardly a nice way to treat a candy cane! */

    {

        if (random(2))

        {

            write("You obviously didn't notice the " + query_short() +
                " lying at your feet - it jumps up, decks you," +
                " and then flies out of the room!.\n");

            say("A " + query_short() + " suddenly jumps off" +
                " the floor and slams into " + QTNAME(tp) +
                ", sending " + tp->query_objective() +
                " sprawling on the floor, then flies out of the room!\n");

        }

        else

        {

            write("A " + query_short() + " lying at" +
                " your feet suddenly explodes! You hit the deck" +
                " to avoid being struck by the flying bits of sugar.\n");

            say("A " + query_short() + " lying on" +
                " the ground suddenly emits a loud 'pop!' and" +
                " vaporizes into a million bits. The sound" +
                " startles " + QTNAME(tp) +
                " so badly that " + tp->query_pronoun() +
                " hits the deck!\n");

        }

        remove_object();

        return 1;

    }

    /*
     * Perform security and power check if not a wizard.   
     */

    if (!tp->query_wiz_level())

    {

        /*
         *  APPROVED LOCATIONS LIST: 
         *  Add the filename patterns for all approved areas to the 'if'
         *  statement below.    
         */

        if (!(this_room->query_prop(ROOM_I_INSIDE) &&
            (wildmatch("/d/Ansalon/estwilde/iron_delving*", room_name)
            || wildmatch("/d/Ansalon/guild/dwarf/*", room_name)
            || wildmatch("/d/Ansalon/guild/kender/room/*", room_name)
            || wildmatch("/d/Krynn/solamn/vin/*", room_name)
            || wildmatch("/d/Genesis/start/human/t*", room_name)
            || wildmatch("/d/Calia/palace*", room_name)
            || wildmatch("/d/Calia/guilds/calians*", room_name)
            || wildmatch("/d/Calia/domain*", room_name)
            || wildmatch("/d/Calia/gelan/cadet*", room_name))))

        {

            write("Decking the halls is prohibited in this area.\n");
            return 1;

        }

        if (Charge)

        {

            Charge = Charge - 1;

            if (!Charge)

            {

                set_alarm(5.0, 0.0, "cane_exhaust");
                set_alarm(60.0, 0.0, "cane_recharge");

            }

        }

        else

        {

            write("Your " + query_short() + " sputters and emits" +
                " a faint smell of burnt sugar.\n");

            say(QCTNAME(tp) + "'s " + query_short() + " sputters" +
                " and emits a faint smell of burnt sugar.\n");

            return 1;

        }

    }

    switch (x)

    {

        case 0:

            write("You point your " + query_short() + " at a wall" +
                " and deck it with a bough of holly!\n");

            say(QCTNAME(tp) + " points " + tp->query_possessive() +
                " " + query_short() + " at a wall and decks it with" +
                " a bough of holly!\n");

            break;

        case 1:

            write("You say a few magic words over your " + query_short() +
                " and a bough of holly suddenly appears on the wall!\n");

            say(QCTNAME(tp) + " says a few magic words over " +
                tp->query_possessive() + " " + query_short() + " and" +
                " a bough of holly suddenly appears on the wall!\n");

            break;

        case 2:

            write("You shout 'take that, Scrooge and Marley!'" +
                " and wave your " + query_short() + " in the air, and" +
                " with a crash of thunder and lightning a" +
                " bough of holly appears on the wall!\n");

            say(QCTNAME(tp) + " shouts 'take that, Scrooge" +
                " and Marley!' and waves " + tp->query_possessive() +
                " " + query_short() + " in the air, and with a" +
                " crash of thunder and lightning a bough of" +
                " holly appears on the wall!\n");

            break;

        case 3:

            write("You deftly perform the Dance of the Sugar" +
                " Plum Fairy, using your " + query_short() +
                " for balance. As you finish the final pirouette," +
                " a bough of holly appears from out of" +
                " nowhere and affixes itself to the wall!\n");

            say(QCTNAME(tp) + " deftly performs the Dance of" +
                " the Sugar Plum Fairy, using " + tp->query_possessive() +
                " " + query_short() + " for balance. As " + tp->query_pronoun()
                + " finishes the final pirouette," +
                " a bough of holly appears from out of" +
                " nowhere and affixes itself to the wall!\n");

            break;

        default:

            write("You gesture mysteriously with your " + query_short() +
                " and concentrate. Eventually, a strange" +
                " green cloud forms, which takes the shape" +
                " of a decorative holly bough and comes to rest on" +
                " one of the walls.\n");

            say(QCTNAME(tp) + " gestures mysteriously with " +
                tp->query_possessive() + " " + query_short() +
                " and concentrates. Eventually, a strange" +
                " green cloud forms, which takes the shape" +
                " of a decorative holly bough and comes to rest on" +
                " one of the walls.\n");

    }

    if (bough) bough->bough_upgrade();

    else

    {

        bough = clone_object("/d/Calia/yuleware/bough.c");
        bough->move(this_room);

    }

    return 1;

}

// Function:  cane_exhaust

/*

Purpose:  Alter the cane's appearance when it is exhausted by repeated use of
the "deck" function.

Arguments:  none

Returns:  nothing

*/

void
cane_exhaust()

{

    write("Your " + query_short() + " droops," +
        " obviously suffering from exhaustion.\n");

    say(QCTNAME(this_player()) + "'s " + query_short() + " droops," +
        " obviously suffering from exhaustion.\n");

    set_short("limp " + query_short());

}

// Function:  cane_recharge

/*

Purpose:  recharges the candy cane's "deck" function.  There's no message to
the owner regarding the cane's recovery - I want it to be a surprise.

Arguments:  none

Returns:  nothing

*/

void
cane_recharge()

{

    string *work_array = explode(query_short(), " ");

    if (member_array("limp", work_array) == -1) return; /* No recharge
        needed.*/

    Charge = random(3) + 3;
    work_array = work_array - ({"limp"});
    set_short(implode(work_array, " "));

}

// Function:  init

/*

Purpose:  define commands available in this object (called by system when
object enters a player's inventory)

Arguments:  none

Returns:  nothing

*/

void
init()

{

    ::init();
    add_action(cane_carol, "carol");
    add_action(cane_wave, "wave");
    add_action(cane_suck, "suck");
    add_action(cane_lick, "lick");
    add_action(cane_tuck, "tuck");
    add_action(cane_smell, "smell");
    add_action(cane_crunch, "crunch");
    add_action(cane_deck, "deck");

}
