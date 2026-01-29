// -*-C++-*-
// file name: 	  /d/Avenir/common/bazaar/intr/clubroom.c
// creator(s):	  Gracie&Tep	July 1995
// last update:	  Lilith, Jun 2004: Separated start room from join room.
//                Lilith, March 26 1997
// purpose:       Joinroom for Dancer of Veils club
// note:          added check for appearance map in restoration()
// bug(s):
// to-do:

#include <const.h>
#include "/d/Avenir/common/clubs/dance/dance_club.h"

#pragma save_binary
inherit "/std/room";

/* Prototypes */
static int initiation(string str);
static int expulsion(string str);
static int restoration(string str);

void
create_room()
{
    set_short("A dressing room");
    set_long("There is a large mirror near the beaded curtain "+
        "covering the doorway. "+
    	"Before it stands a table bearing many little pots and vials. "+
        "There are rows of pegs along the walls, all occupied with "+
        "various items of clothing. "+
        "A glass case occupies one corner. "+
        "There is a small sign resting on it.\n");

	
	IN;       // Avenir is an undergound domain.
	IN_IN;    // Interior room, no flux msgs, steeds etc.


    add_exit(BAZAAR + "intr/alcove", "south");

    add_item("sign", "@@read_sign");
    add_cmd_item("sign", "read", "@@read_sign");

    add_item(({"mirror", "large mirror"}), 
        "In it you can see a reflection of the room:\n"+
        "sdants ti erofeB .yawrood dedaeb eht raen rorrim egral a si erehT\n"+ 
        "a si moor eht ssorcA  .slaiv dna stop elttil ynam gniraeb elbat a\n"+ 
        " lla ,sllaw eht gnola sgep era erehT .gnitten ni depard deb egral\n"+
        "  setaroced esac ssalg A .gnihtolc fo smeti suoirav htiw deipucco\n"+
        "                 .ti no gnitser ngis llams a si erehT .renroc eno\n"+
        "\n");
    add_item(({"glass case", "case"}),
	"The glass case is locked. Within it are displayed some valuable "+
	"trinkets with which the dancers adorn themselves.\n");
    add_item(({"trinkets", "valuables", "baubles"}),
	"These baubles are gem-encrusted. They are made of precious metals"+
	" and seem quite valuable.\n");
    add_item(({"pots", "vials", "lids"}), 
	"The little pots and vials are filled with miscellaneous beauty "+
	"potions and scents. Some of the pots have jeweled lids.\n");
    add_item(({"table"}), "It is delicately carved and gilded. There are "+
	"many little shelves and compartments, each containing pots and "+
	"vials.\n");   
    add_item(({"peg", "pegs", "rows"}),
	"Wooden pegs have been hammered into the walls. Though the pegs "+
	"make neat rows, clothing has been hung haphazardly from them, "+
	"making the room feel cluttered.\n");
    add_item(({"clothes", "cloth", "patterns", "embroidery", "clothing"}),
	"Clothing of all sorts and colours dangle from pegs. Some have "+
	"bright patterns, others, metallic embriodery'\n");
    add_item(({"bed", "beds", "netting", "sheets", "blankets",
      "mattresses", "mattress"}),
	"The beds are both lovely and sturdy. The mattresses are stuffed "+
	"with feathers. Silken sheets and wool blankets are piled at the "+
	"foot of each bed. The beds are all draped in fine white netting.\n");

    seteuid(getuid(TO));
}


string
read_sign()
{
  return "The Dance of the Veils is a difficult one to learn, and few  "+
    "women have the beauty and agility to perform it well. If you "+
    "are willing, Qalita or one of her apprentices may test you for "+
    "the Dance. Some applicants are rejected outright, while most "+
    "are simply taught a few of the tricks of the Dance trade.\n\n"+
    "   To join the club of the Dancers of the Veil, type <teach me>\n"+
    "   To leave the club of the Dancers of the Veil, type <unlearn>\n"+
    "   Lost veils may be restored to you through <restore me>\n"+
    "   Members can no longer start here, but may use the room\n "+
    "    reserved for us at the Stormy Haven, up at the port.\n"+
    "\n";
}

void
init()
{
    ::init();
    add_action(initiation, "teach");
    add_action(expulsion, "unlearn");
    add_action(restoration, "restore");
}

static int
initiation(string str)
{
    object veil, anklet;
    mapping m_app;     // stores members' appearances
  
    NF("Teach who?\n");
    if (str != "me") 
        return 0;

    NF("We only train females in this art.\n");
    if (this_player()->query_gender() != G_FEMALE) 
        return 0;

    NF("Here, in Sybarus, we do not believe in 'hobbits'.\n"+
       "You look a bit like dwarf, though, and we do not train "+
       "those for the Dance.\n");
    if (RACE == "hobbit") 
        return 0;

    NF("Your race doesn't have the physical grace for "+
       "the Dance.\n");
    if (RACE == "dwarf" || RACE == "goblin" || RACE == "ogre" || RACE == "orc") 
        return 0;

    if (objectp(veil = present(VEIL, TP))) 
    {
        write ("You are a dancer already!\n");
        return 1;
    }
    
    write("You have been accepted as a Dancer of Veils.\n");
    say(QCTNAME(TP) + " has been accepted as a Dancer of Veils.\n");
    write_file(DANCE_LOG, capitalize(TP->query_real_name())+ 
        " became a Dancer "+ ctime(time()) + ".\n");

    // store people's appearances in order to restore it when they leave.
    // serves as members' list as well.
    m_app = restore_map(APPEARANCE_LOG);
    m_app += ([TP->query_real_name() : TP->query_appearance_offset()]);
    save_map(m_app, APPEARANCE_LOG);
  
    clone_object("/d/Avenir/common/clubs/dance/veil")->move(TP,1);
    write("An apprentice dancer hands you a lovely veil.\n");
  
    anklet = present(ANKLET, TP);
    if (!objectp(anklet)) 
    {
        clone_object("/d/Avenir/common/clubs/dance/anklet")->move(TP,1);
        write("A shy apprentice dancer gifts you with a pair of anklets.\n");
        return 1;
    }
    return 1;
}

static int
expulsion(string str)
{
    object veil, anklet;
    int app;
    mapping m_app;
    string name;
  
    NF("Unlearn what?\n");
    if (str) 
    return 0;

 // does not work for wizards 
    if (!TP->remove_cmdsoul(DANCE_SOUL)) 
    {
        write("It doesn't seem you were a member anyway.\n");
        return 1;
    }
    else 
    {
        write("An apprentice dancer intones: As you wish, so be it!\n");
        veil = present(VEIL, TP);
        if (objectp(veil)) 
        {
            veil->remove_object();
            write("An apprentice dancer takes away your veil and anklets!\n");
            say(QCTNAME(TP) + " is no longer a Dancer of Veils.\n");
            write_file(DANCE_LOG, TP->query_real_name() + " left " +
                "the Dancers on "+ extract(ctime(time()), 4, 15) + "\n");     
        }

        anklet = present(ANKLET, TP);
        if (objectp(anklet))
            anklet->remove_object();

        // Do this just in case something goes wrong with the leave_env
        // in the bells. Want to make sure player m_in is reset.
        if (!TP->query_wiz_level())
            TP->set_m_in("arrives.");
    
        TP->update_hooks();
        // restore their appearance.
        // Bug here: if they have died while being a member and changed their
        // body, restored appearance offset value would be uncorrect.
        // Leaving it here because otherwise we need to access the mapping
        // file frequently, from enter_ and leave_env in veil code.
        m_app = restore_map(APPEARANCE_LOG);
        name = TP->query_real_name();
        app = m_app[name];
        if (app) 
        {
            TP->set_appearance_offset(-app); // doing this to fix past error
            save_map(m_delete(m_app, name), APPEARANCE_LOG);
        }
        else
            TP->set_appearance_offset(0);  // this happens when the stored int is 0.
        return 1;
    }
}


static int
restoration(string str)
{
    object veil, anklet;
    int app;
    mapping m_app;
    string name;

    if (str != "me" ) 
    {
        NF("Restore whom?\n");
        return 0;   
    } 
     
    m_app = restore_map(APPEARANCE_LOG);
    name = TP->query_real_name();
    app = m_app[name];
    if (!app) 
    {
        NF("Only club members may restore themselves here.\n");
        return 0;   
    }

    veil = present(VEIL, TP);
    if (!objectp(veil)) 
    {
        clone_object("/d/Avenir/common/clubs/dance/veil")->move(TP,1);
        write("A dancer hands you a veil.\n");
        say(QCTNAME(TP)+" is given a spare veil by one of the dancers.\n");
    }

    anklet = present(ANKLET, TP);
    if (!objectp(anklet)) 
    {
        clone_object("/d/Avenir/common/clubs/dance/anklet")->move(TP,1);
        write("A dancer gives you a spare pair of anklets.\n");
        say(QCTNAME(TP)+" is given spare anklets by one of the dancers.\n");
    }

    write("You have everything you need now.\n");
    return 1;       
}
