// file name:        /d/Avenir/smis/modules/statserv.c
// creator(s):       Denis, Apr 1996
// purpose:          The statistic server.
//		     Provides means of gathering statistical information,
//		     saving it for later use and showing it in convinient
//		     form.
//
//		     THIS IS A SMIS MODULE!
// note:             For additional information see
//			/d/Avenir/smis/doc/statserv.doc
/*  
 * Revisions:
 *	Denis, May 1996: Changed it to use SMIS and moved to
 *			 /d/Avenir/smis/modules/statserv.c
 *	Lucius, Jul 2017: Misc. Cleanups.
 */
#pragma strict_types

#include <mail.h>
#include <std.h>

#include "../smis.h"
#include "../sys.h"

inherit SMIS_MODULE;

#define STATSERV_DATA_DIR	(data_dir + "statserv/")
#define STATSERV_CURRENT_FILE	(STATSERV_DATA_DIR + "current")

#define STATSERV_FNAME		"fname"
#define STATSERV_START		"date_start"
#define STATSERV_FINISH		"date_finish"


mapping gStatistics,
        gOld_statistics;

int gAlarm_id;

static string	gCaption =
"Statserv module: ----------------------------------------------------------\n",
		gBottom =
"---------------------------------------------------------------------v.1.00\n",
		data_dir;

/* Prototypes.
 */
string ctime2fname(string t);
void initiate_save();
void perform_save();
void send_statistics_mail();

/*
 * Function name: create_module
 * Description:   The statserv initialization.
 */
void create_module()
{
    seteuid(getuid());

    set_module_id("statserv");
    set_module_description("Domain statistics server v.1.00");

    data_dir = SMIS_MANAGER->query_data_dir();

    if(file_size(STATSERV_CURRENT_FILE + ".o") > -1)
        gStatistics = restore_map(STATSERV_CURRENT_FILE);
    else
    {
	gStatistics = ([ STATSERV_START : ctime(time()),
			 STATSERV_FNAME : ctime2fname(ctime(time())) ]);
	save_map(gStatistics, STATSERV_CURRENT_FILE);
    }
}

/*
 * Function name: ctime2fname
 * Description:   Converts the string representation of date (returned
 *		  by ctime()) to <day><month><year>.
 * Arguments:     t - the string to convert from.
 * Returns:       The converted string.
 */
string ctime2fname(string t)
{
    string day_of_week,
	   month,
	   day,
	   time,
	   year;

    if(t[8] == ' ')
	sscanf(t, "%s %s  %s %s %s", day_of_week, month, day, time, year);
    else
        sscanf(t, "%s %s %s %s %s", day_of_week, month, day, time, year);

    return day + month + year;
}

/*
 * Function name: topic_statistics
 * Description:   Returns the informatioon about one topic.
 * Arguments:     
 * Returns:       
 */
static string topic_statistics(mapping topic_data, string topic)
{
    string *topic_parts,
	   res;
    int i;

    res = "\nTopic: " + topic + ".\n";

    topic_parts = m_indexes(topic_data);
    for(i = 0; i < sizeof(topic_parts); i++)
	res += sprintf("   %-50s%s\n", topic_parts[i] + ":",
				       "" + topic_data[topic_parts[i]]);

    return res;
}

/*
 * Function name: statistics
 * Description:   Generates the data from the mapping containing statistical
 *		  information.
 * Arguments:     st - the mapping containing the information;
 *		  str - the topic to give the information about.
 * Returns:       The statistical information (if topic is given) or
 *		  the list of topics (if the topic is not given).
 */
static string statistics(mapping st, string str)
{
    string *dm,
	   *topics,
	   topic,
	   res;
    int i, j;

    res ="\n" +
	 "Started on:             " + st[STATSERV_START]  + "\n" +
	 (st[STATSERV_FINISH] ?
	 "Finished on:            " + st[STATSERV_FINISH] + "\n": "");

    if(!strlen(str))
    {
	dm = m_indexes(st) -
	    ({ STATSERV_START, STATSERV_FINISH, STATSERV_FNAME });
	return res +
		(sizeof(dm) ?
		"\nThe following topics are present:\n" +
		break_string(implode(dm, ", "), 60) + ".\n" :
		"\nNo topics present.\n");
    }

    if(str == "all")
	topics = m_indexes(st);
    else
	topics = explode(str, " ");

    topics -= ({ STATSERV_FNAME, STATSERV_START, STATSERV_FINISH });
    for(i = 0; i < sizeof(topics); i++)
    {
	topic = topics[i];
        if(!m_sizeof(st[topic]))
           res += "\nNo such topic: " + topic +".\n";
	else
	   res += topic_statistics(st[topic], topic);
    }

    return res;
}

/*
 * Function name: show_statistics
 * Description:   Interface function for 'stat' module command.
 * Arguments:     str - the topic inquired (if any).
 * Returns:       The information that will be shown on user's screen.
 */
public string show_statistics(string str)
{
    return gCaption + "Current information:\n" +
	   statistics(gStatistics, str) + gBottom;
}

/*
 * Function name: show_old_statistics
 * Description:   Interface to 'oldstat' module command.
 * Arguments:     file - the filename (without .o) of the old data;
 *		  str  - the topic inquired (if any).
 * Returns:	  The information that will be printed on users screen.
 */
public string show_old_statistics(string file, string str)
{
    string res;

    if(!gOld_statistics || gOld_statistics[STATSERV_FNAME] != str)
        gOld_statistics = restore_map(STATSERV_DATA_DIR + file);
    return gCaption + "Old information:\n" +
	   statistics(gOld_statistics, str) + gBottom;
}

/*
 * Function name: log_event
 * Description:   This function is used to notify the statserv that a
 *		  particular event happened.
 * Arguments:	  topic - The type (or area, etc) of event that happened.
 *		          should not be large, as user has to enter this
 *			  each time he wants the information about this
 *			  topic.
 *		  what -  The very short description of what happened.
 */
public void log_event(string topic, string what)
{
    mapping tmp;

    initiate_save();
    if(!m_sizeof(gStatistics[topic]))
	gStatistics[topic] = ([ ]);

    gStatistics[topic][what]++;
}

/*
 * Function name: initiate_save
 * Description:   Starts alarm to save the gathered information.
 *		  The data isn't saved immediately, as some events might come
 *		  in rapid succession (such as area entrances, etc.)
 */
void initiate_save()
{
    if(gAlarm_id)
	return;

    if(ctime(time())[0..2] == "Mon" &&
       gStatistics[STATSERV_FNAME] != ctime2fname(ctime(time())))
    {
	gStatistics[STATSERV_FINISH] = ctime(time());
	send_statistics_mail();
	save_map(gStatistics, STATSERV_DATA_DIR + gStatistics[STATSERV_FNAME]);
	gStatistics = ([ STATSERV_START : ctime(time()),
			 STATSERV_FNAME : ctime2fname(ctime(time())) ]);
	save_map(gStatistics, STATSERV_CURRENT_FILE);
    }
    gAlarm_id = set_alarm(600.0, 0.0, perform_save);
}

/*
 * Function name: perform_save
 * Description:   Saves the gathered data.
 */
void perform_save()
{
    gAlarm_id = 0;
    save_map(gStatistics, STATSERV_CURRENT_FILE);
}

int perform_stat_command(string foo)
{
    SMIS_CHECK_CALLER;

    write(show_statistics(strlen(foo) ? foo : 0));
    return 1;
}

int perform_oldstat_command(string foo)
{
    string arg1, arg2;

    SMIS_CHECK_CALLER;

    if(strlen(foo) &&
       parse_command(foo, ({ }), "%w %s", arg1, arg2))
	write(show_old_statistics(arg1, arg2));
    else
        write(gCaption + "Usage: aoldstat <statistics file> [<topic>]\n" +
		         "For more info see <astathelp>.\n" + gBottom);
    return 1;
}

int perform_mailto_command()
{
    object *mail_receivers =
	    SMIS_MANAGER->query_module_parameter("statserv", "mail receivers");

    SMIS_CHECK_CALLER;

    if(sizeof(mail_receivers))
    {
	if(member_array(this_player()->query_real_name(), mail_receivers) > -1)
	{
	    SMIS_MANAGER->set_module_parameter("statserv", "mail receivers",
				       mail_receivers -
				       ({ this_player()->query_real_name() }));
	    write(gCaption + "\n  You have been removed " +
		  "from the weekly statistics receivers list.\n\n" + gBottom);
	    return 1;
	}
	else
	    SMIS_MANAGER->set_module_parameter("statserv", "mail receivers",
				       mail_receivers +
				       ({ this_player()->query_real_name() }));
    }
    else
	SMIS_MANAGER->set_module_parameter("statserv", "mail receivers",
				   ({ this_player()->query_real_name() }));
	
    write(gCaption + "\n  You have been added to the " +
	  "weekly statistics receivers list.\n\n" + gBottom);
    return 1;
}

int perform_help_command()
{
    write(gCaption +
"Satistics Server Interface:\n\n" +
"The command 'stat' is used to show information that is currently\n" +
"gathered by the statistics server and 'aoldstat' is used to retrieve\n" +
"(obviously) the previously gathered information.\n\n" +
"The 'stat' command without arguments will give the list of topics\n" +
"the information is gathered for and with topic(s) (or keyword 'all') given\n" +
"as an argument will show the gathered information about the inquired topics.\n\n" +
"The 'oldstat' works the same as 'stat', but its first argument is\n" +
"used to notify which file containing previously gathered information\n" +
"to show.\n\n" +
"How server works and how to use it in your code see\n" + 
"  /d/Avenir/smis/doc/statserv.doc .\n" + gBottom);
	    return 1;
}

int perform_empty_command()
{
    write(gCaption + 
"The following module commands are implemented:\n\n" +
" - help:        I guess someone will actually check it out;\n" +
" - stat:        Shows the gathered statistics for this week;\n" +
" - oldstat:     Shows the statistics of one of the previous weeks;\n\n" +
" - mailto:      Adds/removes you to/from the list of the weekly statistics\n" +
"                mail receivers. THIS FEATURE DOESN'T WORK YET, SORRY.\n" +
" Be sure to read the files /d/Avenir/smis/doc/statserv.doc and\n" +
"                           /d/Avenir/smis/doc/stasterv.lst\n" + gBottom);
        return 1;
}

/*
 * Function name: send_statistics_mail
 * Description:   Sends the weekly mail to the recepients.
 */
void send_statistics_mail()
{
    string *mail_receivers;

    mail_receivers = SMIS_MANAGER->query_module_parameter("statserv",
							  "mail receivers");

    filter(mail_receivers,
	   &operator(!=)(WIZ_MORTAL) @ SECURITY->query_wiz_rank);

    SMIS_MANAGER->set_module_parameter("statserv", "mail receivers",
				       mail_receivers);

    if(sizeof(mail_receivers))
        MAIL_READER->create_mail("Statistics for "+gStatistics[STATSERV_FNAME],
			         implode(mail_receivers, " "),
			         "",
			         statistics(gStatistics, "all"));
}

/*
 * Function name: 
 * Description:   
 * Arguments:     
 * Returns:       
 */
