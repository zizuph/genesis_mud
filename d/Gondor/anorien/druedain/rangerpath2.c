/*
 *      /d/Gondor/anorien/druedain/rangerpath2.c
 *
 *      Coded by Elessar.
 *
 *      Modification log:
 *      26-Jan-1997, Olorin:    General revision.
 *      24-Aug-1997, Gnadnar:   2 minor fixes (check_awareness(string time))
 *      24-April-2004, Tigerlily: updated file references for ranger recode
 */
#pragma strict_types

inherit "/d/Gondor/std/room.c";
inherit "/d/Gondor/common/lib/friend_or_foe.c";
inherit "/d/Gondor/common/lib/herbsearch.c";

#include <filter_funs.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <config.h>     /* for OWN_STATUE */

#include "/d/Gondor/defs.h"
#include "/d/Gondor/bits.h"
#ifdef NEW_RANGERS_OPEN
#include "/d/Gondor/guilds/rangers/rangers.h"
#endif

#define AWARE_LOW        5
#define AWARE_MEDIUM        15
#define AWARE_HIGH      25
#define AWARE_TOP       40
#define TRAP_MIN        20
#define TRACK_MIN       15
#define TRACK_MEDIUM        20
#define TRACK_MAX       25

/*
 *      Prototypes:
 */
public void reset_trap();
public void create_gondor();
public void reset_room();
private string  check_awareness(string time);
public string   check_track();
public string   check_trapped();
public string   describe();
public int  free_trapped();
public int  is_weapon(object weapon);
private void    rope_cut();
private int got_weapon(object player);
public int  cut_rope(string str);
private void    get_trapped();
public int  test_trap();
private void    remove_leaves();
public int  query_trapped_today(string name);
public int  remove_trap(string str);
public int  try_remove(string str);
public string   try_search(object tp, string str);
public int  catch_all(string str);
public void rescue_the_trapped();
public void give_proof(object player) ;
public string   exa_leaves();
public string   exa_trap();
public void leave_inv(object obj, object to);
public void enter_inv(object obj, object from);
public string   exa_rope();
public string   exa_noose();
public int  hook_friend_or_foe(object pl);
public void init() ;

/*
 *      Global variables:
 */
static int     Trap,
               Leaves,
               Rescue_Alarm;
static object  Trapped;
static string *Trapped_Today = ({ }),
           Last_Trapped;

public void 
reset_trap()
{
    Trap = 1;
    Leaves = 1;
}

public void 
create_gondor()
{
    set_short("an old path in the western parts of the Druedain Forest "+
    "in Anorien");
    set_long(describe);
    reset_trap();

    add_exit(ANO_DIR + "druedain/rangerpath1", "north",         0, 1, 1);
    add_exit(ANO_DIR + "druedain/rangerpath3", "west",  test_trap, 1, 1);

    set_up_herbs( ({ HERB_DIR + "foxglove",
                     ONE_OF_LIST(HERB_MASTER->query_herbs("forest")), 
                     ONE_OF_LIST(HERB_MASTER->query_herbs("middle earth")), }),
        ({ "forest", "thicket", "bushes", }), 4);
    add_item(({"track","path"}), check_track);
    add_item("leaves", exa_leaves);
    add_item(({"noose-trap", "trap"}), exa_trap);
    add_item(({"rope"}),  exa_rope);
    add_item(({"noose"}), exa_noose);
    add_item(({"thicket","bush","bushes"}), BSN(
        "A dense thicket of thorny bushes blocks the passage to " +
            "the south and east. To the north, you can see a narrow " +
            "path running through the thicket. "));
    add_item(({"forest", "oaks","oak trees","birches", "birch trees",
                   "tree", "trees","branches"}), 
        BSN("The trees line the old path on both sides. Over your "
            + "head, their thick branches form a dense roof."));

    add_prop(ROOM_I_LIGHT,1);

    add_prop(OBJ_S_SEARCH_FUN, "try_search");
    add_prop(OBJ_I_SEARCH_TIME, 8);
}

void 
reset_room()
{
    Trapped_Today = ({ });
}

private string 
check_awareness(string time)
{
    int    skill;
    string awaretext;
    string birdtext;

    if ( time != "evening" && time != "night" )
    birdtext = "birds singing";
    else
    birdtext = "an owl hooting";

    if (TP->test_bit("Gondor", GONDOR_GROUP, RANGER_TEST_BIT) &&
        query_friend_or_foe(TP) >= 0)  
        return "You hear " + birdtext + " among the trees. ";
    if (!Leaves && Trap) 
        return "On the path to the west a noose-trap has been revealed. ";
    if (!Leaves && !Trap) 
        return "You hear " + birdtext + " among the trees. ";
    if ((skill = TP->query_skill(SS_AWARENESS)) > AWARE_LOW)
        awaretext = "The forest is silent. ";
    if (skill > AWARE_MEDIUM)
      awaretext += "This gives you an eerie feeling that something is wrong. ";
    if (skill > AWARE_HIGH)
        awaretext += "At the same time you feel as if you are being watched. ";
    if ((skill > AWARE_TOP) || (TP->query_skill(SS_FR_TRAP) >= TRAP_MIN))
        awaretext += "Something strikes you as being odd about the path. ";
    if (strlen(awaretext))
        return awaretext;
    else 
        return "";
}

public string 
check_track()
{
    int     skill = TP->query_skill(SS_TRACKING);
    string  trackdesc;

    if (TP->test_bit("Gondor", GONDOR_GROUP, RANGER_TEST_BIT) &&
        (query_friend_or_foe(TP) >= 0))
    return "From studying the track, you gather that the path has been "+
           "used recently.\n";
    if (Trap && Leaves) 
    {
        if (skill <= TRACK_MIN)
            trackdesc = "You see nothing special about the path. It looks "+
        "like the usual kind of path, covered with dry leaves "+
        "and sticks. ";
        if (skill > TRACK_MIN)
            trackdesc = "Your skilled eyes examine the track upon which "+
        "you walk. It seems as if someone has skillfully covered "+
        "it up to conceal it. ";
        if (skill > TRACK_MEDIUM)
            trackdesc += "From the tracks you gather that this path has "+
                "been used quite recently, most likely by humans. ";
        if ((skill > TRACK_MAX) || (TP->query_skill(SS_FR_TRAP) >= TRAP_MIN) || 
            (TP->query_skill(SS_AWARENESS) > AWARE_TOP))
            trackdesc += "As your trained and skilled eyes carefully study "+
        "the path, it strikes you that something might be wrong "+
        "with the leaves that cover the path a little further west.";

        return BSN(trackdesc);
    }
    else if (Trap && !Leaves) 
    {
        trackdesc = "Now that the path is cleared of leaves, it is easy "+
        "to see the trap that has been set up just to the west.";
        return BSN(trackdesc);
    }
    else if (!Trap)
        return "You don't see anything special about the path. It leads "+
        "north and west.\n";
    return "";
}

public string 
check_trapped()
{
    if (objectp(Trapped) && (TP != Trapped))
        return Trapped->query_Art_name(TP)+" is hanging upside down, with "+
            Trapped->query_possessive()+" feet stuck in the noose of a rope. ";
    if (Trapped == TP)
        return "You are seeing everything upside down, since you are "+
        "hanging with your feet stuck in a noose from one of the trees. ";
    else 
        return "";
}

public string
describe()
{
    string  time  = tod(),
            long_descf = "You are on an old path in the western parts "
        + "of the Druedain Forest, in southern Anorien. "; 

    switch (time)
    {
    case "evening":
    case "night":
        long_descf += "It is currently quite dark in the forest, "
            + "since it is " + time + ", and the great trees do not "
            + "let much light through their crowns. ";
        break;
    default:
        long_descf += "You see rays of light coming through the "
            + "ceiling of leaves above you, as the sun shines on the "
            + time + " sky. ";
        break;
    }

    long_descf += "Oaks and birch trees line the old path on both sides. "+
        "Their thick branches are tangled together over your head, now "+
    "almost forming a tunnel through which you are walking. The old "+
    "path runs north through a thicket of bushes and trees, while it "+
    "turns towards the west here. ";
    if (Trap)
        long_descf += check_awareness(time);
    long_descf += "The forest looks too dense to walk through to the "+
        "east and to the south. ";
    long_descf += check_trapped();
    return BSN(long_descf);
}

public int 
free_trapped()
{
    if (!objectp(Trapped))
        return 0;
    if (TP == Trapped) 
    {
        write("You can't free yourself just like that! You'll either have "+
        "to get someone else to free you, or cut the rope yourself.\n");
    }
    else
        write("You'll have to cut the rope with a knife or something.\n");
    return 1;
}

public int 
is_weapon(object weapon)
{
    if (!objectp(weapon))
        return 0;
    if (!weapon->check_weapon())
        return 0;
    if (weapon->query_wielded() != TP)
        return 0;
    return (weapon->query_dt() & W_SLASH);
}

private void
rope_cut()
{
    if (!objectp(Trapped))
        NFN0("What rope?");
    remove_alarm(Rescue_Alarm);
    Rescue_Alarm = 0;
    if (Trapped != TP) 
    {
        TP->catch_msg("You successfully cut the rope, and "+QCTNAME(Trapped)+
            " falls to the ground.\n");
        Trapped->catch_msg(QCTNAME(TP)+
        " cuts the rope around your feet, and suddenly!\n"+
            "THUMP! you find yourself sitting on the ground, with "+
        "a headache.\n");
        say(QCTNAME(TP)+" cuts the rope around "+QTNAME(Trapped)+"'s feet.\n"+
            QCTNAME(Trapped)+" falls down THUMP! on "+
        Trapped->query_possessive()+" head!\n", ({ Trapped, TP }) );
    }
    else
    {
        write("You successfully cut the noose around your feet, and fall "+
        "on your head.\n"+
            "OUCH! That hurt!\n");
        say(QCTNAME(Trapped)+" cuts the rope around "+
        Trapped->query_possessive()+
            " own feet, \n and falls THUMP! down on "+
        Trapped->query_possessive()+" head!\n",Trapped);
    }
    Last_Trapped = "";
    Trapped = 0;
    return;
}

private int 
got_weapon(object player)
{
    mixed  *items;
    int     n = -1;

    if (!objectp(player))
        return 0;
    if (!sizeof(items = player->query_weapon(-1)))
    return 0;

    while (++n < sizeof(items)) 
    {
        if (items[n]->query_dt() & W_SLASH) 
            return 1;
    }
    return 0;
}

public int 
cut_rope(string str)
{
    string  what,
            wep;

    if (!strlen(str))
        NFN0("Cut what?");

    if (sscanf(str,"%s with %s", what, wep) == 2) 
    {
        if ((what !="rope") && (what != "noose"))
            NFN("Cut what?");
        else if (objectp(present(wep, TP))) 
        {
            if (is_weapon(present(wep, TP))) 
            {
                rope_cut();
                return 1;
            }
            NFN("You are not wielding any " + wep + ".");
        }
    else
        NFN("You do not have any " + wep + ".");
    return 0;
    }


    if ((str == "rope") || (str == "noose"))
    {
        if (!got_weapon(TP)) 
        {
            write("You are not wielding anything sharp enough to cut with!\n");
            say(QCTNAME(TP)+
                " tries to cut the rope, but has no weapon to cut with.\n",TP);
            return 1;
        }
        rope_cut();
        return 1;
    }
    return 0;
}

private void 
get_trapped()
{
    string  name = TP->query_real_name();

    Last_Trapped = "";
    Trapped = TP;
    if (!pointerp(Trapped_Today) || !sizeof(Trapped_Today))
        Trapped_Today = ({ });
    Trapped_Today += ({name});
    WRITE("As you continue west, you feel your left foot touching "+
    "something. Suddenly, the world is upside down - or maybe you are? "+
    "Something sits very tight around your feet, and as blood rushes "+
    "to your head, you realise you have walked right into a simple "+
    "noose-trap!");
    SAY(" is suddenly caught in a noose-trap, and pulled up "+
        "into the air upside down!");
    Trap = 0;
    Leaves = 0;
    if (query_friend_or_foe(TP) > -1)
        Rescue_Alarm = set_alarm(120.0 + rnd()*40.0, 0.0, rescue_the_trapped);
    log_file("traps", TP->query_name()+
    " went in the Rangers' trap in Druedain Forest, "
        + ctime(time())+".\n", 0);
    add_action(catch_all, "", 1);
    return;
}

public int 
test_trap()
{
    if (this_player()->query_wiz_level())
        return 0;
    if (TP->query_npc()) 
        return 0;
    if (TP->test_bit("Gondor", GONDOR_GROUP, RANGER_TEST_BIT) &&
        (query_friend_or_foe(TP) >= 0)) 
    {
        write("You walk along the path towards the west.\n");
        return 0;
    }
    if (Trap) 
    {
        get_trapped();
        return 1;
    }
    write("You walk along the path towards the west.\n");
    return 0;
}

private void
remove_leaves()
{
    if (TP == Trapped)
    {
        write(BSN("You are hanging with your feet stuck in a noose from "+
        "one of the trees. You cannot reach the path to "+query_verb()+
        " the leaves."));
    }
    else if (TP->test_bit("Gondor", GONDOR_GROUP, RANGER_TEST_BIT) &&
        (query_friend_or_foe(TP) >= 0) && Leaves)  
    {
        write("You do not have to do that; you have already done "+
        "this test!\n");
    }
    else if (!Leaves) 
    {
        write("The path has already been cleared of leaves.\n");
    }
    else if (!Trap) 
    {
        write("You clear away the leaves from the path. You do not find "+
        "anything.\n");
        say(QCTNAME(TP)+" clears away the leaves from the path, "+
            "but discovers nothing underneath.\n",TP);
    }
    else
    {
        write("You clear away the leaves from the path. Under the cover "
            + "of leaves you discover a trap!\n");
        say(QCTNAME(TP)+" clears away the leaves from the path, and "
            + "reveals a trap!\n"); 
        Leaves = 0;
    }
}


public int 
query_trapped_today(string name)
{
    return (member_array(LOW(name), Trapped_Today) >= 0);
}

public int 
remove_trap(string str)
{
    if (!strlen(str) || (str != "trap"))
    {
        NFN(CAP(query_verb()) + " what?");
        return 0;
    }
    
    if (TP->test_bit("Gondor", GONDOR_GROUP, RANGER_TEST_BIT) &&
        (query_friend_or_foe(TP) >= 0) && Trap) 
        write("Sorry - as you have done this earlier, you're not allowed "+
        "to do it again.\n");
    else if (Leaves) 
        write("You cannot see any trap here!\n");
    else if (!Trap) 
        write("There is no trap here!\n");
    else
    {
        WRITE("As the trap is just a simple one, with a rope put out as "+
        "a noose, you have no trouble disarming and removing the trap.\n");
        say(QCTNAME(TP)+" disarms and removes the noose-trap.\n");
        Trap = 0;
        if (!query_trapped_today(TP->query_real_name()))
            set_alarm(4.0, 0.0, &give_proof(TP));
    }
    return 1;
}

public int 
try_remove(string str)
{
    string  s1,
            s2;

    if (!strlen(str))
        return 0;

    if (str == "leaves") 
        remove_leaves();
    else if (str == "trap")
        remove_trap("trap");
    else if (sscanf(str, "%s lea%s", s1, s2) > 0) 
        remove_leaves();
    else if (sscanf(str, "%srap %s", s1 ,s2) > 0) 
        remove_trap("trap");
    else
        return 0;
    return 1;
}

public string
try_search(object tp, string str)
{
    string tmpstr;
    if (parse_command(LOW(str), ({}), "'leaves' %s", tmpstr) &&
    (!strlen(tmpstr) ||
     parse_command(tmpstr, ({}), "[for] [noose] / [trap] / [rope]")))
    {
    remove_leaves();
    }
    return "";
}

public int 
catch_all(string str)
{
    string  vb = query_verb();

    if (TP != Trapped) 
        return 0;
    
    switch (vb)
    {
    case "north":
    case "northeast":
    case "northwest":
    case "southwest":
    case "southeast":
    case "west":
    case "up":
    case "down":
    case "south":
    case "east":
    case "search":
        WRITE("You are hanging upside down, with your feet stuck in a "+
        "noose, so that is quite impossible.");
        return 1;
        break;
    case "commune":
        if (query_friend_or_foe(TP) <= -1)
    {
            write("Nope. You are trapped. Now figure out a way to get "+
        "loose.\n");
            return 1;
    }
    write("Why be so pessimistic? There are ways out of this....\n");
    return 1;
    break;
    case "quit":
        if (query_friend_or_foe(TP) == -1)
            return 0;
        write("Don't be so pessimistic! Hang on - something might happen!\n");
        return 1;
        break;
    default:
        return 0;
    }
}

public void 
rescue_the_trapped()
{
    Rescue_Alarm = 0;

    if (!objectp(Trapped))
        return 0;

    if (ENV(Trapped) != TO) 
    {
    Last_Trapped = "";
        Trapped = 0;
        return;
    }
    tell_room(TO,"Suddenly, two rugged Rangers step onto the path "+
    "from between the trees. ");
    tell_object(Trapped,
        "One of them silently takes hold under your arms, while the "+
        "other swiftly opens the noose around your feet. Then they put "+
        "you down, grin at you, and step away from the path into the "+
        "shadows again. But before the last Ranger leaves, he says: "+
        "'You'd better turn back again, "+
            Trapped->query_race_name()+".'");
    tell_room(TO,
    "One of them silently takes hold under "+QTNAME(Trapped)+"'s arms\n"+
    "while the other swiftly removes the rope and noose. Then they put\n"+
        QTNAME(Trapped)+" down again, grin at "+Trapped->query_objective()+
        ", and step away\n"+
        "from the path into the shadows again.\n", Trapped);
    Last_Trapped = "";
    Trapped = 0;
    return;
}

public void 
give_proof(object player) 
{
    object  note;
    if (query_friend_or_foe(player) <= -1) 
        return;
    tell_object(player,"Suddenly a pigeon flies in, delivering you a note.\n");
    tell_room(ENV(player),
        "Suddenly a pigeon flies in, delivering a note to "+
        QTNAME(player)+".\n",player);

#ifndef NEW_RANGERS_OPEN
    note = clone_object(RANGER_DIR + "proofnote");
#endif

#ifdef NEW_RANGERS_OPEN
    note = clone_object(RANGERS_OBJ + "proofnote"); 
#endif

    note->set_playername(player->query_name());
    note->move(player);
    tell_room(ENV(player),"The white pigeon flies away again.\n");
    return;
}

public string 
exa_leaves()
{
    if (Leaves && Trap) 
    return BSN("There are both dry and fresh oak leaves covering parts "+
        "of the path here. Something strikes you as odd about "+
        "them though.");
    if (Leaves && !Trap) 
    return BSN("There are both dry and fresh oak leaves scattered "+
        "about on the path. They don't look interesting. ");
    if (!Leaves) 
    return "There are dry leaves on both sides of the path, "+
        "but none upon it.\n";
}

public string 
exa_trap()
{
    if (Leaves) 
      return "You don't see any traps here.\n";
    if (Trap && !Leaves) 
    return BSN("The trap is a really simple one, consisting of a noose "+
        "lying on the ground, in the end of a long rope, which is "+
        "carefully camouflaged along a tree. The trap seems to be "+
        "designed in the way that a person stepping inside the noose "+
        "would trigger it, and be pulled up in the air by a foot or "+
        "two. It looks easy to disarm and remove.");
    if (Trapped && Trapped==TP)
    return BSN("Your feet are stuck in the tightened noose in the end "+
        "of the rope. Your only way to get out would be by cutting "+
        "the rope.");
    if (Trapped) 
    return Trapped->query_The_name(TP)+
        " is swinging by "+Trapped->query_possessive()+
            "feet in the noose-trap.\nYou will have to cut the rope to free "+
        Trapped->query_objective()+" from the trap.\n";
    if (!Trap && !Leaves) 
    return "You don't see any traps here.\n";
}

public void 
leave_inv(object obj, object to)
{
    ::leave_inv(obj, to);

    if (!objectp(obj) || !living(obj))
        return;
    if (obj == Trapped)
    {
        Trapped = 0;
    if ( !strlen(query_verb()) )
        /* ahhh, escaping trap by going netdead ... */
        Last_Trapped = obj->query_real_name();
    }

    if (!sizeof(FILTER_PLAYERS(all_inventory(TO) - ({ obj }))))
        reset_trap();
}

public void
enter_inv(object obj, object from)
{
    object tp;
    string name;

    ::enter_inv(obj, from);

    if (objectp(Trapped) || !objectp(obj) || !living(obj) || !objectp(from))
        return;

    if ((name = obj->query_real_name()) == Last_Trapped &&
    file_name(from) == OWN_STATUE)
    {
    log_file("traps", name+
        " returned to the Rangers' trap in Druedain Forest, "
            + ctime(time())+".\n", 0);
    Last_Trapped = "";
    Trapped = obj;
    Leaves = 0;
    Trap = 0;
    if (!pointerp(Trapped_Today) || !sizeof(Trapped_Today))
            Trapped_Today = ({ });
    Trapped_Today += ({name});

        /* be sure the trapped player is this_player
         * before doing add_action
         */
        if ( (tp = TP) != obj )
            set_this_player(obj);
        add_action(catch_all, "", 1);
        if ( tp != obj )
            set_this_player(tp);
    }
}

public string 
exa_rope()
{
    if (!objectp(Trapped))
        return "You find no rope.\n";

    return "It's a thick rope. with a noose at the end.\n";
}

public string 
exa_noose()
{
    if (!objectp(Trapped))
        return "You find no noose.\n";

    return "The end of the rope has been formed into a noose.\n";
}

public int 
hook_friend_or_foe(object pl)
{
#ifndef NEW_RANGERS_OPEN
    if ((R_OUTLAW)->query_outlaw(pl->query_real_name()))
        return -1;
#endif

#ifdef NEW_RANGERS_OPEN
    if ((MANAGER)->query_is_outlaw(pl->query_real_name()))
        return -1;
    if ((MANAGER)->query_notorious_outlaw(pl->query_real_name()))
        return -1;
#endif

    return 0;
}

public void 
init() 
{
    ::init();

    add_action(try_remove,   "remove");
    add_action(try_remove,   "move");
    add_action(try_remove,   "clear");
    add_action(remove_trap,  "untrap");
    add_action(remove_trap,  "disarm");
    add_action(cut_rope,     "cut");
    add_action(free_trapped, "free");
}

