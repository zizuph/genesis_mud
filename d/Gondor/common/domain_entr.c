/*    
      This is the room that presents the domain Gondor to the apprentice
      wizards who wonder what domain to join. This room will be a link
      from Tech's tower to our domain, and it will contain info about
      Gondor, the wizards currently in the domain, and their projects.
*/

#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/std/room";

#include <composite.h>
#include <std.h>

#include "/d/Gondor/defs.h"

public string  query_wiz_pretitle(mixed wiz);
public string  list_domain_members();

void
create_gondor()
{
    set_short("Welcome to the domain Gondor");
    set_long(BSN("You are standing on the top of a mountain, on a "
      + "plateau from which you have a great view over Gondor and Rohan, "
      + "the areas covered by the domain Gondor. Far to the east you "
      + "see the jagged and torn peaks of the mountains that surround "
      + "Mordor, far north you can see the southern peaks of the Misty "
      + "Mountains, and northeast you spot the edges of the great forest "
      + "Mirkwood. West you see the plains of Eriador, and south lies the "
      + "ocean. You have a better view to the areas closer to this mountain "
      + "though, and what dominates the view are the grassy fields of "
      + "Rohan to the north, and the great river Anduin that runs through "
      + "the lands of Gondor to the east.")
      + "This is the domain Gondor, in which the following people are "
      + "members:\n"
      + break_string(list_domain_members() + ".\n", 60, "\t")
      + BSN("If you would like to know more about what these people are "
      + "creating, you may type 'project <name-of-wiz>'. If you want to "
      + "know what needs to be done in the domain, type 'needed'. If you "
      + "think that you are the right person to join the domain Gondor, "
      + "type 'apply Gondor', and your application will be noted.")
      + "\tThank you for your visit.\n");
    add_exit("/d/Genesis/wiz/dom_a2","north");
    add_exit("/d/Gondor/workroom","south");
}

public string
list_domain_members()
{
    int     i, s;
    string *members = SECURITY->query_domain_members(getuid());

    for (i = 0, s = sizeof(members); i < s; i++)
	members[i] = query_wiz_pretitle(members[i]) + " " +
	    CAP(members[i]);

    return COMPOSITE_WORDS(members);
}

int
project(string str)
{
    string  file,
	    msg = "\n",
	    title,
	    domain;

    if (!strlen(str))
        return 0;
    str == lower_case(str);

    if (!SECURITY->exist_player(str))
	msg += CAP(str) + " has left Genesis.\n\n" 
	    + "While in Gondor, " + CAP(str) + " worked on this project:\n\n";
    else
    {
	title = query_wiz_pretitle(str);
	if (!strlen(title))
	    msg += CAP(str) + " has returned to the ranks of the mortals.\n\n"
		+ "While in Gondor, " + CAP(str) + " worked on this project:\n\n";
	else if ((domain = SECURITY->query_wiz_dom(str)) != getuid())
	{
	    if (strlen(domain))
		msg += title + " " + CAP(str) + " has joined the domain " + domain + ".\n\n"
		    + "While in Gondor, " + CAP(str) + " worked on this project:\n\n";
	    else
		msg += title + " " + CAP(str) + " has retired.\n\n"
		    + "While in Gondor, " + CAP(str) + " worked on this project:\n\n";
	}
	else if (SECURITY->query_domain_lord(getuid()) == str)
	    msg += title + " " + CAP(str) + " is the Liege of Gondor.\n";
	else if (SECURITY->query_domain_steward(getuid()) == str)
	    msg += title + " " + CAP(str) + " is the Steward of Gondor.\n";
	else
	    msg += title + " " + CAP(str) + " is a wizard of Gondor.\n";
    }

    if (file_size(file = PROJECT_DIR + CAP(str) + ".prj") > 0)
	msg += read_file(file);
    else
    {
	switch (str)
	{
	case "elessar":
	case "honourable elessar":
	    msg += ("Lord Elessar is the Lord of the domain Gondor.\n"
	      + BSN("He is responsible for the work of the members of "
		    + "the domain, as well as building the city Minas Tirith, "
		    + "capital of Gondor. Lord Elessar is also the Chieftain "
		    + "of the Rangers of the Westlands."));
	    break;
	case "hamurabbi":
	case "sir hamurabbi":
	    msg += (BSN("Sir Hamurabbi was the wizard responsible for the "
		  + "building of Edoras, the capital of Rohan, as well as "
		  + "the general outlay of Rohan."));
	    break;
        case "gus":
        case "sir gus":
            msg += (BSN("Sir Gus coded the road from Edoras to Firienwood."));
            break;
        case "xyzzy":
        case "sir xyzzy":
            msg += (BSN("Sir Xyzzy's project consisted of Isengard and the "
              + "castle Orthanc."));
            break;
        case "costa":
        case "sir costa":
            msg += (BSN("Sir Costa was creating the ruined city of "
              + "Osgiliath."));
            break;
        case "zephram":
        case "sir zephram":
            msg += (BSN("Sir Zephram's project was to make Dunland, west "
		      + "of the Misty Mountains."));
            break;
        case "sithas":
        case "sir sithas":
            msg += (BSN("Sir Sithas' project consisted of the Shades quarter "
              + "in Minas Tirith, the sewers of Minas Tirith, and the "
              + "Shades Occupational Guild."));
            break;
        case "cinder":
        case "dame cinder":
            msg += (BSN("Dame Cinder is working on Pelargir upon Anduin."));
            break;
        case "olorin":
        case "honourable olorin":
            msg += (BSN("Honourable Olorin is the guildmaster of the Society "
              + "of Morgul Mages. His other projects include work on the "
              + "\"Return of the King\" Quest and preparing the domain "
              + "for work on the Ring Quest."));
            break;
        case "soermo":
        case "sir soermo":
            msg += (BSN("Sir Soermo was madwand of Gondor and the first "
              + "wizard working on the Society of Morgul Mages."));
            break;
        case "tumeric":
        case "sir tumeric":
            msg += (BSN("Sir Tumeric was working on the Morgul Mages."));
            break;
        case "mercade":
        case "proctor mercade":
            msg += (BSN("Proctor Mercade is working on Shelob's Lair and "
              + "Cirith Ungol when he needs to relax from his duties as "
              + "Arch of Balance and mudlib arch."));
            break;
        case "arren":
        case "sir arren":
            msg += (BSN("Sir Arren has created the Hornburg and Fornost. "
              + "Now he is working on a quest in Minas Tirith."));
            break;
        case "elanor":
        case "dame elanor":
            msg += (BSN("Dame Elanor was working on horses, riding, and "
              + "combat on horse back."));
            break;
        case "dunstable":
        case "sir dunstable":
            msg += (BSN("Sir Dunstable was coding Pelargir, the sea-port "
              + "of Gondor, and its corsair infested surroundings, "
              + "and assisting Elessar as guildmaster of the Rangers. "
              + "Now he has left for a greater task: Lord of the Shire!"));
            break;
        case "ride":
        case "sir ride":
            msg += (BSN("Sir Ride was specializing in coding NPC's, for "
              + "for several places in Gondor: The Elves or Lorien are "
              + "his, for example."));
            break;
        case "ghalinn":
        case "sir ghalinn":
            msg += (BSN("Sir Ghalinn was working on the Mouths of the Entwash."));
            break;
        case "leholas":
        case "sir leholas":
            msg += (BSN("Sir Leholas was working on the Riders of Rohan and "
              + "on Edoras, capital of Rohan."));
            break;
        case "justus":
        case "sir justus":
            msg += (BSN("Sir Justus created the grasshoppers and the half "
              + "orcs in Anorien."));
            break;
        case "randor":
        case "sir randor":
            msg += (BSN("Sir Randor created a part of the Eagle Quest in the "
              + "White Mountains."));
            break;
        case "tan":
        case "sir tan":
            msg += (BSN("Sir Tan was with us only for a short time."));
            break;
        case "fingolfin":
        case "sir fingolfin":
            msg += (BSN("Sir Fingolfin was with us only for a short time."));
            break;
        case "trout":
        case "sir trout":
            msg += (BSN("Sir Trout was madwand of Gondor for a short time."));
            break;
        case "elistar":
        case "sir elistar":
            msg += (BSN("Sir Elistar was madwand of Gondor for a short time."));
            break;
        case "gorboth":
        case "sir gorboth":
            msg += (BSN("Sir Gorboth is currently coding a small village in Anorien, "
              + "as well as the beacon hill of Amon Din."));
            break;
        case "thowlimer":
        case "sir thowlimer":
            msg += (BSN("Sir Thowlimer is working on Isengard and Orthanc."));
            break;
        case "boromir":
        case "sir boromir":
            msg += (BSN("Sir Boromir is working on Thornlin, a village "
              + "in Lossarnach."));
            break;
	case "boron":
	case "sir boron":
	    msg += (BSN("Sir Boron was working on a layman fighter "
		+  "guild called the Ohtari Carneo Heni, situated "
	        +  "in the Morgul vale."));
	    break;
        case "denbarra":
        case "sir denbarra":
            msg += (BSN("Sir Denbarra is working on a quest in Minas Tirith."));
            break;
        case "quetzl":
        case "honourable quetzl":
            msg += (BSN("Honourable Quetzl is working on the Riders of Rohan, "
              + "a guild situated in Edoras."));
            break;
        case "ladindell":
        case "sir ladindell":
            msg += (BSN("Sir Ladindell is working on improving and extending "
              + "Edoras, the capital of Rohan."));
            break;
        case "kanga":
        case "dame kanga":
            msg += (BSN("Dame Kanga is working on Lothlorien."));
            break;
	case "akeisha":
	case "dame akeisha":
	    msg += (BSN("Akeisha was guildmaster of the Society of "
			+ "Morgul Mages."));
	    break;
	case "radagast":
	case "sir radagast":
	    msg += BSN("Radagast was working on Druadan Forest.");
	    break;
	case "mali":
	case "sir mali":
	    msg += BSN("Mali left before finishing his apprenticeship "
	        + "project, which consisted of creating Aldburg in "
		+ "Eastfold of Rohan.");
	    break;
        default:
            NF("That person is not and has not been a member of the domain Gondor.\n");
	    return 0;
            break;
	}
    }
    write(msg);
    return 1;
}

int
needed()
{
    write(
    BSN("The domain Gondor is based on the books \"Lord of the Rings\" "
      + "by J.R.R. Tolkien. If you have read those books and enjoyed "
      + "them, Gondor is the perfect domain for you!") +
    BSN("If you are not a Tolkien afficionado or if you never even "
      + "heard about Tolkien and his works, do not despair! Gondor has "
      + "large areas that Tolkien never managed to describe, like large "
      + "parts of Mordor, the Black Land, home of orcs and other evil "
      + "creatures, wide areas south of the White Mountains and west "
      + "of the Gap of Rohan, where you can let your imagination run "
      + "wild!") +
    BSN("The domain Gondor consists of the kingdoms of Rohan and "
      + "Gondor. Presently, there are three major cities: Minas Tirith, "
      + "capital of Gondor, Edoras, capital of Rohan, and Minas Morgul, "
      + "the chief city of the evil ringwraiths. The domain has three "
      + "guilds open to mortals: the Rangers of the Westlands, the "
      + "Society of Morgul Mages, and the Rockfriends. Work on more "
      + "guilds is under progress: the Dunedain, a human race guild; "
      + "the Riders of Rohan, a fighter guild; and the Shades, a thief "
      + "guild.") +
    BSN("Work in the domain is concentrating on filling the gaps between "
      + "existing areas and on large, domain-wide quests, like the "
      + "\"Return of the King\" and the Ring Quest."));
    return 1;
}

int
former(string str)
{
    if (str != "wizards")
        return 0;

    write("Former members of the domain Gondor:\n"
        + break_string(
          "Sir Hamurabbi"
        + ", Sir Gus"
        + ", Sir Ghalinn"
        + ", Sir Xyzzy"
        + ", Sir Soermo (Madwand)"
        + ", Sir Costa"
        + ", Sir Zephram"
        + ", Sir Justus"
//      + ", Sir Olorin"
        + ", Sir Randor"
	+ ", Sir Arren"
	+ ", Sir Mercade"
        + ", Sir Sithas"
        + ", Dame Elanor (Madwand)"
        + ", Sir Dunstable"
        + ", Sir Tumeric"
        + ", Sir Ride"
        + ", Dame Cinder"
        + ", Sir Leholas"
        + ", Sir Tan (Madwand)"
        + ", Sir Fingolfin"
        + ", Sir Trout (Madwand)"
//      + ", Sir Gorboth (Madwand)"
        + ", Sir Thowlimer"
        + ", Sir Elistar (Madwand)"
        + ", Sir Boromir, Sir Boron"
        + ", Sir Denbarra"
        + ", Honourable Quetzl"
        + ", Sir Ladindell"
        + ", Dame Kanga"
	+ ", Sir Ride (trainee)"
	+ ", Dame Akeisha"
	+ ", Sir Radagast (trainee)"
	+ ", Sir Mali (trainee)"
        + ".\n", 60, "\t"));

    return 1;
}

void
init()
{
    add_action(project, "project");
    add_action(needed,  "needed");
    add_action(former,  "former");
    ::init();
}

/*
 * Function name: query_wiz_pretitle
 * Description  : Gives a pretitle for a specific wizard type.
 *                Had to recode this here, since in SECURITY, it needs
 *                a player object. Duh! 
 * Arguments    : mixed wiz - the wizard object or name.
 * Returns      : string - the pretitle for the wizard.
 */
public string
query_wiz_pretitle(mixed wiz)
{
    int     gender,
	    finger;
    object  wiz_obj;

    if (stringp(wiz))
    {
	wiz_obj = find_player(wiz);
	if (!objectp(wiz_obj) && SECURITY->exist_player(wiz))
	{
	    finger = 1;
	    wiz_obj = SECURITY->finger_player(wiz);
	}
    }
    else if (objectp(wiz))
    {
	wiz_obj = wiz;
	wiz = wiz_obj->query_real_name();
    }
    else
	return "";

    if (!objectp(wiz_obj))
	return "";

    if (finger)
    {
	gender = member_array(wiz_obj->query_gender_string(), 
			  ({ "male", "female", "neuter", }));
	wiz_obj->remove_object();
    }
    else
	gender = wiz_obj->query_gender();

    switch (SECURITY->query_wiz_rank(wiz))
    {
    case WIZ_APPRENTICE:
        return ({ "Squire", "Maid", "Some" })[gender];

    case WIZ_PILGRIM:
        return ({ "Brother", "Sister", "Brother" })[gender];

    case WIZ_RETIRED:
        return ({ "Mister", "Miss", "Some" })[gender];

    case WIZ_NORMAL:
        return ({ "Sir", "Dame", "It" })[gender];

    case WIZ_MAGE:
        return "Honourable";

    case WIZ_STEWARD:
        return "Warden";

    case WIZ_LORD:
        return ({ "Lord", "Lady", "Lord" })[gender];

    case WIZ_ARCH:
        return "Proctor";

    case WIZ_KEEPER:
        return "Master";
    }

    /* Should never end up here. */
    return "";
}

