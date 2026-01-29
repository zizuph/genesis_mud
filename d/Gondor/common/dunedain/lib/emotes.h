/*
 *	The emotes in the soul of the Dunedain.
 *
 *	Copyright (c) 1994, 1997 by Christian Markus
 *
 *	Created: Olorin, 08-nov-1994
 *
 *	Modification log:
 *	12-Feb-1997, Olorin:	General revision.
 *	28-Jun-1998, Gnadnar:	Gondor wizards and arches always
 *				understand adunaic.
 *      Emotion 'ecry' added 30-jan-2002, Skippern
 */
#include <adverbs.h>
#include <cmdparse.h>
#include <composite.h>
#include <filter_funs.h>
#include <formulas.h>
#include <stdproperties.h>
#include <std.h>
#include <files.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/dunedain/lib/song.h"

#define SOULDESC(x)	(this_player()->add_prop(LIVE_S_SOULEXTRA, x))
#define ADV_DUMMY	"ADVERB"

/*
 * emotions, ordered alphabetically
 */
int
amazed(string str)
{
    object *oblist;

    if (!strlen(str))
    {
        write("You are amazed and look with great wonder at your "
          + "surroundings.\n");
        allbb(" is amazed and looks with great wonder at "+POSSESSIVE(TP)
          + " surroundings.");
        SOULDESC("looking amazed");
        return 1;
    }

    oblist = parse_this(str, "[at] [the] %l");
    oblist -= ({ TP });

    if (!sizeof(oblist))
        NFN0("Look amazed at whom?");

    SOULDESC("looking amazed");
    actor("You are amazed and look with great wonder at", oblist, ".");
    targetbb(" is amazed and looks with great wonder at you.", oblist);
    all2actbb(" is amazed and looks with great wonder at", oblist, ".");

    return 1;
}

int
battle_cry(string str)
{
    int     il;
    object  troom,
           *rooms;

    if (strlen(str))
        write("You cry out: "+str+"!\n");
    else
    {
        write("You shout the ancient battle cry of the Edain of the North: "
          + "Lacho calad! Drego Morn!\n");
        str = "Lacho calad! Drego Morn";
    }

    if (!(troom = ENV(TP)))
        return 0;

    FIX_EUID
    rooms = FIND_NEIGHBOURS(troom, 2);

    for (il = 0; il < sizeof(rooms); il++)
        tell_room(rooms[il], "@@shout_name:" + CMD_LIVE_SPEECH +
                  "@@ cries out: " + str + "!\n", TP);

    return 1;
}

int
ecry(string str)
{
    int     il;
    object  troom,
            *rooms;

    if (strlen(str))
        write("You cry out: "+str+"!\n");
    else
    {
        write("You cry out the old numenorian oath: "
	    + "Zori agan! Kalab ugru-dalad!\n");
	str = "Zori agan! Kalab ugru-dalad";
    }

    if (!(troom = ENV(TP)))
        return 0;

    FIX_EUID
    rooms = FIND_NEIGHBOURS(troom, 2);

    for (il = 0; il < sizeof(rooms); il++)
        tell_room(rooms[il], "@@shout_name:" + CMD_LIVE_SPEECH +
	    "@@ cries out: " + str + "!\n", TP);

    return 1;
}

int
behold(string str)
{
    object *oblist = ({}),
           *elves,
            item,
           *items,
            tp = TP;
    string *how,
            item_str;

    how = parse_adverb_with_space(str, "happily", 0);

    oblist = FILTER_LIVE(all_inventory(ENV(tp))) - ({ tp });
    elves = filter(oblist, filter_elf) + filter(oblist, query_is_dunadan);
    oblist -= elves;

    if (!strlen(how[0]))
    {
        write("You cry out"+how[1]+": Yo! utuvienyes!\n");
	if (sizeof(oblist))
	{
            target(" cries out"+how[1]+": Yo! utuvienyes!", oblist);
	}
	if (sizeof(elves))
	{
            target(" cries out"+how[1]+
		": Yo! utuvienyes! Lo! I have found it!", elves);
	}
        return 1;
    }

    if (ENV(tp)->item_id(how[0]))
        item_str = "the " + how[0];
    else if (parse_command(how[0], all_inventory(ENV(tp)), "%i", items))
    {
        items = NORMAL_ACCESS(items, 0, 0);
        items = FILTER_DEAD(items);

        if (!sizeof(items))
            NFN0("Behold which item?");

        item_str = COMPOSITE_DEAD(items);
    }
    else
        NFN0("Behold which item?");

    write("You point at "+item_str+" and cry out"
      + how[1]+": Yo! utuvienyes!\n");
    if (sizeof(oblist))
    {
        target(" points at "+item_str
            + " and cries out"+how[1]+": Yo! utuvienyes!", oblist);
    }
    if (sizeof(elves))
    {
        target(" points at "+item_str
            + " and cries out"+how[1]+
	    ": Yo! utuvienyes! Lo! I have found it!", elves);
    }

    return 1;
}

int
dlaugh(string str)
{
    int     so;
    object *oblist,
            tp = TP;
    string *how;

    how = parse_adverb_with_space(str, "comfortingly", 0);

    if (!strlen(how[0]))
        NFN0("Try to comfort whom?");

    oblist = parse_this(how[0], "[at] [the] %l");
    oblist -= ({ TP });

    if (!(so = sizeof(oblist)))
        NFN0("Try to comfort whom?");

    SOULDESC("laughing"+how[1]);
    actor("You laugh"+how[1]+" at", oblist, ", seeing the dismay in "
      + (so > 1 ? "their" : POSSESSIVE(oblist[0])) + " eyes.");
    targetbb(" laughs"+how[1]+" at you, seeing the dismay in your "
      + "eyes.", oblist);
    all2actbb(" laughs"+how[1]+" at", oblist, ", seeing the dismay in "
      + (so > 1 ? "their" : POSSESSIVE(oblist[0])) + " eyes.");
    
    return 1;
}

int
doffer(string str)
{
    object *oblist,
           *weapon,
            tp = TP;
    string  dummy,
            his,
            wname;

    NFN("Offer which weapon to whom?");
    if (!strlen(str) || !CAN_SEE_IN_ROOM(tp))
        return 0;

    /* trying to use two placeholders in parse_command() does not
       work properly:
       parse_command(LOW(str), ENV(tp), "[the] %i 'to' [the] %l", weapon, oblist);
       does not find any living in ENV(tp).
       parse_command(LOW(str), deep_inventory(ENV(tp)), "[the] %i 'to' [the] %l", weapon, oblist);
       finds arbitrary livings in ENV(tp), but not the ones you look for
     */
    if (!parse_command(LOW(str), ENV(tp), "[the] %i 'to' %s", weapon, dummy))
        NFN0("Offer which weapon to whom?");
        
    weapon = NORMAL_ACCESS(weapon, 0, 0) - ({ 0 });
    /* This cannot be done in NORMAL_ACCESS, as nacs() as filter function
       is replaced is another one is specified using the second argument
       of NORMAL_ACCESS
     */
    weapon = filter(weapon, filter_weapon);
    if (!sizeof(weapon))
        NFN0("Offer which weapon to whom?");

    oblist = parse_this(dummy, "[the] %l");

    if (!sizeof(oblist))
        NFN0("Offer your "+weapon[0]->short()+" to whom?");
    oblist = ({ oblist[0] });

    his = POSSESSIVE(tp);
    wname = weapon[0]->short();
    actor("You offer your "+wname+" to", oblist, ".");
    targetbb(" swings "+his+" "+wname+" around in "+his
      + " hand and offers it to you.", oblist);
    all2actbb(" swings "+his+" "+wname+" around in "+his
      + " hand and offers it to", oblist, ".");
    return 1;
}

int
dsmile(string str)
{
    object *oblist,
            tp = TP;
    string *how;

    how = parse_adverb_with_space(str, "confidently", 0);

    if (!strlen(how[0]))
    {
        write("You smile"+how[1]+", despite the adversity facing you.\n");
        allbb(" smiles"+how[1]+", despite the adversity facing "+OBJECTIVE(tp)+".");
        SOULDESC("smiling"+how[1]);
        return 1;
    }
    
    oblist = parse_this(how[0], "[at] [the] %l");

    if (!sizeof(oblist))
        NFN0("Smile at whom?");

    actor("You smile"+how[1]+" at", oblist,
	", despite the adversity facing you.");
    target(" smiles"+how[1]+
	" at you, despite the adversity facing "+OBJECTIVE(tp)+".",
        oblist);
    all2actbb(" smiles"+how[1]+ " at", oblist,
	", despite the adversity facing " + OBJECTIVE(tp)+".");
    SOULDESC("smiling"+how[1]);
    return 1;
}

int
dstare(string str)
{
    object *oblist,
            tp = TP;
    string *how;

    how = parse_adverb_with_space(str, "grimly", 0);

    if (!strlen(how[0]))
    {
        write("You stare"+how[1]+" at the storm clouds in the East, "
          + "gauging their distance.\n");
        allbb(" stares"+how[1]+" at the storm clouds in the East, "
          + "gauging their distance.");
        return 1;
    }

    oblist = parse_this(how[0], "[at] [the] %l");
    oblist -= ({ TP });
    if (!sizeof(oblist))
        NFN0("Stare at whom?");

    actor("You stare"+how[1]+" at", oblist, ", uncertain what to expect.");
    targetbb(" stares"+how[1]+" at you as if uncertain of your intentions.", oblist);
    all2actbb(" stares"+how[1]+" at", oblist, " as if uncertain what to expect.");
    return 1;
}

int
drefuse(string str)
{
    object *oblist,
            tp = TP;
    string *how;

    how = parse_adverb_with_space(str, "steadfastly", 0);

    if (!strlen(how[0]))
    {
        write("You"+how[1]+" refuse to back down.\n");
        allbb(how[1]+" refuses to back down.");
        return 1;
    }

    oblist = parse_this(how[0], "[the] %l");
    oblist -= ({ TP });

    if (!sizeof(oblist))
        NFN0("Refuse whose advice?");

    actor("You"+how[1]+" refuse the advice of", oblist, ".");
    target(how[1]+" refuses to follow your counsel.", oblist);
    all2actbb(" " + how[1][1..]+" refuses the advice of", oblist, ".");
    return 1;
}

int
elfhail(string str)
{
    object *oblist,
            tp = TP;
    string *how;

    how = parse_adverb_with_space(str, "deeply", 0);

    if (!strlen(how[0]))
        how[0] = "all";

    oblist = parse_this(how[0], "[the] %l");
    oblist -= ({ TP });
    oblist = filter(oblist, filter_elf);

    if (!sizeof(oblist))
        NFN0("Hail whom?");

    actor("You bow"+how[1]+" before", oblist, ", saying: "
      + "Elen sila lumenn' omentielvo!");
    target(" bows"+how[1]+" before you, saying: Elen sila lumenn' omentielvo, "
      + "a star shines on the hour of our meeting!", oblist);
    all2act(" bows"+how[1]+" before", oblist, ", saying: "
      + "Elen sila lumenn' omentielvo!");

    return 1;
}

int
embrace(string str)
{
    object *oblist,
            tp = TP;
    string *how;

    how = parse_adverb_with_space(str, "warmly", 0);

    if (!strlen(how[0]))
        NFN0("Embrace whom?");

    oblist = parse_this(how[0], "[to] [the] %l");
    oblist -= ({ TP });

    if (!sizeof(oblist) || sizeof(oblist) > 1)
        NFN0("Embrace whom?");

    actor("You embrace", oblist, how[1]+", kissing "
      + OBJECTIVE(oblist[0]) + " on the forehead.");
    target(" embraces you"+how[1]+", kissing you on the forehead.",
        oblist);
    all2act(" embraces", oblist, how[1]+", kissing "
      + OBJECTIVE(oblist[0]) + " on the forehead.");

    return 1;
}

int
farewell(string str)
{
    object *oblist,
            tp = TP;
    string *how;

    how = parse_adverb_with_space(str, "warmly", 0);

    if (!strlen(how[0]))
        how[0] = "all";

    oblist = parse_this(how[0], "[to] [the] %l");
    oblist -= ({ TP });

    if (!sizeof(oblist))
        NFN0("Bid farewell to whom?");

    actor("You"+how[1]+" bid farewell to", oblist, ", saying: "
      + "Go now with good speed, and may the Sun of your setting "
      + "out not cease to shine on your road.");
    target(how[1]+" bids you farewell with the words: "
      + "Go now with good speed, and may the Sun of your setting "
      + "out not cease to shine on your road.", oblist);
    all2act(" " + how[1][1..strlen(how[1])]+" bids farewell to", oblist,
        " with the words: Go now with good speed, and may the "
      + "Sun of your setting out not cease to shine on your road.");

    return 1;
}

int
gleam(string str)
{
    object *oblist,
            tp = TP;

    if (!strlen(str))
    {
        write("You feel your eyes to get a peculiar gleam.\n");
        allbb(" gets a peculiar gleam in "+POSSESSIVE(tp)+" eyes.");
        return 1;
    }

    oblist = parse_this(str, "[at] [the] %l");
    oblist -= ({ TP });

    if (!sizeof(oblist))
        NFN0("Look at whom?");

    actor("You look at", oblist, " in a peculiar way.");
    targetbb(" looks at you with a peculiar gleam in "+POSSESSIVE(tp)+" eyes.",
        oblist);
    all2actbb(" looks at", oblist, " with a peculiar gleam in "
      + POSSESSIVE(tp)+" eyes.");

    return 1;
}

int
glitter(string str)
{
    object  tp = TP,
            scabbard,
           *weapons;
    string  his = "",
            your = "",
            msg1 = "",
            msg2 = "."; 

    if (strlen(str))
        NFN0("What ?");

    weapons = tp->query_weapon(-1);
    if (objectp(scabbard = present("scabbard", tp)))
        weapons += all_inventory(scabbard);
    if (sizeof(weapons = filter(weapons, filter_sword)))
    {
        msg1 = ", smiting the hilt of ";
        msg2 = " sword.";
        his = POSSESSIVE(tp);
        your = "your";
    }
    write("You feel a glitter in your eyes as you think of battle"
      + msg1 + your + msg2 + "\n");
    allbb(" has a glitter in "+POSSESSIVE(tp)+" eyes as "+PRONOUN(tp)
      + " thinks of battle" + msg1 + his + msg2);
    return 1;
}

int
oath(string str)
{
    string oname;

    if (!strlen(str))
        str = "of Elendil";

    str = LOW(str);

    parse_command(str, ({}), "[of] %w", oname);
    NF("Swear which oath?\n");
    switch (oname)
    {
        case "elendil":
            write("You renew the Oath of Elendil with the words "
                + "that Elendil spoke when he came up out of the Sea "
                + "on the wings of the wind:\n"
                + "\tEt Earello Endorenna utulien.\n"
                + "\tSinome maruvan ar Hildinyar tenn' Ambar-metta!\n");
            all(" renews the Oath of Elendil, speaking the ancient words:\n"
                + "\tEt Earello Endorenna utulien.\n"
                + "\tSinome maruvan ar Hildinyar tenn' Ambar-metta!");
            break;
        default:
            return 0;
            break;
    }
    return 1;
}

int
pace(string str)
{
    string *how;

    how = parse_adverb_with_space(str, "restlessly", 0);

    if (strlen(how[0]))
    {
        NF("Pace how?\n");
        return 0;
    }

    SOULDESC("pacing around"+how[1]);
    write("You pace the ground"+how[1]+", thinking about the proper "
      + "course of action.\n");
    allbb(" paces the ground"+how[1]+", thinking about the proper "
      + "course of action.");

    return 1;
}

int
dsalute(string str)
{
    object *oblist,
            tp = TP;
    string *how;

    how = parse_adverb_with_space(str, "courteously", 0);

    if (!strlen(how[0]))
    {
        write("You"+how[1]+" salute after the manner of Gondor "
          + "with bowed head and hands upon your breast.\n");
        allbb(how[1]+" bows "+POSSESSIVE(tp)+" head with hands upon "
          + POSSESSIVE(tp)+" breast.");
        return 1;
    }

    oblist = parse_this(how[0], "[at] [the] %l");
    oblist -= ({ TP });

    if (!sizeof(oblist))
        NFN0("Salute whom?");

    actor("You"+how[1]+" salute", oblist, " after the manner of Gondor.");
    targetbb(how[1]+" salutes you with bowed head and hands upon "
      + POSSESSIVE(tp) + " breast.", oblist);
    all2actbb(" " + how[1][1..]+" salutes", oblist,
        " with bowed head and " + "hands upon " + POSSESSIVE(tp) + " breast.");

    return 1;
}

int
silence(string str)
{
    NF("If you want to observe the Standing Silence, type 'silence'.\n");
    if (strlen(str))
        return 0;

    SOULDESC("observing the Standing Silence");
    write("Observing ancient custom, before you begin your meal "
      + "you turn west in silence and look towards Numenor "
      + "that was, and beyond to Elvenhome that is, and to that which "
      + "is beyond Elvenhome and will ever be.\n");

    all(" turns and faces west in a moment of silence before beginning "
      + POSSESSIVE(TP) + " meal.");

    return 1;
}

string
adunaic_text(string text)
{
    object player = previous_object(-1);
    int skill = player->query_skill(SS_LANGUAGE);
    string name = player->query_real_name();

    int understand = ((IS_RANGER(player) && (skill > 15)) ||
        (query_is_dunadan(player) && (skill > 1)) ||
        (IS_SINDAR(player) && (skill > ADUNAIC_DIFF - 25)) ||
        (skill > ADUNAIC_DIFF) ||
        ((SECURITY->query_wiz_dom(name) == "Gondor") ||
	 (SECURITY->query_wiz_rank(name) >= WIZ_ARCH)));

    if (!understand)
	return "speaks in an unknown language.";
    else
	return "speaks in Adunaic: " + text;
}

int
speak_adunaic(string str)
{
    mixed   gag;
    string *words, *texts;
    object *objs;
    string  msg;
    int     line;
   
    if (!strlen(str))
        NFN0("Say what in Adunaic?");

    if (gag = TP->query_prop(LIVE_M_MOUTH_BLOCKED))
    {
        if (stringp(gag))
	{
            TP->catch_msg(gag);
	    return 1;
	}
        write("You are unable to speak right now!\n");
        return 1;
    }

    /* Adunaic is broken into several speeches if the text exceeds 60. */
    if (strlen(str) < 60)
    {
	texts = ({ str });
    }
    else
    {
	words = explode(str, " ");
	texts = ({ "" });
	line = 0;
	foreach(string word: words)
	{
	    if (strlen(texts[line] + " " + word) > 60)
	    {
		texts += ({ "" });
	        line++;
	    }
	    texts[line] += (" " + word);
	}
    }

    foreach(string text: texts)
    {
        say_gmcp("adunaic", QCTNAME(this_player()) +
	    " @@adunaic_text:" + file_name(this_object()) + "|" + text + "@@\n");

        msg = "You speak in Adunaic: " + text; 
        write(msg + "\n");
        this_player()->gmcp_comms("adunaic", 0, msg);
    }
    return 1;
}

int
sing(string str)
{
    int     sing_alarm;
    object  tp = TP;
    string  title;

    if (!strlen(str))
        return 0;

    str = LOW(str);

    switch (str)
    {
        case "earendil":
        case "elbereth":
        case "gilthoniel":
        case "snowwhite":
        case "felagund":
        case "gil-galad":
        case "thalion":
        case "tinuviel":
            if (tp->query_prop(DUNEDAIN_S_SINGING))
            {
                NF("You are already singing a song!\n");
                return 0;
            }
            title = str;
            set_alarm(0.0, 0.0, "do_song", tp, title, 1);
            tp->add_prop(DUNEDAIN_S_SINGING, title);
            break;
        default:
            NFN0("You do not know a song of that name!");
            break;
    }
    SOULDESC("singing a song");
    return 1;
}

int
steel(string str)
{
    object  tp = TP;

    if (!strlen(str))
        str = "the coming onslaught";

    write("You steel yourself for "+str+".\n");
    allbb(" steels "+OBJECTIVE(tp)+"self for "+str+".");
    return 1;
}

int
stop_singing(string str)
{
    int     title = TP->query_prop(DUNEDAIN_S_SINGING);

    if (str != "singing")
    {
        if (!title)
        {
            NFN0("Stop what? The world?");
        }
        else
        {
            NFN0("Stop what? Singing perhaps?");
        }
    }
    else
    {
        if (!title)
        {
            NFN0("But you are not singing any song!");
        }
        else
        {
            TP->remove_prop(DUNEDAIN_S_SINGING);
            TP->remove_prop(LIVE_S_SOULEXTRA);
            write("You stop singing.\n");
            return 1;
        }
    }
}

int
do_song(object tp, string title, int verse)
{
    float   delay = 5.0;
    object  room;
    string *song_text;

    if (!objectp(tp) || !living(tp))
        return 0;

    if (!tp->query_prop(DUNEDAIN_S_SINGING))
        return 0;

    if (!objectp(room = ENV(tp)))
    {
        tp->remove_prop(DUNEDAIN_S_SINGING);
        return 0;
    }

    switch (title)
    {
        case "gil-galad":
            song_text = D_SONG_GILGALAD;
            if (verse == 1)
            {
                write("You start to sing a song about "
                  + "Gil-Galad, the "
                  + "last High King of the Noldor in Middle Earth:\n");
                tell_room(room, QCTNAME(tp)+" starts to sing a song "
                  + "about Gil-Galad, the last "
                  + "High King of the Noldor in Middle Earth:\n\n", tp);
            }
            break;
        case "tinuviel":
            song_text = D_SONG_TINUVIEL;
            if (verse == 1)
            {
                write("You start to sing the tale of "
                  + "Luthien Tinuviel:\n");
                tell_room(room, QCTNAME(tp)+" starts to sing the "
                  + "tale of Luthien Tinuviel:\n\n", tp);
            }
            break;
        case "earendil":
            song_text = D_SONG_EARENDIL1 + D_SONG_EARENDIL2;
            if (verse == 1)
            {
                write("You start to sing a song about "
                  + "Earendil the Mariner:\n");
                tell_room(room, QCTNAME(tp)+" starts to sing a song "
                  + "about Earendil the Mariner:\n\n", tp);
            }
            break;
        case "elbereth":
        case "gilthoniel":
            song_text = D_SONG_ELBERETH;
            if (verse == 1)
            {
                write("You sing a song to Elbereth, the Starkindler:\n");
                tell_room(room, QCTNAME(tp)+" sings a song to "
                  + "Elbereth, the Starkindler:\n\n", tp);
            }
            break;
        case "snowwhite":
            song_text = D_SONG_SNOWWHITE;
            if (verse == 1)
            {
                write("You sing a song to Elbereth, the Starkindler:\n");
                tell_room(room, QCTNAME(tp)+" sings a song to "
                  + "Elbereth, the Starkindler:\n\n", tp);
            }
            break;
        case "felagund":
            song_text = D_SONG_FELAGUND;
            if (verse == 1)
            {
                write("You start to sing the part of the "
                  + "Lay of Leithian that tells of the contest between "
                  + "Sauron and King Finrod Felagund which is renowned:\n");
                tell_room(room, QCTNAME(tp)+" starts to sing the part of "
                  + "the Lay of Leithian that tells of the contest "
                  + "between Sauron and King Finrod Felagund which "
                  + "is renowned:\n\n", tp);
            }
            break;
        case "thalion":
            song_text = D_SONG_THALION_1 + D_SONG_THALION_2
                      + D_SONG_THALION_3 + D_SONG_THALION_4;
            delay = 20.0;
            if (verse == 1)
            {
                write("You start to sing the first part of "
                  + "the Lay of the Children of Hurin, which relates the "
                  + "feats of Hurin Thalion in the Nirnaeth Arnoediad "
                  + "and his fate thereafter:\n");
                tell_room(room, QCTNAME(tp)+" starts to sing the first part "
                  + "of the Lay of the Children of Hurin, which relates the "
                  + "feats of Hurin Thalion in the Nirnaeth Arnoediad and "
                  + "his fate thereafter:\n\n", tp);
            }
            break;
        default:
            tp->remove_prop(DUNEDAIN_S_SINGING);
            tp->remove_prop(LIVE_S_SOULEXTRA);
            return 0;
            break;
    }

    if (verse > 1)
    {
        tp->catch_msg("You continue your song:\n\n");
        tell_room(room, QCTNAME(tp)+" continues "+POSSESSIVE(tp)
          + " song:\n\n", tp);
    }
    tp->catch_msg(song_text[verse-1] + "\n");
    tell_room(room, song_text[verse-1] + "\n", tp);
    if (verse >= (sizeof(song_text)))
    {
        tp->catch_msg("You have finished your song.\n");
        tell_room(room, QCTNAME(tp)+" has finished "+POSSESSIVE(tp)
          + " song.\n", tp);
        tp->remove_prop(DUNEDAIN_S_SINGING);
        tp->remove_prop(LIVE_S_SOULEXTRA);
        return 0;
    }

    set_alarm(delay, 0.0, "do_song", tp, title, verse+1);
    return 1;
}

int
tongue(string str)
{
    int     s;
    object *oblist,
            tp = TP;
    string *how,
            his;

    how = parse_adverb_with_space(str, "desperately", 0);

    if (!strlen(how[0]))
        NFN0("Wish whom to be silent?");

    oblist = parse_this(how[0], "[the] %l");
    oblist -= ({ TP });

    if (!sizeof(oblist))
        NFN0("Wish whom to be silent?");

    if ((s = sizeof(oblist)) == 1)
    {
        his = POSSESSIVE(oblist[0]) + " tongue";
    }
    else
    {
        his = "their tongues";
    }

    actor("You"+how[1]+" wish", oblist, " would hold "
      + his + ".");
    targetbb(" looks like "+PRONOUN(tp)+how[1]+" wished you would hold your "
      + "tongue.", oblist);
    all2actbb(" looks like "+PRONOUN(tp)+how[1]+" wished", oblist,
        " would hold " + his + ".");

    return 1;
}

int
turneyes(string str)
{
    object *oblist,
            tp = TP;
    string *how;

    how = parse_adverb_with_space(str, "fiercely", 0);

    if (!strlen(how[0]))
        NFN0("Turn your eyes on whom?");

    oblist = parse_this(how[0], "[on] [the] %l");
    oblist -= ({ TP });

    if (!sizeof(oblist))
        NFN0("Turn your eyes on whom?");

    actor("You turn your eyes"+how[1]+" on", oblist, ".");
    targetbb(" turns "+POSSESSIVE(tp)+" piercing eyes"+how[1]
      + " on you like stabbing daggers of fire.", oblist);
    all2actbb(" turns"+how[1]+" to", oblist, ", "+POSSESSIVE(tp)
      + " piercing eyes glowing with smouldering fire that may "
      + "suddenly burst into flame.");

    return 1;
}

int
uplift(string str)
{
    object *oblist,
            tp = TP;
    string *how;

    how = parse_adverb_with_space(str, "deeply", 0);

    if (strlen(how[0]))
        NFN0("Uplift your heart how?");

    write("You drink"+how[1]+" of the fresh air, uplifting "
      + "your heart like the drinking of cool wine!\n");
    say(QCTNAME(tp)+" drinks"+how[1]+" of the fresh air, which "
      + "seems to uplift "+POSSESSIVE(tp)+" heart.\n");
    SOULDESC("drinking"+how[1]+" of the fresh air");
    return 1;
}

int
wellmet(string str)
{
    object *oblist,
            tp = TP;
    string *how;

    how = parse_adverb_with_space(str, "happily", 0);

    if (!strlen(how[0]))
        how[0] = "all";

    oblist = parse_this(how[0], "%l");
    oblist -= ({ TP });
    oblist = filter(oblist, query_is_dunadan);

    if (!sizeof(oblist))
        NFN0("Hail whom?");

    actor("You call out"+how[1]+" at", oblist, ": "
      + "Ai na vedui Dunadan! Mae govannen!");
    target(" calls out"+how[1]+" at you: "
      + "Ai na vedui Dunadan! Mae govannen!", oblist);
    all2act(" calls out"+how[1]+" at", oblist, ": "
      + "Ai na vedui Dunadan! Mae govannen!");
    return 1;
}

