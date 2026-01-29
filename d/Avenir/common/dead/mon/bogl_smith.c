// file name: /d/Avenir/common/dead/mon/bogl.c
// creator(s): Lilith June 2021
// last update:
// purpose: smithy for the BOGL encampment
// note:   
// bug(s):
// to-do:

#pragma strict_types

inherit "/std/monster";
#include "../dead.h"
#include "/d/Avenir/include/basic.h"
#define BOBJ "/d/Avenir/common/bazaar/Obj/"
#define ZOBJ "/d/Avenir/common/city/zigg/obj/"
void
equip_me()
{
	
    seteuid(getuid());

    clone_object(ZOBJ+"soap")->move(TO,1);
    clone_object(BOBJ+"worn/loincloth")->move(TO, 1);
    command("wear all");	
}

string 
my_long()
{
	string str;
    str = CAP(HE(TO)) +" is a "+query_adj()	+" "+ query_gender_string() 
	    + " goblin who seems to be "
	    + query_exp_title() +" in size.\n";
    str += CAP(HE(TO)) +" is a proud member of B.O.G.L. and the blacksmith "
	    +"of this tribe.\n"
		+ CAP(HIS(TO)) +" biceps are huge and "+ HIS(TO) +" back is strong.\n"
        + CAP(HE(TO)) +" appears to be remarkably mild-mannered for a goblin.\n"
		+ CAP(HE(TO)) +" seems to take pride in "+ HIS(TO) +" horns, "
		+"which are steel-tipped.\n"
		+ CAP(HE(TO)) +" has a smile on "+HIS(TO)+" face, showing clean fangs.\n"
		+ CAP(HIS(TO)) +" eyes are dark and formidable.\n"
		+ CAP(HIS(TO)) +" skin is light brown with dark creases.\n";
    return str;
}	
	
public void
create_monster(void)
{

    string str = one_of_list(({
	"thoughtful", "hard-working", "sweaty", "red-faced", "dusty"}));

    set_adj(str);
	set_name("half-thor");
    add_name(({"bogl","smith", "blacksmith", "_Avenir_BOGL_goblin"}));
    set_race_name("goblin"); 
	set_gender(G_MALE);
    set_short(str +" "+ query_gender_string() +" goblin");
    set_pshort(str + " goblins");
    set_long(my_long);
    //Thick skinned little sucker.
    set_all_hitloc_unarmed(25);
    default_config_npc(random(240) + 80);
	set_skill(SS_DEFENCE, 125);
    set_skill(SS_UNARM_COMBAT, 125);
	set_act_time(60);
	add_act("emote pumps the bellows and watches the coals flare.");
	add_act("emote stirs the coals a little bit.");
	add_act("puts some lumps of metal in the crucible.");
	add_act("emote hums a little melody.");
	add_act("emote sweeps the floor.");
	add_act("emote pounds on a piece of red-hot metal with a hammer.");
	add_act("emote strokes a fang thoughtfully.");
	add_act("emote searches through the materials stacked against the "
	    +"far wall.\n");
	add_act("emote eats a packet of fish.");
	add_act("sigh content");
	add_act("boggle");
	add_act("nod under");
    set_chat_time(60 + random(30));
	add_chat("It like my job. I get paid to pound on things.");
	add_chat("I like it here.");
	add_chat("I'm hungry for some fish.");
	add_chat("I feel peaceful when I am at my forge.");
	add_chat("This is a good home for us.");
	add_chat("I fix things so they don't break.");
	add_chat("We serve Mascarvin and the Hegemon.");
	add_chat("I don't understand much but I don't need to.");
	set_default_answer(VBFC_ME("what_me"));
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(OBJ_M_HAS_MONEY, 500);
	add_prop(CONT_I_HEIGHT, 100);
	add_prop(CONT_I_WEIGHT, 90000);


}

string
what_me()
{
    command("say All I can talk about is fixing weapons.");
	return "";
}
