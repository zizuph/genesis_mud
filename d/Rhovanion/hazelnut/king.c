


inherit "/std/monster";

#include <macros.h>
#include <ss_types.h>
#include <language.h>
#include <stdproperties.h>
#define THIS this_object()


equip_me(){
object axe;
object helmet;
object chainmail;
string type;
seteuid(getuid(THIS));
axe=clone_object("/d/Avenir/farlong/obj/axe.c")->move(this_object());
command("wield all");
helmet=clone_object("/d/Avenir/farlong/obj/ddhelm.c")->move(this_object());
chainmail=clone_object("/d/Avenir/farlong/obj/ddchain.c")->move(this_object());
command("wear all");
}
create_monster() {
set_name("king");
set_adj("dwarf");
add_adj("dark");
set_short("Dark dwarf");
	set_race_name("dwarf");

call_out("equip_me", 1);
set_alignment(-845);
   set_long(
	"This is the king of the Dark dwarves.  He looks to be in excellent\n"+
	"shape.  He seems a little crazed about the eyes, as though something"+
	"\n haunts his thoughts.\n");
   add_prop(CONT_I_WEIGHT, 300*1000);
   add_prop(CONT_I_HEIGHT, 400);
set_stats(({107,76,108,49,47,110}));
set_hp(10000);


   set_skill(SS_UNARM_COMBAT, 40);
set_skill(SS_WEP_AXE, 120);
set_skill(SS_DEFENCE, 95);
   set_skill(SS_PARRY,        40);
   set_pick_up(43);
   set_attack_chance(87);


   set_act_time(6);
   add_act("smirk");
   add_act("finger all");
   add_act(({"fume", "stomp"}));

   set_cact_time(7);
    add_cact("scream");
   add_cact("fume");


}


