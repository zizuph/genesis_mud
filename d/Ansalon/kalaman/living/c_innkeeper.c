/* Navarre July 3rd, fixed grammar for maid act */

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"

inherit AM_FILE

void
create_krynn_monster()
{
   if (!IS_CLONE)
      return;
   
   set_name("barmaid");
   set_short("attractive barmaid");
   set_long("This attractive barmaid works the tavern serving the merchants and travellers, " +
      "and obviously enjoys the attention her good looks bring.\nShe looks very attractive.\n");

   set_gender(1);   
   set_act_time(5);
   add_act("smile sweet");
   add_act("say Can I get you a drink sweety?");
   add_act("say Undead from Dargaard Keep have been terrorising the merchants lately...");
   add_act("say I once met this handsome half-elven warrior... I was his sweetheart, " +
      "he was my darling Seawolf.");
   set_stats(({40,40,40,40,40,40}));
   set_hp(10000);

    add_prop(CONT_I_HEIGHT, 185);
    add_prop(CONT_I_WEIGHT, 49000);
    add_prop(NPC_I_NO_LOOKS, 1);
}

#include "maiden_funcs.h"   

void
init_living()
{
    if(P("ansalon_sword_object",TP))
        set_alarm(1.0, 0.0, "greet_func1",TP);
    if(TP->query_knight_level())
        set_alarm(0.5, 0.0, "knight_greet",TP);
    if(TP->query_race_name() == "hobbit")
        set_alarm(1.0,0.0, "hobbit_greet",TP);
    ::init_living();
}
