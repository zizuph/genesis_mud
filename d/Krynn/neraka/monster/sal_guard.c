/* Guard at Salamic, an Hobgoblin, made by Nick*/

#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <ss_types.h>
#include QUESTH

inherit M_FILE

void
create_krynn_monster()
{
    int i;
    
    set_name("hobgoblin");
    add_name("sal_guard");
    set_long("A large hobgoblin, probably here to guard the prisoners.\n");
    set_race_name("hobgoblin");
    set_adj("large");
    
    add_act("say Get lost!");
    add_act("say There is nothing for you to do here!");
    set_act_time(15);
    
    set_gender(0); /* male = 0, female = 1, other = 2 */
    
    for (i = 0; i < 6; i++)
      set_base_stat(i, 25 + random(5));
    set_skill(SS_BLIND_COMBAT, 31 + random(20));
    set_skill(SS_AWARENESS, 43 + random(20));
    set_skill(SS_WEP_CLUB, 30 + random(15));
    add_prop(LIVE_I_SEE_DARK,1);

    set_alignment(-170);
    set_knight_prestige(500);
    
    set_all_attack_unarmed(20, 15);
    set_all_hitloc_unarmed(12);
    
    NEVERKNOWN;
    set_alarm(1.0,0.0,"equip_me");
    
    trig_new("%s 'arrives' 'in' 'a' 'puff' 'of' %s", "react_appear");

}

void
hello(object ob) 
{
    if (ob && present("chef_apron", ob))
      command("say Hi chef, feeding time heh?");
    else if (ob)
      command("say Who are you?");
}

void
init_living()
{
    if (TP && living(TP) && !TP->query_npc() && CAN_SEE(TO,TP))
      {
	  hello(TP);
	  set_alarm(5.0,0.0,"try_throw_out", TP);
      }
}

int
react_appear(string str1, string str2)
{
    object who = find_player(L(str1));
    if (E(who) == E(TO))
      {
	  set_this_player(who);
	  init_living();
      }
}

void
throw_out(object ob)
{
    tell_room(E(TO), "The hobgoblin points at " + QCTNAME(ob) + " and says: " +
	      "LEAVE!!!\nYou are not allowed to be with the " +
	      "prisoners!!!!!!!!\n");
    tell_object(ob, "You feel you have to do like it demands.\n");
    tell_room(E(ob), QCTNAME(ob) + " feels obliged to leave.\n", ob);
    ob->command("north");
}

void
try_throw_out(object ob)
{
    if (!present(ob, environment(TO)))
      return;
    if (!present("chef_apron", ob))
      throw_out(ob);
}

int
second_life(object killer)
{
    killer->add_prop(PLAYER_I_HELP_SALAMIC,
		     killer->query_prop(PLAYER_I_HELP_SALAMIC) | 4);
    return 0;
}

void
equip_me()
{
    seteuid(getuid(TO));
    clone_object(OBJ + "gob_club")->move(TO);
}

void
attacked_by(object ob)
{
    ::attacked_by(ob);
    command("wield all");
}
