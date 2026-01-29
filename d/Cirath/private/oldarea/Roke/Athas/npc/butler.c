inherit "/std/monster";
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <const.h>
#include "/d/Roke/common/defs.h"

string	riddle,
	answer;
static int current;


#define RIDDLEFILE "/d/Roke/Athas/npc/riddles"

void read_riddle()
{
  string apa;
  int i;

  apa = read_file(RIDDLEFILE,1,1);
  
  current = atoi(apa);
  current = random(current);

  for(i=2;i<current+3;i++)
    {
      riddle = read_file(RIDDLEFILE,i,i);
      sscanf(riddle,"%s#%s$",riddle,answer);
    }
}

void reward_player(object ob);

void
create_monster()
{
    if (!IS_CLONE)
        return;
    seteuid(getuid());

    set_name("butler");
    set_race_name("human");
    set_living_name("drabakk");
    set_long("@@long_desc");
	add_adj("grummy");
	add_adj("old");

    set_alignment(-10);      
    set_gender(G_MALE);

    add_prop(CONT_I_WEIGHT, 47000);
    add_prop(CONT_I_HEIGHT, 142);
    add_prop(NPC_M_NO_ACCEPT_GIVE, 1);

    set_stats(({ 30, 30, 30, 30, 30, 30 }));
    heal_hp(10000);

    set_skill(SS_DEFENCE, 30);
    set_skill(SS_UNARM_COMBAT, 30);

    add_ask(({ "pass", "about passing", "passing" }), VBFC_ME("ask_riddle"), 0);

    read_riddle();
}

string
long_desc()
{
    return break_string("This is the sorcerer Pandora's butler, Drabakk."+
			" He is here to see that no one gets into the building "+
			"unless they know the riddles. You may ask him "+
			"about passing by, and \"answer\" it with the "+
			"solution to his riddle.\n",76);
}

void
init_living()
{
    ::init_living();
    add_action("answer", "answer");
}

string
ask_riddle()
{
  
    return "The butler asks you: "+riddle+"?\n";
}


int
answer(string str)
{
    notify_fail("Huh? Answer what?\n");
    if (!strlen(str))
	return 0;
    if (str == answer) {
	write("The answer is correct.\n");
	say(QCTNAME(this_player()) + " answered a riddle correctly.\n");
	read_riddle();
	this_player()->move_living("past the door",HOUS_D+"sittroom");
	reward_player(this_player());
	return 1;
    }
    write("The answer is wrong.\n");
    say(QCTNAME(this_player()) + " answered a riddle wrong.\n");
    attack_object(this_player());
    return 1;
}

void
reward_player(object ob)
{
}

