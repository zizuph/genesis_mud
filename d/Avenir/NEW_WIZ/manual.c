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
#define DIR "/d/Avenir/NEW_WIZ/book/"
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

    setuid();
    seteuid(getuid());
}
 
void
read_book_at_page(int which)
{
    string text;

    switch(which)
    {
        case 1:    text = read_file(DIR + "CONTENTS");   break;
        case 2:    text = read_file(DIR + "A");          break;
        case 3:    text = read_file(DIR + "B");          break;
        case 4:    text = read_file(DIR + "C");          break;
        case 5:    text = read_file(DIR + "D");          break;
        case 6:    text = read_file(DIR + "E");          break;
        case 7:    text = read_file(DIR + "F");          break;
        case 8:    text = read_file(DIR + "G");          break;
        case 9:    text = read_file(DIR + "H");          break;
        case 10:   text = read_file(DIR + "I");          break;
        case 11:   text = read_file(DIR + "J");          break;
        case 12:   text = read_file(DIR + "K");          break;
        case 13:   text = read_file(DIR + "L");          break;
        case 14:   text = read_file(DIR + "M");          break;
        default:   text = read_file(DIR + "CONTENTS");   break;
    }

    this_player()->more(text);
    return;
}
 

string query_auto_load() {  return MASTER + ":";  }

