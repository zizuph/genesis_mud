
/*
 * chapel.c
 *
 * Chapel for the Spirit Circle of Psuchae Temple
 * This chamber will serve as a ceremony room for various 
 * ceremonies like member promotions, Archon appointments,
 * and Patriarch/Matriarch appointments. My great thanks
 * to Zima for such wonderful ceremony code.
 * Only members of the guild will be allowed to go north 
 * into the training room, into the council chambers 
 * (they'll have to be council members AND members of the 
 * guild to get in there), and enter the sacristy (items 
 * for the various ceremonies are held in there). Players
 * must also be members to do any of the ceremony related
 * commands (promote, lay hands, etc...) EXCEPT kneel. I
 * figure if anyone wants to kneel before they altar, they
 * can go right ahead and do so <grin>.
 *
 * Copyright (C): Jaacar (Mike Phipps), July 29, 2003
 *
 */
 
#pragma strict_types
#pragma save_binary

inherit "/std/room";

#include <macros.h>
#include <std.h>
#include <stdproperties.h>
#include <language.h>
#include <wa_types.h>
#include <ss_types.h>

#include "defs.h"
#include SPIRIT_HEADER
#include COUNCIL_HEADER

#define JOIN_LOG     SPIRIT_LOGS+"joinlog"

#define INCENSE_BEAT 30.0

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
  "Incense rises gracefully from the censor in thinning whisps",           \
  "The cloud begins to thin as the incense burns low",                     \
  "Whisps of incense rise from the vents of the censor",                   \
  "Incense whisps gracefully from the silver censor",                      \
  "Incense rises slowly from the dieing embers of its ash",                \
  "Thinning plumes of incense rise solemnly from the censor",              \
  "Incense smokes lightly from the silver censor"}))

#define LEFT(x) ({"You hear the voice of Psuchae proclaim: "+x->query_name()+ \
    " has left the Spirit Circle and is no longer one of us!"})

int incensing=0;

string *council = ({ });
mapping punishments = ([ ]);
mapping mentors = ([ ]);
string *spirit_apprentices = ({ });
string *spirit_masters = ({ });
string *spirit_elders = ({ });
string archon = "";
string patriarch = "";

int
is_spirit(object living)
{
    return living->query_guild_name_occ() == SPIRIT_GUILD_NAME;
}

string
my_time()
{
    return (ctime(time())[4..9] + ": ");
}

void
create_room()
{
    set_short("Chapel");
    set_long("You have entered the chapel of this temple, a place "+
        "full of memories of ceremonies gone by. A polished marble "+
        "altar stands near the west wall. A copper brazier sits on "+
        "one side of the altar, while a silver censor sits atop a "+
        "slender tripod on the other. A few rows of wooden benches "+
        "face the front of the chapel. There is an entrance to the "+
        "council chambers, a door in the north wall, a small "+
        "golden door to the south leads to the sacristy, as well as "+
        "a second passageway leading to the south.\n");

    add_item(({"wall","walls"}),"The walls are constructed of "+
        "irregular stones of various sizes and shapes. They seem to "+
        "be very natural, smoothed by centuries of wind. The fact "+
        "that they fit together so well seems amazing.\n");
    add_item(({"floor","tile","tiles","matrix"}),
        "The floor of the chapel is covered with white tiles. "+
        "They are set into the floor into an orderly matrix of "+
        "columns and rows.\n");
    add_item(({"roof","ceiling"}),"Far above you lies the smooth "+
        "domed ceiling of the chapel. It appears to be made from "+
        "the same type of stones as the walls are constructed with.\n");
    add_item(({"altar","marble altar","polished marble altar",
        "polished altar","white altar","white marble altar"}),"It is "+
        "a long narrow altar made of polished white marble. An emblem "+
        "has been carved into its polished surface.\n");
    add_item("emblem","Carved into the top of the altar, the emblem "+
        "is that of three intertwined circles in the centre of a "+
        "fourth circle.\n");
    add_item(({"brazier","copper brazier"}),"It is a large copper "+
        "container, bowl-like in shape, cast with runes on its outer "+
        "surface. A large blue flame burns solemnly from it, warming "+
        "the cold stones of the chamber.\n");
    add_item(({"flame","blue flame","large flame","large blue flame"}),
        "The large blue flame burns quietly and evenly in "+
        "the brazier, giving the chapel a warm ambiance.\n");
    add_item(({"benches","wooden benches","bench","wooden bench"}),
        "The simple wooden benches run west to east, "+
        "bisected by an aisle leading to the altar.\n");
    add_item("aisle","It cuts between the benches from the entrance "+
        "to the altar.\n");
    add_item(({"council chamber", "council chambers"}), "There is an "+
        "entrance to the council chambers here. You could try to enter "+
        "them if you would like. <enter council chambers>\n");
    add_item(({"golden door", "small golden door"}), "There is a small "+
        "golden door in the south wall. It leads to the sacristy. You "+
        "could try to enter it if you wanted to go into the sacristy. "+
        "<enter sacristy>\n");
    add_item("sacristy","The sacristy is through the small golden "+
        "door in the south wall. You could try to enter it if you "+
        "wished. <enter sacristy>\n");
    add_item(({"censor","silver censor"}),"@@exa_censor");
    add_item("tripod","The tripod is made of three long rods made "+
        "of silver, joined together at the top providing a stand "+
        "for the censor.\n");

    IN;
    add_prop(ROOM_M_NO_ATTACK,"You cannot attack in here, you are in a "+
        "sacred place!\n");
    add_prop(ROOM_M_NO_MAGIC_ATTACK,"You cannot attack in here, you are in "+
        "a sacred place!\n");

    add_exit(SPIRIT_TEMPLE+"training_room","north","@@check_spirit",1);
    add_exit(SPIRIT_TEMPLE+"common_room","south","@@check_kneeling",1);
    add_exit(SPIRIT_TEMPLE+"antechamber","east","@@check_kneeling",1);
}

string 
exa_censor() 
{
    string desc = "It is a silver censor, a bowl with a vented lid, used "+
        "to burn incense during ceremonies. ";
    object incense=present(INCENSE_CLOUD,TO);
   
    if ((incense)||(incensing))
        desc=desc+"A bitter-sweet aroma pervades the air as incense "+
            "streams from the censor filling the sanctuary.\n";
    else
        desc=desc+"\n";
   
    return desc;
}

int
check_kneeling()
{
    object kneeling=present(KNEELING_OBJECT,TP);
    object layobj=present(CEREMONIAL_LAYOBJ,TP);

    if (kneeling) 
    {
        write("You are kneeling. You must rise first.\n");
        return 1;
    }
   
    if (layobj)
        layobj->remove_object();

    return 0;
}

int
check_spirit()
{
    object kneeling=present(KNEELING_OBJECT,TP);
    object layobj=present(CEREMONIAL_LAYOBJ,TP);

    if (kneeling) 
    {
        write("You are kneeling. You must rise first.\n");
        return 1;
    }

    if (is_spirit(TP))
    {
        if (layobj)
            layobj->remove_object();
        
        if (TP->query_skill(SS_SPIRIT_PUNISHMENT) == TRAIN_BANNED)
        {
            write("A voice echoes through your mind: You have been "+
                "banned from training by the council. You may not "+
                "enter the training chamber.\n");
            return 1;
        }
        
        return 0;
    }
    
    if(TP->query_wiz_level())
    {
        write("Normally you would not be allowed in this chamber, "+
            "but since you are a wizard an exception can be made.\n");
        if(layobj)
            layobj->remove_object();

        return 0;
    }

    write("A voice from above:\nOnly those who "+
        "follow the Spiritual Path may pass.\n\n");
    return 1;
}

int
do_enter(string str)
{
    object kneeling=present(KNEELING_OBJECT,TP);
    object layobj=present(CEREMONIAL_LAYOBJ,TP);

    if (kneeling) 
    {
        write("You are kneeling. You must rise first.\n");
        return 1;
    }
   
    if (layobj)
        layobj->remove_object();

    if (!str)
    {
        NF("Enter what? The council chambers? The sacristy? <enter "+
           "council chambers> <enter sacristy>\n");
        return 0;
    }

    if (str == "sacristy")
    {
        if(is_spirit(TP))
        {
            write("You enter into the sacristy.\n");
            say(QCTNAME(TP)+" leaves through the small golden door.\n");
            TP->move_living("M",SPIRIT_TEMPLE+"sacristy");
            tell_room(environment(TP),QCTNAME(TP)+" enters through the "+
                "small golden door.\n",TP);
            return 1;
        }

        write("A voice from above:\nOnly those who follow the "+
            "Spiritual Path may pass.\n\n");
        say(QCTNAME(TP)+" tried to leave through the small golden "+
            "door, but seemed to be stopped by some magical force.\n");
        return 1;
    }

    if (str == "council chambers")
    {
        if(is_spirit(TP))
        {
            if (!(COUNCIL_CODE->is_council_member(TP->query_name()) ||
                COUNCIL_CODE->is_calian_wiz(TP)) &&
                (SECURITY->query_wiz_level(TP->query_real_name()) < 39))
            {
                write("Only the council members may enter the council "+
                    "chambers.\n");
                say(QCTNAME(TP)+" attempted to enter the council "+
                    "chambers, but was stopped by some unseen force.\n");
                return 1;
            }

            write("You enter the council chambers.\n");
            say(QCTNAME(TP)+" enters the council chambers.\n");
            TP->move_living("M",SPIRIT_TEMPLE+"councilroom");
            tell_room(environment(TP),QCTNAME(TP)+" enters the room.\n",TP);
            return 1;
        }

        write("A voice from above:\nOnly those who follow the "+
            "Spiritual Path may pass.\n\n");
        say(QCTNAME(TP)+" tried to enter the council chambers, but "+
            "seemed to be stopped by some magical force.\n");
        return 1;
    }

    NF("Enter what? The council chambers? The sacristy? <enter council "+
       "chambers> <enter sacristy>\n");
    return 0;
}

int 
do_kneel() 
{
    object kneeling=present(KNEELING_OBJECT,TP);
 
    if (kneeling)
        write("You already kneel before the altar.\n");
    else 
    {
        write("You kneel reverently before the altar.\n");
        tell_room(this_object(),QCTNAME(TP)+
            " kneels reverently before the altar.\n",TP);
        clone_object(SPIRIT_OBJECTS+"kneelobj")->move(TP);
        TP->add_prop(LIVE_S_EXTRA_SHORT," is kneeling reverently "+
            "before the altar");
    }
   
    return 1;
}
 
int 
do_anoint(string str) 
{
    object ITP,anoint_obj;

    /* player must be a member to perform rite */
    if (!(IS_MEMBER(TP))) 
        return 0;
 
    /* player must be properly dressed to perform rite */
    if (!((TP->query_armour(A_ROBE))->id(CEREMONIAL_ROBE))) 
    {
        write("You are not suitably vested to do that.\n");
        return 1;
    }
 
    /* incense cloud must be present to perform rite */
    if (!(present(INCENSE_CLOUD,TO))) 
    {
        write("The room should be filled with incense to mark the "+
            "solemnity of such an occassion.\n");
        return 1;
    }
 
    if (!str)
    {
        write("Lay hands on whom?\n");
        return 1;
    }
   
    /* member must be present in room */
    ITP=find_player(lower_case(str));
 
    if (!((ITP) && (present(ITP,TO)))) 
    {
        write("But "+capitalize(str)+" is not here!\n");
        return 1;
    }
 
    /* initiate must be kneeling */
    if (!(present(KNEELING_OBJECT,ITP))) 
    {
        write("The member must kneel before the altar in respect.\n");
        return 1;
    }
 
    /* all is well, allow anointing */
    TP->catch_msg("You anoint "+(ITP->query_The_name(TP)) + 
        " with oil.\n");
    ITP->catch_msg((TP->query_The_name(ITP))+" anoints you with oil.\n");
    tell_room(TO,QCTNAME(TP) + " anoints "+QTNAME(ITP)+" with oil.\n",
        ({ITP,TP}));
    anoint_obj = clone_object(SPIRIT_OBJECTS+"anoint_obj");
    anoint_obj->move(ITP);
 
    return 1;
}

int 
do_rise() 
{
    object kneeling=present(KNEELING_OBJECT,TP);
    
    if (kneeling) 
    {
        write("You rise from kneeling.\n");
        tell_room(TO,QCTNAME(TP)+" rises from kneeling.\n",TP);
        kneeling->remove_object();
        TP->remove_prop(LIVE_S_EXTRA_SHORT);
    }
    
    else 
        write("You are not kneeling.\n");
   
    return 1;
}
 
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
            cloud=clone_object(SPIRIT_OBJECTS+"incloud");
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
            tell_room(TO,"Whisps of incense rise from the censor as the "+
                "aromatic ash begins to run out.\n");
            break;
        default: 
            tell_room(TO,"The incense burns out and the cloud disperses.\n");
            incensing=0;
            cloud->remove_object();
            (SPIRIT_TEMPLE+"antechamber")->set_ceremony(0);
            return;
            break;
    }
    
    set_alarm(INCENSE_BEAT, 0.0, "cloud", (step+1));
}

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
            (SPIRIT_TEMPLE+"antechamber")->set_ceremony(1);
            set_alarm(15.0,0.0,"cloud",0);
        }
    
    else
        write("You don't have any incense to load the censor.\n");
    
    return 1;
}

int 
do_lay(string Parms) 
{
    object ITP,LayObj;
    int    i,OK;
    string TPName=(TP->query_name());
    string *Parm,IName,FirstName;
 
    /* player must be a member to perform rite */
    if (!(IS_MEMBER(TP))) 
        return 0;
 
    /* player must be properly dressed to perform rite */
    if (!((TP->query_armour(A_ROBE))->id(CEREMONIAL_ROBE))) 
    {
        write("You are not suitably vested to do that.\n");
        return 1;
    }
 
    /* incense cloud must be present to perform rite */
    if (!(present(INCENSE_CLOUD,TO))) 
    {
        write("The room should be filled with incense to mark the "+
            "solemnity of such an occassion.\n");
        return 1;
    }
 
    /* must pass parameters with command: "lay hands on <Player>" */
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
 
    /* member must be present in room */
    ITP=find_player(lower_case(IName));
 
    if (!((ITP) && (present(ITP,TO)))) 
    {
        write("But "+IName+" is not here!\n");
        return 1;
    }
 
    /* initiate must be kneeling */
    if (!(present(KNEELING_OBJECT,ITP))) 
    {
        write("The member must kneel before the altar in respect.\n");
        return 1;
    }
 
    /* must not have already laid hands on same person */
    LayObj=present(CEREMONIAL_LAYOBJ,ITP);
    if (LayObj)     /* someone has already laid hands */
    { 
        FirstName=capitalize((LayObj->query_prop(CEREMONIAL_LAYOBJ_FNPROP)));
        if (FirstName==TPName) 
        {
            write("You have already laid hands on "+IName+".\n");
            return 1;
        }

        else /* indicate second person has laid hands */
            LayObj->add_prop(CEREMONIAL_LAYOBJ_SPROP,1);
    }
   
    else       /* first person to lay hands */
    {
        LayObj=clone_object(CEREMONIAL_LAYOBJ_FILE);
        ITP->move(LayObj);
        LayObj->add_prop(CEREMONIAL_LAYOBJ_FNPROP,capitalize(TPName));
        LayObj->move(ITP);
    }
 
    /* all is well, allow laying of hands */
    TP->catch_msg("You lay your hands on the shoulders of "+
        (ITP->query_The_name(TP)) + ".\n");
    ITP->catch_msg((TP->query_The_name(ITP))+" lays "+
        (TP->query_possessive())+" hands on your shoulders.\n");
    tell_room(TO,QCTNAME(TP) + " lays "+(TP->query_possessive())+
        " hands on the shoulders of "+QTNAME(ITP)+".\n",
        ({ITP,TP}));
 
    return 1;
}
 
int 
do_promote(string Parms) 
{
    object ITP,LayObj,beads;
    int    i,OK;
    string TPName=(TP->query_name());
    string *Parm,IName,FirstName,Title;
 
    /* player must be a member to perform rite */
    if (!(IS_MEMBER(TP))) 
        return 0;
 
    /* player must be properly dressed to perform rite */
    if (!((TP->query_armour(A_ROBE))->id(CEREMONIAL_ROBE))) 
    {
        write("You are not suitably vested to do that.\n");
        return 1;
    }
 
    /* must pass parameter with name with title */
    OK=1;

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

    else 
        OK=0;
   
    if (OK==0) 
    {
        write("Promote whom?\n");
        return 1;
    }
   
    IName=capitalize(IName);
 
    /* new member must be present in room */
    ITP=find_player(lower_case(IName));
    if (!((ITP) && (present(ITP,TO))))  
    {
        write("But "+IName+" is not here!\n");
        return 1;
    }
     
    /* Inductee must have hands laid on him at least twice */
    
    LayObj=present(CEREMONIAL_LAYOBJ,ITP);
    if (!((LayObj) && (LayObj->query_prop(CEREMONIAL_LAYOBJ_SPROP)))) 
    {
        write("This one has not been chosen by two within the Circle.\n");
        return 1;
    }
       
    Title = capitalize(Title);

    LayObj->remove_object();
      
    TP->catch_msg("You induct "+(ITP->query_The_name(TP))+ " as the "+
        "new "+Title+".\n");
    ITP->catch_msg((TP->query_The_name(ITP))+ " inducts you as the new "+
        Title+".\n");
    tell_room(TO,QCTNAME(TP)+" inducts "+QTNAME(ITP)+" as the new "+
        Title+".\n",({ITP,TP}));
    if (COUNCIL_CODE->is_council_member(TP->query_real_name()))
    {
        switch (Title)
        {
            case "Harbinger":
                (COUNCIL_CODE->add_council_member(ITP->query_real_name(),
                    TP->query_real_name()));
                break;
            case "Archon":
                (COUNCIL_CODE->set_archon(ITP->query_real_name(),
                    TP->query_real_name()));
                break;
            case "Patriarch":
                (COUNCIL_CODE->set_patriarch(ITP->query_real_name(),
                    TP->query_real_name()));
                break;
            case "Matriarch":
                (COUNCIL_CODE->set_patriarch(ITP->query_real_name(),
                    TP->query_real_name()));
                break;
            case "Theurgist":
                (COUNCIL_CODE)->set_theurgist(ITP->query_real_name(),
                    TP->query_real_name());
                break;
            case "Liberator":
                (COUNCIL_CODE->set_liberator(ITP->query_real_name(),
                    TP->query_real_name()));
                break;
            case "Cultivator":
                (COUNCIL_CODE->set_cultivator(ITP->query_real_name(),
                    TP->query_real_name()));
                break;
            case "Beacon":
                (COUNCIL_CODE->set_beacon(ITP->query_real_name(),
                    TP->query_real_name()));
                break;
            case "Missionary":
                (COUNCIL_CODE->set_missionary(ITP->query_real_name(),
                    TP->query_real_name()));
                break;
            case "Luminary":
                (COUNCIL_CODE->set_luminary(ITP->query_real_name(),
                    TP->query_real_name()));
                break;
            case "Emissary":
                (COUNCIL_CODE->set_emissary(ITP->query_real_name(),
                    TP->query_real_name()));
                break;
            case "Illuminati":
                (COUNCIL_CODE->set_illuminati(ITP->query_real_name(),
                    TP->query_real_name()));
                break;
            case "Intercessor":
                (COUNCIL_CODE->set_intercessor(ITP->query_real_name(),
                    TP->query_real_name()));
                break;
            case "Conservator":
                (COUNCIL_CODE->add_conservator(ITP->query_real_name(),
                    TP->query_real_name()));
                break;
            case "Master":
                (COUNCIL_CODE->promote_apprentice(ITP->query_real_name(),
                    TP->query_real_name()));
                break;
            case "Elder":
                (COUNCIL_CODE->promote_master(ITP->query_real_name(),
                    TP->query_real_name()));
                break;
            default:
                write("The title "+Title+" is not an official title, therefore "+
                    "no official promotion has been done.\n");
                break;
        }
    }
    return 1;
}

int
grr()
{
    present("_spirit_action_limiter_",TP)->remove_object();
    write("You feel your tongue growing back.\n");
    write("You feel a firm grip upon your shoulders, picking you "+
        "up and moving you. You feel yourself being put back on "+
        "the ground. Your heart starts again, your sight returns "+
        "and you find yourself elsewhere.\n");
    say(QCTNAME(TP)+" is suddenly picked up by two shadowy hands and "+
        "hauled off through the doors to the east.\n",TP);
    TP->move_living("X",SPIRIT_TEMPLE+"entryway");
    tell_room(environment(TP),QCTNAME(TP)+" comes out of the double "+
        "doors to the north carried by two shadowy hands and placed "+
        "down on the ground. The shadowy hands disappear just as the "+
        "doors close.\n",TP);
    return 1;
}

int
do_betray(string str)
{
    string name;
    int xp_remove;

    name = lower_case(TP->query_real_name());

    if (!is_spirit(TP))
    {
        notify_fail("You are not a member of this guild!\n");
        return 0;
    }
    if (str !="my Blessing")
    {
        NF("Betray what? Your Blessing? <betray my Blessing>\n");
        return 0;
    }

    xp_remove = ((TP->query_exp_combat() * 2) / 10);
    TP->add_exp(-xp_remove, 1);
    present("spirit_holy_symbol",TP)->remove_object();
    present("_spirit_apprentice_spells_",TP)->remove_object();
    present("_spirit_master_spells_",TP)->remove_object();
    present("_spirit_elder_spells_",TP)->remove_object();
    COUNCIL_CODE->remove_apprentice(name);
    COUNCIL_CODE->remove_master(name);
    TP->remove_skill(SS_PATRON_ELEMENTAL);
    TP->remove_skill(SS_ELEMENT_SPIRIT);
    TP->remove_skill(SS_SPIRIT_TITLE);
    TP->remove_skill(SS_SPIRIT_CHOSEN);
    TP->set_skill(SS_PUNISHMENT,EXPELLED);
    TP->set_skill(SS_SPIRIT_PUNISHMENT,EXPELLED);
    write("Your holy symbol disappears!\n");
    reset_euid();
    if (TP->query_default_start_location() == SPIRIT_START)
        TP->set_default_start_location(TP->query_def_start());
    TP->remove_guild_occ();
    TP->remove_guild_lay();
    TP->clear_guild_stat(SS_OCCUP);
    TP->clear_guild_stat(SS_LAYMAN);
    TP->remove_cmdsoul("/d/Calia/guilds/scop/specials/spiritsoul");
    TP->remove_cmdsoul("/d/Calia/guilds/scop/specials/spiritlaysoul");
    TP->update_hooks();
    write_file(JOIN_LOG, TP->query_name()+" betrayed their Blessing on "+
        ctime(time()) +", losing "+xp_remove+" exp.\n");
    (SPIRIT_OBJECTS+"council_log_book")->update_log_book(my_time()+
        TP->query_name()+" betrayed their Blessing.\n");
    write("You stand defiantly and telepathically convey your thoughts "+
        "to betray your Blessing from Psuchae. You feel your heart stop. "+
        "You cannot breathe. Your eyes begin to blur and everything becomes "+
        "black. You cannot see!\nThe voice of Psuchae echoes through your "+
        "mind: \"You have chosen to betray your Blessing. As you have been "+
        "warned, I shall now remove some of that which my gifts have helped "+
        "you gain. You shall not be welcomed by an of the Elementals again. "+
        "I have removed all I have given you and I shall return what I have "+
        "taken from you. Be gone from my Temple\".\n");
    tell_room(environment(TP),QCTNAME(TP)+" leaves the guild.\n",TP);
    filter(users(), &is_spirit())->catch_msg(LEFT(TP)[0]+"\n");
    set_alarm(1.0,0.0,&grr());
    return 1;
}

int
do_pray(string str)
{
    object kneeling=present(KNEELING_OBJECT,TP);

    if (!kneeling)
    {
        NF("You must kneel before the altar to pray.\n");
        return 0;
    }

    if (!str)
    {
        NF("Pray to whom?\n");
        return 0;
    }

    if (str != "to Psuchae")
    {
        write("You pray "+str+".\n");
        return 1;
    }

    if (is_spirit(TP))
    {
        write("You pray to Psuchae. A power flows through your body.\n");
        return 1;
    }

    if (present("_schosen_",TP))
    {
        write("You pray to Psuchae. A voice echoes through your mind "+
            "saying: \"Seek me out in the Ancient City.\"\n");
        say(QCTNAME(TP)+" prays at the altar.\n");
        kneeling->remove_object();
        return 1;
    }

    write("You pray "+str+".\n");
    return 1;
}

void
init()
{
    ::init();
    add_action(do_enter,"enter");
    add_action(do_kneel,"kneel");
    add_action(do_rise,"rise");
    add_action(do_load,"load");
    add_action(do_lay,"lay");
    add_action(do_promote,"promote");
    add_action(do_betray,"betray");
    add_action(do_pray,"pray");
    add_action(do_anoint,"anoint");
}
