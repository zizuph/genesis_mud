/*
 * 1k4.c
 * This is the back room of a library, lotsa books.
 * Don't know who the original author is.
 * Update and re-describe by Alaron August 15, 1996
 */

#include "default.h"

inherit CASTLE_ROOM;

void
create_room()
{
   ::create_room();
   set_short("Small library");
   set_long("   This is a small, back room attached to a small "+
	    "libary to the south. It seems as though it was put on "+
	    "as an afterthought, perhaps because there were more "+
	    "books than storage space. All of the walls are filled with "+
	    "stacked books, loose books and shelves filled with more "+
	    "books. There is a brightly burning fire in a round-stone "+
	    "fireplace in a corner to the west.\n\n");

   
   add_exit(CASTLE_DIR + "1k8","south",0);
   
    add_item( ({"fire", "bright fire", "burning fire"}),
             "It is a small cook fire to brew tea and heat "+
             "refreshments for those who spend long hours pouring "+   
             "over the texts in this room.\n");
   add_item(({"fire", "fireplace"}), "There is a bright fire burning in "+
      "the fireplace.\n");
   add_item(({"shelf","shelves"}),"The shelves are deeply varnished and "+
      "well taken care of. There are some books on them.\n");
   add_item(({"books","book"}),
      "The black and time darkened shelves contain several books.\n"+
	    "The titles are:\n" +
	    "        Monarchy\n" +
	    "        History of Telberin\n" +
	    "        Elven magic\n" +
	    "        Telberin\n" +
	    "The other books are old and decayed or simply don't look all "+
	    "that interesting.\n"+
	    "To read a book, try <read [title]>.\n");
      
}

void
init()
{
   ::init();
   add_action("do_read","read");
}

int
do_read(string str)
{
   str = lower_case(str);
   if(str == "monarchy")
      {
	  write("You do some reasearch on the monarchy of Telberin ...\n\n");
	  say(QCTNAME(this_player())+" eagerly delves into a book on "+
	      "the monarchy of Telberin.\n");
	  write("The monarchy of Telberin and the surrounding lands dates "+
		"back nearly two thousand years. Up until a few years ago, "+
		"some of the elders remembered their childhood during the "+
		"formation of the monarchy. The monarchy of Telberin was "+
		"instuted after the city, with the aid of the Keepers of "+
		"Telberin, repelled several attacks against human and "+
		"orc alike. The King was chosen from the ranks of the "+
		"Protectorate of Telberin, and was referred to as "+
		"Elluin the Wise. His wife, of the Order of Telan-Ri, was "+
		"the greatly adored Harmena. Since then, the Kings and "+
		"queens are all descendants in some fashion from these "+
		"two founders.\n");
	  return 1;
      }
   if((str == "history") || (str == "history of telberin"))
   {
       write("You do some research on the history of Telberin ...\n\n");
       say(QCTNAME(this_player())+" eagerly delves into a book on "+
	   "the history of Telberin.\n");
       reset_euid();
       write("You manage to find an excerpt from a historian's "+
	     "journal ...\n\n");
       reset_euid();
       this_player()->more(read_file(
                     "/d/Emerald/common/guild/kot/help/history.help"));
       return 1;
   }
    if ( (str=="magic") || (str=="elven magic") )
   {
       write("You do some research on the nature of elven magic ...\n\n");
       say(QCTNAME(this_player())+" delves into a book on the nature of "+
	   "elven magic.\n");
       write("The nature of the magic used by the Keepers of Telberin "+
	     "is quite different than the magic most people have seen "+
	     "or heard of before. It is far from prosaic magic, it is "+
	     "a deep, religious magic. They do not consider it magic. "+
	     "Rather, they consider their abilities to be gifts from "+
	     "Telan-Ri, and through their worship and ritual, such "+
	     "gifts as 'spells' can be granted to them by communing "+
	     "with Him. A lot of what is in this text seems to be "+
	     "nothing more than conjecture, and some of it seems "+
	     "a bit unreliable.\n");
       return 1;
   }
   if(str == "telberin")
   {
       write("The city itself has the most powerful "+
	     "temples within its walls. It has been "+
	     "built up over two thousand years and many parts are old "+
	     "enough to be beyond the oldest Elf living. It is a "+
	     "beautiful and ancient city which is ruled by a fair and "+
	     "just King and Queen.\n");
       return 1;
   }
   notify_fail("You read that book for a while, but it is not all that "+
	       "interesting.\n");
   return 0;
   
}

