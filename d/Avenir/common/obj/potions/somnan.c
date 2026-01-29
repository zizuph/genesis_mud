// -*-C++-*-
// Stun potion      /d/Avenir/common/potions/somnan.c    
// creator(s):      Lilith  01/30/97
// revisions:       Lilith  04/20/98: removed unwield functionality.
//                  Lilith Feb 2022: reduced stun time to 5+random(6) seconds.
// purpose:         This vial/potion, when smelled or quaffed, will cause 
//                  an add_attack_delay of 5 + random(6) seconds when
//                  opened, in which case there are ~10.0 seconds before 
//                  the special effect is called. This means it is possible
//                  to give it to someone else and cause him to be stunned. 
// note:            Repeated doses will have no additional effect.
// bug(s):
// to-do:

inherit "/std/potion";
#include <herb.h>
#include <stdproperties.h>
#include <macros.h>
#define SOMNAN_STUNNED  "_Avenir_somnan_stunned_"

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
    set_name("somnan");
    add_name(({"_stunning_potion","vial", "potion"}));
    set_short("vial of greenish gas");
    set_adj(({"green", "greenish", "virulent", "frothy"}));
    set_potion_name("somnanesthai");
    set_id_long("This is a glass vial containing a greenish, semi-"+
       "gaseous liquid that, when quaffed, smelled or opened, "+
       "will cause the owner to be stunned.\n"+ stopper_desc());
    set_unid_long("This is a glass vial containing a greenish, semi-"+
       "gaseous liquid.\n"+ stopper_desc());
    add_item(({"gas", "liquid", "gaseous liquid"}), 
        "It is a stunning and virulent green frothy gas that is in "+
        "constant, ominous motion.\n");
    add_item(({"cork", "stopper", "neck"}), 
        "There is a cork stopper for keeping the liquid inside the "+
        "vial. You can pull the stopper from the vial to open it.\n");

    set_soft_amount(4);
    set_alco_amount(15);
    set_id_diff(30 + random(15));
    set_quaff_verb("smell");
    set_effect(HERB_SPECIAL, "stunned", 1);
    set_potion_value(1000);

    add_prop(MAGIC_AM_ID_INFO, ({
        "When smelled or quaffed, the contents of this vial will "+
        "cause a person to be stunned enough to disable him or "+
        "her in combat.\n", 25,
        "Also, the gaseous liquid in this vial is highly unstable "+
        "when exposed to air. Within moments it will evaporate, "+
        "causing whoever is in possession of the vial to suffer "+
        "from a combat-disabling stun.\n", 50 }));
    add_prop(OBJ_S_WIZINFO, "The contents of this vial will cause "+
        "add_attack_delay(5 + random(6)).\n");

} 


/* 
 * Function name: special_effect
 * Description:   This is called by using  set_effect(HERB_SPECIAL) which is 
 *                a part of /lib/herb_support.h. 
 *                causes add_attack_delay
 */
void 
special_effect()
{
    if (living(environment(this_object())))
        set_this_player(environment(this_object()));
    else
        return;

    /* Player is immune to the effects of the potion*/
    if (this_player()->query_prop(SOMNAN_STUNNED))
    {
        write("You don't feel as though you have been affected by "+
            "the greenish gas.\n");
        return;
    }
    /* Add this prop to make sure player is immune to future potions */
    this_player()->add_prop(SOMNAN_STUNNED, 1);    
    this_player()->add_attack_delay(5 + random(6));
    write("You feel sluggish and so peculiar that you will be useless "+
        "in a fight.\nHopefully this feeling will quickly pass.\n");
}    

/* 
 * Function name: dest_effect
 * Description:   Calls destruct_object for a delay
 */
void
dest_effect()
{
    write("A frothy greenish gas bubbles out of the vial.\n");
    say("A frothy greenish gas bubbles out of the vial.\n");
    set_alarm((7.0 + itof(random(7))), 0.0, destruct_object);
}

int
pull_it(string str)
{
    if (!str)
        return 0;

    notify_fail("Pull what? The stopper from the "+ short() +" vial?\n");
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


