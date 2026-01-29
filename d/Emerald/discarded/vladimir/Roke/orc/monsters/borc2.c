/* Vladimir 8-09-94 */
inherit "/std/monster";

#include "local.h"
#define TO this_object()
#include <macros.h>
#include <ss_types.h>

create_monster()
{
   set_race_name("orc");
   set_name("tander");
   set_title("the Bouncer");
   set_adj("well-built");
   set_alignment(-100);
   default_config_npc(17);

   add_adj("broad-shouldered");
  set_long("This is one of the two bouncers that work at the bar. " +
          "You feel as though messing with him would be a bad idea.\n");

   call_out("arm_me",1);
   set_skill(SS_DEFENCE, 10);
   set_skill(SS_WEP_KNIFE, 15);
   trig_new("%s 'introduces' %s", "return_introduce");
}

arm_me()
{
   clone_object(ORC+"obj/tknife")->move(TO);
   clone_object(ORC+"obj/bshirt")->move(TO);

   command("wear all");
   command("wield all");
}
public int
return_introduce(string s1, string s2)
{
    object who;
    string *stuff;
    stuff = explode(s2, " as:\n");
    if (sizeof(stuff) != 2)
        return 0;
    stuff = explode(stuff[1], " ");
    who = find_player(lower_case(stuff[0]));
    if (!who)
        who = find_player(lower_case(stuff[1]));
    if (!who)
        return 0;
    if (who->query_met(this_object()))
        return 1;
    stuff[0] = "introduce myself to " + who->query_real_name();
    set_alarm(1.0, 0.0, "command", stuff[0]);
    return 1;
}
