/*
 * Private Chapel of the Elemental Temple of Calia
 * 
 * Created by Petros, April 2010
 *
 * Added Elemental Cleric routines - Jaacar, April 2017
 * Modified to properly execute dicharge/expel as well as permit
 * elders to access some commands as requested by council - Mirandus,2020
 */

#pragma strict_types

#include "defs.h"
#include <stdproperties.h>
#include <cmdparse.h>
#include <macros.h>
#include <composite.h>
#include <wa_types.h>

inherit TEMPLE_ROOM_BASE;

#include "/d/Genesis/specials/debugger/debugger_tell.h"

// Defines
#define INCENSE_BEAT              30.0
#define INCENSE_CLOUD             "_incense_cloud"
#define INCENSE_QTY               "_incense_qty"
#define CEREMONIAL_ROBE           "_ceremonial_robe"
#define CEREMONIAL_GARB           "_ceremonial_garb"
#define ANOINTED_OBJECT           "_anointed_object"
#define CEREMONIAL_LAYOBJ         "_ceremonial_layobj"
#define CEREMONIAL_LAYOBJ_FNPROP  "_ceremonial_layobj_fname_prop"
#define CEREMONIAL_LAYOBJ_SPROP   "_ceremonial_layobj_second_prop"
#define CLERIC_BOARDROOM          (ELEMENTALIST_TEMPLE + "ec_boardroom")

#define IncenseStreaming (({                                               \
  "Incense streams from the censor filling the room with its aroma",       \
  "Incense continues to stream from the censor thickening the cloud",      \
  "Incense boils from the censor dancing in the rays of sunlight",         \
  "Incense rises from the censor saturating you with its sweet smell",     \
  "Incense continues to issue forth from the vents of the censor",         \
  "Incense spouts from the censor in balls of aromatic smoke",             \
  "Incense gushes from the censor in rivulets of smoke",                   \
  "Incense continues to boil from the censor in elegant patterns of smoke",\
  "Incense pours from the censor perfuming all it touches",                \
  "Incense streams from the censor mystifying the chapel"}))
 
#define IncenseRising (({                                                  \
  "Incense rises gracefully from the censor in thinning wisps",           \
  "The cloud begins to thin as the incense burns low",                     \
  "Wisps of incense rise from the vents of the censor",                   \
  "Incense wisps gracefully from the silver censor",                      \
  "Incense rises slowly from the dying embers of its ash",                \
  "Thinning plumes of incense rise solemnly from the censor",              \
  "Incense smokes lightly from the silver censor"}))

#define DEATH_OBJECT (ELEMENTALIST_OBJS + "elemental_punishment")

#define JOINED(x) ({"The voice of Lord Pyros echoes in your mind: "+x->query_name()+" has joined the Elemental Clerics.\n",\
        "Lady Gu's voice rings forth in your head: "+x->query_name()+" is the newest member of the Elemental Clerics.\n",\
        "Echoing through your mind you hear Lord Diabrecho say: "+x->query_name()+" has just joined the Elemental Clerics.\n",\
        "Like a small breeze in your ears you hear Lady Aeria say: "+x->query_name()+" has joined the Elemental Clerics.\n",\
        "Resonating in your mind you hear Psuchae say: "+x->query_name()+" has joined the Elemental Clerics.\n"})

#define LEFT(x) ({"You hear the thunderous voice of Lord Pyros proclaim: "+x->query_name()+" has betrayed us and has been banished from the Circle!\n",\
        "Winds howl in the voice of Lady Aeria: "+x->query_name()+" has betrayed the Circle and is no longer one of us!\n",\
        "The ground shakes violently below you momentarily as Lady Gu speaks: "+x->query_name()+" has betrayed the Elementals and is no longer one of the Circle!\n",\
        "You hear the angry voice of Lord Diabrecho: "+x->query_name()+" has betrayed the Circle and is no longer with us!\n",\
        "Resonating in your mind you hear Psuchae say: "+x->query_name()+" has betrayed the Circle and is no longer with us!\n"})
  
// Prototypes
public void betray1(object player);
int incensing = 0;
int penta = 0;
int ceremony = 0;
string cer_name = 0;

string
my_time()
{
    return (ctime(time())[4..9] + ": ");
}

public void
create_temple_room()
{
    set_short("In a private chapel");
    set_long("@@desc_long_description");
   
    try_item( ({ "chapel" }),
        "You are standing in the chapel, a place of worship and ceremonies.\n");
    
    try_item( ({ "altar", "marble altar", "polished altar",
        "polished marble altar" }),                   
        "The altar is made of white marble from the quarries of Argos, the "
      + "same material that is used in the marble columns.\n");
    
    try_item( ({ "copper brazier", "brazier", "tripod", "slendar tripod" }),  
        "The brazier, censor, and tripod are all implements used in the "
      + "rituals and ceremonies performed here at the temple.\n");
      
    add_item(({"censor","silver censor"}),"@@exa_censor");
    add_item(({"pentagram","glowing pentragram"}),"@@exa_pentagram");
    
    try_item( ({ "mats", "prayer mats", "mat", "prayer mat" }),
        "It looks like you can <kneel> before the altar on one of the "
      + "prayer mats surrounding the altar if you wish to pray to the "
      + "Elementals of Calia.\n");
    
    add_exit(ELEMENTALIST_TEMPLE + "middle10", "west", "@@cannot_enter_middle_circle", 1, "@@cannot_see_middle_circle");
    add_exit(ELEMENTALIST_TEMPLE + "middle11", "east", "@@cannot_enter_middle_circle", 1, "@@cannot_see_middle_circle");
    add_exit(ELEMENTALIST_TEMPLE + "statue", "north", "@@cannot_enter_inner_circle", 1, "@@cannot_see_inner_circle");
    add_exit(ELEMENTALIST_TEMPLE + "greathall", "south"); 
}

public string 
exa_censor() 
{
    string desc = "It is a silver censor, a bowl with a vented lid, used "+
        "to burn incense during ceremonies. ";
    object incense=present(INCENSE_CLOUD,TO);
   
    if ((incense)||(incensing))
        desc=desc+"A sweet aroma pervades the air as incense "+
            "streams from the censor filling the sanctuary.\n";
    else
        desc=desc+"\n";
   
    return desc;
}

public string
exa_pentagram()
{
    string desc = "You find no pentagram.\n";
    
    if (penta)
        desc = "There is a glowing pentagram cast upon the floor, large "+
            "enough to stand in the centre section.\n";
    
    return desc;
}
        
public void
init()
{
    ::init();
    add_action("do_kneel", "kneel");
    add_action("do_rise", "rise");
    add_action("do_anoint", "anoint");
    add_action("do_load", "load");
    add_action("do_lay", "lay");
    add_action("do_cast", "cast");
    add_action("do_erase", "erase");
    add_action("do_face", "face");
    add_action("do_stand", "stand");
    add_action("do_pray", "pray");
    add_action("do_turn", "turn");
    add_action("do_betray", "betray");
    add_action("do_promote", "promote");
    add_action("set_ceremony", "ceremony");
}

int
set_ceremony(string str)
{
    str = lower_case(str);
    
    // Player must be a member to perform rite
    if (!(IS_MEMBER(TP))) 
        return 0;
    
    // Player must be properly dressed to perform rite 
    if (!((TP->query_armour(A_ROBE))->id(CEREMONIAL_ROBE))) 
    {
        write("You are not suitably vested to do that.\n");
        return 1;
    }
         
    if (!str)
    {
        if (ceremony)
        {
            write("The current Ceremony is "+cer_name+".\n");
            return 1;
        }
        
        write("What Ceremony are you setting? Valid choices are:\n"+
            "Gennisi, Enarxi, Anavasi, Kyverno, Provoli, End\n");
        return 1;
    }
    
    // Check to see if a ceremony is already taking place
    if (ceremony)
    {
        // If there is one and they weren't asking it to 'end', let them know
        if(str != "end")
        {
            switch(ceremony)
            {
                case 1:
                    cer_name = "Gennisi";
                    break;
                case 2:
                    cer_name = "Enarxi";
                    break;
                case 3:
                    cer_name = "Anavasi";
                    break;
                case 4:
                    cer_name = "Kyverno";
                    break;
                case 5:
                    cer_name = "Provoli";
                    break;
            }
            write("There is already a "+cer_name+" happening. If you "+
                "do not wish that Ceremony to take place, use the "+
                "'ceremony end' command.\n");
            return 1;
        }
        
        // They are asking for the ceremony to end
        ceremony = 0;
        write("You have ended the "+cer_name+" Ceremony.\n");
        return 1;
    }
    
    // They are setting a ceremony to start
    switch(str)
    {
        case "gennisi":
            ceremony = 1;
            cer_name = "Gennisi";
            break;
        case "enarxi":
            ceremony = 2;
            cer_name = "Enarxi";
            break;
        case "anavasi":
            ceremony = 3;
            cer_name = "Anavasi";
            break;
        case "kyverno":
            ceremony = 4;
            cer_name = "Kyverno";
            break;
        case "provoli":
            ceremony = 5;
            cer_name = "Provoli";
            break;
        case "end":
            write("There is currently no Ceremony taking place.\n");
            return 1;
            break;
        default:
            write("What Ceremony are you setting?\nValid choices are:\n"+
                "Gennisi, Enarxi, Anavasi, Kyverno, Provoli, End\n");
            return 1;
            break;
        }
                   
        write("You have set the Ceremony to "+cer_name+".\n");
        return 1;
}

int 
do_promote(string Parms) 
{
    object ITP;
    int    i;
    string TPName=(TP->query_name());
    string *Parm,IName,FirstName,Title;
    string log_message;
 
    // Player must be a member to perform rite
    if (!(IS_MEMBER(TP))) 
        return 0;
 
    // Player must be properly dressed to perform rite 
    if (!((TP->query_armour(A_ROBE))->id(CEREMONIAL_ROBE))) 
    {
        write("You are not suitably vested to do that.\n");
        return 1;
    }

    // Player must be an elder to do a promotion ceremony
    if (!(GUILD_MANAGER->query_is_elder_cleric(lower_case(TPName))))
    {
        write("You must be an Elder Cleric to do promotions.\n");
        return 1;
    }
    
    // Must pass parameter with name with title 
    if (!Parms)
    {
        write("Promote whom?\n");
        return 1;
    }
    
    if (Parms) 
    {
        Parm=explode(Parms," ");
        IName=Parm[0];
        
        if ((sizeof(Parm))<2) 
        {
            write("You must give a rank or title. Try 'promote "+
                IName+" <rank>'.\n");
            return 1;
        }
        
        Title="";
      
        for (i=1; i<(sizeof(Parm)-1); i++) 
            Title=Title+Parm[i]+" ";
        Title=Title+Parm[(sizeof(Parm)-1)];
    }
   
    IName=capitalize(IName);
 
    // Member must be present in room
    ITP=find_player(lower_case(IName));
    if (!((ITP) && (present(ITP,TO))))  
    {
        write("But "+IName+" is not here!\n");
        return 1;
    }
     
    // Inductee must be in the guild
    
    if (!IS_MEMBER(ITP)) 
    {
        write("This one is not a member of the Circle.\n");
        return 1;
    }
       
    Title = capitalize(Title);      
    
    if (GUILD_MANAGER->query_is_ec_council(TP->query_real_name()))
    {
        switch (Title)
        {
            case "Luminary":
                (GUILD_MANAGER->set_ec_luminary(ITP->query_real_name()));
                break;
            case "Illuminati":
                (GUILD_MANAGER->set_ec_illuminati(ITP->query_real_name()));
                break;
            case "Emissary":
                (GUILD_MANAGER->set_ec_emissary(ITP->query_real_name()));
                break;
            case "Cultivator":
                (GUILD_MANAGER->set_ec_cultivator(ITP->query_real_name()));
                break;
            case "Liberator":
                (GUILD_MANAGER->set_ec_liberator(ITP->query_real_name()));
                break;
            case "Conservator":
                (GUILD_MANAGER->set_ec_conservator(ITP->query_real_name()));
                break;               
            case "Harbinger":
                (GUILD_MANAGER->set_ec_council(ITP->query_real_name(),1));
                log_message = capitalize(ITP->query_real_name())
                    + " has been added to the Elemental Clerics Council "
                    + "by " + capitalize(TP->query_real_name()) + ".\n";
                send_debug_message("cleric", log_message);
                COUNCIL_LOG_BOOK->update_log_book(my_time() + log_message);
                break;
            case "Archa":
                (GUILD_MANAGER->set_ec_archon_apotheosis(ITP->query_real_name()));
                break;
            case "Archr":
                (GUILD_MANAGER->set_ec_archon_revelation(ITP->query_real_name()));
                break;
            case "Archd":
                (GUILD_MANAGER->set_ec_archon_deliverance(ITP->query_real_name()));
                break;
            case "Focus":
                (GUILD_MANAGER->set_ec_focus(ITP->query_real_name(),
                    TP->query_real_name()));
                break;
            case "Master":
                (GUILD_MANAGER->set_master_cleric(ITP->query_real_name(),1));
                log_message = capitalize(ITP->query_real_name())
                    + " has been promoted to the Master Cleric "
                    + "by " + capitalize(TP->query_real_name()) + ".\n";
                send_debug_message("cleric", log_message);
                COUNCIL_LOG_BOOK->update_log_book(my_time() + log_message);
                TP->catch_msg("You promote "+(ITP->query_The_name(TP))+ " to the "+
			        "rank of "+Title+" Cleric.\n");
			    ITP->catch_msg((TP->query_The_name(ITP))+ " promotes you to the rank of "+
			        Title+" Cleric.\n");
			    tell_room(TO,QCTNAME(TP)+" promotes "+QTNAME(ITP)+" to the rank of "+
			        Title+" Cleric.\n",({ITP,TP}));
			    return 1;
                break;
            case "Fmaster":
                (GUILD_MANAGER->set_full_master(ITP->query_real_name(),1));
                (GUILD_MANAGER->set_master_cleric(ITP->query_real_name(),1));
                log_message = capitalize(ITP->query_real_name())
                    + " has been promoted to the Full Master Cleric "
                    + "by " + capitalize(TP->query_real_name()) + ".\n";
                send_debug_message("cleric", log_message);
                COUNCIL_LOG_BOOK->update_log_book(my_time() + log_message);
                TP->catch_msg("You promote "+(ITP->query_The_name(TP))+ " to the "+
			        "rank of Full Master Cleric.\n");
			    ITP->catch_msg((TP->query_The_name(ITP))+ " promotes you to the rank of "+
			        "Full Master Cleric.\n");
			    tell_room(TO,QCTNAME(TP)+" promotes "+QTNAME(ITP)+" to the rank of "+
			        "Full Master Cleric.\n",({ITP,TP}));
			    return 1;
                break;
            case "Elder":
                (GUILD_MANAGER->set_elder_cleric(ITP->query_real_name(),1));
                (GUILD_MANAGER->set_full_master(ITP->query_real_name(),1));
                (GUILD_MANAGER->set_master_cleric(ITP->query_real_name(),1));
                log_message = capitalize(ITP->query_real_name())
                    + " has been promoted to the Elder Cleric "
                    + "by " + capitalize(TP->query_real_name()) + ".\n";
                send_debug_message("cleric", log_message);
                COUNCIL_LOG_BOOK->update_log_book(my_time() + log_message);
                TP->catch_msg("You promote "+(ITP->query_The_name(TP))+ " to the "+
			        "rank of "+Title+" Cleric.\n");
			    ITP->catch_msg((TP->query_The_name(ITP))+ " promotes you to the rank of "+
			        Title+" Cleric.\n");
			    tell_room(TO,QCTNAME(TP)+" promotes "+QTNAME(ITP)+" to the rank of "+
			        Title+" Cleric.\n",({ITP,TP}));
			    return 1;
                break;      
            default:
                write("The title "+Title+" is not an official title, therefore "+
                    "no official promotion has been done. Official titles are:\n"+
                    "Luminary, Illuminati, Emissary, Cultivator, Liberator, "+
                    "Conservator, Harbinger, Archa, Archd, Archr, Focus, "+
                    "Master, Fmaster, Elder.\n");
                break;
        }
    }
    
    TP->catch_msg("You induct "+(ITP->query_The_name(TP))+ " as the "+
        "new "+Title+".\n");
    ITP->catch_msg((TP->query_The_name(ITP))+ " inducts you as the new "+
        Title+".\n");
    tell_room(TO,QCTNAME(TP)+" inducts "+QTNAME(ITP)+" as the new "+
        Title+".\n",({ITP,TP}));
    return 1;
}

/*
 * Function:    betray
 * Description: Betray the Elementals and leave the guild
 */
public int
do_betray(string str)
{
    setuid();
    seteuid(getuid());
    if (!IS_CLERIC(this_player()))
    {
        notify_fail("What?\n");
        return 0;
    }

    if (!strlen(str) || !parse_command(lower_case(str), this_player(), " [the] 'elementals' "))
    {
        notify_fail("Betray who? The Elementals\n");
        return 0;
    }

    str = lower_case(str);    
    clone_object("/std/paralyze")->move(this_player(), 1);
    present("_elemental_guild_wand", this_player())->remove_object();
    present("_elemental_guild_dagger", this_player())->remove_object();
    present("_elemental_guild_chalice", this_player())->remove_object();
    present("_elemental_guild_pentacle", this_player())->remove_object();
    present("_elemental_guild_mandala", this_player())->remove_object();
    present("_echosen_", this_player())->remove_object();
    
    GUILD_MANAGER->set_guild_betrayed(this_player(), 1);
    GUILD_MANAGER->leave_occ_guild(this_player());
    if (this_player()->is_elemental_racial_cleric())
    	GUILD_MANAGER->leave_race_guild(this_player());
    
    object board = present("board", CLERIC_BOARDROOM->get_this_object());
    if (objectp(board)) 
    { 
        board->create_note("Betrayal!", 
                 "Sehis", capitalize(TP->query_real_name()) + 
                 " has betrayed the Elementals and is no longer welcome in "+
                 "this Temple!\n\nSehis\n"); 
    }
    
    send_debug_message("cleric", capitalize(this_player()->query_real_name())
                       + " has betrayed the Elementals.", EVENTS_LOG);
    COUNCIL_LOG_BOOK->update_log_book(
        my_time() + capitalize(this_player()->query_real_name()) 
        + " has betrayed the Elementals.\n");
    write("The air around feels like it is closing in on you. Your "+
        "skin begins to feel very warm. Your blood temperature seems "+
        "to be rising very rapidly. You notice the area around you "+
        "begins to get darker. The ground beneath your feet rumbles "+
        "and shakes. Suddenly you find yourself surrounded by four "+
        "powerful beings, one made of earth, one of air, one of water, "+
        "and one of fire. Each seems to be invoking some terrible "+
        "spell. All goes dark.\nYou still feel the ground trembling.\n");
    tell_room(environment(this_player()),
              QCTNAME(this_player())+" prays at the altar.\nSuddenly, the air "+
              "around "+this_player()->query_objective()+" grows very dark, the ground "+
              "beneath "+this_player()->query_possessive()+" feet begins to shake violently. "+
              capitalize(this_player()->query_possessive())+" eyes glaze over.\n", this_player());
    set_alarm(2.0, 0.0, &betray1(this_player()));
    return 1;
}

public void
betray1(object player)
{
    setuid();
    seteuid(getuid());

    tell_object(player, "Your blood begins to boil under your skin.\n"+
                "You hear a demonic laughter filling the air around you.\n");
                              
    tell_room(environment(player), capitalize(player->query_pronoun()) +
              " is surrounded totally by "+
              "darkness.\nThe ground shakes massively.\n", player);
    tell_object(player,"A voice echoes in your mind: You have betrayed us and "+
            "shall now pay the ultimate price!\n"+
            "The last thing you feel is your arms and legs literally exploding "+
            "from the pressure of your boiling blood.\n");
          
	tell_room(environment(player),"Suddenly, all is back "+
          "to normal, except where " + QTNAME(player) + " was standing is now a "+
          "smouldering pile of remains.\n", player);
	if (!player->query_prop(LIVE_I_NO_CORPSE))
	{
    	player->add_prop(LIVE_I_NO_CORPSE, 1);
	}
	string enemy_race = player->query_race_name();
	player->heal_hp(-player->query_max_hp());
  	player->do_die(this_object());
    object piece = clone_object(DEATH_OBJECT);
    piece->set_race(enemy_race);
    piece->move(this_object(), 1);

    object * listeners = GUILD_MANAGER->query_awake_clerics() + GUILD_MANAGER->query_awake_worshippers();
    listeners->catch_tell(LEFT(player)[random(4)]);
}

public void
set_pentagram(int i)
{
    penta = i;
}

public int
query_pentagram()
{
    return penta;
}

/*
 * Function name: do_kneel
 * Description  : Allows the player to kneel before the altar
 * Arguments    : arg - should be empty
 * Returns      : int 1/0 - success/failure.
 */
public int
do_kneel(string arg)
{
    // We need to add this function because the gs_catch_all captures
    // all of the commands. We do add_action here so that we can change
    // the verbs that are used to "meditate"
    if (this_player()->query_prop(LIVE_I_MEDITATES))
    {
        write("You are already kneeling!\n");
        return 1;
    }

    write("You find yourself an empty prayer mat and kneel before "
        + "the altar to begin praying. Once you are done, you can "
        + "<rise> to your feet.\n");
    say(QCTNAME(this_player()) + " kneels down on the prayer mat before "
        + "the altar.\n");
    this_player()->add_prop(LIVE_S_EXTRA_SHORT, " is praying");
    this_player()->add_prop(LIVE_I_MEDITATES, 1);
    return 1;
}

/*
 * Function:    do_rise
 * Description: Function to allow someone to rise from the prayer
 *              mats.
 */
public int
do_rise(string arg)
{
    if (!this_player()->query_prop(LIVE_I_MEDITATES))
    {
        write("You are not kneeling!\n");
        return 1;
    }
    
    write("You complete your prayers and rise from the prayer "
        + "mat.\n");
    say(QCTNAME(this_player()) + " rises from the prayer mat.\n");
    this_player()->remove_prop(LIVE_S_EXTRA_SHORT);
    this_player()->remove_prop(LIVE_I_MEDITATES);
    return 1;
}

/*
 * Function:    do_anoint
 * Description: Function to allow someone to anoint a player
 *              in preparation for ceremony.
 */
int 
do_anoint(string str) 
{
    object ITP,anoint_obj;

    // Player must be a member to perform rite 
    if (!(IS_MEMBER(TP))) 
        return 0;
 
    // Player must be properly dressed to perform rite 
    if (!((TP->query_armour(A_ROBE))->id(CEREMONIAL_ROBE))) 
    {
        write("You are not suitably vested to do that.\n");
        return 1;
    }
 
    // Incense cloud must be present to perform rite 
    if (!(present(INCENSE_CLOUD,TO))) 
    {
        write("The room should be filled with incense to mark the "+
            "solemnity of such an occassion.\n");
        return 1;
    }
 
    if (!str)
    {
        write("Anoint whom?\n");
        return 1;
    }
   
    // Member must be present in room 
    ITP=find_player(lower_case(str));
 
    if (!((ITP) && (present(ITP,TO)))) 
    {
        write("But "+capitalize(str)+" is not here!\n");
        return 1;
    }
 
    // Initiate must be kneeling 
    if (!ITP->query_prop(LIVE_I_MEDITATES)) 
    {
        write("The person must kneel before the altar in respect.\n");
        return 1;
    }
 
    // All is well, allow anointing 
    TP->catch_msg("You anoint "+(ITP->query_The_name(TP)) + 
        " with oil.\n");
    ITP->catch_msg((TP->query_The_name(ITP))+" anoints you with oil.\n");
    tell_room(TO,QCTNAME(TP) + " anoints "+QTNAME(ITP)+" with oil.\n",
        ({ITP,TP}));
    anoint_obj = clone_object(ELEMENTALIST_OBJS+"anoint_obj");
    anoint_obj->move(ITP);
 
    return 1;
}

/*
 * Function:    cloud
 * Description: Function to have incense stream from censor
                and unblock entrance to the room during ceremonies.
 */
void 
cloud(int step) 
{
    object cloud=present(INCENSE_CLOUD,TO);
 
    if ((step>0) && (!(cloud))) 
    {
        incensing=0;
        return;
    }
 
    switch (step) 
    {
        case 0:
            tell_room(TO,"The chapel is filled with a cloud of incense.\n");
            cloud=clone_object(ELEMENTALIST_OBJS+"incloud");
            cloud->move(TO);
            break;

        case 1:
            tell_room(TO,IncenseStreaming[(random(sizeof(IncenseStreaming)))]
                +".\n");
            break;
        case 2:
            tell_room(TO,IncenseRising[(random(sizeof(IncenseRising)))]
                +".\n");
            break;
        case 3:
            tell_room(TO,IncenseStreaming[(random(sizeof(IncenseStreaming)))]
                +".\n");
            break;
        case 4:
            tell_room(TO,IncenseRising[(random(sizeof(IncenseRising)))]
                +".\n");
            break;
        case 5:
            tell_room(TO,IncenseStreaming[(random(sizeof(IncenseStreaming)))]
                +".\n");
            break;
        case 6:
            tell_room(TO,IncenseRising[(random(sizeof(IncenseRising)))]
                +".\n");
            break;
        case 7:
            tell_room(TO,IncenseStreaming[(random(sizeof(IncenseStreaming)))]
                +".\n");
            break;
        case 8:
            tell_room(TO,IncenseRising[(random(sizeof(IncenseRising)))]
                +".\n");
            break;
        case 9:
            tell_room(TO,IncenseStreaming[(random(sizeof(IncenseStreaming)))]
                +".\n");
            break;
        case 10:
            tell_room(TO,IncenseRising[(random(sizeof(IncenseRising)))]
                +".\n");
            break;
        case 11:
            tell_room(TO,IncenseStreaming[(random(sizeof(IncenseStreaming)))]
                +".\n");
            break;
        case 12:
            tell_room(TO,IncenseRising[(random(sizeof(IncenseRising)))]
                +".\n");
            break;
        case 13:
            tell_room(TO,IncenseStreaming[(random(sizeof(IncenseStreaming)))]
                +".\n");
            break;
        case 14:
            tell_room(TO,IncenseRising[(random(sizeof(IncenseRising)))]
                +".\n");
            break;
            
        case 15:
            tell_room(TO,IncenseStreaming[(random(sizeof(IncenseStreaming)))]
                +".\n");
            break;
        case 16:
            tell_room(TO,IncenseRising[(random(sizeof(IncenseRising)))]
                +".\n");
            break;
        case 17:
            tell_room(TO,IncenseStreaming[(random(sizeof(IncenseStreaming)))]
                +".\n");
            break;
        case 18:
            tell_room(TO,IncenseRising[(random(sizeof(IncenseRising)))]
                +".\n");
            break;
        case 19..20:
        	tell_room(TO,"Wisps of incense rise from the censor as the "+
                "aromatic ash begins to run out.\n");
            break;
        default: 
            tell_room(TO,"The incense burns out and the cloud disperses.\n");
            incensing=0;
            cloud->remove_object();
            (ELEMENTALIST_TEMPLE+"middle10")->set_ceremony(0);
            (ELEMENTALIST_TEMPLE+"middle11")->set_ceremony(0);
            (ELEMENTALIST_TEMPLE+"statue")->set_ceremony(0);
            (ELEMENTALIST_TEMPLE+"greathall")->set_ceremony(0);
            return;
            break;
    }
    
    set_alarm(INCENSE_BEAT, 0.0, "cloud", (step+1));
}

/*
 * Function:    do_load
 * Description: Function to load incense into the censor
                and block entrance to the room during ceremonies.
 */
int 
do_load(string Parms) 
{
    object incense=present(INCENSE_QTY,TP);
    object cloud  =present(INCENSE_CLOUD,TO);
    int    i;
    int    OK=0;
    string *Parm;
 
    if (Parms) 
        Parm=explode(Parms," ");
   
    else 
        return 0;
 
    for (i=0; i<sizeof(Parm); i++)
        if ((Parm[i]=="censor") || (Parm[i]=="incense"))
            OK = 1;
 
    if (!(OK)) 
    {
        NF("Load what?\n");
        return 0;
    }
 
    if (incense)
        if ((cloud) || (incensing))
            write("There is already incense in the censor.\n");
        else 
        {
            write("You load the censor with incense and it bursts into smoke.\n");
            incense->remove_object();
            tell_room(TO,QCTNAME(TP)+" loads the censor with incense.\n",TP);
            tell_room(TO, "Incense begins to stream from the censor.\n");
            incensing=1;
            (ELEMENTALIST_TEMPLE+"middle10")->set_ceremony(0);
            (ELEMENTALIST_TEMPLE+"middle11")->set_ceremony(0);
            (ELEMENTALIST_TEMPLE+"statue")->set_ceremony(0);
            (ELEMENTALIST_TEMPLE+"greathall")->set_ceremony(0);
            set_alarm(15.0,0.0,"cloud",0);
        }
    
    else
        write("You don't have any incense to load the censor.\n");
    
    return 1;
}

/*
 * Function:    do_lay
 * Description: Function to lay hands on someone during
                ceremonies.
 */
int 
do_lay(string Parms) 
{
    object ITP,LayObj;
    int    i,OK;
    string TPName=(TP->query_name());
    string *Parm,IName,FirstName;
 
    // Player must be a member to perform rite 
    if (!(IS_MEMBER(TP))) 
        return 0;
 
    // Player must be properly dressed to perform rite 
    if (!((TP->query_armour(A_ROBE))->id(CEREMONIAL_ROBE))) 
    {
        write("You are not suitably vested to do that.\n");
        return 1;
    }
 
    // Incense cloud must be present to perform rite 
    if (!(present(INCENSE_CLOUD,TO))) 
    {
        write("The room should be filled with incense to mark the "+
            "solemnity of such an occassion.\n");
        return 1;
    }
 
    // Must pass parameters with command: "lay hands on <Player>" 
    OK=1;
    if (Parms) 
    {
        Parm=explode(Parms," ");
        if ((sizeof(Parm)==3) && (Parm[0]=="hands") && (Parm[1]=="on"))
            IName=Parm[2];
        else 
            OK=0;
    }
   
    else 
        OK=0;
    
    if (OK==0) 
    {
        write("Lay hands on whom?\n");
        return 1;
    }
   
    IName=capitalize(IName);
 
    // member must be present in room 
    ITP=find_player(lower_case(IName));
 
    if (!((ITP) && (present(ITP,TO)))) 
    {
        write("But "+IName+" is not here!\n");
        return 1;
    }
 
    // Initiate must be kneeling 
    if (!ITP->query_prop(LIVE_I_MEDITATES)) 
    {
        write("The person must kneel before the altar in respect.\n");
        return 1;
    }
 
    // Must not have already laid hands on same person 
    LayObj=present(CEREMONIAL_LAYOBJ,ITP);
    if (LayObj)     // someone has already laid hands 
    { 
        FirstName=capitalize((LayObj->query_prop(CEREMONIAL_LAYOBJ_FNPROP)));
        if (FirstName==TPName) 
        {
            write("You have already laid hands on "+IName+".\n");
            return 1;
        }

        else // Indicate second person has laid hands 
            LayObj->add_prop(CEREMONIAL_LAYOBJ_SPROP,1);
    }
   
    else       // First person to lay hands 
    {
        LayObj=clone_object(ELEMENTALIST_OBJS+"layobj");
        ITP->move(LayObj);
        LayObj->add_prop(CEREMONIAL_LAYOBJ_FNPROP,capitalize(TPName));
        LayObj->move(ITP);
    }
 
    // All is well, allow laying of hands
    TP->catch_msg("You lay your hands on the shoulders of "+
        (ITP->query_The_name(TP)) + ".\n");
    ITP->catch_msg((TP->query_The_name(ITP))+" lays "+
        (TP->query_possessive())+" hands on your shoulders.\n");
    tell_room(TO,QCTNAME(TP) + " lays "+(TP->query_possessive())+
        " hands on the shoulders of "+QTNAME(ITP)+".\n",
        ({ITP,TP}));
 
    return 1;
}

/*
 * Function:    do_cast
 * Description: Function to cast (draw) a pentagram on the floor
                for use in ceremonies.
 */
public int
do_cast(string str)
{
    // Player must be a member to perform rite 
    if (!(IS_MEMBER(TP))) 
        return 0;
    
    if (!str || str != "pentagram")
    {
    	NF("Cast what? A pentagram?\n");
    	return 0;
    }
 
    // Player must be properly dressed to perform rite
    if (!((TP->query_armour(A_ROBE))->id(CEREMONIAL_ROBE))) 
    {
        write("You are not suitably vested to do that.\n");
        return 1;
    }
    
    if (penta)
    {
        write("There is already a pentagram cast on the floor.\n");
        return 1;
    }
    
    write("You trace your fingers across the floor in the pattern "+
        "of a pentagram. A glowing line appears just behind your "+
        "hand, following where you trace. When you have completed "+
        "the shape, there is a glowing pentagram on the floor.\n");
    tell_room(TO,QCTNAME(TP) + " traces "+TP->query_possessive()+
        " fingers across the floor. A glowing line appears just "+
        "behind "+TP->query_possessive()+" hand, following where "+
        TP->query_pronoun()+" traces. When "+TP->query_pronoun()+
        " finishes, there is a glowing pentagram "+
        "on the floor.\n",({TP}));
    penta = 1;
    
    return 1;
}

/*
 * Function:    do_erase
 * Description: Function to erase a pentagram on the floor.
 */
public int
do_erase(string str)
{
    // Player must be a member to perform rite 
    if (!(IS_MEMBER(TP))) 
        return 0;
    
    if (!str || str != "pentagram")
    {
    	NF("Erase what? A pentagram?\n");
    	return 0;
    }
 
    // Player must be properly dressed to perform rite
    if (!((TP->query_armour(A_ROBE))->id(CEREMONIAL_ROBE))) 
    {
        write("You are not suitably vested to do that.\n");
        return 1;
    }
    
    if (!penta)
    {
        write("There is no pentagram cast on the floor to erase.\n");
        return 1;
    }
    
    write("You wave your hand across the pentagram that is cast "+
        "on the floor. The glowing lines disappear just behind your "+
        "hand, following where you trace. When you have completed "+
        "the shape, the glowing pentagram on the floor is gone.\n");
    tell_room(TO,QCTNAME(TP) + " waves "+TP->query_possessive()+
        " hand across the floor. The glowing lines disappear just "+
        "behind "+TP->query_possessive()+" hand, following where "+
        TP->query_pronoun()+" traces. When "+TP->query_pronoun()+
        " finishes, the glowing pentagram "+
        "on the floor is gone.\n",({TP}));
    penta = 0;
    
    return 1;
}

/*
 * Function:    do_face
 * Description: Function to face someone in a specific direction
 *              during ceremonies.
 */
int 
do_face(string Parms) 
{
    object ITP,LayObj;
    int    i,OK;
    string TPName=(TP->query_name());
    string *Parm,IName,FirstName, direction;
 
    // Player must be a member to perform rite
    if (!(IS_MEMBER(TP))) 
        return 0;
 
    // Player must be properly dressed to perform rite 
    if (!((TP->query_armour(A_ROBE))->id(CEREMONIAL_ROBE))) 
    {
        write("You are not suitably vested to do that.\n");
        return 1;
    }

    if (!penta)
    {
        write("There is no pentagram cast on the floor.\n");
        return 1;
    }
 
    // Incense cloud must be present to perform rite 
            
    if (!(present(INCENSE_CLOUD,TO))) 
    {
        write("The room should be filled with incense to mark the "+
            "solemnity of such an occassion.\n");
        return 1;
    }

    // Must pass parameters with command: "face <player> <direction>" 

    if (sscanf(Parms, "%s %s", IName, direction) == 2)
        OK=1;   
    else 
        OK=0;
    
    if (OK==0) 
    {
        write("Face whom which direction? (face <player> <direction>)\n");
        return 1;
    }
   
    IName=capitalize(IName);
 
    // Member must be present in room 
    ITP=find_player(lower_case(IName));    
 
    if (!((ITP) && (present(ITP,TO)))) 
    {
        write("But "+IName+" is not here!\n");
        return 1;
    }

    direction = lower_case(direction);
    switch(direction)
    {
        case "north":
            break;
        case "northeast":
            break;
        case "northwest":
            break;
        case "southeast":
            break;
        case "southwest":
            break;
        default:
            write("That is not a valid direction. Valid directions "+
                "are North, Northeast, Northwest, Southeast and Southwest.\n");
            return 1;
            break;
    }            
 
    // All is well, allow laying of hands 
    TP->catch_msg("You grasp the shoulders of "+
        (ITP->query_The_name(TP)) + " and turn "+
        ITP->query_objective()+" to face "+capitalize(direction)+".\n");
    ITP->catch_msg((TP->query_The_name(ITP))+" grasps "+
        "your shoulders and turns you to face "+
        capitalize(direction)+".\n");
    tell_room(TO,QCTNAME(TP) + " grasps the shoulders of "+
        QTNAME(ITP)+" and turns "+ITP->query_objective()+
        " to face "+capitalize(direction)+".\n",
        ({ITP,TP}));
 
    return 1;
}

/*
 * Function:    do_turn
 * Description: Function to have someone turn to a specific direction
 *              during ceremonies.
 */
int 
do_turn(string Parms) 
{
    string TPName=(TP->query_name());
    string direction;
 
    // Player must be a member to perform rite 
    if (!(IS_MEMBER(TP))) 
        return 0;
 
    // Player must be properly dressed to perform rite 
    if (!((TP->query_armour(A_ROBE))->id(CEREMONIAL_ROBE))) 
    {
        write("You are not suitably vested to do that.\n");
        return 1;
    }

    if (!penta)
    {
        write("There is no pentagram cast on the floor.\n");
        return 1;
    }
     
    // Incense cloud must be present to perform rite 

    if (!(present(INCENSE_CLOUD,TO))) 
    {
        write("The room should be filled with incense to mark the "+
            "solemnity of such an occassion.\n");
        return 1;
    }   

    direction = lower_case(Parms);
    switch(direction)
    {
        case "north":
            break;
        case "northeast":
            break;
        case "northwest":
            break;
        case "southeast":
            break;
        case "southwest":
            break;
        default:
            write("That is not a valid direction. Valid directions "+
                "are North, Northeast, Northwest, Southeast and Southwest.\n");
            return 1;
            break;
    }            
 
    TP->catch_msg("You turn to face "+capitalize(direction)+".\n");
    tell_room(TO,QCTNAME(TP) + " turns to face "+capitalize(direction)+".\n",
        ({TP}));
 
    return 1;
}

public int
do_stand(string str)
{   
    if (!penta)
    {
        NF("What?\n");
        return 0;
    }
    
    if (!str)
    {
        NF("Stand where? In the pentagram?\n");
        return 0;
    }
    
    switch(str)
    {
        case "pentagram":
        case "in pentagram":
        case "in the pentagram":
            break;
        
        default:
            NF("Stand where? In the pentagram?\n");
            return 0;
            break;
    }
        
    write("You stand in the centre of the pentagram.\n");
    say(QCTNAME(TP)+" stands in the centre of the pentagram.\n");    
    return 1;
}

public void            
inform_player_need_permission(object player)
{
    // Begin Sequence
    player->catch_tell("An apparition appears to you.\n");
    tell_room(this_object(), QCTPNAME(player) + " eyes suddenly glaze over.\n", player);
        
    // Actual Instructions
    player->catch_tell(
        "The apparition speaks to you: Greetings again, Seeker.\n");
    player->catch_tell(
        "The apparition speaks to you: You have not yet been accepted by an Elder "
        + "of the Elemental Clerics. Return to me again once this has "
        + "been done.\n\n");
        
    // End Sequence
    player->catch_tell("The apparition disappears.\n");
    tell_room(this_object(), QCTPNAME(player) + " eyes return to normal.\n", player);
}

public void
join_clerics(object player)
{
    setuid();
    seteuid(getuid());

    // Begin Section
    player->catch_msg(
        "A cloud suddenly appears from nowhere and slowly solidifies into a "+
        "human shape.\n");
    tell_room(environment(player), "A cloud suddenly appears and slowly "+
        "solidifies into human shape.\n", player);

    player->catch_msg(
        "The shape speaks to you in the same voice that you recognize as "+
        "the apparition:\nI am Nysa. I congratulate you on proving yourself "+
        "worthy of beginning your journey to become one with the Elementals. "+
        "Welcome to the Circle, Child. May the Elementals nurture you and guide "+
        "you on your journeys.\n\n" +
        "Nysa hands you some scrolls and whispers to you: These scrolls will help "+
        "you get acquainted with your new gifts. You can refer to them anytime by "+
        "using the <help cleric> command.\nYou quickly read the scrolls and their "+
        "knowledge is instantly set in your mind. The scrolls evaporate into nothingness.\n\n"+
        "Nysa whispers to you: You must now build your sacred mandala. In order to "+
        "do that, you will require the seed to start it. This seed is knows as the "+
        "Sporos. Jardeth will be happy to help you with that, all you need do is "+
        "ask him about your Sporos.\n\n" +
        "You may now pass through into the inner parts of this Temple. "+
        "May the Elementals guide your ways always.\n");
    tell_room(environment(player), "The shape speaks to " + QTNAME(player) + ": "+
        "I am Nysa. I congratulate you on proving yourself worthy of "+
        "becoming one with the Elementals. I hereby welcome you into the Circle!\n"+
        "The shape whispers something to " + QTNAME(player) + ".\n", player);

    GUILD_MANAGER->join_occ_guild(player);

    // End Sequence
    player->catch_tell("The pentagram glows very brightly for a moment, then "+
        "vanishes without a trace.\nNysa disappears into a swirling mass of mist.\n");
    tell_room(environment(player),"The pentagram glows very brightly for a moment, "+
        "then vanishes without a trace.\nNysa disappears into a swirling mass of mist.\n", player);
    penta = 0;


    // Inform the rest of the guild
    object * listeners = GUILD_MANAGER->query_awake_clerics() + GUILD_MANAGER->query_awake_worshippers() +
        GUILD_MANAGER->query_awake_seekers();
    listeners -= ({ player });
    listeners->catch_tell(JOINED(player)[random(4)]);

    seteuid(getuid());
    object board = present("board", CLERIC_BOARDROOM->get_this_object());
    if (objectp(board)) 
    { 
        board->create_note("New Circle Member", 
                 "Sehis", capitalize(player->query_real_name()) + 
                 " has joined the Elemental Clerics!\n\nSehis\n"); 
    }
    send_debug_message("cleric", capitalize(this_player()->query_real_name())
                       + " has joined the Elemental Clerics.", EVENTS_LOG);
    COUNCIL_LOG_BOOK->update_log_book(my_time() + capitalize(this_player()->query_real_name()) 
        + " has joined the Elemental Clerics.\n");

}

public void
begin_cleric_joining_sequence(object player)
{
    player->catch_tell("The apparition speaks to you: 'You have brought "+
        "all of the Elemental Tools before the Five.\nYou have undergone "+
        "the Ceremony of Gennisi and received permission from an Elder in "+
        "the Circle.'\n\nYou feel energy surge throughout your body. As "+
        "it quickly disappears, you seem to feel a bit hollow.\n\n'Yes, I "+
        "agree. I think this one will do very well.' you hear the apparition "+
        "say.\n\n");
    set_alarm(2.0, 0.0, &join_clerics(player));
}

public int
do_pray(string str)
{
    setuid();
    seteuid(getuid());
 
    object player = this_player();
    if (!player->query_prop(LIVE_I_MEDITATES))
    {
        notify_fail("You should <kneel> before praying.\n");
        return 0;
    }

    if (!strlen(str))
    {
        notify_fail("Pray to whom?\n");
        return 0;
    }       

    str = lower_case(str);
    if (parse_command(str, player, " [to] [the] 'elementals' "))
    {
        if (IS_MEMBER(player) && !IS_SEEKER(player))
        {
        	if (!present("_echosen_",player))
        	{
	            write("An apparition appears to you and says: "+
	                  "Go in peace my child.\n");
	            write("The apparition disappears.\n");
	            return 1;
	        }
        }

        //  If you are a member of the Seekers guild and have been
        //  given permission, then the joining sequence begins.
        
        if (!GUILD_MANAGER->query_can_join_clerics(player))
        {
        	if (!present("_echosen_",player))
            {
        		inform_player_need_permission(player);
            	return 1;
            }
        }

        // If we get here, they are ready to become an Elemental Cleric
        begin_cleric_joining_sequence(player);
        return 1;
    }
    else if (parse_command(str, player, " [to] [lord] [lady] 'psuchae' / 'pyros' / 'diabrecho' / 'aeria' / 'gu' "))
    {
        // Is there a ceremony taking place?
        if (ceremony)
        {
            int i = 0;
            string * raw_command = explode(str," ");
            string element, diety_name, triangle, color, sign;
            
            // Determine what happens depending on the Ceremony
            switch(ceremony)
            {
                case 1: // Gennisi
                    break;
                case 2: // Enarxi
                    break;
                case 3: // Anavasi
                    for(i=0; i<sizeof(raw_command); i++)
                    {
                        switch(raw_command[i])
                        {
                            case "pyros":
                                element = "fire";
                                triangle = "southeast";
                                color = "red";
                                sign = "smoke";
                                diety_name = "Lord Pyros";
                                break;
                            case "psuchae":
                                element = "life";
                                triangle = "north";
                                color = "black";
                                sign = "mist";
                                diety_name = "Psuchae";
                                break;
                            case "diabrecho":
                                element = "water";
                                triangle = "northeast";
                                color = "blue";
                                sign = "steam";
                                diety_name = "Lord Diabrecho";
                                break;
                            case "aeria":
                                element = "air";
                                triangle = "northwest";
                                color = "white";
                                sign = "breeze";
                                diety_name = "Lady Aeria";
                                break;
                            case "gu":
                                element = "earth";
                                triangle = "southwest";
                                color = "brown";
                                sign = "dust";
                                diety_name = "Lady Gu";
                                break;
                            default:
                                break;
                        }
                    }
                    
                    if (element == (GUILD_MANAGER->query_primary_element(TP->query_real_name())))
                    {
                        if (penta)
                        {
                            write("As you pray fervently to "+diety_name+", the "+triangle+
                                " triangle of the pentagram flashes "+color+" and "+
                                sign+" rises up from it for moment. You feel that your "+
                                "prayer has been heard.\n");
                            say(QCTNAME(player) + " prays fervently before the altar. "+
                                "The "+triangle+" triangle of the pentagram flashes "+
                                color+" and "+sign+" rises up from it for a moment.\n");
                            return 1;
                        }
                    }
                                
                    write("You pray fervently to "+diety_name+" and you feel that your "
                        + "prayer has been heard.\n");
                    say(QCTNAME(player) + " prays fervently before the altar.\n");
                    return 1;
                    break;
                case 4: // Kyverno
                    for(i=0; i<sizeof(raw_command); i++)
                    {
                        switch(raw_command[i])
                        {
                            case "pyros":
                                element = "fire";
                                triangle = "southeast";
                                color = "red";
                                sign = "smoke";
                                diety_name = "Lord Pyros";
                                break;
                            case "psuchae":
                                element = "life";
                                triangle = "north";
                                color = "black";
                                sign = "mist";
                                diety_name = "Psuchae";
                                break;
                            case "diabrecho":
                                element = "water";
                                triangle = "northeast";
                                color = "blue";
                                sign = "steam";
                                diety_name = "Lord Diabrecho";
                                break;
                            case "aeria":
                                element = "air";
                                triangle = "northwest";
                                color = "white";
                                sign = "breeze";
                                diety_name = "Lady Aeria";
                                break;
                            case "gu":
                                element = "earth";
                                triangle = "southwest";
                                color = "brown";
                                sign = "dust";
                                diety_name = "Lady Gu";
                                break;
                            default:
                                break;
                        }
                    }
                    
                    if (element == (GUILD_MANAGER->query_primary_element(TP->query_real_name())))
                    {
                        if (penta)
                        {
                            write("As you pray fervently to "+diety_name+", the "+triangle+
                                " triangle of the pentagram flashes "+color+" and "+
                                sign+" rises up from it for moment.\n\nThe voice of "+
                                diety_name+" echoes in your mind saying: Congratulations "+
                                "on being worthy to guide others upon the path of the "+
                                "Circle. May the Elementals all guide you upon your "+
                                "chosen path, Always.\n");
                            say(QCTNAME(player) + " prays fervently before the altar. "+
                                "The "+triangle+" triangle of the pentagram flashes "+
                                color+" and "+sign+" rises up from it for a moment.\n");
                            return 1;
                        }
                    }
                                
                    write("You pray fervently to "+diety_name+" and you feel that your "
                        + "prayer has been heard.\n");
                    say(QCTNAME(player) + " prays fervently before the altar.\n");
                    return 1;
                    break;
                case 5: // Provoli
                    break;
            }
        }
        
        // No ceremony taking place - continue as normal
        write("You pray fervently to the Elemental and you feel that your "
            + "prayer has been heard.\n");
        say(QCTNAME(player) + " prays fervently before the altar.\n");
    }
    else
    {   
        write("You pray " + str + ".\n");
        say(QCTNAME(player) + " prays fervently before the altar.\n");
    }

    return 1;
}

/*
 * Function name: prevent_leave
 * Description:   Called when an object is trying to leave this container
 *                to see if we allow it to leave.
 * Arguments:     object ob - the object trying to leave
 * Returns:       1 - The object is not allowed to leave
 *                0 - The object is allowed to leave
 */
public int
prevent_leave(object ob)
{
    if (ob->query_prop(LIVE_I_MEDITATES))
    {
        ob->catch_tell("You can't leave while you're still kneeling and "
            + "praying! Try to <rise> from the prayer mat first.\n");
        return 1;
    }
    
    return 0;
}

public string
desc_long_description()
{
    string long_desc = 
          "You have entered the chapel of the Elemental Temple of "
        + "Calia, a place full of memories of ceremonies gone by. A "
        + "polished marble altar stands in the center of the room. On "
        + "top of one side of the altar sits a copper brazier, while "
        + "a silver censor sits atop a slender tripod on the other side. ";
    
    if (this_player()->query_prop(LIVE_I_MEDITATES))
    {
        long_desc += "You are kneeling at a prayer mat surrounding the altar "
            + "from which you can <rise>. ";
    }
    else
    {
        long_desc += "Closely surrounding the altar are prayer mats where one may "
        + "<kneel>. ";
    }
    
    long_desc += "Behind the mats a few rows of wooden benches encircle "
        + "the altar. "; 
    
    return long_desc += "\n\n";
}
