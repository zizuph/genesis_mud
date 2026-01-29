#include "/d/Immortal/std/domain.h"

inherit "/d/Immortal/std/book";

void
create_book()
{
  set_name("the Battle of Three Armies");
  add_name("book");
  set_short("leather-bound book");
  set_long("The thick, black, leather-bound book appears very old, the "+
    "leather binding is cracked in many places and the paper has yellowed "+
    "with time. Upon the cover is the text 'The Battle of Three Armies', "+
    "which appears to be a sizeable story. Perhaps you should open it, "+
    "check the 'index' and read the pages, it might prove interesting.\n");
  set_title("The Battle of Three Armies\n");
  set_text_file("/d/Immortal/volcano/citadel/docs/THREE_ARMIES");
  set_pages(({ ({1, 20}),
               ({21, 20}),
               ({41, 20}),
               ({61, 20}),
               ({81, 20}),
               ({101, 20}),
               ({121, 20}),
               ({141, 20}),
               ({161, 20}),
               ({181, 20}),
               ({201, 20}),
               ({221, 20}),
               ({241, 20}),
               ({261, 20}),
               ({281, 20}),
               ({301, 20}),
               ({321, 20}),
               }));
  set_page_ids(({
                 "In the beginning",
                 "The Battle continued",
                 "The Battle continued",
                 "The Battle continued",
                 "The Battle continued",
                 "The Battle continued",
                 "The Battle continued",
                 "The Battle continued",
                 "The Battle continued",
                 "The Battle continued",
                 "The Battle continued",
                 "The Battle continued",
                 "The Battle continued",
                 "The Battle continued",
                 "The Battle continued",
                 "The Battle continued",
                 "The Battle continued",
                  }));
}
