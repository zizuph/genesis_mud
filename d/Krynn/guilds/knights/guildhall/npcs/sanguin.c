/* New Librarian */

#include "../../guild.h"
#include <macros.h>
#include <language.h>
#include <money.h>
#include <ss_types.h>

inherit "/std/act/action";
inherit M_FILE

#include "./std/killer.h"

int query_knight_level() { return 4; }

int soul_id;
void get_me_soul();

string query_race_name()
{
    return(calling_function() == "query_presentation" ? "Solamnian" :
      "human");
}

public void
create_krynn_monster()
{
    int i;

    set_name("sanguin");
    set_living_name("sanguin");
    set_adj(({"aged", "grey-haired"}));
    set_title("of Palanthus, the Elder of Swords");
    set_gender(0);
    set_introduce(1);
    set_long("This elderly human serves as the librarian of Vingaard Keep. "+
      "Amazingly enough, he has a full head of silvery grey hair that hangs "+
      "in wispy strands over his ears. His moustache is the grandest you "+
      "have ever seen, and the same bright silver as his hair. From how "+
      "often he strokes it, you can tell it is his pride and joy. Two light "+
      "green eyes look fondly over the books, which he occasionally takes "+
      "from the shelves and dusts off.\n"+
      "His tunic is decorated with the symbol of the Order of the Sword.\n");
    set_race_name("human");
    for (i = 0; i < 6; i++)
        set_base_stat(i, 80 + random(40));

    set_knight_prestige(-4);
    set_alignment(1500);

    set_skill(SS_WEP_CLUB, 100);
    set_skill(SS_PARRY, 90);
    set_skill(SS_DEFENCE, 70);
    set_skill(SS_AWARENESS, 75);
    set_skill(SS_2H_COMBAT, 90);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(CONT_I_HEIGHT, 190);
    add_prop(CONT_I_WEIGHT, 70100);
    MONEY_MAKE_GC(random(15) + 5)->move(TO);
    soul_id = set_alarm(1.0, 0.0, &get_me_soul());
    set_alarm(1.0,0.0,"arm_me");

    set_act_time(5);
    add_act("ksmooth");
    add_act("ksmooth");
    add_act("ksmooth");
    add_act("smile quietly");
    add_act("emote retrieves a book from the shelves and dusts it off "+
      "gently.");
    add_act("ksomber");
    add_act("say I remember my first battle like it was yesterday. I was "+
      "sent to defend a village in southern Solamnia from a band of "+
      "marauding goblins.");
    add_act("say I was stationed in Palanthus for many years. I took such "+
      "a liking to the Great Library there, that when I returned to Vin"+
      "gaard a few years ago, I was assigned to keep up the library here.");
    add_act("say As fine a library as this is, it doesn't compare to the "+
      "Great Library of Palanthus.");
    add_act("say I should like to visit the Palace of Palanthus again "+
      "soon.");
    add_act("emote straightens the books on the shelves behind him.");
    add_act("emote turns as he hears something, and his hand absentmindedly "+
      "drops to an odd shape concealed beneath his robes. You look up at "+
      "him again, seeing his face soften, and realize this man is not as "+
      "helpless as he appears.");
    add_act("kbow");
    add_act("cough");
    add_act("stretch");

    set_default_answer("For some reason, you are ignored.\n");
    add_ask(" [about] 'book' / 'books'",
      "say Of course there are books here, we are in "+
      "a library after all.",1);
    add_ask(" [about] 'palanthus' / 'palanthus'",
      "say You've never heard of Palanthus? "+
      "It's the largest city on Ansalon, far to the northwest of "+
      "Vingaard Keep.",1);
}

void
get_me_soul()
{
    TO->add_cmdsoul(SOULS + "solamnian_soul");
    TO->update_hooks();
    remove_alarm(soul_id);
}

int
special_attack(object enemy)
{
    TO->command("charge " + enemy->query_real_name());
    TO->command("kattack " + enemy->query_real_name());
    return 0;
}

void
arm_me()
{
    object mace;
    clone_object("/d/Krynn/solamn/hctower/spur/obj/clericrobe")->move(TO);
    mace = clone_object(VWEP + "s_mace");
    mace->set_short("silver solamnic mace");
    mace->set_hit(30);
    mace->set_pen(35);
    mace->move(TO);
    command("wear all");
    command("wield all");
}

void
attacked_by(object ob)
{
    TO->command("kwar");
    set_alarm(1.0, 0.0, "message1");
    ::attacked_by();
}

void
message1()
{
    TO->command("kc1");
}

