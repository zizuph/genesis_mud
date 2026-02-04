/*
 *  A blue sword. Mortricia 920722
 *  Modified Jan. 95
 */

inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>

#define TO           this_object()
#define ETO          environment(TO)
#define TP           this_player()
#define HARD_TO_READ 42
#define TIME_TO_DEST 220

public void set_hit_and_pen(int val);

static int bb_broken=0, dest_id=0;

public void
init()
{
    ::init();
    add_action("read",  "read");
    if (ETO == TP) add_action("shout", "shout");
}

public void
create_weapon()
{
    set_name(({"sword", "bluebolt"}));
    set_short("blue sword");
    set_long("A blue sword. Some runes are engraved in the blade.\n");
    set_adj("blue");

    set_hit(34);
    set_pen(34);
    add_prop(OBJ_I_WEIGHT, 8000);
    add_prop(OBJ_I_VOLUME, 3000);

    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(OBJ_S_WIZINFO, "A magic sword. By shouting its name (Bluebolt) " +
             "the player can rise its powers for a while. Afterwards it is " +
             "virtually useless.\n");
    add_prop(MAGIC_AM_MAGIC, ({ 40, "enchantment" }) );
    add_prop(MAGIC_AM_ID_INFO,
        ({"My maker is master Sal.\n", 10,
          "Call me out load by my name, and my powers will " +
          "increase for a while.\n", 20,
          "My name is Bluebolt.\n", 40}));

    add_item(({"runes"}), "The runes seem to be very ancient. " +
                          "Maybe you can read them?\n");

    set_wt(W_SWORD);
    set_dt(W_SLASH | W_IMPALE);

    set_hands(W_RIGHT);
}

public int
read(string what)
{
    if (what != "runes") return 0;
    
    if (TP->query_skill(SS_LANGUAGE) < HARD_TO_READ) {
        write("You cannot interpret the ancient runes.\n");
    } else if (bb_broken) {
        write("The runes read:\n" +
           "I have lost my power and you will not be able to regain it.\n" +
           "This sword was made by master Sal.\n");
    } else if (dest_id) {
        write("The runes shine with a faint blueish light, they read:\n" +
              "At your service.\n" +
              "This sword was made by master Sal.\n");
    } else {
        write("The runes read:\n" +
            "I am powerful like a bolt from the blue, hence call " +
            "me Bluebolt.\n" +
            "To invoke my powers you need to speak out my name " +
            "loud and clear.\n" +
            "This sword was made by master Sal.\n");
    }
    say(QCTNAME(TP) + " examines " + TP->query_possessive() + " sword.\n");
    return 1;
}

/* Note, this shout() function triggered by shout must always return 0, so that
 * the normal shout cmd always gets executed. For proper timing we call then
 * function enhance_sword() with a small delay.
 */
public int
shout(string str)
{
    if (bb_broken) return 0;
    
    if (lower_case(str) != "bluebolt") return 0;
    
    if (present("bluebolt", TP) == TO) set_alarm(1.0, -1.0, "enhance_sword");
    
    return 0;
}

public void
enhance_sword()
{
    object who;
    
    who = query_wielded();
    add_prop("_wep_i_blademaster_no_exchange",1);
    add_prop(OBJ_M_NO_DROP, "The "+short()+" refuses to be abandoned!\n");
    add_prop(OBJ_M_NO_SELL, "The "+short()+" refuses to be abandoned!\n");
    
    if (!dest_id) {
        set_hit_and_pen(58);
        set_short("bluebolt");
        dest_id = set_alarm(itof(TIME_TO_DEST), -1.0, "destroy_bb");
        if (who) {
            who->catch_msg("The " + short() + " flickers and you feel it has " +
                  "become much more powerful, but you are not certain for how " +
                  "long it will last.\n");
            tell_room(environment(who), "The " + short() + " " + QTNAME(who) +
                  " is wielding shines brightly for a while.\n", who);
        }
        return;
    }
    if (who) {
        who->catch_msg("The " + short() + " shines faintly as a response to " +
                       "your call.\n");
        tell_room(environment(who), "The " + short() + " " + QTNAME(who) +
                  " is wielding shines faintly for a while.\n", who);
    }
}

public void
destroy_bb()
{
    object who;
    
    set_hit_and_pen(5);
    
    set_short("dull blue sword");
    set_long("A dull blue sword. Some runes are engraved in the blade.\n");
    set_adj(({"blue", "dull"}));
    add_prop(OBJ_I_VALUE, 100);
    bb_broken = 1;
    dest_id = 0;
    remove_prop("_wep_i_blademaster_no_exchange");
    remove_prop(OBJ_M_NO_DROP);
    remove_prop(OBJ_M_NO_SELL);

    
    who = query_wielded();
    if (who)
        who->catch_msg("You feel the " + short() + " has lost its powers.\n");
}

string
query_recover()
{
    if (!bb_broken && !dest_id)  /* Only recover it if it not has been used */
        return MASTER + ":" + query_wep_recover();
    return "";
}

void
init_recover(string arg)
{
    init_wep_recover(arg);
}

public void
set_hit_and_pen(int val)
{
    set_hit(val);
    set_pen(val);
    
    if (query_wielded()) query_wielded()->update_weapon(TO);
}
