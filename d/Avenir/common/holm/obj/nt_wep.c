/*  file name:        /d/Avenir/common/holm/t_camp/nt_wep.c
 *  creator(s):       (Rangorn , Feb 97)
 *  revisions:        Lilith, 11/05/97 (changed to polearm)
 *  purpose:
 *  note:
 *  bug(s):
 *  to-do:
 */                                                                            

inherit "/d/Avenir/inherit/weapon";

#include "../holm.h"
#include <formulas.h>
#include <ss_types.h>
#include <wa_types.h>

void
create_weapon()
{
    set_name("polearm");
    add_name(({"bardiche", "weapon"}));
    set_adj(({"bright", "half-moon", "halfmoon"}));    
    set_short("bright half-moon bardiche");
    set_long("The blade of this bardiche is as long as your arm. One end of "+
           "the blade curves back toward the haft, forming a ring through "+
           "which the kesoit pole passes before fitting snugly into the wedge-"+
           "like head. The blade arcs to a deadly point a handspan beyond, "+
           "its steel gleaming so brightly it is almost luminous.\nYou feel "+
           "a strong urge to try and swing the bardiche through the air.\n");           


    set_hit(35);
    set_pen(38);
    set_wt(W_POLEARM);
    set_dt(W_IMPALE);
    set_hands(W_BOTH);
   
    // The wep provides a light source of 1 , this is not a magical attribute.
    // It just reflects that traces of the Source has been forged into it.
    add_prop(OBJ_I_LIGHT, 1);
}

int
swing_me(string str)
{
    object tp = this_player();  
    object to = this_object();
    object ob;
    string player_message, wiever_message;  
    int i;

    // Check if player is wielding this weapon.
    if (!to->query_wielded())
    {
        notify_fail("Swing what?\n");
        return 0;
    }

    if (str != query_short() && str != "bardiche" && str != "bright bardiche" &&
        str != "polearm")
    {
        notify_fail("Swing what?\n");
        return 0;
    }

    i = tp->query_skill(SS_WEP_POLEARM);
    switch (i)
    {
        case 0..40:
            write("You swing the "+ short() +" so fiercely that it "+
                "flies from your inexperienced hands and lands on the ground "+
                "with a thud!\n");  
            say(QCTNAME(tp) + " swings the "+ short() +" so fiercely that "+
                "it flies from "+ tp->query_possessive() +" hands and lands "+ 
                "on the ground with a thud!\n");
            to->move(environment(tp));
            return 1;
            break;
        case 41..60:
            write("You brace your feet well-apart and swing the "+ short() +
                " in a wide arc that sends light flashing off the blade.\n");
            say(QCTNAME(tp) + " swings "+ tp->query_possessive() +" "+ short() +
                " before "+ tp->query_objective() +" in a wide arc that sends "+
                " light flashing off the blade.\n");
            return 1;
            break; 
        case 61..88:
            write("With a couple of fluid and well-coordinated motions, you "+
                "swing your "+ short() +" in a fast circle above your head.\n"+
                "The blade disturbs the air with a humming 'whoosh' and "+
                "scatters flashes of light everywhere.\n");
            say(QCTNAME(tp)+" swings "+ tp->query_possessive() +" "+ short() +
                " in a fast circle above "+ tp->query_possessive() +" head.\n"+
                "The blade disturbs the air with a humming 'whoosh' and "+
                "scatters flashes of light into your eyes.\n");
            return 1;
            break;
        case 89..100:
            write("You swing your "+ short() +" in a series of arcs and circles "+
                "with a fluid economy of movement. The grace and speed with "+
                "which you swing it creates a glowing pattern of "+
                "light in the air.\nUsing your strong, flexible wrists to full "+
                "advantage, you dramatically change the "+ short() +"'s path in "+
                "mid-swing, forcing the butt to descend toward the ground and "+
                "the pole to flip back to rest against your shoulder, the blade "+
                "humming near your ear.\n");  
            say(QCTNAME(tp) + " swings "+ tp->query_possessive() +" "+ short() +
                " with a fluid economy of movement, creating a glowing pattern "+
                "of light in the air as "+ tp->query_pronoun() +" spins it a "+
                "series of arcs and circles.\nWith a stunning display of "+
                "dexterity and skill, "+ QCTNAME(tp) +" stops the "+ short() + 
                "in mid-swing and flips it back to rest against "+ 
                tp->query_possessive() +" shoulder, the blade still humming!\n");
            return 1;
            break;
    }     
}

void
init()
{
    ::init();
    add_action(swing_me, "swing");
}

