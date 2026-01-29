/* Corpse on a pole
** This is a corpse which doesn't rot, on a pole, a warning of the Kretans
** for visitors of Argos.
** History:
** Date          Coder           Action
** ----------- ---------------  ----------------------------------------
**  9/30/96    Zima             Created
*/
inherit "std/object";
#include <stdproperties.h>
#include <composite.h>
#include <macros.h>
#include "defs.h"
 
#define MAX_LOOT 4
#define ADJ1 ({                                                        \
        "fat","skinny","emaciated","plump","muscular","sad","short",   \
        "tall","long-legged","short-legged","ugly","handsome",         \
        "long-armed","short-eared","long-nosed","wrinkled","hairy",    \
        "pale","dark-skinned","gaunt","crooked-nosed","stiff"          \
        })
#define ADJ2 ({                                                        \
        "red-haired","black-haired","blonde-haired","brown-haired",    \
        "red-bearded","black-bearded","brown-beared","bald",           \
        "dark-skinned","light-skinned","olive-skinned","long-haired",  \
        "bushy-eyebrowed","short-haired","old","young","middle-aged"    \
        })
#define RACES ({"human","elf","gnome","orc","human","dwarf","elf",     \
                "human"})
#define LOOT ({"armours/ccloak","armours/cmail","armours/cboots",      \
               "armrous/crobe","armours/chelmet","weapons/csword",     \
               "weapons/caxe","weapons/cknife","armours/cring",        \
               "armours/cbelt","armours/cshield"})
 
int looted=0;
 
void create_object() {
    string adj1=ADJ1[(random(sizeof(ADJ1)))];
    string adj2=ADJ2[(random(sizeof(ADJ2)))];
    string race=RACES[(random(sizeof(RACES)))];
    string text;
 
    set_name("corpse on a pole");
    add_name(({"corpse",race,"pole"}));
    add_adj(({adj1,adj2}));
    set_short("corpse of a "+adj1+" "+adj2+" "+race+" on a pole");
    set_long(
       "The bloody corpse of a "+adj1+" "+adj2+" "+race+" hangs "+
       "impaled from a long pole which is set deep in the ground. A sign "+
       "hangs around the neck of the unlucky "+race+". The "+
       "sight sends chills down your spine.\n");
 
    add_item("sign",
       "It's just a crumpled piece of wood on a thin rope, hanging around "+
       "the neck of the victim. There are words written on it with blood.\n");
 
    switch (random(5)) {
       case 0:  text="It reads: The same to all who come here!\n";      break;
       case 1:  text="It reads: I was lucky. I died quickly.\n";        break;
       case 2:  text="It reads: Someone send word to my mother.\n";     break;
       case 3:  text="It reads: Death to all intruders!\n";             break;
       default: text="It reads: Those who go further shall face the same!\n";
    }
    add_cmd_item("sign","read",text);
 
    add_prop(OBJ_I_NO_GET, 1);
    add_prop(OBJ_M_NO_GET, 1);
    add_prop(OBJ_I_NO_INS, 1);
    add_prop(OBJ_M_NO_INS, 1);
}
 
void reset_me() { looted=0; }
 
void search_done(object Tr, object To, object Tp) {
   object *loot=allocate(MAX_LOOT);        /* array of looted objects  */
   string *ldesc=({});                     /* array of loot short descs*/
   string cldesc;                          /* found message            */
   int    numloot=((random(MAX_LOOT))+1);  /* number of looted objects */
   int    i;                               /* loop/index               */
 
   /* if corpse already looted, nothing found */
   set_this_player(Tp);                /* for writes */
   if (looted) {
      write("Your search reveals nothing special.\n");
      return;
   }
 
   /* clone loot items, give to player, and create list of descs */
   for (i=0; i<numloot; i++) {
      loot[i]=clone_object((NWTERR_DIR+LOOT[(random(sizeof(LOOT)))]));
      ldesc=ldesc+({"a "+(loot[i]->query_short())});
      (loot[i])->move(Tp);
   }
 
   /* tell the player what he got */
   cldesc=COMPOSITE_WORDS(ldesc);
   write("You find "+cldesc+" on the "+(To->query_short())+".\n");
   looted=1;
}
 
void search_object(string parms) {
   object To=this_object();
   object Tp=this_player();
   object Tr=environment(Tp);
   tell_room(QCTNAME(Tp)+" starts searching the "+(To->query_short())+".\n",
             Tp);
   set_alarm(5.0,0.0,&search_done(Tr,To,Tp));
}
