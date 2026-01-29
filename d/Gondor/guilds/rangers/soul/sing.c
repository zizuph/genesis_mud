/*
 * /d/Gondor/guilds/rangers/soul/sing.c
 *
 * Included in the soul. Ability to sing Ranger songs.
 * Songs available by 'sing <songname>':
 * Campfire, Dawn, Elbereth, Eorl, Eressea, Galadriel, Gondor, Honour,
 * Ithilien, Parting, Ranger, Valimar, Wanderer, Winds
 *
 * Please add additional songs in alphabetical order for ease of finding.
 *
 * Original coder unknown.
 *
 * Modification log:
 *
 * 21 April 2001 Gwyneth: Cleanup and move
 */

#include <macros.h>

/* Function name: sing
 * Description  : 
 * Arguments    : string str - the argument
 * Returns      : 1 on success, 0 on failure
 */
public int
sing(string str)
{
    if (this_player()->query_ghost())
    {
        notify_fail("You struggle to sing the song, but find it impossible " +
            "in your ghostly state.\n");
        return 0;
    }

    str = lower_case(str);
    switch(str)
    {
    case "campfire":
        write("You sing a song about the warmth of the campfire.\n");
        say(QCTNAME(this_player()) + " sings a song about the warmth " +
            "of the campfire.\n");
        tell_room(environment(this_player()), "\n" +
            "    The flicker of the campfire\n" +
            "    The wind in the pines\n" +
            "    The moon in the heavens\n" +
            "    The stars that shine.\n" +
            "    A place where people gather\n" +
            "    Meeting friends of all kinds\n" +
            "    A place where all troubles\n" +
            "    Are always left behind!\n\n" +
            "    So, give me the light of the campfire!\n" +
            "    Warm and bright\n" +
            "    And give me some friends to sing with!\n" +
            "    I'll be here all night\n" +
            "    Love is for those who find it\n" +
            "    I found mine right here.\n" +
            "    Just you and me and the campfire...\n" +
            "    And the songs we like to hear!\n\n");

        if (present("campfire", environment(this_player())))
            say(QCTNAME(this_player()) + " smiles contentedly, warming " +
              this_player()->query_objective() + "self by the campfire.\n");
        else
            say(QCTNAME(this_player()) + " smiles happily, looking for " +
                "a campfire to warm by.\n");
        return 1;
    case "dawn":
        write("You sing a song of hope.\n");
        say(QCTNAME(this_player()) + " sings a song of hope.\n");
        tell_room(environment(this_player()), "\n" +
            "    The first rays of sun,\n" +
            "      like blades of bright steel,\n" +
            "      cut free of the clouds in the East;\n" +
            "    And are hailed by a robin,\n" +
            "      from a perch out of sight,\n" +
            "      where it sings like a bird released.\n\n" +
            "    At my feet a black patch,\n" +
            "      scorched by fire, drenched with blood,\n" +
            "      tells its story of darkness and crime.\n" +
            "    But a different tale,\n" +
            "      blades of grass pushing through,\n" +
            "      whisper to me: We will win, given time.\n\n" +
            "    With the dawn I return,\n" +
            "      to find solace and sleep,\n" +
            "      from the terrors I faced through the night;\n" +
            "    And though silent my home,\n" +
            "      though no hearth there is lit,\n" +
            "      still the flames of defiance are bright!\n\n" +
            "    We shall fight for our lands,\n" +
            "      though the clouds of the East,\n" +
            "      seek to smother the stars and the sun.\n" +
            "    True and bright shine our blades,\n" +
            "      bright and strong as the faith,\n" +
            "      of the people of Henneth Annun.\n\n");
        say(QCTNAME(this_player()) + " finishes " + 
            this_player()->query_possessive() + " song, smiling " +
            "confidently.\n");
        return 1;
    case "elbereth":
        write("You sing a song to praise Elbereth, the Goddess of the " +
            "Stars.\n");
        say(QCTNAME(this_player()) + " sings a song to praise Elbereth, " +
            "the Goddess of Stars.\n");
        tell_room(environment(this_player()), "\n" +
            "    A! Elbereth, Gilthoniel,\n" +
            "    silivren penna miriel\n" +
            "    o menel aglar elenath!\n" +
            "    Na chaered palan-diriel\n" +
            "    o galadhremmin ennorath,\n" +
            "    Fanuilos, le linnathon\n" +
            "    nef aear, si nef aearon!\n\n");
        say("\n\n" + QCTNAME(this_player()) + " sighs, and silently " +
            "stares at the stars for a while.\n");
        return 1;
    case "eorl":
        write("You sing a song recalling how tall and fair was Eorl " +
            "the Young.\n");
        say(QCTNAME(this_player()) + " sings a song recalling how tall " +
            "and fair was Eorl the Young.\n");
        tell_room(environment(this_player()), "\n" +
            "    Where now the horse and the rider?\n" +
            "      Where is the horn that was blowing?\n" +
            "    Where is the helm and the hauberk,\n" +
            "      and the bright hair flowing?\n" +
            "    Where is the hand on the harpstring,\n" +
            "      and the red fire glowing?\n" +
            "    Where is the spring and the harvest\n" +
            "      and the tall corn growing?\n" +
            "    They have passed like rain on the mountain,\n" +
            "      like a wind in the meadow;\n" +
            "    The days have gone down in the West\n" +
            "      behind the hills into shadow.\n\n" +
            "    Who shall gather the smoke of the dead wood burning,\n" +
            "    Or behold the flowing years from the Sea returning?\n\n");
        return 1;
    case "eressea":
        write("You sing a song to the Sea and to Eressea, the Elven-home " +
            "in the West.\n");
        say(QCTNAME(this_player()) + " sings a song to the Sea and to " +
            "Eressea, the Elven-home in the West.\n");
        tell_room(environment(this_player()), "\n" +
            "    To the Sea, to the Sea! The white gulls are crying,\n" +
            "    the wind is blowing, and the white foam is flying.\n" +
            "    West, west away, the round sun is falling.\n" +
            "    Grey ship, grey ship, do you hear them calling,\n" +
            "    The voices of my people that have gone before me?\n" +
            "    I will leave, I will leave the woods that bore me;\n" +
            "    For our days are ending and our years are failing.\n" +
            "    I will pass the wide waters lonely sailing.\n" +
            "    Long are the waves on the Last Shore falling,\n" +
            "    Sweet are the voices in the Lost Isle calling,\n" +
            "    In Eressea, in Elvenhome that no man can discover,\n" +
            "    Where the leaves fall not: land of my people for ever!\n\n");
        say(QCTNAME(this_player()) + " sighs and quietly stares west " +
            "in the direction of the Sea.\n");
        return 1;
    case "galadriel":
        write("You sing a song of fair Lorien and the Lady Galadriel.\n");
        say(QCTNAME(this_player()) + " sings a song of fair Lorien and " +
            "the Lady Galadriel.\n");
        tell_room(environment(this_player()), "\n" +
            "    In Dwimordene, in Lorien\n" +
            "    Seldom have walked the feet of Men,\n" +
            "    Few mortal eyes have seen the light\n" +
            "    That lies there ever, long and bright.\n" +
            "    Galadriel! Galadriel! \n" +
            "    Clear is the water of your well;\n" +
            "    White is the star in your white hand;\n" +
            "    Unmarred, unstained is leaf and land\n" +
            "    In Dwimordene, in Lorien\n" +
            "    More fair than thoughts of Mortal Men.\n\n");
        say("\n" + QCTNAME(this_player()) + " sighs, and quietly stares " +
            "in the direction of Lothlorien.\n");
        return 1;
    case "gondor":
        write("You sing a song to praise Gondor, your fair homeland.\n");
        say(QCTNAME(this_player()) + " sings a sad song to praise Gondor, " +
            "the fair Kingdom.\n");
        tell_room(environment(this_player()), "\n" +
            "    Gondor! Gondor, between the Mountains and the Sea!\n" +
            "    West Wind blew there; the light upon the Silver Tree\n" +
            "    Fell like bright rain in gardens of the Kings of old.\n" +
            "    O proud walls! White towers! O winged crown and throne of gold!\n" +
            "    O Gondor, Gondor! Shall Men behold the Silver Tree,\n" +
            "    or West Wind blow again between the Mountains and the Sea?\n\n");
        say(QCTNAME(this_player()) + " sighs, and quietly stares in the " +
            "direction of Gondor.\n");
        return 1;
    case "honour":
        write("You sing a song about honour and duty.\n");
        say(QCTNAME(this_player()) + " sings a song about honour and duty.\n");
        tell_room(environment(this_player()), "\n" +
            "    On my honour I will try\n" +
            "    There's a duty to be done, and I say 'Aye'\n" +
            "    There's a reason here for reason above\n" +
            "    My honour is to try, and my duty is to love!\n\n" +
            "    People don't need to know my name\n" +
            "    If I've done any harm then I'm to blame\n" +
            "    If I've helped somebody, then I've helped me\n" +
            "    And I've opened up my eyes to see.\n\n" +
            "    So come with me where the fires burn bright\n" +
            "    We can see better by candlelight\n" +
            "    And we'll learn more here by the campfire's glow\n" +
            "    Than we'd ever learn in a year or so!\n\n" +
            "    We made a promise to always keep\n" +
            "    And a prayer softly falls before we sleep\n" +
            "    We'll be Rangers together, and when we're done,\n" +
            "    We'll still be trying, and singing this song.\n\n");
        say(QCTNAME(this_player()) + " finishes " + 
            this_player()->query_possessive() + " song.\n");
        return 1;
    case "ithilien":
        write("You sing a song to praise the fair lands of Ithilien.\n");
        say(QCTNAME(this_player()) + " sings a song to praise the fair " +
            "lands of Ithilien.\n");
        tell_room(environment(this_player()), "\n" +
            "    Ithilien, my Love, when will I ever see thee free,\n" +
            "     and green and beautiful again, as thou alone canst be?\n" +
            "    When will thy bleedings would be healed,\n" +
            "     and Darkness deep to Moonlight yield,\n" +
            "     and crawl before thy mighty shield surrendering to thee?\n\n" +        
            "    Ithilien, my Love, cast off the shadow of the East,\n" +
            "     and tear its banners black and red, and slay its dreadful beasts!\n" +
            "    And pride thee on thy valiant men,\n" +
            "     who'll fight for fair Ithilien,\n" +
            "     until the Moonlight flows again upon a land at peace!\n\n");
        say(QCTNAME(this_player()) + " finishes " + 
            this_player()->query_possessive() + " song with a soft sigh.\n");
        return 1;
    case "parting":
        write("You sing a few lines of an ancient song, attributed to " +
            "Beren Erchamion.\n");
        say(QCTNAME(this_player()) + " sings the Song of Parting.\n");
        tell_room(environment(this_player()), "\n" +
            "    Farewell sweet earth and northern sky,\n" +
            "    for ever blest, since here did lie\n" +
            "    and here with lissom limbs did run\n" +
            "    beneath the Moon, beneath the Sun,\n" +
            "    Luthien Tinuviel\n" +
            "    more fair than mortal tongue can tell.\n" +
            "    Though all to ruin fell the world\n" +
            "    and were dissolved and backward hurled\n" +
            "    unmade into the old abyss,\n" +
            "    yet were it's making good, for this - \n" +
            "    the dusk, the dawn, the earth, the sea - \n" +
            "    that Luthien for a time should be.\n\n");
        say(QCTNAME(this_player()) + " sighs, remembering the Heroes of " +
            "the First Age.\n");
        return 1;
    case "ranger":
        write("You sing a song about being a Ranger.\n");
        say(QCTNAME(this_player()) + " sings a song about being a Ranger.\n");
        tell_room(environment(this_player()), "\n" +
            "    Elven, Human, Hobbit, Dwarf or Gnome,\n" +
            "     All the Westland do we roam.\n" +
            "    Protecting Gondor, Rohan, and Shire\n" +
            "     From the wrath of Sauron's fire\n" +
            "    Scholars of many an ancient lore,\n" +
            "     We protect, patrol, defend and explore.\n\n" +
            "    With allies of good, like Calians and Knights\n" +
            "     We are skilled in battle, but do not pick fights.\n" +
            "    The Angmarim and Mages all from the East,\n" +
            "     march attacks on the Westlands, and allow little peace\n" +
            "    Our honour and bravery, our courage and hope,\n" +
            "     alone will sustain us in the fight with our foe.\n\n" +
            "    Gathering 'round campfires telling all kinds of tales\n" +
            "     We enjoy a roast elk, and a tall mug of ale.\n" +
            "    We live in the forests, knowing well stealth and speed\n" +
            "     Our purpose is defence, of all those in need\n" +
            "    Yes we are Rangers, we are the Westlands' friends\n" +
            "     Our watch of our borders will never, ever end.\n\n");
        say(QCTNAME(this_player()) + " ends " + 
            this_player()->query_possessive() + " song with a proud smile.\n");
        return 1;
    case "valimar":
        write("You longingly sing a song of Valimar, the land of the " +
            "Valar lost in the West.\n");
        say(QCTNAME(this_player()) + " longingly sings a song about " +
            "Valimar, the land lost in the West.\n");
        tell_room(environment(this_player()), "\n" +
            "    Ai! laurie lantar lassi surinen,\n" +
            "    Yeni unotime ve ramar aldaron!\n" +
            "    Yeni ve linte yuldar avanier\n" +
            "    mi oromardi lisse-miruvoreva\n" +
            "    Andune pella, Vardo tellumar\n" +
            "    nu luini yassen tintilar i eleni\n" +
            "    omaryo airetari-lirinen.\n\n" +
            "    Si man i yulma nin enquantuva?\n\n" +
            "    An si Tintalle Varda Oiolosseo\n" +
            "    ve fanyar maryat Elentari ortane\n" +
            "    ar ilye tier undulave lumbule;\n" +
            "    ar sindanoriello caita mornie\n" +
            "    i falmalinnar imbe met, ar hisie\n" +
            "    untupa Calaciryo miri oiale.\n" +
            "    Si vanwa na, Romello vanwa, Valimar!\n\n" +
            "    Namarie! Nai hiruvalye Valimar.\n" +
            "    Nai elye hiruva. Namarie!\n\n");
            say("\n" + QCTNAME(this_player()) + " sighs, and longingly " +
                "stares to the West.\n");
            return 1;
    case "wanderer":
        write("You sing a song about the end of the journey and the joy " +
            "of coming home.\n");
        say(QCTNAME(this_player()) + " sings a song about the end of the " +
            "journey and the joy of coming home.\n");
        tell_room(environment(this_player()), "\n" +
            "    Roads go ever ever on,\n" +
            "      Over rock and under tree,\n" +
            "    By caves where never sun has shone,\n" +
            "      By streams that never find the sea:\n" +
            "    Over snow by winter sown,\n" +
            "      And through the merry flowers of June,\n" +
            "    Over grass and over stone,\n" +
            "      And under mountains in the moon.\n\n" +
            "    Roads go ever ever on,\n" +
            "      Under cloud and under star, \n" +
            "    Yet feet that wandering have gone,\n" +
            "      Turn at last to home afar.\n" +
            "    Eyes that fire and sword have seen\n" +
            "      And horror in the halls of stone\n" +
            "    Look at last on meadows green\n" +
            "      And trees and hills they long have known.\n\n");
        say(QCTNAME(this_player()) + " sighs, and wishes that the end of " +
            "the journey had already come.\n");
        return 1;
    case "winds":
        write("You sing a song that is a call to arms.\n");
        say(QCTNAME(this_player()) + " sings a song that is like a " +
            "call to arms.\n");        
        tell_room(environment(this_player()), "\n" +
            "    Do you hear the east winds blow?\n" +
            "     Bringing the storm upon the lands,\n" +
            "    Echoing the coming of a host\n" +
            "     Which the Dark Lord now commands!\n\n" +
            "    Will you join our cause?\n" +
            "     Who will be strong and stand with me?\n" +
            "    Somewhere beyond the Morgul Storm,\n" +
            "     Is there a world you long to see?\n\n" +
            "    Then join in the fight that will give you the right\n" +
            "      to be free!\n\n" +
            "    Do you hear the west winds blow?\n" +
            "     Bringing the hope of all the lands!\n" +
            "    It is the sound of people who\n" +
            "     Will not be slaves in Sauron's hands!\n\n" +
            "    Will you give all you can give?\n" +
            "     So that our banners may yet stand?\n" +
            "    Some will fall and some will live,\n" +
            "     Will you come with me hand in hand?\n\n" +
            "    The blood of the martyrs will water the meadows\n" +
            "      throughout the Land!\n\n" +
            "    Do you hear the winds of change?\n" +
            "     Bringing our cause to every heart!\n" +
            "    With our Faith there will be Hope\n" +
            "     When we all do our part!\n\n" +
            "    Will you heed the call to arms?\n" +
            "     Carry the flame that never dies?\n" +
            "    Even the darkest night will end\n" +
            "     And the sun will rise!\n\n" +
            "    Together, we shall forever remove the darkness\n" +
            "      from the Skies!\n\n");

        say(QCTNAME(this_player()) + " finishes " + 
            this_player()->query_possessive() + " song with a challenging " +
            "stare at everyone in " + this_player()->query_possessive() + 
            " audience.\n");
        return 1;
    default:
        notify_fail("You don't seem to remember the lyrics to that song.\n");
        return 0;
    }
}

