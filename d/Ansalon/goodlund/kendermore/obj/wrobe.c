/* Sateela's Robe, by Gwyneth, 06/16/99 */
/* Modfied by Vitwitch to include MAGIC props descriptors */

inherit "/std/armour";
inherit "/lib/keep";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"


int worn;

void
create_armour()
{
    set_name("robe");
    set_short("silky black robe");
    set_pname("robes");
    set_pshort("silky black robes");
    set_adj("silky");
    add_adj("black");
    set_long("The material of this silky black robe feels soft and light " + 
        "to your touch. You detect a slight shimmering aura surrounding " + 
        "this robe.\n");
    set_ac(5);
    set_at(A_ROBE);

   add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);

   add_prop(OBJ_S_WIZINFO,"This is a magical robe which causes " +
       "the wearers' appearance_offset to be set to -50, making " +
       "them appear very attractive. When it is removed, the " +
       "appearance offset is set to +50, making the non-wearer "+
       "hideous. This effect is permanent unless the offset is "+
       "reset through some other agency (eg. Robe of Woven Worms).\n");

  add_prop(MAGIC_AM_ID_INFO,
       ({"This robe is the product of divine divising. Wearing it "+
       "causes all the natural beauty of the wearer to be drawn in " +
       "and magnified.\n", 20, 
       "This robe is the product of Takhsis. Wearing it "+
       "causes all the natural beauty of the wearer to be drawn in " +
       "and magnified. Unfortunately, the robe retains this beauty "+
       "even when it is removed, leaving the mortal more ugly.\n", 30 }) );

    add_prop(OBJ_I_VALUE, 120);
    add_prop(OBJ_I_VOLUME, 200);
    add_prop(OBJ_I_WEIGHT, 300);

    set_af(TO);
    seteuid(getuid(TO));

    worn = 0;
}

/* Function name : Wear
 * Description : When worn by a female, this robe will make her look like 
 *     the image of perfection. Sets worn status to true.
 * Returns : 0 and 1
*/

mixed
wear(object what)
{
    if (what != TO)
        return 0;

    if(TP->query_gender()==1)
    {
        write("You slip on the silky black robe. It clings to your body, " + 
            "and you suddenly feel more confident. You toss your hair over " + 
            "your shoulder.\n");
        say(QCTNAME(TP) + " slips on the silky black robe. It clings to her " + 
            "body, and your eyes are drawn to her. She confidently tosses " + 
            "her hair over her shoulder.\n");

        TP->set_appearance_offset(-50);
    }

    else
    {
        write("You feel a bit silly wearing a robe obviously meant for a " + 
            "woman. The silky material feels nice, but it hugs your body " + 
            "too closely in some spots, hanging loose in others.\n");
        say(QCTNAME(TP) + " squeezes into the silky black robe. He looks " + 
            "a bit silly wearing a garment obviously meant for a woman.\n");
    }
    worn = 1;
    return 1;
}
/* Function name : Remove
 * Description : When removed by a female, it will make her look hideous,
 *     no matter what the original appearance was. Sets worn status to
 *     false.
 * Returns : 0 and 1
*/

mixed
remove(object what)
{
    if (what != TO || !TP)
        return 0;

    if (TP->query_gender()==1)
    {
        write("You regretfully remove the silky black robe, feeling less " + 
            "confident and a bit self conscious.\n");
        if(!TP->query_npc())
            say(QCTNAME(TP) + " hesitantly removes the silky black robe.\n");
        TP->set_appearance_offset(50);
    }
    else
    {
        write("You remove the silky black robe with a sigh of relief.\n");
        if(!TP->query_npc())
            say(QCTNAME(TP) + " removes the silky black robe with a sigh of " + 
                "relief.\n");
    }
    worn = 0;
    return 1;
}

