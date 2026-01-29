inherit "/std/monster";

#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <const.h>
#include "/d/Roke/common/defs.h"

#define RIDDLEFILE "/d/Roke/Athas/npc/riddles"

string	riddle,answer;
static int current;

void reward_player(object ob);

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
  

void
create_monster()
{
    if (!IS_CLONE)
        return;
    seteuid(getuid());

    set_name("citizen");
    set_race_name("gnome");
    set_living_name("rothwarin");
    set_long("@@long_desc");
    set_adj("little kringe");

    set_alignment(-10);      
    set_gender(G_MALE);

    add_prop(CONT_I_WEIGHT, 47000);
    add_prop(CONT_I_HEIGHT, 142);
    add_prop(NPC_M_NO_ACCEPT_GIVE, 1);

    set_stats(({ 30, 30, 30, 30, 30, 30 }));
    heal_hp(10000);

    set_skill(SS_DEFENCE, 30);
    set_skill(SS_UNARM_COMBAT, 30);

    add_ask(({ "quest","pandora","help",
		 "information","info", "about information", "for information" }), VBFC_ME("ask_riddle"), 0);

    read_riddle();
}

string
long_desc()
{
    return break_string("The gnome here thinks he might have some information for you "+
			"if you ask him, he will demand that you answer a riddle first, "+
			"and if you \"answer\" the riddle right, he will give you his"+
			" information.\n",76);
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
  
    return "The gnome asks you: "+riddle+"?\n";
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

	clone_object(A_OBJ_D+"letter")->move(this_object());
	read_riddle();
	reward_player(this_player());
	return 1;
    }
    write("The answer is wrong.\n");
    say(QCTNAME(this_player()) + " answered a riddle incorrectly.\n");
    return 1;
}

void
reward_player(object ob)
{
     seteuid(getuid());
     command("give letter to " + lower_case(NAME));
     return 0;
}
