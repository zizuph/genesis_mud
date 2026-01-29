/* A std library for general purposes.
 * 
 * Aridor, 10/96
 *
 * update history:
 * Aridor 05/97: various fixes
 * Aridor 05/97: added later editing of the book (not finished yet)
 * Aridor 11/97: finished editing of an already present book
 * Milan  10/02: Runtime error fix. See around line 550.
 *
 * Allows the employment of a librarian to sort the books,
 * and different levels of accessability to the library.
 *
 * Usage Example:
 * --------------
 * void
 * create_room()
 * {
 *     // Standard room setup
 *     ...
 *
 *     // Library setup
 *     set_lib_id("vkeep_lib_id");
 *     set_lib_path("/d/Krynn/solamn/vin/library");
 *     set_default_topics((["General":0,"Knights Private":2]));
 *     set_lib_type(4);
 *     set_search_delay(6.7);
 *     set_max_librarian_num(1);
 *     setup_library();
 * }
 *
 * void
 * init()
 * {
 *     ::init();
 *     init_library();
 * }
 *
 * void
 * leave_inv(object player, object dest);
 * {
 *     library_leave_inv(player, dest);
 *     ::leave_inv(player, dest);
 * }
 *
 */

#include "lib.h"
#include <std.h>

string *librarian =({});
int max_lib_num = 1;
mapping topics = (["New Arrivals":1,
		   "Books":0,
		   "Trash":1]);
/* Contains something of the form: <topic>:<access level>
 * The number means: 0: Everyone has access
 *                   1: Librarian only
 *                 <n>: Special group only
 */

mapping books = ([]);
/* contains something of the form: <booktitle>:({<Full title>,<shelf/topic>,<author>})
 */

string lib_path = 0;
string lib_id   = "my_lib_id";
string lib_long = "great library";
float  search_delay = 5.0;
int lib_type = 0;
/* 0: allows borrowing of books
 * 1: allows writing new books
 * 2: employs a librarian
 * 4: appointed librarian
 */


static string oldtitle;
static string book_to_change;
static string* to_delete = ({});
static string* currently_borrowed = ({});
static string bookfile = BOOK;

#define BOOKLIST   m_indexes(books)
#define TOPICLIST  m_indexes(topics)


void
set_book_file(string file)
{
    bookfile = file;
}

void
set_default_topics(mapping tpc)
{
    topics = tpc;
    if (member_array("New Arrivals",TOPICLIST) == -1)
      topics += (["New Arrivals":1]);
    if (member_array("Trash",TOPICLIST) == -1)
      topics += (["Trash":1]);
}

void
set_lib_type(int id)
{
    lib_type = id;
}

void
set_lib_id(string id)
{
    lib_id = id;
}

void
set_lib_long(string id)
{
    lib_long = id;
}

void
set_lib_path(string path)
{
    if (!path || !strlen(path))
      return 0;
    if (path[strlen(path)-1..] == "/")
      lib_path = path;
    else
      lib_path = path+"/";
}

void
set_search_delay(float f)
{
    search_delay = f;
}

void
set_max_librarian_num(int i)
{
    max_lib_num = i;
}

void
setup_library()
{
    seteuid(getuid(TO));
    restore_object(MASTER);

    this_object()->add_prop(OBJ_S_WIZINFO,
			    "This is a library, derived from the standard " +
			    "library in Krynn. The following options are " +
			    "available for wizards (apart from what mortals " +
			    "can do):\n" +
			    "- Movebook <booktitle> to topic <topic>\n" +
			    "          to move a book from the one shelf to " +
			    "another shelf.\n" +
			    "          For adding new books to the library " +
			    "(after using the 'blank'\n" +
			    "          command), use 'movebook <title> to " +
			    "topic <topic>'\n" +
			    "          For throwing books into the trash use\n" +
			    "          'movebook <title> to topic trash', then\n" +
			    "- Erase <booktitle>\n" +
			    "          and follow the instructions given to get " +
			    "rid of a book completely.\n");
}

/*
void
create()
{
    create_library();
    seteuid(getuid(TO));
    restore_object(MASTER);
}
*/

nomask void
init_library()
{
    ADA("index");
    ADA("catalog");
    ADA("blank");
    ADA("borrow");
    ADD("my_return","return");
    ADA("appoint");
    ADA("unappoint");
    ADA("retire");
    ADA("movebook");
    ADD("erase_book","erase");
    ADD("my_create","create");
    ADA("uncreate");
    ADA("beautify");
    ADA("edit");
}

public void
hook_borrow()
{
    write("You start to search through the bookshelves, eager to find the " +
	  "book.\n");
    say(QCTNAME(TP) + " starts to look through the bookshelves.\n");  
}

public void
hook_leave_with_books(object who, int num)
{
    if (num == 1)
    {
	who->catch_msg("One of the library assistants runs after you and takes the " +
		       "book you didn't return.\n"); 
	tell_room(TO, QCTNAME(who) + " tried to take a book from " +
		  "the library. One of the library assistants got it back.\n",who);
    } 
    else if (num > 1) 
    {
	who->catch_msg("One of the library assistants runs after you and takes the " +
		       "books you didn't return.\n"); 
	tell_room(TO, QCTNAME(who) + " tried to take some books from " +
		  "the library. One of the library assistants got them back.\n",
		  who);
    }
}

public void
hook_appointed_info()
{
}

public int
hook_librarian_requirements()
{
    return 1;
}

/* state 0: give was ok,
 *       1: give failed, book was moved to room.
 */
public void
hook_give_blank_book(int state)
{
    say(QCTNAME(TP) + " got a blank book.\n");  
    write("You take a blank book from one of the shelves.\n");
    if (state)
    {
	say("But it was too heavy. The books falls to the ground.\n");
	write("It's to heavy for you, you drop it.\n");
    }
}

/* Returns 1 if book was found, 0 if something went wrong
 * (Player left the room, ...
 */
public int
hook_find_book(object who)
{
    if (!present(who,TO))
	return 0;
    return 1;
}

public void
hook_found_book(object who)
{
    tell_object(who, "You find the book in the shelf and take it.\n");
    tell_room(TO, QCTNAME(who) + " finds a book in one of the shelves.\n", who);
}

public void
hook_book_currently_borrowed(object who, string str)
{
    who->catch_msg("The book you have been looking for seems to have been borrowed.\n");
}

/* who: Person who was looking.
 * str: the bookname as given by 'who'
 */
public void
hook_book_not_found(object who, string str)
{
    if (P(who,TO))
      who->catch_msg("You could not find the book you were looking for. Be sure " +
		     "to give the full title (up to any '-' which may be " +
		     "present in the title).\n");
}

public void
hook_index_fail()
{
    write("You are not allowed to read the index.\n");
}

public int
hook_appoint_unappoint()
{
    return 0;
}

public int
hook_can_use_library()
{
    /* put checks for library npcs here */
    return 1;
}

public mixed
hook_can_access_catalog(int level)
{
    /* add special access levels here */
    return ({0,"No access"});
}


private int
lex_greater(string a, string b)
{
    if (a==b)
      return 0;
    else if (a > b)
      return 1;
    else
      return -1;
}

nomask mixed
can_access_catalog(int level)
{
    string ret = "No access";
    int access = 0;
    mixed tmp;

    if (level == 0)		/* free access */
    {
	ret = "";
	access = 1;
    }
    else if (level == 1)	/* librarian only */
    {
	ret = "Librarian only";
	if (member_array(TP->query_real_name(),librarian) != -1)
	{
	    if (hook_librarian_requirements())
	      access = 1;
	    else
	    {
		write("You do not meet the requirements to be the librarian. " +
		  "You have been automatically unappointed.\n");
		access = 0;
		librarian -= ({ TP->query_real_name(), 0 });
		save_object(MASTER);
	    }
	}
	else
	  access = 0;
    }
    /* add new general access levels here */
    else
    {
	tmp = hook_can_access_catalog(level);
	access = tmp[0];
	ret = tmp[1];
    }

    return ({ access, ret });
}

nomask void
library_leave_inv(object player, object dest)
{
    int took, i;
    object *ob;
  
    if (!player || !living(player))
      return;
  
    ob = deep_inventory(player);
    for (i = 0; i < sizeof(ob); i++)
      if (ob[i]->id(lib_id))
      {
	  took++;
	  currently_borrowed -= ({ ob[i]->query_bookname() });
	  ob[i]->remove_object();
      }

    if (took > 0)
      hook_leave_with_books(player, took);

    if (present(lib_id + "_new", player))
      player->catch_msg("Please remember to finish writing that book.\n");
}

/* prototype */
nomask int catalog(string str);

nomask int
index(string str)
{
    int i, acc;
    string *ltopics = sort_array(TOPICLIST,lex_greater);
    mixed access;

    if (str)
      return catalog(str);

    write("These Topics are available in the library:\n");
    for(i=0;i<m_sizeof(topics);i++)
    {
	acc = topics[ltopics[i]];
	access = can_access_catalog(acc);
	if (access[0] == 1) /* ok to access */
	  write(sprintf("  %-25s\t%-20s\n",ltopics[i],access[1]));
    }
    write("Use 'catalog <topic>' for a list of books within the topic.\n");
    return 1;
}

nomask int
catalog(string str)
{
    int i,j=0;
    int top;
    string *btitles;
    string txt;
    mapping tmp = mkmapping(map(TOPICLIST,lower_case),TOPICLIST);

    if (!str)
      return index(str);

    for(i=0;i<m_sizeof(tmp);i++)
      if (wildmatch(L(str)+"*",m_indexes(tmp)[i]))
      {
	  str = m_indexes(tmp)[i];
	  break;
      }

    NF("No such topic!\n");
    /* No real topic */
    if (member_array(L(str),m_indexes(tmp)) == -1)
      return 0;

    NF("You are not allowed access to this topic.\n");
    top = topics[tmp[L(str)]];
    /* Librarian only topic */
    if (!TP->query_wiz_level())
    {
	if (top == 1 && member_array(TP->query_real_name(), librarian) == -1)
	  return 0;
	
	if (!hook_can_access_catalog(top))
	  return 0;
    }
    btitles = sort_array(BOOKLIST,lex_greater);
    write(tmp[L(str)] + ":\n");
    for(i=0;i<m_sizeof(books);i++)
      if (L(books[btitles[i]][1]) == L(str))
      {
	  j++;
	  write("  " + books[btitles[i]][0] + "\n");
      }
    txt = (j == 1 ? "is one volume" : "are " + LANG_WNUM(j) + " volumes");
    write("There " + txt + " available.\n");
    return 1;
}


nomask string
bookname(string str)
{
    string str2;
    if (!str)
      return "";
    str2 = implode(explode(str," "),"");
    str2 = implode(explode(str2,"/"),"") + "-extra";
    return L(explode(str2,"-")[0]);
}

nomask int
blank()
{
    object book;
    int state;

    NF("What?\n");
    if (lib_type == 0 && !TP->query_wiz_level())
      return 0;

    if (!hook_can_use_library())
      return 0;
  
    seteuid(getuid(TO));
    book = clone_object(W_BOOK);
    book->add_name(lib_id + "_new");
    state = book->move(TP);
    if (state)
      book->move(TO,1);
    hook_give_blank_book(state);

    return 1;
}

nomask void
come_back(object who, string str)
{
    object book;
    int i, access;
    string bname = bookname(str);
    string shortname, longname, textname;
    string *adj;
    mapping topictmp = mkmapping(map(TOPICLIST,lower_case),TOPICLIST);
    string *tmp = sort_array(BOOKLIST,lex_greater);
    
    if (!str || str == "")
    {
	hook_book_not_found(who, str);
	return;
    }

    for(i=0;i<sizeof(tmp);i++)
      if (wildmatch(bname + "*",tmp[i]))
      {
	  bname = tmp[i];
	  break;
      }

    shortname = lib_path + "short/" + bname,
    longname = lib_path + "long/" + bname,
    textname = lib_path + "book/" + bname;
    
    if (!hook_find_book(who))
      return;
    
    if (file_size(lib_path + "short/" + bname) < 0)
    {
	hook_book_not_found(who, str);
	return;
    }

    /* This prevents people from reading books from restricted categories
     * If they are not, it tells them there is no such book :-E
     */
    
    /* !!! Need to get the access level from the bookname... */
    
    // Milan: This was added to prevent indexing on illegal type runtime
    if (sizeof(books[bname]) < 2)    
    {
	hook_book_not_found(who, str);
	return 0;
    }
    // Milan - I have removed define for this long line (used only here)
    access = topics[mkmapping(map(TOPICLIST,lower_case),TOPICLIST)[books[bname][1]]];
    if (!TP->query_wiz_level())
      if (!(can_access_catalog(access)[0]))
      {
	  hook_book_not_found(who, str);
	  return 0;
      }

    if (member_array(bname, currently_borrowed) != -1)
    {
	hook_book_currently_borrowed(who, str);
	return;
    }
    
    hook_found_book(who);
    book = clone_object(bookfile);
    book->add_name(lib_id);
    adj = explode(read_file(shortname), " ") - ({ "book" });
    for (i = sizeof(adj) - 1; i >= 0; i--)
      book->set_adj(adj[i]);
    book->set_name(adj[sizeof(adj) - 1]);

    book->set_short(read_file(shortname));
    book->set_long(read_file(longname));
    book->set_file(textname);
    book->set_bookname(bname,file_name(TO));
    book->move(who,1);
    
    currently_borrowed += ({ bname });
}

nomask int
borrow(string str)
{
    if (!hook_can_use_library())
      return 0;
    
    NF("Borrow what?\n");
    if (!str || str == "")
      return 0;

    hook_borrow();
    set_alarm(search_delay, 0.0, "come_back", TP, str);
    return 1;
}

nomask int
lib_books(object ob)
{
    return (ob->id(lib_id) || ob->id(lib_id + "_new"));
}

public nomask void
returned_book(string bname)
{
    currently_borrowed -= ({ bname });
}

nomask int
my_return(string str)
{
    object *ob;
    int i;
  
    NF("Return what?\n");
    if (!str)
      return 0;
  
    ob = FIND_STR_IN_OBJECT(str, TP);
    NF("Couldn't find any " + str + " around.\n");
    if (!sizeof(ob))
      return 0;
  
    ob = filter(ob, "lib_books", TO);
    NF("You can only return books from this library.\n");
    if (!sizeof(ob))
      return 0;
  
    write("You return " + COMPOSITE_DEAD(ob) + ".\n");
    say(QCTNAME(TP) + " returns " + QCOMPDEAD + ".\n");
  
    for (i = 0; i < sizeof(ob); i++)
    {
	if (ob[i]->id(lib_id + "_new"))
	  write("Too bad you didn't choose to bstore it instead.\n");
      
	currently_borrowed -= ({ ob[i]->query_bookname() });
	ob[i]->remove_object();
    }
  
    return 1;
}

nomask int
appoint(string str)
{
    string who;

    NF("What?\n");
    if (lib_type != 4)
      return 0;

    if (!str)
      return 0;

    if (!hook_appoint_unappoint())
      return 0;

    NF("Appoint who as librarian?\n");
    if (!str)
      return 0;
  
    if (!sscanf(str, "%s as librarian", who))
      return 0;

    NF("There maximum number of librarians has been reached already. You have to " +
       "unappoint a present librarian first.\n");
    if (sizeof(librarian) >= max_lib_num)
      return 0;

    librarian += ({ L(who) });
    write("You have appointed " + C(L(who)) + " as librarian.\n");
    say(QCTNAME(TP) + " changes the sign on the librarian's office.\n");
    hook_appointed_info();
    save_object(MASTER);
    return 1;
}

nomask int
unappoint(string str)
{
    string who;

    NF("What?\n");
    if (lib_type != 4)
      return 0;

    if (!str)
      return 0;

    if (!hook_appoint_unappoint())
      return 0;

    NF("Unappoint who as librarian?\n");
    if (!str)
      return 0;
  
    if (!sscanf(str, "%s as librarian", who))
      return 0;
    
    NF(C(L(who)) + " is not a librarian.\n");
    if (member_array(who,librarian) == -1)
      return 0;

    write("You have unappointed " + C(L(who)) + " as librarian.\n");
    librarian -= ({ L(who) });
    say(QCTNAME(TP) + " changes the sign on the librarian's office.\n");
    save_object(MASTER);
    return 1;
}

nomask int
retire(string str)
{
    NF("What?\n");
    if (lib_type != 2 && lib_type != 4)
      return 0;
    if (member_array(TP->query_real_name(), librarian) == -1)
      return 0;

    NF("Retire as librarian?\n");
    if (!str || str != "as librarian")
	return 0;

    write("You have retired from your position as librarian.\n");
    librarian -= ({ TP->query_real_name() });
    say(QCTNAME(TP) + " changes the sign on the librarian's office.\n");
    save_object(MASTER);
    return 1;
}

/* Move a book from one topic to another, or from the input section
 * to the library itself
 */
nomask int
movebook(string str)
{
    string thebook,newshelf,oldtopic;

    NF("What?\n");
    if (lib_type != 2 && lib_type != 4 && !TP->query_wiz_level())
      return 0;
    if (member_array(TP->query_real_name(), librarian) == -1 && !TP->query_wiz_level())
      return 0;
  
    NF("Movebook <booktitle> to topic <newtopic>.\n");
    if (!str)
      return 0;
    if (sscanf(str, "%s to topic %s",thebook,newshelf) != 2)
      return 0;

    thebook = bookname(thebook);

    NF("No such book title found.\n");
    if (member_array(thebook,BOOKLIST) < 0)
      return 0;
    NF("No such Topic available.\n");
    if (member_array(L(newshelf),map(TOPICLIST,lower_case)) < 0)
      return 0;

    oldtopic = books[thebook][1];
    books[thebook][1] = L(newshelf);
    write("You move the book '" + books[thebook][0] + "' from the Topic '" +
	  oldtopic + "' to the Topic '" + newshelf + "'.\n");
    save_object(MASTER);
    return 1;
}

/* Add a new book
 * all new books will end up in the 'New Arrivals Section'
 */
nomask void
add_book(string descript)
{
    books += ([bookname(descript):({descript,"new arrivals",
				      TP->query_real_name()})]);
    save_object(MASTER);
}

nomask int
add_new_book(string blong,string bshort, string blist, string bfile)
{
    string str = bookname(blist);
    string tme;

    if (file_size(lib_path + "short/" + str) != -1 ||
	file_size(lib_path + "long/" + str) != -1 ||
	file_size(lib_path + "book/" + str) != -1)
      return 0;

    write_file(lib_path + "short/" + str,bshort);
    write_file(lib_path + "long/" + str,blong);
    write_file(lib_path + "book/" + str,bfile/*read_file(bfile)*/);
    add_book(blist);
    
    tme = ctime(time());
    write_file(lib_path + "book_log",tme[4..15] + " " + tme[22..23] + " " +
	       TP->query_name() + ": " + str + "\n");
    return 1;
}


/* Allow for wizards to delete books which are in the trash
 *
nomask int
remove_book(string descript)
{
    string *b;
    string *btitles = sort_array(BOOKLIST,lex_greater);
    string str = "These books were deleted from the trash:\n";
    int i,j = 0;

    if (SECURITY->query_wiz_rank(TP->query_real_name()) < WIZ_MAGE)
      return 0;
    
    /* Remove all books in the trash *
    if (!descript || descript == "")
    {
	write("Give a specific book title or '-all books in trash-' as " +
	      "argument if you want to empty the trash.\n");
	return 1;
    }
    if (descript == "-all books in trash-")
    {
	for(i=0;i<m_sizeof(books);i++)
	  if (L(books[btitles[i]][1]) == "trash")
	  {
	      if (member_array(btitles, to_delete) < 0)
	      {
		  j--;
		  to_delete += ({ btitles[i] });
	      }
	      else
	      {
		  j++;
		  str += btitles[i] + "\n";
		  books = m_delete(books,btitles[i]);
	      }
	  }
	if (j > 0)
	  write(str + "Please remove the long-, short- and book-files for " +
		"each of those books.\n");
	else if (j < 0)
	  write("Please repeat the last command to really delete the book(s).\n");
	else
	  write("Trash was empty, no books removed.\n");
	save_object(MASTER);
	return 1;
    }

    /* Remove a specific book *
    descript = bookname(descript);
    b = books[L(descript)];
    if (!b)
    {
	write("No such book found!\n");
	return 0;
    }
    if (b[1] != "trash")
    {
	write("Book must be in the trash before it can be removed completely.\n");
	return 1;
    }
    if (member_array(descript,to_delete) < 0)
    {
	to_delete += ({ descript });
	write("Really delete this book? - To continue repeat the last " +
	      "command.\n");
	return 1;
    }
    else
    {
	books = m_delete(books,descript);
      	write("Book: " + descript + " was erased! Please remove the " +
	      "corresponding files in the library's directories.\n");
	save_object(MASTER);
	return 1;
    }
}
*/

nomask int
erase_book(string descript)
{
    string *b;
    string *btitles = sort_array(BOOKLIST,lex_greater);
    string str = "These books were deleted from the trash:\n";
    string bname = "";
    string shortname, longname, textname;
    int i,j = 0;

    NF("What?\n");
    if (lib_type != 2 && lib_type != 4 && !TP->query_wiz_level())
      return 0;
    if (member_array(TP->query_real_name(), librarian) == -1 && !TP->query_wiz_level())
      return 0;
  
    /* Remove all books in the trash */
    if (!descript || descript == "")
    {
	write("Give a specific book title or '-all books in trash-' as " +
	      "argument if you want to empty the trash.\n");
	return 1;
    }
    if (descript == "-all books in trash-")
    {
	for(i=0;i<m_sizeof(books);i++)
	  if (L(books[btitles[i]][1]) == "trash")
	  {
	      if (member_array(btitles[i], to_delete) < 0)
	      {
		  j--;
		  to_delete += ({ btitles[i] });
	      }
	      else
	      {
		  j++;
		  str += btitles[i] + "\n";
		  books = m_delete(books,btitles[i]);
		  
		  /* Here we remove the long-, short- and text-file for this book */
		  bname = bookname(btitles[i]);
		  shortname = lib_path + "short/" + bname;
		  longname = lib_path + "long/" + bname;
		  textname = lib_path + "book/" + bname;
		  rm(longname);
		  rm(shortname);
		  rm(textname);
	      }
	  }
	if (j > 0)
	  write(str + "\n");
	else if (j < 0)
	  write("Please repeat the last command to really delete the book(s).\n");
	else
	  write("Trash was empty, no books removed.\n");
	save_object(MASTER);
	return 1;
    }

    /* Remove a specific book */
    descript = bookname(descript);
    b = books[L(descript)];
    if (!b)
    {
	write("No such book found!\n");
	return 0;
    }
    if (b[1] != "trash")
    {
	write("Book must be in the trash before it can be removed completely.\n");
	return 1;
    }
    if (member_array(descript,to_delete) < 0)
    {
	to_delete += ({ descript });
	write("Really delete this book? - To continue repeat the last " +
	      "command.\n");
	return 1;
    }
    else
    {
	books = m_delete(books,descript);
	/* Here we remove the long-, short- and text-file for this book */
	bname = descript;
	shortname = lib_path + "short/" + bname;
	longname = lib_path + "long/" + bname;
	textname = lib_path + "book/" + bname;
	rm(longname);
	rm(shortname);
	rm(textname);

      	write("Book: " + descript + " was erased!\n");
	save_object(MASTER);
	return 1;
    }
}


/* Add a topic to the topics list
 */
nomask int
my_create(string str)
{
    string newtopic;
    int access;
    string *tmp;

    NF("What?\n");
    if (lib_type != 2 && lib_type != 4)
      return 0;
    if (member_array(TP->query_real_name(),librarian) == -1)
      return 0;
  
    NF("Create what topic?\n");
    if (!str)
      return 0;
  
    tmp = explode(str," ");
    NF("Create <new topic> <access level>?\n");
    newtopic = implode(tmp[..sizeof(tmp)-2]," ");
    if (!newtopic || !strlen(newtopic))
      return 0;
    if (sscanf(tmp[sizeof(tmp)-1],"%d",access) != 1)
      return 0;
  
    topics += ([newtopic:access]);
    save_object(MASTER);
    write("Topic " + C(newtopic) + " created.\n");
    return 1;
}


/* Remove a topic from the topics list
 */
nomask int
uncreate(string str)
{
    int i;

    NF("What?\n");
    if (lib_type != 2 && lib_type != 4)
      return 0;

    if (member_array(TP->query_real_name(), librarian) == -1)
      return 0;

    NF("Uncreate what topic?\n");
    if (!str)
      return 0;

    NF("There are still books in this topic. Topic must be empty " +
       "before it can be 'uncreated'.\n");
    for(i=0;i<m_sizeof(books);i++)
      if (books[BOOKLIST[i]][1] == L(str))
	return 0;

    NF("No such topic found. Watch for upper and lower case.\n");
    if (member_array(str, m_indexes(topics)) == -1)
      return 0;
    /*if (!topics[str])
      return 0;*/

    topics = m_delete(topics, str);
    save_object(MASTER);
    write("Topic " + str + " removed.\n");
    return 1;
}


/* Change the catalog entry of a book.
 * eg. if it was misformatted
 */
nomask void
input_new_title(string str)
{
    string newtitle = ((str && strlen(str)) ? str : oldtitle);
    mixed oldentry = books[book_to_change];
    string newbookname = bookname(newtitle);

    if (newbookname != bookname(oldtitle) &&
	file_size(lib_path + "short/" + bookname(newtitle)) != -1)
    {
	write("There is already a book with that title. Beautify failed.\n");
	return;
    }
    oldentry[0] = newtitle;
    books = m_delete(books, book_to_change);
    books += ([newbookname:oldentry]);
    if (book_to_change != newbookname)
    {
	rename(lib_path + "short/"+ book_to_change,
	       lib_path + "short/"+ newbookname);
	rename(lib_path + "long/" + book_to_change,
	       lib_path + "long/" + newbookname);
	rename(lib_path + "book/" + book_to_change,
	       lib_path + "book/" + newbookname);
    }
    write("Catalog entry set to:\n'" + newtitle +"'\n");
    save_object(MASTER);
    
    /* Add the option to modify the short and long of the book as well. */
}

nomask int
beautify(string str)
{
    NF("What?\n");
    if (lib_type != 2 && lib_type != 4 && !TP->query_wiz_level())
      return 0;

    if (member_array(TP->query_real_name(),librarian) == -1 && !TP->query_wiz_level())
      return 0;

    NF("Beautify what book?\n");
    if (!str)
      return 0;
  
    if (!books[bookname(str)])
      return 0;

    book_to_change = bookname(str);
    oldtitle = books[book_to_change][0];
  
    write("Catalog entry is:\n'" + oldtitle + "'\nEnter new catalog entry " +
	  "(Hit Return to leave as is).\n");
    input_to(input_new_title);
    return 1;
}

void
done_editing(string text)
{
    string file = TP->query_prop("_temp_s_editing_book");

    if (!text || text == "")
    {
	write("Aborted.\n");
	return;
    }

    if (!file)
    {
	write("Sorry, something went wrong, the book was NOT stored!\n");
	return;
    }

    write("Ok.\n");
    seteuid(getuid(TO));
    rm(file);
    write_file(file, text);
}

nomask int
edit(string str)
{
    string author;
    string booktext;

    if (lib_type != 2 && lib_type != 4 && !TP->query_wiz_level())
      return 0;
    
    NF("Edit what book?\n");
    if (!str)
      return 0;
  
    if (!books[bookname(str)])
      return 0;

    book_to_change = bookname(str);

    // Navarre July 28th 2007, changed the >= 2 to > 2, since if = 2 [2] doesn't exist.
    //if (sizeof(books[book_to_change]) >= 2)
    //  author = books[book_to_change][2];
    if (sizeof(books[book_to_change]) > 2)
      author = books[book_to_change][2];
    else
      author = TP->query_real_name();

    book_to_change = lib_path + "book/" + book_to_change;
    TP->add_prop("_temp_s_editing_book", book_to_change);

    NF("What?\n");
    if (author != TP->query_real_name() &&
	member_array(TP->query_real_name(),librarian) == -1 &&
	!TP->query_wiz_level())
      return 0;

  
    write("Editing mode.\n");
    booktext = read_file(book_to_change);
    clone_object(BEDIT)->edit("done_editing", booktext,
			      booktext ? sizeof(explode(booktext,"\n")) : 0);
    return 1;
}

nomask string*
query_librarian()
{
    return librarian;
}

nomask int
check_librarian(string who)
{
    return (member_array(L(who), librarian) != -1);
}

nomask string
query_lib_long()
{
    return lib_long;
}

nomask int
query_lib_type()
{
    return lib_type;
}

nomask string
query_lib_path()
{
    return lib_path;
}

nomask float
query_search_delay()
{
    return search_delay;
}

nomask int
query_max_librarian_num()
{
    return max_lib_num;
}
