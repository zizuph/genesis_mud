/* created by Aridor, 06/06/94 */
/* edited by Arman to include SoHM spells May 2016 */
/* Added SoHM revelation - Arman 2017 */

inherit "/std/room";

#include "local.h"
#include <macros.h>
#include <ss_types.h>
#include "/d/Krynn/guilds/sohm/defs.h"
#include "/d/Krynn/common/defs.h"

object brother;
mixed *titles = ({ });
object *has_book = ({ });
static int *books_out = ({ });
object someone_has_audition = 0;

#define OOTS_MANAGER           ("/d/Krynn/guilds/OotS/lib/oots_manager")
#define IS_OOTS(x)             ((x)->query_guild_name_lay() == "Holy Order of the Stars")
#define OOTS_ADD_REV(p,r1,r2)  OOTS_MANAGER->add_oots_revelations(p, r1, r2)
#define OOTS_QUERY_REV(p, r)   (member_array(r, m_indexes(OOTS_MANAGER->query_oots_revelations(p))) > -1)

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
    set_short("Public room in a great library");
    set_long("You are in the public entry of the Great Library "
	+ "of Palanthas, a vast hall with a high vaulted ceiling "
	+ "and rows of desks and study cubicles peopled by scholars, "
	+ "young students, aesthetics, and servants collecting books "
	+ "for their lords. Several doorways lead off from the hall "
	+ "including a previously closed door to the southeast recently "
	+ "opened. A wide, translucent marble counter stands at the "
	+ "end of the hall behind which several aesthetics in their "
	+ "maroon robes provide service. There is a sign hanging "
	+ "above the counter and to the south is a long hall leading "
	+ "to a private study.\n");
	    
    add_prop(ROOM_I_LIGHT, 10);
    INSIDE;
    add_prop(ROOM_M_NO_ATTACK, 1);
    add_prop(ROOM_M_NO_MAGIC_ATTACK, 1);
    add_prop(OBJ_S_WIZINFO,"Wizards can add books here with 'Call here " +
	     "add_a_book title%%volumenumber'. The respective book with " +
	     "this number must be stored in .../library/books/v<number>\n" +
	     "You can remove books again with 'Call here remove_a_book " +
	     "volumenumber'.\n");

    add_exit(LIBRARY_LANE, "northwest", "@@without_book_only");
    add_exit(LIBRARY + "magazine","east","@@wizzes_only");
    add_exit(LIBRARY + "magazine","northeast","@@wizzes_only");
    add_exit(LIBRARY + "magazine","north","@@wizzes_only");
    add_exit(LIBRARY + "private","south","@@no_book_only_prop");
    add_exit(RACEGUILD, "southeast");

    add_item(({"sign"}),"The white wooden sign is written in plain, black "
	+ "lettering. It hangs from a pair of small chains in the ceiling. "
	+ "You can read it.\n");
    add_item(({"index"}),"This is a long scroll with all the book titles " +
	     "and their respective index reference number on it.\n");
    add_item(({"counter"}),"It is a large counter upon which books are " +
	     "neatly stacked.\n");
    add_item(({"books"}),"These are books waiting to be sorted back into " +
	     "the magazine.\n");
    add_item(({"curious runes","runes","runes of magic"}),
             "@@exa_volume_runes");

    add_cmd_item(({"sign"}),({"read"}),"@@read_the_sign");
    add_cmd_item(({"index"}),({"read"}),"@@read_the_index");

    seteuid(getuid(TO));

    set_alarm(1.0,0.0,"reset_room");
    load_index();
}

string
exa_volume_runes()
{
    if (present(PALANTHAS_BOOK,TP)->query_prop("_obj_s_volume_number") == "459")
    {
        if((this_player()->query_guild_name_occ() != "School of High Magic") &&
           (this_player()->query_guild_name_occ() != "Wizards of High Sorcery")) 
        {
          write("Towards the back of the dull tome you notice curious runes " +
            "of magic. You can't make out anything further from them.\n");
          return "";
        }

        write("Towards the back of the dull tome you notice curious runes " +
            "of magic, likely of the defensive teleportation spell previously " +
            "described. If properly prepared you could scribe them.\n");
        return "";

      }

    return "You don't find any runes to examine.\n";

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
    ADD("borrow_book","lborrow");
    ADD("return_book","return");
    ADD("scribe_spell","scribe");
}


int
read_the_sign()
{
    write("On the sign you read:\n\n" +
	  "You can only borrow books that are listed in the public index.\n" +
          "You can <read index> to review the index list.\n" +
	  "Give the number to simplify the search procedure.\n" +
	  "Books may under no circumstances leave the building.\n" +
          "In small print you notice that kender may only <lborrow> books here!\n");
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
    NF("There is no one here to fulfill your request.\n");
    if (!brother || E(brother) != TO)
      return 0;
    NF("The librarian cannot see you!\n");
    if (!brother->can_see_in_room() || !CAN_SEE(brother, TP))
        return 0;
    NF("You cannot see the librarian!\n");
    if (!TP->can_see_in_room() || !CAN_SEE(TP, brother))
        return 0;
    NF("Borrow what volume?\n");
    if (!str)
      return 0;
    NF("You already borrowed a volume! You cannot borrow more than one book at a time.\n");
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

int
scribe_spell(string str)
{
    if (!present(PALANTHAS_BOOK,TP))
    {
        NF("What?\n");
        return 0;
    }

    if (present(PALANTHAS_BOOK,TP)->query_prop("_obj_s_volume_number") != "459")
    {
        NF("What?\n");
        return 0;
    }

    if((this_player()->query_guild_name_occ() != "School of High Magic") &&
       (this_player()->query_guild_name_occ() != "Wizards of High Sorcery")) 
    {
        NF("What?\n");
        return 0;
    } 

    if (!str)
    {
      NF("Scribe what?\n");
      return 0; 
    }

    if (str != "the curious runes")
    {
      NF("Scribe what? <the curious runes>?\n");
      return 0; 
    }    

    if(this_player()->query_skill(SS_SPELLCRAFT) < 40)
    {
	NF("Your spellcraft skills are too poor to " +
          "comprehend the curious runes in the tome.\n");
	return 0;
    }

    if(!this_player()->query_prop("_sohm_read_magic_active")) 
    {
        NF("You are not mentally focused enough to decypher the " +
        "magical runes carved into the floor here. Perhaps try again after " +
        "preparing yourself to read magic?\n");
        return 0;
    }

    if(this_player()->query_minor_spells_max() < 1)
    {
        NF("This spell is too advanced for you to learn at this " +
        "time.\n");
        return 0;
    } 

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"ripeidronik"))
    {
        NF("The curious runes seems to detail the blink spell, " +
            "which you have already scribed in your " +
            "spellbook.\n");
        return 0;
    }

    write("Ah! The tome details an unknown spell to you! " +
        "The defensive teleportation spell blink!\nYou carefully study the " +
        "tome and scribe the spell in to your spellbook!\n");
    say(QCTNAME(this_player()) + " carefully reviews one of the library's volumes " +
       "and begins copying a spell in to " +
        this_player()->query_possessive() + " leather-bound " +
       "spellbook.\n");
    
    SOHM_MANAGER->scribe_spell_to_spellbook(this_player(),"ripeidronik");
    return 1;

}

int
canticle_revelation(object ob)
{
     ob->catch_msg("\n\nThe rows of books trigger a divine revelation of a time " +
           "in the distant past when another sought the wisdom of the Gods...\n\n\n");
     OOTS_ADD_REV(ob,"canticle56","edification - canticle of the dragon, verse 5 and 6"); 

}


void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (living(ob))
    {
       if(IS_OOTS(ob))
       {
          if(!OOTS_QUERY_REV(ob, "canticle56"))
          {
            set_alarm(2.5, 0.0, &canticle_revelation(ob)); 
          }
       }
    }

}
