#include "/d/Terel/include/Terel.h"

inherit STDARMOUR;

#include <wa_types.h>

public void
create_terel_armour()
{
    set_name(({"shield","shield of kalth"}));
    set_short("large silver shield");
    set_long("A large finely crafted silver shield. By the intricate "+
                   "craftsmanship you'd guess it was made by elves. "+
                   "The shield is unnaturally light, and quite easy to "+
                   "use.\n");
    add_prop(OBJ_I_IS_MAGIC_ARMOUR,1);
    add_prop(MAGIC_AM_MAGIC,({ 40, "enchantment"}));
    add_prop(MAGIC_AM_ID_INFO,({10,"This shield was forged long ago in the "+
             "time of elves.\n",30,"It has been enchanted to enhance "+
             "protection from physical blows.\n",80,"The shield can only be "+
             "worn by those of elven blood, or pure of heart.\n"}));
    add_prop(OBJ_M_NO_BUY,1);
    add_prop(OBJ_I_VALUE, 10000);
    add_prop(OBJ_I_WEIGHT,10000);
    set_adj(({"silver","large"}));
    add_prop(OBJ_S_WIZINFO,"This is the shield of Kalth. It provides "+
                 "protection of 45 to the body, legs, head, and left arm. It "+
                  "can only be worn by elves or people with alignments of 1200."+
                    "This is the treasure from the giant troll in the troll "+
                     "caves of Terel. /d/Terel/common/moor/tcaves/ \n");


    set_default_armour(45,A_SHIELD, 0, TO);
    set_armour_size(MEDIUM);

}

int *
query_shield_slots()
{
    return (::query_shield_slots() +({A_BODY,A_HEAD,A_LEGS}));
}

public mixed
wear_terel_armour(object obj)
{
    if(TP->query_race_name() == "elf" || TP->query_alignment() == 1200)
    {
        write("You wear the "+short()+" on your right arm.\n");
        say(QCTNAME(TP)+" wears the "+short()+" on "+POSSESSIVE(TP)+" right arm.\n");
        return 1;
    }
    write("You are burned as you try to wear the "+short()+"!\n");
    say(QCTNAME(TP)+" is burned as "+PRONOUN(TP)+" tries to wear the "+ 
                short()+"! \n");
    TP->heal_hp(-500);
    return -1;
}

