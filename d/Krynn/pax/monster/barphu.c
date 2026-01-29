/*
   barphu.c
   --------

   Coded ........: 95/01/15
   By ...........: Jeremiah
 
   Latest update : 95/07/28
   By ...........: Jeremiah

   This gully dwarf has the rag doll, thats needed to solve the quest
   to free the prisoners. If the player kills the gully dwarf, there
   will be blood on the doll, and it will be useless in solving the
   quest. 

*/


#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"
inherit M_FILE

inherit "/std/act/domove"; /* allows Barphu to move */ 
inherit "/std/act/action"; /* allows Barphu to act  */

#define I_FOUND_DOLL  "_i_found_pax_doll"

int    ladder_learned = 0; /* 1 = Barphu has learned to use ladder */
string player_w_ladder;

object doll;

void
create_krynn_monster()
{
   int i;

   set_name("barphu");
   add_name("gully");
   add_name("gully dwarf");
   set_pname("dwarves");
   set_race_name("dwarf");
   set_long("He is a small, smelly and rather ugly looking gully " +
            "dwarf. His clothes looks very dirty and ragged. " +
            "He has a look of total confusion on his face.\n");
   set_adj("dirty");
   add_adj("gully");
   set_short("dirty gully dwarf");

   for (i = 0; i < 6; i++)
      set_base_stat(i,10 + random(10));

   set_all_attack_unarmed(10, 10);
   set_all_hitloc_unarmed(10);
   set_alignment(50);
   set_knight_prestige(-2);
   set_gender(G_MALE);

   set_default_answer("The gully dwarf says: Me not know that!.\n");

   add_ask(({"lamp", "oil lamp"}), VBFC_ME("lamp_hint"));

   set_alarm(30.0,45.0,"do_gully_actions");

   trig_new("%w 'gives' 'you' 'a' 'ladder.\n' %s", "react_to_give_ladder");

   trig_new("%w 'sets' 'the' 'ladder' 'against' 'the' 'wall.\n' %s",
            "react_to_place_ladder");
   trig_new("%w 'puts' 'the' 'ladder' 'against' 'the' 'wall.\n' %s",
            "react_to_place_ladder");
   trig_new("%w 'places' 'the' 'ladder' 'against' 'the' 'wall.\n' %s",
            "react_to_place_ladder");

   trig_new("%w 'climbs' 'the' 'ladder.\n' %s", "react_to_climb_up");
   trig_new("%w 'climbs' 'down' 'from' 'the' 'ladder.\n' %s",
            "react_to_climb_down");

   add_prop(NPC_I_NO_RUN_AWAY, 1);
   add_prop(NPC_M_NO_ACCEPT_GIVE,0);
   seq_new("do_things");
   seq_addfirst("do_things","@@get_doll");

   seteuid(getuid(TO));
}


void
get_doll()
{
   doll = clone_object(POBJ + "rag_doll");
   doll->move(TO);
}


void
do_die(object killer)
{
   if (query_hp() != 0)
       return;

   if(objectp(doll))
   {
      if(present(doll,TO))
         doll->set_blood_stains();
   }

   ::do_die(killer);
}


lamp_hint()
{
   command("say Boss tell me to fill lamps. Me not remember how I get up " +
           "there.");
   command("emote points at the oil lamp on the wall.");
   command("say Me need thing that makes me big. Me not know where it is.");
   
   return "";
}


void
react_to_give_ladder(string who)
{
   set_alarm(2.0, 0.0, "return_give_ladder", who);
}


void
return_give_ladder(string who)
{
   who = L(who);

   if (ladder_learned)
   {
      command("say Thank you. Me have thing already.");
      command("give ladder to " + who);
   }
   else
   {
      command("emote looks completely confused.");
      command("emote swings the ladder around dangerously.");
      command("emote hits himself over the head with the ladder.");
      command("drop ladder");
      command("say Me not know what to do with that.");
   }
}


void 
react_to_place_ladder(string who)
{
   set_alarm(2.0, 0.0, "return_place_ladder", who);
}


void 
return_place_ladder(string who)
{
   who = L(who);

   command("smile " + who);
   command("emote looks with interest at the ladder.");
}


void
react_to_climb_up(string who)
{
   set_alarm(2.0, 0.0, "return_climb_up", who);
}


void
return_climb_up(string who)
{
   player_w_ladder = who;

   who = L(who);
   command("emote claps his little hands joyfully together.");
   command("admire " + who);
}


void
react_to_climb_down(string who)
{
   set_alarm(2.0, 0.0, "return_climb_down", who);
}


void
remove_barphu()
{
   tell_room(E(TO), "The dirty gully dwarf runs happily off.\n", TO);
   remove_object();
}   


void
return_climb_down(string who)
{
   who = L(who);
   command("cheer");
   command("say Me can do that! Me remember now!");
   command("get ladder");
   command("say You very nice!. Me give you nice thing!");
   command("give doll to " + who); 
   command("drop doll");
   (P(who,E(TO)))->add_prop(I_FOUND_DOLL, 1);
   command("hug " + who);
   ladder_learned = 1;
   set_alarm(2.0, 0.0, "remove_barphu");
}


void
do_gully_actions()
{
   if(!ladder_learned)
   {
      switch(random(4))
      {
         case 0 : command("sigh");
                  break;
         case 1 : command("emote stares with disbelief at the oil lamp " +
                          "on the wall.");
                  break;
         case 2 : command("confused");
                  break;
         case 3 : command("emote peers quizzically at the oil lamp on " +
                          "the wall.");
                  break;
      }
   }
}
