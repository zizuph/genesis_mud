/*
**  Temple of Dephonia - Library middle room. General info on Order
**
**  History:
**  Coder        Date                       Action
**  ---------- --------  -----------------------------------------------------
**  Zima       1/1/95    Created
**
*/
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "defs.h"
 
create_room() {
   set_short("The Library of the Temple of Dephonia");
   set_long(break_string(
      "The musty smell of old parchment permeates the air as you " +
      "walk through the quiet shelves of the main part of the temple's "+
      "library. Tall, unornate bookshelves stand in rows, almost " +
      "touching the ceiling, rows of scrolls and tomes lined along " +
      "their shelves. The narrow row between the shelves leads to " +
      "the northwest and southeast through the library.\n",70));
 
   add_prop(ROOM_I_INSIDE,1);
 
   add_item(({"bookshelf","bookshelves","shelf","shelves"}), break_string(
      "Made of dark pine, the shelves are not decorated, except with "+
      "some dust in their corners.\n",70));
   add_item(({"scrolls","tomes"}), "@@exa_scrolls");
 
   add_item("scroll on Delphia","It is on the bookshelf.\n");
   add_cmd_item("scroll on Delphia","read","@@delphia");
   add_item("scroll on Demonstates","It is on the bookshelf.\n");
   add_cmd_item("scroll on Demonstrates","read","@@demonstrates");
   add_item("scroll on Dephonia","It is on the bookshelf.\n");
   add_cmd_item("scroll on Dephonia","read","@@dephonia");
   add_item("scroll on the Guardian","It is on the bookshelf.\n");
   add_cmd_item("scroll on the Guardian","read","@@guardian");
   add_item("scroll on the Talisman","It is on the bookshelf.\n");
   add_cmd_item("scroll on the Talisman","read","@@talisman");
   add_item("scroll on the Vision","It is on the bookshelf.\n");
   add_cmd_item("scroll on the Vision","read","@@vision");
   add_item("scroll on History Alpha","It is on the bookshelf.\n");
   add_cmd_item("scroll on History Alpha","read","@@alpha");
   add_item("scroll on History Beta","It is on the bookshelf.\n");
   add_cmd_item("scroll on History Beta","read","@@beta");
   add_item("scroll on History Gamma","It is on the bookshelf.\n");
   add_cmd_item("scroll on History Gamma","read","@@gamma");
 
   add_exit(ROOM_DIR+"library1","northwest",0);
   add_exit(ROOM_DIR+"library3","southeast",0);
}
 
string
exa_scrolls() {
   return break_string(
      "Hundreds of them lay in neat rows on the shelves, though you "+
      "can not read the titles of most due to the language or their "+
      "poor condition. You can make out the following titles: " +
      "Delphia, Demonstrates, Dephonia, the Guardian, "+
      "the Talisman, the Vision, "+
      "History Alpha, History Beta, History Gamma. "+
      "You can read one "+
      "of the scrolls with 'read scroll on <topic>'.\n",70);
}
 
string
delphia() {
   return break_string(
      "Delphia was the first Hierophant of our Order, chosen and " +
      "anointed by our Mother Dephonia herself at the founding of " +
      "the Order. To her was given the prophetic and power-giving " +
      "Vision which she has preserved in our sacred tomes. Delphia " +
      "lead our people through the persecution while in Argos, " +
      "through the battles for freedom, and finally into the " +
      "tranquility of our sacred forest. She is always portrayed " +
      "in the sacred dress of the one who recieves the Vision, the "+
      "black robe of the Raven encircled with stars and the golden "+
      "medallion of Delphia. To her be all honor and praise forever " +
      "and ever.\n",70);
}
string
demonstrates() {
   return break_string(
      "Demonstrates was the great warrior who led our people in " +
      "battle in the early days. Our Mother Dephonia blessed him " +
      "with his sacred armour which he wore bravely in battle. " +
      "His glory was crowned with the killing of Argosius who lead "+
      "the infidels against us long ago, aided by the Guardian of " +
      "the forest. " +
      "His armour is still one of the most treasured possessions " +
      "of the Order.\n",70);
}
string
dephonia() {
   return break_string(
      "Dephonia is the Goddess of the Light of Darkness, a mysterious " +
      "life force over which she gives the ability to channel to her " +
      "priests and priestesses. She was born of Archatheos, the king " +
      "of the olden gods, and his mortal High Priestess. Spurned " +
      "because of her mixed heritage, our Mother did not reveal " +
      "herself to mortals until she came to give refuge to those who "+
      "lived in near slavery to the Orders of the gods of Argos in "+
      "ancient times. To the faithful she gave the Light of Darkness, "+
      "as well as many other blessings throughout the history of our " +
      "Order. Her power is the very life force of our existence, and "+
      "to her we give our eternal worship.\n",70);
}
string
guardian() {
   return break_string(
      "During the great battles in ancient times with the Orders " +
      "of the gods of Argos and with their appointed king, our " +
      "mother Dephonia appeared before our tattered army, prepared "+
      "to face its greatest battle, and called forth from the forest "+
      "a great Guardian to aid us in our struggle. With the aid of " +
      "the guardian, our great hero Demonstrates slew King Argosius "+
      "in battle as well as his winged steed. The guardian has "+
      "the body of a giant muscular man, clothed only in a small "+
      "loincloth, with the head of a great bull. His gaze strikes " +
      "fear in the most courageous of foes, his breath burns their "+
      "skin, and his twisted horns of gold gore through the strongest "+
      "armour. The Guardian is summonsed by the Hierophant in times "+
      "of great danger, and then returns to his slumber in the realm " +
      "of the Light of Darkness.\n",70);
}
string
talisman() {
   return break_string(
      "The second great blessing of our Mother Dephonia, the Talisman "+
      "is a sacred instrument which allows its keeper to especially " +
      "channel the Light of Darkness to poison food and drink. It was "+
      "given to the faithful by our Mother in ancient times so that "+
      "they might do away with their most secure enemies.\n",70);
}
string
vision() {
   return break_string(
      "The Vision was given by our Mother to Delphia as she prayed for "+
      "the goddess' guidance. The vision she recieved was filled " +
      "with apocalyptic prophecy, and with the sacred truths of "+
      "the Light of Darkness. As instructed during the vision, Delphia "+
      "wrote down all that she saw, and these sacred tomes are now " +
      "the scriptures of our Order. The performance of the Ritual " +
      "of the Vision is now the rite of entrance into our Order, to " +
      "recieve the power of the Light of Darkness, and may also "+
      "be performed by others to recieve a great blessing from "+
      "our goddess.\n",70);
}
string
alpha() {
   return break_string(
      "The history of our Order begins with the colonization of "+
      "Tritheonopolis, now Argos, when the gods of old rescued "+
      "the remnants of the dying civilization of our pre-historic "+
      "ancestors and brought them to this isolated valley in Calia "+
      "where the new civilation could flourish in isolation. Three "+
      "Orders of the gods were raised to govern the people, but "+
      "these Orders enslaved them, forcing them to toil night and "+
      "day building great marble temples while the people lived in "+
      "tents. It was then that Dephonia appeared to our forefathers "+
      "and promised them freedom and power if they would follow her.\n",
      70);
}
string
beta() {
   return break_string(
      "Our mother chose and anointed Delphia to be the first Hierophant "+
      "of our Order, and began to give the power of the Light of "+
      "Darkness to her followers. We stuggled in vain to be accepted "+
      "by the ruling Orders of Argos, but like as our Mother was "+
      "rejected by their gods, so were we. Our struggle eventually "+
      "lead to war, and in the final great battle when Demonstrates "+
      "and the Guardian slew King Argosius were we given our freedom "+
      "to live peacefully in our beloved dark forest.\n",70);
}
string
gamma() {
   return break_string(
      "Our Mother revealed the place in the forest where we should "+
      "build her temple, and our ancestors labored many decades " +
      "to construct it, but for themselves and not for others as "+
      "they had done in Argos. At the dedication of the temple, "+
      "our Mother appeared and blessed the fruit of our labor, "+
      "filling the shrine with the Light of Darkness, turning "+
      "the marble to black. We have dwelt here in peace ever "+
      "since.\n",70);
}
