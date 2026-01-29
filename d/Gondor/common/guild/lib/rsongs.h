/*
 *  Code for the Rangers songs.
 *  Songs available by 'sing <songname>':
 *  Gondor, Elbereth, Wanderer, Parting, Eressea
 */

#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/sys/formulas.h"

#define TR(x) tell_room(environment(TP),x)

int
do_song(string songname)
{
    if (TP->query_ghost())
    {
	notify_fail("You are a ghost and cannot sing this song.\n");
	return 0;
    }

    songname = lower_case(songname);

    if(songname == "valimar")
    {
	write("You longingly sing a song of Valimar, the land of the Valar lost in the West.\n\n");
	say(QCTNAME(TP)+" longingly sings a song about Valimar, the land lost in the West.\n\n");
	TR("    Ai! laurie lantar lassi surinen,\n");
	TR("    Yeni unotime ve ramar aldaron!\n");
	TR("    Yeni ve linte yuldar avanier\n");
	TR("    mi oromardi lisse-miruvoreva\n");
	TR("    Andune pella, Vardo tellumar\n");
	TR("    nu luini yassen tintilar i eleni\n");
	TR("    omaryo airetari-lirinen.\n\n");
	TR("    Si man i yulma nin enquantuva?\n\n");
	TR("    An si Tintalle Varda Oiolosseo\n");
	TR("    ve fanyar maryat Elentari ortane\n");
	TR("    ar ilye tier undulave lumbule;\n");
	TR("    ar sindanoriello caita mornie\n");
	TR("    i falmalinnar imbe met, ar hisie\n");
	TR("    untupa Calaciryo miri oiale.\n");
	TR("    Si vanwa na, Romello vanwa, Valimar!\n\n");
	TR("    Namarie! Nai hiruvalye Valimar.\n");
	TR("    Nai elye hiruva. Namarie!\n\n");
	say("\n"+QCTNAME(TP)+" sighs, and longingly stares to the West.\n");
	return 1;
    }
    if(songname=="galadriel" || songname=="Galadriel")
    {
	write("You sing a song of fair Lorien and the Lady Galadriel.\n\n");
	say(QCTNAME(TP)+" sings a song of fair Lorien and the Lady Galadriel.\n\n");
	TR("    In Dwimordene, in Lorien\n");
	TR("    Seldom have walked the feet of Men,\n");
	TR("    Few mortal eyes have seen the light\n");
	TR("    That lies there ever, long and bright.\n");
	TR("    Galadriel! Galadriel! \n");
	TR("    Clear is the water of your well;\n");
	TR("    White is the star in your white hand;\n");
	TR("    Unmarred, unstained is leaf and land\n");
	TR("    In Dwimordene, in Lorien\n");
	TR("    More fair than thoughts of Mortal Men.\n\n");
	say("\n"+QCTNAME(TP)+" sighs, and quietly stares in the direction of Lothlorien.\n");
	return 1;
    }
    if(songname=="eorl" || songname=="Eorl")
    {
	write("You sing a song recalling how tall and fair was Eorl the Young.\n\n");
	say(QCTNAME(TP)+" sings a song recalling how tall and fair was Eorl the Young.\n\n");
	TR("    Where now the horse and the rider?\n");
	TR("      Where is the horn that was blowing?\n");
	TR("    Where is the helm and the hauberk,\n");
	TR("      and the bright hair flowing?\n");
	TR("    Where is the hand on the harpstring,\n");
	TR("      and the red fire glowing?\n");
	TR("    Where is the spring and the harvest\n");
	TR("      and the tall corn growing?\n");
	TR("    They have passed like rain on the mountain,\n");
	TR("      like a wind in the meadow;\n");
	TR("    The days have gone down in the West\n");
	TR("      behind the hills into shadow.\n\n");
	TR("    Who shall gather the smoke of the dead wood burning,\n");
	TR("    Or behold the flowing years from the Sea returning?\n\n");
	return 1;
    }
    if(songname=="gondor" || songname=="Gondor")
    {
	write("You sing a song to praise Gondor, your fair homeland.\n\n");
	say(QCTNAME(TP)+" sings a sad song to praise Gondor, the fair Kingdom.\n\n");
	TR("    Gondor! Gondor, between the Mountains and the Sea!\n");
	TR("    West Wind blew there; the light upon the Silver Tree\n");
	TR("    Fell like bright rain in gardens of the Kings of old.\n");
	TR("    O proud walls! White towers! O winged crown and throne of gold!\n");
	TR("    O Gondor, Gondor! Shall Men behold the Silver Tree,\n");
	TR("    or West Wind blow again between the Mountains and the Sea?\n\n");
	say(QCTNAME(TP)+" sighs, and quietly stares in the direction of Gondor.\n");
	return 1;
    }
    if(songname=="elbereth" || songname=="Elbereth")
    {
	write("You sing a song to praise Elbereth, the Goddess of the Stars.\n");
	say(QCTNAME(TP)+" sings a song to praise Elbereth, the Goddess of Stars.\n");
	TR("\n    A! Elbereth, Gilthoniel,\n");
	TR("    silivren penna miriel\n");
	TR("    o menel aglar elenath!\n");
	TR("    Na chaered palan-diriel\n");
	TR("    o galadhremmin ennorath,\n");
	TR("    Fanuilos, le linnathon\n");
	TR("    nef aear, si nef aearon!\n\n");
	say("\n\n"+QCTNAME(TP)+" sighs, and silently stares at the stars for a while.\n");
	return 1;
    } 
    if(songname=="wanderer" || songname=="Wanderer")
    {
	write("You sing a song about the end of the journey and the joy of coming home.\n");
	say(QCTNAME(TP)+" sings a song about the end of the journey and the joy of coming home.\n");
	TR("\n    Roads go ever ever on,\n");
	TR("      Over rock and under tree,\n");
	TR("    By caves where never sun has shone,\n");
	TR("      By streams that never find the sea:\n");
	TR("    Over snow by winter sown,\n");
	TR("      And through the merry flowers of June,\n");
	TR("    Over grass and over stone,\n");
	TR("      And under mountains in the moon.\n\n");
	TR("    Roads go ever ever on,\n");
	TR("      Under cloud and under star, \n");
	TR("    Yet feet that wandering have gone,\n");
	TR("      Turn at last to home afar.\n");
	TR("    Eyes that fire and sword have seen\n");
	TR("      And horror in the halls of stone\n");
	TR("    Look at last on meadows green\n");
	TR("      And trees and hills they long have known.\n\n");
	say(QCTNAME(TP)+" sighs, and wishes that the end of the journey had already come.\n");
	return 1;
    }
    if(songname=="parting" || songname=="Parting")
    {
	write("You sing a few lines of an ancient song, attributed to Beren Erchamion.\n");
	say(QCTNAME(TP)+" sings the Song of Parting.\n");
	TR("\n    Farewell sweet earth and northern sky,\n");
	TR("    for ever blest, since here did lie\n");
	TR("    and here with lissom limbs did run\n");
	TR("    beneath the Moon, beneath the Sun,\n");
	TR("    Luthien Tinuviel\n");
	TR("    more fair than mortal tongue can tell.\n");
	TR("    Though all to ruin fell the world\n");
	TR("    and were dissolved and backward hurled\n");
	TR("    unmade into the old abyss,\n");
	TR("    yet were it's making good, for this - \n");
	TR("    the dusk, the dawn, the earth, the sea - \n");
	TR("    that Luthien for a time should be.\n\n");
	say(QCTNAME(TP)+" sighs, remembering the Heroes of the First Age.\n");
	return 1;
    }
    if(songname=="eressea" || songname=="Eressea")
    {
	write("You sing a song to the Sea and to Eressea, the Elven-home in the West.\n");
	say(QCTNAME(TP)+" sings a song to the Sea and to Eressea, the Elven-home in the West.\n");
	TR("\n    To the Sea, to the Sea! The white gulls are crying,\n");
	TR("    the wind is blowing, and the white foam is flying.\n");
	TR("    West, west away, the round sun is falling.\n");
	TR("    Grey ship, grey ship, do you hear them calling,\n");
	TR("    The voices of my people that have gone before me?\n");
	TR("    I will leave, I will leave the woods that bore me;\n");
	TR("    For our days are ending and our years are failing.\n");
	TR("    I will pass the wide waters lonely sailing.\n");
	TR("    Long are the waves on the Last Shore falling,\n");
	TR("    Sweet are the voices in the Lost Isle calling,\n");
	TR("    In Eressea, in Elvenhome that no man can discover,\n");
	TR("    Where the leaves fall not: land of my people for ever!\n\n");
	say(QCTNAME(TP)+" sighs and quietly stares west in the direction of the Sea.\n");
	return 1;
    }
    if (songname == "campfire" || songname == "Campfire")
    {
	write("You sing a song about the warmth of the campfire.\n\n");
	say(QCTNAME(TP) + " sings a song about the warmth of the campfire.\n\n", TP);
	TR("    The flicker of the campfire\n");
	TR("    The wind in the pines\n");
	TR("    The moon in the heavens\n");
	TR("    The stars that shine.\n");
	TR("    A place where people gather\n");
	TR("    Meeting friends of all kinds\n");
	TR("    A place where all troubles\n");
	TR("    Are always left behind!\n\n");
	TR("    So, give me the light of the campfire!\n");
	TR("    Warm and bright\n");
	TR("    And give me some friends to sing with!\n");
	TR("    I'll be here all night\n");
	TR("    Love is for those who find it\n");
	TR("    I found mine right here.\n");
	TR("    Just you and me and the campfire...\n");
	TR("    And the songs we like to hear!\n\n");
	if (present("campfire",environment(TP)))
	    say(QCTNAME(TP)+" smiles contentedly, warming " +
	      TP->query_objective()+"self by the campfire.\n", TP);
	else
	    say(QCTNAME(TP)+" smiles happily, looking for a campfire " +
	      "to warm by.\n", TP);
	return 1;
    }
    if (songname == "honour" || songname == "duty")
    {
	write("You sing a song about honour and duty.\n\n");
	say(QCTNAME(TP) + " sings a song about honour and duty.\n\n", TP);
	TR("    On my honour I will try\n");
	TR("    There's a duty to be done, and I say 'Aye'\n");
	TR("    There's a reason here for reason above\n");
	TR("    My honour is to try, and my duty is to love!\n\n");
	TR("    People don't need to know my name\n");
	TR("    If I've done any harm then I'm to blame\n");
	TR("    If I've helped somebody, then I've helped me\n");
	TR("    And I've opened up my eyes to see.\n\n");
	TR("    So come with me where the fires burn bright\n");
	TR("    We can see better by candlelight\n");
	TR("    And we'll learn more here by the campfire's glow\n");
	TR("    Than we'd ever learn in a year or so!\n\n");
	TR("    We made a promise to always keep\n");
	TR("    And a prayer softly falls before we sleep\n");
	TR("    We'll be Rangers together, and when we're done,\n");
	TR("    We'll still be trying, and singing this song.\n\n");
	say(QCTNAME(TP) + " finishes "+TP->query_possessive()+" song.\n",TP);
	return 1;
    }
    if (songname == "winds" || songname == "wind"
      || songname == "hear the wind")
    {
	write("You sing a song that is a call to arms.\n\n");
	say(QCTNAME(TP) + " sings a song that is like a call to arms.\n\n", TP);
	TR("    Do you hear the east winds blow?\n");
	TR("     Bringing the storm upon the lands,\n");
	TR("    Echoing the coming of a host\n");
	TR("     Which the Dark Lord now commands!\n\n");
	TR("    Will you join our cause?\n");
	TR("     Who will be strong and stand with me?\n");
	TR("    Somewhere beyond the Morgul Storm,\n");
	TR("     Is there a world you long to see?\n\n");
	TR("    Then join in the fight that will give you the right\n");
	TR("      to be free!\n\n");
	TR("    Do you hear the west winds blow?\n");
	TR("     Bringing the hope of all the lands!\n");
	TR("    It is the sound of people who\n");
	TR("     Will not be slaves in Sauron's hands!\n\n");
	TR("    Will you give all you can give?\n");
	TR("     So that our banners may yet stand?\n");
	TR("    Some will fall and some will live,\n");
	TR("     Will you come with me hand in hand?\n\n");
	TR("    The blood of the martyrs will water the meadows\n");
	TR("      throughout the Land!\n\n");
	TR("    Do you hear the winds of change?\n");
	TR("     Bringing our cause to every heart!\n");
	TR("    With our Faith there will be Hope\n");
	TR("     When we all do our part!\n\n");
	TR("    Will you heed the call to arms?\n");
	TR("     Carry the flame that never dies?\n");
	TR("    Even the darkest night will end\n");
	TR("     And the sun will rise!\n\n");
	TR("    Together, we shall forever remove the darkness\n");
	TR("      from the Skies!\n\n");
	say(QCTNAME(TP) + " finishes " + TP->query_possessive() + " song with a "
	  + "challenging stare at everyone in " + TP->query_possessive() 
	  + " audience.\n", TP);
	return 1;
    }
    if (songname == "ithilien" || songname == "Ithilien")
    {
	write("You sing a song to praise the fair lands of Ithilien.\n");
	say(QCTNAME(TP) + " sings a song to praise the fair lands of Ithilien.\n", TP);
	TR("    Ithilien, my Love, when will I ever see thee free,\n");
	TR("     and green and beautiful again, as thou alone canst be?\n");
	TR("    When will thy bleedings would be healed,\n");
	TR("     and Darkness deep to Moonlight yield,\n");
	TR("     and crawl before thy mighty shield surrendering to thee?\n\n");
	TR("    Ithilien, my Love, cast off the shadow of the East,\n");
	TR("     and tear its banners black and red, and slay its dreadful beasts!\n");
	TR("    And pride thee on thy valiant men,\n");
	TR("     who'll fight for fair Ithilien,\n");
	TR("     until the Moonlight flows again upon a land at peace!\n\n");
	say(QCTNAME(TP) + " finishes " + TP->query_possessive() 
	  + " song with a soft sigh.\n", TP);
	return 1;
    }
    if (songname == "ranger" || songname == "Ranger")
    {
	write("You sing a song about being a Ranger.\n");
	say(QCTNAME(TP) + " sings a song about being a Ranger.\n", TP);
	TR("    Elven, Human, Hobbit, Dwarf or Gnome,\n");
	TR("     All the Westland do we roam.\n");
	TR("    Protecting Gondor, Rohan, and Shire\n");
	TR("     From the wrath of Sauron's fire\n");
	TR("    Scholars of many an ancient lore,\n");
	TR("     We protect, patrol, defend and explore.\n\n");
	TR("    With allies of good, like Calians and Knights\n");
	TR("     We are skilled in battle, but do not pick fights.\n");
	TR("    The Angmarim and Mages all from the East,\n");
	TR("     march attacks on the Westlands, and allow little peace\n");
	TR("    Our honour and bravery, our courage and hope,\n");
	TR("     alone will sustain us in the fight with our foe.\n\n");
	TR("    Gathering 'round campfires telling all kinds of tales\n");
	TR("     We enjoy a roast elk, and a tall mug of ale.\n");
	TR("    We live in the forests, knowing well stealth and speed\n");
	TR("     Our purpose is defence, of all those in need\n");
	TR("    Yes we are Rangers, we are the Westlands' friends\n");
	TR("     Our watch of our borders will never, ever end.\n\n");
	say(QCTNAME(TP) + " ends " + TP->query_possessive() + " song with a proud smile.\n");
	return 1;
    }
    if (songname == "dawn" || songname == "Dawn")
    {
	write("You sing a song of hope.\n");
	say(QCTNAME(TP) + " sings a song of hope.\n", TP);
	TR("    The first rays of sun,\n");
	TR("      like blades of bright steel,\n");
	TR("      cut free of the clouds in the East;\n");
	TR("    And are hailed by a robin,\n");
	TR("      from a perch out of sight,\n");
	TR("      where it sings like a bird released.\n\n");
	TR("    At my feet a black patch,\n");
	TR("      scorched by fire, drenched with blood,\n");
	TR("      tells its story of darkness and crime.\n");
	TR("    But a different tale,\n");
	TR("      blades of grass pushing through,\n");
        TR("      whisper to me: We will win, given time.\n\n");
	TR("    With the dawn I return,\n");
	TR("      to find solace and sleep,\n");
	TR("      from the terrors I faced through the night;\n");
	TR("    And though silent my home,\n");
	TR("      though no hearth there is lit,\n");
	TR("      still the flames of defiance are bright!\n\n");
	TR("    We shall fight for our lands,\n");
	TR("      though the clouds of the East,\n");
	TR("      seek to smother the stars and the sun.\n");
	TR("    True and bright shine our blades,\n");
	TR("      bright and strong as the faith,\n");
	TR("      of the people of Henneth Annun.\n\n");
	say(QCTNAME(TP) + " finishes " + TP->query_possessive() + " song, "
	  + "smiling confidently.\n");
	return 1;
    }
    notify_fail("You don't remember the lyrics to that song.\n");
    return 0;
}



