inherit "/std/monster.c";
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Roke/common/defs.h"


void
create_monster()
{
   set_name("malanze");
   add_name("sergeant");
   set_title(", Drill Sergeant of Cove's Law Enforcement");
   set_race_name("human");
   set_long("This well built human is the sergeant of Cove's law enforcement\n"
      + " department.\n");
   set_adj("musclebound");
   add_adj("sergeant");
   
   default_config_npc(135);
   
   set_hp(10000);
   
   set_skill(SS_DEFENCE, 95);
   set_skill(SS_WEP_AXE, 95);
   set_skill(SS_BLIND_COMBAT, 90);
   set_skill(SS_PARRY, 95);
   
   add_act("emote studies you.");
   add_act("emote stares at you.");
   add_act("say Recruitment of possible officers is my job.");
   
   
   set_act_time(20);
   set_chat_time(50);
   
   set_alignment(500);
   
   
   
   if (IS_CLONE)
      call_out("arm_me", 1);
   
   
 trig_new("%s 'introduces' %s", "return_introduce");
}

void
arm_me()
{
   seteuid(geteuid(this_object()));
   
   clone_object(KARGS + "obj/karg_platemail")->move(TO);
   clone_object(KARGS + "obj/karg_ghelm")->move(TO);
   clone_object("/d/Roke/vladimir/obj/weapons/bataxe")->move(TO);
   clone_object(KARGS + "obj/karg_greaves")->move(TO);
   clone_object(KARGS + "obj/karg_bracers")->move(TO);
   
   command("wear all");
   command("wield all");
   seteuid(getuid(TO));
   
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
