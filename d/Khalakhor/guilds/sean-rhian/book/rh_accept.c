// Rhian of Acceptance
#include "defs.h"
inherit  SR_RHIAN;
 
void create_book()
{
   title="Rhian of Acceptance";
   set_short("purple cloth-bound book");
   add_name(({"acceptance", lower_case(title)}));
   add_adj(({"cloth-bound","purple"}));
   set_long("It is a purple cloth-bound book entitled: "+title+".\n");
   set_max_pages(3);
   set_sr_level(SRLVL_SEARM1);
   set_book_file("rh_accept.txt");
   add_prop(SR_RES_BOOK,1);
   set_cmdlist(({
      "rhian of acceptance",
      "shout Luiadh bi Ardaugh!",
      "shout Luiadh bi Maighal an Archangel!",
      "shout Luiadh bi am Solsheyderi!",
      "shout Seadh Car Daonnan!",
      "say Seeker, do you come before the altar of Ardaugh seeking the "+
           "Harmony of The Way?",
      "say Should you be accepted to travel The Way, are you prepared to "+
           "submit yourself in Obedience as a disciple of The Way?",
      "say So be it!",
      "say Hence you are sent on a journey into the mysteries of Ardaugh, "+
           "to prove yourself worthy of the gift of Harmony.",
      "say Seek ye the Wisdom of Ossian, the ancient Oracle of The Way, "+
           "and you shall be enlightened.",
      "say Receive this token of your journey.",
      "say This shall be a sign unto us, and to the world, that you seek "+
           "the Harmony of Ardaugh.",
      "say It shall also be a sign of your worthiness and enlightenment.",
      "say Return it unto us when you are fully enligtened in he Wisdom of "+
           "Ossian.",
      "say and present it as your sacrifice and token of worthiness.",
      "say May the Solsheyderi bless you on your quest.",
      "say Go in Harmony!"
      }));
}
