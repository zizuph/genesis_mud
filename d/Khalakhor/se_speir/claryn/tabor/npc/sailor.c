/*
 * marinagh.c
 *
 * anxious sailor on the pier of Tabor Sogh.
 *
 * Khail - April 4/97
 * Zima  - March 15/98
 * Zima  - June 13/98 - sailor is now a recipient of a letter/postman tour
 * Tapakah - 07/21 - refactored
 */

#pragma strict_types
 
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Khalakhor/sys/defs.h"
#include "/d/Khalakhor/sys/paths.h"
#include "npc.h"
 
inherit BASE_NPC;

void
arm_me ()
{
  armours = ({ COMMON+"arm/shirt_cloth",
               COMMON+"arm/belt",
               ARM+"pants",
               ARM+"eyepatch" });
  weapons = ({ COMMON+"wep/dirk" });
  ::arm_me();
}
 
/*
 * Function name: create_khalakhor_human
 * Description  : Turns this object into a landlord.
 * Arguments    : n/a
 * Returns      : n/a
 */
void
create_khalakhor_human ()
{
  explicit_name = "marinagh";
  ::create_khalakhor_human();
  add_name(({"sailor","seaman","man"}));
  set_adj("stout");
  add_adj("black-bearded");
  set_long(
           "From his dress, you can see that this man is obviously a sailor. "+
           "His clothes look a little damp and he seems very anxious about "+
           "something.\n");
 
  default_config_npc(60);
  set_skill(SS_AWARENESS, 75);
  set_skill(SS_UNARM_COMBAT, 40);
  set_skill(SS_DEFENCE, 40);
  set_skill(SS_PARRY,   40);
  set_skill(SS_WEP_KNIFE, 50);
 
  set_act_time(60);
  add_act("emote gazes out over the horizon of the sea.");
  add_act("emote rubs his bearded chin bewilderedly.");
  add_act("emote wrings his hands nervously.");
  add_act("emote glances at a speck on the horizon expectantly, then "+
          "sighs dejectedly.");
  add_act("emote scans the horizon of the sea for anything afloat.");
  add_act("say She naught ne'er gone out in these winds.");
  add_act("say She ought been back days ago.");
  add_act("say Whar' could she be?");
  add_act("say Winds preserve her! Bring her home!");
 
  set_cact_time(30);
  add_cact("say I'll hang yer hide from the main mast, ye yeller-bellied "+
           "eel!");
  add_cact("say I'll feed ye to the fishies, ye low-life octipus!");
  add_cact("say Ye're shark bait, ye stinking rogue!");
  add_cact("emote blasts out a hearty triumphant laugh!");
  add_cact("emote I'll drag yer carcass 'ahind me ship!");
  add_cact("emote I'll drop anchor wi' yer carcass atied to it!");
 
  set_default_answer("I 'taint got time for such nonsense, matey! "+
                     "Now run along!");
  add_ask(({"ship","bonnie blue lass","Bonnie Blue Lass","boat"}),
          "say Aye, the Bonnie Blue Lass, queen 'o the coast of Tabor Sogh. "+
          "She be like me mathair, matey.",1);
  add_ask(({"ships","boats","other ships","other boats","passage"}),
          "say Aye, 'taint a ship landed here in months, matey, 'cept the "+
          "Bonnie Blue Lass.",1);
  add_ask(({"anxious","why","why anxious","where ship","where is ship",
            "where bonnie blue lass","where Bonnie Blue Lass",
            "where boat","when"}),
          "say Mi boats a missin', matey, and I'm beginnin' ta worry "+
          "about 'er.",1);
  add_ask(({"job","tour","quest","task"}),
          "say 'Taint nothin' I ha' fer ye to do matey. Look elsewhere.",1);
 
  set_alignment(200);
  set_exp_factor(100);
  set_size_descs("tall", "of normal width");
}
 
void
hook_return_intro_new (string str)
{
  command("say G'day thar, matey!");
  command("say Me be "+query_name()+", "+query_title()+"!");
  command("say May the good winds 'ere blow yer way!");
}
