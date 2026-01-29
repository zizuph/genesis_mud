
/*  
    The alchemist's foyer in Gelan 

    coder(s):   Maniac

    history:  
               22.3.95     Modified                     Maniac
               28.2.95     Created                      Maniac

    Comments: Alchemist stands around here, can allow players
              to begin alchemist quest by giving them potion.
*/


#pragma save_binary

#include "defs.h"
#include "room.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <money.h>
#include GUARD_INCLUDE
#include ALCHEMIST_QUEST
#undef PINK_POTION

inherit GELAN_BASE_ROOM;

object keeper;
object box; 
string *permitted = ({ });


void
fix_keeper()
{
  keeper = clone_object(GELAN_MONSTERS + "raspatoon");
  keeper->move(TO);
  tell_room(this_object(), QCTNAME(keeper) + " arrives.\n");
}

void
reset_room()
{
  if (!objectp(keeper)) fix_keeper();
#ifdef PINK_POTION
  if (!objectp(box)) { 
     box = clone_object(GELAN_OBJECTS+"potion_box"); 
     box->move(this_object());
  } 
#endif
}

int
check_keeper()
{
  if (present(ALCHEMIST_NAME, this_object())) return 1;
  else return 0;
}


public void
create_gelan_room() 
{
   set_short("The alchemist's foyer");
   set_long("A spacious well decorated room where Raspatoon Goldiloon, " +
        "alchemist of Gelan, receives his visitors. Everything from " +
        "the exotic woven rugs on the floor to the cushioned seating " +
        "and impressive fireplace leaves a good impression on those " +
        "who visit here. Evidently Raspatoon likes to make his guinea " +
        "pigs feel at home. The things of most interest here though " +
        "are the wall adornments. On one wall is a huge diagram of the " +
        "signs of the zodiac, on another a picture of the four " +
        "alchemical elements, and on another a large unfurled scroll " +
        "with gold lettering. To the west there is a laboratory; the " +
        "strange bubbling sounds and odours that come from that " +
        "direction tell you as much.\n"); 


  add_item(({"seating", "cushioned seating"}), "The cushioned seating " +
             "looks very comfortable.\n");

  add_item(({"exotic rugs", "woven rugs", "exotic woven rugs", 
             "rugs"}), "The rugs are luxurious and by their exotic " + 
             "look it seems that they were " +
             "imported from some distant country.\n"); 

  add_item(({"fireplace", "impressive fireplace"}), "A large " +
             "grand fireplace, it seems pretty unused and ornamental.\n");  

  add_cmd_item(({"large scroll", "unfurled scroll", 
                 "large unfurled scroll",
                 "scroll", "lettering", "gold lettering"}), "read",
                 "@@scroll_long");

  add_item(({"large scroll", "unfurled scroll", 
             "large unfurled scroll",
             "scroll", "lettering", "gold lettering"}),
             "@@scroll_long");

  add_item(({"diagram", "zodiac", "signs", "signs of the zodiac",
             "huge diagram"}),
       "The diagram is of all the signs of the Zodiac in one large " +
       "circle; the diagram almost covers an entire wall. At the " +
       "centre of the diagram is written the following text:\n" + 
       "`The timing of alchemical operations should accord with " +
       "appropriate astrological configurations. The celestial " +
       "bodies are indeed animate - they are instruments, agents " +
       "of divine will, governing the growth of everything upon " +
       "the earth. Each metal is influenced by, and corresponds to, " +
       "a particular planet (for instance copper to Venus). Celestial " +
       "influence on alchemical experiments may be assessed " +
       "astrologically, by studying the position of the planets in " +
       "relation to the signs of the Zodiac for the time in question. " +
       "It would not be an understatement to say that timing is " +
       "everything.' - Chyron Garr, Alchemist Supreme of the Ages.\n" +
       "Underneath is written in plain handwriting:\n" +
       "`Yes, timing is everything, so make sure that in your " +
       "calculations you also allow yourself adequate time for a " +
       "couple of visits to the privy, a sandwich break and a quick " +
       "ale down at the local. *Burp*.' - Raspatoon Goldiloon, " +
       "Alchemist of Gelan.\n"); 

   add_item(({"picture", "elements", "alchemical elements", 
             "four elements", "four alchemical elements"}), 
      "On one wall is a picture of the four alchemical elements, one " +
      "at each corner of a square. They are depicted as powerful forces " +
      "or deities: air as the god of wind, water as a mighty whirlpool, " +
      "fire as a raging inferno and earth as a mountain god. In the " +
      "middle of the picture is some text, which reads:\n" +
      "`All substances are made of the four basic elements earth, " +
      "air, fire and water, and each element is composed of two " +
      "qualities, there being four qualities in all: hot, dry, moist " +
      "and cold. The element of air is hot and moist, fire hot and " +
      "dry, water cold and moist, and earth dry and cold. By changing " +
      "a quality in each element, transformation becomes possible. The " +
      "elements are of course forces or agencies rather than the " +
      "common entities that we know. The elements are found only at " +
      "the heart of matter.' - Chryon Garr, Alchemist Supreme of " +
      "the Ages.\n" + "Underneath is written in plain handwriting:\n" +
      "`I can't help thinking that this periodic table may need " +
      "some minor alterations before it can be called finished.' - " +
      "Raspatoon Goldiloon, Alchemist of Gelan.\n");

   add_prop(ROOM_I_INSIDE,1);  /* This is a real room */

   add_exit(GELAN_ROOMS + "square_corner_nw","east",0);
   add_exit(GELAN_ROOMS + "alchemist_lab","west", "@@lab_check");

   reset_room();
}


/* Stop people taking potion from room */
void
leave_inv(object ob, object dest)
{
    object p;

    ::leave_inv(ob, dest);
    if (p = present(AQ_GREEN_POTION, ob)) {
        ob->catch_msg("You notice the " + p->short() + " magically " +
                      "removed from your possessions.\n");
        p->remove_object();
    }
}


string
scroll_long()
{
  return "On the large scroll is written in gold lettering:\n" +
    "`The earth is a living organism that is in a constant state " +
    "of change and growth. Within its bosom it holds Gold, the " +
    "incorruptible and pure, the divine substance, containing " +
    "the perfect balance of all four elements of earth, air, " +
    "fire and water. Indeed Nature grows Gold in the earth, as " +
    "Nature is in a constant process of perfecting that which is " +
    "originally gross or corrupt into that which is incorruptible " +
    "and pure. Thus in due course all metals will by the forces of " +
    "Nature grow to become Gold. It is such a process of perfecting " +
    "that we must study as the Central Goal of Alchemy.' - Chryon " +
    "Garr, Alchemist Supreme of the Ages.\n" +
    "Underneath is written in plain handwriting:\n" +
    "`Turning base metals into gold is all very well, but personally " +
    "I've found it's a lot more fun and a lot more easy to turn " +
    "_ignorance_ into gold by selling impressively coloured bubbly " +
    "potions to the local population for exorbitant prices.' - " +
    "Raspatoon Goldiloon, Alchemist of Gelan.\n";
}


void
enter_inv(object ob, object old)
{
    ::enter_inv(ob, old);
    if (!interactive(ob) || !check_keeper()) return;

    if (ob->query_prop(AQ_EXPERIMENT_FAILURE) ||
        ob->query_prop(AQ_CURE_SUCCESS))
        keeper->react(ob);
}


int
has_side_effect(object tp)
{
    if (present(STUTTER_NAME, tp) ||
        tp->has_weaken_stat_shadow() ||
        tp->has_g_change_shadow())
        return 1;
    else
        return 0;
}


int
lab_check()
{
    object tp = this_player();

    if (has_side_effect(tp))
        return 0;
    else {
       tp->catch_msg("You try to go west into the laboratory " +
          "but a strong magical force stops you.\n");
       tell_room(this_object(), QCTNAME(tp) + " tries to go " +
         "west into the laboratory but a strong magical force " +
         "stops " + tp->query_objective() + ".\n", tp);
       if (check_keeper())  {
           keeper->command("say My laboratory will only allow people " +
                 "in if I have instructed it to do so!");
           keeper->command("emote grins enigmatically.");
       }
       return 1;
    }
}
