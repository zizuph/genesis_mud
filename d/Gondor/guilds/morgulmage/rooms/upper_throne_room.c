/*
 * The throne room of the Lord of Morgul in the Society of Morgul Mages
 *
 * Based on the work of Olorin, Gorboth, Chmee and Toby.
 *
 * Moved to the new guild directory and extracted the administrative 
 * functions into the master object and a seperate command object.
 * Eowul, July 2009
 */

#pragma no_inherit
#pragma save_binary
#pragma strict_types2

#include <composite.h>
#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/guilds/morgulmage/morgulmage.h"

inherit "/d/Gondor/morgul/tower/tower.c";
inherit "/d/Gondor/common/lib/tail.c";

// Prototypes
public int block_non_nazgul();
public string list_records();
public string list_complaints();
public string list_mages();

public void create_morgul_tower_room()
{
    set_level( 5 );
    set_room_type( "large hall" );
    set_extra_long( "This is the throne room of the Lord of Morgul, First "
      + "Servant of Sauron, Lord of the Nazgul. In this room the Nazgul "
      + "discuss the future of the Society of the Morgul Mages and other "
      + "such matters. Prominent in the room is the throne of the King; "
      + "behind it the Kings cabinet. There is a bulletin board bolted on "
      + "the wall. Next to the board is a plaque with a list of all "
      + "Servants of the Dark Lord; below it is a small desk on which the "
      + "warden deposits reports that he receives from members of the "
      + "Society. On the other side of the board there is a scroll on "
      + "which the Nine keep some records. Standing in front of the wall "
      + "opposite of the board is a chest. A doorway to the north leads "
      + "back into the staircase at the centre of the tower, a second one "
      + "south into the library of the Nazgul." );

    add_exit( "tower_5c", "north", 0, 0 );
    add_exit( "nazgul_library", "south", block_non_nazgul, 0 );

    add_prop( ROOM_I_LIGHT, 1 );
    add_prop( ROOM_I_NO_CLEANUP, 1 );

    add_walls();
    add_floor();
    add_roof();
    
    add_item( ({ "plaque", "list" }), list_mages );
    add_cmd_item( ({ "plaque", "list" }), "read", list_mages );

    add_item( ({ "scroll", "records" }), list_records );
    add_cmd_item( ({ "scroll", "records" }), ({ "read", "tail" }),
        list_records );

    add_item( ({ "reports", "desk" }), list_complaints );
    add_cmd_item( ({ "reports" }), ({ "read", "tail" }), list_complaints );

    add_item( ({ "throne", "dais" }),
        "A black throne is raised on a dias, looking down at the doorway. "+
        "The throne is hewn from dark rock. On the sides are many bas "+
        "reliefs carved into the stone, depicting scenes of the First "+
        "Age of Middle Earth. Behind the throne is the Kings cabinet.\n" );
    add_item( ({ "reliefs", "relief", "bas reliefs", "bas relief",
        "scenes", "scene" }),
        "You run your hand admiringly over the bas relief carved into the "+
        "throne. All in all there are seven different scenes depicted.\n" );
    add_item( ({ "first bas relief", "first relief", "first scene" }),
        "The first scene depicts a horde of orcs slaughtering a group "+
        "of Laiquendi in a sylvan glade.\n" );
    add_item( ({ "second bas relief", "second relief", "second scene" }),
        "The second bas reliefs shows a Balrog dismembering a group of "+
        "terrified dwarves." );
    add_item( ({ "third bas relief", "third relief", "third scene" }),
        "This scene shows the great wolf Anfauglir ravaging Doriath.\n" );
    add_item( ({ "fourth bas relief", "fourth relief", "fourth scene" }),
        "Here Glaurung, the first of the Uruloki, the fire drakes of "+
        "the North, is routing the forces of the Quendi in the Nirnaeth "+
        "Arnoediad, the Fifth Battle of Beleriand.\n" );
    add_item( ({ "fifth bas relief", "fifth relief", "fifth scene" }),
        "Here is depicted the death of Feanor at the hands of Gothmog, "+
        "Lord of the Balrogs in the Dagor-nuin-Giliath, second of "+
        "the Battles of Beleriand.\n" );
    add_item( ({ "sixth bas relief", "sixth relief", "sixth scene" }),
        "The sixth bas relief shows the torment of Maedhros upon the peak "+
        "of Thangorodrim.\n" );
    add_item( ({ "seventh bas relief", "seventh relief", "seventh scene" }),
        "The last bas relief shows Melkor Bauglir on His Throne in "+
        "Angband wearing His Iron Crown with the three silmarils.\n" );

    setuid();
    seteuid(getuid());

    if (!present( "board", this_object() ))
    {
        object board = clone_object(MORGUL_OBJ_DIR + "nazgul_board");
        board->move( this_object() );
    }

    clone_object(MORGUL_OBJ_DIR + "dagger_chest")->move( this_object(), 1 );
    clone_object(MORGUL_OBJ_DIR + "kings_cabinet")->move( this_object(), 1 );
    clone_object( "/d/Gondor/clubs/anghoth/obj/anghoth_admin" )->
        move( this_object(), 1 ); 
    clone_object(MORGUL_OBJ_DIR + "nazgul_admin")->move( this_object(), 1 );
} 

public int block_non_nazgul()
{
    if (this_player()->query_nazgul() || this_player()->query_wiz_level())
    {
        return 0;
    }
    write( "Only nazgul are permitted to enter the library!\n" );
    return 1;
}

/*
 * Function name: list_records
 * Description  : Print the file that keeps the logs of demotions and
 *                promotions. 
 * Returns      : ""
 */
public string list_records()
{
    if (!this_player()->query_nazgul() && 
        (SECURITY->query_wiz_rank(this_player()->query_real_name()) < WIZ_NORMAL))
    {
        write( "You do not have the power to read this scroll!\n" );

        tell_room(this_object(), QCTNAME(this_player()) + " tries to access the " +
                  "scroll containg the logs of the Nazgul!\n", this_player());
        return "";
    }

    write( "You read the scroll with the records of punishments and "+
        "rewards:\n" );
    seteuid( getuid() );
    if (query_verb() == "tail")
    {
        tail_file(MORGUL_NAZGUL_RECORDS);
    }
    else
    {
        this_player()->more(read_file(MORGUL_NAZGUL_RECORDS, 1 ), 0 );
    }  

    MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_MINOR);
    tell_room(this_object(), QCTNAME(this_player()) 
        + " scans the scroll containg the logs of the Nazgul.\n"
        , this_player());

    return "";
}

/*
 * Function name: list_complaints
 * Description  : Print the file with the anon complaints.
 * Returns      : ""
 */
public string list_complaints()
{
    if (!this_player()->query_nazgul() && 
        (SECURITY->query_wiz_rank(this_player()->query_real_name()) < WIZ_NORMAL))
    {
        write( "You do not have the power to investigate the reports!\n" );
        tell_room(this_object(), QCTNAME(this_player()) + " tries to access the " +
                  "reports for the Nazguls eyes only!\n", this_player());
        return "";
    }

    if (file_size(MORGUL_WARDEN_RECORDS) < 1)
    {
        write( "At present, there are no reports on the desk.\n" );
        return "";
    }

    write( "These are the reports that are on the desk:\n" );
    if (query_verb() == "tail")
    {
        tail_file(MORGUL_WARDEN_RECORDS);
    }
    else
    {
        this_interactive()->more(MORGUL_WARDEN_RECORDS, 1 );
    }

    MORGUL_MASTER->increase_activity(this_player(), ACTIVITY_MINOR);
    tell_room(this_object(), QCTNAME(this_player()) 
        + " riffle through the pile of reports.\n", this_player());

    return "";
}

private int is_guildmaster(string name)
{
    return member_array(name, 
        GONDOR_MASTER->query_domain_aliases(GUILD_NAME)) != -1;
}

private string *get_titles(int type, int gender)
{
    switch(type) 
    {
    case 1: return MORGUL_BLACKSPEECH_TITLES;
    case 2: return MORGUL_ADUNAIC_TITLES;
    case 3: 
        return (gender == 0 
                ? MORGUL_QUENYA_MALE_TITLES 
                : MORGUL_QUENYA_FEMALE_TITLES);
    default:
        return (gender == 0 
                ? MORGUL_COMMON_MALE_TITLES 
                : MORGUL_COMMON_FEMALE_TITLES);
    }
}

private string get_title(int level, int gender, object for_player)
{
    int title_type = for_player->query_mage_option(OPTION_TITLE_MLIST);
    string *titles = get_titles(title_type, gender);
    return (level >= sizeof(titles)) ? "---" : titles[level];
}

private string chance_time(int time) 
{
    string timetext = ctime(time);
    return timetext[4..9] + ", " + timetext[22..24];
}

private string position_text(string mage) {
    string result = "";
    
    foreach(string key, string title : ASSIGNABLE_POSITIONS) {
        if(key == "lieutenant") continue;

        if(lower_case(MORGUL_MASTER->query_position(key)) ==
           lower_case(mage)) {
               result += sprintf("\n%-:30s %s", "", title);
        }
    }
    return result;
}

private mixed *get_mage_info(string name, object player)
{
    int wiz_level, nazgul_level;
    string mage_name = MORGUL_MASTER->query_mage_name(name);
    
    mixed rank_info = MORGUL_MASTER->get_mage_rank(name);    
    int gender = (rank_info ? rank_info[2] : 0);
    int rank = (rank_info ? rank_info[0] : 0);
    int time = (rank_info ? rank_info[1] : 0);
    
    if (wiz_level = SECURITY->query_wiz_rank(name)) 
    {
        string wizard_member = capitalize(name);
        if (mage_name) wizard_member += " (" + mage_name + ")";

        if(is_guildmaster(name)) {
            return ({ "Guildmaster", wiz_level, wizard_member });
        }
        
        return ({ "Immortals", wiz_level, wizard_member });
    }
    
    if(nazgul_level = MORGUL_MASTER->query_is_nazgul(name)) {
        return ({ "The Nine", nazgul_level, sprintf("%-:24s %s",
            capitalize(name) + " (" + mage_name + ")", 
            get_title(MAX_NORMAL_LEVELS + 1 + nazgul_level, gender, player)) });
    }
    else if (rank == 47)
        rank_info = 0;

    string rank_title = (rank_info ? 
        get_title(rank, gender, player) + " [" + chance_time(time) + "]" :
        "---");
    
    if (mage_name) {
        return ({ "Mages", rank, sprintf("%-:24s %s", 
            capitalize(name) + " (" + mage_name + ")",
            rank_title) + position_text(name) });
    }
    
    return ({ "Apprentices", rank, sprintf("%-24s %s", 
        (name ? capitalize(name) : ""),
        (rank_title ? rank_title : "")) });
}

private int group_order(string group)
{
    switch(group) {
    case "The Nine": return 1;
    case "Mages": return 2;
    case "Apprentices": return 3;
    case "Guildmaster": return 4;
    case "Immortals": return 5;
    default:
        100;
    }
}

int sort_by_group_and_rank(mixed info1, mixed info2)
{
    int order1 = group_order(info1[0]);
    int order2 = group_order(info2[0]);

    if (order1 == order2) {
        return info2[1] - info1[1];
    }
    
    return order1 - order2;
}

/*
 * Function name: list_mages
 * Description  : Print the member list.
 * Returns      : The output.
 */
public string list_mages()
{
    string str = 
          "    Listed below are the Servants of the Dark Lord:\n"
        + "    (Dates represent last update of current rank.)\n";
        
    string *mages = MORGUL_MASTER->query_mages();
    mages = filter( mages, &not() @ &wildmatch( "*jr", ) );
    
    mixed *mage_info = map(mages, &get_mage_info(, this_player()));
    mage_info = sort_array(mage_info, "sort_by_group_and_rank");
    
    string last_group;
    foreach(mixed info : mage_info) {
        if (!last_group || last_group != info[0]) {
            last_group = info[0];
            str += "\n    " + last_group + "\n";
        }
        str += "    - " + info[2] + "\n";
    }

    MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_MINOR);
    tell_room(this_object(), QCTNAME(this_player()) 
        + " studies the plaque.\n", this_player());

    return str+ "\n";
}

object On_Throne;
int do_sit( string str )
{
    object  tp = this_player();

    if (!str)
    {
        notify_fail( "Sit where?\n" );
        return 0;
    }
    if (str != "throne" && str != "on throne")
    {
        notify_fail( "Sit on the throne, perhaps?\n" );
        return 0;
    }

    if (tp->query_prop( "_On_Throne" ))
    {
        notify_fail( "But you are already sitting on the throne!\n" );
        return 0;
    }

    if (objectp( On_Throne ))
    {
        if (!present( On_Throne, this_object() ) ||
            !(On_Throne->query_prop( "_On_Throne" )))
        {
            On_Throne->remove_prop( "_On_Throne" );
            On_Throne = 0;
        }
        else
        {
            notify_fail( QCTNAME( On_Throne )+
                " is already sitting on the throne!\n" );
            return 0;
        }
    }

    if (tp->query_nazgul() < 2)
    {
        write( "As you lower yourself to the Dark Throne, the gaze of the "+
            "Red Eye falls upon you, and you quickly rise again.\n" );
        say( QCTNAME( tp )+ " tries to sit on the Dark Throne, but "+
            tp->query_pronoun() + " quickly rises again, trembling for fear.\n" );
        return 1;
    }

    write( "You sit down on your throne.\n" );
    say( QCTNAME( tp )+ " sits down on " + tp->query_possessive() 
        + " Dark Throne.\n", tp );
    On_Throne = tp;
    tp->add_prop( "_On_Throne", 1 );
    tp->add_prop(LIVE_S_EXTRA_SHORT, ", sitting on " 
        + tp->query_possessive() + " Dark Throne" );
    MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_EMOTION);
    return 1;
}

int do_rise( string str )
{
    object tp = this_player();
    string vb = query_verb();

    if (vb == "stand" && str != "up")
    {
        notify_fail( capitalize( vb )+ " what? Up?\n" );
        return 0;
    }

    if (!tp->query_prop( "_On_Throne" ) && On_Throne != tp)
    {
        notify_fail( "But you are not sitting on the throne!\n" );
        return 0;
    }
 
    write( "You rise from your Dark Throne.\n" );
    say( QCTNAME( tp )+ " rises from "+ tp->query_possessive() 
        + " Dark Throne.\n", tp );
    tp->remove_prop( "_On_Throne" );
    tp->remove_prop( LIVE_S_EXTRA_SHORT );
    On_Throne = 0;
    return 1;
}

int do_recline( string str )
{
 object tp = this_player();

    if (tp != On_Throne)
    {
        return 0;
    }
    write( "You recline thoughtfully upon your Throne.\n" );
    say( "The Lord of the Nazgul reclines thoughtfully upon "+
        tp->query_possessive() + " Dark Throne.\n" );
    MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_EMOTION );
    return 1;
}

int do_inspect( string str )
{
 object tp = this_player(), *objs, *live, *dead;

    if (tp != On_Throne)
    {
        return 0;
    }
    if (!str)
    {
        notify_fail( "Inspect what?\n" );
        return 0;
    }

    if (!parse_command( str, this_object(), "%l", objs ))
    {
        notify_fail( "You cannot find any "+ str+ " here.\n" );
        return 0;
    }

    objs = NORMAL_ACCESS( objs, 0, 0 );
    objs -= ({ tp });
    if (!sizeof( objs ))
    {
        notify_fail( "You cannot find any "+ str+ " here.\n" );
        return 0;
    }

    write( "You sit forward on your throne, inspecting "+
        COMPOSITE_LIVE( objs )+ " carefully.\n" );
    objs->catch_tell( "The Lord of the Nazgul sits forward on "+
        tp->query_possessive() + " Dark Throne, scrutinizing you carefully.\n" );
    say( "The Lord of the Nazgul sits forward on "+ On_Throne->query_possessive() +
        " Dark Throne, inspecting "+ COMPOSITE_LIVE( objs )+
        " carefully.\n", ({ tp })+ objs );
    MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_EMOTION );
    return 1;
}

private int lord_has_voted_for_mage(string name) {
	string lord = MORGUL_MASTER->query_lord_nazgul();
	if (!lord) return 0;
	
	foreach(string nazgul, string mage : MASTER->query_nazgul_votes()) {
		if ((nazgul == lord) && (mage == name)) return 1;
	}
	
	return 0;
}

int do_grant( string str )
{
    object  tp = this_player();
    object  mage;

    if (tp->query_nazgul() < 1)
    {
        notify_fail("What?\n");
        return 0;
    }

    if (!str || !strlen(str))
    {
        notify_fail("Grant what Mage access to the Throne Room?\n");
        return 0;
    }

    mage = find_player(lower_case(str));

    if (!mage)
    {
        notify_fail("Grant what Mage access to the Throne Room?\n");
        return 0;
    }

	string lord = MORGUL_MASTER->query_lord_nazgul();
	int player_is_not_lord = (this_player()->query_real_name() != lord); 
    if ((lord && player_is_not_lord) 
	    && !lord_has_voted_for_mage(mage->query_real_name())) {
		
        notify_fail("Only the King may grant a Mage access to the "
			+ "Throne Room.\n");
        return 0;
	}
		
    if(mage->query_morgul_level() <= APPRENTICE_LEVEL)
    {
        notify_fail("There is no use in granting a mere Apprentice access "
           + "to the throne room. It can not reach the upper levels of the "
           + "Tower!\n");
        return 0;
    }

    write_file( MORGUL_NAZGUL_RECORDS, this_player()->query_name() 
        + " grants " + mage->query_name()+ " access to the throne room" 
        + " ("+ ctime( time() )+ ").\n" );

    write("You grant " +mage->query_name()+ " access to the throne room!\n");
    mage->add_prop(MORGUL_S_THRONE_GRANT, 1);
    MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_EMOTION );
    return 1;
}


public void init() {
    ::init();
    
    add_action( do_sit,         "sit" );
    add_action( do_rise,        "stand" );
    add_action( do_rise,        "rise" );
    add_action( do_recline,     "recline" );
    add_action( do_inspect,     "inspect" );
    add_action( do_grant,       "grant" );
}

void leave_inv( object ob, object to )
{
    ::leave_inv( ob, to );

    if (!objectp( ob ))
    {
        return;
    }
    if (living( ob ) && ob->query_prop( "_On_Throne" ))
    {
        ob->catch_msg( "You rise from your Dark Throne.\n" );
        tell_room(this_object(),
            QCTNAME( ob )+ " rises from the Dark Throne.\n", ob);
        ob->remove_prop( LIVE_S_EXTRA_SHORT );
        ob->remove_prop( "_On_Throne" );
        On_Throne = 0;
    }
}

void performed_mordor_emote() {
	if (!this_player()->query_nazgul()) return;

    string *values = ({ 
		"you deserve to be relieved of your burden soon",
		"you are unworthy to hold a ring of power",
		"he has seen maggots which are more useful to his cause",
		"your efforts are pathetic and worthless", 
		"you have convinced him to start looking for your replacement", 
		"he finds your inherent laziness intolerable",
		"your performance does not inspire confidence", 
		"your actions lack sincerity", 
		"your attempts to further his goals are defective",
		"you are a disgrace to the black tower",
		"your efforts require drastic improvement",
		"he finds your devotion to his cause to be shameful",
		"your actions are deemed to be barely adequate"
	});

	string value = MORGUL_MASTER->describe_time_remaining(this_player()->query_real_name(), values);
	
	this_player()->catch_msg("With terrible certainty, you feel the mind of "
		+ "the Dark Lord, your Master upon you! Though no words are uttered "
		+ "or heard, you are shaken by the judgement of Sauron the Great, "
		+ "who decrees that " + value + ".\n");
}
