inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>

#include "../defs.h"

int sneeze,itch,smoke,stink,laugh;
void save_stick();

void create_object()
{
 set_name("stick");
 add_name("_trickster_stick_");
 set_adj("big");
 add_adj("heavy");
 add_prop(OBJ_M_NO_DROP,1);
 set_long(BS(
   "This is a big heavy stick, used to bonk people over the head with. "+
   "It is filled with many nooks and holes in which you can store "+
   "various things a Trickster uses for making mischief. You can read "+
   "the stick.\n"));
}

int is_living(object ob)
{
 if(!living(ob) || ob==TP) return 0;

 return 1;
}

void init()
{
 ::init();
 add_action("do_read","read");
 add_action("do_inspect","inspect");
}

int do_read(string what)
{
 if(!what || what!="stick") return 0;

 write("The stick has words on it that read: help trickster.\n");
 return 1;
}

int do_inspect(string what)
{
 NF("Inspect you stick moron!\n");
 if(!what || what!="stick") return 0;

 write(BS(
   "You inspect your stick trying to figure out what you have stored "+
   "in it.\n"));
 write(BS(
   sprintf("There are %d sneezing powders in your stick.\n",sneeze)));
 write(BS(
   sprintf("There are %d itching powders in your stick.\n",itch)));
 write(BS(
   sprintf("There are %d smokebombs in your stick.\n",smoke)));
 write(BS(
   sprintf("There are %d stinking liquids in your stick.\n",stink)));
 write(BS(
   sprintf("There are %d laughing gas vials in your stick.\n\n",laugh)));

 return 1;
}

int *get_contents()
{
 return ({ sneeze,itch,smoke,stink,laugh });
}

void outfit()
{
 int *max;

 max=ENV(TO)->query_max_stick();
 sneeze=max[0];
 itch=max[1];
 smoke=max[2];
 stink=max[3];
 laugh=max[4];

 save_stick();
}

void used_sneeze() {sneeze--; save_stick();}
void used_itch() {itch--; save_stick();}
void used_smoke() {smoke--; save_stick();}
void used_stink() {stink--; save_stick();}
void used_laugh() {laugh--; save_stick();}

void save_stick()
{
 (TRICK_SERVER)->save_stick(ENV(TO)->query_real_name(),get_contents());
}

void load_stick()
{
 int *q;

 q=(TRICK_SERVER)->query_stick_contents(ENV(TO)->query_real_name());
 sneeze=q[0];
 itch=q[1];
 smoke=q[2];
 stink=q[3];
 laugh=q[4];
}

