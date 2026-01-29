/*  /d/Raumdor/common/beach/bountiful/chest_rewards/shadowy_platemail.c
 *
 *  The black platemail equivalent - Same properties,  but will
 *  instead resist vs life magic.
 *
 *  Nerull, 2021
 *
 */

inherit "/std/armour";
#include "../defs.h";
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>

string wizinfo();

void
create_armour()
{
    set_name("platemail");
    set_adj("shadowy");
    add_adj("steel");

    set_short("shadowy steel platemail");
    set_pshort("shadowy steel platemail");

    set_long("After examining the platemail you notice it's "
    +"not just a regular platemail. The front is curved "
    +"slightly to deflect blows. In the center of the platemail "
    +"a bright blut thin line runs down, from top to bottom. The "
    +"side and back pieces are all in a unnatural blackish color. The "
    +"inside is laced with a strange fabric, that is cold to the"
    +"touch. Looking at this armour almost hyptnotizes "
    +"you.\n");
    
    add_item(({ "line", "small line", "bright line", "small blue line", 
    "blue line", "bright blue line",}), "A small bright blue line runs "
    +"down the center of the platemail. It shimmers slightly and is rather "
    +"difficult to focus on.\n");
    
    add_item(({"fabric", "strange fabric", "lace", "laced fabric"}),"An "
    +"odd looking fabric lines the inside of this armour. It radiates "
    +"cold and is slightly painful to touch. It has no colour, at least "
    +"none that can be described, and it seems to shift and fold in upon "
    +"itself.\n");
    
    add_item(({"back piece", "side piece", "pieces", "side pieces",
    "back pieces", "unnatural blackish color","blackish color",
    "black color"}),"The side and back pieces of this platemail are a "
    +"different color than the rest of it. The black seems as though it "
    +"has been corrupted or changed, it is wholly unnatural and out of "
    +"place.\n");

    set_default_armour( 50, A_BODY, ({ -3, 2, 1 }), this_object() );
    add_prop( OBJ_I_VALUE,F_VALUE_ARMOUR( 50 )+ random( 1000 )+ 500 );
    add_prop( OBJ_M_NO_BUY, 1 );
    add_prop( OBJ_I_WEIGHT, 8800 + random(200) );
    add_prop( OBJ_I_VOLUME, query_prop( OBJ_I_WEIGHT )/ 6 );

    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);

    add_prop(MAGIC_AM_MAGIC, ({ 10, "enchantment" }));

    add_prop( MAGIC_AM_ID_INFO,
    ({
        "The shadowy steel platemail seems to be magically strengthened. ", 1,
        "Some of this strength is put into the steel itself " +
        "which is hammered really thin to reduce some weight, yet " +
        "being as strong as a regularly made platemail. ", 10,
        "Though it is enhanced the piercing blows will still penetrate " +
        "but the slashing and bludgeoning hits that would land on this " +
        "great armour would have a harder time penetrating through onto " +
        "the wearer. ", 30,
        "It is magically enhanced to protect the wearer against magical spells.", 40,
        "More specifically the shadowy steel platemail protects against the " +
        "magical energies of life.", 65,
        "\n", 1
    }) );
        
    add_prop( OBJ_S_WIZINFO, wizinfo );
    add_prop( MAGIC_I_RES_LIFE, 100 );
    add_prop( MAGIC_I_RES_LIFE, ({ 33, 0 }) );
                                /*Let us reduce the number of glowing
                                 *platemails a bit.                       */
    if (random( 1 ))
    {
        set_may_not_recover();
    }
}


string wizinfo()
{
    return "A platemail forged by lich Gylar in Raumdor. \n"+
        "Magically strengthened against life spells. \n" +
        "MAGIC_AM_MAGIC    : " + query_prop(MAGIC_AM_MAGIC)[0] + "%, "
                               + query_prop(MAGIC_AM_MAGIC)[1] + "\n" +
        "MAGIC_I_RES_LIFE : 33%, additive.\n";
}


public mixed wear( object obj )
{
    object tp = environment( this_object() );
    
    if ((tp != this_player()) || (obj != this_object()))
    {
        return -1;
    }
    
    if (living( tp ))
    {
        tp->add_magic_effect( this_object() );
    }
    
    return 0;
}


public mixed remove( object obj )
{
    object tp = query_worn();
    
    if ((tp != this_player()) || (obj != this_object()))
    {
        return -1;
    }
    
    if (living(tp))
    {
        tp->remove_magic_effect( this_object() );
    }
    
    return 0;
}


mixed query_magic_protection( string prop, object for_what =
    previous_object() )
{
    object tp = query_worn();
 
    if (for_what == tp)
    {
        switch (prop)
        {
        case MAGIC_I_RES_LIFE:
            return ({ 33, 1 });
        }
    }
    
    return ::query_magic_protection( prop, for_what );
}
