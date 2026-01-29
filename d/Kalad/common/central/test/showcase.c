/*******************************************************************
 * High Lord's Announcement Showcase
 * Located at the top of the lift in Central district Kabal
 *
 * Created by Ashbless   8/16/96
 * Last Modified: 8/16/96
 *
 *    Decrees can be posted on the showcase with the decree command in our
 * Kalad Key. "decree" with no arguments puts you in the editor. You can
 * give a filename as an argument to knote, to use the contents of the file
 * as the text of the note. You do not have to be present to post on the kiosk.
 *    This showcase is where the High Lord (or his officials) and the City
 * Council will post official annoucements, Royal decrees, edicts, or bulls.
 * Anything written here is considered to be law in the city of Kabal.
 *
 * PLEASE MAKE SURE THAT ANY POSTS YOU MAKE STAY WITHIN THE THEME OF THIS
 * OBJECT!!! WHATEVER YOU WRITE HERE, IS CONSIDERED TO COME FROM THE
 * HIGHLORD, HIS OFFICIALS, OR THE CITY COUNCIL, _NOT_ THE WIZARDS OF
 * KALAD!
 *
 * Note: This showcase is a plot device! It is not a bulletin board
 *       and no it does _not_ follow all the regulations for boards.
 *       No one but Kalad wizzes should be able to put anything
 *       here, because this is only for ficticious postings to
 *       support the roleplay of developments in Kabal.
 ******************************************************************/
inherit "/std/board";
#include "/d/Kalad/defs.h"


#define NO_ACCESS  "That is quite impossible, as the documents are safely " + \
      "behind a thick glass plate.\n"


/*
 * Prototypes
 */
int post_it(string body, int type);
string type_desc(int type);
string get_author(int type);
string signature(int type);


void load_me() {}


void
create_board()
{
   set_name("case");
   add_name("showcase");
   remove_name("board");
   remove_name("bulletinboard");
   set_adj("glass");
   add_adj("shiny");
   remove_adj("bulletin");
   set_short("shiny glass showcase");
   
   set_long(BS(
      "A large block of white granite, with blue veins running through it, " +
      "dominates the center of the intersection. A thick plate of glass " +
      "has been mounted on the front of the block and official looking " +
      "documents are visible behind it. This is where the High Lord " +
      "and the City Council post official proclamations, edicts, decrees, " +
      "and bulls. The glass is remarkably shiny. " +      
      "A large platinum plaque set in the stone reads: " +
      "\n") +
      "            ******************\n" +
      "            *                *\n" +
      "            *    OFFICIAL    *\n" +
      "            * ANNOUNCEMENTS! *\n" +
      "            *                *\n" +
      "            ******************\n");

/* For some reason examining these items returns the long desc of this object
   instead of the desc of the item. A bug in /std/board?
   
   add_item( ({"glass","thick glass","plate","glass plate"}),
      "It is remarkably shiny. Some official looking documents are visible\n" +
      "behind it.\n");
   add_item( ({"block","granite","white granite","granite block"}),BS(
      "This huge block of granite must have come from the nearby " +
      "Hespyre mountains, at great expense to someone. Veins of " +
      "blue run through the white rock. There is a thick glass " +
      "plate mounted on it.\n"));
*/

   add_cmd_item( ({"plaque","large plaque","platinum plaque","large platinum plaque"}),
      ({"get","take","steal"}),
      ({"It is securely behind the glass!\n",
      "It is securely behind the glass!\n",
      "It is securely behind the glass!\n"}) );
   add_cmd_item( ({"glass","case","showcase","glass case","glass showcase"}),
      ({"break", "open", "unlock"}),
      ({"It is remarkably resistant to your efforts. Strange...\n",
       "It is locked!\n", "You don't have the right key!\n"}) );
   add_cmd_item("lock","pick","You don't have much luck.\n");

   set_board_name(CENTRAL(test/case_data));
   set_num_notes(50);
   set_silent(0);
   set_remove_str(BS(NO_ACCESS));
   set_show_lvl(0);
   set_no_report(1);
   set_keep_discarded(1);
}


void
reset_board()
{
   tell_room(E(TO), BS(
   "A small man wearing the High Lord's colors, arrives. He quickly wipes " +
   "the face of the glass showcase with a dirty cloth, before scurrying off. " +
   "\n"));
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
   tell_room(E(TO),BS(
   "A small entourage arrives, led by a self-important " + 
   "looking fellow, draped in gaudy robes. The man strides arrogantly " + 
   "up to the glass showcase, opening the front panel with a small " + 
   "key that is handed to him by a man at his side. He dramatically inserts " +
   "something into the case, then closes and locks it. He nods to " +
   "another man behind him, who blows a few notes on a trumpet, then " +
   "the entire group departs the way they came. " +
   "\n")); 
}


int
post_it(string body, int type)
{
   object ob;
   string header, author;

   header = type_desc(type);
   author = get_author(type);
   body = "Citizens of Kabal, Travellers, let it be known:\n\n" +
          body + "\n" + signature(type);

   seteuid(geteuid(PO));
   
   create_note(header,author,body);
      
   return 1;
}


int no_rename() { write(BS(NO_ACCESS)); return 1; }


int
no_post()
{
   write(BS(NO_ACCESS));
   return 1;
}


string
type_desc(int type)
{
   string *post_types = ({
      "Royal Proclamation",             /* Urian                 */
      "Royal Decree",                   /* Shamein               */
      "Council Edict",                  /* Mortimeth             */
      "Church Bull",                    /* High Priest of Solara */
      "Military Declaration",           /* Gurnik                */
      "Principal Statute",              /* Roeven                */      
      "Royal Canon",                    /* Hamer                 */
      "City Ordinance",                 /* Council               */
      "Public Safety Mandate",          /* Arth                  */
      "Official Announcement",          /* Council               */
      "Official Notice",                /* Arth                  */
      "Public Announcement"             /* Wessle                */
      });

   return post_types[type];
}


string
get_author(int who)
{
   string *authors = ({
      "Urian",     /* Urian Ra'Solev, High seat of House Uthraal and
                      High Lord of Kabal                                     */
      "Shamein",   /* Shamein the Personal Advisor of the High Lord and
                      High Minister of Kabal                                 */      
      "Mortimeth", /* Speaker of the City Council of Kabal                   */        
      "Rosumaen",  /* Rosumaen Ta'Chedrith, High Priest of Solara            */
      "Gurnik",    /* Gurnik the Knight Marshall of the High Lord's Armies   */
      "Roeven",    /* Roeven the Ring Prince								 */
      "Hamer",     /* Hamer, Priest of Solara and High Cleric of the Citadel */
      "Council",   /* City Council                                           */
      "Arth",      /* Knight Captain of the Kabal Militia                    */
      "Council",
      "Arth",
      "Wessle   "  /* Wessle the Minister of Public Relations                */
      });
      
   return authors[who];
}


string
signature(int type)
{
   string *sigs = ({
      "   ,Urian Ra'Solev                         \\             \n" +
      "<===========================================)[[[[[[[[[|||)\n" +
      "    High Seat of House Uthraal             /              \n" +
      "    Knight Marshall of the Armies of Kabal         _      \n" +
      "    Bearer of the Ring of the Midnight Sun       ( O )    \n" +
      "    High Lord of Kabal                             -      \n",
      
      "   ,Shamein Eo'Thar                                     \n\n" +
      "    High Seat of House Odruuk                             \n" +
      "    Personal Advisor to the High Lord of Kabal            \n" +
      "    Hereditary Bearer of the Seal                         \n" +
      "    High Minister of Kabal                                \n",
      
      "   ,Mortimeth Al'Yusfrid                                \n\n" +
      "    High Seat of House Aeridol                            \n" +
      "    Elder Speaker of the High Council of Kabal            \n",
      
      "   ,Rosumaen Ta'Chedrith                                  \n" +
      "                                      |                   \n" +
      "    of House Gerindel               \\ | /                \n" +
      "    Patriarch of Kabal           ---( * )---              \n" +
      "    Defender of the Eternal Orb     / | \\                \n" +
      "    Arch Prelate of Solara            |                   \n",
      
      "                                                  (-----) \n" +
      "   ,Gurnik Kal'Denos                               {   }  \n" +
      "                                    (|||]]]]]]]]]]])   >  \n" +
      "    High Seat of House Endaen                      {   }  \n" + 
      "    Knight General of the Armies of Kabal         (_____) \n",
      
      "   ,Roeven Te'Solev                        \\             \n" +
      "<===========================================([[[[[[[[[|||)\n" +
      "    First Heir of House Uthraal            /       _      \n" +
      "    Knight Commander of the Armies of the East   ( O )    \n" +
      "    Ring Prince of Kabal                           -      \n",
      
      "   ,Hamer Us'Andab                  *  ^  *               \n" +
      "                                     *****                \n" +
      "    of House Relaar                <***o***)[[[[[[[[[|||) \n" +
      "    High Cleric of the Citadel       *****                \n" +
      "    Prelate of Solara               *  v  *               \n",
      
      "   ,High Council of Kabal\n",
      
      "                                                  ^          \n" +
      "   ,Arth Ap'Ffyndol                              { }         \n" +
      "(|||]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]])===   ======>  \n" +
      "    of House Loriden                            /   \\       \n" +
      "    Knight Captain of the Kabal Militia        /_____\\      \n",
      
      "   ,High Council of Kabal\n",
      
      "                                                  ^          \n" +
      "   ,Arth Ap'Ffyndol                              { }         \n" +
      "(|||]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]])===   ======>  \n" +
      "    of House Loriden                            /   \\       \n" +
      "    Knight Captain of the Kabal Militia        /_____\\      \n",
      
      "   ,Wessle Memnaur                                      \n\n" +
      "    Underassistant Minister of Public Relations           \n"
      });
      
   return sigs[type];   
}