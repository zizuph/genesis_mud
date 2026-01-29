//
// Sean-Rhian Book - book base for easy coding
//
// Zima May 25, 1998
//
inherit "/std/book";
#include <ss_types.h>
#include "defs.h"
 
int    lpp        = STD_LPP;                 // lines per page
int    min_lang   = STD_MIN_LANG_LEVEL;      // min lang needed to read
int    sr_level   = -1;                      // min sr_level req. to read
string bname;                                // book text file name
string title;                                // title of the book
 
void   set_lpp(int i)          { lpp=i;                }
void   set_min_lang(int i)     { min_lang=i;           }
void   set_sr_level(int i)     { sr_level=i;           }
void   set_book_file(string s) { bname=SR_BOOK_TEXT+s; }
int    query_lpp()             { return lpp;           }
int    query_min_lang()        { return min_lang;      }
int    query_sr_level()        { return sr_level;      }
string query_book_file()       { return bname;         }
string query_srbook_title()    { return title;         }
 
void create_book()
{
   set_short("black book");
   set_long("An empty black book.\n");
}
 
int allowed(object tp)
{
   if (sr_level <= -1) return 1;
   if (!(tp->is_saggart())) return 0;
   if ((tp->query_sr_level()) < sr_level) return 0;
   return 1;
}
 
string srb_read_page(int which)
{
   int    start=((which-1)*lpp)+1;
   seteuid(getuid());
   return (read_file(bname,start,lpp));
}
 
varargs void read_book_at_page(int which, string verb)
{
 
   if ((TP->query_skill(SS_LANGUAGE))<min_lang)
      {
      write("You are unable to read the cryptic writing.\n");
      return;
      }
   if (!allowed(TP))
      {
      write("The book is enchanted. Your vision blurs when you try to "+
            "look at the lettering.\n");
      return;
      }
   write(srb_read_page(which));
}

// masks /std/book.c, to remove say()
void read_it(string verb)
{
    switch (verb)
    {
    case "read":
    case "mread": if (book_is_closed)
                     write("The " + short(this_player()) + " is closed.\n");
                  else
                     read_book_at_page(what_page, verb); break;
                  break;
    case "turn":  turn_me(); break;
    case "open":  open_me(); break;
    case "close": close_me(); break;
    }
}
