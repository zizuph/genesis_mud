/* Creative rights reserved to Mecien (Jeff Babcock) and team. */
inherit "/std/object.c";

#include <stdproperties.h>
#include <macros.h>

#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

#define TP              this_player()
#define TO              this_object()
#define ETP             environment(TP)
#define ETO             environment(TO)

#define CANDLE_DELAY    28 + random(5)
#define CANDLE_MAX      4 + random(3)
#define CANDLE_INC      8 + random(5)

#define CANDLE_HEAL     0
#define CANDLE_MANA     1
#define CANDLE_FATIGUE  2
#define CANDLE_TYPES    ({CANDLE_HEAL, CANDLE_MANA, CANDLE_FATIGUE})
#define CANDLE_NAMES    ({MYSTIC_HCANDLE, MYSTIC_MCANDLE, MYSTIC_FCANDLE})
#define CANDLE_CFACT    ({10, 20, 8})

int                     amount_burned = 0;
int                     lit_flag = 0;
int                     type = CANDLE_HEAL;
int                     heal = CANDLE_INC;
int                     max_burned = CANDLE_MAX;
int                     aid = 0;
string                  candle_long = "A candle.";
string                  heal_msg = "";
string                  other_msg = "";
string                  out_msg = "The candle gutters and dies. " +
                                  "The delightful smell soon disperses.\n";

public int
set_healing_type(int t)
{
    if (member_array(t, CANDLE_TYPES) < 0) return 0;
    
    add_name(CANDLE_NAMES[t]);
    type = t;
    
    return 1;
}

public void
set_candle_long(string s)
{
    candle_long = s;
}

public void
init()
{
    ::init();
    add_action("do_light",   "light");
    add_action("do_unlight", "extinguish");
    add_action("do_smell",   "smell");
}

public string
how_much()
{
    int length = (5*(max_burned - amount_burned))/max_burned;
    string s = query_adj() + " candle";
    
    switch (length)
    {
        case 5:
            return "The " + s + " has never been lit.";
        case 4:
            return "The " + s + " is almost whole.";
        case 3:
            return "The " + s + " has burned perhaps a fourth of the way down.";
        case 2:
            return "The " + s + " is about half gone.";
        case 1:
            return "Most of the " + s + " has burned away.";
        default:
            return "The " + s + " is almost gone; only a stub remains.";
    }
}

public string
is_lit()
{
    string s = query_adj() + " candle";
    
    if (lit_flag)
        return "The " + s + " is burning; a wonderful odour fills this place.";
    else
        return "The " + s + " is not lit.";
}

public string
my_short()
{
    if (lit_flag)
        return "burning " + query_adj() + " candle";
    else
        return query_adj() + " candle";
}

public string
my_long()
{
    return candle_long + " " + how_much() + " " + is_lit() + "\n";
}

public int
my_light()
{
    return lit_flag;
}

public int
query_value()
{
    return CANDLE_CFACT[type]*heal*(max_burned + 1 - amount_burned);
}

public void
create_candle()
{
}

public void
create_object()
{
    set_name("candle");
    set_short("@@my_short@@");
    set_long("@@my_long@@");
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 200);
    add_prop(OBJ_I_LIGHT, "@@my_light@@");
    add_prop(OBJ_I_VALUE, "@@query_value@@");
    
    create_candle();
}

public void
heal_action(object who)
{
    switch (type) {
        case CANDLE_HEAL:
            who->heal_hp(heal); break;
        case CANDLE_MANA:
            who->add_mana(heal); break;
        case CANDLE_FATIGUE:
            who->add_fatigue(heal); break;
        default:
            break;
    }
}

public void
set_heal_msg(string s)
{
    heal_msg = s;
}

public void
set_other_msg(string s)
{
    other_msg = s;
}

public void
set_out_msg(string s)
{
    out_msg = s;
}

public void
heal_mystics(object ob)
{
    if (!living(ob)) return;
    
    if (MEMBER(ob)) {
        heal_action(ob);
        if (strlen(heal_msg))
            ob->catch_msg(heal_msg);
    } else {
        if (strlen(other_msg))
            ob->catch_msg(other_msg);
        ob->catch_msg();
    }
}

public void
burn()
{
    int i;
    object where;
    
    if (!lit_flag) return;
    
    if (ETO->query_prop(ROOM_I_IS))
        where = ETO;
    else
        where = environment(ETO);
        
    map(all_inventory(where), heal_mystics);
    
    amount_burned++;
    
    if (amount_burned > max_burned) {
        if (aid) {
            remove_alarm(aid);
            aid = 0;
        }
        if (strlen(out_msg))
            tell_room(where, out_msg);
        remove_object();
        where->update_light(1);
    }
}

public int
do_light(string str)
{
    object ob;

    notify_fail("Light what?\n");
    
    if (!parse_command(str, ETO, "%o", ob)) return 0;
    if (ob != TO) return 0;
    
    if (!MEMBER(TP)) {
        notify_fail("You do not possess the powers to do that.\n");
        return 0;
    }
    
    if (lit_flag) {
        notify_fail("But the candle is already lit!\n");
        return 0;
    }
    
    if (!ETO->query_prop(ROOM_I_IS) || living(ETO)) {
        notify_fail("You sense somehow that the sacred candle's " +
                    "benefits are to be shared, and that it must " +
                    "not be lit in your hands alone.\n");
        return 0;
    }
    
    write("You light the "+ short() + ", and the air soon fills " +
          "with a wonderful fragrance. Inhaling the heady aroma, you " +
          "soon forget your wounds and worries, and begin to feel better.\n");
    say(QCTNAME(TP) + " lights the " + short() + ", and the air " +
        "soon fills with a wonderful fragrance. Inhaling the heady " +
        "aroma, you soon forget your wounds and worries, and begin " +
        "to feel better.\n");
    
    lit_flag = 1;
    add_adj("burning");
    if (amount_burned == 0) amount_burned++;
    ETO->update_light(1);
    
    add_prop(OBJ_M_NO_GET, "The sacred flame is not to be moved " + 
                           "while burning.\n");
    aid = set_alarm(itof(CANDLE_DELAY), itof(CANDLE_DELAY), burn);

    return 1;
}

public int
do_unlight(string str)
{
    object ob;

    notify_fail("Extinguish what?\n");
    
    if (!parse_command(str, ETO, "%o", ob)) return 0;
    if (ob != TO) return 0;
    
    if (!MEMBER(TP)) {
        notify_fail("You do not possess the powers to do that.\n");
        return 0;
    }
    
    if (!lit_flag) {
        notify_fail("But the candle is not lit!\n");
        return 0;
    }
    
    write("Regretfully, you extinguish the candle, and the delightful " +
          "odour soon vanishes.\n");
    say(QCTNAME(TP) + " extinguishes the candle, and the delightful " +
        "odour soon vanishes.\n");
    
    lit_flag = 0;
    remove_adj("burning");
    remove_prop(OBJ_M_NO_GET);
    ETO->update_light(1);
    
    if (aid) {
        remove_alarm(aid);
        aid = 0;
    }
    
    return 1;
}

public int
do_smell(string str)
{
    if (lit_flag && (!str || str == "candle" || str == "odour")) {
        write("You inhale deeply and sense a delightful odour.\n");
        say(QCTNAME(TP) + " inhales deeply.\n");
        return 1;
    }
    return 0;
}

public string
query_recover()
{
    if (amount_burned > max_burned || lit_flag) return "";
    
    return MASTER + ":" +
           amount_burned + "##" + heal + "##" + max_burned +
           "##" + type;
}

public void
init_recover(string arg)
{
    sscanf(arg, "%d##%d##%d##%d",
           amount_burned, heal, max_burned, type);
}
