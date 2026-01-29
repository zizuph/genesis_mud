/* 
 * /d/Kalad/common/wild/pass/wep/sword_of_solara.c
 * Purpose    : A magical sword; reward for deep dragon quest
 * Located    : The Deep Dragon
 * Created By : Antharanos  ??.??.??
 * Modified By: Rico 15.Mar.97 
 */ 

inherit "/d/Kalad/std/weapon";

#include "/d/Kalad/defs.h"

int uses = 1;

create_weapon()
{
    ::create_weapon();

    set_name("sword");
    add_name("sword of solara");
    set_adj("pure");
    add_adj("snow-white");
    set_long("@@my_long");

    set_hit(45);
    set_pen(45);
    set_hands(W_BOTH);
    set_wt(W_SWORD);
    set_dt(W_SLASH | W_IMPALE);
    set_wf(TO);

    KVWEP(300);
    KWWEP(500);
    KVOLUME;
    add_prop(OBJ_I_IS_MAGIC_WEAPON,1);
    add_prop(OBJ_S_WIZINFO,"This is the sword blessed by the Sun Goddess "+
      "Solara. It can only be wielded by someone with an alignment of "+
      "at least 1000. The weapon, if wielded, grants its wielder the ability "+
      "to see into one level of darkness. This ability vanishes if the "+
      "weapon is not wielded. The sword also has the ability to grant "+
      "its wielder the ability to see into one level of invisibility. This "+
      "ability only lasts for about 1 minute in RL (20 minutes Kalad time). "+
      "Also, the weapon can only grant this ability a limited number of "+
      "times.\n");
    add_prop(MAGIC_AM_ID_INFO,({"The sword is magically enchanted.\n",5,
	"The sword possess a great power enabling its wielder to survive the fiercest of attacks.\n",25,
	"The sword can only be wielded by one of pure intent. All others "+
	"will fail at the task.\n",55}));
    add_prop(MAGIC_AM_MAGIC, ({ 75, "enchantment" }));
    add_prop(OBJ_M_NO_BUY,1);
}
string
my_long()
{
    string empty_desc;
    if(uses < 1)
	empty_desc = "A faint thrumming emanates from the blade.";
    else
	empty_desc = "A strong pulse emanates from the blade.";
    return("A sword that seems to be fashioned out of light itself, so "+
      "pure is its countenance. " + empty_desc + "\n");
}
mixed
wield(object what)
{
    if(TP->query_alignment() > 1000)
    {
	write("With great satisfaction, you grasp the sword.\n");
	say(QCTNAME(TP) + " with great satisfaction, grasps the pure snow-white sword.\n");
	write("Instinctively, you realize that you now have the ability to "+
	  "see in the dark.\n");
	say(QCTNAME(TP) + "'s eyes glow a strange red in color.\n");
	TP->add_prop(LIVE_I_SEE_DARK,1);
	set_alarm(10.0,0.0,"sword");
	return 0;
    }
    write("You attempt to wield the blade but instead are engulfed in a "+
      "energy-draining white ball of light!\n");
    write("Your very soul seems to drain away...\n");
    say(QCTNAME(TP) + " foolishly attempted to wield the pure snow-white sword and as a result, is engulfed in an energy-draining white ball of light!\n");
    say(QCTNAME(TP) + "'s very soul seems to drain away...\n");
    TP->heal_hp(-500);
    if(TP->query_hp() <= 0)
	TP->do_die(TO);
    uses = uses + 1;
    return "A portion of your soul was drained away!\n";
}
sword(object ob)
{
    write("The pure snow-white sword urges you to crush all those of black hearts.\n");
    say(QCTNAME(TP) + " gets a slightly fanatic look upon " + TP->query_possessive() + " face.\n");
    TP->command("say I swear by Solara, that evil shall never triumph!");
    set_alarm(10.0,0.0,"fortify");
    return 1;
}
mixed
unwield(object what)
{
    write("The power of seeing in the darkness leaves you.\n");
    say(QCTNAME(TP) + "'s eyes seem to lose their strange quality.\n");
    TP->add_prop(LIVE_I_SEE_DARK,0);
    return 0;
}
init()
{
    ::init();
    add_action("command","command");
}
fortify()
{
    if(!query_wielded(TO))
    {
	write("The pure snow-white sword urges you to wield it.\n");
	return 1;
    }
    write("The mere presence of the pure snow-white sword gives you "+
      "confidence.\n");
    say(QCTNAME(TP) + " looks completely invincible.\n");
    TP->command("smile conf");
    return 1;
}
command(s)
{
    if(!query_wielded(TO))
    {
	write("You must wield the pure snow-white sword first.\n");
	return "You feel the need to wield it";
    }
    NF(query_verb() + " what?\n");
    if(!s)
	return 0;
    if(query_verb() == "command")
    {
	if(s != "aralos")
	    return 0;
    }
    else
    if(s != "aralos")
	return 0;
    NF("You call upon the power of the pure snow-white sword, but nothing occurs.\n");
    if(uses < 1)
	return 0;
    write("You call upon the power of the pure snow-white sword.\n");
    say(QCTNAME(TP) + " concentrates deeply.\n");
    uses = uses - 1;
    see_invis();
    return 1;
}
see_invis()
{
    write("You realize that you can now see invisible objects.\n");
    TP->add_prop(LIVE_I_SEE_INVIS,1);
    set_alarm(60.0,0.0,"no_see_invis");
}
no_see_invis()
{
    write("Your ability to see invisible objects fades away.\n");
    TP->add_prop(LIVE_I_SEE_INVIS,0);
}
