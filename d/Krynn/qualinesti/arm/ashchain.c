/* 
 * File: ashchain.c
 * The ash-grey chainmail worn by Qualthas. Such armours are granted
 * to very brave elves so I give bonus armour class of 5 to those with 
 * elven blood. It also increases fire resistance by 30.
 * People with average stat lower than 70 are not worthy to wear it.
 *
 * Blizzard, 02/2003
 * 
 *
 * Note by Navarre, November 22th 2005:
 *
 * This item was one of many inappropriate items that was created.
 * The armour adds too much fire-resistance, so I lowered it to 10.
 */
 
inherit "std/armour.c";
inherit "/lib/keep";

#include <wa_types.h>
#include <macros.h>
#include <formulas.h>
#include "/d/Krynn/common/defs.h"

void
create_armour()
{
    set_name("mail");
    set_short("ash-grey scaled splint mail");
    add_adj(({ "ash-grey", "scaled", "elven", "splint" }));
    set_ac(45);     
    set_am( ({-1, 2, -1}) );
    set_af(TO);
    set_at(A_BODY);
    set_long("This strong mail is of Qualinesti elf construction, " +
        "and therefore its elegance is only exceeded by its rarity. " +
        "Instead of metal strips, this armour uses wyvern scales bound " +
        "to a chain backing by means of a magical fire. The resulting " +
        "armour is ash-grey in colour and more flexible than standard " +
        "splint mail. It is also surprisingly light. " +
        "Normally granted only to especially brave elves, " +
        "seldom is this armour found outside of their kingdom, and " +
        "rarer still on someone not of elven lineage.\n");
    set_keep(1);
    
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(OBJ_S_WIZINFO, 
        "Thanks to wyvern scales bound to this armour it provides " +
        "resistance against fire (10). This is an elven item and those " +
        "of elven blood will receive additional AC of 5 while " +
        "wearing it. People with average stat below 70 can not wear it.\n");
    add_prop(MAGIC_AM_ID_INFO,
        ({"Only those, who proved themselves in battle may wear this " +
        "armour.\n", 5,
        "This is a magical elven armour and only those of elven blood " +
        "know its real worth.\n", 20,
        "Wyvern scales used in this armour provide protection against " +
        "fire.\n", 40}) );        
    add_prop(MAGIC_AM_MAGIC, ({ 80, "enchantment" }) );

    add_prop(OBJ_M_NO_BUY, "Such priceless items are not for sale!\n");
    add_prop(OBJ_I_WEIGHT, 9000);
    add_prop(OBJ_I_VOLUME, 7500);
    add_prop(OBJ_I_VALUE, 10);
}

varargs mixed
query_magic_protection(string prop, object what)
{
    if ( what == query_worn() && prop == MAGIC_I_RES_FIRE )
        return ({ 10, 1 });
    
    return ::query_magic_protection(prop, what);
}

mixed
wear(object what)
{
    if ( TP->query_average_stat() < 70 )
    {
        say(QCTNAME(TP) + " attempts to wear the " + what->short() +
            ", but it doesn't seem to fit " + OBJECTIVE(TP) + ".\n");
        return "You try to wear the " + what->short() + ", but you " +
            "do not seem to be worthy of it.\n";
    }
                
    if (TP->query_race_name() == "elf" || TP->query_race_name() == "half-elf")
    {
        TP->catch_msg("You wear the " + what->short() + ". To your " +
            "satisfaction it fits you perfectly.\n");
        say(QCTNAME(TP) + " wears the " + what->short() + ", which " +
        "seems to fit " + OBJECTIVE(TP) + " perfectly.\n");

        TP->add_magic_effect(TO);
        set_ac(50);
        wearer->update_armour(TO); 
        
        return 1;
    }
    
    TP->add_magic_effect(TO);

    return 0;
}    

mixed
remove(object what)
{
    wearer->remove_magic_effect(TO);
    set_ac(45);
    
    return 0;
}
     
