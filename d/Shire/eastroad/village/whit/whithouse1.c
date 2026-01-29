inherit "/d/Shire/eastroad/village/whit/whithouse";
#include "/d/Shire/common/defs.h"
#include <macros.h>


create_house()
{
   set_short("Hobbit house");
   set_long("This is a small home in Whitfurrows, that is owned by a " +
      "couple of hobbits.  There are two beds against the far wall, with " +
      "a cupboard, chairs and a table.  Set into a wall is a small window.  " +
      "The house is neat and tidy, and is obviously much loved by its " +
      "owners.\n");
   
add_exit("/d/Shire/eastroad/village/whit/whitlane1","out");
   
/*  Two hobbits from the hobbitmaker */
}
