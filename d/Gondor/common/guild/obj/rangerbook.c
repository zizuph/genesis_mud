/*
 * /d/Gondor/common/guild/rangerbook.c
 *
 * Original version by Elessar
 *
 * Modification log:
 *  3-Dec-1996, Olorin: small fixes, mainly cosmetical, some additions to the text
 */
#pragma save_binary
#pragma strict_types

inherit "/std/object.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/guild/lib/ranger_defs.h"

/*
 * Prototypes:
 */
public int     read_chapter(string str);
public int     try_get();

public void
create_object()
{
    set_short("large, brown leatherbound book");
    set_name("book");
    add_name("ranger_book");
    set_long("The large book bound in brown leather looks quite new.\n"+
        "You open to the index page, and read:\n"+
        "  The Tome of the Rangers of Gondor.\n"+
        "  Available chapters:\tWelcome,\n"+  
        "                     \tRules of the Rangers,\n"+
        "                     \tJoining the Rangers,\n"+
        "                     \tLeaving the Rangers,\n"+
        "  More information can be gained in the library.\n");
    add_prop(OBJ_I_NO_GET, try_get);
}

public int
try_get()
{
    write("The book is chained to the altar, you cannot take it!\n");
    say(QCTNAME(TP)+" tries to take the Tome of the Rangers, but it "
	+ "is chained to the altar.\n", TP);
    return 1;
}

public void
init()
{
    ::init();
    add_action(read_chapter, "read");
}

public int
read_chapter(string str)
{
    NFN("Read what?");

    if (!strlen(str)) 
	return 0;

    switch (LOW(str))
    {
    case "book":
	write("You open the book to the index page, and read:\n"+
	  "  The Guildbook of the Rangers of the Westlands.\n"+
	  "  Available chapters:\tWelcome,\n"+
	  "                     \tRules of the Rangers,\n"+
	  "                     \tJoining the Rangers,\n"+
	  "                     \tLeaving the Rangers,\n"+
	  "  More information can be gained in the library.\n");
	say(QCTNAME(TP)+" reads the index page of the large brown book.\n");
	break;
    case "welcome":
	write("\n\t\tWELCOME!\n\n" +
	  "Welcome to the Guild Hall of the Rangers of Gondor!\n\n" +
	break_string(
	  "And congratulations on finding this place! By doing so, " +
	  "you have proven a beginning talent as a pathfinder and " +
	  "scout, in other words some of the talents needed for becoming " +
	  "a Ranger. Be proud of your passing this initial test, but " +
	  "you are not yet ready, your journey to join our " +
	  "ranks has only just begun.\n", 70) +
	break_string(
	  "The Rangers are a part of the fighting forces of the Free " +
	  "Peoples of Middle-earth. Founded by the Dunedain as scouts " +
	  "and guerrillas, the Rangers now accept representatives of " +
	  "all the Free Peoples, to defend Gondor, and to retake " +
	  "Ithilien and Arnor from the minions of the Dark Lord.\n", 70) +
	break_string(
	  "The struggle is tough, for the Enemy's forces are numerous " +
	  "and strong, and at times only the hope of " +
	  "the return of the King keeps our spirit up.\n", 70) +
	break_string(
	  "But the lands are beautiful, and the hope of renewed peace and " +
	  "prosperity is great enough inspiration to keep us going.\n", 70) +
	  "\n" +
	break_string(
	  "To qualify for membership in this guild, you should be a good " +
	  "roleplayer, without ambitions of becoming a powerful hero. " +
	  "You should also be familiar with Master J.R.R. Tolkien's " +
	  "great trilogy, 'The Lord of the Rings', for it is out of " +
	  "that saga the Rangers have been shaped, and it is in the " +
	  "likeness of that saga that these lands have been made.\n", 70) +
	break_string(
	  "You must have high moral standards, and a will to learn " +
	  "and to defend the Free Peoples and fight the Enemy. And you " +
	  "will also, above all, need to learn patience. To join, you " +
	  "need a Mentor to vouch for you, and your next task " +
	  "now is to find one who agrees to do so.\n", 70) +
	break_string(
	  "You must first write a note on the board in the hall south " +
	  "of here, where you state your name, other guild affiliations, " +
	  "and tell the story of your life; why do you want to be a " +
    "Ranger. You must also 'apply to join the Rangers' here in " +
    "this room. And you should also contact a member of the Recruitment " +
    "team and let them know when you usually are available for interviews.\n", 70) +
	break_string(
	  "Hopefully, someone will find you interesting, and will " +
	  "talk to you about the Rangers. But you may also have to " +
	  "be more direct in your approach, by actively seeking out the " +
	  "Rangers, and try to find a sponsor that way. To help you in " +
	  "this, the master ranger Amaron here will have rota of all " +
	  "Mentors and Officers, and can tell you who are free " +
	  "to take in a new pupil. To get these rota, just type " +
	  "\"disclose rota\" while you are in this room.\n", 70) + "\n" +
	break_string(
	  "Still it may take days, weeks, or even months before you " +
	  "find someone who can be your Mentor, especially if you " +
	  "choose the passive approach and spend your time outside Gondor " +
	  "and Middle-earth. The Mentor should take only one pupil at a time, " +
	  "and will remain the instructor until the pupil is deemed worthy " +
	  "to join one of the three Companies. So while waiting, it would " +
	  "be wise to try to learn and adopt the ways of the Rangers.\n", 70) +
	  "\n  Good luck!\n");
	say(QCTNAME(TP)+" reads the welcome-page in the leatherbound book.\n");
	break;
    case "rules":
    case "rules of the rangers":
	write("\nRules for the Rangers of the Westlands.\n\n"+
	"  1.  To serve the Free People by fighting against the Evil One,\n"+
	"      his agents and minions.\n\n"+
	"  2.  To swear fealty and service to Gondor, and to the Lord and\n"+
	"      Steward of the realm.\n\n"+
	"  3.  To keep and defend secrets of Gondor from falling in wrongful\n"+
	"      hands, by protecting Gondor with your life.\n\n"+
 	"  4.  No mage may be a Ranger of Gondor. To have such a profession,\n"+
	"      allowing offensive spells, you will have to leave the guild.\n\n"+
        "  5.  Kender and goblins are not allowed to become Rangers.\n\n"+
	"  6.  Those elves who acknowledge not the authority of the Valar, but\n"+
	"      spite them by having sworn allegiance to a spawn of Ungoliante\n"+
        "      are not permitted to join the ranks of the Rangers of the\n"+
        "      Westlands.\n\n");
	say(QCTNAME(TP)+" reads the rules of the Rangers of the Westlands.\n");
	break;
    case "joining":
    case "join":
    case "joining the rangers":
	write("\nJoining the Rangers of Gondor.\n\n"+
	break_string(
          "As the Rules state, no mage, kender, goblin, or dark elf may "+
          "become a Ranger of Gondor.\n", 70) +
	break_string(
	  "You are hereby advised to read the chapter about leaving the " +
	  "Rangers of Gondor before you join.\n\n", 70) +
    break_string(
        "It is important that you 'apply to join the rangers' here " +
        "in this room, to get registered as an applicant. " +
        "If you do not register, you will not be considered.\n", 70) +
	break_string(
          "After joining, you will be a Ranger pupil, learning the ways " +
          "of Rangers until you are found ready to join a Company.\n", 70) +
	break_string(
	  "If you feel the Rangers of Gondor is the guild for you, you can " +
          "join the Rangers if you can find one to vouch for you first. " +
          "After you have been vouched for, you can sign your name in " +
          "this book, and that Ranger will be your teacher. You will " +
	  "then be given a ring as a physical proof of your membership of " +
	  "the Rangers of the Westlands, and a scroll telling you more about the " +
	  "services and privileges this membership makes available to you.\n", 70) +
          "If you lose your ring you can ask for a new one here.\n");
	say(QCTNAME(TP)+
	  " reads the chapter about joining the Rangers of Gondor.\n");
	break;
    case "leaving":
    case "leave":
    case "leaving the rangers":
	write("\nLeaving the Rangers of the Westlands.\n\n"+
	  "  1.  If you manage to join the Rangers of Gondor, you are \n"+
          "      probably not a kender or a goblin. If, however, you pick\n"+
          "      a new body after being killed, and become a kender or a\n"+
          "      goblin, you will automatically be expelled from the guild.\n"+
	  "  2.  If a Captain of the Rangers finds that you repeatedly broke\n"+
	  "      the rules of the Rangers as laid down in the Charter of the\n"+
	  "      Guild, the Captain can expel you from the guild.\n"+
	  "  3.  If you feel this guild is not the right guild for you, you \n"+
	  "      may leave the guild by erasing your name from this book.\n\n"+
	break_string("All the three items above will remove you " +
		  "from the Guild of the Rangers of the Westlands.\n", 70) + 
	break_string("However, leaving the guild will not be " +
		  "completely for free. You will lose all privileges " +
		  "offered by the Guild, which involves the right " +
		  "to wear a token of your guild membership, and use " +
		  "of the facilities within the headquarters of the Guild.\n", 70));
	break;
    default:
        return 0;
    }
    return 1;
}
