#include "/d/Immortal/std/domain.h"

inherit "/d/Immortal/std/book";

void
create_book()
{
  set_name("the Book of Belythyn");
  add_name("book");
  set_short("leather-bound book");
  set_long("The book is bound in sturdy leather, embossed with silver "+
    "letterings, which read 'The Book of Belythyn'. Upon the dark leather "+
    "cover, below the script, is the image of a long, two-handed sword "+
    "beneath a strange helm with no slit in the visor."+
    "\nDISCLAIMER: This is just a draft, once a more detailed history of "+
    "Kha'Sukri, the Paladins, the Kraxian Warriors and the Betrayel become "+
    "available, I'll have this looking like a chapter out of the "+
    "Silmarillion *grin*\n"+
    "Lord Stexx Firesteel - May 5 1995"+
    "\n");
  set_title("The Book of Belythyn\n");
  set_text_file("/d/Immortal/volcano/citadel/docs/BELYTHYN");
  set_pages(({ ({1,20}), ({21,18}), ({39,20}), ({59,25}), }));
  set_page_ids(({"Belythyn's Youth",
                  "Belythyn's Youth (cont'd)",
                  "Belythyn in Kha'Sukri",
                  "Belythyn with the Kraxian Warriors",
                  }));
}
