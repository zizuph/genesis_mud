/*******************************************************************
 * Propaganda Minister's Kiosk
 * Located at the intersection of Market and Caravan in Caravan district Kabal
 *
 * Created by Ashbless   8/3/96
 * Last Modified: 8/16/96
 *
 *    Notes can be posted on the kiosk with the knote command in our Kalad Key.
 * Knote with no arguments puts you in the editor. You can give a filename
 * as an argument to knote, to use the contents of the file as the text of
 * the note. You do not have to be present to post on the kiosk.
 *    This kiosk is a device of the High Lord's Minister of Public Relations,
 * otherwise known as the Minister of Propaganda. It is disguised as a tool
 * for free speech where citizens of Kabal can post their opinions. In reality
 * it is used soley by the Public Relations Commission to spread their propaganda.
 * Whenever there is turmoil in the city, over some issue, the Minister may
 * post a note that attempts to put the High Lord in the best light possible.
 * Of course, many people see right through this sham, and there will be other
 * places where less biased views of the situation can be heard.
 *
 * PLEASE MAKE SURE THAT ANY POSTS YOU MAKE STAY WITHIN THE THEME OF THIS
 * OBJECT!!! WHATEVER YOU WRITE HERE, IS CONSIDERED TO COME FROM THE
 * MINISTER OF PROPAGANDA, POSING AS A CITIZEN OF KABAL, _NOT_ THE WIZARDS
 * OF KALAD!
 *
 * Note: This kiosk is a plot device! It is not a bulletin board
 *       and no it does _not_ follow all the regulations for boards.
 *       No one but Kalad wizzes should be able to put anything
 *       here, because this is only for ficticious postings to
 *       support the roleplay of developments in Kabal.
 ******************************************************************/
inherit "/std/board";
#include "/d/Kalad/defs.h"

#define TEXT "An unimportant looking man, wearing the High Lord's " + \
   "colors, arrives. Frowning, he removes some worn announcements " + \
   "from the " + short() + ", and replaces them with fresh " + \
   "copies, before scurrying off.\n"

/*
 * Prototypes
 */
int post_it(string msg);
string which_desc();
int check_written(string msg);


void load_me() {}


void
create_board()
{
   set_name("kiosk");
   remove_name("board");
   remove_name("bulletinboard");
   set_adj("granite");
   add_adj("cylindrical");
   remove_adj("bulletin");
   set_short("cylindrical granite kiosk");
   set_long(BS(
      "This massive granite kiosk, must have been brought from the " +
      "nearby Hespyre mountains, at great expense. It is planted " +
      "firmly in the center of the intersection, so that none may " +
      "pass without taking notice of it. It is plastered with " +
      "posters, flyers, and paper of all kinds, " +
      "and it's cylindrical shape allows it to be " +
      "viewed from all directions. Ostensibly a forumn for exchange " +
      "of information and expression of public opinion, the kiosk " +
      "appears remarkably well maintained. A small gold plaque reads:" +
      "\n") +
      "            **************\n" +
      "            *            *\n" +
      "            * THE PEOPLE *\n" +
      "            *   SPEAK!   *\n" +
      "            *            *\n" +
      "            **************\n");

   set_board_name(CENTRAL(test/kiosk_data));
   set_num_notes(50);
   set_silent(0);
   set_remove_str(BS(
      "As you reach up to tear down the announcement, you notice a " +
      "rather large detachment of city militia marching in your " +
      "direction. As the officer's glance strays towards you, you " +
      "wisely lower your hand." +
      "\n"));
   set_show_lvl(0);
   set_no_report(1);
   set_keep_discarded(1);
}


void
reset_board()
{
   tell_room(E(TO), BS(TEXT));
}


void
init()
{
   ::init();

   AA(no_post,note);
   AA(no_rename,rename);
}


post_note_hook(string head)
{
   tell_room(E(TO),BS(TEXT)); 
}


int
post_it(string body)
{
   object ob;
   string header, author;

   header = which_desc();
   header = sprintf("%-30s",header) + "   length:";
   author = "     dated:";

   seteuid(geteuid(PO));
   
   create_note(header,author,body);
      
   return 1;
}


int no_rename() { write("What ?\n"); return 1; }


int
no_post()
{
   if (TP->query_skill(SS_AWARENESS) >= 10 + random(30))
      write(BS(
         "As you start to write the note, you notice two men " +
         "staring intently at you, from the shadows. The first " +
         "fellow whispers something to a short dirty man at his side, " +
         "who runs off posthaste. " +
         "He then begins writing furiously on a pad he produced from " +
         "his pocket, glancing up at you periodically. " +
         "\n\n"));

   "/std/edit"->edit("check_written");
   return 1;
}


int
check_written(string msg)
{
   string timedesc;

   if (DAY)
      timedesc = "crowd";
   else
      timedesc = "shadows";

   if (!strlen(msg))
      write(BS("\n" +
      "It seems you wisely changed your mind about posting the note, " +
      "for as soon as you step back into the " + timedesc +
      ", a short dirty " +
      "man arrives. He is at the head of a detachment of soldiers, " +
      "that are dressed smartly in black with green armbands, and he " +
      "is pointing towards the kiosk. Luckily, they don't notice you. " +
      "\n"));

   else
      write(BS("\n" +
         "As you are about to post your note, a short dirty man " +
         "arrives at the head of a detachment of soldiers, pointing " +
         "urgently in your direction. The soldiers are dressed " +
         "completely in black, with the sole exception of bright green " +
         "armbands, worn proudly on their right arm. With a " +
         "purposeful air, they head slowly towards you. " +
         "\n"));
}


string
which_desc()
{
   string *adj1 = ({
      "bright", "shiny", "thin", "worn", "damp", "nondescript",
      "wrinkled", "smudged", "dusty", "wind-blown", "fancy",
      "eye-catching", "small", "brilliant", "matted"
      });

   string *adj2 = ({
       "yellow", "red", "grey", "white", "beige", "blue",
       "purple", "green", "lavender", "magenta", "orange",
       "scarlet", "papyrus", "newsprint", "cardboard",
       "paper", "tassled", "framed", "decorative"
      });

   string *noun = ({
      "scroll", "poster", "announcement", "posting", "pamphlet",
      "flyer", "note", "message", "handbill", "bulletin",
      "notice"
      });

   return "A " + adj1[random(sizeof(adj1))] +
   " " + adj2[random(sizeof(adj2))] +
   " " + noun[random(sizeof(noun))] + ".";
}
