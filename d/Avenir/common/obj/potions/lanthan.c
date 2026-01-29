// -*-C++-*-
// Amnesia potion   /d/Avenir/common/potions/lanthan.c    
// creator(s):      Lilith  01/21/97
// purpose:         This vial/potion, when smelled or quaffed, will cause one 
//                  to forget ~5% of the remembered list. It can also be
//                  opened, in which case there are ~10.0 seconds before 
//                  the special effect is called. This means it is possible
//                  to give it to someone else and cause him to have amnesia. 
//                  Repeated doses will have no further effect.
// last update:     Lilith Feb 2020: Reduced to 5% of names being forgotten.
// note:
// bug(s):
// to-do:

inherit "/std/potion";
#include <herb.h>
#include <stdproperties.h>
#include <macros.h>
#define AMNESIA  "_Avenir_amnesia_"

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
    set_name("lanthan");
    add_name(({"_amnesia_potion","vial", "potion"}));
    set_short("vial of blue liquid");
    set_adj("blue");
    set_potion_name("lanthanesthai");
    set_id_long("This is a glass vial containing a blue, semi-"+
       "gaseous liquid that, when quaffed, smelled or opened, "+
       "will cause partial amnesia.\n"+ stopper_desc());
    set_unid_long("This is a glass vial containing a blue, semi-"+
       "gaseous liquid.\n"+ stopper_desc());
    add_item(({"gas", "liquid", "gaseous liquid"}), 
        "It is opaque blue and not-quite liquid. Its swirling movements "+
        "inside the vial remind you of something long-forgotten.\n");
    add_item(({"cork", "stopper", "neck"}), 
        "There is a cork stopper for keeping the liquid inside the "+
        "vial. You can pull the stopper from the vial to open it.\n");

    set_soft_amount(2);
    set_alco_amount(10);
    set_id_diff(40);
    set_quaff_verb("smell");
    set_effect(HERB_SPECIAL, "amnesia", 1);
    set_potion_value(1000);

    add_prop(MAGIC_AM_ID_INFO, ({
        "When smelled or quaffed, the contents of this vial will "+
        "cause partial amnesia.\n", 25,
        "Also, gaseous liquid in this vial is highly unstable if "+
        "exposed to air. Within moments it will evaporate, causing "+
        "whoever is in possession of the vial to suffer from "+
        "amnesia.\n", 50 }));
    add_prop(OBJ_S_WIZINFO, "The contents of this vial will cause "+
        "~5% loss of the remembered list (ie amnesia).\n");
} 

int
random_name(string name)
{
    if (random(20) == 0)    
        this_player()->remove_remembered(name);
    return 0;
}
/* 
 * Function name: special_effect
 * Description:   This is called by using  set_effect(HERB_SPECIAL) which is 
 *                apart of /lib/herb_support.h. 
 *                Causes loss of ~5% of names in the query_remembered map.
 */
void 
special_effect()
{
    if (living(environment(this_object())))
        set_this_player(environment(this_object()));
    else
        return;
 
    if (this_player()->query_prop(AMNESIA))
    {
        write("You don't feel as though you have been affected by "+
            "the blue gas.\n");
        return;
    }
    
    this_player()->add_prop(AMNESIA, 1);
    filter(m_indexes(this_player()->query_remembered()), random_name);
    write("Your ears suddenly feel very warm and your eyes begin to "+
        "water.\nYou feel lightheaded and befuddled.\n");
}    

/* 
 * Function name: dest_effect
 * Description:   Calls destruct_object for a delay
 */
void
dest_effect()
{
    write("A thin blue gas begins to waft from the vial.\n");
    say("A thin blue gas begins to waft from the vial.\n");
    set_alarm((7.0 + itof(random(7))), 0.0, destruct_object);
}

int
pull_it(string str)
{
    if (!str)
        return 0;

    notify_fail("Pull what? The stopper from the "+ short() +"?\n");
    if ( (!parse_command(str, ({ }),
            "[the] 'stopper' / 'cork' [from] [the] 'vial' / 'potion' / 'neck'")) &&
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
        say(QCTNAME(this_player()) +" pulls the stopper out of a "+ short() +".\n");
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


