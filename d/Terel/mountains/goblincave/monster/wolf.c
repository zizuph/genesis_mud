/*
 * Modified Jan 2021 by Lucius - Modernized
 */
#include "/d/Terel/include/Terel.h"
inherit STDCREATURE;

inherit "/std/combat/unarmed";
inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/attack";

#include <formulas.h>
#include <wa_types.h>
#include <ss_types.h>

#define A_BITE  0
#define A_LCLAW 1
#define A_RCLAW 2

#define H_HEAD 0
#define H_BODY 1

private string *adj1 = ({
  "black-haired","shaggy","mangy", "dark",
  "one-earred","scarred","tawny", "brown-haired",
  "long-haired", "short-marked", "wiry","dappled",
  "grey","tan","brown","black"
});
private string *adj2 = ({
  "massive", "angry", "powerful", "thin", "agile",
  "lanky","tall","enormous","stout", "confident",
  "huge","towering","vicious","ferocious","graceful",
  "sinuous"
});

mixed benice();

/*
 * Function name: create_creature
 * Description:   Create the creature.
 */
public void
create_creature()
{
    ::create_creature();
    set_name("animal");
    add_name("_goblin_lord_wolf");
    set_pshort("enormous grey wolves");
    set_long("This wolf appears to be working for or with " +
      "the goblins within the cave.\n");
    set_adj(one_of_list(adj1));
    set_adj(one_of_list(adj2));
    set_race_name("wolf");
    set_alignment(-40 - random(20));

    set_stats(({random(30)+80,random(30)+80, 120, 10, 13, 80}));
    ADDSKIN;
    //    add_leftover(MOUNTAIN_DIR + "goblincave/obj/wolf_skin","skin", 1, "", 0, 1);

    set_attack_unarmed(A_BITE,  30, 30, W_IMPALE, 40, "jaws");
    set_attack_unarmed(A_LCLAW, 30, 30, W_SLASH,  30, "left claw");
    set_attack_unarmed(A_RCLAW, 30, 30, W_IMPALE, 30, "right claw");

    set_hitloc_unarmed(H_HEAD, ({ -15, -25, -20, -20 }), 20, "head");
    set_hitloc_unarmed(H_BODY, ({  10,  15,  30,  20 }), 80, "body");

    set_aggressive("@@benice@@");
    SET_MAX_HP;
    set_gender(NEUTER);
    set_skill(SS_UNARM_COMBAT, 50);
    set_skill(SS_DEFENCE, 40);
    BRAVE;
    add_prop(LIVE_I_SEE_INVIS,50);
    add_prop(LIVE_I_SEE_DARK,100);
    add_prop(NPC_I_NO_FEAR, 1); 

    set_act_time(5 + random(20)); 
    add_act("growl");
    add_act("emote sniffs the air.");
    add_act("emote scratches itself with its hind leg.");
    add_act("emote howls loudly.");
}

int
special_attack(object enemy)
{
    if (random(10) < 4)
    {
	object me = TO;
	int intox = enemy->query_intoxicated();
	int hurt = F_PENMOD(30 + intox/4, 30 + intox/4);
	mixed *hitresult = enemy->hit_me(hurt, W_IMPALE, me, -1);
	string how = "unharmed";

	if (hitresult[0] > 0)
	    how = "slightly hurt";
	if (hitresult[0] > 20)
	    how = "rather hurt";
	if (hitresult[0] > 50)
	    how = "crushed";
	if (hitresult[0] > 100)
	    how = "devastated";

	tell_watcher(QCTNAME(me) + " mauls " + QTNAME(enemy) + ".\n", enemy); 
	enemy->catch_msg(QCTNAME(me) + " mauls you!\n");
	enemy->catch_msg("You feel " + how + ".\n");

	return 1;
    }

    return 0;
}

mixed
benice()
{
    if (TP->query_race_name() == "goblin")
	return 0;

    /* Invisible players doesn't mean they dont smell */
    if (TP->query_prop(OBJ_I_INVIS))
    {
	write("The wolf raises his snout high in the air " +
	  "sniffing in your direction.\n");
	say("The wolf raises his snout as if smelling something.\n", TP);
	return 1;
    }

    /* Too small, throw em back!  */
    if (TP->query_average_stat() <= 90)
	return 0;

    return 1; 
}
