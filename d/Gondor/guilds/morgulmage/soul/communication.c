/*
 *    /d/Gondor/guilds/morgulmage/soul/emotes.c
 *
 *    This file is part of the command soul for the Morgul mages.
 *    The commands used for communicating.
 *
 *    Created by Eowul, Apr 30, 2009, split from the other various
 *    command soul files.
 *
 */
 
#define ORC_MEMBER(p) ((p)->query_guild_name_race() == "Orcs of Middle Earth")
#define URUK_MEMBER(p) ((p)->query_guild_name_race() == "Uruk-hai of Middle Earth")

// This is to say something with a hiss
public int mhiss( string str )
{
 object *oblist;
 string *how, text, say_text;

    if (text = this_player()->query_prop( LIVE_M_MOUTH_BLOCKED ))
    {
        write( stringp( text ) ? text :
            "You are gagged and cannot hiss.\n" );
        return 1;
    }

    how = parse_adverb_with_space( str, "dangerously", 0 );
    SOULDESC( "hissing"+ how[1] );

    if (!strlen( how[0] ))
    {
        write( "You hiss"+ how[1]+ ".\n" );
        all( " hisses"+ how[1]+ ".", "", 0, "hiss");
        MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_TALK );
        return 1;
    }
    oblist = parse_this( how[0], "'at' / 'to' [the] %i" );    
    oblist -= ({ this_player() });

    say_text = how[0];

    if (parse_command(say_text, environment( this_player() ),
        " 'at' / 'to' [the] %i %s ", oblist, text ))
    {
        oblist = NORMAL_ACCESS( oblist, 0, 0 ) - ({ 0, this_player() });
        if (sizeof( oblist ) && strlen( text ))
        {

            if (this_player()->query_option( OPT_ECHO ))
            {
                actor("You hiss to", oblist, ": " + text, "hiss");
            }
            else
            {
                write( "Ok.\n" );
            }
            target(" hisses to you: " + text, oblist, "", 0, "hiss");
            all2act( " hisses at", oblist, ": "+ text, "", 0, "hiss" );
            MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_TALK );
            return 1;
        }
    }
    oblist = FILTER_LIVE( all_inventory( environment( this_player() ) ) )-
        ({ this_player() } );
    if (this_player()->query_option( OPT_ECHO ))
    {
        string text = "You hiss: "+ str;
        write(text + "\n");
        this_player()->gmcp_comms("hiss", 0, text);
    }
    else
    {
        write( "Ok.\n" );
    }
    all( " hisses: "+ str, "", 0, "hiss" );
    MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_EMOTION );
    return 1;
}

// This is the speech command
public int rasp_say( string str ) 
{
 object *oblist, *watchers, *members, *others;
 string *how, text, say_text;

    if (text = this_player()->query_prop( LIVE_M_MOUTH_BLOCKED ))
    {
        write( stringp( text ) ? text :
            "You are gagged and cannot rasp.\n" );
        return 1;
    }

    how = parse_adverb_with_space( str, "threateningly", 0 );
    SOULDESC( "rasping"+ how[1] );

    if (!strlen( how[0] ))
    {
        write( "You rasp"+ how[1]+ ".\n" );
        all( " rasps"+ how[1]+ "." );
        MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_EMOTION );
        return 1;
    }

    oblist = parse_this( how[0], "[at] [the] %i" );    
    oblist -= ({ this_player() });

    say_text = how[0];

    if (parse_command( say_text, environment( this_player() ),
        " 'at' / 'to' [the] %i %s ", oblist, text) )
    {
        oblist = NORMAL_ACCESS( oblist, 0, 0 ) - ({ 0, this_player() });
        if (sizeof( oblist ) && strlen( text ))
        {

            if (this_player()->query_option( OPT_ECHO ))
            {
                actor("You rasp to", oblist, ": "+ text, "rasp");
            }
            else
            {
                write( "Ok.\n" );
            }
            members = filter( oblist, member_filter );
            members += filter( oblist- members, &->query_wiz_level());
            others = oblist- members;
            if (sizeof( members ))
            {
                target( " rasps to you: "+ text, members, "", 0, "rasp" );
            }
            if (sizeof( others ))
            {
                target( " rasps some low guttural sounds at you.", others, 
                    "", 0, "rasp" );
            }
            watchers = FILTER_LIVE( all_inventory( environment(
                this_player() ) ) )- ({ this_player() }) - oblist;
            members = filter( watchers, member_filter );
            members += filter( watchers- members, special_wizard_filter );
            others = watchers- members;
            all2act_split( "rasps at", oblist, others, ": "+ text, "", "rasp");
            all2act_split( "rasps some low guttural sounds at", oblist,
                members, ".", "", "rasp");
            MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_TALK );
            return 1;
        }
    }
    oblist = FILTER_LIVE( all_inventory( environment( this_player() ) ) );
    if (this_player()->query_option( OPT_ECHO ))
    {
        string text = "You rasp: " + str;
        write(text + "\n");
        this_player()->gmcp_comms("rasp", 0, text);
    }
    else
    {
        write( "Ok.\n" );
    }
    members = filter( oblist, member_filter );
    members += filter( oblist- members, &->query_wiz_level());
    others = oblist- members;
    members -= ({ this_player() });
    if (sizeof( members ))
    {
        target( " rasps: "+ str, members, "", 0, "rasp" );
    }
    if (sizeof( others ))
    {
        target( " rasps some low guttural sounds.", others, "", 0, "rasp" );
    }
    MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_TALK );
    return 1;
}


public int shriek( string str )
{
 int i, j, s;
 object room, mroom, *oblist, *mages;
 string out, *how, where, land, domain, circle_region;

    if (out = this_player()->query_prop( LIVE_M_MOUTH_BLOCKED ))
    {
        write( stringp( out ) ? out :
            "You are gagged and cannot speak.\n" );
        return 1;
    }
    how = parse_adverb_with_space( str, "shrilly", 0 );
    room = environment( this_player() );
//    while (!(room = environment(room))->query_prop(ROOM_I_IS));

    if (!strlen( how[0] ))
    {
        if (room->query_prop( ROOM_I_INSIDE ))
        {
            write( "You shriek"+ how[1]+ ".\n" );
            all( " shrieks"+ how[1]+ "." );
            tell_next_room_with_dir( room, "You hear a shrill cry from" );
            return 1;
        }
        write( "You raise a shrill cry to the wind.\n" );
        all( " raises a shrill cry to the wind, as if to signal some "
            + "distant party." );
        tell_next_room_with_dir( room,
            "The wind carries a shrill cry to you from" );

        where = "A shrill cry of "+ QTNAME( this_player() )+ " is carried "+
            "to you by the wind from ";
        land = implode( explode( file_name( room ), "/" )[..-3], "/" );
        mages = filter( users() - ({ this_player() }), member_filter );
        domain = room->query_domain();

        switch (domain)
        {
        case "Gondor":
            where += "";
            switch (land)
            {
            case "/d/Gondor/ithilien":
                where += "the land of Ithilien in Gondor";
                break;
            case "/d/Gondor/anduin":
            case "/d/Gondor/river":
                where += "near the Anduin river in Gondor";
                break;
            case "/d/Gondor/arnor":
                where += "the land of Arnor in Gondor";
                break;
               case "/d/Gondor/anorien":
                where += "the Anorien area of Gondor";
                break;
            case "/d/Gondor/dunland":
                where += "the Dunland area of Gondor";
                break;
            case "/d/Gondor/emyn-muil":
                where += "the Emyn-Muil area of Gondor";
                break;
            case "/d/Gondor/gwathlo":
                where += "the Gwathlo river in Gondor";
                break;
            case "/d/Gondor/lebennin":
                where += "the land of Lebennin in Gondor";
                break;
            case "/d/Gondor/minas":
                where += "the city Minas Tirith in Gondor";
                break;
            case "/d/Gondor/mordor":
                where += "the land of Mordor";
                break;
            case "/d/Gondor/morgul":
                where += "the city of Minas Morgul";
                break;
            case "/d/Gondor/pelargir":
                where += "the city of Pelargir in Gondor";
                break;
            case "/d/Gondor/rohan":
                where += "the land of Rohan";
                break;
            case "/d/Gondor/tharbad":
                where += "the Tharbad area of in Gondor";
                break;
            default:
                {
                    if(circle_region = room->query_circling_region())
                    {
                        where += implode(map(explode(circle_region, " "), 
                            capitalize), " ") + " in Gondor";
                    }
                    else
                    {
                        where += "the realm of Gondor";
                    }
                    break;
                }
            }
            break;
        case "Ansalon":
            where += "the continent of Ansalon";
            break;
        case "Avenir":
            where += "the lands of Avenir";
            break;
        case "Calia":
            where += "the lands of Calia";
            break;
        case "Cirath":
            where += "the lands of Athas";
            break;
        case "Emerald":
            where += "the lands of Emerald";
            break;
        case "Genesis":
            where += "the Sparkle area";
            break;
        case "Immortal":
            where += "the lands of Immortal";
            break;
        case "Kalad":
            where += "the lands of Kalad";
            break;
        case "Khalakhor":
            where += "the lands of Khalakhor";
            break;
        case "Krynn":
            where += "the lands of Krynn";
            break;
        case "Shire":
            where += "the lands of the Shire";
            break;
        case "Terel":
            where += "the lands of the Terel";
            break;
        default:
            where += "some unknown land.";
            break;
        }
        j = sizeof( mages );
        for (i=0;i<j;i++)
        {
            mroom = environment( mages[i] );
            if (!(mroom->query_prop( ROOM_I_INSIDE )) &&
                (mroom != room))
            {
                mages[i]->catch_msg( where+ ".\n", this_player() );
            }    
        }
        return 1;
    }
    oblist = parse_this( how[0], "[at] [the] %l" );
    oblist -= ({ this_player() });
    if (!sizeof( oblist ))
    {
        notify_fail( "Shriek at whom?\n" );
        return 0;
    }

    target( " shrieks"+ how[1]+ " at you.", oblist );
    actor( "You shriek"+ how[1]+ " at", oblist, "." );
    all2act( " shrieks"+ how[1]+ " at", oblist, "." );
    MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_EMOTION );
    return 1;
}

public int slave_speak(string str)
{
	object oActor = this_player ();
	int    iListener;
	object oListener;
	object *aoListeners;
	
	notify_fail ("What do you want to say?\n");
	
	if (!strlen (str)) return (0);
	
    string text = "You hiss in the dialect of the slaves: " + str;
	write (text + "\n");
    this_player()->gmcp_comms("mssay", 0, text);

	aoListeners = FILTER_LIVE (all_inventory (environment (oActor)) - ({ oActor }));
	for (iListener = 0 ; iListener < sizeof (aoListeners) ; iListener ++)
	{
		oListener = aoListeners [iListener];
		if(IS_MEMBER (oListener))
		{
            string message = oActor->query_The_name (oListener) + " hisses in the dialect of the slaves: " + str;
			oListener->catch_tell (message + "\n");
            oListener->gmcp_comms("mssay", oActor->query_The_name (oListener), message);
		}
		
		else if(ORC_MEMBER(oListener) || URUK_MEMBER(oListener) || oListener->query_wiz_level())
		{
            string message = oActor->query_The_name (oListener) + " hisses in the black tongue: " + str;
			oListener->catch_tell (message + "\n");
            oListener->gmcp_comms("mssay", oActor->query_The_name (oListener), message);
		}

		else	
		{
            string message = oActor->query_The_name (oListener) + " hisses something unintelligible.";
			oListener->catch_tell (message + "\n");
            oListener->gmcp_comms("mssay", oActor->query_The_name (oListener), message);
		}
		
	}
	
	return (1);
}
