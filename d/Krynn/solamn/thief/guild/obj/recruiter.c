/* the recruiter of the thieves, by Aridor 12/13/95*/
/* 2.11.2000 little fixes by Milan
 */
inherit "/d/Krynn/std/travellingsalesman";
inherit "/d/Krynn/std/bribe";

#include "../guild.h"
#include <macros.h>
#include <ss_types.h>
#include <money.h>
#include <cmdparse.h>
#define SCARF   "/d/Krynn/solamn/thief/obj/scarf3"
#define DUDGEON "/d/Krynn/solamn/thief/obj/dudgeon"
#define PANTS   "/d/Krynn/solamn/palan/obj/pants"
#define SHIRT   "/d/Krynn/solamn/palan/obj/lshirt"
#define TORCH   "/d/Krynn/solamn/thief/obj/torch"

object waitfornod = 0;
void do_nod(object actor, string adverb);

void
equip_me()
{
    object obj;

    seteuid(getuid(TO));
    (obj = clone_object(SCARF))->move(TO);
    add_own_stuff(obj);
    (obj = clone_object(DUDGEON))->move(TO);
    add_own_stuff(obj);
    clone_object(CHALK_OBJ)->move(TO);
    (obj = clone_object(PANTS))->move(TO);
    add_own_stuff(obj);
    (obj = clone_object(SHIRT))->move(TO);
    add_own_stuff(obj);
    clone_object(TORCH)->move(TO);
    clone_object(TORCH)->move(TO);
    clone_object(TORCH)->move(TO);
    clone_object(TORCH)->move(TO);
    (obj = MONEY_MAKE(100,"copper"))->move(TO);
    add_own_stuff(obj);
    (obj = MONEY_MAKE(50,"silver"))->move(TO);
    add_own_stuff(obj);
    (obj = MONEY_MAKE(3,"gold"))->move(TO);
    add_own_stuff(obj);
    command("wear all");
    command("wield all");
}

string
resetexpelbit()
{
    if (!TP || !interactive(TP))
      return "Uhoh, something went wrong. Try again or leave a bug report.";
    TP->clear_bit(1,12);
    write_file("/d/Krynn/solamn/thief/guild/log/cleared",ctime(time())[4..15] +
	       ": " + TP->query_name() + "\n");
    return "OK! Here's the deal: I can't promise anything, but I'll try to " +
      "vouch for you the next time you try to join.";
}

void
create_merchant()
{
    set_name("finias");
    set_living_name("finias");
    add_name("recruiter");
    set_adj("long-legged");
    add_adj("olive-skinned");
    set_title("the Merchant");
    set_gender(0);
    set_long("This is a long-legged, olive-skinned man in his best years. " +
	     "He looks very agile. He seems to be selling and buying " +
	     "things. Actually he seems to carry an entire shop around with him. " +
	     "Use the commands 'list', 'buy', 'value', 'show' and 'sell' just like " +
	     "in any normal shop.\n");
    set_race_name("human");
    default_config_mobile(110);
    set_all_attack_unarmed(90, 90);
    set_all_hitloc_unarmed(90);
    set_skill(SS_BACKSTAB, 80);
    set_skill(SS_WEP_KNIFE, 80);
    set_skill(SS_AWARENESS, 100);
    set_skill(SS_PICK_POCKET, 80);
    set_skill(SS_FR_TRAP, 80);
    set_skill(SS_HIDE, 80);
    set_skill(SS_SNEAK, 80);
    set_skill(SS_OPEN_LOCK, 80);
    set_skill(SS_ACROBAT, 80);
    set_skill(SS_TRADING, 100);
    set_skill(SS_APPR_OBJ, 90);
    set_skill(SS_APPR_VAL, 90);

    set_alignment(-100);
    set_knight_prestige(-1);
    set_whimpy_dir("north");
    set_whimpy(50);

    set_introduce(1);

    equip_me();    
//    set_alarm(1.0,0.0,"equip_me");

    set_random_move(20);
    set_pick_up(10);
    set_act_time(10);
    add_act("say Torches, torches, cheap torches!");
    add_act("say Would you like to buy some torches?");
    add_emote_hook("nod", 2.0, do_nod);

    set_bribe(({ 1,"Is that a joke or what??",
		   100, "Well, we're getting there... slowly.",
		   1000, "The idea looks promising, and you're definitely heading in the right direction...",
		   10000, "You're doing great! Just a tiny little more, and we're doing business.",
		   20000, resetexpelbit}));
}

void
reset_merchant()
{
    object obj;
    
    ::reset_merchant();
    FIND_STR_IN_OBJECT("coins",TO)->remove_object();
    clone_object(TORCH)->move(TO);
    clone_object(TORCH)->move(TO);
    clone_object(TORCH)->move(TO);
    clone_object(TORCH)->move(TO);
    clone_object(CHALK_OBJ)->move(TO);
    (obj = MONEY_MAKE(100,"copper"))->move(TO);
    add_own_stuff(obj);
    (obj = MONEY_MAKE(50,"silver"))->move(TO);
    add_own_stuff(obj);
    (obj = MONEY_MAKE(3,"gold"))->move(TO);
    add_own_stuff(obj);
    
}

void
init_living()
{
    ::init_living();
    init_bribe();
}


int
prospective_member(object who)
{
  if (who->query_wiz_level()) return 1;

    //no layman guild yet.
    if(who->query_guild_name_lay())
      return 0;
    //no good aligned occ guild.
    if(who->query_alignment() > 100)
      return 0;
    //no magic occ guild.
    if (who->query_guild_style_occ() == "magic")
      return 0;
    return 1;
}

int
former_member(object who)
{
    //no layman guild.
    if (who->query_guild_name_lay())
      return 0;
    //former member.
    if (who->test_bit("Krynn",1,12) &&
	!who->test_bit("Krynn",1,11))
      return 1;
    return 0;
}

void
wh(object who,string str)
{
    command("whisper to " + OB_NAME(who) + " " + str);
}

void
wantstorejoin(object who)
{
    wh(who, "Oh hello, old friend. If you're interested in us again, how about a little gift?");
    set_alarm(2.0, 0.0, &wh(who, "(And I'm only interested in coins :-)"));
    set_alarm(5.0, 0.0, &wh(who, "(And yes, I'm bribable!)"));
}

void
timeoutnod(object who)
{
    if (!waitfornod)
      return;
    waitfornod = 0;
    command("say Guess not.");
    command("shrug .");
}

void
recruit(object who)
{
    wh(who,"Hello my friend. You look like someone I might have need for.");
    wh(who,"If you are interested in something new, just give me a nod.");
    set_alarm(20.0, 0.0, &timeoutnod(who));
    waitfornod = who;
}

varargs void
react_introduce(mixed who = 0)
{
    object person;

    ::react_introduce(who);
    if (!who)
      return;

    person = find_player(who);
    if (!person || E(person) != E(TO))
      return;

    if (former_member(person))
    {
	set_alarm(1.0, 0.0, &wantstorejoin(person));
	return;
    }
    
    if (prospective_member(person))
      set_alarm(3.0, 0.0, &recruit(person));
}

void
do_nod(object actor, string adverb)
{
    if(!waitfornod)
      return;
    
    if(waitfornod != actor)
      return;

    waitfornod = 0;

    seteuid(getuid(TO));
    write_file("/d/Krynn/solamn/thief/guild/log/recruited",
	       C(actor->query_name()) + " asked " +
	       extract(ctime(time()),4,15) + "\n");

    wh(actor,"In order to prove your usefulness for our task, you need " +
       "to figure out where to go first.");
    set_alarm(1.0, 0.0, &wh(actor,"Here is what you need to do:"));
    set_alarm(2.0, 0.0, &wh(actor,"Find a movable room."));
    set_alarm(3.0, 0.0, &wh(actor,"Enter the door that lies in the center."));
    set_alarm(5.0, 0.0, &wh(actor,"Then you have found your destination."));
    set_alarm(10.0, 0.0, &wh(actor,"A hint on the side: A map might be helpful."));
}

EMOTE_HOOK

