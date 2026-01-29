/* this is the fulte of the satyrs */

inherit "std/object";
#include <macros.h>
#include <stdproperties.h>
 
void
create_object()
{
    set_name("flute");
    set_adj("reed");
    set_short("reed flute");
    set_long("It is a small flute made with six reeds of varying lengths, "+
             "banded together from longest to shortest with a gold brace. "+
             "It recites an enchanting tune when played. "+
             "You think its probably worth a little with the gold on it.\n");
 
    add_prop(OBJ_I_WEIGHT, 600);
    add_prop(OBJ_I_VOLUME, 500);
    add_prop(OBJ_I_VALUE, 75); /* worth 75 cc */
}

void init() {

   ::init();
   add_action("play","play");
}

int play(string Parms) {
   object Tobj = this_object();
   object TP   = this_player();
   string *Parm;
   int OK,i;

   /* flute must be in player inventory */
   if (!(present(Tobj,TP))) return 0;  

   /* player must specify to play the flute: "play flute" */
   if (!(Parms)) return 0;                
   Parm=explode(Parms," ");
   OK=0;
   for (i=0; i<sizeof(Parm); i++) if (Parm[i]=="flute") OK = 1;
   if (!(OK)) return 0;

   write("You play an enchanting tune on the reed flute.\n");
   tell_room(QCNAME(this_player())+" plays an enchanting tune on a reed flute.\n");

   return 1;
}

 
