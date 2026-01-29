/* Kirk of Port City - Abbey garden
**
** History:
** Date        Coder       Action
**----------   ----------- ----------------------------------
** 1/18/98     Zima        Created
** 3/9/98      Zima        Add lilac shrub support
*/
#define  INC_KHALSYS_DEFS 1
#include "defs.h"
#include <macros.h>
#include <ss_types.h>
#define  LILAC_ID_DIFF 44
inherit  ROOM+"kgardbase";
int numbunches=0;
 
void reset_room() {
   numbunches=6;
}
 
/* room definition */
void create_khalakhor_room() {
   setup_garden_room();
   set_long((query_std_long())+"The heavy scent of a flowering shrub next "+
            "to the abbey wall hangs heavy in the air here.\n");
 
   add_item(({"lilac","lilac shrub"}),"@@exa_lilac");
   add_item("lilacs","@@exa_lilacs");
   add_item(({"shrub","purple flowers","shrub flowers","flowers on shrub",
      "bunches","bunches of flowers","bunch of flowers","bunch"}),
      "@@exa_shrub");
   add_exit("kgarden5","north");
   add_exit("kgarden1","south");
   add_exit("kgarden4","east");
   reset_room();
}
 
string shrubdesc()
{
   return (
      "There is a large shrub growing next to the abbey wall, just to "+
      "the west of where you are standing. It must be a transplanted and "+
      "cultivated plant, as it is not native to this land. It is covered "+
      "with small purple flowers which hang in bunches like grapes. The "+
      "heavenly perfume of these flowers pervades the air here, tempting "+
      "you to pluck them from the shrub. ");
}
 
string recog_shrub_desc()
{
   return (shrubdesc() +"You recognize the flowers as lilacs.\n");
}
 
string exa_lilacx(string s)
{
   if (TP->query_skill(SS_HERBALISM) >= LILAC_ID_DIFF)
      return (shrubdesc()+"You recognize the flowers as lilacs.\n");
   return ("You find no lilac"+s+".\n");
}
string exa_lilac() { return exa_lilacx(""); }
string exa_lilacs() { return exa_lilacx("s"); }
string exa_shrub()
{
   if (TP->query_skill(SS_HERBALISM) >= LILAC_ID_DIFF)
      return (shrubdesc()+"You recognize the flowers as lilacs.\n");
   return (shrubdesc()+"\n");
}
 
/*
** DO_PICK - allows player to pick flowers
*/
int do_pick(string cmd) {
   object bunch;
   int    rc;
 
   //check arguments to command
   if (!stringp(cmd))
      { notify_fail("Pick what from what?\n"); return 0; }
   rc = parse_command(cmd,({TO}),
        "[a] [the] [bunch] [of] 'flower' / 'flowers' / 'lilac' / 'lilacs' "+
        "'from' [the] [a] 'shrub' / 'vine' / 'bush'");
   if (!rc)
      { notify_fail("Pick what from what?\n"); return 0; }
 
   // args OK, so do pick if any here
   if (numbunches <=0)
      write("None of the remaining bunches of flowers are pickable.\n");
   else {
      numbunches--;
      bunch=clone_object(COM_HERBS+"lilac");
      bunch->move(TP);
      write("You pick a "+(bunch->query_short())+" from the shrub.\n");
      tell_room(TO,QCTNAME(TP)+" picks a "+(bunch->query_short())+
                   " from the shrub.\n",TP);
   }
   return 1;
}
 
void init() {
   ::init();
   add_action(&do_pick(),"pick");
   add_action(&do_pick(),"pluck");
}
