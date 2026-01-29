mapping		info_map = ([]);/* Contains indexes in the help map file. */
static int	index_line,	/* The current index line. */
		count_line;	/* The number of lines in a help text. */
static string	command_name;	/* The current command name. */

#define HELP_FILE	H_GUILD_DIR + "infofile"
#define INDEX_FILE	H_GUILD_DIR + "infoind"
#define BASE_COMMAND	"info"

void
load_index()
{
    setuid(); seteuid(getuid());

    if(!m_sizeof(info_map))
	restore_object(INDEX_FILE);
}

int
do_index(string what)
{
    notify_fail("Index what? The info-file?\n");

    if(strlen(what) && what == "info-file")
    {
	call_out("index_loop", 0, 1);
	write("Starting indexing.\n");
	return 1;
    }
}

/*
 * index_loop - Index the help file.
 */
public void
index_loop(int cmd)
{
    int i;
    string line, name;
    
    setuid();
    seteuid(getuid());

    /*
     * Start the process.
     */
    if (cmd == 1)
    {
	info_map = ([]);
	index_line = 0;
	count_line = 0;
	command_name = "";
    }

    call_out("index_loop", 10, 0);

    /*
     * Read 50 lines at a time.
     */
    for (i = 0 ; i < 50 ; i++)
    {
	line = read_file(HELP_FILE, index_line, 1);
	if (!strlen(line))
	{
	    info_map += ([ command_name + "_len" : count_line ]);
	    seteuid(getuid());
	    save_object(INDEX_FILE);
	    remove_call_out("index_loop");
	    index_line = 0;
	    return;
	}
	
	if (sscanf(line, "#ENTRY %s\n", name) == 1)
	{
	    if (count_line > 0)
	    {
		info_map += ([ command_name + "_len" : count_line ]);
		count_line = 0;
	    }

	    command_name = name;
	    info_map += ([ command_name : index_line + 1]);
	}
	else
	    if (command_name != "")
		count_line++;

	index_line++;
    }
}

int
not_len(string what)
{
    string d;
    return sscanf(what, "%s_len", d)!=1;
}

int
sort_ind(string a, string b)
{
    if(a<b) return -1;
    if(b>a) return 1;
    return 0;
}

/*
 * do_info - Do help for 'info'
 */
do_info(string cmd)
{
    int line;

    setuid(); seteuid(getuid());

    if (index_line != 0)
    {
	write("Automatic indexing of help file in progress... please try later.\n" + "Indexing at line " + index_line + " of the help file.\n");
	return 1;
    }

    if (file_time(HELP_FILE) > file_time(INDEX_FILE + ".o"))
    {
	if (index_line == 0)
	{
	    index_loop(1);
	    write("Automatic indexing of help file in progress... please try later.\n" + "Indexing at line " + index_line + " of the help file.\n");
	    return;
	}
    }

    if(!m_sizeof(info_map))
	load_index();

    switch (lower_case(cmd))
    {
    case 0:
    case "":
	write(read_file(HELP_FILE, info_map["info"], info_map["info_len"]));
	break;

    case "subjects":
    case "-s":
    case "-info":
    case "index":
	write("Available 'info' commands: \n" +
	    sprintf("%-20#s", implode(sort_array(
		filter(m_indexes(info_map), "not_len", TO),
		"sort_ind", TO),"\n"))+
	    ".\n");
	break;

    default:
	if (!(line = info_map[cmd]))
	    return notify_fail("That command does not exist in the helpfile.\n");
	else
	    write(read_file(HELP_FILE, line, info_map[cmd + "_len"]));
	break;
    }
    return 1;
}
