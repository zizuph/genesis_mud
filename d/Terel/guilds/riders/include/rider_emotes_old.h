/*
 * Rider Guild Emotes
 * 
 * Tomas/Jaypeg -- April 2000
 * 
 */

#pragma save_binary

#include <wa_types.h>
#include <composite.h>
#include <cmdparse.h>
#include <macros.h>
#include "guild.h"
#include "/sys/stdproperties.h"
#include <filter_funs.h>
#include <formulas.h>

#define SOULDESC(x)     (this_player()->add_prop(LIVE_S_SOULEXTRA, x))
// #define IS_MEMBER(o)    ((o)->query_prop(RIDER_GUILD_EMBLEM_ID))

#define TP         this_player()
#define TO         this_object()
#define NF(mesg)   notify_fail(mesg)

/* Gender specific definitions, because Jaypeg is lazy! */
#define HE_SHE(o)  (o)->query_pronoun()
#define HIS_HER(o) (o)->query_possessive()
#define HIM_HER(o) (o)->query_objective()

/* Some filter functions */
private int male (object ob) { return ob->query_gender() == G_MALE; }
private int female (object ob) { return ob->query_gender() == G_FEMALE; }




                     /*    E M O T I O N S    */

//          emotes 'A - J'




int
rol_comb(string str)
{
   if(!present("horse",ENV(TP)))
   {
       write("You need a horse before you can comb one!\n");
       return 1;
   }
   write("Using a stiff metal comb, you give the horse " +
      "a good brushing.\n");
   allbb(" brushes the horses coat with a stiff metal brush.\n");
   return 1;
}


int
rol_hair(string str)
{
    write("You run your fingers through your hair, freeing the grit "+
          "you've collected from long hours of riding.\n");
    all(" runs "+ HIS_HER(TP) +" fingers through "+ HIS_HER(TP) +
        " hair, dirty from the long miles on horseback.\n");
    return 1;
}







//          emotes 'K - T'



int
rol_pat(string str)
{
   if(!present("horse",ENV(TP)))
   {
       write("You need a horse before you can pat one!\n");
       return 1;
   }
   write("You pat the horse lovingly as to comfort it.\n");
   allbb(" pats the horse attempting to comfort it.\n");
   return 1;
}


int
rol_reins(string str)
{
   if(!present("horse",ENV(TP)))
   {
       write("You need a horse first.\n");
       return 1;
   }
   if(!TP->query_prop("_live_o_steed"))
   {
       write("Mount up first!\n");
       return 1;
   }

   write("You pull up sharply on the reins attempting " +
          "to halt the horse.\n");
   allbb(" reins in the horse slowing it down.\n");
   return 1;
}



int
rol_seat(string str)
{
   if(!present("horse",ENV(TP)))
   {
       write("You need a horse first!\n");
       return 1;
   }
   write("You squirm in the saddle attempting to find a " +
      "more comfortable position.\n");
   allbb(" squirms in the saddle attempting to find a more " +
      "comfortable position.\n");
   return 1;
}


int
rol_shoes(string str)
{
   if(!present("horse",ENV(TP)))
   {
       write("You need a horse first!\n");
       return 1;
   }
   write("You check the horse's hooves for loose shoes.\n");
   allbb(" checks the horse's hooves for loose shoes.\n");
   return 1;
}


int
rol_stroke(string str)
{
   if(!present("horse",ENV(TP)))
   {
       write("You need a horse first!\n");
       return 1;
   }
   write("You stroke the horses mane lovingly.\n");
   allbb(" reaches down and strokes the horses mane.\n");
   return 1;
}


//          emotes 'U - Z'



int
rol_victory(string str)
{
   if(!present("corpse",ENV(TP)))
   {
       write("You need a corpse first!\n");
       return 1;
   }
   TP->command("smile victoriously");
   write("You loom over the body of your enemy, smiling victoriously.\n");
   allbb(" looms over the body of "+ HIS_HER(TP) +" enemy, smiling victoriously.\n");
   return 1;
}
