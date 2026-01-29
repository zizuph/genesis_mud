inherit "/std/object";
#include <stdproperties.h>
#include "/d/Shire/common/defs.h"
#include <ss_types.h>

#define MIN_LANG 22

int do_read(string str);

void
create_object()
{
   set_short("crumpled sheet of paper");
   add_name(({"paper","sheet","roster"}));
   add_adj(({"crumpled","sheet","sheet of"}));
   set_long("This crumpled sheet of paper has words written on it.\n");

   add_prop(OBJ_I_WEIGHT, 10);
   add_prop(OBJ_I_VOLUME, 10);
   add_prop(OBJ_I_VALUE, 0);
   add_prop("_i_am_mayor_roster_",1);

}

void
init()
{
    ::init();
   add_action("do_read","read");
}

int
do_read(string str)
{
    int lang;

   lang = TP->query_skill(SS_LANGUAGE);

   if(!str)
   {
     notify_fail("What?\n");
     return 0;
   }

    if((str != "words") && (str != "paper"))
   {
     notify_fail("Read what?\n");
     return 0;
    }

   if((lang + random(lang / 3)) < MIN_LANG)
   {
    write("The "+short()+" is illegible.\n");
    return 1;
   }


   write("The paper reads:\n\n"+
   "Bowman Oldbuck- Gamwich: Monday, Tuesday and Wednesday.\n"+
   "Carl Cotton- Whitfurrows: Monday through Saturday.\n"+
   "Isengrim Took- Frogmorton: Tuesday through Thursday.\n"+
   "Andwise Roper- Northern Bounds: All this month.\n"+
   "Samwise Gammidge- Western Bounds: For the next two weeks.\n"+
   "Bilbo Hornblower- Southern Bounds: All this month.\n"+
   "Hob Sandheaver- Patrol on the East Road: Next two weeks.\n"+
   "Sam Chubb, Amaranth Bunce, Largo Smallburrows, Hugo Bracegirdle, "+
   "Toby Brandybuck, Isenbold, Ferumbras, and Rosa Took all are assigned "+
   "to postal service.\n");
   return 1;

}
