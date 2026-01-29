/* Standard book for the library                */
/*    Cirion 032796                             */

inherit "/std/book";
inherit "/d/Avenir/inherit/tail.c";

#include "/d/Avenir/common/common.h"
#include "/d/Avenir/include/book.h"

int      type,
         lang_to_read;
string   f_name,
         blank_page = "This page appears to be blank.\n";
mixed   *a_name;

public void create_book()
{
  set_name("tome");
  set_short("massive dusty tome");
  set_long("It is a massive tome, heavy and "
          +"unwieldly.\n");
}

varargs public mixed long(string str, object for_obj)
{
  string mystr;
  
  if(book_is_closed)
   mystr = "It is closed.\n";
  else mystr = "It is opened to the "+LANG_WORD(what_page)+" page.\n";

  return ::long(str, for_obj) + mystr;
}

/*
 * Function name: read_book_at_page
 * Description:   should be redefined in your book. is called from read_me
 * Arguments:	  which - read the book at which page
 *		  verb  - If the player wanted to read it, or mread it.
 *			  To mread something, you can look how the scoll.c does
 *			  it in read_it() if needed.
 */
varargs void
read_book_at_page(int which, string verb)
{ 
  string  written,
         *nihil = allocate(query_max_pages() + 20);
  int     i;
  
  if(!CAN_SEE_IN_ROOM(TP))
  {
    write("You cannot see to read.\n");
    return;
  }

  if(!CAN_SEE(TP, TO))
  {
    write("Read what?\n");
    return;
  }

  if(TP->query_skill(SS_LANGUAGE) < lang_to_read)
  {
    write("The words are in a language you do not understand.\n");
    return;
  }

  seteuid(getuid());

  switch(type)
  {
    case BOOK_TEXT:
    case 0: // Let it be a text file by default...
      written = read_file(f_name, ((which - 1) * PAGELENGTH), PAGELENGTH);
      break;
    case BOOK_ARRAY:
      written = "";
      for(i=0;i<sizeof(PAGELENGTH);i++)
      {
        if(i + (PAGELENGTH * which) < sizeof(a_name))
          written += a_name[i + (PAGELENGTH * which)] + "\n";
      }
      break;
    case BOOK_BTEXT:
      nihil = explode(read_file(f_name), "**");
      if(sizeof(nihil) > which)
        written = nihil[which-1];
      else
        written = "";
      break;
    default:
      written = "";
      break;
   }

  if(!strlen(written) || written == "0")
    TP->catch_msg(blank_page);
  else
    TP->catch_msg(written);
}

/*
 * Function:  text_file
 * Arguments: file - the filename
 *            flag - 1 if it is the whole path,
 *                   otherwise <file path for this_object()>/<file>.book
 * Returns:   1 OK
 *           -1 File does not exist.
 */
varargs int text_file(string file, int flag)
{
  string   path,
          *words;
  int      i;

  seteuid(getuid());

  words = explode(file_name(TO), "/");
  path = "";

  for(i=0;i<(sizeof(words)-1);i++)
    path += words[i] + "/";

  if(flag)
   f_name = file;
  else
   f_name = path + file + ".book";

  if(!file_size(file))
   return -1;

  return 1;
}

string query_file()
{
  return f_name;
}

int set_array(mixed *arg)
{
  if(!sizeof(arg))
    return 0;

  a_name = arg;
  return 1;
}

void set_blank_page(string str)
{
  blank_page = str;
}

void set_lang_to_read(int num)
{
  if(num > 100)
   lang_to_read = 100;
  else if(num < 0)
   lang_to_read = 0;
  else
   lang_to_read = num;
}

void set_max_pages(int num)
{
  add_prop(OBJ_I_WEIGHT, (num * 100));
  add_prop(OBJ_I_VOLUME, (num * 210));
  ::set_max_pages(num);
}

void set_book_type(int what)
{
  type = what;
}

string query_book_type()
{
  switch(type)
  {
    case 0: return "No type set\n"; break;
    case BOOK_TEXT: return "Basic text file\n"; break;
    case BOOK_ARRAY: return "Array\n"; break;
    case BOOK_BTEXT: return "Broken text\n"; break;
    default: return "Illegal type\n"; break;
  }
}

/*
 * Function name: read_scroll
 * Description:   We need some special stuff for the turn page command
 *		  The turn page has the following syntax
 *		    turn page - turn forward one page
 *		    turn page forward/[backward, back] - turn one page
 *			in the appropriate direction
 *		    turn book to/at page <num> - turn to page <num>
 *			where <num> is a string like one, two, eight,
 *			not an integer like 7.
 */
mixed
read_scroll(string str)
{
    string where, what;

    if (!str)
	return ::read_scroll(what);

    if (str == "page")
    {
	gPage = "forward";
	what = "book";
    }
    else if (parse_command(str, ({}), "'last' [page] / [entry]" )) 
    {   
	return ::tail_file(f_name);
    }
    else if (parse_command(str, ({}), "'page' [to] %w", where)) 
    {
	gPage = where;
	what = "book";
    }
    else if (!parse_command(str, ({}), "%s 'at' / 'to' 'page' %w", what, where))
    {
	gPage = "";
	what = str;
    }
    else
	gPage = where;

    return ::read_scroll(what);
}
