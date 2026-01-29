// FOOD:  ham_cooked

    /* Calia Domain

    HISTORY

    [99-07-07] Created by Uhclem from
    [D:\CALIA\CENTRAL\BOG\OBJECTS\HAM_SLIC.DOC].

    PURPOSE

    A large glazed ham ready for eating, anywhere from 5 to 10 kilos, whole if
    you have a truly monstrous appetite or sliced if you don't.  Slicing
    requires a good sharp knife. */

// INCLUSIONS AND DEFINITIONS

inherit "/std/food";

#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <options.h>

// OBJECT DEFINITION

void
create_food()

{

    /*
     *  DESCRIPTION    
     */

    set_long("The ham is thinly sliced and" +
        " coated with a" +
        " tempting, sweet, glistening glaze.\n");

    set_short("slice of ham");
    set_pshort("slices of ham");
    add_name("slice");
    add_name("ham");

    /*
     *  PROPERTIES    
     */

    /*
     *  These properties are dummy values to be used if a wizard should clone 
     *  this item for personal use. In the game, the ham_cooked object clones
     *  this one when it is sliced and sets all the slice properties to be
     *  consistent with the whole ham.    
     */

    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VOLUME, 175);
    add_prop(OBJ_I_VALUE, 29);
    set_amount(200);
    set_heap_size(1);

    add_prop(OBJ_M_NO_SELL, "Sell a slice of ham? And where" +
        " have you been keeping it, pray tell - rolled up" +
        " in your boot?\n");

    /*
     *  ITEMS    
     */

    add_item(({"glaze", "glistening glaze", "cloves", "clove",
        "edge", "outer edge"}),
        "The glaze coats the outer edge of the slice and is" +
        " studded with a few cloves.\n");

}

// FUNCTIONS

// Function:  special_effect(num)

/*

Purpose:  add taste characteristics to this object.

Arguments:  int num, number of items eaten.

Returns:  nothing.

*/

void
special_effect(int num)

{

    /*
     *  The flavors are inspired by a maple and bourbon glazed ham prepared in 
     *  a Washington area shop, Sutton Place Gourmet.  Those of you on the
     *  other side of the pond can find worthy competitors in the Selfridge
     *  food hall, London.    
     */

    if (num == 1)

    {

        /*
         *  You only get to enjoy the taste if you eat the ham by itself.  If 
         *  you stuff it into your mouth along with other items with an 'eat
         *  all' command, I assume you're not interested.    
         */

        write(({"The promise of the fragrance is fulfilled in the" +
            " taste! The meat is tender and marbled," +
            " and its delicate natural flavor is enhanced by" +
            " the contrasting maple and whiskey flavors" +
            " in the glaze.\n",
            "First the startling flavor of the glaze hits" +
            " your tongue, an unexpected pairing of sweet maple" +
            " sugar and well-aged whiskey, but it complements" +
            " the natural delicate taste of the meat and" +
            " leaves a lingering, agreeable aftertaste.\n",
            "Tastes of delicate salt-cured ham, sweet maple" +
            " sugar, and robust oak-aged whiskey fill your mouth all" +
            " at once, a tumult of flavors that quickly merge" +
            " into a mellow, satisfying union that lingers after" +
            " the ham is consumed.\n"})[random(3)]);

    }

}

// Function:  hook_smelled()

/*

Purpose:  add smell characteristics to this object.

Arguments:  none.

Returns:  nothing.

*/

void
hook_smelled()

{

    write("The freshly-cut slice affords a variety of" +
        " tantalizing aromas, the delicate natural" +
        " aroma of the salt-and-sugar-cured ham enhanced by" +
        " pungent traces of whiskey, clove, and mustard" +
        " in the glaze.\n");

}
