/* Generic npc modules
**
** This inheritable module is designed to make NPCs for a room
** Use: inherit this file, call the setup functions in create_room,
**      and make the monsters in reset_room.
** History:
** Date        Coder       Action
**----------   ----------- ----------------------------------
** 1/30/97     Zima        Created
**
*/
#include <macros.h>
#define NPC_MAX 5
/* global vars */
string  npc_dir="";               /* directory where npc files are found   */
string *npc_list=({});            /* list of filenames relative to npc_dir */
string  npc_arr_msg=" arrives.";  /* npc arrival message                   */
object *npc = allocate(NPC_MAX);  /* list of pointers to the npcs          */
 
/* set-up functions */
void npc_set_dir(string folder)      { npc_dir=folder; }
void npc_set_arrival_msg(string msg) { npc_arr_msg = msg; }
void npc_set_list(string *theList)   { npc_list = theList; }
 
/* clone the npcs, equip them, and move them into the room */
void npc_make_monsters() {
   int    i;
   int    num=sizeof(npc_list);
   object Tr=this_object();
 
   if (num > NPC_MAX) num=NPC_MAX;
   for (i=0; i<num; i++) {
      npc[i]=clone_object((npc_dir+(npc_list[i])));
      npc[i]->equip_me();
      npc[i]->move(Tr);
      tell_room(Tr,QCNAME(npc[i])+npc_arr_msg+"\n");
   }
}
