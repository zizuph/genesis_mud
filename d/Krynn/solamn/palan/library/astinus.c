/* created by Aridor, 06/06/94 */

#include "local.h"

inherit M_FILE

#include <macros.h>
#include <ss_types.h>

object *has_book = ({ });
string *books_out = ({ });
object *given_list = ({ });

void
create_krynn_monster()
{
    set_name("astinus");
    set_living_name("astinus");
    set_long("Astinus the Ageless One.\nHe is the head of the " +
	     "Library of Palanthas.\nHe is the chronicler of all history in Krynn.\n");
    set_race_name("human");
    default_config_npc(100);
    ALWAYSKNOWN;
    set_skill(SS_AWARENESS,100);
    set_default_answer(VBFC_ME("default_ans"));
    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    seteuid(getuid(TO));
}

void
init_living()
{
    ::init_living();
    ADD("return_book","return");
}

string
default_ans()
{
    command("say Shhhh! Don't disturb the quiet here.");
    return "";
}

void
do_the_giving(object who, string what)
{
    object scr;
    int prp;
    seteuid(getuid(TO));
    scr = clone_object("/std/scroll");
    scr->set_name("volume");
    scr->add_name("book");
    scr->add_name(PALANTHAS_BOOK);
    scr->set_long("You hold in your hands a volume from the fabled Library " +
		  "of Palanthas. It does not have a volume number imprinted " +
		  "on it which you find rather peculiar, but the author is " +
		  "marked as Astinus of Palanthas. This book must be of " +
		  "the private collection of Astinus.\n");
    scr->set_file(PERSONAL + what);
    scr->add_prop(OBJ_S_VOLUME_NUMBER, what);
    scr->add_prop(OBJ_M_NO_STEAL, 1);
    scr->move(TO);
    if (command("give volume to " + who->query_real_name()))
      {
	  who->remove_prop(PLAYER_M_PAL_LIB_AUDITION);
	  scr->add_prop(OBJ_M_NO_INS, 1);
	  command("say There you are...");
	  has_book += ({ who });
	  books_out += ({ what });
	  given_list += ({ who });

	  if (what != "draconians")
	  {
	      prp = who->query_prop("_player_i_visited_library");
	      who->add_prop("_player_i_visited_library", prp | 2);
	  }
	  
	  if (what == "draconians" && !who->test_bit("Krynn",2,6))
	  { /* Reward the quest here */
	      who->set_bit(2,6);
	      who->add_exp(500);
	      STD_QUEST_LOG("Identify Draconians",who,500);
	  }
      }
    else
      {
	  command("shrug");
	  command("say Guess not.");
	  scr->remove_object();
      }
}


void
give_out_book(object who)
{
    mixed prp;
    string bok;
    if (!who)
      return;
    if (member_array(who, given_list) != -1)
      {
	  who->remove_prop(PLAYER_M_PAL_LIB_AUDITION);
	  command("say I already helped you! Don't disturb me any more!");
	  who->command("north");
	  return;
      }
    prp = who->query_prop(PLAYER_M_PAL_LIB_AUDITION);
    if (!prp)
      {
	  command("say You are not allowed into this room! Please leave.");
	  who->command("north");
	  return;
      }
    if (pointerp(prp))
      bok = prp[sizeof(prp)-1];
    else
      bok = prp;
    command("say Ah yes, I have been informed of your coming. I have " +
	    "with me some special information which you might want to " +
	    "look at.");
    do_the_giving(who, bok);
    return;
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

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (from && ob->id(PALANTHAS_BOOK))
      set_alarm(1.5,0.0,"remove_the_book",from, ob);
    if (from)
      set_alarm(2.5,0.0,"command","drop all");
}

