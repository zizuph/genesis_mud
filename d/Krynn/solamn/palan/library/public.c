/* created by Aridor, 06/06/94 */

inherit "/std/room";

#include "local.h"
#include <macros.h>

object brother;
mixed *titles = ({ });
object *has_book = ({ });
static int *books_out = ({ });
object someone_has_audition = 0;

void
load_index()
{
    restore_object(INDEX_FILE);
}

void
write_index()
{
    save_object(INDEX_FILE);
}


void
reset_room()
{
    if (brother)
      return;
    brother = clone_object(LIBRARY + "brother");
    brother->move_living("xxx",TO);
}


void
create_room()
{
    set_short("Public room in the library");
    set_long("You are in a grand hall. There are many exits leading off " +
	     "into the other parts of the library, those parts where " +
	     "books are stored, living quarters of the Aesthetics and " +
	     "studies. A counter with a brother of the order of the " +
	     "Aesthetics behind it is standing in the middle of the hall, " +
	     "and a sign is placed on it. There is an index of books " +
	     "here, which lists only those books that can be accessed " +
	     "by the public. You are quite certain that an incredible " +
	     "number of books are stored in this building, here in the " +
	     "Great Library of Palanthas. A previously closed door to the " +
        "southeast seems to be open now! To the south, a lone exit " +
	     "from the hall leads off into some private study.\n");
    
    add_prop(ROOM_I_LIGHT, 10);
    INSIDE;
    add_prop(ROOM_M_NO_ATTACK, 1);
    add_prop(ROOM_M_NO_MAGIC_ATTACK, 1);
    add_prop(OBJ_S_WIZINFO,"Wizards can add books here with 'Call here " +
	     "add_a_book title%%volumenumber'. The respective book with " +
	     "this number must be stored in .../library/books/v<number>\n" +
	     "You can remove books again with 'Call here remove_a_book " +
	     "volumenumber'.\n");

    add_exit(LIBRARY_LANE,"west","@@without_book_only");
    add_exit(LIBRARY + "magazine","east","@@wizzes_only");
    add_exit(LIBRARY + "magazine","northeast","@@wizzes_only");
    add_exit(LIBRARY + "magazine","north","@@wizzes_only");
    add_exit(LIBRARY + "private","south","@@no_book_only_prop");
    add_exit(RACEGUILD,"southeast");

    add_item(({"sign"}),"It has words written on it.\n");
    add_item(({"index"}),"This is a long scroll with all the book titles " +
	     "and their respective index reference number on it.\n");
    add_item(({"counter"}),"It is a large counter and some books are " +
	     "neatly stacked onto it.\n");
    add_item(({"books"}),"These are books waiting to be sorted back into " +
	     "the magazine.\n");

    add_cmd_item(({"sign"}),({"read"}),"@@read_the_sign");
    add_cmd_item(({"index"}),({"read"}),"@@read_the_index");

    seteuid(getuid(TO));

    set_alarm(1.0,0.0,"reset_room");
    load_index();
}

int
without_book_only()
{
    if (present(PALANTHAS_BOOK,TP))
      {
	  write("Don't forget to return the book first.\n");
	  return 1;
      }
    return 0;
}

int
wizzes_only()
{
    if (TP->query_wiz_level())
      return 0;
    write("You are not allowed in there!\n");
    return 1;
}

object
query_on_audition()
{
    return someone_has_audition;
}

void
back_from_audition(object who)
{
    if (who == someone_has_audition)
      someone_has_audition = 0;
}

int
no_book_only_prop()
{
    mixed prp;
    int i;
    if (without_book_only())
      return 1;
    if (someone_has_audition)
      {
	  write("I'm sorry, but there is already someone at an audition.\n");
	  return 1;
      }
    if (prp = TP->query_prop(PLAYER_M_PAL_LIB_AUDITION))
      {
	  if (pointerp(prp))
	    for(i = 0; i < (sizeof(prp) - 1); i++)
	      brother->command(prp[i]);
	  else
	    brother->command("say I see you are on an important quest, please enter.");
	  someone_has_audition = TP;
	  (LIBRARY + "private")->is_coming_on_audition(TP);
	  return 0;
      }
    write("You are not allowed in there!\n");
    return 1;
}

void
init()
{
    ::init();
    ADD("borrow_book","borrow");
    ADD("return_book","return");
}


int
read_the_sign()
{
    write("On the sign you read:\n\n" +
	  "You can only borrow books that are listed in the public index.\n" +
	  "Give the number to simplify the search procedure.\n" +
	  "Books may under no circumstances leave the building.\n");
    return 1;
}

int
read_the_index()
{
    int i,maxl1 = 4, maxl2 = 6;
    string str = "", idx;
    NF("The index is empty.\n");
    if (!sizeof(titles))
      return 0;
    for(i=0;i<sizeof(titles);i++)
      {
	  if (strlen(titles[i][0]) > maxl1)
	    maxl1 = strlen(titles[i][0]);
	  if (strlen("" + titles[i][1]) > maxl2)
	    maxl2 = strlen("" + titles[i][1]);
      }
    for(i=0;i<sizeof(titles);i++)
      str += sprintf("%-*s   %*s", maxl1, titles[i][0], maxl2, "" + titles[i][1]) + "\n";
    say(QCTNAME(TP) + " reads the index.\n");
    idx = "The following titles are listed in the index:\n" +
      sprintf("%-*s   %-*s", maxl1, "NAME", maxl2, "VOLUME") + "\n" + str;
    clone_object(MORE_OBJ)->more(idx);
    return 1;
}

int
volume_greater(mixed *a, mixed *b)
{
    if (a[1] == b[1])
      return 0;
    if (a[1] > b[1])
      return 1;
    return -1;
}

int
add_a_book(string my_ttl, int num)
{
    NF("This book does not exist!\n");
    if (!read_file(BOOK_PATH + num))
      return 0;
    titles += ({ ({ my_ttl, num }) });
    titles = sort_array(titles,"volume_greater");
    write_index();
    write("Ok.\n");
    return 1;
}

int
remove_a_book(int num)
{
    int i;
    for(i=0;i<sizeof(titles);i++)
      if (titles[i][1] == num)
	{
	    titles -= ({ titles[i] });
	    write("Ok.\n");
	    write_index();
	    return 1;
	}
    NF("No such volume found!\n");
    return 0;
}

int
borrow_book(string str)
{
    NF("There is no one here to fulfill your wish.\n");
    if (!brother || E(brother) != TO)
      return 0;
    NF("Borrow what volume?\n");
    if (!str)
      return 0;
    NF("You already borrowed a volume! You cannot borrow more than one book at any time.\n");
    if (member_array(TP,has_book) != -1)
      return 0;
    NF("This volume cannot be borrowed!\n");
    if (!read_file(BOOK_PATH + str))
      return 0;
    say(QCTNAME(TP) + " asks " + QTNAME(brother) + " about some book.\n");
    TP->catch_msg("You ask " + QTNAME(brother) + " for a specific book.\n");
    brother->move_living("into the " + ({"north","northeast","east"})[atoi(str) % 3] +
			 " magazine",LIBRARY + "magazine");
    set_alarm(itof(random(20) + 15),0.0,"found_the_book", TP, str);
    return 1;
}

void
found_the_book(object who, string what)
{
    object scr;
    int prp;
    brother->move_living("xxx",TO);
    if (member_array(what,books_out) != -1)
      {
	  brother->command("say Sorry, this book currently isn't in its place.");
	  brother->command("say Most likely someone has borrowed it.");
	  return;
      }
    scr = clone_object("/std/scroll");
    scr->set_name("volume");
    scr->add_name("book");
    scr->add_name(PALANTHAS_BOOK);
    scr->set_long("You hold in your hands a volume from the fabled Library " +
		  "of Palanthas. It has the volume number " + what +
		  " imprinted on it and the author is marked as " +
		  "Astinus of Palanthas.\n");
    scr->set_file(BOOK_PATH + what);
    scr->add_prop(OBJ_S_VOLUME_NUMBER, what);
    scr->add_prop(OBJ_M_NO_STEAL, 1);
    scr->move(brother,1);
    if (brother->command("give volume to " + who->query_real_name()))
      {
	  scr->add_prop(OBJ_M_NO_DROP, 1);
	  scr->add_prop(OBJ_M_NO_INS, 1);
	  scr->add_prop(OBJ_M_NO_GIVE, 1);
	  brother->command("say There you are...");
	  has_book += ({ who });
	  books_out += ({ what });
	  prp = who->query_prop("_player_i_visited_library");
	  who->add_prop("_player_i_visited_library", prp | 1);
      }
    else
      {
	  brother->command("shrug");
	  brother->command("say Guess not.");
	  brother->command("emote leaves into the magazine to return the book.");
	  scr->remove_object();
	  brother->command("emote arrives.");
      }
}

void
remove_the_book(object who, object book)
{
    string what = book->query_prop(OBJ_S_VOLUME_NUMBER);
    book->remove_object();
    has_book -= ({ who });
    has_book -= ({ 0 });
    books_out -= ({ what });
}

int
return_book(string str)
{
    object ob;
    string what;
    NF("Return what?\n");
    if (!str)
      return 0;
    NF("You can't return that!\n");
    if (str != "volume" && str != "book")
      return 0;
    ob = present(PALANTHAS_BOOK,TP);
    if (ob)
      {
	  remove_the_book(TP, ob);
	  write("You return the volume.\n");
	  say(QCTNAME(TP) + " returns a book.\n");
	  return 1;
      }
    NF("You don't have a volume you could return.\n");
    return 0;
}
