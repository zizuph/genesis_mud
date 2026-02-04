/* A good/neutral/evil knife. Mortricia 921029
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

#define TO              this_object()
#define TP              this_player()
#define ALIGN_LIM       100
#define LANG_LIM        35
#define AWARE_LIM       32
#define HIT_PEN_BAD     ({ 3,  3})
#define HIT_PEN_STD     ({10, 10})
#define HIT_PEN_GOO     ({18, 18})
#define TYPE            "evil"

string type;

string query_type();
void set_type(string str);
void set_random_type();
void set_hit_pen(int *hp);
void good_sword(object who);
void bad_sword(object who);

public void
create_weapon()
{
    set_name("knife");
    set_pname("knives");
    set_adj("blackened");
    set_long("It's a blackened silver knife. It has some runes " +
             "engraved on the blade.\n");
    set_type(TYPE);
    add_item("runes", "@@my_runes");
    add_cmd_item("runes", "read", "@@my_runes");
    add_prop(OBJ_I_WEIGHT, 800);
    add_prop(OBJ_I_VOLUME, 200);
    add_prop(OBJ_I_VALUE,  107);
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_S_WIZINFO, "This knife belongs to Zasultra.\n");
    add_prop(MAGIC_AM_MAGIC, ({ 20, "enchantment" }));
    add_prop(MAGIC_AM_ID_INFO,
        ({"This is Zasultra's magical knife. It will give you some " +
          "resistance against fire.\n", 20}));
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_I_RES_FIRE, ({8, 1}));
    set_hit_pen(HIT_PEN_STD);
    set_wt(W_KNIFE);
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

public void
leave_env(object from, object to)
{
    int poi;

    ::leave_env(from, to);
    
    if (from && living(from)) {
        poi = from->query_prop(MAGIC_I_RES_FIRE);
        if (poi>0) from->add_prop(MAGIC_I_RES_FIRE, poi-1);
    }
}

public void
enter_env(object new, object old)
{
    int poi;

    ::enter_env(new, old);
    
    if (new && living(new)) {
        poi = new->query_prop(MAGIC_I_RES_FIRE);
        new->add_prop(MAGIC_I_RES_FIRE, poi+1);
        if (query_type() == "good") {
            if (new->query_alignment() > ALIGN_LIM) {
                good_sword(new);
            } else {
                bad_sword(new);
            }
        } else if (query_type() == "evil") {
            if (new->query_alignment() < -ALIGN_LIM) {
                good_sword(new);
            } else {
                bad_sword(new);
            }
        } else if (query_type() == "neutral") {
            if (new->query_alignment() >= -ALIGN_LIM &&
                new->query_alignment() <=  ALIGN_LIM) {
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
delay_msg(object who, string msg)
{
    if (who) who->catch_msg(msg);
}

void
good_sword(object who)
{
    set_hit_pen(HIT_PEN_GOO);
    if (who->query_skill(SS_AWARENESS) < AWARE_LIM) return;
    set_alarm(1.0, -1.0,
        &delay_msg(who, "The " + short() + " suits you!\n"));
}

void
bad_sword(object who)
{
    set_hit_pen(HIT_PEN_BAD);
    if (who->query_skill(SS_AWARENESS) < AWARE_LIM) return;
    set_alarm(1.0, -1.0,
        &delay_msg(who, "The " + short() + " doesn't suit you at all!\n"));
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
    return s + "\n";
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
        write("It must be a magic weapon.\n");
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
    string foo;
    
    init_wep_recover(arg);
    sscanf(arg, "%s##%s##", foo, type);
}
