#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"

inherit AM_FILE
inherit "/std/act/action";

#define WEP "/d/Ansalon/balifor/flotsam/obj/weapon/fishing_rod"
#define PLAYER_I_FOUND_F_ROD  "_player_i_found_flotsam_f_rod"


void
create_krynn_monster()
{
   if(!IS_CLONE)
      return;
   
   set_name("dwarf");
   set_adj("gully");
   add_adj("fishing");
   set_short("fishing gully dwarf");
   set_long("Standing dangerously close to the edge of the " +
      "rockpools, this smelly gully dwarf seems to be fishing... " +
      "fairly unsuccessfully. \n");
   
   set_stats(({40,30,70,15,15,15}));
   
   set_alignment(0);
   set_knight_prestige(-2);
   
   set_skill(SS_DEFENCE, 10);
   
   set_act_time(10);
   add_act("emote clumsily casts a line into the rockpools.");
   
   add_ask("relic","say Relish? Mmmmm... yummy!",1);
   add_ask("fishing rod","say Fishing rod catch " +
      "me dinner... me hope anyway.",1);
   add_ask("fish","say Me not stop fishin' 'til me " +
      "catch fishy!",1);
   add_ask("rotten fish","say Mmmm... what I would give " +
      "for a rotten fish!",1);
   set_default_answer("The gully dwarf looks very confused, " +
      "and then replies: Only two... no more than two.\n");
   
   add_prop(NPC_M_NO_ACCEPT_GIVE, 0);
   add_prop(OBJ_M_NO_ATTACK,"Cowering and grovelling " +
      "as only a gully dwarf can do, you cannot bring " +
      "yourself to attack such a pathetic creature. \n");
}

void
arm_me()
{
   seteuid(getuid(this_object()));
   clone_object(WEP)->move(this_object(),1);
   command("wield all");
}


void
return_give_fish()
{
   command("emote looks happily at the rotten fish.");
   command("say Yummy! Dinner! Me thank you...");
   command("think");
   command("drop rod");
   command("say Me no need dat!");
   
   command("smile");
   command("emote waddles off.");
   
   remove_object();
}


void
give_it_back(object ob, object from)
{
   string what,
   who;
   
   what = L(ob->query_short());
   who  = from->query_real_name();
   
   command("confused");
   command("give " + what + " to " + who);
   command("say Me no need for that!");
}


void
enter_inv(object ob, object from)
{
   ::enter_inv(ob, from);
   
   if (ob->id("_flotsam_f_rod_"))
      {
      return;
   }
   
   if(ob->id("_flotsam_r_fish_"))
      {
      set_alarm(1.0, 0.0, &return_give_fish());
      from->add_prop(PLAYER_I_FOUND_F_ROD, 1);
      return;
   }
   
   set_alarm(1.0, 0.0, &give_it_back(ob, from));
   return;
}
