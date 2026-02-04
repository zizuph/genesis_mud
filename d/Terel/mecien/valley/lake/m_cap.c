inherit "/std/monster";
inherit "/lib/trade";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <money.h>

#define	NUM	 sizeof(MONEY_TYPES)
#define TP       this_player()
#define TO       this_object()
#define NF(xx)   notify_fail(xx)
#define BSN(xx)  break_string(xx+"\n", 70)
#define STAT_LIM 20
#define SHIP "/d/Terel/mecien/valley/lake/"

object ship;

void
do_die(object killer)
{
    ::do_die(killer);
    if (ship)
	ship->stop_ship("The ship stops; someone killed the captain!\n");
}

void
set_ship(object s)
{
    ship=s;
}

void
create_monster()
{
   object ring;
    set_name("Cirenore");
    add_name("captain");
   add_name("cirenore");
    set_living_name("cirenore");
    set_race_name("elf");
    set_adj("exalted");
    add_adj("mystical");
    set_long(
    "An elf of great magnitude, he stands tall and noble, his eyes\n"
   +"of sparkling blue, his hair long and silver. Wearing a white tunic\n"
   +"and breeches, a long brilliant blue cloak, a silver helm and a\n"
   +"pair of fur trim boots, he seems almost dazzling.\n"
   +"Over his tunic he wears a silver surcoat on which is emblazoned\n"
   +"a mystical emerald tree.\n"
);

    set_stats(({ 101, 124, 105, 112, 111, 134 }));
    set_skill(SS_SWIM, 120);
    set_skill(SS_AWARENESS, 100);
    set_base_stat(SS_OCCUP, 94);
    set_title("the Wise Voyager, Navigator of the Stars");
    setuid();
    seteuid(getuid());
    ring=clone_object("/d/Terel/mecien/valley/guild/mring");
    ring->move(this_object());
   
    config_default_trade();

    trig_new("%w 'introduces' %s", "react_introduce");
}

void
init_living()
{
    ::init_living();
    add_action("buy", "buy");
    add_action("ask", "ask");
}

int
buy(string str)
{
    object buy_ob;
    string what, for_c, get_c, change;
    int    *result, m_res, price;

    if (!str) {
	notify_fail("Buy what?\n");
	return 0;
    }
    if (sscanf(str, "%s with %s and get %s", what, for_c, get_c) != 3)
	if (sscanf(str, "%s with %s", what, for_c) != 2)
	    what = str;
    if (what != "ticket") {
	notify_fail("The captain sings: I have no such thing\n");
	return 0;
    }
    buy_ob=clone_object(SHIP + "m_ticket");
    if (!buy_ob) {
	notify_fail("The captain sings: I have no more\n");
	return 0;
    }
    if (this_player()->query_average_stat() <= STAT_LIM) {
	buy_ob -> add_prop(OBJ_I_VALUE, 0);
    } else {
        price = buy_ob->query_prop(OBJ_I_VALUE);
        result=pay(price,this_player(),for_c,0,0,get_c);
        if (sizeof(result)==1) {
            buy_ob->remove_object();
            return 0;
        }
        write("You pay " + text(result[0 .. NUM - 1]) + ".\n");
        if (change) write("You get " + change + " as change.\n");
    }

    if (buy_ob->move(this_player())) {
	write("You drop the " + buy_ob->short() + " on the ground.\n");
	say(QCTNAME(this_player()) + " drops one " + buy_ob->short() +
	    " on the ground.\n");
	buy_ob->move(environment(this_player()));
    } else {
	write("You get your " + buy_ob->short() + ".\n");
	say(QCTNAME(this_player()) + " buys a " + buy_ob->short() + ".\n");
    }
    return 1;
}

void
react_introduce(string person, string who)
{
    call_out("introduce_me", 3);
}

void
introduce_me()
{
    command("introduce myself");
}

int
ask(string str)
{
    object who;
    string what;

    NF("Ask who about what?\n");
    if (!str) return 0;

    if (!parse_command(str, environment(), " %o 'about' / 'for' %s ",
	who, what)) return 0;

    if (!who) return 0;
    if (who != TO) return 0;
    if (!what) return 0;
    if (what == "ship" || what == "your ship" || what == "boat" ||
	what == "your boat" || what == "sailing ship" ||
	what == "destination") {
	TO->command("say I travel the sparkling lake");
	return 1;
    }
    if (what == "ticket" || what == "cost") {
	TO->command("say Passage costs normally 20 copper coins");
	TO->command("say I can sell you");
	TO->command("smile");
	return 1;
    }
    TO->command("sigh");
    TO->command("say I do not understand");
    return 1;
}
