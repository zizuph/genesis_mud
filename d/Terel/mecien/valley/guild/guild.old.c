/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
/*   Mecien
 *   The Ancient Mystic Order
 *   Adapted from
 *   adv_guild.c    Styles   Wed Jan 22 1992
 *
 */

inherit "/std/room";

inherit "/lib/guild_support"; 
inherit "/lib/skill_raise";

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include <money.h>
#include <composite.h>
#include <cmdparse.h>

#include "/d/Terel/common/terel_defs.h"
#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

#define NF(str)      notify_fail(str)
#define TO           this_object()
#define TP           this_player()
#define NUM          sizeof(query_money_types(-1))
#define BS(xxx)      break_string(xxx, 72)
#define CLOSED 0     /* 1 = closed,   0 = open.  */

#define MOQ_DIR      GUILD_DIR + "quest/"
#define BAD_SYNTAX   0

int closed;
object meditate;
string *str_numbers;

/*
 * Prototypes
 */
void set_up_skills();
void tell_all_about_new_member(object new);
void tell_all_about_old_member(object old);

void
create_room()
{ 
   
   add_prop(OBJ_S_WIZINFO, "@@wizinfo");
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_HIDE, -1);
   
   set_short(GUILD);
   
   set_long(break_string(
         "The ancient hall of mystic wisdom. "
         +"This hall rises up to form a great dome, fashioned of a dark "
         +"grey stone. The dome contains circular windows that form a "
         +"ring, each of which focuses down upon a statue that stands high "  
         +"up into the dome. Majestic icons of the latter days, these monoliths "
         +"stand to represent the ancient beings, twelve in all. Each of "
         +"the statues stand at a point of a cryptic pattern that is contained "
         +"in the mosaic tiles that cover the floor. "
         +"In the center of the grand hall is a stone table, upon which is "
         +"a large tome. The table reflects light from the windows far above "
         +"it, causing it to illuminate the hall with a luminous prism of "
         +"colors. The air is filled with clouds of incense."
         +"\n", 72));
   
   add_exit(GUILD_DIR+"hall",    "east",  0);
   add_exit(GUILD_DIR+"sanctum", "north", 0);
   add_exit(GUILD_DIR+"library", "west",  0);
   add_exit(GUILD_DIR+"chamber", "south", 0);
   
   add_item("dome", "An immense dome of dark stone.\n");
   add_item("alcove", "A peace and mysterious power resides there.\n");
   add_item("tome", "It is an ancient tome.\n");
   add_item("table", "A large circular stone table.\n");
   add_item(({"window", "windows"}), 
      "They are open to the outside and ring the lower part of the dome.\n");
   add_item(({"statues", "icons", "monoliths"}),
     "There are twelve statues.\n"
     +"These incredible statues stand like colossal icons of some great\n"
     +"peoples. They are in fact monoliths of the Ancients, those great\n"
     +"and wise powers who govern and protect the world from the malice\n"
     +"of the dark ones. The statues stand high up into the dome and circle\n"
     +"the hall, as if guardians of some awesome secrets. They are the\n"
     +"watchers of this hall and serve the mystery that resides within.\n");
   add_item(({"first statue", "first", "1", "statue 1"}),
      "This statue is of a lordly and magnificent\n"
     +"looking man. He is strong of body, standing proud, his face\n"
     +"radiant like the sun. Wearing a golden mantle, a circlet\n"
     +"of gold and a belt of fiery crystals. He holds a long\n"
     +"golden sceptre in his left hand.\n");
   add_item(({"second statue", "second", "2", "statue 2"}),
      "Like an icon of beauty itself, this statue\n"
     +"embodies grace and radiance. An elegant lady, wearing a\n"
     +"a gown of aquamarine and covered with a brilliant cope\n"
     +"of blue. The cope sparkles and glimmers as if it were\n"
     +"emblazoned with stars. Her hands outstretched as if in\n"
     +"prayer, upon her head a silver tiara set with a stone\n"
     +"thats glows white like the moon itself.\n");
   add_item(({"third statue", "third", "3", "statue 3"}),
      "This great statue takes the shape of an\n"
     +"aged and learned man. He wears a robe of deep purple,\n"
     +"over which is a tabard of black, upon which the\n"
     +"astrological symbols have been embroidered. His hands\n"
     +"are upraised to the sky, at his side hangs a silver ring\n"
     +"of keys.\n");
   add_item(({"fourth statue", "fourth", "4", "statue 4"}),
      "Appearing as if only a fading image, this\n"
     +"statue is a maid of simple beauty. Her long hair\n"
     +"cascading down over her face, seemingly blown in\n"
     +"in the winds. She wears a long pale blue gown and\n"
     +"is draped in a plain white cape. In her hands is\n"
     +"a silver harp, she seems to whisper.\n");
   add_item(({"fifth statue", "fifth", "5", "statue 5"}),
      "A man of vigilance, this animate statue\n"
     +"stand in defiance, proud yet gentle. He wears a robe of\n"
     +"deep brown and a short cloak of emerald green. In his\n"
     +"right hand he holds a tall spear, in his left, a white\n"
     +"shield emblazoned with a brilliant green tree. On his\n"
     +"head he wears a garland of silver-blue leaves.\n");
   add_item(({"sixth statue", "sixth", "6", "statue 6"}),
      "This statue is a tall and aged man, bearded\n"
     +"long and white. He wears a long and royal robe of\n"
     +"blue and white, a silver helmet and a ring of gold\n"
     +"set with a large sapphire. He holds a silver flagon\n"
     +"close to his chest with his left hand. In his right\n"
     +"hand he bears a gold and amber rod.\n");
   add_item(({"seventh statue", "seven", "7", "statue 7"}),
      "This statue is of a noble and wise looking\n"
     +"young man. His face presents feelings of uncompromising belief, yet\n"
     +"not stern or unkind. He wears a silver cloak, a white robe\n"
     +"and a gray stole. In his right hand is a silver candlestick\n"
     +"that holds a blue candle. His left hand holds a bright\n"
     +"longsword which he holds over his heart.\n");
   add_item(({"eighth statue", "eighth", "8", "statue 8",
              "eigth statue", "eigth"}),  /*Some players can't spell!!  ;-) */
      "Like some forgotton image, this statue\n"
     +"remains shrouded in darkness. It is an ancient man, his hair\n"
     +"gray and long. He wears a robe and gown of black. Upon his\n"
     +"back a mantle of silver, on which runes of gold and black\n"
     +"are embroidered, upon his head is a black cap. His left\n"
     +"hand is held aloft in some cryptic gesture, his right hand\n"
     +"clutches a sealed scroll.\n");
   add_item(({"ninth statue", "ninth", "9", "statue 9"}),
      "An intense and massive man, strong and muscular,\n"
     +"is this statue. He stands lordly, bearded long and dark, wearing\n"
     +"a silverly breastplate. Upon his head a diadem set with diamonds,\n"
     +"his hands are covered in silvery gauntlets. In his right hand he\n"
     +"holds a dark silver inlaid hammer at his side. His left hand is\n"
     +"clenched in a fist and held over his chest.\n");
   add_item(({"tenth statue", "tenth", "10", "statue 10"}),
      "This statue is tall and thin, depicting a dark\n"
     +"and cowled lordly figure. The face appears elven, but is too\n"
     +"hidden under the cowl to identify. The lord is cloaked in black,\n"
     +"wearing a dim gray robe. A luminous pectoral star amulet hangs\n"
     +"from his neck. In his right hand is a long white staff.\n");
   add_item(({"eleventh statue", "eleventh", "11", "statue 11"}),
      "A statue of luminous beauty taking the shape\n"
     +"of a woman robed and hooded in white, but her face clear and\n"
     +"emotive. She expresses hope and trust, faith and vigilance. She\n"
     +"wears a cloak of scarlet over her robe, from her neck hangs a\n"
     +"luminous pectoral star amulet. She hold a gold chalice before\n"
     +"her and looks upwards.\n");
   add_item(({"twelfth statue", "twelfth", "12", "statue 12"}),
      "Like a revelation itself, this statue stands\n"
     +"as an affront to all knowledge, for in it some divine power\n"
     +"seems to reach out and grasp the living. It is the likeness of\n"
     +"a tall man. He stands bound in black, draped with a mantle of\n"
     +"gray and from his neck hangs a luminous pectoral star amulet.\n"
     +"In his right hand he holds a black tome, set with many silver\n"
     +"seals, at his side. His left hand holding a brass horn at his\n"
     +"other side, it gleams bright.\n");

    str_numbers = ({ "zeroth", "first", "second", "third",
		     "fourth", "fifth", "sixth", "seventh",
		     "eighth", "ninth", "tenth", "eleventh",
		     "twelfth" });
  
    create_skill_raise();
    set_up_skills();
}

string
wizinfo()
{
   return ("If there should be due cause to close down the guild, do so by\n" +
      "typing:  Call here close_guild\n" +
      "This will temporarily prevent mortals from entering. After a\n" +
      "reboot, the guild will be open by default. Please send me some\n" +
      "mail if there is anything that needs to be fixed.\n\n   /Mecien.\n"
   );
}

void
enter_inv(object ob, mixed from) 
{
   ::enter_inv(ob, from);
   
   if (!query_ip_number(ob) || !closed)
      return;
   
   if (ob->query_wiz_level()) 
      write("\n\nWARNING!\nYou shouldn't be here. " +
      "I'm doing some work on the guild.\n");
   else
   {
      write("The guild is closed. Come back later.\n");
      ob->move(GUILD_DIR+"hall");
   }
}

void
init()
{
   ::init();
   add_action("join", "make");
   add_action("leave", "renounce");
   add_action("ask", "ask");
   add_action("list", "list");
   init_skill_raise();
   init_guild_support();
   add_action("read", "read");
   add_action("offer", "offer");
}

string
close_guild()
{
   if (closed)
   {
      closed = 0;
      return "  **The guild is now open**";
   }
   closed = 1;
   return "  **The guild is now closed**";
}

query_closed() { return closed; }

int
read(string str)
{
   NF("Read what? Tome?\n");
   if (str!="tome" && str!="book") return 0;
   write("You open the aged tome and read its pages:\n\n\n" +
      "         THE ANCIENT MYSTIC ORDER\n" +
      "        ------===============-----\n"+
      "If ye seek to bring thyself into our fold, thou must\n" +
      "with all thy heart seek after Truth. Our wisdom abides\n" +
      "in Truth, being revealed through the Ancients.\n" +
      "We are an order of light and holiness. Our light being that\n" +
      "given from the Ancients, resting upon the foundation of\n" +
      "holiness which we aspire to through mystery.\n" +
      "If ye seek our way, make then thy oath here and the Ancients\n" +
      "shall witness it thus. Be ye warned, to renounce thy oath shall be\n" +
      "a matter of grave consequence. Indeed thy life shall be forfeit\n" +
      "to the Ancients, thou will surely die.\n\n" +
      "The Ancients will take from thee a third of thy future\n" +
      "gains in experience as recompense for thy oath, a sacrifice\n" +
      "suitable for the gifts thou shalt receive from them.\n" +
      "Thou shalt be expected to uphold the mystic laws and remain\n" +
      "true to thy solemn vows. Many are thy obligations in this great\n" +
      "Order, so learn our ways before ye make thy oath.\n");
   return 1;
} 

int
offer(string str)
{
    object *items, r_ob;
    int i, statue_number;
    string correct_ob;
    string str1, str2, statue_str;

    NF("Thy path must be holiness before any offering is made.\n");
    if (TP->query_alignment() < JOIN_LIM) return 0;
    /*
     * First I check if syntax is ok.
     */
    NF("Offer what before which statue?\n");
    if (!str || (sscanf(str, "%s before the %s statue", str1, str2) != 2 &&
		sscanf(str, "%s before %s statue", str1, str2) != 2))
	return 0;


    /*
     * Then find the object player was offering and to what statue
     */
    NF("Offer what before which statue?\n");
    if (!parse_command(str, all_inventory(TP),
        	"%i 'before' [the] %w 'statue'", items, statue_str)) 
        return 0;

/* 
	Special macro defined in cmdparse.h that handles
	the return value of a %i. It also handles parts of heaps such
	as coins etc. The two '0' mean that we use a standard access
	function, i.e. accessible things are on me or around me.

	As we in the parse_command has limited us to this_player's 
	inventory, the access function should have no effect in 
	this case.

	/Cmd
 */
   items = VISIBLE_ACCESS(items, 0, 0);

   if (sizeof(items) <= 0) return 0;

   for (i = 1; i < sizeof(str_numbers) ; i++) {
       if (statue_str == str_numbers[i]) {
	  statue_number = i;
	  break;
       }
   }

   switch(statue_number) {
       case 0: 
           NF("You must specify an existing statue.\n");
           return 0;
       case 1:
           correct_ob = MOQ_DIR + "flower";
           break;
       case 2: 
           correct_ob = MOQ_DIR + "leaf"; 
           break;
       case 3:
           correct_ob = MOQ_DIR + "ore";
           break;
       case 4:
           correct_ob = MOQ_DIR + "feather";
           break;
       case 5:
           correct_ob = MOQ_DIR + "acorn";
           break;
       case 6:
           correct_ob = MOQ_DIR + "ice";
           break;
       case 7:
           correct_ob = MOQ_DIR + "ash";
           break;
       case 8:
           correct_ob = MOQ_DIR + "scroll";
           break;
       case 9:
           correct_ob = MOQ_DIR + "gold";
           break;
       case 10:
           correct_ob = MOQ_DIR + "crystal";
           break;
       case 11:
           correct_ob = MOQ_DIR + "apple";
           break;
       case 12:
           correct_ob = MOQ_DIR + "dust";
           break;
       default: 
           NF("You must specify an existing statue.\n");
           return 0;
   }

   write("You offer " + COMPOSITE_DEAD(items) + " before the " +
         statue_str + " statue.\n");

   for (i = 0; i < sizeof(items); i++) {
       if(MASTER_OB(items[i])!=correct_ob) {
           write("Your offering is consumed by a blue flame.\n");
           write("Thy offering was in vain.\n");
           items[i]->remove_object();
           return 1;
       } else {
           r_ob = items[i];
       }
   }
   if(TP->query_skill(ENTRANCE_QUEST)!=statue_number) {
       write("Your offering is consumed by a blue flame.\n");
       write("Thy offering was in vain.\n");
       r_ob -> remove_object();
       return 1;
   }
   if (TP->test_bit("Terel", QUEST_MOQ_GROUP, QUEST_MOQ_BIT)) {
       write("You have already made your offering.\n");
       write("Your offering is consumed by a blue flame.\n");
       write("Thy offering was in vain.\n");
       r_ob -> remove_object();
       return 1;
   }
   write("The statue trembles with satisfaction.\n");
   if (TP->query_exp() <= QUEST_MOQ_EXP ) {
       TP -> add_exp(TP->query_exp());
       write("You suddenly feel much more experienced.\n");
   } else {
       TP -> add_exp(QUEST_MOQ_EXP);
       write("You suddenly feel more experienced.\n");
   }
   say(QCTNAME(TP) + " has become more experienced.\n");
   TP -> set_bit(QUEST_MOQ_GROUP, QUEST_MOQ_BIT);
   write_file(QUEST_LOG, TP->query_name() +
            " solved the mystic order quest (" +
            ctime(time()) + ")\n");
   return 1;
}

int
join(string str)
{
   int number;
   object shadow, mring;
   string *banned;
   int i;

   NF("Make what?\n");
   if (str != "oath" && str != "my oath") return 0;

   if (MEMBER(TP)) {
      NF("You are already one of the chosen.\n");
      return 0;
   }

   if (file_size(BANNED) > 0) {
      banned = explode(read_file(BANNED), "\n");
      for (i=0; i<sizeof(banned); i++)
         if (TP->query_real_name()==banned[i])
         {
            NF("You have been banned from the Ancient Mystic Order!\n");
            return 0;
         }
   }
   if (TP->query_guild_style("fighter")) {
      NF("Mystics can belong to no other guilds.\n");
      return 0;
   }

   /* Assign a random statue to the player, if the player is doing this
      for the first time, i.e. skill == 0.
    */
   if (TP->query_skill(ENTRANCE_QUEST)==0) {
       number = random((sizeof(str_numbers)-1)) + 1;
       write("A mysterious voice says: Let first thy name be proven. Bring "
        + "us an\noffering that shall mark thy name in dignity.\n");
       write("The "+str_numbers[number]+" statue emits a mysterious " +
             "glow.\n");
       write("A mysterious voice says: Let this be the icon of thy oath!\n");
       TP->set_skill(ENTRANCE_QUEST, number);
       return 1;
   }

/* If the MOQ is solved let the player join */

   if (TP->test_bit("Terel", QUEST_MOQ_GROUP, QUEST_MOQ_BIT)) {
       shadow=clone_object(MYSTIC_SHADOW);
       if (shadow->shadow_me(TP, GUILD_TYPE, GUILD_STYLE, GUILD)!=1){
          NF("For some unknown reason you cannot join this guild.\n");
          "/secure/master"->do_debug("destroy", shadow);
          return 0;
       }
       write("Thou art now of this ancient order.\n");
       mring=present(MYSTIC_RING, TP);
       if (!mring) {
          mring=clone_object(GUILD_DIR+"mring");
          mring->move(TP);
          write("There is a brilliant flash of blue light.\n");
          write("The voices of ancient spirits call out from the depths.\n");
          write("A silver ring appears in your hand.\n");
       }
       tell_all_about_new_member(TP);
       write_file(JOINED, TP->query_name() +
            " joined the Ancient Mystic Order (" +
            ctime(time()) + ")\n");
   } else { /* If not solved let the player get his/her/its statue number */
       number = TP->query_skill(ENTRANCE_QUEST);
       write("Thy offering has not yet been made.\n");
       write("The " + str_numbers[number] + " statue was chosen for you.\n");
   }
   return 1;
}

int
leave(string str)
{
   object ring;
   
   NF("Renounce what?\n");
   if (str!="oath" && str!="my trust") return 0;
   if (!MEMBER(TP)) {
      write("You are not a member of this guild.\n");
      return 1;
   }
   if (TP->remove_guild_occ()) {
       write("You abandon your vows to the order.\n");
       write("The void enters your soul and the Ancients depart from you.\n");
       TP->remove_cmdsoul(MYSTIC_SOUL);
       ring=present(MYSTIC_RING, TP);
       if (ring) {
         ring->remove_object();
         write("A spirit appears and takes away your ring.\n");
       }
       TP->update_hooks();
       tell_all_about_old_member(TP);
       write_file(JOINED, TP->query_name() +
            " left the Ancient Mystic Order (" +
            ctime(time()) + ")\n");
       if (TP->query_wiz_level()) {
         write("Lamentations resound from the depths of this place.\n");
         return 1;
       }
       write("So be it.\n");
       say(QCTNAME(TP) + " breaks his vows before the Ancients.\n");
       TP->set_hp(0);
       TP->do_die(TO);
   } else {
      write("Because of a bug you cannot leave the guild.\n");
   }
   return 1;
}

int
ask(string str)
{
   object ring;

   NF("Ask for what?\n");
   if (str != "ring" && str != "for ring") return 0;
   if (!MEMBER(TP)) {
      write("You are not a member of this guild.\n");
      return 1;
   }
   if (TP->query_mystic_rank() == MYSTIC_TRAITOR) {
      write("You are banned from this guild.\n");
      return 1;
   }
   ring = present(MYSTIC_RING, TP);
   if (ring) {
      write("The spirits sense you already possess one.\n");
      return 1;
   }
   ring = clone_object(GUILD_DIR+"mring");
   ring->move(TP);
   write("A spirit appears and gives you a silver ring.\n");
   return 1;
}

int
list(string str)
{
   object guilds;

   NF("List what?\n");
   if(str!="guilds")
      if(str && str!="titles") return 0;
   else{
      write("The ancient order ranks its followers "
         +"with the following titles:\n"
         +"mystic initiate.\n"
         +"mystic acolyte.\n"
         +"mystic of the white circle.\n"
         +"elder mystic of the white circle.\n"
         +"high elder mystic of the white circle.\n"
         +"mystic of the Holy Star.\n"
         +"elder mystic of the Holy Star.\n"
         +"high elder mystic of the Holy Star.\n"
         +"Mystic Cantor.\n"
         +"Mystic Exarch.\n"
         +"Mystic Archon.\n"
         +"Patriarch of the Ancients.\n"
      );
      return 1;
   }
   guilds=TP->list_mayor_guilds();
   if(guilds)
      write("You are a member of the following guilds:\n"+guilds);
   else
      write("You are not a member of any guild.\n");
   return 1;
}

void
set_up_skills()
{
    string me, ot;
   
   me = "defend yourself"; ot = "use defence skill";
   sk_add_train(SS_DEFENCE,     ({ me, ot }),        0, 0, 90 );
   me = "sense presences"; ot = me;
   sk_add_train(SS_AWARENESS,   ({ me, ot }),        0, 0, 80 );
   me = "parry"; ot = me;
   sk_add_train(SS_PARRY,       ({ me, ot }),        0, 0, 50 );
   me = "climb"; ot = me;
   sk_add_train(SS_CLIMB,       ({ me, ot }),        0, 0, 30 );
}

void
gs_hook_start_meditate()
{   
   write("Slowly you sit down in the quiet alcove and close your eyes.\n" +
      "A feeling of great ease and self control falls upon you.\n" +
      "You block off your senses and concentrate solely upon your\n" +
      "own mind. You find yourself able to <estimate> your different\n" +
      "preferences and <set> them at your own desire.\n" +
      "Just <rise> when you are done meditating.\n");
}

int
gs_meditate(string str)
{
   if (!MEMBER(TP)) {
      write("You are not a member of this guild.\n");
      return 1;
   }
   return ::gs_meditate(str);
}

int
sk_improve(string str)
{
   if (!MEMBER(TP)) {
      write("You are not a member of this guild.\n");
      return 1;
   }
   return ::sk_improve(str);
}

void
tell_all_about_new_member(object new)
{
   int i;
   object *ul;
   
   ul = users();
   for (i=0; i<sizeof(ul); i++) {
       if (MEMBER(ul[i]) && ul[i] != new && present(MYSTIC_RING, ul[i])) {
           tell_object(ul[i], "A mystic voice tells you that " +
                       new->query_name() + " has joined our order.\n");
       }
   } 
}

void
tell_all_about_old_member(object old)
{
   int i;
   object *ul;
   
   ul = users();
   for (i=0; i<sizeof(ul); i++) {
       if (MEMBER(ul[i]) && ul[i] != old && present(MYSTIC_RING, ul[i])) {
           tell_object(ul[i], "A mystic voice tells you that " +
                       old->query_name() + " has left our order.\n");
       }
   } 
}
