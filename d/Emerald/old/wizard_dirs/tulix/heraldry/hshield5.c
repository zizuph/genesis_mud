/* A Heraldic shield - another classic from Tulix's Armoury inc. */
/* This is a nice little shield to be returned to the owner.     */
/* coded 16/4/1993 */

inherit "/std/armour";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/macros.h"                               

void
create_armour()
{
    /* Set name, short description and long description */
    set_name("shield");
    set_short("heraldic shield"); /* Yup. Its a heraldic shield */
    set_long(break_string("It is a heraldic shield. It was not designed for "  
        + "combat, being too elaboratly decorated for use in a fight. "
        + "The shield is thin metal, which has been carefully painted with "
        + "a rampant silver pegasus on a blue background. The pegasus has a "
        + "ring "
        + "superimposed above it. You feel the urge to return it "
        + "to its rightful owner.\n",75));

    /* Better add an adjective */
    set_adj("heraldic");

    /* Nice to know which shield it is */
    add_name("ring shield");

    /* Set armour class */
    set_ac(10);

    /* Set slash,impale,bludgeon, modifiers.  */
    set_am(({   0,   1,  -1}));
    set_at(A_SHIELD);
    
    /* Set physical attributes */    
    add_prop(OBJ_I_WEIGHT, 2500); /* shield weighs 2.5 kg        */
    add_prop(OBJ_I_VOLUME, 800);  /* shield takes up 0.8 litres  */
    add_prop(OBJ_I_VALUE, 2000);  /* shield is expensive 2000 cc */
    add_prop(OBJ_S_WIZINFO, "@@wizinfo");
    add_prop(OBJ_M_NO_SELL, "You cannot sell something so precious!\n");
    add_prop(OBJ_M_NO_BUY, "There are some things which money cannot buy.\n");
    add_prop(OBJ_I_NO_STEAL, 1);
    add_prop(OBJ_M_NO_DROP, "You cannot drop such a precious item.\n");
}

/* Better make it recoverable in these days of short up times. */
string
query_recover()
{
    return "/d/Emerald/tulix/heraldry/hshield5" + ":" +
        query_arm_recover();
}

void
init_recover(string arg)
{
    init_arm_recover(arg);
}

string
wizinfo()
{
    return "This shield is a quest item for the Heraldry quest in Emerald.\n"
    + "It cannot be sold, but can be dropped. For more info on the quest,"
    + " see Tulix.\n";
}
