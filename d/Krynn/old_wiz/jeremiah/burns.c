/* 

    Mr. Burns .. (And we all know who he is!)

    Coded ........: 95/09/26
    By ...........: Jeremiah

    Latest update : 95/09/26
    By ...........: Jeremiah

*/
   
#include "/d/Krynn/common/defs.h"
inherit M_FILE

#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>


inherit "/std/act/domove"; /* Include this if you want the creature to move */
inherit "/std/act/action"; /* Include this if you want your creature to act */

/*
 * Prototypes
 */
void return_intro(string who);

   
string ret_str;

void
create_krynn_monster()
{
    set_name("Montgomery Burns");
    add_name(({"human", "montgomery", "burns", "mr. burns",
               "montgomery burns"}));
    set_race_name("human");
    set_title("ruler of springfield");
    set_adj("old");
    add_adj("pale-skinned");
    set_gender(G_MALE);

    set_long("@@long_descr");
   
    set_base_stat(0,10);
    set_base_stat(1,50);
    set_base_stat(2,50);
    set_base_stat(3,180);
    set_base_stat(4,180);
    set_base_stat(5,100);
   set_hp(query_max_hp());
   
   set_skill(SS_DEFENCE, 100);
   set_skill(SS_UNARM_COMBAT,90);

   set_knight_prestige(1000);
   
   set_alignment(-1000);
   
   add_prop(LIVE_I_SEE_DARK, 100);
   add_prop(NPC_I_NO_RUN_AWAY, 1);
   add_prop(CONT_I_VOLUME, 70000);
   add_prop(CONT_I_WEIGHT, 75000);

   add_ask(({"jeremiah", "Jeremiah"}), VBFC_ME("jer_hint"));

   trig_new("%w 'introduces' %s", "react_to_intro");
}

string
long_descr()
{
    ret_str = "This is a very old man.\n";

    return ret_str;
}


jer_hint()
{
   if (P("jeremiah",E(TO)))
   {
      command("say Jeremiah ??, he's right there");
      command("point at jeremiah");
      command("say Ask him yourself!");
   }
   else
   {
      command("say He's not here right now!");
      command("scratch head");
      command("say and I don't really know where he is!");
   }
   return "";
}
 

void
react_to_intro(string who, string garbage)
{
   set_alarm(1.0, 0.0, &return_intro(who));
}


void
return_intro(string who)
{
   who = L(who);
   if (P(who,E(TO)))
   {
      command("introduce myself");
   }
}

