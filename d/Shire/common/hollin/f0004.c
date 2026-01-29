#include "rom.h"

#define TROLLS	4
object *pack;
int possible_get_trolls;

create_rom()
{
    set_short("In a clearing within the boulders");
    set_long(
	"You are in a clearing within the boulders. By the looks on all "+
	"the foot-prints here, you would guess that someone of quite "+
	"small size recently was here. A path winds in the south-east "+
	"direction through the boulders.\n");
    ADD_EXA("path,trail","It winds through boulders scattered around here.");
    ADD_EXA("boulders,rocks",
	"These boulders somehow give you an uneasy feeling. You "+
	"get the impression that if someone were behind them, you'd be "+
	"subject to an awesome ambush.\n");
    ADD_EXA("clearing",
	"You notice a lot of foot-prints here!");
    ADD_EXA("foot-prints,prints",
	"They are increadibly small, perhaps only 6 cm (2 inches) long."+
	"They criss-cross the area, so you would guess that this pack of "+
	"creatures recently was here.");
    add_exit(STAND_DIR+"f0103", "southeast", "@@chk_move");

    possible_get_trolls = 1;

    TO->reset_rom();
}

int
is_alive(object troll)
{
    return troll && living(troll) &&
	   function_exists("create_me", troll)==(STAND_MONSTER + "smalltr");
}

int
is_enemy(object enemy)
{
    return enemy && living(enemy) && enemy->query_race_name()!="troll";
}

object *
pack_members(object to)
{
    return pack;
}

object *
get_small_trolls()
{
    return filter(all_inventory(TO), "is_alive", TO);
}

void
re_enter(object who)
{
    who->move(TO);
    who->command("shout I am back!!");
    who->command("grin");
}

int
chk_move()
{
    int i, r;
    object *ltroll=get_small_trolls();

    if (!ltroll) return 0;
    if (sizeof(ltroll)<1)
	return 0;
    if (member_array(TP, ltroll) >= 0)
    {
	TP->move_living("into the rocks", STAND_DIR+"b_rocks");
	TP->command("trollheal");
   set_alarm(itof(random(10 + 2)), 0.0, TP);
	return 1;
    }

    r = sizeof(ltroll)*100/13;
    if (random(100) >= r)
	return 0;

    i = random(sizeof(ltroll));
    TP->catch_msg(QCTNAME(ltroll[i])+" dodges into you as you try to flee!!\n");
    tell_room(TO,
	QCTNAME(TP)+" tries to leave, but "+QTNAME(ltroll[i])+" dodges into "+
	HIM_HER(TP)+".\n", TP);
    ltroll[i]->command("laugh");
    switch(random(5)) {
	case 0:
	    ltroll[i]->command("shout So you think you can just run away, LOOSER!!!!?????");
	    break;
	case 1:
	    ltroll[i]->command("shout Ha! Gotcha!!!");
	    break;
	case 2:
	    ltroll[i]->command("shout You're gonna die, stupid "+TP->query_race_name()+"!!");
	    break;
	case 3:
	    ltroll[i]->command("emote jumps in happiness, as he managed to stop a wimp!");
	    break;
	case 4:
	    ltroll[i]->command("flip");
	    break;
    }
    return 1;
}

reset_rom()
{
    possible_get_trolls = 1;
    TO->create_small_trolls();
}

create_small_trolls()
{
    int i;

    if (!possible_get_trolls)
       return;

    if (!pack || sizeof(pack)==0)
	pack = allocate(TROLLS);

    for (i=0; i<sizeof(pack); i++)
	if(!pack[i] || !living(pack[i]))
	{
	    pack[i] = clone_object(STAND_MONSTER+"smalltr");
	    pack[i] -> move_living("M", STAND_DIR+"b_rocks");
	    pack[i] -> create_me(i);
	}

    possible_get_trolls = 0;
}

int
filter_troll(object who)
{
    return is_alive(who) && ENV(who) != TO;
}

init_fight()
{
    int i;
    object *new_trolls;

    if (sizeof(get_small_trolls()))
	return;

    new_trolls = filter(pack, "filter_troll", TO);

    if (sizeof(new_trolls))
    {
/*
	dump_array(new_trolls);
*/

	if (sizeof(new_trolls) > 8)
	    tell_room(TO,
		"Suddenly a group of small trolls attack you from behind the rocks!\n");
	else if (sizeof(new_trolls) > 1)
	    tell_room(TO,
		"Suddenly " + LANG_WNUM(sizeof(new_trolls)) +
		" small trolls attacks from behind the rocks!\n");
	else
	    tell_room(TO,
		"Suddenly " + LANG_ASHORT(new_trolls[0]) +
		" attacks you from behind the rocks!\n");
    }

    for (i=0; i<sizeof(new_trolls); i++)
    {
	if (pack[i]->move(TO))
	    continue;
	pack[i]->attack_object(TP);
    }
}

prepare_attack()
{
    set_alarm(0.0, 0.0, create_small_trolls);
}

void
enter_inv(object ob, object from)
{
    if (function_exists("create_monster", ob)==STAND_MONSTER+"smalltr")
    {
	switch(random(10))
	{
	    case 0: ob->command("scream"); break;
	    case 1: ob->command("shout Pecks to kill, folks!"); break;
	    case 2: ob->command("giggle"); break;
	    case 3: ob->command("emote hisses: Yeah! Let's kill!"); break;
	    case 4: ob->command("shout I hate bigfolks! Let's waste'm!"); break;
	    case 5: ob->command("grin"); break;
	    case 6: ob->command("puke"); break;
	    case 7: ob->command("laugh"); ob->command("say He's never gonna hit us! ATTACK!!"); break;
	    case 8: ob->command("shout Agreed!! Let's rock!!"); break;
	    case 9: ob->command("shout Let us trap that mother stinkink animal!"); break;
	}
    }
    else if(living(ob) && !ob->query_npc())
      set_alarm(itof(random(8) + 2), 0.0, init_fight);
    ::enter_inv(ob, from);
}
