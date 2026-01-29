//
// Canticles - player can 'chant' the canticles in this book
//
// Zima May 25, 1998
//
#include "defs.h"
inherit  SR_BOOK_BASE;
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#define  CHANT_TIME   3.0
 
string *verse;  // array of verses being chanted
 
void create_book()
{
   set_name("book");
   title="Lioar Orans Moyllee";
   add_name(({"canticles","canticle","_lioar_orans",title,
              lower_case(title),"lioar","orans","moyllee"}));
   set_short("purple cloth-bound book");
   set_long("It is a purple cloth-bound book entitled: "+
            title+".\n");
   add_prop(OBJ_I_NO_STEAL,1);
   set_max_pages(9);
   set_book_file("canticles.txt");
   set_lpp(10);
   set_sr_level(10);
}
 
int allowed(object tp)
{
   if ((::allowed(tp))||(present(SHAM_PENDANT,tp))) return 1;
   return 0;
}
 
void do_chant(int v, object tp, int which)
{
   object rm=ENV(TP);
 
   if (v>=sizeof(verse)) return;
   if (strlen(verse[v])<3) return;
   tp->catch_msg("You chant: "+verse[v]+"\n");
   tell_room(rm,QCTNAME(tp)+" chants: "+verse[v]+"\n",TP);
   v++;
   if ((v<sizeof(verse))&&(strlen(verse[v])>=3)) // sched next verse
      set_alarm(CHANT_TIME,0.0,&do_chant(v,tp,which));
   else
      if (rm->query_prop(CANTICLE_ROOM)) // if room wants to know when done
         rm->canticle_chanted(which,tp);
}
 
int chant(string cmd)
{
   string song;
   int    i;
 
   if (!allowed(TP)) return 0;
   if ((cmd != "canticle")&&(cmd != "oran"))
      write("Chant what?\n");
   else if (book_is_closed)
      write("You need to open the book to a canticle to chant it.\n");
   else
      {
      song=srb_read_page(what_page);
      verse=explode(song,"\n");
      do_chant(3,TP,what_page); // lines 0-2 are the title
      }
   return 1;
}
 
void init()
{
   ::init();
   add_action(&chant(),"chant");
}
