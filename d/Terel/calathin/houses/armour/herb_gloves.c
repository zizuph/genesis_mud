/*
  Gardener's Gloves
*/
#pragma strict_types
inherit "/lib/keep";
inherit "/d/Terel/include/cloned_armours.c";
inherit "/std/armour";

#include "/d/Terel/include/Terel.h"
#include <wa_types.h>
#include <ss_types.h>
#include <tasks.h>
#include <formulas.h>
#include <macros.h>

#define ERROR_LOG "/d/Terel/log/bug_gloves"
int gglove_alarm;
int gg_drain_count = 0;
int gg_mental_cost = 100;
int gg_skill_inc = 0;
float gg_mana_drain = 75.0;
float gg_skill_bonus = 4.0;
float gg_drain_delay = 60.0;
float gg_drain_cycle = 60.0;

void
create_armour()
{
    set_name("gloves");
    set_short("pair of thick leather gloves");
    set_pshort("pairs of thick leather gloves");
    set_adj("leather");
    add_adj(({"dirty", "thick", "grimy"}));
    set_long("The grimy gloves are covered in layers of dirt " +
        "and stained in many places. " +
        "Small cracks and nicks in the thick leather hint to " +
        "the many hours of hardwork done with these gloves.\n");

    set_default_armour(10, A_HANDS, 0, 0);
    set_af(this_object());
    set_keep(1);
    set_may_not_recover();

    add_prop("_Terel_Gardener_Gloves",1);
    add_prop(OBJ_I_WEIGHT, 390);
    add_prop(OBJ_I_VOLUME, 420);
    add_prop(OBJ_I_VALUE, 405);
    add_prop(OBJ_M_NO_BUY, 1);    

    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(MAGIC_AM_MAGIC,({50,"enchantment"}));
    add_prop(MAGIC_AM_ID_INFO, ({"You sense that the gloves " +
       "possess ancient magic that will enhance your abilities " +
       "in dealing with plants.\n", 30}));
    add_prop(OBJ_S_WIZINFO,"The gloves add increased herbalism " +
        "based on mental capablities and natural skill. " +
        "query_gglove_drains() returns number of times gloves drained. " +
        "query_gglove_cost() returns actual charged mana per drain. " +
        "query_gglove_skill() returns levels of skill increased. " +
        "A cost of mana is charged upon wearing and periodically " +
        "while gloves remain worn. Gloves wear down and will " +
        "break if not repaired or if mana runs too low.\n");
    return;
}

void
calc_cost()
{    
    float mental_factor, skill_factor;
    mental_factor = 
        itof(TP->query_base_stat(SS_INT) + TP->query_base_stat(SS_WIS)) /
            200.0;
    skill_factor = 
        itof(TP->query_base_skill(SS_HERBALISM)) / 50.0;

    gg_mental_cost = ftoi(gg_mana_drain / 
        ((2.0 * mental_factor) + skill_factor + 1.0)); 
    gg_skill_inc = ftoi(gg_skill_bonus * (mental_factor + skill_factor));    

    return;
}

int
query_gglove_drains() {return gg_drain_count;} 

int
query_gglove_cost() {return gg_mental_cost;}

int
query_gglove_skill() {return gg_skill_inc;}

void
glove_drain()
{
    object wearer = query_worn();
    int w_mana_max, w_mana, w_mana_fac;

    //check for linkdead
    if (!interactive(wearer)) return;

    //no drain if gloves broke
    if(TO->query_prop(OBJ_I_BROKEN)) {
        remove_alarm(gglove_alarm);
        return;
    }   
 
    //no drain if not worn still
    if(!objectp(wearer)) {
        write_file(ERROR_LOG, 
            "herb_gloves.c is buggy.\n");
        return;
    }

    //check mana amounts remaining
    w_mana = wearer->query_mana();
    w_mana_fac = wearer->query_max_mana() / (w_mana + 1);
    gg_drain_count += 1;

    //magic in use deteriorates the gloves
    if(random(10) < 2) TO->set_condition(TO->query_condition() + 1);

    //check if fail to pay
    if(w_mana <= gg_mental_cost) {
        wearer->set_mana(0);

        TO->add_prop("_ggloves_torn", 1);
        remove_broken(1);
        return;
    }
    //collect the cost
    wearer->add_mana(-gg_mental_cost);

    //notify receipt    
    switch(w_mana_fac) {
        case 1: 
            wearer->catch_msg("Your palms feel slightly itchy.\n");
            break;
        case 2:
            wearer->catch_msg("Your palms feel itchy.\n");
            break;
        case 3:
            wearer->catch_msg("Your palms feel very itchy.\n");
            break;
        case 4:
            wearer->catch_msg("Your palms feel like a bug is " +
            "crawling over them.\n");
            break; 
        default:
            wearer->catch_msg("Your palms feel like they are " +
            "covered with fiery bugs.\n");
    }
    return;
}

mixed
wear(object ob)
{
    calc_cost();  

    //must pay the cost or fail to wear
    if(TP->query_mana() <= gg_mental_cost)
    {
        TP->set_mana(0);
        return "You struggle to get your hands inside these " +
        "gloves and can not understand why they will not fit.\n" +
        "You feel mentally exhausted.\n";
    }
    //collect the cost
    TP->add_mana(-gg_mental_cost);
   
    //add bonus extra skill 
    TP->set_skill_extra(SS_HERBALISM,
        TP->query_skill_extra(SS_HERBALISM) + gg_skill_inc);

    //set alarm to drain mana periodically
    gglove_alarm = set_alarm(gg_drain_delay + itof(random(120)),
        gg_drain_cycle + itof(random(30)), &glove_drain());

    TP->add_magic_effect(TO);

    TP->catch_msg("Your hands slide easily inside and a tingling " +
        "sensation in your fingertips begins to grow stronger.\n" +
        "You feel mentally drained.\n");
    say(QCTNAME(TP) + " wears the " + short() + ".\n");
    return 1;
}

mixed
remove(object ob)
{
    object wearer = query_worn();

    //stop the drain alarm
    remove_alarm(gglove_alarm);

    //remove bonus extra skill
    wearer->set_skill_extra(SS_HERBALISM,
        wearer->query_skill_extra(SS_HERBALISM) - gg_skill_inc);

    wearer->remove_magic_effect(TO);

    if(ob->query_prop("_ggloves_torn")) {
        wearer->catch_msg("You can no longer resist the urge to " +
            "scratch that itch!\nYou violently rip off the " +
            short() + " and scratch your palms furiously.\n");

        say(QCTNAME(wearer) +
            " suddenly rips off the " + short() +
            " tearing them to shreds in the process.\n", 0);
        return 1;
    }

    wearer->catch_msg("You tug at the fingers of the " + short() +
        " and manage pull your itchy hands free.\n");
    return 0;
}

int
add_prop_obj_i_broken(mixed value) {
    set_adj("broken");
    add_adj(({"torn", "shredded", "scrap"}));
    add_name(({"strips", "pieces", "pile"}));
    set_long("These strips of thick leather are covered " +
    "in layers of dirt and sticky resins. Whatever used to " +
    "bind the pieces into gloves is gone and now only a " +
    "small pile of scrap leather remains.\n");
    return 0;
}

void 
leave_env(object from, object to)
{
    ::leave_env();
    remove_alarm(gglove_alarm);
    return;
}

