// -*-C++-*-
// nausea potion    /d/Avenir/common/potions/anarex.c    
// creator(s):      Lilith  04/07/97
// purpose:         This vial/potion, when smelled or quaffed, will cause 
//                  a person to be unable to eat or drink for a period.
//                  Repeated doses will have no further effect.
// last update:
// note:
// bug(s):
// to-do:

inherit "/std/potion";

#include <herb.h>
#include <macros.h>
#include <stdproperties.h>
#include "/d/Avenir/include/paths.h"
#include "/d/Avenir/include/defs.h"

#define SPROP  "_Avenir_nausea_"

int istopr = 1;

string stopper_desc()
{
    if (istopr)
        return "There is a cork stopper in the neck of the vial.\n";
    if (!istopr)
        return "The vial has been opened.\n";
}

void
create_potion()
{
    set_name("anarex");
    add_name(({"_anarexia_potion","vial", "potion",}));
    set_short("vial of dark purple fluid");
    set_adj(({"purplish", "purple", "dark", "frothy", "noxious"}));

    set_potion_name("anarexanai");
    set_id_long("This is a glass vial containing a purplish, "+
       "noxious liquid that, when quaffed or opened, "+
       "will cause that individual to become nauseated and unable "+
       "to eat or drink for a while.\n"+ stopper_desc());
    set_unid_long("This is a glass vial containing a dark purple "+
       "fluid.\n"+ stopper_desc());

    add_item(({"liquid", "gaseous liquid", "fluid"}), 
        "This purplish fluid swirls of its own accord in the vial, "+
        "making you feel dizzy and nauseated just looking at it.\n");
    add_item(({"cork", "stopper", "neck"}), 
        "There is a cork stopper for keeping the liquid inside the "+
        "vial. You can pull the stopper from the vial to open it.\n");

    set_id_diff(30 + random(15));
    set_quaff_verb("drink");
    set_effect(HERB_SPECIAL, "nausea", 1);
    set_potion_value(400);

    set_soft_amount(4);
    set_alco_amount(15);

    add_prop(MAGIC_AM_ID_INFO, ({
        "When opened or quaffed, the contents of this vial will "+
        "cause a person to become so nauseated as to be unable to "+
        "ingest food or drink for quite some time.\n", 25,
        "Also, the gaseous liquid in this vial is highly unstable "+
        "when exposed to air. Within moments it will evaporate, "+
        "causing whoever is in possession of the vial to suffer "+
        "the nauseating effects.\n", 50 }));
    add_prop(OBJ_S_WIZINFO, "The contents of this vial will cause "+
        "an inability to ingest food or drink for a while.\n");
    seteuid(getuid());    
} 


/* 
 * Function name: special_effect
 * Description:   This is called by using  set_effect(HERB_SPECIAL) which is 
 *                apart of /lib/herb_support.h. 
 */
void 
special_effect()
{
    object ob;

    if (living(environment(this_object())))
        set_this_player(environment(this_object()));
    else
        return;

    if (TP->query_prop(SPROP))
    {
        write("You don't feel as though you have been affected by "+
            "the purplish gas.\n");
        return;
    }


    TP->add_prop(SPROP, 1);
    ob = clone_object(POTION +"special/nausea");
    ob->set_time(1000 + (random(150)));
    ob->move(this_player(),1);
    write("ACK! What an awful SMELL!\n");
    TP->command("$gag");

}    

/* 
 * Function name: dest_effect
 * Description:   Calls destruct_object for a delay
 */
void
dest_effect()
{
    write("A frothy purple fluid bubbles out of the vial.\n");
    say("A frothy greenish gas bubbles out of the vial.\n");
    set_alarm((7.0 + itof(random(7))), 0.0, destruct_object);
}

int
pull_it(string str)
{
    if (!str)
        return 0;

    notify_fail("Pull what? The stopper from the "+ short() +"?\n");
    if ( (!parse_command(str, ({ }),
            "[the] 'stopper' / 'cork' [from] [the] 'purple' 'vial' / 'potion' / 'neck'")) &&
         (!parse_command(str, ({ }), 
            "[the] 'stopper' / 'cork' / 'vial' / 'potion'")) )
        return 0;    

    if (!istopr)
    {
        write("The stopper has already been pulled. The vial is open!\n");
        return 0;
    }

    else
    {
        istopr = 0;
        write("You pull the stopper out of the vial, opening it.\n");                 
        say(QCTNAME(TP) +" pulls the stopper out of a "+ short() +".\n");
        dest_effect();
        return 1;
    }
}


/*
 * Function name: init
 * Description:   adds the quaff-action to the player
 */
void
init()
{
    ::init(); 

    add_action(pull_it, "pull");
    add_action(pull_it, "open");
    add_action(pull_it, "uncork");
}


