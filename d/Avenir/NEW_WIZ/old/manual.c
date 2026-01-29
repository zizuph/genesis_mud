// The Avenir New Wiz Manual
// file name:    /d/Avenir/NEW_WIZ/manual.c
// creator(s):   Tepisch
// last update:  Lilith, March 1997
// purpose:      So you can carry the docs around with you :)
// note: 
// bug(s):
// to-do:

 
inherit "/std/book";
#include "/d/Avenir/common/common.h"  
#define DIR "/d/Avenir/NEW_WIZ/old/"
void
create_book()
{
    set_name("book");
    add_name("manual");
    add_adj(({"golden", "gray", "silk", "avenir", "domain", "wizard",
        "new", "new wizard"}));
    set_short("Avenir wizard's manual");
    set_long("A book with a gray silk cover. It is outlined in "+
        "golden light, and the words: Avenir's New Wizard Manual "+
        "are written on it.\n");

    set_max_pages(20);

    add_prop(OBJ_I_NO_GIVE, "Don't give it away!\n");
    add_prop(OBJ_I_NO_DROP, "Not a good idea.\n");
    add_prop(OBJ_M_NO_SELL, "Not a good idea.\n");
    add_prop(OBJ_M_NO_STEAL, 1);

    seteuid(getuid());
}
 
void
read_book_at_page(int which)
{

    switch(which)
    {
        case 1:    cat(DIR + "CONTENTS");   break;
        case 2:    cat(DIR + "A");          break;
        case 3:    cat(DIR + "B");          break;
        case 4:    cat(DIR + "C");          break;
        case 5:    cat(DIR + "D");          break;
        case 6:    cat(DIR + "E");          break;
        case 7:    cat(DIR + "F");          break;
        case 8:    cat(DIR + "G");          break;
        case 9:    cat(DIR + "H");          break;
        case 10:   cat(DIR + "I");          break;
        case 11:   cat(DIR + "J");          break;
        case 12:   cat(DIR + "K");          break;
        case 13:   cat(DIR + "L");          break;
        case 14:   cat(DIR + "M");          break;
        default:   cat(DIR + "CONTENTS");   break;
    }
    return;
}
 

string query_auto_load() {  return MASTER + ":";  }

