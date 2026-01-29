/* Vladimir 8-09-94 */
inherit "/std/monster";

#include "local.h"
#define TO this_object()
#include <macros.h>
#include <ss_types.h>

 create_monster()
{
 set_race_name("orc");
   set_name("jazmine");
   set_title("the Smelly");
 set_adj("smelly");
 set_alignment(-100);
 default_config_npc(5);

   add_adj("wretched");
 set_long("You seem to have disturbed this orc as "+
          "he is about to fall asleep. He does not "+
          "look happy about it.\n");

 call_out("arm_me",1);
 set_skill(SS_DEFENCE, 4);
 set_skill(SS_WEP_KNIFE, 4);
trig_new("%s 'introduces' %s", "return_introduce"); 
 }

arm_me()
{
 clone_object(ORC+"obj/tknife2")->move(TO);
clone_object(ORC+"obj/sleepshirt")->move(TO);

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
