/* A good/neutral/evil sword. Mortricia 921029
 * The type TYPE can be set to
 * 1) "good"    -> players with alignment > +ALIGN_LIM will benefit
 * 2) "evil"    -> players with alignment < -ALIGN_LIM will benefit
 * 3) "neutral" ->  -ALIGN_LIM <= player alignment <= +ALIGN_LIM
 */
inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

#define BSN(xx)         break_string(xx+"\n", 70)
#define TO              this_object()
#define TP              this_player()
#define ALIGN_LIM       160
#define LANG_LIM        25
#define AWARE_LIM       25
#define HIT_PEN_BAD     ({ 8,  8})
#define HIT_PEN_STD     ({15, 15})
#define HIT_PEN_GOO     ({30, 30})
#define TYPE            "neutral"

string type;
string query_type();
void set_type(string str);
void set_random_type();
void set_hit_pen(int *hp);
void good_sword(object who);
void bad_sword(object who);

void
create_weapon()
{
    set_name("sword");
    set_short("mysterious sword");
    set_long(BSN(
	"It's a mysterious sword. It has some runes engraved on " +
	"the blade."
    ));
    set_adj("mysterious");
    set_type(TYPE);
    add_item("runes", "@@my_runes");
    add_cmd_item("runes", "read", "@@my_runes");
    add_prop(OBJ_I_WEIGHT, 6000);
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_VALUE, 207);
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_S_WIZINFO, "This sword plays a role in the " +
                            "magician's quest in the gypsy camp.\n");
    add_prop("mystic_weapon", 1);
    add_prop(MAGIC_AM_MAGIC, ({ 30, "enchantment" }));
    add_prop(MAGIC_AM_ID_INFO,
	({"This is Penthir's magical sword. It will give you some " +
	  "resistance against poison.\n", 30}));
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_I_RES_POISON, ({13, 1}));
    set_hit_pen(HIT_PEN_STD);
    set_wt(W_SWORD);
    set_dt(W_SLASH | W_IMPALE);
    set_hands(W_ANYH);
}

void
set_hit_pen(int *hp)
{
    if (sizeof(hp) != 2) return;
    set_hit(hp[0]);
    set_pen(hp[1]);
}

void set_type(string str) { type = str; }

string query_type() { return type; }

void
set_random_type()
{
    switch (random(3)) {
	case 0:
	    set_type("good");
	    break;
	case 1:
	    set_type("neutral");
	    break;
	case 2:
	    set_type("evil");
	    break;
	default:
	    set_type("skillful");
	    break;
    }
}

void
leave_env(object from, object to)
{
    int poi;

    ::leave_env(from, to);
    if (living(from)) {
	poi = from->query_prop(MAGIC_I_RES_POISON);
	if (poi>0) from->add_prop(MAGIC_I_RES_POISON, poi-1);
    }
}

void
enter_env(object new, object old)
{
    int poi;

    ::enter_env(new, old);
    if (living(new)) {
	poi = new->query_prop(MAGIC_I_RES_POISON);
	new->add_prop(MAGIC_I_RES_POISON, poi+1);
	if (query_type() == "good") {
            if (new -> query_alignment() > ALIGN_LIM) {
		good_sword(new);
	    } else {
		bad_sword(new);
	    }
	} else if (query_type() == "evil") {
	    if (new -> query_alignment() < -ALIGN_LIM) {
		good_sword(new);
	    } else {
	        bad_sword(new);
	    }
	} else if (query_type() == "neutral") {
	    if (new -> query_alignment() >= -ALIGN_LIM &&
		new -> query_alignment() <=  ALIGN_LIM) {
		good_sword(new);
	    } else {
	        bad_sword(new);
	    }
	}
    } else {
        set_hit_pen(HIT_PEN_STD);
    }
}

void
good_sword(object who)
{
    set_hit_pen(HIT_PEN_GOO);
    if (who->query_skill(SS_AWARENESS) < AWARE_LIM) return;
    set_alarmv(1.0, -1.0, "delay_msg", ({who, "The sword suits you!\n"}));
}

void
bad_sword(object who)
{
    set_hit_pen(HIT_PEN_BAD);
    if (who->query_skill(SS_AWARENESS) < AWARE_LIM) return;
    set_alarmv(1.0, -1.0, "delay_msg",
	       ({who, "The sword doesn't suit you at all!\n"}));
}

void
delay_msg(object who, string msg)
{
    if (who) who->catch_msg(msg);
}

string
my_runes()
{
    string s;

    if (TP->query_skill(SS_LANGUAGE) >= LANG_LIM) {
        s = "Only those who are "+query_type()+" enough will benefit " +
	    "from me.";
    } else {
	s = "You don't understand the runes.";
    }
    return BSN(s);
}

void
appraise_object(int num)
{
    int skill;

    ::appraise_object(num);
    if (!num) {
        skill = TP->query_skill(SS_APPR_OBJ);
    } else {
        skill = num;
    }
    if (skill > AWARE_LIM) {
	write("It must be a magic sword.\n");
    }
}

string
query_recover()
{
    return MASTER + ":" + query_wep_recover() + "##" + type + "##";
}

void
init_recover(string arg)
{
    init_wep_recover(arg);
    sscanf(arg, "%s##%s##", type);
}
