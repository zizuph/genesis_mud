/*********************************************************************
 * - altar.c                                                       - *
 * - Include this file if you want altar functions                 - *
 * - remember to add: init_altar();                                - *
 * - to your init                                                  - *
 * - Created by Damaris 3/2004                                     - *
 *********************************************************************/
#pragma strict_types
#include <cmdparse.h>
#include <composite.h>
#include <filter_funs.h>
#include <macros.h>
#include <stdproperties.h>
#include "../guild.h"

/*
 * Function name: fade1
 * Description  : Description of the apparation fading
 */
void
fade1(void)
{
    write("The apparition fades leaving you filled with strength and hope.\n");

}

/*
 * Function name: dpray3
 * Description  : Random messages from prayer
 */
int
dpray3(string str)
{
    string *msg1= ({
      "Blessed are you my child.",
      "Blessed are you who seek justice.",
      "Blessed are you, thou art my beloved faithful child.",
      "Thou art worthy of greatness my child.",
      "Always seek the truth my beloved child.",
      "Let no one sway you from truth my child.",
      "Spread the truth to all who might learn my child.",
      "Depart from the demi-humans and become great my child.",
      "Follow the path of righteousness my child.",
      "Let no one deter you from truth my child."}),
           *msg2= ({
      "Righteousness is within your grasp.",
      "Justice is within your grasp.",
      "Virtue is within your grasp.",
      "Integrity is within your grasp.",
      "Graciousness is within your grasp.",
      "Honor is within your grasp.",
      "Strength is within your grasp.",
      "Vigor is within your grasp.",
      "Concentration is within your grasp.",
      "Power is within your grasp.",
      "Control is within your grasp.",
      "Dominance is within your grasp."});
     write("Lord Thanar speaks to you: "+
      ""+msg1[random(sizeof(msg1))] + " " + msg2[random(sizeof(msg2))] + " "+
      "I am with you always.\n");
      set_alarm(3.0, 0.0, fade1);
}

/*
 * Function name: dpray2
 * Description  : Second message from pray string
 */
void
dpray2(void)
{
    write("An apparition of the almighty Lord Thanar appears "+
      "before you.\n");
    set_alarm(2.0, 0.0, dpray3);
}

/*
 * Function name: dpray1
 * Description  : Initial prayer message
 */
public int
dpray(string s)
{
    write("You offer up faithful prayers to Lord Thanar.\n");
    set_alarm(2.0, 0.0, dpray2);
    return 1;
}

public void
init_altar()
{

    add_action(dpray, "dpray");
}
