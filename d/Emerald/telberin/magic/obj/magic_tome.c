/*
 *  /d/Emerald/telberin/magic/obj/magic_tome.c
 *
 *  This book is used by the scholars of the Telberin Magic Guild, and is
 *  housed within their campus. Though its contents would be cryptic and
 *  beyond comprehension to most people, it is nonetheless available for
 *  the public, and may be read by anyone who wishes to do so.
 *
 *  Copyright (c) February 2001, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/std/object";

#include <macros.h>  /* for QCTNAME, etc */
#include <stdproperties.h>
#include "/d/Emerald/blackwall/delrimmon/defs.h"

/* global variables */
public int     Book_Open = 0;

/* prototypes */
public void        create_object();
public string      describe();
public int         mess_with_book(string arg);
public int         read_book(string arg);
public string      read_index();
public void        init();
public string      exa_cover();


/*
 * Function name:        create_object
 * Description  :        set up the book
 */
public void
create_object()
{
    set_name("tome");
    add_name( ({ "book", "_telberin_enchantment_tome" }) );
    add_adj( ({ "massive", "enchanters", "enchanter's" }) );

    set_short("massive tome");
    set_long(describe);

    add_item( ({ "cover", "leather cover", "thick cover",
                 "thick leather cover", "cover of the book",
                 "cover of the tome", "book cover",
                 "bracket", "brackets", "metal bracket",
                 "metal brackets" }), exa_cover);
    add_item( ({ "page", "pages", "pages of the book",
                 "pages of the tome", "many pages" }),
        "The number of pages contained in the tome are daunting"
      + " to any but the most motivated student of the magic arts."
      + " It is doubtful that the book could be read cover to cover"
      + " in less than a year's time.\n");
    add_item( ({ "gem", "gems", "metal", "metals",
                 "gems and metals", "metals and gems" }),
        "The cover of the book is inlaid with gems and metals,"
      + " many of which appear rather exotic in color.\n");


    add_prop(OBJ_M_NO_GET, "You could not possibly lift this book.\n");

    FIX_EUID
} /* create_object */


/*
 * Function name:        describe
 * Description  :        provide a long description for the object,
 *                       with some changes depending on global vars
 * Returns      :        string - the description
 */
public string
describe()
{
    string txt = "This massive book is nearly a meter high, and looks to"
               + " be many hundreds of pages thick. Its covers are"
               + " elegantly bound in fine leather, inlaid with many"
               + " beautiful gems and metals. You gaze upon the"
               + " Enchanter's Tome, the pride and joy of the Magic"
               + " Guild of Telberin.";

    if (!Book_Open)
    {
        return txt + " Its covers are currently closed.\n";
    }

    return txt + " Its covers are currently spread wide open.\n";
} /* describe */


/*
 * Function name:        mess_with_book
 * Description  :        allow the player to open/close, etc the book
 * Arguments    :        string arg - what the player typed
 * Returns      :        int 1 - success, 0 - failure
 */
public int
mess_with_book(string arg)
{
    if (!strlen(arg))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[up] [the] [massive] [enchanters] [enchanter's]"
      + " 'book' / 'tome' / 'pages' / 'cover'"))
    {
        return 0; /* the player used syntax we can't process */
    }

    if (query_verb() == "open")
    {
        if (Book_Open)
        {
            write("The book already lies open.\n");
            return 1;
        }

        write("You carefully lift the mighty cover of the tome, and"
            + " lay the book open. The heavy pages slide slowly apart"
            + " and then lie still.\n");
        tell_room(environment(this_player()),
            QCTNAME(this_player()) + " carefully opens the massive"
          + " tome.\n", this_player());

        Book_Open = 1;

        return 1;
    }

    if (Book_Open)
    {
        write("You lift the cover of the book, and lay it shut.\n");
        tell_room(environment(this_player()),
            QCTNAME(this_player()) + " closes the massive tome.\n",
            this_player());

        Book_Open = 0;

        return 1;
    }

    write("The tome is already shut.\n");
    return 1;
} /* mess_with_book */


/*
 * Function name:        read_book
 * Description  :        allow the player to read various things in
 *                       the book.
 * Arguments    :        string arg - what the player typed
 * Returns      :        int 1 - success, 0 - failure
 */
public int
read_book(string arg)
{
    string  txt = "Much of what you see written here is beyond your"
                + " reckoning, having been written using the distinct"
                + " formulaic jargon of the Telberin Magic Guild.";
    string *names = ({
        "appendix",
        "maelstrom",
        "purification",
        "flayance",
        "articulation",
        "phonic repeal",
        "pulsation",
        "decayance",
        "ambiant aura",
        "diliniation",
        "intonation",
        "illumination",
        "divination",
        "corporeal flux",
        "unification",
        "transmogrification",
        "magnification",
        "focus",
        "clairvoyance",
        "crystal formation",
        "ignition",
        "synthesis",
        "phasic induction",
                    });

    if (!strlen(arg))
    {
        notify_fail(CAP(QVB) + " what?\n");
        return 0;
    }
    arg = LOW(arg);

    if (!parse_command(arg, ({}),
        "[about] %p", names))
    {
        if (!parse_command(arg, ({}),
            "[the] [massive] [enchanters] [enchanter's]"
          + " 'book' / 'tome' / 'pages' / 'page'"))
        {
            if (arg == "index")
            {
                if (!Book_Open)
                {
                    write("The massive tome lies shut.\n");
                    return 1;
                }

                write(read_index());
                return 1;
            }

            return 0; /* we don't like the syntax */
        }

        if (!Book_Open)
        {
            write("The massive tome lies shut.\n");
            return 1;
        }

        write("What do you wish to read about? The tome is filled with"
            + " a vast amount of knowledge, and would require a very"
            + " specific selection if you wish to spend anything less"
            + " than months in this room. There seems to be an index"
            + " at the front of the book which might help you in your"
            + " choice.\n");

        return 1;
    }

    if (!Book_Open)
    {
        write("The massive tome lies shut.\n");
        return 1;
    }

    switch(names[0])
    {
        case "appendix":
            MANAGER->assign_suffix(this_player());
            write("The Appendix is quite brief, compared to much of the"
                + " other sections in this book. Most of what you see is"
                + " utterly beyond your comprehension, but there are"
                + " a few passages which catch your eye. One says something"
                + " about how certain alterations can be made to"
                + " standard enchantments and runes. In such cases, the"
                + " command word must include the suffix = '"
                + MANAGER->query_suffix(this_player()) + "' to be"
                + " effective. Another speaks of how command words are"
                + " not simply spoken. To activate or cast an enchantment,"
                + " one must <incant> the command word.\n");
            break;
        case "maelstrom":
            write("You read the chapter titled 'Maelstrom'. Apparently"
                + " it is a spell of great power which allows the caster"
                + " to command elemental forces against an area. "
                + txt + " You read something about the need to stand"
                + " upon a height, and the command word 'Releai'.\n");
            break;
        case "purification":
            write("You read the chapter titled 'Purification'. This"
                + " seems to be an enchantment placed on an area"
                + " to increase the purity of the light or darkness"
                + " within its bounds. " + txt + " There is something"  
                + " about needing to meditate for a time, and then"
                + " the command word 'Haredhi'.\n");
            break;
        case "flayance":
            write("You read the chapter titled 'Flayance'. This spell"
                + " seems to be geared toward channeling large amounts"
                + " of destructive force in a particular direction. "
                + txt + " You read something about a slashing motion"
                + " with the hands, and the command word 'Thelai'.\n");
            break;
        case "articulation":
            write("You read the chapter titled 'Articulation'. Though"
                + " you aren't quite sure, this seems to be some kind"
                + " of an enchantment which one places upon oneself in"
                + " order to increase the clarity of one's 'music'. Just"
                + " what is meant here by music seems unclear, though it"
                + " is obviously some magical format. " + txt
                + " You read something about a tapping motion with the"
                + " back teeth, and the command word 'Tasteiat'.\n");
            break;
        case "phonic repeal":
            write("You read the chapter titled 'Phonic Repeal'. This"
                + " seems to be a spell which is meant to clean up, or"
                + " 'bring back' music or magic which has gone awry. "
                + txt + " You read something about a beckoning gesture,"
                + " and the command word 'Cantreait'.\n");
            break;
        case "pulsation":
            write("You read the chapter titled 'Pulsation'. The nature"
                + " of this spell is mostly lost on you. It appears to"
                + " be a rune of some kind which can be placed upon a"
                + " surface, and used to summon those who can 'listen'"
                + " from afar. " + txt + " You read something about"
                + " subtle patting of the hand on the desired surface,"
                + " and the command word 'Eitet'.\n");
            break;
        case "decayance":
            write("You read the chapter titled 'Decayance'. Apparently,"
                + " this is a spell which can be cast to cause magic or,"
                + " as the tome says, 'resonance', to decay and fall"
                + " in effect. Perhaps it is some kind of dispel magic"
                + " ability, but that is not certain. " + txt
                + " You read something about lowering both hands, and"
                + " the command word 'Rummidh'.\n");
            break;
        case "ambiant aura":
            write("You read the chapter titled 'Ambiant Aura'. This"
                + " is apparently some kind of enchantment which one"
                + " can place upon oneself to increase the amount of"
                + " light one projects into the world. " + txt
                + " You read something about singing softly, and"
                + " the command word 'Lileati'.\n");
            break;
        case "diliniation":
            write("You read the chapter titled 'Dilineation'. It would"
                + " seem that this spell deals with separating the"
                + " pure from the impure 'tones' in 'music'. " + txt
                + " You read something about closing the eyes, and the"
                + " command word 'Fredhaeti'.\n");
            break;
        case "intonation":
            write("You read the chapter titled 'Intonation'. Though it"
                + " is difficult to be sure, this spell seems to deal"
                + " with deepening the 'resonance' of an individual's"
                + " 'music'. " + txt + " You read something about"
                + " a deep-throated hum, and the command word"
                + " 'Uulaesis'.\n");
            break;
        case "illumination":
            write("You read the chapter titled 'Illumination'. It seems"
                + " that this is a rune of some kind which can be placed"
                + " upon a surface which, when triggered, will fill the"
                + " area with additional light. " + txt + " You read"
                + " something about placing one's hands upon the"
                + " desired surface, and the command word 'Livurae'."
                + " To activate a rune which is already in place, one"
                + " must touch the rune, and again incant the"
                + " command word.\n");
            break;
        case "divination":
            write("You read the chapter titled 'Divination'. Apparently,"
                + " this spell can lead one lost in darkness to nearby"
                + " sources of light. " + txt + " You read something"
                + " about placing the fingers on the temples, and"
                + " the command word 'Faedria'.\n");
            break;
        case "corporeal flux":
            MANAGER->assign_password(this_player());
            MANAGER->assign_suffix(this_player());
            write("You read the chapter titled 'Corporeal Flux'. This"
                + " is apparently some sort of rune which, when"
                + " triggered, negates the corporeal balance of the"
                + " catalyst, rendering him momentarily present only"
                + " in spirit form. " + txt + " You read something"
                + " about placing hands on the desired surface, and the"
                + " command word '" + CAP(MANAGER->query_password(TP))
                + "'. To activate a rune which is already in place, one"
                + " must touch the rune, and incant the command word.\n");
            break;
        case "unification":
            MANAGER->assign_spell(this_player());
            write("You read the chapter titled 'Unification'. This"
                + " enchantment seems to somehow bind one object"
                + " to another. Apparently, it is often used upon"
                + " valuables which the owner will bind to either"
                + " themselves, or a location. " + txt + " You read"
                + " something about passing hands over an object,"
                + " and the command word '"
                + CAP(MANAGER->query_spell(TP)) + "'.\n");
            break;
        case "transmogrification":
            write("You read the chapter titled 'Transmogrification'."
                + " Apparently, this spell is capable of changing"
                + " simple materials into other simple materials. "
                + txt + " You read something about praying over the"
                + " materials, and the command word 'Fwildaet'.\n");
            break;
        case "magnification":
            write("You read the chapter titled 'Magnification'. This"
                + " enchantment is apparently to be used for amplifying"
                + " certain characteristics of an object or being. " 
                + txt + " You read something about calling forth the"
                + " 'music' from the target, and the command word"
                + " 'Shureci'.\n");
            break;
        case "focus":
            write("You read the chapter titled 'Focus'. It is rather"
                + " difficult for you to understand much of anything"
                + " about what this spell might accomplish. It is,"
                + " however, spoken of with great importance. "
                + txt + " You read something about joining in the"
                + " 'chorus', and the command word 'Zhigaar'.\n");
            break;
        case "clairvoyance":
            write("You read the chapter titled 'Clairvoyance'. This"
                + " spell purportedly has the ability to grant certain"
                + " casters a vision of future events. " + txt
                + " You read something about deep sleep, and the"
                + " command word 'Revvic'.\n");
            break;
       case "crystal formation":
            write("You read the chapter titled 'Crystal Formation'."
                + " Apparently, certain magical crystals exist which"
                + " are known to be the most radiant source of light"
                + " in Emerald. Enchanting an object with this spell"
                + " causes these crystals to grow upon the surface of"
                + " the enchanted material. " + txt + " You read"
                + " something about arms outstretched, and the command"
                + " word 'Guugarve'.\n");
            break;
        case "ignition":
            write("You read the chapter titled 'Ignition'. Apparently,"
                + " this spell deals with the attack which one places"
                + " on the 'resonance' of their own personal 'music'. "
                + txt + " You read something about deep breath, and"
                + " the command word 'Jhaelod'.\n");
            break;
        case "synthesis":
            write("You read the chapter titled 'Synthesis'. The full"
                + " nature of this enchantment eludes you, though it"
                + " seems to deal with the performance of higher"
                + " quality 'music' through increased 'counterpoint'. "
                + txt + " You read something about finger motion, and"
                + " the command word 'Argelia'.\n");
            break;
        case "phasic induction":
            write("You read the chapter titled 'Phasic Induction'."
                + " This spell seems to trigger some sort of pulsation"
                + " in the ambiant aura of the individual upon which"
                + " it is cast. " + txt + " You read something about"
                + " uplifted hands, and the command word 'Aeleid'.\n");
            break;
        default:
            write("Hmmm ... \n");
            break;
    }

    tell_room(environment(this_object()), QCTNAME(this_player())
      + " reads through a few pages of the massive tome.\n",
        this_player());

    return 1;
} /* read_book */



/*
 * Function name:        read_index
 * Description   :        show the player the index of the tome
 * Returns       :        string - the index description
 */
public string
read_index()
{
        return("\n"
        + "\t     ===============================================\n"
        + "\t -=  Index of Common Enchantments, Runes, and Spells  =-\n"
        + "\t     ===============================================\n\n"
        + "\t            Compiled by, and the property of\n"
        + "\t              The Magic Guild of Telberin\n\n"
        + "\t    For additional information, refer to the Appendix\n\n"
        + "\t- Maelstrom                             - Divination\n"
        + "\t- Purification                          - Corporeal Flux\n"
        + "\t- Flayance                              - Unification\n"
        + "\t- Articulation                          - Transmogrification\n"
        + "\t- Phonic Repeal                         - Magnification\n"
        + "\t- Pulsation                             - Focus\n"
        + "\t- Decayance                             - Clairvoyance\n"
        + "\t- Ambiant Aura                          - Crystal Formation\n"
        + "\t- Diliniation                           - Ignition\n"
        + "\t- Intonation                            - Synthesis\n"
        + "\t- Illumination                          - Phasic Induction\n");
} /* read_index */


/*
 * Function name:        exa_cover
 * Description  :        let the player examine the book's cover
 * Returns      :        string - the description
 */
public string
exa_cover()
{
    string cover_desc = "The book is bound with a thick leather cover,"
      + " tacked into place with metal brackets along its edges. ";

    if (Book_Open)
    {
        cover_desc += "Presently, the cover lies open.";
    }
    else
    {
        cover_desc += "Presently, the cover lies shut.";
    }

    return cover_desc + "\n";
} /* exa_cover */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(read_book, "read");
    add_action(mess_with_book, "open");
    add_action(mess_with_book, "close");
} /* init */
