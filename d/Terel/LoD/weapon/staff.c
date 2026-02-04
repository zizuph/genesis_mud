#include "/d/Terel/include/Terel.h"
inherit STDWEAPON;
inherit "/lib/keep";

#include <std.h>
#include <wa_types.h>
#include <cmdparse.h>
#include <ss_types.h>

#define LANG_LIMIT  35

int kissed = 0;
string desc = "";

public void
create_weapon()
{
    ::create_weapon();
    
    set_name("staff");
    set_long("It is a simple wooden staff. It is made of some kind of " +
             "whiteish wood.@@my_staff@@\n");
    set_adj(({"simple", "wooden"}));
    set_hit(60);
    set_pen(13);
    add_prop(OBJ_I_WEIGHT, 1600);
    add_prop(OBJ_I_VOLUME,  800);
    add_prop("mystic_weapon", 1);
    
    set_wt(W_POLEARM);
    set_dt(W_IMPALE);
    set_hands(W_BOTH);
    
    set_keep(0);
    
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 40, "enchantment" }) );
    add_prop(MAGIC_AM_ID_INFO, ({
             "This is Sawoq's magic staff.", 10,
             "It can be used to find the name of someone.", 30,
             "But it must be kissed first and you must be skillful " +
             "in the ancient languages.", 45
	         }));
    add_prop(OBJ_S_WIZINFO, "This is Sawoq's magic staff.\n");
}

public string
my_staff()
{
    if (!strlen(desc))
        return "";
    if (TP->query_skill(SS_LANGUAGE) < LANG_LIMIT)
        return " There is an ancient looking inscription on it, " +
               "but you cannot decipher it.";
               
    return " There is an inscription on it. It simply reads: " +
           desc + ".";
}

public int
do_point(string str)
{
    object ob, *who;
    
    if (!str || query_wielded() != TP)
        return 0;
        
    notify_fail("Point what at whom?\n");
    if (!parse_command(str, ETP, "'staff' [at] %l", who))
        return 0;
        
    who = NORMAL_ACCESS(who, 0, 0);
    
    if (sizeof(who) != 1)
        return 0;
        
    ob = who[0];
    
    if (ob == TP || !CAN_SEE(TP, ob))
        return 0;
    
    if (random(TP->query_stat(SS_WIS)) > ob->query_stat(SS_WIS) &&
        !(SECURITY->query_wiz_level(ob->query_real_name())) &&
        kissed) {
        desc = ob->query_name();
        kissed = 0;
        TP->catch_msg("As you point your " + short() + " at " + QTNAME(ob) +
                      " you feel it shiver slightly.\n");
    } else {
        desc = "";
        TP->catch_msg("You point your " + short() + " at " + QTNAME(ob) +
                      ".\n");
    }
    ob->catch_msg(QCTNAME(TP) + " points " + TP->query_possessive() +
                  " " + short() + " at you.\n");
    say(QCTNAME(TP) + " points " + TP->query_possessive() + " " +
        short() + " at " + QTNAME(ob) + ".\n", ({TP, ob}));
    
    return 1;
}

public int
do_kiss(string str)
{
    if (str != "staff" && query_wielded() != TP)
        return 0;
        
    write("You kiss your " + short() + ".\n");
    say(QCTNAME(TP) + " kisses " + TP->query_possessive() + " " +
        short() + ".\n");
    kissed = 1;
    return 1;
}

public void
init()
{
    ::init();
    if (ETO == TP) {
        add_action(do_point, "point");
        add_action(do_kiss, "kiss");
    }
}

public string
query_recover()
{
    return MASTER + ":" + query_wep_recover() + query_keep_recover();
}

public void
init_recover(string arg)
{
    init_wep_recover(arg);
    init_keep_recover(arg);
}
