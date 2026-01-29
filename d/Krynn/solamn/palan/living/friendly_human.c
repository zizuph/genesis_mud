/* created by Aridor 11/30/93
 *
 * 2021-04-02 - Cotillion
 * - Fixed add_ask parse_command issue 
 */


#include "/ss_types.h"
#include <macros.h>
#include "../local.h"
#include <money.h>
#include <filter_funs.h>
#define CITY_GUARD     "/d/Krynn/solamn/palan/palace/office15"

inherit M_FILE


/*prototypes*/
string my_answer();

string intro_title;

void
equip_me()
{
    MONEY_MAKE_CC(random(10))->move(TO);
}

void
create_citizen()
{
}

void
create_krynn_monster()
{
    set_name("citizen");

    set_long("This is a citizen.\n");

    default_config_mobile(random(60) + 10);

    add_prop("_live_m_attack_thief",1);

    set_default_answer(VBFC_ME("my_answer"));
    add_ask("lighthouse",
	    "say It's somewhere in the harbour I believe.",1);
    add_ask("garden","say Oh, there is only one garden in Palanthas " +
	    "I know.",1);
    add_ask(({"cutter","peat","peat cutter"}),"say I don't think I " +
	    "ever saw one. He can't be in the city then.",1);
    add_ask("inn", "say It's a fine inn. You can find it south of the " +
	    "Great Library",1);
    add_ask("palace","say It's a lovely palace, isn't it? The line " +
	    "shouldn't be that long, too.",1);
    add_ask("harbour","say There certainly is one in Palanthas. You'll " +
	    "even find ships going overseas there.",1);
    add_ask(({"shop","store"}),
	    "say The shop is west of the harbour.",1);
    add_ask("library",
	    "say You can find the Library south of the Great Plaza.",1);
    add_ask(({"plaza","great plaza"}),
	    "say The Plaza is right in the middle of the city.",1);
    add_ask(({"club","'knights'' 'club'","knights club"}),
	    "say Hmm, never heard of that.",1);
    add_ask(({"tower"}),
	    "say The black tower you mean? Ack! Don't go there, it's " +
	    "cursed!",1);
    add_ask(({"temple"}),"say Yes we had one but it's all rubble now.",1);
    add_ask(({"post","post office"}),
	    "say The post office is on Circle Street in the southwest of " +
	    "the city.\n",1);

    set_knight_prestige(-1);
    set_alignment(50 + random(200));
    //set_see_blood(1);
    set_tell_active(1);
    add_emote_hook("bow",1.0,&command("bow"));
    trig_new("%s 'attacks' %s", "call_the_guards");
    trig_new("%s 'hurts' %s", "call_the_guards");
    trig_new("%s 'smashes' %s", "call_the_guards");

    create_citizen();
    
    if (query_skill(SS_AWARENESS) == 0)
      set_skill(SS_AWARENESS, (query_stat(3) + query_stat(4)) / 3);
    set_alarm(0.1,0.0,"equip_me");
}


string
my_long()
{
    string str = query_art_name(TP);
    if (str == query_name())
      return str + " " + intro_title + ".\n";
    else
      return C(query_pronoun()) + " is " + str + ".\n";
}


void
my_react_introduce()
{
    tell_room(E(TO), QCTNAME(TO) + " introduces " + query_objective() +
	      "self as:\n" + query_name() + 
	      (intro_title ? (intro_title[0..0] == "," ? "" : " ") + 
	       intro_title : query_exp_title())+
	      ", " + query_gender_string() + " " + query_race_name() + ".\n");
    FILTER_PLAYERS(all_inventory(E(TO)))->add_introduced(L(query_name()));
}

void
react_introduce(mixed who=0)
{
  set_alarm(2.0,0.0,"my_react_introduce");
}

string
my_answer()
{
  set_alarm(1.0,0.0,"command","shrug");
  set_alarm(3.0,0.0,"command","say I cannot help you with that.");
  return "";
}

void
call_the_guards(string aggressor, string dummy)
{
  object hitem, *thigy = all_inventory(E(TO));
  int i;
  for (i = 0; i < sizeof(thigy); i++)
    if ((thigy[i]->vbfc_short() == aggressor[4..strlen(aggressor)]) ||
	(thigy[i]->vbfc_short() == aggressor))
      hitem = thigy[i];
  CITY_GUARD->load_me();
  if (!random(5))
    CITY_GUARD->help_i_need_help(hitem, E(TO));
}

void
attacked_by(object who)
{
    ::attacked_by(who);
    command("shout HELP! Help ME! I am being attacked!");
    if (!random(2))
      CITY_GUARD->help_i_need_help(who, E(TO));
}

void
set_introduce(string str)
{
    intro_title = str;
    ::set_introduce(1);
}
