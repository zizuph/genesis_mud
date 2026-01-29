inherit "/std/object";
#include "/d/Kalad/defs.h"


#define MORE_PAGESIZE (20)
#define MORE_PROMPT   write("-- More -- " + lineno +             \
		      ((numlines > 1) ? ("/" + numlines) : "") + \
		      " -- (<cr> t b r a <num> q x !<cmd> h ?) -- ")
#define MORE_DONE     if (functionp(ret_func)) { ret_func(); }
#define MORE_INPUT    input_to(&input_to_more(, lines, filename, \
					ret_func, first, lineno))


/*
 * Prototypes
 */
int mtail(string filename, function func);
public nomask varargs int more(string arg, int start, function func, int top);
static nomask void input_to_more(string answer, string *lines, string filename,
  function ret_func, int first, int lineno);


static nomask void
input_to_more(string answer, string *lines, string filename,
  function ret_func, int first, int lineno)
{
    int    index;
    int    pagesize;
    string error;
    int    numlines = sizeof(lines);

    pagesize = (((pagesize = TP->query_option(OPT_MORE_LEN)) < 5) ?
      MORE_PAGESIZE : pagesize);
    answer = lower_case(answer);

    if (stringp(answer) &&
      (sscanf(answer, "%d", index) == 1))
    {
	lineno = index + pagesize - 1;
	answer = "Goto";
    }

    switch (answer)
    {
    case "":
	lineno += pagesize;
	break;

	/* Since we use the lower case of answer, this can never be triggered
	 * by the command of a player, so we can use it as a flag to check on
	 * numerical input.
	 */
    case "Goto":
	break;

    case "q":
    case "quit":
    case "x":
    case "exit":
	MORE_DONE;
	return;

    case "?":
    case "h":
    case "help":
	write(
	  "\nAvailable commands:\n\n" +
	  "   <return>     press <return> to display next page\n" +
	  "   t(op)        go to top of document\n" +
	  "   b(ack)       go back one page\n" +
	  "   r(edisplay)  display the same page again\n" +
	  "   <number>     go to line <number>\n" +
	  "   a(ll)        display all the text remaining if it isn't too much\n" +
	  "   h(elp) or ?  display this help message\n" +
	  "   !<command>   escape and execute <command>, then continue reading\n" +
	  "   q(uit)       quit reading document\n" +
	  "(e)x(it)        exit reading document\n\n");
	MORE_PROMPT;
	MORE_INPUT;
	return;

    case "t":
    case "top":
	lineno = first;
	break;

    case "r":
    case "redisplay":
	break;

    case "b":
    case "back":
    case "p":
    case "previous":
	lineno -= pagesize;
	break;

    case "a":
    case "all":
	if (stringp(filename))
	{
	    if (strlen(error = catch(cat(filename, lineno + 1))))
	    {
		write("Cannot print remainder: " + error);
		MORE_PROMPT;
		MORE_INPUT;
		return;
	    }
	    write("EOF\n");
	}
	else
	{
	    if (strlen(error = catch(write(implode(lines[lineno..], "\n")))))
	    {
		write("Cannot print remainder: " + error);
		MORE_PROMPT;
		MORE_INPUT;
		return;
	    }
	}
	MORE_DONE;
	return;

    default:
	MORE_PROMPT;
	MORE_INPUT;
	return;
    }	

    if (lineno < (pagesize + first))
    {
	lineno = pagesize + first;
    }

    if (stringp(filename))
    {
	/* Cat will return the number of lines that are actually read.
	 * If you read beyond the EOF, the reading will stop. This means
	 * that if the last chunk is exactly one page, you still have to
	 * read the EOF sign.
	 */
	if (cat(filename, (lineno - pagesize + 1), pagesize) < pagesize)
	{
	    write("EOF\n");
	    MORE_DONE;
	    return;
	}
    }
    else
    {
	for (index = (lineno - pagesize);
	  ((index < lineno) && (index < numlines)); index++)
	{
	    write(lines[index] + "\n");
	}

	if (lineno >= numlines)
	{
	    MORE_DONE;
	    return;
	}
    }

    MORE_PROMPT;
    MORE_INPUT;
    return;
}


int
mtail(string filename, function ret_func)
{
    int flen, pagelen, startline, size;

    if ( (size = file_size(filename)) < 1)
	return 0;

    if (size > 50000)
    {
	tail(filename);
	MORE_DONE;
    }

    else
    {
	pagelen = (((pagelen = TP->query_option(OPT_MORE_LEN)) < 5) ?
	  MORE_PAGESIZE : pagelen);

	flen = sizeof(explode(read_file(filename), "\n"));
	startline = flen - pagelen;
	if (startline < 0)
	    startline = 0;

	input_to_more("",0,filename,ret_func,0,startline);
    }

    return 1;
}


public nomask varargs int
more(string arg, int start, function func, int top)
{
    string *lines, filename;

    if (start)
    {
	filename = arg;
	lines = 0;
	start--;
    }

    else
    {
	filename = 0;
	lines = explode(arg, "\n");
    }

    input_to_more("", lines, filename, func, top, start);
    return 1;
}
