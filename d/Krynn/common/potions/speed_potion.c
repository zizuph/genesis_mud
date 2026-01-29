/*
*
* Even more modified by Vencar for the use in palanthas.
*
* Modified from /d/Krynn/common/potions/quenta.c
* By Arman 16/10/97
 *
 * modified from Olorin's ipotion.c, by Teth Jan 1997
 */
#pragma strict_types

#include <ss_types.h>
#include "potion_defs.h"
inherit "/std/potion.c";
#include <herb.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"

public void
create_potion()
{
    set_potion_name("sahavuli potion");
    add_name("potion");
    set_short("dark mirky potion");
    set_adj("dark");
    add_adj("mirky");
    set_pshort("dark mirky potions");
    /* The potion's true name, used when mixing the potion. */
    set_id_long("A gnomish mixup of some dark mirky, " +
      "chemicals, or at least thats how it look at first " +
      "glance. The liquid swirls around itself in " +
      "a strange but very rapid fashion. " +
      "To create the potion, one would require some gnomish " +
      "materials, a gnome-mix-o-matic, and a good bit of luck. " +
      "The potion would probably make your actions quicker, " +
      "but you might not be as good at thinking about those " +
      "actions.\n");

    /* Set the long description if identified. */
    set_unid_long("A gnomish mixup of some dark mirky, " +
      "chemicals, or at least thats how it look at first " +
      "glance. The liquid swirls around itself in " +
      "a strange but very rapid fashion.\n");
    /* Set the long description if unidentified. */
    set_id_taste("Aaaaahhh this tastes great! " +
      "You feel a quickness to your limbs, making everything " +
      "much slower around you. You think you might taste " +
      "some bitter chemicals mixed with strong alcohol.\n");
    /* Set the taste if identified. */
    set_unid_taste("Aaaaahhh this tastes great! " +
      "You feel a quickness to your limbs, making everything " +
      "much slower around you!\n");
    /* Set the taste if unidentified. */
    set_id_smell("This potion smells of strong alcohol " +
       "mixed together with dark chemicals.\n");
    /* Set the smell if identified. */
    set_unid_smell("The potion smells of alcohol, strong " +
       "alcohol.\n");
    /* Set the smell for those who can't identify it. */
    set_id_diff(14);
    /* How hard is it to identify? */
    set_soft_amount(150);
    /* What is the amount of liquid in mL? */
    set_alco_amount(240);
    /* How much alcohol in the potion? Alcohol is needed for */
    /* potions to go ;-)  */
    set_potion_value(SPEED_POTION_COST);

    add_prop(OBJ_I_VALUE, SPEED_POTION_COST);
    /* approx 45 plats should make it worth it! */

    set_effect(HERB_SPECIAL, "speed", 1);
    /* Set the effect */

    add_prop(MAGIC_AM_MAGIC,({ 20, "enchantment"}));
    add_prop(MAGIC_AM_ID_INFO,({"This potion has been brewed "+
             "with the use of gnome magic. Quafing it will make you move faster.\n",15}));
}

public void
special_effect()
{
  object ob;
  
  if (P("_speed_obj",TP))
    {
      write("Ahhhh, You already feel hasted enough, any more " +
	    "haste would burst you into pieces.\n");
      return ;
    }
  seteuid(getuid());
  ob = clone_object(SPEED_OBJ);
  ob->set_duration(SPEED_POTION_TIME);
  ob->set_target(TP);
  if (ob->move(TP))
    ob->move(TP, 1);

    
    log_file(POTION_EFFECT_LOG, ctime(time()) + " " +
	     this_player()->query_name() + " got hasted by speed_potion.\n");
}
