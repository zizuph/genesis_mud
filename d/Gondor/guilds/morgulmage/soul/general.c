/*
 *    /d/Gondor/guilds/morgulmage/soul/general.c
 *
 *    This file is part of the command soul for the Morgul mages.
 *    General commands used by the Society.
 *
 *    Created by Eowul, Apr 30, 2009, split from the other various
 *    command soul files.
 *
 */


#define COST   4                /* Mana-cost for tracking.                */
#define RACES  ({"dwarf","elf","gnome","goblin","hobbit","human","animal"})
#define EXTRA  ", sniffing on the ground"
#define LIVE_S_EXTRA_SHORT_OLD    "_live_s_extra_short_old"

#include <terrain.h>

int sniff_alarm;

public int designate_ingredient( string str )
{
 int s;
 object *oblist, tp = this_player();
 string  name;
 mixed  *adjs;

    if (!strlen( str ))
    {
        notify_fail( "Designate which object to be a spell ingredient?\n" );
        return 0;
    }

    str = lower_case( str );
    if (!parse_command( str, tp, "[the] %i [as] [an] 'ingredient' [for] %w",
        oblist, name ))
    {
        notify_fail( capitalize( query_verb() )+ " which object as "+
            "an ingredient for which spell?\n" );
        return 0;
    }

    oblist = NORMAL_ACCESS( oblist, 0, 0 );
    if (!(s = sizeof( oblist )))
    {
        notify_fail( capitalize( query_verb() )+ " which object as "+
            "an ingredient for which spell?\n" );
        return 0;
    }
    if (s > 1)
    {
        notify_fail( "You can only designate one object at a time!\n" );
        return 0;
    }

    switch (name)
    {
                                /*For the spell 'naro', the mages need
                                 *a knife with a value of at least 10 sc and
                                 *to_hit and pen values with
                                 *(to_hit * pen) > 100.                     */
    case "naro":
        if ((function_exists( "create_object", oblist[0] ) != "/std/weapon")
            || (oblist[0]->query_wt() != W_KNIFE))
        {
            notify_fail( "You can only designate a knife as ingredient "+
                "for the spell \"naro\"!\n" );
            return 0;
        }
        if ((oblist[0]->query_prop( OBJ_I_VALUE ) < 120) ||
            ((oblist[0]->query_pen()* oblist[0]->query_hit()) < 100))
        {
            notify_fail( "That "+ oblist[0]->short()+ " is not worthy to "+
                "be designated as ingredient for the spell \"naro\"!\n" );
            return 0;
        }
        oblist[0]->add_name( "naro_ingr3" );
        write( "You designate your "+ oblist[0]->short()+ " to be an "+
            "ingredient for the spell \"naro\"!\n" );
        say( QCTNAME( tp )+ " rasps silently, examining "+ LANG_ADDART(
            oblist[0]->short() )+ " with piercing eyes.\n" );
        oblist[0]->add_prop( MORGUL_M_MAGIC_INGREDIENT, 1 );
        MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_TYPICAL );
        return 1;
        break;
    case "gostangwedh":
        if (oblist[0]->query_prop( OBJ_I_VALUE ) < 120)
        {
            notify_fail( "That "+ oblist[0]->short()+ " is not worthy to "+
                "be designated as an ingredient for the spell "+
                "\"gostangwedh\"!\n" );
            return 0;
        }
        oblist[0]->add_name( "gosta_ingr2" );
        write( "You designate your "+ oblist[0]->short()+ " to be an "+
            "ingredient for the spell \"gostangwedh\"!\n" );
        say( QCTNAME( tp )+ " rasps silently, examining "+ LANG_ADDART(
            oblist[0]->short() )+ " with piercing eyes.\n" );
        oblist[0]->add_prop( MORGUL_M_MAGIC_INGREDIENT, 1 );
        MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_TYPICAL );
        return 1;
        break;
    default:
        notify_fail( "You cannot designate any ingredient for that "+
            "spell!\n" );
        return 0;
        break;
    }
    return 0;
}

public int
compare_anghoth_level( object x, object y )
{
    return x->query_anghoth_level() - y->query_anghoth_level();
}

public string
list_active_anghoth()
{
    object *anghoth = filter(users(), &->query_anghoth_level());
    sort_array(anghoth, "compare_anghoth_level");

    string result = "";
    foreach(object member : anghoth) {
        string name = member->query_real_name();

        if ((extract(name, -2 ) == "jr")
            && (!(this_player()->query_wiz_level())))
        {
            continue;
        }

        if (result == "") {
            result += "\nThese Shields of Minas Morgul are currently "
                + "at your disposal:\n";
        }

        int ashuk = ANGHOTH_MANAGER->query_ashuk(name);
        string rank = capitalize(member->query_anghoth_rank());

        result += ": " + member->query_name();

        if (ashuk) {
            result += ", Ashuk " + rank;
        } else {
            string sponsor = ANGHOTH_MANAGER->query_anghoth_sponsor(name);
            string magename = MORGUL_MASTER->query_mage_name(sponsor);

            result += ", " + rank + " for " 
                + (magename ? magename : capitalize(sponsor));
        }

        result += "\n";
    }

    if (result == "") {
        return "\nThere are no Shields of Morgul available.\n";
    }

    return result;
}


public int
compare_rank( object x, object y )
{
 int dum,
 ix = x->query_morgul_level(),
 iy = y->query_morgul_level();

    if(x->query_sage(x))
       ix = 25;

    if(y->query_sage(y))
       iy = 25;

    if (dum = SECURITY->query_wiz_rank(x->query_real_name()))
    {
        ix = dum + 100;
    }
    if (dum = SECURITY->query_wiz_rank(y->query_real_name()))
    {
        iy = dum + 100;
    }
    return (iy - ix);
}

public int
list_active_mages()
{
    int i, cnt;
    object *list;
    string  magename, mage_title, mage_list;
    int title_type = this_player()->query_mage_option(OPTION_TITLE_MLIST, 0);

    mage_list = "The members of the Society of Morgul Mages currently "+
        "in the realms:\n";
    list = filter( users(), member_player_filter);
    list = sort_array( list, "compare_rank" );

    i = -1;
    while (++i < sizeof( list ))
    {
        magename = list[i]->query_real_name();
                            /*Don't want a jr's name on the guildlist.*/
        if ((extract( magename, -2 ) == "jr") &&
            (!(this_player()->query_wiz_level())))
        {
            continue;
        }
        if (!list[i]->query_invis())
        {
            if (list[i]->query_wiz_level())
            {
                mage_list += ": " +
                    SECURITY->query_wiz_pretitle( magename )+ " "+
                    capitalize( magename )+ " "+ list[i]->query_title();
            }
            else
            {
                mage_title = ", "+ list[i]->query_morgul_title(title_type);
                mage_list += ": "+ capitalize( magename )+ mage_title;
            }
            
            mage_title = MORGUL_MASTER->query_mage_name( magename );
            if (strlen( mage_title ))
            {
                mage_list += ", " + mage_title;
            }
            if (list[i]->query_ghost())
            {
                mage_list += " <dead>";
            }

            mage_list += ("\n");
            cnt++;
        }
        
        if (list[i]->query_invis() && (!list[i]->query_wiz_level() ||
            this_player()->query_wiz_level()))
        {
            mage_list += ": (" + capitalize( magename ) + ")";
            mage_list += ("\n");
            cnt++;
        }
    }
    if (cnt == 1)
    {
        mage_list += "There is presently only one Morgul Mage serving the "+
            "Dark Lord.\n";
    }
    else if (cnt)
    {
        mage_list += "There are now "+ LANG_WNUM( cnt )+
            " Morgul Mages serving the Dark Lord.\n";
    }
    else
    {
        mage_list = "There are currently no Morgul Mages serving the "+
            "Dark Lord.\n";
    }

    write (mage_list + list_active_anghoth());
    return 1;
}

private int has_access_to_help_section(object player,
    string section, string topic)
{
    if (!IS_MEMBER(player)) return 0;
    
    switch(section)
    {
        case "king":
            if (player->query_nazgul() == 2) return 1;
            break;
        case "nazgul":
            if (player->query_nazgul()) return 1;
            break;
        case "lieutenant":
            if (player->query_nazgul()) return 1;
            if (IS_LIEUTENANT(player)) return 1;
            break;
        case "mage":
            if (!IS_APPRENTICE(player)) return 1;
            break;
        case "apprentice":
            return 1;
        case "spells":
            object spellob = player->find_spell(topic);
            if (!objectp(spellob)) return 0;
            return spellob->query_spell_can_be_learned(player);
            break;
    }
    
    return 0;
}

private string *find_accessible_help_files(object player,
    string topic, string *sections)
{
    string *files = ({ });
    
    foreach(string section : sections) {
        if (!has_access_to_help_section(player, section, topic)) 
            continue;
        
        topic = implode(explode(topic, " "), "_");
        if (file_size(MORGUL_HELP_DIR + section + "/" + topic) > 0)
            files += ({ MORGUL_HELP_DIR + section + "/" + topic });
    }
    
    return files;
}

public int help(string str)
{
    string topic;    
    string *sections = ({ "king", "nazgul", "lieutenant",
        "mage", "apprentice", "spells" });
    
    if ((query_verb() != "mhelp") && !strlen( str ))
    {
        return 0;
    }
    
    if (query_verb() == "mhelp") {
        notify_fail("There is no help on that subject.\n");
        topic = str;
    } else {
        if((str == "mages") || (str == "morgul")) {
            str = "mages index";
        }
        
        if ((sscanf( str, "mages %s", topic ) != 1) &&
            (sscanf( str, "morgul %s", topic ) != 1))
        {
            return 0;
        }
    }

    if (strlen(topic)) {    
        string *words = explode(topic, " ");
        if (member_array(words[0], sections) != -1) {
            sections = ({ words[0] });
            topic = implode(words[1..], " ");
        }
    }
    
    if (!strlen(topic) || (topic == "")) topic = "index";
    
    setuid();
    seteuid(getuid());
    
    string *files = find_accessible_help_files(this_player(),
        topic, sections);
        
    foreach(string file : files) {
        cat(file);
    }    
   
    if (sizeof(files)) return 1;
}

public int morgul_titles( string str )
{
    string *male_titles = MORGUL_COMMON_MALE_TITLES, 
           *female_titles = MORGUL_COMMON_FEMALE_TITLES,
           result;
    int i;

    if (!str || (str != "common" && str != "adunaic" && str != "black speech" && str != "quenya"))
    {
        notify_fail("'mtitles' lists the titles available within the "
            + "guild of the Morgul Mages.\n"
            + "Syntax: mtitles <type>, where type is either common, adunaic, "
            + "black speech or quenya.\n");
        return 0;
    }
    
    if (str == "adunaic") {
        male_titles = MORGUL_ADUNAIC_TITLES;
        female_titles = MORGUL_ADUNAIC_TITLES;
    }
    
    if (str == "black speech") {
        male_titles = MORGUL_BLACKSPEECH_TITLES;
        female_titles = MORGUL_BLACKSPEECH_TITLES;
    }

    if (str == "quenya") {
        male_titles = MORGUL_QUENYA_MALE_TITLES;
        female_titles = MORGUL_QUENYA_FEMALE_TITLES;
    }
    
    result  = sprintf( " %4s  %-30s      %-30s\n", "Rank", "Male Titles", "Female Titles");
    result +=  "----------------------------------------------------------------------------\n";
    for(i = sizeof(male_titles) - 1; i >= sizeof(male_titles) - 2; i--) {
        result  += sprintf(" %4s  %=-33s   %=-33s\n", 
            "[C]", male_titles[i], female_titles[i]);
    }
    result +=  "----------------------------------------------------------------------------\n";
    
    for(i = ARCHMAGE_LEVEL; i >= 0; i--) {
        string level_count = (i >= LT_LEVEL) ? "" : "["+(i+1)+"]";        
        result += sprintf(" %4s  %-:34s  %-:34s\n", level_count,
            male_titles[i], female_titles[i]);
        if (i >= LT_LEVEL) result += "----------------------------------------------------------------------------\n";            
    }

    write(result);
    return 1;
}

public int sort_spells(object spell1, object spell2)
{
    return spell1->query_morgul_rank() - spell2->query_morgul_rank();
}

/*
 * List all spells, including the level at which they become available
 */
public int list_spells( string str )
{
    int i, j, s, level, ntitles;
    object  tp = this_player();
    string *titles, title, msg =
        "\n\t ________________________________________________ \n"+
        "\t/                                                \\\n"+
        "\t|  The Dark Lord has granted you these spells:   |\n"+
        "\t|  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~   |\n";

    if (str != "spells")
    {
        return 0;
    }

    object *morgul_spells = filter(filter(this_player()->query_spellobjs(),
        stringp @ &function_exists("query_morgul_rank")), 
        &->query_spell_can_be_learned(this_player()));
    sort_array(morgul_spells, "sort_spells");

    if (tp->query_gender() == 1)
    {
        titles = MORGUL_COMMON_FEMALE_TITLES;
    }
    else
    {
        titles = MORGUL_COMMON_MALE_TITLES;
    }

    ntitles = sizeof( titles );
    foreach(object spell : morgul_spells) {
        level = spell->query_morgul_rank();
        if (level < ntitles)
        {
            title = titles[level];
        }
        else
        {
            title = "Nazgul";
        }
        msg += sprintf( "\t|  %-13s - %-28s  |\n", spell->query_spell_name(),  
            title );
    }
    msg += "\t\\________________________________________________/\n\n";
    write( msg );
    return 1;
}

void sniff_now( object room, object player, int track_skill )
{
 string *track_arr, result, old_prop, dir, race;
 int i;
 mixed  *exits;

    result = "You do not smell any tracks.\n";
    old_prop = 0;
    remove_alarm( sniff_alarm );
    sniff_alarm = 0;

    if (!objectp( player ))
    {
        return;
    }
    track_arr = room->query_prop( ROOM_S_DIR );
    if (player->query_wiz_level())
    {
        write( "Wizinfo: "+ player->query_name()+ ": tracking skill "+
            track_skill+ ", "+ implode( track_arr, ", " )+ "\n" );
    }
                                /* just in case, but presently,
                                 *ROOM_I_INSIDE prevents setting of
                                 *ROOM_S_DIR                              */
    if (room->query_prop( ROOM_I_INSIDE ))
    {
        track_skill -= 50;
    }
    if (this_player()->query_morgul_invis())
    {
        track_skill += 50;
    }
    track_skill /= 2;
    track_skill += random( track_skill );

    if (pointerp( track_arr ) && track_skill > 0)
    {
        dir = track_arr[0];
        if (dir == "X" || dir == "M")
        {
            dir = "nowhere";
        }
        race = track_arr[1];
        result = "You can smell some tracks on the ground.\n";
        switch (track_skill)
        {
        case  1..10:
            break;
        case 11..20:
            if (random( 2 ))
            {
                exits = room->query_exit();
                if (i = sizeof( exits ))
                {
                    dir = exits[random( i/ 3 )* 3+ 1]; 
                }   
            }
            result += "They are probably leading " + dir + ".\n";
            break;
        case 21..50:
            result += "They are leading "+ dir+ ".\n";
            break;
        case 51..75:
            if (random( 2 ))
            {
                race = RACES[random( sizeof( RACES ) )];
            }
            result += "They were probably made by "+ LANG_ADDART( race )+
                " and are leading "+ dir+ ".\n";
            break;
        case 76..150:
            result += "They were made by "+ LANG_ADDART( race ) + 
                " and are leading "+ dir+ ".\n";
            break;
        }
    }
         
    player->catch_msg( result );
    if (old_prop = player->query_prop( LIVE_S_EXTRA_SHORT_OLD ))
    {
        player->change_prop( LIVE_S_EXTRA_SHORT, old_prop );
    }
    else
    {
        player->remove_prop( LIVE_S_EXTRA_SHORT );
    }
    tell_room( environment( player ), QCTNAME( player )+ " rises again.\n",
        player, player );
    return;
}

int
do_msniff()
{
 object paralyze, _here;
 int time, track_skill;
 string  old_prop = 0, msg = "";

    _here = environment( this_player() );
    if (!_here->query_prop( ROOM_I_IS ))
    {
        msg = ", but you do cannot smell anything";
    }
    if (_here->query_prop( ROOM_I_INSIDE ))
    {
        msg = ", but since you are inside a room, you cannot smell "+
            "anything";
    }
    if (_here->terrain_includes_any( TERRAIN_UNDERWATER ))
    {
        msg = ", but you only pulled in some water through your nose";
    }
    if (_here->terrain_includes_any( TERRAIN_ONVEHICLE ))
    {
        msg = ", but except the presence of dust you can't feel anything";
    }
    if (this_player()->query_mana() < 2*COST)
    {
        msg = ", but you are mentally too exhausted";
    }
    write( "You lower yourself to the ground and start sniffing for tracks"+
        msg+ ".\n" );
    allbb( " lowers "+ this_player()->query_objective()+ "self to the "+
		"ground and seems to sniff for something, as if hunting." );

    if (strlen( msg ))
    {
        return 1;
    }
    old_prop = this_player()->query_prop( LIVE_S_EXTRA_SHORT );
    if(old_prop == EXTRA)
    {
        old_prop = 0;
    }
    if(stringp( old_prop ))
    {
        this_player()->add_prop( LIVE_S_EXTRA_SHORT_OLD, old_prop );
    }
    this_player()->add_prop( LIVE_S_EXTRA_SHORT, EXTRA );
    this_player()->add_mana( -COST );
    time = _here->query_prop( OBJ_I_SEARCH_TIME );
    if (time < 1)
    {
        time = 10;
    }
    else
    {
        time += 5;
    }
    track_skill = this_player()->query_skill( SS_TRACKING );
    time -= track_skill/ 10;
    if (time < 1)
    {
        sniff_now( _here, this_player(), track_skill );
    }
    else
    {
        sniff_alarm = set_alarm( itof( time ), 0.0, &sniff_now( _here,
            this_player(), track_skill ) );
        setuid();
        seteuid( getuid() );
        paralyze = clone_object( "/std/paralyze" );
        paralyze->set_standard_paralyze( "tracking" );
        paralyze->set_stop_fun( "stop_sniff" );
        paralyze->set_stop_verb( "stop" );
        paralyze->set_stop_message( "You stop sniffing for tracks on the "+
            "ground.\n" );
        paralyze->set_remove_time( time );
        paralyze->set_fail_message( "You are busy sniffing for tracks. "+
            "You must 'stop' to do something else.\n" );
        paralyze->move( this_player(), 1 );
    }
    return 1;
}

varargs int stop_sniff( mixed arg )
{
 string old_prop;

    if(!objectp( arg ))
    {
        remove_alarm( sniff_alarm );
    }
    sniff_alarm = 0;
    tell_room( environment( this_player() ), QCTNAME( this_player() )+
        " stops sniffing for tracks on the ground.\n", this_player() );
    if (old_prop = this_player()->query_prop( LIVE_S_EXTRA_SHORT_OLD ))
    {
        this_player()->change_prop( LIVE_S_EXTRA_SHORT, old_prop );
    }
    else
    {
        this_player()->remove_prop( LIVE_S_EXTRA_SHORT );
    }
    return 0;
}

private string title_description(int type)
{
    switch(type) 
    {
        case 1:
            return "Black Speech";
        case 2:
            return "Adunaic";
        case 3:
            return "Quenya";
        case 4:
            return "Generic title";
        case 5:
            return "Hidden title";
        default:
            return "Common Speech";
    }
}

private int convert_title_type(string text, int allow_special)
{
    switch(text) 
    {
    case "common":
    case "common speech":
        return 0;
    case "black":
    case "black speech":
    case "blackspeech":
        return 1;
    case "adunaic":
        return 2;
    case "quenya":
        return 3;
    case "generic":
        if (allow_special) return 4;
        break;
    case "hidden":
        if (allow_special) return 5;
        break;    
    }
    
    return -1;
}

nomask int
moptions(string arg)
{
    string *args, rest;
    int     wi;

    if (!stringp(arg))
    {
        moptions("introtitle");
        moptions("normaltitle");
        moptions("listtitle");
        moptions("autoignite");
        moptions("nifarist");
        return 1;
    }
    
    args = explode(arg, " ");
    if (sizeof(args) == 1)
    {
        switch(arg)
        {
        case "introtitle":
        case "intro":
            write("Introduction title:  " +
                title_description(this_player()->query_mage_option(OPTION_TITLE_INTRO)) + "\n");
            break;        
        case "normaltitle":
        case "normal":
            write("Normal title:        " +
                title_description(this_player()->query_mage_option(OPTION_TITLE_NORMAL)) + "\n");
            break;        
            break;
        case "listtitle":
        case "list":
            write("List title:          " +
                title_description(this_player()->query_mage_option(OPTION_TITLE_MLIST)) + "\n");
            break;  
        case "autoignite":
            if(!(MORGUL_SPELL_DIR + "narusse")->query_spell_can_be_learned(this_player())) {
                return notify_fail("Syntax error: No such option.\n");
            }
            write("Narusse auto ignite: " +
                (this_player()->query_mage_option(OPTION_NARUSSE_IGNITE) ? "yes" : "no") + "\n");
            break;
        case "nifarist":
            if(!(MORGUL_SPELL_DIR + "nifarist")->query_spell_can_be_learned(this_player())) {
                return notify_fail("Syntax error: No such option.\n");
            }
            
            int visible = this_player()->query_mage_option(OPTION_NIFARIST);
            
            string *visible_for = ({ });
            if (visible & NIFARIST_FULL_MAGES) visible_for += ({ "full mages" });
            if (visible & NIFARIST_APPRENTICES) visible_for += ({ "apprentices" });
            if (visible & NIFARIST_TEAM) visible_for += ({ "your team" });

            write("Nifarist visibility: " + 
                (sizeof(visible_for) ? COMPOSITE_WORDS(visible_for) 
                    : "higher ranking mages") + "\n");
            break;
        default:
            return notify_fail("Syntax error: No such option.\n");
            break;
        }
        return 1;
    }

    rest = implode(args[1..], " ");

    switch(args[0])
    {
    case "introtitle":
    case "intro":
    {
        int title_type = convert_title_type(rest, 1);
        if (title_type == -1) 
        {
            return notify_fail("Unknown title type '" + rest + "', allowed "
                + "types are 'common', 'adunaic', 'black speech', 'quenya', "
                + "'hidden' and 'generic'.\n");
        }
        this_player()->set_mage_option(OPTION_TITLE_INTRO, title_type);
        moptions("introtitle");
        break;
    }
    case "normaltitle":
    case "normal": 
    {
        int title_type = convert_title_type(rest, 1);
        if (title_type == -1) 
        {
            return notify_fail("Unknown title type '" + rest + "', allowed "
                + "types are 'common', 'adunaic', 'black speech', 'quenya', "
                + "'hidden' and 'generic'.\n");
        }
        this_player()->set_mage_option(OPTION_TITLE_NORMAL, title_type);
        moptions("normaltitle");
        break;
    }
    case "listtitle":
    case "list":     
    {
        int title_type = convert_title_type(rest, 0);
        if (title_type == -1) 
        {
            return notify_fail("Unknown title type '" + rest + "', allowed "
                + "types are 'common', 'adunaic', 'black speech', 'quenya'.\n");
        }
        this_player()->set_mage_option(OPTION_TITLE_MLIST, title_type);
        moptions("listtitle");
        break;
    }
    case "autoignite":
    {
        if(!(MORGUL_SPELL_DIR + "narusse")->query_spell_can_be_learned(this_player())) {
            return notify_fail("Syntax error: No such option.\n");
        }
        rest = lower_case(rest);
        int ignite = ((rest == "yes") || (rest == "on"));
        this_player()->set_mage_option(OPTION_NARUSSE_IGNITE, ignite);
        moptions("autoignite");
        break;
    }
    case "nifarist":
    {
        if(!(MORGUL_SPELL_DIR + "nifarist")->query_spell_can_be_learned(this_player())) {
            return notify_fail("Syntax error: No such option.\n");
        }

        rest = lower_case(rest);
        string *toggles = explode(rest, " ");

        int visibility = this_player()->query_mage_option(OPTION_NIFARIST);
        foreach(string toggle : toggles) 
        {
            switch(toggle) {
                case "team": 
                    visibility ^= NIFARIST_TEAM; 
                    break;                
                case "mage":
                case "mages": 
                case "fullmage": 
                case "fullmages":
                    visibility ^= NIFARIST_FULL_MAGES; 
                    break;
                case "apprentice":
                case "apprentices":
                    visibility ^= NIFARIST_APPRENTICES; 
                    break;
                default:
                    return notify_fail("Syntax error: No such option '" 
                        + toggle + "'.\n");
            }
        }

        this_player()->set_mage_option(OPTION_NIFARIST, visibility);
        moptions("nifarist");
        break;
    }
    default:
        return notify_fail("Syntax error: No such option.\n");
        break;
    }
    return 1;
}