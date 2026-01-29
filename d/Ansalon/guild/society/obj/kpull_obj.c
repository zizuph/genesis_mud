/*
 * /d/Ansalon/guild/society/obj/kpull_obj.c
 *
 * Copyright (c) 2001 by Alyssa Hardy
 *
 * Copyright notice, please read.
 *
 * You are welcome to read this file for information & education purposes.
 * However, you are expressly forbidden to copy this code for use in any
 * other mud. This code is part of Genesis and we want Genesis to remain
 * unique. You must invent your own world on your own mud.
 *
 * Instead of having a million different objects, here is
 * the object that sets them all up.
 * 
 * Gwyneth, January 2001
 */
inherit "/std/object";
#include <stdproperties.h>

public void
setup_junk(int num)
{
    switch(num)
    {
    case 0:
        set_name("button");
        set_adj(({"brass"}));
        set_short("brass button");
        set_long("This is a small brass button. Four holes are in the " +
            "center for sewing it onto a piece of clothing. Bits of thread " +
            "still cling to one of the holes.\n");
        break;
    case 1:
        set_name("card");
        set_adj(({"playing"}));
        set_short("playing card");
        set_long("This is the a single card from a deck used to play 'Black " +
            "Banshee'. This is the highest card, depicting Takhisis, Queen " +
            "of darkness.\n");
        break;
    case 2:
        set_name("cord");
        set_adj(({"red", "silk"}));
        set_short("red silk cord");
        set_long("This is a thin silk cord. It was most likely used to " +
            "open and close fancy drapes before it was detached.\n");
        break;
    case 3:
        set_name("crystal");
        set_adj(({"yellow"}));
        set_short("yellow crystal");
        set_long("This beautifully coloured yellow crystal is the length and " +
            "width of a man's index finger. It sparkles and shines when " +
            "turned in the light.\n");
        break;
    case 4:
        set_name("cymbals");
        set_adj(({"pair", "pairs", "of", "finger"}));
        set_short("pair of finger cymbals");
        set_pshort("pairs of finger cymbals");
        set_long("This is a tiny pair of brass plates that are attached to the " +
            "the index finger and thumb. When clashed together, a lovely " +
            "sound results.\n");
        break;
    case 5:
        set_name("doll");
        set_adj(({"raggedy"}));
        set_short("raggedy doll");
        set_long("This is a well-loved doll by the looks of it. It has brown " +
            "yarn hair, a blue-checked dress, and tiny black shoes. One beady " +
            "eye is missing, and half the hair has been pulled or worn out.\n");
        break;
    case 6:
        set_name("earring");
        set_adj(({"copper"}));
        set_short("copper earring");
        set_long("This is a slightly tarnished copper earring. Three slender " +
            "copper ropes dangle from a single copper stud.\n");
        break;
    case 7:
        set_name("fur");
        set_adj(({"bit", "of", "rabbit", "bits"}));
        set_short("bit of rabbit fur");
        set_pshort("bits of rabbit fur");
        set_long("This bit of rabbit fur is dark brown and soft to the " +
            "touch.\n");
        break;
    case 8:
        set_name("hoof");
        set_adj(({"minotaur"}));
        set_short("minotaur hoof");
        set_long("This is the hoof of a minotaur. It looks rather worn, " +
            "as if from years and years of walking.\n");
        break;
    case 9:
        set_name(({"horseshoe", "shoe"}));
        set_adj(({"horse", "iron"}));
        set_short("iron horseshoe");
        set_long("A few nails still stick out of this rusted iron horseshoe, " +
            "but they are too worn out to be dangerous. Some people think " +
            "horseshoes bring good luck.\n");
        break;
    case 10:
        set_name("box");
        set_adj(({"ivory", "sealed"}));
        set_short("sealed ivory box");
        set_long("This box has been carved from a solid block of ivory, and " +
            "hollowed out in the middle, leaving two pieces that fit " +
            "together seamlessly. It has been sealed, however, and there is " +
            "no way to open it again.\n");
        break;
    case 11:
        set_name("lace");
        set_adj(({"boot", "leather"}));
        set_short("leather boot lace");
        set_long("This is a perfectly good boot lace, and it should still " +
            "be with the boot!\n");
        break;
    case 12:
        set_name("leaf");
        set_adj(({"red", "orange", "red-orange"}));
        set_short("red-orange leaf");
        set_long("This leaf is in the last of its days, as it turns from " +
            "green to red-orange to brown. This one most likely fell to the " +
            "ground in the fall, and was picked up as a lovely and " +
            "interesting item.\n");
        break;
    case 13:
        set_name(({"pick", "lockpick"}));
        set_adj(({"lock", "bent"}));
        set_short("bent lockpick");
        set_long("This lockpick used to be quite useful, but it's been bent " +
            "out of shape beyond use now.\n");
        break;
    case 14:
        set_name("mouse");
        set_adj(({"toy"}));
        set_short("toy mouse");
        set_long("This is a knitted stuffed brown mouse with a piece of yarn " +
            "as a tail.\n");
        break;
    case 15:
        set_name("petal");
        set_adj(({"rose", "blue"}));
        set_short("blue rose petal");
        set_long("This petal has the delicate scent of a rose in full " +
            "bloom. Its surface is silky soft, and the unusual shade of " +
            "blue!\n");
        break;
    case 16:
        set_name("key");
        set_adj(({"piano", "ivory"}));
        set_short("piano key");
        set_long("Made of ivory, this piano key is a soft white.\n");
        break;
    case 17:
        set_name("pillow");
        set_adj(({"small", "white"}));
        set_short("small white pillow");
        set_long("This is a small white pillow, just big enough to tote around " +
            "and still be useful for sleeping. It is still white, but that " +
            "won't last long.\n");
        break;
    case 18:
        set_name("quill");
        set_adj(({"feather"}));
        set_short("feather quill");
        set_long("This multi-coloured feather quill still has a black stain " +
            "on the tip from the last ink it was dipped in. The ink is dry, " +
            "however, and you can't write with it.\n");
        break;
    case 19:
        set_name("rope");
        set_adj(({"frayed"}));
        set_short("frayed rope");
        set_long("This is a short length of strong braided rope, frayed on each " +
            "end.\n");
        break;
    case 20:
        set_name("seed");
        set_adj(({"dried"}));
        set_short("dried seed");
        set_long("This is a large dried seed with a slightly greenish tint.\n");
        break;
    case 21:
        set_name("watchamagoozit");
        set_adj(({"metal"}));
        set_short("metal watchamagoozit");
        set_long("This metal watchamagoozit looks like it belongs in a " +
            "gnomish invention. Hopefully nothing serious comes about " +
            "from it being missing...\n");
        break;
    case 22:
        set_name("statue");
        set_adj(({"kender"}));
        set_short("kender statue");
        set_long("This is an intricately detailed statue of a mischievous " +
            "looking kender. A small half-smile has been added to his face, " +
            "and a twinkle of excitement can be seen in his eyes.\n");
        break;
    case 23:
        set_name("strip");
        set_adj(({"leather"}));
        set_short("leather strip");
        set_long("This is just a plain strip of leather. There's no telling " +
            "what its use was.\n");
        break;
    case 24:
        set_name("ticket");
        set_adj(({"old"}));
        set_short("old ticket");
        set_long("This is a tattered piece of paper with the markings of " +
            "a ticket barely visible.\n");
        break;
    case 25:
        set_name("tip");
        set_adj(({"sword"}));
        set_short("sword tip");
        set_long("This is the tip of a broken iron sword. It is still " +
            "sharp!\n");
        break;
    default:
        set_name("twig");     
        set_adj(({"crooked"}));
        set_short("crooked twig");
        set_long("This crooked twig has been plucked recently from a living " +
            "tree or bush, as it is still green.\n");
        break;
    }
}

public void
create_object()
{
    add_name("junk");
    add_pname("junks");
    add_prop(OBJ_I_WEIGHT, 40 + random(15));
    add_prop(OBJ_I_VOLUME, 110 + random(15));
    remove_prop(OBJ_I_VALUE);
}
