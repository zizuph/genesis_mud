/*
 * /d/Ansalon/guild/kender_occ/songlist.c
 *
 * Copyright (c) 2001 by Alyssa Hardy
 *
 * Copyright notice, please read.
 *
 * You are welcome to read this file for information & education purposes.
 * However, you are expressly forbidden to copy this code for use in any
 * other mud. This code is part of Genesis and we want Genesis to remain
 * unique. You must invent your own world on your own mud.
 *
 * Handles song singing
 *
 * Originally put together by Gwyneth, 1999
 * Modification log:
 * Completely recoded by Gwyneth January 2001
 */
mapping gSongList = ([ 
"thinking" : ({"        If thought is the mother of all good action,\n" +
    "        then what is the child of plain distraction?\n" +
    "        Think! Pay attention! Let your mind change!\n" +
    "        Make everyday things complicated and strange!\n" + 
    "        There are fish to be fried, but first to be caught\n" +
    "        So spread wide the nets and get tangled in thought!\n\n"}),
"mourning" : ({"        Always before, the spring returned.\n" + 
    "        The bright world in its cycle spun\n" +
    "        In air and flowers, grass and fern,\n" +
    "        Assured and cradled by the sun.\n\n",
        "        Always before, you could explain\n" +
        "        The turning darkness of the earth,\n" +
        "        And how that dark embraced the rain,\n" +
        "        And gave the ferns and flowers birth.\n\n",
            "        Already I forget those things,\n" +
            "        And how a vein of gold survives\n" +
            "        The mining of a thousand springs,\n" +
            "        The seasons of a thousand lives.\n\n",
                "        Now winter is my memory,\n" +
                "        Now autumn, now the summer light-\n" +
                "        So every spring from now will be\n" +
                "        Another season into night.\n\n"}),
"trail" : ({"        Your one true love's a sailing ship\n" +
    "          That anchors at our pier.\n" +
    "        We lift her sails, we man her decks,\n" +
    "          We scrub the portholes clear;\n\n",
        "        And yes, our lighthouse shines for her,\n" +
        "          And yes, our shores are warm;\n" +
        "           We steer her into harbor-\n" +
        "             Any port in a storm.\n\n",
            "        The sailors stand upon the docks,\n" +
            "            The sailors stand in line,\n" +
            "          As thirsty as a dwarf for gold\n" +
            "           Or centaurs for cheap wine.\n\n",
                "          For all the sailors love her,\n" +
                "        And flock to where she's moored,\n" +
                "         Each man hoping that he might\n" +
                "          Go down, all hands on board.\n\n" }),
"kdrinking" : ({"        Swing 'er around\n" +
    "        And up and down\n" +
    "        Hey, swing 'er around til morning\n\n",
        "        Hear ye here, the sad tales are sung\n" +
        "        Now there's nothing left but laughter,\n" +
        "        For we've set the sail, the chores are done,\n" +
        "        And the moons are following after,\n" +
        "        Aye, the moons are following after.\n\n",
            "        'Tis a world of war, 'tis a world of strife,\n" +
            "        'Tis a world both tough and tender\n" +
            "        'Tis a world where heroes come to life-\n" +
            "        Say, an elf-maid and a kender.\n" +
            "        Aye, an elf-maid and a kender.\n\n" }),
"drinking" : ({"        Sing as the spirits move you,\n" +
    "        Sing to your doubling eye,\n" +
    "        Plain Jane becomes Loveable Lindas\n" +
    "        When six moons shine in the sky.\n\n",
        "        Sing to a sailor's courage,\n" +
        "        Sing while the elbows bend,\n" +
        "        A ruby port your harbor,\n" +
        "        Hoise three sheets to the wind.\n\n",
            "        Sing while the heart is cordial,\n" +
            "        Sing to the absinthe of cares,\n" +
            "        Sing to the one for the weaving road,\n" +
            "        And the dog, and each of his hairs.\n\n",
                "        All the waitresses love you,\n" +
                "        Every dog is your friend,\n" +
                "        Whatever you say is just what you mean,\n" +
                "        So hoist three sheets to the wind.\n\n" }),
"death" : ({"        Return this man to Huma's breast:\n" +
"        Let him be lost in sunlight,\n" +
"        In the chorus of air where breath is translated;\n" +
"        At the sky's border to receive him.\n\n",
 "        Beyond the wild, impartial skies\n" +
 "        Have you set your lodgings,\n" +
 "        In cantonments of stars, where the sword aspires\n" +
 "        In an arc of yearning, where we join in singing.\n\n",
  "        Grant him to a warrior's rest.\n" +
  "        Above our singing, above song itself,\n" +
  "        May the ages of peace converge in a day,\n" +
  "        May he dwell in the heart of Paladine.\n\n",
   "        And set the last spark of his eyes\n" +
   "        In a fixed and holy place\n" +
   "        Above words and the borrowed land too loved\n" +
   "        As we recount the ages.\n\n",
    "        Free from the smothering clouds of war\n" +
    "        As he once rose in infancy,\n" +
    "        The long world possible and bright before him,\n" +
    "        Lord Huma, deliver him.\n\n",
     "        Upon the torches of the stars\n" +
     "        Was mapped the immaculate glory of childhood;\n" +
     "        From that wronged and nestling country,\n" +
     "        Lord Huma, deliver him.\n\n",
      "        Let the last surge of his breath\n" +
      "        Perpetuate the wine, the attar of flowers;\n" +
      "        From the vanguard of love, the last to surrender,\n" +
      "        Lord Huma, deliver him.\n\n",
       "        Take refuge in the cradling air\n" +
       "        From the heart of the sword descending,\n" +
       "        From the weight of battle on battle;\n" +
       "        Lord Huma, deliver him.\n\n",
        "        Above the dreams of ravens where\n" +
        "        His dreams first tried a rest beyond changing,\n" +
        "        From the yearning for war and the war's ending,\n" +
        "        Lord Huma, deliver him.\n\n",
         "        Only the hawk remembers death\n" +
         "        In a late country; from the dusk,\n" +
         "        From the fade of the senses, we are thankful that you,\n" +
         "        Lord Huma, deliver him.\n\n",
          "        Then let his shade to Huma rise\n" +
          "        Out of the body of death, of the husk unravelling,\n" +
          "        We are thankful that you,\n" +
          "        Lord Huma, deliver him.\n\n",
           "        Beyond the wild, impartial skies\n" +
           "        Have you set your lodgings,\n" +
           "        In cantonments of stars, where the sword aspires\n" +
           "        In an arc of yearning, where we join in the singing.\n\n"}),
"elven" : ({"        The Sun\n" +
    "        The Splendid eye\n" +
    "        Of all our heavens\n" +
    "        Dives from the day,\n\n",
        "        And Leaves\n" +
        "        The dozing sky,\n" +
        "        Spangled with fireflies,\n" +
        "        Deepening in gray.\n\n",
            "        Now Sleep,\n" +
            "        Our oldest friend,\n" +
            "        Lulls in the trees\n" +
            "        And calls\n" +
            "        Us in.\n\n",
                "        The Leaves\n" +
                "        Give off cold fire,\n" +
                "        They blaze into ash\n" +
                "        At the end of the year.\n\n",
                    "        And birds\n" +
                    "        Coast on the winds,\n" +
                    "        And wheel to the North\n" +
                    "        When Autumn ends.\n\n",
                        "        The day grows dark,\n" +
                        "        The seasons bare,\n" +
                        "        But we\n" +
                        "        Await the sun's\n" +
                        "        Green fire upon\n" +
                        "        The Trees.\n\n",
                            "        The wind\n" +
                            "        Dives through the days.\n" +
                            "        By season, by moon\n" +
                            "        Great kingdoms arise.\n\n",
                                "        The breath\n" +
                                "        Of firefly, of bird,\n" +
                                "        Of trees, of mankind\n" +
                                "        Fades in a word.\n\n",
                                    "        Now Sleep,\n" +
                                    "        Our oldest friend,\n" +
                                    "        Lulls in the trees\n" +
                                    "        And calls\n" +
                                    "        Us in.\n\n",
                                        "        The Age,\n" +
                                        "        The thousand lives\n" +
                                        "        Of men and their stories\n" +
                                        "        Go to their graves.\n\n",
                                            "        But we,\n" +
                                            "        The people long\n" +
                                            "        In poem and glory\n" +
                                            "        Fade from the song.\n\n"}),
"dwarf" : ({"        Metal rings beneath my hammer\n" +
    "        Steel takes shape on anvil cold.\n" +
    "        Fire glows bright with sighs from bellows,\n" +
    "        Gold, silver, bronze, all these to mold.\n\n",
        "        Metal sings beneath my hammer,\n" +
        "        Star-bright sparks rain down and fade.\n" +
        "        Quench the blank in fog draped water,\n" +
        "        Draw fire again and none afraid.\n\n"}),
"gully" : ({"        Be there strings of greeney goop\n" +
  "        in you head like tides?\n" +
  "        Belly doing flop flops?\n" +
  "        Nose red enough to hide?\n\n",
    "        Rat it was some over-aged\n" +
    "        when you cared to dine?\n" +
    "        Got a good cure sure enough,\n" +
    "        soon you be all fine!\n\n",
      "        Lizard Cure, Lizard Cure,\n" +
      "        it sure make you whole.\n" +
      "        Get better inhale scent,\n" +
      "        should be you only goals.\n" +
      "        Do not mind its cold dead eyes\n" +
      "        staring at you chin.\n" +
      "        Just think what it do for you,\n" +
      "        make you right again!\n\n",
        "        Stew is fighting back tonight?\n" +
        "        Shoulders caught a shiver?\n" +
        "        Mage he threw a spell on you?\n" +
        "        Lightning left you quiver?\n\n",
          "        Crossed a dragon's path again,\n" +
          "        skin burned, muscles sore?\n" +
          "        Got the thing to fix you up:\n" +
          "        stand still get the cure!\n\n",
            "        Lizard Cure, Lizard Cure,\n" +
            "        it sure make you whole.\n" +
            "        Get better inhale scent,\n" +
            "        should be you only goals.\n" +
            "        Do not mind its cold dead eyes\n" +
            "        staring at you chin.\n" +
            "        Just think what it do for you,\n" +
            "        make you right again!\n\n",
              "        Hail danced dimples on you head?\n" +
              "        Fall smack down in slime?\n" +
              "        Knight he knocked big hole in you?\n" +
              "        Be all right in time!\n\n",
                "        Got huge curse laid on you tail?\n" +
                "        Toe swole big as tree?\n" +
                "        Do not fret, the Lizard Cure'll\n" +
                "        sure soon set you free!\n\n",
                  "        Lizard Cure, Lizard Cure,\n" +
                  "        it sure make you whole.\n" +
                  "        Get better inhale scent,\n" +
                  "        should be you only goals.\n" +
                  "        Do not mind its cold dead eyes\n" +
                  "        staring at you chin.\n" +
                  "        Just think what it do for you,\n" +
                  "        make you right again!\n\n",
                    "        Pimples on you earlobes, blue\n" +
                    "        fungus on you toes,\n" +
                    "        Ouch among you insides,\n" +
                    "        sick from gods may know.\n\n",
                      "        Gotta get soon better,\n" +
                      "        important things to do.\n" +
                      "        Stand real still, the Lizard Cure\n" +
                      "        gonna take care of you!\n\n",
                        "        Lizard Cure, Lizard Cure,\n" +
                        "        it sure make you whole.\n" +
                        "        Get better inhale scent,\n" +
                        "        should be you only goals.\n" +
                        "        Do not mind its cold dead eyes\n" +
                        "        staring at you chin.\n" +
                        "        Just think what it do for you,\n" +
                        "        make you right again!\n\n" }) ]);

static int gMarker = 0;
static int gSongAlarm;
object gSinger;

public void
sing_song(string song)
{
    set_this_player(gSinger);

    if (!gMarker)
    {
        write("You raise your voice in song.\n");
        tell_room(environment(this_player()), QCTNAME(this_player()) + 
            " raises " + this_player()->query_possessive() + 
            " voice in song.\n", this_player());
    }

    if (gMarker >= sizeof(gSongList[song]))
    {
        gSongAlarm = 0;
        return;
    }
    else
    {
        tell_room(environment(gSinger), gSongList[song][gMarker]);
        gSongAlarm = set_alarm(3.5, 0.0, &sing_song(song));
        gMarker++;
        return;
    }

}

public int
ksong(string str)
{
    if (!strlen(str))
    {
        notify_fail("Sing what song? Or stop?\n");
        return 0;
    }

    str = lower_case(str);

    if (str == "stop")
    {
        remove_alarm(gSongAlarm);
        write("You stop your song.\n");
        return 1;
    }

    if (gSongAlarm)
    {
        write("You are already singing.\n");
        return 1;
    }

    gSinger = this_player();
    gMarker = 0;

    switch(str)
    {
    case "thinking song":
    case "thinking":
        sing_song("thinking");
        break;
    case "gully dwarf":
    case "gully":
    case "gully dwarf healing song":
    case "healing song":
        sing_song("gully");
        break;
    case "dwarf song":
    case "dwarf":
    case "forging song":
    case "dwarven song":
    case "dwarven":
    case "forging":
    case "dwarven forging song":
        sing_song("dwarf");
        break;
    case "mourning":
    case "mourning song":
        sing_song("mourning");
        break;
    case "trail":
    case "trail song":
        sing_song("trail");
        break;
    case "drinking":
    case "drinking song":
    case "kender drinking song":
        sing_song("kdrinking");
        break;
    case "three sheets":
    case "three sheets to the wind":
        sing_song("drinking");
        break;
    case "death song":
    case "death":
    case "solamnic death song":
        sing_song("death");
        break;
    case "elven hymn":
    case "elven":
    case "hymn":
        sing_song("elven");
        break;
    default:   
        notify_fail("Sing what song? Or stop singing?\n");
        return 0;
    }

    return 1;
}
