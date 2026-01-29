// OBJECT:  yuletree

    /* Calia Domain

    HISTORY

    [98/12/22] Created by Uhclem from [D:\CALIA\YULEWARE\YULETREE.DOC].

    PURPOSE

    A Christmas decoration (and candy cane dispenser) for the domain office in
    the Tower of Realms. */

// INCLUSIONS AND DEFINITIONS

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>

// GLOBAL VARIABLES

string *Ornaments = ({"star", "angel", "ball", "snowflake", "icicle", "bell",
    "drum", "horn", "harp", "reindeer", "sleigh", "pinecone", "nutcracker",
    "bow"});

string *Colors = ({"gold", "silver", "blue", "yellow", "pink", "white",
    "purple", "mauve", "aquamarine", "orange", "copper", "red", "magenta",
    "indigo"});

int Ready_to_dispense = 1;  /*  Indicates whether a cane is available.  */

int Drop_count = random(5);  /*  Counts items that fall off the tree, with a
    random starting point to vary how quickly players will reach 10, the level
    at which Jinglefrog and Frudolph take corrective action.  */

// OBJECT DEFINITION

void
create_object()

    {

    /* VARIABLES */

    string *trees = ({"fir", "spruce", "pine", "balsam", "cedar"});
    int i;  /*  General purpose counter.  */

    /*  The values for Ornaments and Colors in the GLOBAL VARIABLES section are
        the universe from which the ornament descriptions will be generated.
        Next step is to delete random items from the arrays until only five
        remain in each.  */

    while(sizeof(Ornaments) > 7)

        {

        Ornaments = Ornaments - ({Ornaments[random(sizeof(Ornaments))]});

        }

    while(sizeof(Colors) > 7)

        {

        Colors = Colors - ({Colors[random(sizeof(Colors))]});

        }

    /*  DESCRIPTION  */

    set_name(trees[random(sizeof(trees))] + " tree");
    set_short("gaily decorated " + query_name());
    add_name("tree");

    set_long("It's a beautiful evergreen tree covered" +
        " with holiday decorations including candles," +
        " ornaments, and candy canes. The sparkling light that" +
        " emanates from it radiates through the entire" +
        " room, making the atmosphere cheerful and putting you" +
        " in a jovial mood. You walk around the tree carefully" +
        " as you examine it, lest you shake it and knock off" +
        " any of the decorations.\n");

    /*  PROPERTIES  */

    add_prop(OBJ_M_NO_GET,
        "A ghost suddenly appears, bound in chains and weighed" +
        " down by ledgers and money-boxes. He scolds you," +
        " saying, 'Anyone who would steal a Christmas tree should" +
        " be boiled in his own pudding and buried with a stake" +
        " of holly through his heart!'\n" +
        "You decide to leave the tree right where it is," +
        " and the apparition disappears.\n");

    add_prop(OBJ_I_WEIGHT,  50000);
    add_prop(OBJ_I_VOLUME, 150000);
    add_prop(OBJ_I_VALUE, 0);
    setuid();  /*  "uid" settings required for cloning candy canes. */
    seteuid(getuid());

    /*  ITEMS  */

    add_item(({"ornament", "ornaments", "sparkling ornaments",
        "decoration", "decorations"}),
        "You see so many ornaments on the " + query_short() +
        " that you can hardly look at just one. There" +
        " are " + implode(Ornaments, "s, ") + "s, and candy" +
        " canes that reflect the warm glow of the" +
        " candles. Whoever did the decoration obviously spent a" +
        " lot of time on it and secured the ornaments so that" +
        " you can't easily take them from the tree.\n");

    add_item(({"candle", "candles", "white candle", "white candles"}),
        "How odd - the candles are all lit, yet they show no" +
        " signs of burning down!  They are all pure white" +
        " and provide just enough light to illuminate the" +
        " ornaments and make them sparkle.\n");

    add_item(({"cane", "canes", "candy cane", "candy canes"}),
        "The candy canes come in a myriad of colors and they" +
        " look edible - in fact, they look downright delicious - but" +
        " try as you may, you simply can't seem to" +
        " take one off the tree.\n");

    for (i = 0; i < 7; i = i + 1)

        {

        add_item(({Ornaments[i], Colors[i] + " " + Ornaments[i],
            Ornaments[i] + "s", Colors[i] + " " + Ornaments[i] + "s"}),
            "You see many little sparkling " + Ornaments[i] +
            "s on the tree. Each one is made of a delicate " + Colors[i] +
            " crystalline material and reflects the warm glow of" +
            " the candles.\n");

        }

    /*  The "pieces" item is here so that a player may examine them after he
        has smashed an ornament with the tree_shake function.  */

    add_item(({"pieces", "piece"}),
        "You look in vain for pieces of a broken ornament," +
        " but it seems they have all disappeared. Whatever" +
        " the ornaments are made of may be beautiful, but" +
        " it certainly isn't durable!\n");

    }

// FUNCTIONS

// Function:  tree_reload

/*

Purpose:  Make a candy cane available which can be released by the tree_shake
function.  The idea behind the timing routines in this object and the many
self-destruct (or compulsory eat) functions in the canes is to allow players to
gather a few canes to give to their friends but prevent them from stockpiling
huge heaps of them.  Canes, that is, not friends.

Arguments:  none

Returns:  nothing

*/

void
tree_reload()

    {

    if (Drop_count < 10) Ready_to_dispense = 1;

    }

// Function:  tree_attach

/*

Purpose:  attach the ornaments securely to the tree so they can't be shaken
off.  This function is called after more than 10 ornaments and/or canes have
been shaken off the tree.  To be loosen them up, a player has to try to take
something directly off the tree.

Arguments:  none

Returns:  nothing

*/

void
tree_attach()

    {

    if (random(2)) tell_room(environment(this_object()),
        "A tiny green frog hops into view dragging a bag of ornaments.\n" +
        "The tiny green frog jumps into the tree, finds the" +
        " empty spaces where ornaments have fallen off, and" +
        " attaches a few sparkling " + Ornaments[random(2)] +
        "s and " + Ornaments[random(2)+3] + "s. He climbs about" +
        " the tree, making sure that all the ornaments and" +
        " candy canes are securely fastened so that they can't" +
        " be shaken off, then jumps back down to" +
        " the ground and disappears.\n");

    else tell_room(environment(this_object()),
        "A tiny red frog hops into view dragging a bag of ornaments.\n" +
        "The tiny red frog climbs into the tree, muttering" +
        " something to herself about the price of " +
        Ornaments[random(sizeof(Ornaments))] + "s, and" +
        " replaces some missing ornaments. Then she makes sure" +
        " that all the ornaments and candy canes are securely" +
        " attached so they won't fall off, hops back down to" +
        " the ground, and disappears.\n");

    Ready_to_dispense = 0;

    }

// Function:  tree_shake

/*

Purpose:  shake the tree and knock off an ornament.  If the player doesn't have
a candy cane and there is no candy cane lying about in the room and the tree is
ready to dispense, one will fall off the tree.  Otherwise, something else will
happen purely for visual effect.

Arguments:  object (this tree)

Returns:  0/1

*/

int
tree_shake(string str)

    {

    object tp = this_player();
    object to = this_object();
    object candy_cane;
    int i;  /*  General purpose counter.  */

    if (!stringp(str)) return 0; /* Player did not specify what to shake. */

    if (present(str, environment()) == to)  /*  Player shakes this tree.  */

        {

        if (!Ready_to_dispense)  /*  Cane is not currently available.  */

            {

            write("You shake the " + query_short() + ".\n");
            say(QCTNAME(tp) + " shakes the " + query_short() + ".\n");

            i = random(10);
            switch (i)

                {

                case 0:

                tell_room(environment(),
                    "The tree quivers and jiggles like a bowl" +
                    " full of jelly, making the ornaments" +
                    " twinkle as they dance in the soft" +
                    " light radiating from the candles.\n");

                break;

                case 1:

                tell_room(environment(),
                    "The tree shakes so hard that the" +
                    " candles flicker and nearly go out, but" +
                    " when the motion has subsided you can see that" +
                    " all of them are still lit.\n");

                break;

                case 2:

                tell_room(environment(),
                    "A few needles fall from the tree," +
                    " but they magically disappear before" +
                    " they reach the ground. You stand" +
                    " amazed at this wonderful tree that" +
                    " cleans up after itself!\n");

                break;

                case 3:

                tell_room(environment(),
                    "The tree nearly falls over!  It sways" +
                    " precariously for a second, then settles" +
                    " back in its place.\n");

                break;

                case 4:

                tell_room(environment(),
                    "A little " + Colors[1] + " " + Ornaments[1] +
                    " and a little " + Colors[3] +
                    " " + Ornaments[3] + " hanging side by side" +
                    " bump into each other and make a cheery" +
                    " little 'ping' each time they meet.\n");

                break;

                case 5:

                tell_room(environment(),
                    "Two little " + Colors[2] + " " + Ornaments[2] + "s" +
                    " hanging close together vibrate in" +
                    " harmony, ringing out a wavering, ethereal" +
                    " tone that is gradually picked up by" +
                    " other ornaments and then" +
                    " mysteriously fades away.\n");

                break;

                case 6:

                tell_room(environment(),
                    "One of the little " +
                    Ornaments[random(sizeof(Ornaments))] +
                    " ornaments is pushed into a candle flame by the" +
                    " rocking motion!  It burns with a" +
                    " brief but brilliant burst of " +
                    Colors[random(sizeof(Colors))] +
                    " light which suddenly winks out, leaving no" +
                    " trace of the ornament behind.\n");

                break;

                case 7:

                tell_room(environment(),
                    "A shock wave travels the length of the" +
                    " tree, causing the sparkling ornaments" +
                    " to produce ripples of " + implode(Colors[0..3], ", ") +
                    ", and " + Colors[4] + " that race up" +
                    " and down, captivating your attention for" +
                    " a few seconds until the tree is still again.\n");

                break;

                case 8:

                write("A little " + Ornaments[random(sizeof(Ornaments))] +
                    " ornament swings wildly and bonks you in" +
                    " the head!  You peer at the tree and cannot" +
                    " fathom how the ornament could have swung" +
                    " out so far.\n");

                say("A little " + Ornaments[random(sizeof(Ornaments))] +
                    " ornament swings wildly and bonks " + QTNAME(tp) +
                    " in the head!  You peer at the tree and" +
                    " cannot fathom how the ornament could have" +
                    " swung out so far.\n");

                break;

                default:

                tell_room(environment(),
                    "The ornaments on the tree swing wildly, sparkling" +
                    " in the light from the candles and" +
                    " dazzling you with reflections" +
                    " of " + implode(Colors[0..5], ", ") +
                    ", and " + Colors[6] + ".\n");

                }

            Drop_count = Drop_count + 1;

            if (Drop_count == 10)

                {

                if (random(2)) tell_room(environment(),
                    "Two tiny frogs hops into view, one bright" +
                    " red and the other bright green. They peer" +
                    " at the tree, which continues to sway a" +
                    " bit. The two frogs whisper something to" +
                    " each other, then hop out of sight.\n");

                else tell_room(environment(),
                    "A tiny red frog hops in.\n" +
                    "A tiny green frog hops in.\n" +
                    "The frogs hop around the base of" +
                    " the " + query_short() + ", looking for" +
                    " any places where ornaments have fallen," +
                    " glance about the room briefly, and" +
                    " then hop away.\n");

                set_alarm(10.0, 0.0, tree_attach);

                }

            return 1;

            }

        if ((present("striped candy cane", tp)) ||
            (present("striped candy cane", environment())))
            /* Player already has a cane, or a cane is lying on the floor. */

            {

            i = random(sizeof(Ornaments));

            write("You shake the " + query_short() + " and knock off" +
                " a little " + Colors[i] + " " + Ornaments[i] +
                " which smashes into a million pieces!\n");

            say(QCTNAME(tp) + " shakes the " + query_short() +
                " and knocks off a little " + Colors[i] +
                " " + Ornaments[i] + " which smashes" +
                " into a million pieces!\n");

            /*  If you knock an ornament off the tree, no canes are available
                for 15 seconds.  */

            Ready_to_dispense = 0;
            set_alarm(15.0, 0.0, tree_reload);

            }

        else  /*  Player has no candy cane.  Put one in the room.  */

            {

            candy_cane = clone_object("/d/Calia/yuleware/candy_cane");
            candy_cane->move(environment());

            write("You shake the " + query_short() + " and knock off" +
                " a little " + candy_cane->query_short() + ". " +
                " It bounces on the floor and lands at your feet.\n");

            say(QCTNAME(tp) + " shakes the " + query_short() +
                " and knocks off a little " + candy_cane->query_short() +
                ". It bounces on the floor and lands at " +
                tp->query_possessive() + " feet.\n");

            /*  If you dispense a candy cane, no more are available for 30
                seconds.  */

            Ready_to_dispense = 0;
            set_alarm(30.0, 0.0, tree_reload);

            }

        Drop_count = Drop_count + 1;

        if (Drop_count == 10)

            {

            if (random(2)) tell_room(environment(),
                "A tiny green frog hops into view.\n" +
                "The tiny green frog looks at all the places on" +
                " the " + query_short() + " where ornaments" +
                " have been knocked off, scratches his" +
                " head, and hops away.\n");

            else tell_room(environment(),
                "A tiny red frog hops into view.\n" +
                "The tiny red frog peers at the " + query_short() +
                " and seems to be wondering why some" +
                " ornaments are missing. She glances at you" +
                " for a moment, raises her eyebrow slightly, and" +
                " then hops away.\n");

            set_alarm(10.0, 0.0, tree_attach);

            }

        return 1;

        }

    return 0;

    }

// Function:  tree_relight

/*

Purpose:  relight a candle after a player has extinguished one (by "take
candle")

Arguments:  none

Returns:  nothing

*/

void
tree_relight()

    {

    if (random(2)) tell_room(environment(this_object()),
        "A tiny green frog, sporting a miniature set of antlers" +
        " and a bright red rubber nose, comes hopping into" +
        " the room carrying a lit match in his mouth. He" +
        " scrambles up the tree and relights a candle that has" +
        " gone out, then blows out the match and merrily hops away.\n");

    else tell_room(environment(this_object()),
        "You hear the sound of approaching jingle" +
        " bells!\nA tiny red frog, wearing a striped stocking" +
        " cap topped with a bell, hops into the room. She jumps into the" +
        " tree, finds a candle that has gone out, and relights it" +
        " from one of the other candles. Then she jumps back down" +
        " to the floor and out of the room.\n");

    }

// Function:  tree_loosen

/*

Purpose:  loosen the candy canes so they can be shaken off (called by tree_take
and needed after tree_attach).

Arguments:  none

Returns:  nothing

*/

void
tree_loosen()

    {

    if (random(2)) tell_room(environment(this_object()),
        "The candy canes on the " + query_short() + " sway and" +
        " glimmer in the soft light of the candles, and you get" +
        " the impression that one or two of them may have" +
        " been loosened when the tree was disturbed.\n");

    else tell_room(environment(this_object()),
        "A tiny red frog hops in to check the condition of" +
        " the " + query_short() + ". She climbs into the tree" +
        " and inspects every ornament from bottom to top, then jumps" +
        " down to the ground with a mighty kick that makes" +
        " the whole tree quiver. As she hops out of sight, you" +
        " notice that her kick seems to have loosened some" +
        " candy canes hanging on the tree.\n");

    Drop_count = 0;

    }

// Function:  tree_take

/*

Purpose:  take something from the tree.  It's impossible, of course - the
ornaments are far too well secured!

Arguments:  string in the form "object1 'from' object2" in which object1 can be
just about anything and object2 is this tree.  The preposition in the middle
may be "from" or "off."

Returns:  0/1

*/

int
tree_take(string str)

    {

    object tp = this_player();
    object to = this_object();
    string *player_input = explode(str, " ");
    string target;
    int i;  /* general purpose counter */
    int preposition = member_array("from", player_input);

    if (preposition == -1) preposition = member_array("off", player_input);

    if ((preposition > 0) && (player_input[sizeof(player_input)-1] == "tree"))
        /*  The player must take something from the tree.  It doesn't matter
        what, or whether it really exists or not - we'll process it as long as
        he takes it from the tree. */

        {

        if (preposition == 1) target = player_input[0];
        else target = implode(player_input[0..(preposition-1)], " ");

        for (i = 0; i < 5; i = i + 1)

            {

            if ((target == Ornaments[i]) || (target == Ornaments[i]+"s"))

                {

                if (target == Ornaments[i])  /*  Single ornament (no "s")  */

                    {

                    if (random(2))

                        {

                        write("You try to wrest the " + target +
                            " from the tree, but it is" +
                            " fastened much too securely!\n");

                        say(QCTNAME(tp) + " yanks and pulls furiously, but" +
                            " the " + target + " " + tp->query_pronoun() +
                            " has " + tp->query_possessive() +
                            " eye on simply won't let go!\n");

                        }

                    else

                        {

                        write("You pull and twist one of" +
                            " the " + target + "s on the " + query_short() +
                            " in a desperate attempt to remove it," +
                            " but the ornament refuses to budge.\n");

                        say(QCTNAME(tp) + " pulls and twists one of" +
                            " the " + target + "s on the " + query_short() +
                            " in a desperate attempt to remove it," +
                            " but the ornament refuses to budge.\n");

                        }

                    }

                else  /*  Multiple ornaments (name + "s")  */

                    {

                    if (random(2))

                        {

                        write("You wrap your hands around some " + target +
                            " and try to take the sparkling ornaments" +
                            " off the " + query_short() + "," +
                            " but your effort only swings the" +
                            " entire tree toward you!  When it" +
                            " whacks you in the face you release" +
                            " your grip, and the tree" +
                            " settles back into place.\n");

                        say(QCTNAME(tp) + " wraps " + tp->query_possessive() +
                            " hands around some " + target +
                            " and tries to take the sparkling ornaments" +
                            " off the " + query_short() + "," +
                            " but " + tp->query_possessive() +
                            " effort only swings the" +
                            " entire tree toward " + tp->query_objective() +
                            "!  When it whacks " + tp->query_objective() +
                            " in the face " + tp->query_pronoun() +
                            " releases " + tp->query_possessive() +
                            " grip, and the tree" +
                            " settles back into place.\n");

                        }

                    else

                        {

                        write("You mutter to yourself," +
                            " 'must have " + target +
                            ", must have " + target + ",' and try" +
                            " to pull some ornaments off" +
                            " the " + query_short() + ". The" +
                            " tree lurches and sways as you" +
                            " pull harder and harder," +
                            " but eventually you realize that" +
                            " you don't have the strength to remove" +
                            " the " + target + " and let go.\n");

                        say(QCTNAME(tp) + " mutters" +
                            " to " + tp->query_objective() +
                            "self, 'must have " + target +
                            ", must have " + target + ",' and tries" +
                            " to pull some ornaments off" +
                            " the " + query_short() + ". The" +
                            " tree lurches and sways" +
                            " as " + tp->query_pronoun() +
                            " pulls harder and harder," +
                            " but eventually " + tp->query_pronoun() +
                            " realizes that " + tp->query_pronoun() +
                            " doesn't have the strength to remove" +
                            " the " + target + " and lets go.\n");

                        }

                    }

                /*  Incur a 15-second delay after trying to take something from
                    the tree.  */

                Ready_to_dispense = 0;
                set_alarm(15.0, 0.0, tree_reload);

                /*  If the ornaments have been firmly attached (tree_attach),
                    there's a 50% chance that trying to take something from the
                    tree will have loosened some of them.  */

                if ((Drop_count > 10) && (random(2)))
                    set_alarm(2.0, 0.0, tree_loosen);

                return 1;

                }

            }

        /*  If the above loop didn't return, the the player is trying to take
            something other than one of the specific items in the Ornaments
            array.  */

        switch (target)

            {

            case "candle":

            if (random(2))

                {

                write("You try to take one of the candles from the" +
                    " tree but only manage to burn your" +
                    " fingers in the attempt!\n");

                say(QCTNAME(tp) + " tries to take one of the" +
                    " candles from the tree but only manages to" +
                    " burn " + tp->query_possessive() +
                    " fingers in the attempt!\n");

                }

            else

                {

                write("You try to take one of the candles from the" +
                    " tree, but it is attached securely and its" +
                    " surface is too slick for you to get a good" +
                    " grip. As your hand slips" +
                    " off, you accidentally extinguish the candle!\n");

                say(QCTNAME(tp) + " tries to take one of the" +
                    " candles from the tree, but it is attached" +
                    " securely and its surface is too slick" +
                    " for " + tp->query_objective() + " to get a" +
                    " good grip. As " + tp->query_possessive() +
                    " hand slips off, " + tp->query_pronoun() +
                    " accidentally extinguishes the candle!\n");

                set_alarm(10.0, 0.0, tree_relight);

                }

            break;

            case "cane":
            case "candy cane":

            if (random(2))

                {

                write("You reach into the tree to take one of" +
                    " the candy canes, but you can't seem to" +
                    " squeeze your hand into the narrow" +
                    " spaces where they're hanging.\n");

                say(QCTNAME(tp) + " reaches into the tree to take" +
                    " one of the candy canes but can't seem to" +
                    " squeeze " + tp->query_possessive() +
                    " hands into the narrow spaces" +
                    " where they're hanging.\n");

                }

            else

                {

                write("You contemplate the candy" +
                    " canes and are mesmerized. You" +
                    " abentmindedly grope about the tree trying to" +
                    " grab one, but they seem to magically elude you.\n");

                say(QCTNAME(tp) + " drools slightly" +
                    " and mutters, 'candy... sweet, sweet candy...'" +
                    " as " + tp->query_pronoun() + " gropes" +
                    " clumsily about the tree, vainly trying to grab" +
                    " one of the canes.\n");

                }

            break;

            case "all":

            write("What unmitigated greed!  You try to" +
                " take every ornament, candle, and candy cane" +
                " for yourself, but in your frenzy you fall" +
                " into the tree, burning yourself on the" +
                " candle flames and earning a few" +
                " scrapes and bruises.\n");

            say(QCTNAME(tp) + " plunges headlong into" +
                " the " + query_short() +
                ", then picks " + tp->query_objective() + "self up," +
                " looking scraped, bruised, and more" +
                " than a little embarrassed.\n");

            tp->command("blush");

            break;

            case "candles":

            write("You clumsily try to grab some candles from" +
                " the " + query_short() + ", but all you manage to" +
                " do is get some hot wax on your hands!\n");

            say(QCTNAME(tp) + " tries to grab some candles from" +
                " the " + query_short() +
                ", but all " + tp->query_pronoun() + " manages to" +
                " do is get some hot wax on " + tp->query_possessive() +
                " hands.\n");

            tp->command("grumble");

            break;

            case "canes":
            case "candy canes":

            write("You grab some candy canes and try with all" +
                " your might to take them from the tree," +
                " but they're stuck tight.\n");

            say(QCTNAME(tp) + " grabs some candy canes and tries" +
                " with all " + tp->query_possessive() + " might to take" +
                " them from the tree," +
                " but they're stuck tight.\n");

            tp->command("cry");

            break;

            case "ornament":
            case "decoration":

            write("You grasp one of the " + target + "s, a sparkling" +
                " little " + Ornaments[random(sizeof(Ornaments))] + "," +
                " and try to take it from the tree," +
                " but the delicate crystalline object crumbles to" +
                " dust in your hand and disappears.\n");

            say(QCTNAME(tp) + " grasps one of the " + target +
                "s on the " + query_short() + " and crushes it," +
                " reducing it to a tiny pile of" +
                " dust that quickly disappears.\n");

            break;

            case "ornaments":
            case "decorations":

            write("A bolt of green lightning flashes from the" +
                " " + query_short() + " and strikes you," +
                " sending you sprawling on the floor!  That's what" +
                " you get for just thinking about taking" +
                " the " + target + "!\n");

            say(QCTNAME(tp) + " is suddenly struck by a" +
                " bolt of green lightning!\n");

            tp->command("groan");

            break;

            default:

            write("Take what from the tree?\n");

            }

        /*  Incur a 15-second delay after trying to take something from the
            tree.  */

        Ready_to_dispense = 0;
        set_alarm(15.0, 0.0, tree_reload);

        /*  If the ornaments have been firmly attached (tree_attach), there's a
            50% chance that trying to take something from the tree will have
            loosened some of them.  */

        if ((Drop_count > 10) && (random(2)))
            set_alarm(2.0, 0.0, tree_loosen);

        return 1;

        }

    return 0;

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
    add_action(tree_shake, "shake");
    add_action(tree_take, "take");
    add_action(tree_take, "get");

    }
