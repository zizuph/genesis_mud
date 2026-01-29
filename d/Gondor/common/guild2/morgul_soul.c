/*
 * The soul of the Morgul mages.
 * /d/Gondor/common/guild2/morgul_soul.c
 *
 * Created: Soermo
 *
 * Modification log:
 * 06-jan-1994: recoded by Olorin
 *              added mtitles, moved emotes to lib/morgul_emotes.h
 * Dec 1999   : Morbeche
 *              Split rasp and hiss into rasp/mrasp and hiss/mhiss 
 * 
 * Feb 8, 2006: Altrus
 *   Added in the command for 'msay', to speak in the dialect of 
 *   the orc and uruk race guilds
 */
#pragma save_binary
#pragma strict_types

inherit "/cmd/std/command_driver.c";

#include <adverbs.h>
#include <cmdparse.h>
#include <composite.h>
#include <filter_funs.h>
#include <formulas.h>
#include <macros.h>
#include <options.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/guild2/newspells/spells.h"

#include "/d/Gondor/common/guild2/lib/morgul_defs.h"
#include "/d/Gondor/common/guild2/lib/morgul_funcs.h"
#include "/d/Gondor/common/guild2/lib/morgul_emotes.h"
#include "/d/Gondor/common/guild2/lib/morgul_lieutenant.h"
#include "/d/Gondor/common/guild2/lib/morgul_nazgul.h"
#include "/d/Gondor/common/guild2/lib/mtrack.h"

public string  get_soul_id()
{
    return GUILD_NAME;
}

public int query_cmd_soul()
{
    return 1;
}

void
create()
{
    setuid();
    seteuid( getuid() );
}

public mapping
query_cmdlist()
{
    return ([
        "approve"    : "approve",
        "aware"      : "aware",
        "battlesong" : "battlesong",
        "chant"      : "recite",
        "damn"       : "damn",
        "designate"  : "designate_ingredient",
        "exalt"      : "exalt",
        "expel"      : "nazgul_expel",
        "fog"        : "fog",
        "gaze"       : "gaze",
        "guildlist"  : "guildlist",
        "hail"       : "hail",
        "mhail"      : "hail",
        "help"       : "help",
        "hgaze"      : "hgaze",
        "leer"       : "leer",
        "list"       : "list_spells",
        "loom"       : "loom",
        "magelist"   : "list_active_mages",
        "marm"       : "marm",
        "mamuse"     : "mamuse",
        "manger"     : "manger",
        "mbrood"     : "mbrood",
        "mbeckon"    : "mbeckon",
        "mcall"      : "mcall",
        "mcurse"     : "curse",
        "mdismiss"   : "mdismiss",
        "mgaze"      : "mgaze",
        "mglare"     : "mglare",
        "mgrab"      : "mgrab",
        "hiss"       : "mhiss",
        "mhiss"      : "hiss_emote",
        "mhood"      : "mhood",
        "mlaugh"     : "mlaugh",
        "mleer"      : "leer",
        "mlist"      : "list_active_mages",
        "minspect"   : "minspect",
        "mlook"      : "mlook",
        "mnarrow"    : "mnarrow",
        "mordor"     : "mordor",
        "mopine"     : "mopine",
        "mremember"  : "mage_remember",
        "mreveal"    : "mreveal",
        "mscoff"     : "mage_scoff",
        "mslap"      : "mslap",
        "msmile"     : "mage_smile",
        "msniff"     : "do_msniff",
        "msummon"    : "msummon",
        "mtitles"    : "morgul_titles",
        "mturn"      : "mturn",
        "punish"     : "nazgul_punish",
        "shriek"     : "shriek",
        "msneer"     : "msneer",
        "rasp"       : "rasp_say",
        "mrasp"      : "rasp_emote",
        "mrecite"    : "recite",
        "regard"     : "regard",
        "reward"     : "nazgul_reward",
        "tempt"      : "tempt",
        "torture"    : "torture",
        "mwail"      : "mwail",
        "withdraw"   : "withdraw",
        "wrath"      : "wrath",
        "mssay"      : "slave_speak",
	    "ms"         : "slave_speak",
    ]);
}

public int
query_is_morgul_mage(object x)
{
    return (x->query_guild_name_occ() == GUILD_NAME);
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

    mage_list = "The members of the Society of Morgul Mages currently "+
        "in the realms:\n";
    list = filter( users(), query_is_morgul_mage );
    list = sort_array( list, "compare_rank" );
    
    if(find_living("toby"))
    {
	mage_list += ": Toby Tainawath, Emissary of the Black Master\n";
	cnt++;
    }

    if(find_living("gorboth"))
    {
	mage_list += ": Gorboth Nwalkaer, Emissary of Lord Sauron the Great\n";
	cnt++;
    }

    i = -1;
    while (++i < sizeof( list ))
    {
        if (list[i]->query_guild_name_occ() == GUILD_NAME)
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
                    mage_title = ", "+ list[i]->query_morgul_title();
                    mage_list += ": "+ capitalize( magename )+ mage_title;
                    mage_title = MORGUL_MASTER->query_mage_name( magename );
                    if (strlen( mage_title ))
                    {
                        mage_list += ", " + mage_title;
                    }
                    if (list[i]->query_ghost())
                    {
                        mage_list += " <dead>";
                    }
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

    write (mage_list);
    return 1;
}

public int guildlist( string str )
{
 string name;
 object ob;

    if (str)
    {
        if (this_player->query_wiz_level())
        {
            name = capitalize( str ) + " is ";
            notify_fail( "No such player found.\n" );
            if (!(ob = find_player( str )))
            {
                return 0;
            }
        } 
        else
        {
            write( "Curious aren't we?\n" );
            return 1;
        }
    }
    else
    {
        ob = this_player();
        name = "You are ";
    }

    str = ob->list_mayor_guilds();
    if (str)
    {
        write( name+ "member of following guilds:\n"+ str );
    }
    else
    {
        write( name+ "not member of any guilds.\n" );
    }

    return 1;
}

public int help( string str )
{
 int guild_level;
 string subject, filename;

    if (!strlen( str ))
    {
        return 0;
    }

    setuid();
    seteuid( getuid() );

    if ((str == "morgul") || (str == "mages") || (str == "guild"))
    {
        cat( GUILD_HELP + "commands" );
        return 1;
    }
    if ((sscanf( str, "mages %s", subject ) != 1) &&
        (sscanf( str, "morgul %s", subject ) != 1))
    {
        return 0;
    }

    guild_level = (this_player()->query_wiz_level() ? 25 :
        this_player()->query_morgul_level());
    switch (subject)
    {
    case "nazgul":
    case "anghoth":
        if (!nazgul_test())
        {
            return 0;
        }
        break;
    case "lieutenant":
        if (!lieutenant_test() && !nazgul_test())
        {
            return 0;
        }
        break;
    case "emotions":
        if (TP->query_morgul_level() > APPRENTICE_LEVEL)
        {
            subject = "emotions_mage";
        }
        break;
    case "mortirio":
        if (guild_level < MS_MORTI_MIN)
        {
            return 0;
        }
        break;
    case "orekir":
        if (guild_level < MS_OREKI_MIN)
        {
            return 0;
        }
        break;
    case "naro":
        if (guild_level < MS_NARO1_MIN)
        {
            return 0;
        }
        break;
    case "arhalgul":
        if (guild_level < MS_ARHAL_MIN)
        {
            return 0;
        }
        break;
    case "dramalgos":
        if (guild_level < MS_DRAMA_MIN)
        {
            return 0;
        }
        break;
    case "faugoroth":
        if (guild_level < MS_FAUGO_MIN)
        {
            return 0;
        }
        break;
    case "sauthacuith":
        if (guild_level < MS_SAUTH_MIN)
        {
            return 0;
        }
        break;
    case "ringurth":
        if (guild_level < MS_RINGU_MIN)
        {
            return 0;
        }
        break;
    case "narusse":
        if (guild_level < MS_NARUS_MIN)
        {
            return 0;
        }
        break;
    case "dollost":
        if (guild_level < MS_DOLLO_MIN)
        {
            return 0;
        }
        break;
    case "ephessul":
        if (guild_level < MS_EPHES_MIN)
        {
            return 0;
        }
        break;
    case "thunaur":
        if (guild_level < MS_THUNA_MIN)
        {
            return 0;
        }
        break;
    case "nifarist":
        if (guild_level < MS_NIFAR_MIN)
        {
            return 0;
        }
        break;
    case "gostangwedh":
        if (guild_level < MS_GOSTA_MIN)
        {
            return 0;
        }
        break;
    case "artirith":
        if (guild_level < MS_ARTIR_MIN)
        {
            return 0;
        }
        break;
    case "crabandir":
        if (guild_level < MS_CRABA_MIN)
        {
            return 0;
        }
        break;
    case "morthul":
        if (guild_level < MS_MORTH_MIN)
        {
            return 0;
        }
        break;
    case "sulambar":
        if (guild_level < MS_SULAM_MIN)
        {
            return 0;
        }
        break;
    case "yalarochrama":
        if (guild_level < MS_YALAR_MIN)
        {
            return 0;
        }
        break;
    }

    filename = GUILD_HELP + subject;
    if (file_size( filename ) > 0)
    {
        cat( filename );
        return 1;
    }
    return 0;
}

string known( object first, object second )
{
    if (second->query_met( first ))
    {
        return (first->query_name());
    }
    else
    {
        return (LANG_ADDART(first->query_gender_string())+ " "+
            first->query_race_name());
    }
}

public int morgul_titles( string str )
{
 string  titles, *male_titles, *female_titles;
 int i;

    notify_fail( "'mtitles' lists the titles available within the guild "+
        "of the Morgul Mages.\n"+ "Syntax: mtitles\n" );
    if (strlen( str ))
    {
        return 0;
    }

    setuid();
    seteuid( getuid() );
    MORGUL_MASTER->load_me();
    male_titles = MORGUL_MASTER->query_male_titles();
    female_titles = MORGUL_MASTER->query_female_titles();

    titles  = sprintf( "  %4s  %-30s   %-30s\n", "Rank", "Male Titles", "Female Titles");
    titles +=          " -----------------------------------------------------------------------\n";
    titles +=          "   [C]  Beleg na Nazgul,                 Beleg na Nazgul,               \n";
    titles +=          "        Heru na Minas Morgul             Híril na Minas Morgul          \n";
    titles +=          "   [C]  Nazgul                           Nazgul                         \n";
    titles +=          " -----------------------------------------------------------------------\n";
    titles +=          "        Istar na Morgul                  Istar na Morgul                \n";
    titles +=          " -----------------------------------------------------------------------\n";

    i = sizeof( male_titles ) - 1;
    titles += sprintf("        %-30s   %-30s\n", 
      male_titles[i], female_titles[i]);
    titles +=          " -----------------------------------------------------------------------\n";

    //while (i--)
    while(i-- && i > 12)
    {
        titles += sprintf("  %4s  %-30s   %-30s\n", "["+(i+1)+"]",
            male_titles[i], female_titles[i]);
    }

    i++;
    titles +=          " -----------------------------------------------------------------------\n";

    while (i--)
    {
        titles += sprintf("  %4s  %-30s   %-30s\n", "["+(i+1)+"]",
            male_titles[i], female_titles[i]);
    }
    
    write( titles );

    return 1;
}

public int sort_spells( string sp1, string sp2 )
{
    return (MORGUL_SPELL_FILE->query_spell_morgul_level( sp1 )-
        MORGUL_SPELL_FILE->query_spell_morgul_level( sp2 ));
}

/*
 * List all spells, including the level at which they become available
 */
public int list_spells( string str )
{
 int i, j, s, level, ntitles;
 object  tp = this_player();
 string *spells, *titles, title, msg =
     "\n\t ________________________________________________ \n"+
      "\t/                                                \\\n"+
      "\t|  The Dark Lord has granted you these spells:   |\n"+
      "\t|  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~   |\n";

    if (str != "spells")
    {
        return 0;
    }

    spells = sort_array( tp->query_spells(), "sort_spells" );

    setuid();
    seteuid( getuid() );
    MORGUL_SPELL_FILE->load_me();

    if (tp->query_gender() == 1)
    {
        titles = MORGUL_MASTER->query_female_titles();
    }
    else
    {
        titles = MORGUL_MASTER->query_male_titles();
    }

    ntitles = sizeof( titles );
    j = sizeof( spells );
    for (i=0,s=j;i<s;i++)
    {
        level = MORGUL_SPELL_FILE->query_spell_morgul_level( spells[i] );
        if (level < ntitles)
        {
            title = titles[level];
        }
        else
        {
            title = "Nazgul";
        }
        msg += sprintf( "\t|  %-13s - %-28s  |\n", spells[i],  title );
    }
    msg += "\t\\________________________________________________/\n\n";
    write( msg );
    return 1;
}
