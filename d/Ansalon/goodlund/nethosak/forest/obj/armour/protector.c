/*****************************************************************
 * Name: ornate full platemail 'Protector'                       *
 * Stats: Ac 47.                                                 *
 * By: Elmore.                                                   *
 * Date: 15/11 2000                                              *
 * Description: This is the legendary artifact 'Protector'. This *
 *    relic has been blessed by Mishakal the Goddess of Healing. *
 *    The armour will add and description to the player.         *
 *                                                               *
 * Limit: 1 each armageddon.                                     *
 *****************************************************************/ 

inherit "/std/armour";
inherit "/lib/keep";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"

#define SUBLOC "protector_subloc"

nomask void
create_armour()
{
    set_name("platemail");
    add_name("protector");
    set_ac(49);
    set_at(A_BODY | A_ARMS | A_LEGS);
    set_af(TO);
    add_adj(({ "ornate", "full"})); 
    set_short("ornate full platemail");
    set_long("This marveleus piece of armour is abolutely breathtaking. Forged "+
             "from the hardest of steel in Krynn and coated in the purest of "+
             "silver, this armour most be the legendary artifact 'Protector'. "+
             "The body-armour part of this armour is covered with ornate "+
             "carvings of an epic battle between good and evil, these carvings "+
             "have been made out of thin gold lines and small emeralds. The "+
             "entire armour is flawless and completely clean, even though it "+
             "must have been made for centuries ago, perhaps even before the "+
             "Cataclysm.\n");
    set_keep(1);
    add_prop(OBJ_I_LIGHT,5);
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_VOLUME, 11040);
    add_prop(OBJ_I_WEIGHT, 10500);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(45) + 5000); 
}



mixed 
wear(object what)
{
    write("Your body is surrounded by a sphere of energy.\n");
    TP->add_subloc(SUBLOC, TO);
    set_long("This marveleus piece of armour is abolutely breathtaking. Forged "+
             "from the hardest of steel in Krynn and coated in the purest of "+
             "silver, this armour most be the legendary artifact 'Protector'. "+
             "The body-armour part of this armour is covered with ornate "+
             "carvings of an epic battle between good and evil, these carvings "+
             "have been made out of thin gold lines and small emeralds. The "+
             "entire armour is flawless and completely clean, even though it "+
             "must have been made for centuries ago, perhaps even before the "+
             "Cataclysm. As you are wearing the platemail, you feel protected "+
             "by Mishakal the Goddess of Healing.\n"+
             "You realize that this platemail must have been made for the High "+
             "Priest of Ishtar, however the legend says that this platemail was "+
             "lost during the transportation from the elven home of Silvasti to "+
             "Ishtar. Years later the platemail reemerged but only to be lost again.\n");
    update_state();
    set_alarm(10.0,182.4, &write("The "+short()+" sends out a bright "+
                                   "white light. Illuminating the area.\n"));
    return 0;
}


mixed
remove(object what)
{
    write("The sphere of energy surrounding your body disappears.\n");
    TP->remove_subloc(SUBLOC);
    set_long("This marveleus piece of armour is abolutely breathtaking. Forged "+
             "from the hardest of steel in Krynn and coated in the purest of "+
             "silver, this armour most be the legendary artifact 'Protector'. "+
             "The body-armour part of this armour is covered with ornate "+
             "carvings of an epic battle between good and evil, these carvings "+
             "have been made out of thin gold lines and small emeralds. The "+
             "entire armour is flawless and completely clean, even though it "+
             "must have been made for centuries ago, perhaps even before the "+
             "Cataclysm.\n");
    update_state();
    return 0;
}

string
show_subloc(string subloc, object carrier, object for_obj)
{
    string str;

    if (carrier->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return "";

    if (for_obj == carrier)
        str = "Your body ";
    else
        str = capitalize(carrier->query_pronoun()) + " body ";

    return str + "is surrounded by a bright white sphere of energy.\n";
}
