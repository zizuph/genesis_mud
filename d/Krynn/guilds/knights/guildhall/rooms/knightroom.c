/* Vingaard Keep coded by Percy.
 * Knight room, Vingaard Keep coded by Percy.
 *                updated: 04/10/94 by Grace.
 *                degrading commands added 07/12/94 by Aridor
 *                degrading removed again 01/29/95 by Aridor
 *                conclave_cmd object added 01/29/95 by Aridor
 *                modified 01/97 by Teth and Morrigan
 */

#include <ss_types.h>
#include <macros.h>
#include <std.h>
#include <cmdparse.h>
#include <composite.h>    
#include <filter_funs.h>                 /* filter functions */          
#include "../../guild.h"

inherit IN_BASE;
inherit RECRUIT_BASE

#define     IS_SITTING       "_player_i_is_sitting"
#define     SIT_SUBLOC       "_subloc_sitting"                          

/*prototype*/
void load_board();

string first, second, sec, fir;
int succ_alrm;

void
create_vin_room()
{
    string str;

    set_army("Knights");

    set_short("Knight room");
    set_long("You are in the Knights room, a large triangular " +
        "chamber with a vaguely festive atmosphere. " +
        "Pennants hang from the ceiling, walls, and " +
        "between high, narrow windows. A poster hangs on " +
        "one of the walls. Cushioned benches " + 
        "provide comfortable seating for those wishing to " +
        "discuss guild matters or swap war-stories over a " +
        "cup of beer from the nearby inn. There are " +
        "three statues, one in each corner of the room. " +
        "There is a sign here, and under the sign hangs a " +
        "parchment scroll. A treasure chest has been set " +
        "up here.");

    AI(({"treasure chest","chest",}),
        "This is a solid treasure chest to keep money in. It is possible " +
        "to 'raise' funds here for the recruitment of guards which must be " +
        "paid their expenses for guarding territory which has been 'conquer'ed " +
        "and/or which is under control " +
        "of the knighthood. Every knight who has money which exceeds his " +
        "or her living needs is asked to contribute to the 'funds'. It is up to the " +
        "Conclave of the Knights to distribute the money.\n\nThis system is " +
        "still in the testing phase.\n");
    AI("book","The label of the book says: 'Private Conclave Log'.\n");
    AI(({"scroll", "parchment", "parchment scroll"}),
        "The parchment scroll is labelled: Private Conclave Log.\n");
    AI("poster","It is rolled up and sealed. A conclave member may " +
        "open it and present it to someone though.\n");
    AI("sign", "This sign looks interesting. Perhaps you should read " +
        "it?\n");
    AI("pennants", 
        "They are the flags of conquered enemies,\n" +
        " the war-trophies of victorious knights.\n");
    AI("pennant", 
        "The flag of a conquered enemy, brought home\n" +
        " to Vingaard by a victorious knight.\n");   
    ACI("pennant", "get", "It is out of your reach.\n");
    AI("walls", "Made of the same stone as the rest of the Keep," +
        " and re-assuring in their solidity.\n");
    AI("wall", "Made of the same stone as the rest of the Keep," +
        " and re-assuring in its solidity.\n"); 
    AI("windows", "Set very high into the walls, they allow light to " +
        "enter the room during the day.\n");   
    AI("window" , "It is set very high in the wall, you can see only " +
        "a small bit of sky, or that may be your imagination.\n");
    AI("floor","The floor is made of stone.\n");
    AI(({"stone"}),"Typical and solid, it is granite.\n");
    AI("ceiling", "It is supported by broad beams.\n");
    AI("beams", "They support the ceiling. Pennants hang from them.\n");
    AI(({"wood","dark wood"}),"It is most likely black walnut.\n");
    AI("cushion", "It is slightly faded and worn by years of use.\n");
    AI(({"bench","cushioned bench"}), "Made of dark wood and covered " +
        "with a cushion.\n");
    AI(({"benches","cushioned benches"}),"Made of dark wood and covered "+
        "with a cushion.\n");
    AI("statues", "There are three of them, one a dragon, one a " +
        "minotaur, and one a bird.\n");
    AI("dragon", 
        "A rendering of one of the chosen forms of Paladine, this is" +
        " an exquisitely-cast sculpture of a platinum dragon with one" +
        " claw clenching the base of the pedestal and the other a " +
        "rose.\n");
    AI("minotaur",
        "This statue is carved from a single piece of red-brown " +
        "jasper.\n" +
        " Its likeness is that of an avatar of Kiri-Jolith, a huge" +
        " bison-headed human wielding a large, two-handed sword.\n");
    AI("bird",
        "A carving of the favoured shape of Habbakuk, this kingfisher " +
        "bird is made of incredibly blue lapis-lazuli. Upon its head" +
        " rests a miniature golden crown.\n");
    AE(VROOM + "north_hallway", "west", 0);

    add_my_desc("@@chair_desc@@", TO);
    
    seteuid(getuid(TO));
    load_board();
}


/* This loads the main knight bulletin board */
void
load_board()
{
    clone_object(VOBJ + "knboard")->move(this_object());
    clone_object(VOBJ + "opinion_box")->move(this_object());
}

void
init()
{
    ::init();
    ADA("read");
    ADA("query");
/*
    ADA("promote"); moved to conclave object by Morrigan 2/2004
    ADA("demote");
    ADA("resign");
    ADA("successor");
*/
    ADD("leave", "leave!");
    ADD("present_poster_to","present");
    ADD("open_poster","open");
    ADD("do_sit", "sit");
    ADD("do_rise", "rise");
    ADD("do_rise", "stand"); 
    
    init_recruit();

    set_alarm(0.1,0.0,"do_write_welcome",TP);
}

void
do_write_welcome(object who)
{
    int a = (ADMIN)->check_can_perform_command(who);
    object p = P(CONCLAVE_OBJ, who);
    mixed c = !p;
    if (c && a)
    {
        who->catch_msg("In this room you have access to the conclave " +
            "command object. Examine it to see your commands. " +
            "If you have problems, suggestions or " +
            "improvements, contact the GuildMaster.\n");
        clone_object(CONCLAVE_CMD)->move(who,1);
    }
}

int
leave(string str)
{
    write("Sorry, but you may not use that command in this room.\n");
    return 1;
}

/* reads the sign about the various commands here */
int
read(string str)
{
    NF("Read what?\n");
    if (str == "book" || str == "degradation book" ||
	str == "degrade" || str == "degradation" ||
        str == "parchment scroll" || str == "parchment" || str == "log"
        || str == "degrading" || str == "scroll")
    {
        return (ADMIN)->log_available_for_all_conclaves();
    }

    if (str == "sign")
    {
        write("In this room you may type 'query' to get a list of\n" +
            "the current conclave members for the different Knight\n" +
            "orders.\n" +
            "Conclave members can also\n" +
            "'promote <player> to crown|sword|rose conclave' or\n" +
            "'demote <player> from crown|sword|rose conclave'.\n" +
            "Demotion will also work for the Grand Master.\n" +
            "Conclave members can also use this room to leave the\n" +
            "conclave simply by typing 'resign'. Additionally, a\n" +
            "conclave member may use the 'successor <player>'\n" +
            "command to select their successor as conclave. This\n" +
            "is only valid with a subsequent 'resign' command.\n" +
		
            "Conclave members and assistants get a separate command\n" +
            "object which will list the commands by looking at it.\n" +
            "The Private Conclave Log can be read here, too.\n" +
            "");
        return 1;
    }
    return 0;
}

int
open_poster(string str)
{
    string whoname;
    object who;

    NF("What?\n");
    if (str != "poster")
        return 0;

    NF("You cannot open the poster!\n");
    if (TP->query_knight_sublevel() != 11)
        return 0;

    write("Just present the poster to someone.\n");
    return 1;
}

int
present_poster_to(string str)
{
    string whoname;
    object who;

    NF("Present what to who? The poster maybe?\n");
    if (!str)
        return 0;
    if (sscanf(str,"poster to %s",whoname) != 1)
        if (sscanf(str,"the poster to %s",whoname) != 1)
            return 0;

    NF("You cannot open the poster!\n");
    if (TP->query_knight_sublevel() != 11)
        return 0;

    who = find_player(whoname);
    if (!who || E(who) != TO)
    {
        NF(C(whoname) + " is not in this room!\n");
        return 0;
    }
    write("You open the poster and present it to " + C(whoname) + ".\n");
    tell_room(QCTNAME(TP) + " unrolls a poster and presents it to " +
        QCTNAME(who) + ".\n", who);
    who->catch_msg("On the poster you can read the following text:\n\n" +
        " Let Ye be tested by the measure and by the oath,\n" +
        "  Findeth three items that represent the Knights.\n" +
        "                One for each order,\n" +
        "        Thee have the choice and the ardour,\n" +
        /*		"                  One of mithril,\n" +
                        "                 The other of gold,\n" +
                        "       Whereas the third is of the purest red.\n" +*/
        "  The reward may be obtained by one of the Conclave.\n" +
        "        Be cautious, Thee have been warned,\n" +
        "long will be thou travels and many dangers lies ahead.\n" +
        "       May Paladine's Grace shine upon Thee,\n" +
        "   Let the Knights' Honor be your road companion.\n" +
        "         and Thou shalt return in glory!\n");
    write("Afterwards, you roll the poster back up.\n");
    return 1;
}

/* querys the existing conclave members */
int
query(string str)
{
    string crown, sword, rose, grandm;
    
    crown = (ADMIN)->query_conclave("crown");
    sword = (ADMIN)->query_conclave("sword");
    rose = (ADMIN)->query_conclave("rose");
    grandm = (ADMIN)->query_grandmaster();
    
    if (crown == "")
        write("There is currently no Conclave member for the Crown order.\n");
    if (crown != "")
        write(crown + " is the Conclave member for the Crown order.\n");
    if (sword == "")
        write("There is currently no Conclave member for the Sword order.\n");
    if (sword != "")
        write(sword + " is the Conclave member for the Sword order.\n");
    if (rose == "")
        write("There is currently no Conclave member for the Rose order.\n");
    if (rose != "")
        write(rose + " is the Conclave member for the Rose order.\n");
    if (!grandm || grandm == "")
        write("There is currently no Grand Master of the Knights.\n");
    if (grandm && grandm != "")
        write(C(grandm) + " is the Grand Master of the Knights.\n");

    return 1;
}


int
promote(string str)
{
    if (member_array(TP->query_name(),GUILDMASTERS) == -1 && 
	TP->query_knight_sublevel() != 11)
    {
	write("You have no such power!\n");
	return 1;
    }

    return (ADMIN)->do_promote(str);
}

int
demote(string str)
{
    if (member_array(TP->query_name(),GUILDMASTERS) == -1 && 
	TP->query_knight_sublevel() != 11)
    {
	write("You have no such power!\n");
	return 1;
    }
    
    return (ADMIN)->do_demote(str);
}


#if 0
/* allows a player to be promoted to the conclave */
int
promote(string str)
{
    int lvl;
    object ob;
    string crown, sword, rose;
    
    crown = (ADMIN)->query_conclave("crown");
    sword = (ADMIN)->query_conclave("sword");
    rose = (ADMIN)->query_conclave("rose");
    
    NF("Promote who?\n");
    if (member_array(TP->query_name(),GUILDMASTERS) == -1 && 
	TP->query_knight_sublevel() != 11)
    {
        write("You have no such power!\n");
        return 1;
    }
    if (!str)
        return 0;
    if (ob = find_player(lower_case(str)))
    {
        lvl = ob->query_knight_level();
        if (lvl < 3)
        {
            write("This player is not a member of a knight order!\n");
            return 1;
        }
        if (ob->query_knight_sublevel() == 11)
        {
            write("This player is already a Conclave member!\n");
            return 1;
        }
        if (lvl == 3 && crown != "")
        {
            write("There is already an existing Crown member!\n");
            return 1;
        }
        if (lvl == 4 && sword != "")
        {
            write("There is already an existing Sword member!\n");
            return 1;
        }
        if (lvl == 5 && rose != "")
        {
            write("There is already an existing Rose member!\n");
            return 1;
        }
        if ((first != ob->query_name() || fir == TP->query_name()) &&
            !TP->query_wiz_level())
        {
            first = ob->query_name();
            fir = TP->query_name();
            write("You have nominated the player he/she still requires " +
                "another nomination.\n");
            return 1;
        }
        first = "";
        fir = "";
        write("Ok.\n");
        ob->set_high(lvl);
        write("Ok.\n");
        return 1;
    }
    return 0;
}
#endif

/* reset the temporarily changed successor of the conclave */
void
reset_default_conclave_successor(object who, int order, int pres, string player)
{
    if (order == 3) /* crown */
        (ADMIN)->set_crown_high(pres, player);
    else if (order == 4) /* sword */
        (ADMIN)->set_sword_high(pres, player);
    else if (order == 5) /* rose */
        (ADMIN)->set_rose_high(pres, player);
    else 
        return;
    if (E(who) == TO)
        who->catch_msg("Your successor has been set back to the default again!\n");
    succ_alrm = 0;
}

/*allows a conclave to name his/her successor in the position */
int
successor(string str)
{
    int lvl;
    object who;
    int tmppres;
    string tmpplayer;
    if (TP->query_knight_sublevel() != 11)
    {
        NF("You are not a Conclave member!\n");
        return 0;
    }
    NF("This command is currently not possible!\n");
    if ("/secure/armageddon"->shutdown_active())
        return 0;
    who = find_player(str);
    NF("The player must be present in this room.\n");
    if (!who || E(who) != E(TP))
        return 0;
    lvl = TP->query_knight_level();
    NF("The player must be of the same order as you.\n");
    if (lvl != who->query_knight_level())
        return 0;
    NF("Your successor must have enough prestige to become Conclave.\n");
    if (who->query_level_up(who->query_skill(SS_PRESTIGE_ST)) < 11)
        return 0;
    NF("Failed to set your successor.\n");
    if (lvl == 3) /* crown */
    {
        tmppres = (ADMIN)->crown_highest();
        tmpplayer = (ADMIN)->query_crown_high();
        (ADMIN)->set_crown_high(99999999, C(str));
    }
    else if (lvl == 4) /* sword */
    {
        tmppres = (ADMIN)->sword_highest();
        tmpplayer = (ADMIN)->query_sword_high();
        (ADMIN)->set_sword_high(99999999, C(str));
    }
    else if (lvl == 5) /* rose */
    {
        tmppres = (ADMIN)->rose_highest();
        tmpplayer = (ADMIN)->query_rose_high();
        (ADMIN)->set_rose_high(99999999, C(str));
    }
    else
        return 0;
    succ_alrm = set_alarm(150.0, 0.0, "reset_default_conclave_successor",
        TP, lvl, tmppres, tmpplayer);
    write("You have selected " + C(str) + " to be your successor as conclave.\n" +
        "Issuing the 'resign' command within the next 2 minutes will prefer your " +
        "choice over the default successor.\n");
    say(QCTNAME(TP) + " has selected " + C(str) + " as successor in the Conclave.\n");
    return 1;
}

/* allows a player to resign from the conclave */
int
resign(string str)
{
    if (TP->query_knight_sublevel() != 11)
    {
        NF("You are not a conclave member!\n");
        return 0;
    }
    if ((ADMIN)->is_grandmaster(TP->query_name()))
    {
	(ADMIN)->remove_grandmaster();
	return 1;
    }
    TP->clear_high(TP->query_knight_level());
    if (succ_alrm)
    {
        remove_alarm(succ_alrm);
        succ_alrm = 0;
        all_inventory(TO)->change_prestige(0,0);
    }
    return 1;
}

#if 0
/* allows a player to be demoted from the conclave/grandmaster */
int
demote(string str)
{
    string order;
    object ob;
    string crown, sword, rose, grandm;
    string nm = C(L(str));
    
    crown = (ADMIN)->query_conclave("crown");
    sword = (ADMIN)->query_conclave("sword");
    rose = (ADMIN)->query_conclave("rose");
    grandm = (ADMIN)->query_grandmaster();
    
    NF("Demote who?\n");
    if (member_array(TP->query_name(),GUILDMASTERS) == -1 && 
	TP->query_knight_sublevel() != 11)
    {
        write("You have no such power!\n");
        return 1;
    }
    if (!str)
        return 0;
    if (nm == crown)
        order = "crown";
    else if (nm == sword)
        order = "sword";
    else if (nm == rose)
        order = "rose";
    else if (L(nm) == grandm)
        order = "grandmaster";
    if (order)
    {
        if ((second != nm || sec == TP->query_name()) &&
            !TP->query_wiz_level())
        {
            second = nm;
            sec = TP->query_name();
            write("You have nominated the player for demotion he/she " +
                "still requires another nomination.\n");
            return 1;
        }
        second = "";
        fir = "";
	  
        if (order == "grandmaster")
	    (ADMIN)->remove_grandmaster();
        else
	    (ADMIN)->remove_conclave(order);
        write("Ok.\n");
        return 1;
    }
    return 0;
}
#endif

/*remove the conclave_obj when leaving the room.*/
void
leave_inv(object ob, object to)
{

    object ccmd = P(CONCLAVE_OBJ, ob);
    if (TP->query_prop(IS_SITTING))
    {
        TP->remove_prop(IS_SITTING);
        TP->remove_subloc(SIT_SUBLOC);
    }
    if (ccmd)
    {
        ccmd->remove_object();
        ::leave_inv(ob, to);
    }
}

/* 
 * Code for chairs
 */
nomask static int
do_sit(string str)
{
    object *pl;
    int i;

    pl = FILTER_CAN_SEE(FILTER_LIVE(all_inventory()), this_player());
    pl = filter(pl, "filter_sitting_in_chair", this_object());

    NF("Sit where?\n");
    if (str && str != "bench" && str != "on bench" &&
        str != "on cushioned bench" && str != "down" &&
        str != "cushioned bench")
        return 0;

    NF("You cannot sit on the bench in two places!\n");
    if (TP->query_prop(IS_SITTING))
        return 0;
    else
    {
        TP->add_prop(IS_SITTING, 1);
        write("You sit on one of the cushioned benches.\n");
        say(QCTNAME(this_player()) + " sits on one of the cushioned benches" +
            ".\n");
    }
    TP->add_subloc(SIT_SUBLOC, this_object());
    return 1;
}        
nomask static int
do_rise(string str)
{

    NF("Rise from where?\n");
    if (str && str != "bench" && str != "from bench" &&
        str != "cushioned bench" && str != "from cushioned bench")
        return 0;

    NF("You are already standing.\n");
    if (!TP->query_prop(IS_SITTING))
        return 0;

    else
    {
        TP->remove_prop(IS_SITTING);
        /*this_player()->unset_no_show_composite();*/
        TP->remove_subloc(SIT_SUBLOC);
        write("You get up from the bench.\n");         
        say(QCTNAME(this_player()) + " gets up from the bench.\n");
    }
    return 1;
}


static int
filter_sitting_in_chair(object pl)
{
    return pl->query_prop(IS_SITTING) == 1;
}

static int
filter_remove_sit(object pl)
{
    /*pl->unset_no_show_composite();*/
    return 1;
}

static int
filter_add_sit(object pl)           
{
    /*pl->set_no_show_composite(1);*/
    return 1;
}

static string
map_live(object pl)
{
    if (pl == this_player())
        return "you";
    return pl->query_the_name(this_player());
}

nomask string
chair_desc()
{
    object *pls;
    string *who, str = "";
    int i;

    pls = FILTER_CAN_SEE(FILTER_LIVE(all_inventory()), TP);           
    pls = filter(pls, "filter_sitting_in_chair", this_object());
    filter(pls, "filter_remove_sit", this_object());

    who = map(pls, "map_live", this_object());
    filter(pls, "filter_add_sit", TO);
    if (sizeof(pls) == 1 && pls[0] == TP)
        str += " You are sitting on one of the benches.";
    else if (sizeof(pls) > 1)
        str += " " + capitalize(COMPOSITE_WORDS(who)) +
            " are sitting on some of the benches.";

    else if (sizeof(pls))
        str += "" + capitalize(COMPOSITE_WORDS(who)) +
            " is sitting on a bench.";

    str += "\n";
    return break_string(str, 70); 
}

nomask string
show_subloc(string subloc, object on, object for_pl)
{
    string str;

    if (on->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS) ||
        subloc != SIT_SUBLOC)
        return "";
    if (for_pl == on)
        str = "You are";
    else
        str = capitalize(on->query_pronoun()) + " is";
}                                











