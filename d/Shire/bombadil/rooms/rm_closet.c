/*
 * Wardrobe/closet in Tom's house
 * By Finwe, January 2001
 */
 
#pragma strict_types

#include "/d/Shire/sys/defs.h" 
#include "../local.h"
 
inherit HOUSE_BASE;

void
create_house_room()
{
    set_short("A large wardrobe room");
    set_long("This large room is lined with shelves, drawers, " +
        "and poles where clothes are hung. The room is quite open, " +
        "allowing someone room to dress. A bench sits under the " +
        "south window. Candles are grouped in clusters giving the " +
        "room a soft light with the lamps hanging from the ceiling. " +
        "A soft rug covers the floor and a small brazier sits on " +
        "a table next to the bench.\n");
// brazier
    add_item(({"brazier"}),
        "This is a small square metal bowl with some coals under " +
        "a grill. The brazier is unlit but is used to heat items " +
        "such as curling wands and hair curlers. The brazier has " +
        "three feet that enable it to sit safely on a small table " +
        "next to the bench.\n");
    add_item("coals",
        "The coals are black chunks that sit beneath the brazier " +
        "grill. They are unlit and provide a means for heating " +
        "items such as curling wands and hair rollers. They also " +
        "provide some warmth to the wardrobe.\n");
    add_item(({"grill", "brazier grill", "mesh"}),
        "The grill is a criss-cross piece of metal that sits above " +
        "the coals. It is sturdy looking and provides a surface " +
        "for heating items.\n");
    add_item("table",
        "The table is about waist high and circular. It's made of " +
        "wood and sits next to the bench. On the table sits a brazier.\n");
// closet
    add_item(({"shelves"}),
        "The shelves are sturdy and made of wood. They are full " +
        "of accessories such as boxes, shoes, belts, and other " +
        "things for dressing. Some of the shelves are as tall as " +
        "the room while others are only half as tall, sitting on " +
        "top of sets of drawers.\n");
    add_item("drawers",
        "The drawers are stacked side by side and made of wood. " +
        "There are a few sets of them beneath some shelves. The " +
        "drawers are closed and presumably hold more clothes and " +
        "accessories.\n");
    add_item(({"poles", "clothing poles"}),
        "The clothing poles are round pieces of wood that have " +
        "been smoothed and are used to hang clothes from. There " +
        "are two levels of them in some parts of the wardrobe, " +
        "and are sandwiched between the shelves and drawers. " +
        "On one side of the wardrobe, a multitude of shirts and " +
        "pants hang from them while on the other side, various " +
        "gowns, cloaks, blouses, gowns, and skirts hang from " +
        "another pole.\n");
    add_item("bench",
        "It is large and comfortable looking with a short back. The bench " +
        "sits beneath the south window.\n");
//clothing
//  gowns
    add_item(({"gowns"}),
        "The gowns are woven from fine fabrics. They are full, " +
        "reach to the ground, and are different bright colors. The " +
        "sleeves of the gowns are long, short, and three quarter " +
        "length. The bodice, or top part of the gowns, are square, " +
        "round, 'V', high, and boat necked. They are generally " +
        "plain looking while some have a little ornamentation on " +
        "them.\n");
    add_item(({"ornamentation"}),
        "The ornamentation on the clothing is  simple. It's " +
        "simply fine embroidery across the bodice and the hem of " +
        "the clothing.\n");
    add_item(({"bodice"}),
        "It is the top part of the gown. There are many different " +
        "styles, depending on the cut and fabric of the gown.\n");
    add_item(({"square neck", "square neckline", "square necked"}),
        "It is a neckline cut in the shape of a square.\n");
    add_item(({"round neck", "round neckline", "round necked"}),
        "It is a neckline cut in the shape of a  half circle.\n");
    add_item(({"v neck", "v neckline", "v necked"}),
        "It is a neckline cut in the shape of a 'V'\n");
    add_item(({"high neck", "high neckline", "high necked"}),
        "It is a neckline that goes up to the top of the neck.\n");
    add_item(({"boat neck", "boat neckline", "boat necked"}),
        "It is a neckline similar to the round neckline, but " +
        "only wider.\n");
//  pants
    add_item(({"pants", "trousers", "breeches"}),
        "They are an outer garment covering each leg " +
        "separately. The pants extend from the waist to the " +
        "ankle while the breeches go from the waist down to the " +
        "bottom of the knees. They are bright colored and cut from "+
        "different fabrics. Some pants are folded and sitting on " +
        "the shelves while others are hung from hangers.\n");
//  cloaks
    add_item(({"cloaks"}),
        "The cloaks are a loose, outer garments worn over clothes. " +
        "They protect the wearer from the elements. They are long, " +
        "reaching down to either the ground or down to the calves. " +
        "The cloaks are made from various fabrics.\n");
//  shirts and blouses
    add_item(({"shirts"}),
        "This is a garment for the upper part of the body with a " +
        "collar, sleeves, and a bodice. Some have tails long " +
        "enough to be tucked inside pants. The shirts are soft and " +
        "are many bright colors.\n");
    add_item(({"blouses", "blouse"}),
        "They are loose-fitting garments for women that cover the " +
        "body from the neck to the waist. The blouses have a collar, " +
        "sleeves, a bodice, and are very soft looking. They " +
        "are sewn from bright colored fabrics.\n");
// miscellaneous items
    add_item(({"hanger", "hangers"}),
        "They are pieces of wood that are shaped to fit shirts, " +
        "blouses, and other clothes that hang on them. A sturdy " +
        "wooden bar on the bottom of the hanger allows pants to be " +
        "hung. A metal loop rises from the top of the hanger " +
        "allowing it to be hung on the pole.\n");
    add_item(({"pole"}),
        "They are thick, round poles that hang horizontal between " +
        "the shelves at different levels. The lower poles have " +
        "shirts, blouses, and smaller garments hanging from them "+ 
        "while on the upper poles hang cloaks, gowns and pants.\n");
    add_item(({"boxes", "hat boxes"}),
        "The boxes are of varying sizes and shapes. Some are round," +
        "oval, square, and rectangle. Some are tall enough to " +
        "probably hold quite a bit of stuff while others are small " +
        "enough to hold small, delicate items. All the boxes are " +
        "made of wood, some being stronger looking than others while " +
        "some of the more unusual shaped ones appear to be made " +
        "from light wood, bent into their odd shapes. They are " +
        "stacked on the shelves. All the boxes have lids and are " +
        "closed.\n");
    add_item(({"belts"}),
        "The belts are made of flexible tanned leather. They are " +
        "worn around the waist and used to hold up pants. The " +
        "belts are black and brown and hang from the upper poles " +
        "of the closet.\n");
    add_item(({"girdle"}),
        "The girdles are fashioned from delicate pieces of worked " +
        "metal. Some are silver, golden, and a combination of both. " +
        "They resemble twined leaves, tree branches, running water, " +
        "the stars of the sky, and flowers and other beautiful " +
        "designs. The girdles are worn by women around their " +
        "waists.\n");
    add_item(({"shoes"}),
        "The shoes are made from worked leather attached toughened " +
        "leather. The shoes are laced up the front with the tops " +
        "reach the top of the ankles. They sit on the shelves and " +
        "are in all different styles.\n");
    add_item(({"slippers"}),
        "The slippers are made from softened leather. They are " +
        "light and slide easily on the feet. They slippers are a " +
        "tan color and sit on the shelves.\n");
    add_item(({"boots"}),
        "The boots are made from tanned leather. Some are short, " +
        "reaching the bottom of your calves while others reach the " +
        "bottom of the knees, with the tops turned down. The boots " +
        "are brown, black, yellow, red, green, and other bright " +
        "colors.\n");
    add_item(({"hats"}),
        "The hats are all types and styles. Some are tall and " +
        "pointed while others are low with feathers. They are " +
        "made of cloth and leathers with some decorated with " +
        "feathers. The hats are all different bright colors and " +
        "sit on shelves.\n");
    add_item(({"feathers"}),
        "The feathers are from a wide variety of birds. They are " +
        "single or multi-colored, fluffy or flat, large and small, " +
        "and used to decorate the hats. Some are attached to hats " +
        "while others are carefully laid out on the shelves.\n");
// hair accessories
    add_item(({"accessories"}),
        "They are various items used to make someone look more " +
        "beautiful. You see brushes, mirrors, combs, hair rollers " +
        "and curling wands sitting on the shelves.\n");
    add_item(({"hair brush", "brushes"}),
        "They are silver paddles that fit the hand. The back of " +
        "the paddles are decorated with filigree, shapes of " +
        "animals and landscape scenes. The front of the brushes " +
        "are covered with thousands of bristles and are used for " +
        "brushing the hair and cleaning clothes.\n");
    add_item(({"combs"}),
        "The combs are made from wood and bone. They are instruments " +
        "with a row of teeth used to arrange and smooth hair.\n");    
    add_item(({"hair rollers", "curling irons"}),
        "These are short metal tubes heated on the brazier. Hair " +
        "is wrapped around the tubes in order to make the hair " +
        "curly or wavy.\n");
    add_item(({"mirrors", "mirror"}),
        "They pieces of highly polished metal. They are attached " +
        "to handles to enable the person to hold the mirror. The " +
        "mirrors are various sizes and sit on some shelves.\n");
    add_item(({"jewelry"}),
        "They look very expensive and cared for. You see rings, " +
        "bracelets, brooches, and necklaces made from gems and " +
        "metals sitting on the shelves.\n");
    add_item(({"rings"}),
        "The rings are made from gold and silver and. Some have " +
        "gems set in the rings. They sit on the shelves.\n");
    add_item(({"bracelets"}),
        "Some bracelets are metal hoops with gems while others are " +
        "made from metal links with gems. Some of the bracelets are " +
        "plain looking.\n");
    add_item(({"necklaces", "necklace",}),
        "The necklaces are both intricate and plain looking. They " +
        "are made from metal, some with gems and others without. " +
        "They are beautiful and look expensive.\n");
    add_item(({"fabrics", "fabric"}),
        "The fabrics are made from various plant and animal fibers. " +
        "They are all soft and smooth looking and in many bright " +
        "colors. You see reds, whites, blues, yellows, greens, as " +
        "well as dark and neutral colors like black, brown, orange, " +
        "and beige.\n");

    reset_shire_room();
    add_item(({"south window", "southern window"}), 
        "@@south_up@@\n");

    set_extra_window("@@window_position@@ set into the " +
        "south wall.");
    add_cmd_item(({"curtains", "drapes"}), "close",
        "@@close_curtains@@");
    add_cmd_item(({"curtains", "drapes"}), "open",
        "@@open_curtains@@");
    num_of_windows=1;

    add_exit(ROOMS_DIR + "rm_bdrm",  "north");
}
void
init()
{
    ::init();

}


void
reset_shire_room()
{
}
